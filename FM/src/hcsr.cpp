#include "hcsr.h"
                       // outside leads to ground and +5V
int val = 0;           // variable to store the value read
int HCSR::hcsrmain()
{
  //读取感测器的数值
  int sensorValue = digitalRead(val);
  Serial.println(sensorValue);
  return sensorValue;
}

void HCSR::init() {
  Serial.begin(9600);
  pinMode(val, INPUT);//感测器的输出为Arduino的输入
}
