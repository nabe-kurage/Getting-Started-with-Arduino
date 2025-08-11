// Cdsアナログ入力の値に応じてLEDの明るさを変える

const int LED = 9;
int val = 0;

void setup(){
  pinMode(LED, OUTPUT);
  // アナログピンは自動的に入力として設定される
}


void loop() {
  val = analogRead(0); // 読み取りたいアナログピンの番号を指定

  analogWrite(LED, val/4); // analogReadは最大値1023なので４で割って調整する
  delay(10);
}