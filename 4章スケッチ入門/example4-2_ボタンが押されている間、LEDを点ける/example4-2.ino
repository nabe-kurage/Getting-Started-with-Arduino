// ボタンが押されている間、LEDを点ける

const int LED = 13;       // LEDが接続されているピン
const int BUTTON = 7;     // プッシュボタンが接続されているピン

int val = 0;              // ボタンの入力状態を記録する変数

void setup() {
  pinMode(LED, OUTPUT);   // LEDピンを出力に設定
  pinMode(BUTTON, INPUT); // ボタンピンを入力に設定
}

void loop() {
  val = digitalRead(BUTTON); // ボタンの状態を読み取る

  if (val == HIGH) {
    digitalWrite(LED, HIGH); // ボタンが押されていればLEDを点灯
  } else {
    digitalWrite(LED, LOW);  // 押されていなければLEDを消灯
  }
}
