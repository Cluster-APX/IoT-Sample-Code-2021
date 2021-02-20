/*
 * เชื่อมต่อไปยัง MQTT Broker ผ่าน WiFi
 * แสดงผลการทำงาน (Debug Message) ผ่าน Serial Port
 * Subscribe ไปยัง Topic ที่ต้องการและแสดงผลลัพธ์ผ่าน Serial Port
 * Publish ข้อมูล 1 ครั้งแต่เชื่อมต่อสำเร็จ
 */


#include "EspMQTTClient.h"


EspMQTTClient client
(
  "My-IoT-Network", // SSID, ชื่อ WiFi ที่ต้องการเชื่อมต่อ
  "mywifipassword", // WiFi Password
  "broker.mqttdashboard.com",  // MQTT Broker Address
  "",   // MQTT Username
  "",   // MQRR Password
  "MyDeviceID-7186243",     // MQTT Device ID
  1883              // MQTT Port
);


void setup()
{

  // ใช้งาน Serial Port
  Serial.begin(115200);

  // แสดงผลการทำงาน (Debug Message) ผ่าน Serial Port
  client.enableDebuggingMessages();

}


// Function นี้ทำงานเมื่อ WiFi และ MQTT เชื่อมต่อไปยัง MQTT Broker สำเร็จ
void onConnectionEstablished()
{
  
  // Subscribe
  client.subscribe("fibo/rpc", [](const String & payload)
  {

    // แสดงข้อความ (Message) เมื่อมีการส่งข้อมูลไปยัง Topic ที่ทำการ Subscribe ไว้
    Serial.println(payload);
    
  });

  // Publish
  client.publish("fibo/log", "My IoT Device Connected.");

}


void loop()
{

  // MQTT Library Core Function.
  client.loop();
  
}
