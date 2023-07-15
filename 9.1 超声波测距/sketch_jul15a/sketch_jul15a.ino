const int trigPin = 4;
const int echoPin = 16;

void setup() {
  Serial.begin(115200);
  delay(200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // 在Trig引脚发送15us脉冲
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(15); // 15us
  digitalWrite(trigPin, LOW);

  // 读取Echo引脚脉冲时长
  auto t = pulseIn(echoPin, HIGH);
  double dis = t * 0.01715; // 单位：CM
  Serial.print(dis);
  Serial.println(" cm");

  delay(200);
}
