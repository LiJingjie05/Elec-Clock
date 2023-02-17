#include "mywifi.h"

WiFiManager wifimanager;


void MYWIFI::wifi_init()
{
    WiFi.mode(WIFI_STA);
    wifimanager.autoConnect("AutoConnectAP","password");
    while (WiFi.status() != WL_CONNECTED) 
    {
    delay(500);
    Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}