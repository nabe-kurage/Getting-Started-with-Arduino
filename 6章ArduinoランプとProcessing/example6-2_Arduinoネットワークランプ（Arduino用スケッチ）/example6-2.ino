// Arduinoネットワークランプ
const int SENSOR = 0;
const int R_LED = 9;
const int G_LED = 10;
const int B_LED = 11;
const int BUTTON = 12;

int val = 0;          // センサ値
int btn = LOW;
int old_btn = LOW;
int state = 0;
char buffer[7];       // 6文字 + 終端用
int pointer = 0;
byte inByte = 0;

byte r = 0;
byte g = 0;
byte b = 0;

void setup() {
  Serial.begin(9600);     // シリアルポート開始
  pinMode(BUTTON, INPUT); // ボタン入力設定
}

void loop() {
  // センサー値を読み取り、Processingへ送信
  val = analogRead(SENSOR);
  Serial.println(val);

  // PC(Processing)からのデータ受信
  if (Serial.available() > 0) {
    inByte = Serial.read();

    // マーカー '#' が来たら続く6文字を色情報として受信
    if (inByte == '#') {
      while (pointer < 6) {
        buffer[pointer] = Serial.read();
        pointer++;
      }
      // RGBに変換（#RRGGBB の順）
      r = hex2dec(buffer[1]) + hex2dec(buffer[0]) * 16;
      g = hex2dec(buffer[3]) + hex2dec(buffer[2]) * 16;
      b = hex2dec(buffer[5]) + hex2dec(buffer[4]) * 16;

      pointer = 0; // バッファリセット
    }
  }

  // ボタンの状態を読み取ってトグル
  btn = digitalRead(BUTTON);
  if ((btn == HIGH) && (old_btn == LOW)) {
    state = 1 - state; // 0⇔1切替
  }
  old_btn = btn;

  // LED制御
  if (state == 1) {
    analogWrite(R_LED, r);
    analogWrite(G_LED, g);
    analogWrite(B_LED, b);
  } else {
    analogWrite(R_LED, 0);
    analogWrite(G_LED, 0);
    analogWrite(B_LED, 0);
  }

  delay(100); // 0.1秒待機
}

// 16進数文字を整数値に変換
int hex2dec(byte c) {
  if (c >= '0' && c <= '9') {
    return c - '0';
  } else if (c >= 'A' && c <= 'F') {
    return c - 'A' + 10;
  }
  return 0; // 想定外の文字は0
}
