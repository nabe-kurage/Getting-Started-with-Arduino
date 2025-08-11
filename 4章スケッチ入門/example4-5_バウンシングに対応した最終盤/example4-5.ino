// ボタンが押されている間、LEDを点ける

const int LED = 13;       // LEDが接続されているピン
const int BUTTON = 7;     // プッシュボタンが接続されているピン

int val = 0;              // ボタンの入力状態を記録する変数
int old_val = 0;        //
int state = 0;            //LEDの状態

void setup() {
  
  pinMode(LED, OUTPUT);   // LEDピンを出力に設定
  pinMode(BUTTON, INPUT); // ボタンピンを入力に設定
}

void loop() {
  val = digitalRead(BUTTON); // ボタンの状態を読み取る

  if (val == HIGH && old_val == LOW) {
    state = 1 - state; //true falseを切りかえる装置になっている
    delay(50);
  }
  
  old_val = val;

  if (state == 1) {
      digitalWrite(LED, HIGH); // LEDをオンにする
  } else {
      digitalWrite(LED, LOW); // LEDをオフにする
  }
}
