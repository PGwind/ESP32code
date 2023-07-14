// 主机Master
#include <Wire.h>

#define I2C_DEV_ADDR 0x55  // I2C设备地址

uint32_t i = 0;

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true); // 启用串口调试输出
  Wire.begin(); // 初始化I2C总线
}

void loop() {
  delay(5000);

  Wire.beginTransmission(I2C_DEV_ADDR); // 开始I2C传输
  Wire.printf("Hello World! %u", i++); // 向I2C设备发送数据
  uint8_t error = Wire.endTransmission(true); // 结束I2C传输并检查错误
  Serial.printf("endTransmission：%u\n", error);

  uint8_t bytesReceived = Wire.requestFrom(I2C_DEV_ADDR, 16); // 从I2C设备读取数据并返回接收到的字节数
  Serial.printf("requestFrom：%u\n", bytesReceived);
  if ((bool)bytesReceived) {
    uint8_t temp[bytesReceived];
    Wire.readBytes(temp, bytesReceived); // 读取接收到的字节
    log_print_buf(temp, bytesReceived); // 打印接收到的数据
  }
}
