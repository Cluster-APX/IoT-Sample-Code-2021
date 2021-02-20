/*
 * เชื่อมต่อไปยัง MQTT Broker ผ่าน WiFi
 * แสดงผลการทำงาน (Debug Message) ผ่าน Serial Port
 * Subscribe ไปยัง Topic ที่ต้องการและแสดงผลลัพธ์ผ่าน Serial Port
 * อ่านค่า Analog และ Digital เพื่อแสดงค่าทั้งหมดที่อ่านได้ผ่านทาง Serial Port
 * เขียนค่า Digital เพื่อควบคุม Relay ที่ต่อกับหลอดไฟและ Buzzer
 */


#include "EspMQTTClient.h"


#define IN_ANA_0  36 // กำหนด Input Port สำหรับ Temperature
#define IN_ANA_1  39 // กำหนด Input Port สำหรับ Infrared
#define IN_ANA_2  34 // กำหนด Input Port สำหรับ Light
#define IN_DIGI_0 35 // กำหนด Input Port สำหรับ Detector

#define OUT_DIGI_0  32  // Output Port สำหรับไฟสีแดง
#define OUT_DIGI_1  33  // Output Port สำหรับไฟสีเหลือง
#define OUT_DIGI_2  23  // Output Port สำหรับไฟสีเขียว
#define OUT_DIGI_3  22  // Output Port สำหรับ Buzzer


int DATA_ANA_0  = 0;  // ตัวแปรสำหรับเก็บค่า Analog ที่อ่านได้
int DATA_ANA_1  = 0;  // ตัวแปรสำหรับเก็บค่า Analog ที่อ่านได้
int DATA_ANA_2  = 0;  // ตัวแปรสำหรับเก็บค่า Analog ที่อ่านได้
int DATA_DIGI_0 = 0;  // ตัวแปรสำหรับเก็บค่า Digital ที่อ่านได้


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

  // ตั้งค่า Port เป็น Input
  pinMode(IN_ANA_0, INPUT);  // Temperature Analog
  pinMode(IN_ANA_1, INPUT);  // Light Analog
  pinMode(IN_ANA_2, INPUT);  // Infrared Analog
  pinMode(IN_DIGI_0, INPUT);  // Infrared Digital

  // ตั้งค่า Port เป็น Output
  pinMode(OUT_DIGI_0, OUTPUT);  // Relay (RED)
  pinMode(OUT_DIGI_1, OUTPUT);  // Relay (YELLOW)
  pinMode(OUT_DIGI_2, OUTPUT);  // Relay (GREEN)
  pinMode(OUT_DIGI_3, OUTPUT);  // Relay (BUZZER)

  // ทดสอบ Output
  digitalWrite(OUT_DIGI_0, LOW);
  digitalWrite(OUT_DIGI_1, LOW);
  digitalWrite(OUT_DIGI_2, LOW);
  digitalWrite(OUT_DIGI_3, LOW);
  delay(1000);
  digitalWrite(OUT_DIGI_0, HIGH);
  digitalWrite(OUT_DIGI_1, HIGH);
  digitalWrite(OUT_DIGI_2, HIGH);
  digitalWrite(OUT_DIGI_3, HIGH);
  
  // ใช้งาน Serial Port
  Serial.begin(115200);

  // แสดงผลการทำงาน (Debug Message) ผ่าน Serial Port
  client.enableDebuggingMessages();

}


// Function นี้ทำงานเมื่อ WiFi และ MQTT เชื่อมต่อไปยัง MQTT Broker สำเร็จ
void onConnectionEstablished()
{
  
  // Subscribe
  client.subscribe("fibo/rpc/red", [](const String & payload)
  {

    // ควบคุมหลอดไฟสีแดง
    if(payload == "0")
    {
      digitalWrite(OUT_DIGI_0, HIGH);
    }
    else if (payload == "1")
    {
      digitalWrite(OUT_DIGI_0, LOW);
    }
    
  });

}


void loop()
{

  DATA_ANA_0  = analogRead(IN_ANA_0); // อ่านค่า Analog
  DATA_ANA_1  = analogRead(IN_ANA_1); // อ่านค่า Analog
  DATA_ANA_2  = analogRead(IN_ANA_2); // อ่านค่า Analog
  DATA_DIGI_0  = digitalRead(IN_DIGI_0); // อ่านค่า Digital

  // Publish ค่า Temperature
  client.publish("fibo/sensor/temperature/0", String(DATA_ANA_0));
  // Publish ค่า Infrared
  client.publish("fibo/sensor/infrared/0", String(DATA_ANA_1));
  // Publish ค่า Light
  client.publish("fibo/sensor/light/0", String(DATA_ANA_2));
  // Publish ค่า Detector
  client.publish("fibo/sensor/detector/0", String(DATA_DIGI_0));

  // MQTT Library Core Function.
  client.loop();

  delay(250);
  
}
