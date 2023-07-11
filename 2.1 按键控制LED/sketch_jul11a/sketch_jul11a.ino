int switchPin = 25; //按键所接GPIO口
int ledPin = 4; //LED接口
int ledStatus = 0; //LED目前状态

void setup() {
  pinMode(switchPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  ledStatus = HIGH;
}

void loop() {
  int val = digitalRead(switchPin); //读取开关引脚的电平状态
  if (val == LOW) //低电平有效
  {
    ledStatus = !ledStatus;
    digitalWrite(ledPin, ledStatus);
  }
}
