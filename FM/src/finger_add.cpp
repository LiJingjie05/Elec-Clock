/**
 * 函数名：finger_add
 * 功能：实现创建指纹
 **/
#include "finger.h"
#include "mykeyboard.h"

//Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
uint8_t id;
void MYFINGER::add_finger()
{
    Serial.println("Ready to enroll a fingerprint!");
    Serial.println("即将开始录入指纹!");
    Serial.println("Please type in the ID # (from 1 to 127) you want to save this finger as...");
    Serial.println("请输入一个用来存储指纹的ID,在1到127之间!");
    gui.label("请输入一个用来存储指纹的ID,在1到127之间!");
    id = readnumber();
    if (id <= 0 || id >127) 
    {// ID #0 not allowed, try again!
        id = 0;
        return;
    }
    Serial.print("New Finger ID #");
    Serial.println(id);
    while (!  getFingerprintEnroll() );
}
//键盘输入转换
uint8_t readnumber(void) {
  uint8_t iddd = 0;
  uint8_t idd = 0;
  char key;
  const char * textread = "";
  int count = 0;

  while(1)
    {
      key = myKeypad.getKey();
      if(key !=NO_KEY)
      {
        textread = textread+key;
        Serial.println(textread);
        gui.label(textread);
        idd =(uint8_t)(key)-'0';
        Serial.println(idd);
        iddd = iddd*10+idd;
        Serial.println(iddd);
        count++;
      }
      if(count == 3)
      {
        count = 0;
        break;
      }
    }
    Serial.println(iddd);
  return iddd;
}

uint8_t getFingerprintEnroll() 
{

  int p = -1;
  Serial.print("Waiting for valid finger to enroll as #"); Serial.println(id);
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      Serial.println("第一次录入成功！");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("请按手指!");
      while(p == FINGERPRINT_NOFINGER )
      {
        p = finger.getImage();
      }
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      Serial.println("转换生成模板成功！");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  Serial.println("Remove finger");
  Serial.println("松开手指！");
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  Serial.print("ID "); Serial.println(id);
  p = -1;
  Serial.println("Place same finger again");
  Serial.println("请再次按下相同的手指！");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      while(p == FINGERPRINT_NOFINGER )
      {
        p = finger.getImage();
      }
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      gui.label("指纹创建失败！");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      gui.label("指纹创建失败！");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      gui.label("指纹创建失败！");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      gui.label("指纹创建失败！");
      return p;
    default:
      Serial.println("Unknown error");
      gui.label("指纹创建失败！");
      return p;
  }

  // OK converted!
  Serial.print("Creating model for #");  Serial.println(id);
  Serial.print("创建指纹成功！ #");Serial.println(id);
  gui.label("指纹创建成功！");
  delay(2000);
  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("Prints matched!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    gui.label("指纹创建失败！");
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println("Fingerprints did not match");
    gui.label("指纹创建失败！");
    return p;
  } else {
    Serial.println("Unknown error");
    gui.label("指纹创建失败！");
    return p;
  }

  Serial.print("ID "); Serial.println(id);
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    Serial.println("Stored!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    gui.label("指纹创建失败！");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not store in that location");
    gui.label("指纹创建失败！");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    gui.label("指纹创建失败！");
    return p;
  } else {
    Serial.println("Unknown error");
    gui.label("指纹创建失败！");
    return p;
  }

  return true;
}