// 从机Slave
#include "Wire.h"

#define I2C_DEV_ADDR 0x55

uint32_t i = 0;

/*
  onRequest()函数：用于处理主机的请求，在每次请求时，
  向主机发送递增的数据包计数，并打印调试信息。
*/
void onRequest(){
  Wire.print(i++);
  Wire.print("Packets.");
  Serial.println("onRequest");
}

//  onReceive()函数：用于处理主机发送的数据，在接收到数据时，打印接收到的数据内容和长度。
void onReceive(int len){
  Serial.printf("onReceived[%d]: ", len);
  while (Wire.available()){
    Serial.write(Wire.read());
  }
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Wire.onReceive(onReceive); // 注册接收回调函数
  Wire.onRequest(onRequest); // 注册请求回调函数
  Wire.begin((uint8_t)I2C_DEV_ADDR); // 初始化I2C从机

  // 如果是ESP系列芯片，可以使用slaveWrite函数发送初始消息
#if CONFIG_IDF_TARGET_ESP#@
  char message[64];
  snprintf(message, 64, "%u Packets.", i++);
  Wire.slaveWrite((uint8_t *)message, strlen(message));
#endif
}

void loop() {

}