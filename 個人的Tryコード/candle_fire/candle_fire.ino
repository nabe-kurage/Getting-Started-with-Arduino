// 炎が燃えるように光るライト
const int LED = 9;

void setup() {
  pinMode(LED, OUTPUT);
  randomSeed(analogRead(0)); // ランダムの初期化（未使用ピンからノイズ取得）
}

void loop() {
  int brightness = random(20, 255); // ゆらぎ範囲
  analogWrite(LED, brightness);
  delay(random(30, 100)); // 不規則な点滅間隔
}