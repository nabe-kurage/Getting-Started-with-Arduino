// ボタンが押されている時間に応じてLEDの明るさを変える

// 装置の定義
const int BUTTON = 7;
const int LED = 9;

// スイッチの状態の変数の定義
int val = 0;
int old_val = 0;
int state = 0;


int brightness = 128; // LEDライトの明るさ
unsigned long startTime = 0; // スイッチを押し始めた時間

void setup() {
  pinMode(BUTTON, INPUT); //
  pinMode(LED, OUTPUT);
}

void loop() {
  val = digitalRead(BUTTON);

  // ボタンが押された瞬間（立ち上がり）を検出
  if (val == HIGH && old_val == LOW) {
    state = 1 - state;        // ON/OFF 状態をトグル
    startTime = millis();     // ボタンを押し始めた時間を記録
    delay(10);                // チャタリング対策の軽い遅延
  }

  // ボタンが押され続けている状態を検出
  if (val == HIGH && old_val == HIGH) {
    // 0.5秒以上スイッチを押し続けていた場合の判定
    if (state == 1 && millis() - startTime > 500) {
      brightness++;
      delay(10);  // 明るさ変更のタイミング調整

      // 最大の明るさになったら明るさをリセットする
      if (brightness > 255) {
        brightness = 0;
      }
    }
  }

  // 前回のボタン状態を保存
  old_val = val;

  // LEDにPWMで明るさを出力
  if (state == 1) {
    analogWrite(LED, brightness);
  } else {
    analogWrite(LED, 0);
  }
}
