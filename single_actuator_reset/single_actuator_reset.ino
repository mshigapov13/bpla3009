
byte in2 = 13;
byte in1 = 12;

void setup() {
  pinMode(in2, OUTPUT);
  pinMode(in1, OUTPUT);
}

void loop() {

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  delay(6000);
}
