/**
 * 函数名：finger_matc
 * 功能：实现指纹对比，匹配开门
 **/
#include "finger.h"

void MYFINGER::matc_finger()
{
    //jianche();
    //getFingerprintID();
    delay(50);
    getFingerprintIDez();
   
}

void jianche()
{
    finger.getTemplateCount();

    if (finger.templateCount == 0) 
    {
        Serial.print("Sensor doesn't contain any fingerprint data. Please run the 'enroll' example.");
        Serial.println("还没有任何指纹，请先添加至少一个指纹");
        return;
    }
    else 
    {
        Serial.println("Waiting for valid finger...");
        Serial.print("Sensor contains "); 
        Serial.print(finger.templateCount); 
        Serial.println(" templates");
    }
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
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
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
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

  // OK converted!
  p = finger.fingerSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }

  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);

  return finger.fingerID;
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() 
{
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;

  // found a match!
  Serial.print("Found ID #"); 
  Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); 
  Serial.println(finger.confidence);
  Serial.println("通过指纹进行解锁，欢迎您！");
  finger_flag = true;
  return 0;
}