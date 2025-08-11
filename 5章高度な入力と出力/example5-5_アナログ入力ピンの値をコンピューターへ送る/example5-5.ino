// ログを取る用
const int SENSOR = 0;       // LEDが接続されているピン
int val = 0;              // ボタンの入力状態を記録する変数

void setup() {
  Serial.begin(9600);
}

void loop() {
  val = analogRead(SENSOR);

  Serial.println(val);
  delay(100);
}
