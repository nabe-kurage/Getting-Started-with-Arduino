// LEDのフェードインとフェードアウト

const int LED = 9; 
int i = 0; // カウントダウンに使用


void setup(){
  pinMode(LED, OUTPUT); // LEDのピンを出力に設定
}


void loop() {
  for(i = 0; i<255; i++){
    analogWrite(LED, i);
    delay(10);
  }

  for(i = 255; i>0; i--){
    analogWrite(LED, i);
    delay(10);
  }
}


// 炎が燃えるように光るライト
// const int LED = 9;

// void setup() {
//   pinMode(LED, OUTPUT);
//   randomSeed(analogRead(0)); // ランダムの初期化（未使用ピンからノイズ取得）
// }

// void loop() {
//   int brightness = random(100, 255); // ゆらぎ範囲
//   analogWrite(LED, brightness);
//   delay(random(30, 100)); // 不規則な点滅間隔
// }