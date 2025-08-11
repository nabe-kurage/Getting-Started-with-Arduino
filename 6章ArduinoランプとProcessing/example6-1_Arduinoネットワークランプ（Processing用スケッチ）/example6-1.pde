import processing.serial.*;
import java.net.*;
import java.io.*;
import java.util.*;

String feed = "https://blog.arduino.cc/feed/";

int interval = 5 * 60 * 1000;
int lastTime;
int love = 0;
int peace = 0;
int arduino = 0;
int light = 0;

processing.serial.Serial port;
color c;
String cs;

String buffer = "";
PFont font;

void setup() {
  size(640, 480);
  frameRate(10);

  font = createFont("Helvetica", 24);
  fill(255);
  textFont(font, 32);

  // 利用可能なシリアルポートの先頭を使用（必要ならprintln(Serial.list())で確認）
  String arduinoPort = processing.serial.Serial.list()[0];
  port = new processing.serial.Serial(this, arduinoPort, 9600);

  lastTime = millis();
  fetchData();
}

void draw() {
  // 先に色を作ってから背景に反映
  c  = color(peace, love, arduino);
  cs = "#" + hex(c, 6);
  background(c);

  int n = max(0, (interval - (millis() - lastTime)) / 1000);

  text("Arduino Networked Lamp", 10, 40);
  text("Reading feed:", 10, 100);
  text(feed, 10, 140);

  text("Next update in " + n + " seconds", 10, 450);
  text("peace", 10, 200);  text("" + peace,   130, 200);  rect(200, 172, peace,   28);
  text("love",  10, 240);  text("" + love,    130, 240);  rect(200, 212, love,    28);
  text("arduino",10, 280); text("" + arduino, 130, 280);  rect(200, 252, arduino, 28);

  text("sending", 10, 340);
  text(cs, 200, 340);

  text("light level", 10, 380);             // 0–1023 → 0–100 目安表示
  rect(200, 352, light / 10.23, 28);

  if (n <= 0) {
    fetchData();
    lastTime = millis();
  }

  // 色コードをArduinoへ（改行で区切る）
  port.write(cs + "\n");

  // Arduinoからのライトレベルを受信（数値+改行を想定）
  while (port.available() > 0) {
    int inByte = port.read();
    if (inByte != '\n') {
      buffer += char(inByte);
    } else {
      buffer = trim(buffer);
      if (buffer.length() > 0) {
        try {
          light = int(buffer);
        } catch (Exception e) {
          // 予期しない文字列は無視
        }
      }
      buffer = "";
    }
  }
}

void fetchData() {
  String chunk;
  love = 0;
  peace = 0;
  arduino = 0;

  try {
    URL url = new URL(feed);
    URLConnection conn = url.openConnection();
    conn.connect();

    BufferedReader in = new BufferedReader(new InputStreamReader(conn.getInputStream()));
    String data;

    while ((data = in.readLine()) != null) {
      StringTokenizer st = new StringTokenizer(data, " \"<>.,()[]{}");
      while (st.hasMoreTokens()) {
        chunk = st.nextToken().toLowerCase();
        if (chunk.indexOf("love") >= 0)    love++;
        if (chunk.indexOf("peace") >= 0)   peace++;
        if (chunk.indexOf("arduino") >= 0) arduino++;
      }
    }
    in.close();

    // 上限64 → 0–255にスケーリング
    love    = min(love,    64) * 4;
    peace   = min(peace,   64) * 4;
    arduino = min(arduino, 64) * 4;

  } catch (Exception ex) {
    ex.printStackTrace();
    System.out.println("ERROR: " + ex.getMessage());
  }
}
