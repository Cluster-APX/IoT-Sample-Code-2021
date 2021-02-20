/*
 * อ่านค่า Analog และ Digital เพื่อแสดงค่าทั้งหมดที่อ่านได้ผ่านทาง Serial Port
 * เขียนค่า Digital เพื่อควบคุม Relay ที่ต่อกับหลอดไฟและ Buzzer
 */


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

  // ใช้งาน Serial Port
  Serial.begin(115200);

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
  
}


void loop()
{

  DATA_ANA_0  = analogRead(IN_ANA_0); // อ่านค่า Analog
  Serial.print(DATA_ANA_0); // ส่งค่า Analog ที่อ่านได้ไปยัง Serial Port
  Serial.print(" ");

  DATA_ANA_1  = analogRead(IN_ANA_1); // อ่านค่า Analog
  Serial.print(DATA_ANA_1); // ส่งค่า Analog ที่อ่านได้ไปยัง Serial Port
  Serial.print(" ");

  DATA_ANA_2  = analogRead(IN_ANA_2); // อ่านค่า Analog
  Serial.print(DATA_ANA_2); // ส่งค่า Analog ที่อ่านได้ไปยัง Serial Port
  Serial.print(" ");

  DATA_DIGI_0  = digitalRead(IN_DIGI_0); // อ่านค่า Digital
  Serial.print(DATA_DIGI_0); // ส่งค่า Digital ที่อ่านได้ไปยัง Serial Port

  Serial.println();

  delay(250);

}
