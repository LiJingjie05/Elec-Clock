#ifndef __MQTT_H__
#define __MQTT_H__

#include <WiFi.h>
#include <PubSubClient.h>

class MQTT
{
    private:

    public:
    // void mqtt_init();
    // void subTopic(); 
     void pubTopic(const char* Mqtt_pub_topic,String json);
    // void connectMQTTserver();
    void mqtt_loop();
    void subscribeTopic();
    void mqtt_init();
    
};

//void callback(char* topic, byte* payload, unsigned int length);
void connectMQTTserver();
void receiveCallback(char* topic, byte* payload, unsigned int length);
 
extern const char* Mqtt_sub_topic; 
extern const char* Mqtt_pub_topic; 

extern bool mqtt_flag;

#endif