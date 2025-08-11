// Cdsアナログ入力の値に応じてLEDの点滅レート変更

const int LED = 13;
int val = 0;

void setup(){
  pinMode(LED, OUTPUT);
}


void loop() {
  val = analogRead(0);

  digitalWrite(13, HIGH);
  delay(val);

  digitalWrite(13, LOW);
  delay(val);
}