int ledPin2 = 2;
int ledStatus2 = 0;  //现在的状态
unsigned int prevTime2 = 0; //改变状态时的时间

int ledPin4 = 4;
int ledStatus4 = 0;  
unsigned int prevTime4 = 0;

void setup() {
  pinMode(ledPin2, OUTPUT);
  digitalWrite(ledPin2, HIGH);
  ledStatus2 = HIGH;
  prevTime2 = millis(); //millis(): 本程序已经运行的时间（ms） micros()微秒us

  pinMode(ledPin4, OUTPUT);
  digitalWrite(ledPin4, HIGH);
  ledStatus4 = HIGH;
  prevTime4 = millis(); //millis(): 本程序已经运行的时间（ms） micros()微秒us
}

void loop() {
  unsigned int now = millis(); //程序运行的时间

  if (now - prevTime2 > 3000) //上次改变状态后已经过了3s
  {
    int status  = ledStatus2 == HIGH ? LOW: HIGH;
    digitalWrite(ledPin2, status);
    ledStatus2 = status;
    prevTime2 = now;
  }

  if (now - prevTime4 > 1000) //上次改变状态后已经过了1s
  {
    int status  = ledStatus4 == HIGH ? LOW: HIGH;
    digitalWrite(ledPin4, status);
    ledStatus4 = status;
    prevTime4 = now;
  }
}
