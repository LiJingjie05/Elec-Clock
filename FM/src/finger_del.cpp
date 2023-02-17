/**
 * 函数名：finger_del
 * 功能：实现删除指纹
 **/
#include "finger.h"

void MYFINGER::del_finger()
{
    Serial.println("Please type in the ID # (from 1 to 127) you want to delete...");
    gui.label("请输入一个想要删除的ID,在1到127之间!");
    uint8_t id = readnumber();
    if (id <= 0 || id >=127) {// ID #0 not allowed, try again!
        return;
    }

    Serial.print("Deleting ID #");
    Serial.println(id);

    deleteFingerprint(id);
}

uint8_t deleteFingerprint(uint8_t id) 
{
  uint8_t p = -1;

  p = finger.deleteModel(id);

  if (p == FINGERPRINT_OK) 
  {
    Serial.println("Deleted!");
    gui.label("删除成功！");
  } 
  else if (p == FINGERPRINT_PACKETRECIEVEERR) 
  {
    Serial.println("Communication error");
    gui.label("删除失败！");
  } 
  else if (p == FINGERPRINT_BADLOCATION) 
  {
    Serial.println("Could not delete in that location");
    gui.label("删除失败！");
  } 
  else if (p == FINGERPRINT_FLASHERR) 
  {
    Serial.println("Error writing to flash");
    gui.label("删除失败！");
  } 
  else 
  {
    Serial.print("Unknown error: 0x"); Serial.println(p, HEX);
    gui.label("删除失败！");
  }

  return p;
}