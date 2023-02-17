#include "mqtt.h"

//MQTT服务器地址
const char* mqttServer = "xueluochangan.fun";
String clientId = "ESP32-lock"; 

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

String userChatString;

// 连接MQTT服务器并订阅信息
void connectMQTTserver()
{
  if (mqttClient.connect(clientId.c_str())) 
  { 
    Serial.println("MQTT Server Connected.");
    Serial.println("Server Address:");
    Serial.println(mqttServer);
    Serial.println("ClientId: ");
    Serial.println(clientId);
  } 
  else 
  {
    Serial.print("MQTT Server Connect Failed. Client State:");
    Serial.println(mqttClient.state());
    delay(5000);
  }   
}
 
// 收到信息后的回调函数
void receiveCallback(char* topic, byte* payload, unsigned int length) 
{
    Serial.print("Message Received [");
    Serial.print(topic);
    Serial.print("] ");
    for (int i = 0; i < length; i++) 
    {
        Serial.print((char)payload[i]);
    }
    Serial.println("");
    Serial.print("Message Length(Bytes) ");
    Serial.println(length);
    
    if(String(topic) == "lock/down")
    {
        userChatString = "";
        mqtt_flag = true;
        for (int i = 0; i < length; i++) 
        {
        userChatString += (char)payload[i];
        }
        Serial.print("userChatString = ");
        Serial.println(userChatString); 
        Serial.print("mqtt_flag:");
        Serial.println(mqtt_flag);
        Serial.println("函数回调成功！");
    }
    
    // if ((char)payload[0] == '1') 
    // {     // 如果收到的信息以“1”为开始
    //     //digitalWrite(BUILTIN_LED, LOW);  // 则点亮LED。
    //     Serial.println("LED ON");
    // } 
    // else 
    // {                           
    //     //digitalWrite(BUILTIN_LED, HIGH); // 否则熄灭LED。
    //     Serial.println("LED OFF");
    // }
}
 
// 订阅指定主题
void MQTT::subscribeTopic(){
 
  // 建立订阅主题。主题名称以Taichi-Maker-Sub为前缀，后面添加设备的MAC地址。
  // 这么做是为确保不同设备使用同一个MQTT服务器测试消息订阅时，所订阅的主题名称不同
  // String topicString = "Taichi-Maker-Sub-" + WiFi.macAddress();
  // char Mqtt_sub_topic[topicString.length() + 1];  
  // strcpy(Mqtt_sub_topic, topicString.c_str());
  
  // 通过串口监视器输出是否成功订阅主题以及订阅的主题名称
  if(mqttClient.subscribe(Mqtt_sub_topic))
  {
    Serial.print("Subscribed Topic: ");
    Serial.println(Mqtt_sub_topic);
    Serial.print("订阅[");
    Serial.print(Mqtt_sub_topic);
    Serial.println("]成功！");
    Serial.println("Subscrib Topic:");
    Serial.println(Mqtt_sub_topic);
  } 
  else 
  {
    Serial.print("Subscribe Fail...");
  }  
}

void MQTT::mqtt_init()
{
  mqttClient.setServer(mqttServer, 1883);
  // 设置MQTT订阅回调函数
  mqttClient.setCallback(receiveCallback);
 
  // 连接MQTT服务器
  connectMQTTserver();
  subscribeTopic();
}

void MQTT::mqtt_loop()
{
    if (mqttClient.connected()) 
    { // 如果开发板成功连接服务器
    mqttClient.loop();          // 处理信息以及心跳
    }  
    else 
    {                      // 如果开发板未能成功连接服务器
        connectMQTTserver();        // 则尝试连接服务器
    } 
}

void MQTT::pubTopic(const char* Mqtt_pub_topic,String json)
{
    connectMQTTserver();
    if(mqttClient.publish(Mqtt_pub_topic,json.c_str()))
    {
        Serial.println("Publish Topic:");
        Serial.println(Mqtt_pub_topic);
        Serial.println("Publish message:");
        Serial.println(json.c_str());    
    } 
    else 
    {
        Serial.println("Message Publish Failed."); 
        return;
    }
}
