/**
 * rc522相关代码
 * 引脚连接：VCC->3.3V  RST->IO22  GND->GND
 * 
 * MISO->IO19  MOSI->IO23  SCK->IO18  SDA->21
 * 
 */
#include "rfid.h"

MFRC522 mfrc522(SS_PIN, RST_PIN);
byte rc522_pp[4];
//extern MYGUI gui;

void RFID::init()
{
  mfrc522.PCD_Init();		// Init MFRC522
  delay(4);				// Optional delay. Some board do need more time after init to be ready, see Readme
	mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
}

void RFID::matcID()
{
	if ( ! mfrc522.PICC_IsNewCardPresent()) {
		return;
	}

	// Select one of the cards
	if ( ! mfrc522.PICC_ReadCardSerial()) {
		return;
	}

  for (byte i = 0; i < 4; i++) {
    rc522_pp[i] = mfrc522.uid.uidByte[i];
  } 
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
  if (rc522_pp[0]==0x2C&&rc522_pp[1]==0xC7&&rc522_pp[2]==0xF2&&rc522_pp[3]==0x38)
  {
    Serial.println("欢迎用户1!");
    //gui.label("RFID解锁成功");
    rfid_flag = true;
    //gui.label("RFID解锁成功");//打印信息到屏幕上
  }
  else Serial.println("非系统用户，无法解锁!");
}
