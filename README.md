# IoT-Sample-Code-2021

ตัวอย่าง Code เกี่ยวกับการรับ-ส่งข้อมูลและการสร้าง Service Application (Node-RED) โดยใช้ ESP32, Local Broker (mosquitto) และ Dashboard (Thingsboard Cloud) สื่อสารด้วย MQTT Protocol

## Arduino

### Basic IO

ตัวอย่าาง Code สำหรับอ่านค่าจาก Sensor ทั้งแบบ Analog และ Digital เพื่อส่งค่าไปแสดงผลยัง Serial Port

- [ตัวอย่าง Code คลิกที่นี้](arduino/ESP32_-_Basic_IO/ESP32_-_Basic_IO.ino)

### Basic MQTT

ตัวอย่าง Code สำหรับรับ-ส่งข้อมูลด้วย MQTT Protocol ผ่าน WiFi เพื่อส่งค่าไปแสดงผลยัง Serial Port และอุปกรณ์อื่น ๆ ที่ใช้ Broker เดียวกัน

- [ตัวอย่าง Code คลิกที่นี้](arduino/ESP32_-_Simple_MQTT/ESP32_-_Simple_MQTT.ino)

### Send and Receive MQTT

ตัวอย่าง Code สำหรับรับ-ส่งข้อมูลด้วย MQTT Protocol ผ่าน WiFi เพื่อส่งค่าไปแสดงผลและรับคำสั่งควบคุมจาก MQTT Utility

- [ตัวอย่าง Code คลิกที่นี้](arduino/ESP32_-_Send_and_Receive_MQTT/ESP32_-_Send_and_Receive_MQTT.ino)

## Node-RED

### Average Temperature

ตัวอย่าง Code สำหรับการอ่านค่าจาก Temperature Sensor จำนวน 3 ตัว เพื่อหาต่าเฉลี่ยของอุณภูมิห้อง และส่งผลลัพธ์ไปยัง Local Broker

- [ตัวอย่าง Code คลิกที่นี้](node-red/Average%20Temperature.json)

### Counter

ตัวอย่าง Code สำหรับอ่านค่าจาก Proximity Sensor จำนวน 1 ตัว เพื่อนับจำนวนที่ตรวจจับวัตถุได้ และส่งผลลัพธ์ไปยัง Local Broker

- [ตัวอย่าง Code คลิกที่นี้](node-red/Counter.json)
