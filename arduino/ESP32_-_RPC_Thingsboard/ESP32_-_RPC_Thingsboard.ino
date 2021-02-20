/*
 * เชื่อมต่อไปยัง MQTT Broker ผ่าน WiFi
 * แสดงผลการทำงาน (Debug Message) ผ่าน Serial Port
 * Publish ข้อมูลของ Sensor ที่อ่านได้หลายตัวไปยัง Thingsboard Cloud
 * Subscribe ไปยัง Topic ที่ Thingsboard Cloud กำหนดเพื่อรับรับคำสั่ง (RPC) และตอบกลับ
 */


#include <ArduinoJson.h>
#include <EspMQTTClient.h>


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


DynamicJsonDocument doc(64);


EspMQTTClient client
(
  "My-IoT-Network", // SSID, ชื่อ WiFi ที่ต้องการเชื่อมต่อ
  "mywifipassword", // WiFi Password
  "thingsboard.cloud",  // MQTT Broker Address
  "Token",   // MQTT Username
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
  client.subscribe("v1/devices/me/rpc/request/+", [](const String & topic, const String & payload)
  {

    deserializeJson(doc, payload);
    String responseTopic = String(topic);
    responseTopic.replace("request", "response");

    if(doc["method"] == "setLightRed")  // Thingsboard ส่งค่า Method สำหรับควบคุม Device
    {

      if(doc["params"] == true) // Thingsboard ส่งค่า Parameter สำหรับเปิดไฟ
      {
        digitalWrite(OUT_DIGI_0, LOW);
        client.publish(responseTopic, "1");
      }
      else if(doc["params"] == false) // Thingsboard ส่งค่า Parameter สำหรับปิดไฟ
      {
        digitalWrite(OUT_DIGI_0, HIGH);
        client.publish(responseTopic, "0");
      }

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
  client.publish("v1/devices/me/telemetry", "{temperature:" + String(DATA_ANA_0) + "}");
  // Publish ค่า Infrared
  client.publish("v1/devices/me/telemetry", "{infrared:" + String(DATA_ANA_1) + "}");
  // Publish ค่า Light
  client.publish("v1/devices/me/telemetry", "{light:" + String(DATA_ANA_2) + "}");
  // Publish ค่า Detector
  client.publish("v1/devices/me/telemetry", "{detector:" + String(DATA_DIGI_0) + "}");

  // Publish ค่าหลอดไฟสีแดง
  int status_red  = (~digitalRead(OUT_DIGI_0)) & 1;
  client.publish("v1/devices/me/telemetry", "{status_red:" + String(status_red) + "}");

  // MQTT Library Core Function.
  client.loop();

  delay(1000);
  
}
