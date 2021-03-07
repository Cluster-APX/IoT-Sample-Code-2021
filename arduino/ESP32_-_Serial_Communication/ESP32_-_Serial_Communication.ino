/*
 * อ่านค่า Analog และ Digital เพื่อแสดงค่าทั้งหมดที่อ่านได้ผ่านทาง Serial Port
 * เขียนค่า Digital เพื่อควบคุม Relay ที่ต่อกับ Conveyor
 */


#define IN_ANA_0  36 // กำหนด Input Port สำหรับ Temperature
#define IN_DIGI_0 39 // กำหนด Input Port สำหรับ Proximitry (Input)
#define IN_DIGI_1 34 // กำหนด Input Port สำหรับ Proximitry (Output)

#define OUT_DIGI_0  22  // Output Port สำหรับ Conveyor

int DATA_ANA_0  = 0;  // ตัวแปรสำหรับเก็บค่า Analog ที่อ่านได้

int DATA_DIGI_0 = 0;  // ตัวแปรสำหรับเก็บค่า Digital ที่อ่านได้
int DATA_DIGI_1 = 0;  // ตัวแปรสำหรับเก็บค่า Digital ที่อ่านได้


void setup() 
{

  // ตั้งค่า Port เป็น Input
  pinMode(IN_ANA_0, INPUT);  // Temperature Analog
  pinMode(IN_DIGI_0, INPUT);  // Proximitry Digital
  pinMode(IN_DIGI_1, INPUT);  // Proximitry Digital

  // ตั้งค่า Port เป็น Output
  pinMode(OUT_DIGI_0, OUTPUT);  // Relay (Conveyor)

  // ใช้งาน Serial Port
  Serial.begin(115200);

  // ทดสอบ Output
  digitalWrite(OUT_DIGI_0, HIGH);
  delay(1000);
  digitalWrite(OUT_DIGI_0, LOW);

}


void loop()
{

  if(Serial.available() > 0)
  {

    // อ่านข้อมูลที่ส่งมาทาง Serial Port
    int data_read  = Serial.read();
    if(data_read == '1')
    {
        // Conveyor เริ่มทำงาน
        digitalWrite(OUT_DIGI_0, HIGH);
    }
    else if(data_read == '0')
    {
      // Conveyor หยุดทำงาน
      digitalWrite(OUT_DIGI_0, LOW);
    }
    
  }


  Serial.print("\r");

  DATA_ANA_0  = analogRead(IN_ANA_0); // อ่านค่า Analog
  Serial.print(DATA_ANA_0); // ส่งค่า Analog ที่อ่านได้ไปยัง Serial Port
  Serial.print(" ");

  DATA_DIGI_0  = digitalRead(IN_DIGI_0); // อ่านค่า Digital
  Serial.print(DATA_DIGI_0); // ส่งค่า Digital ที่อ่านได้ไปยัง Serial Port
  Serial.print(" ");

  DATA_DIGI_1  = digitalRead(IN_DIGI_1); // อ่านค่า Digital
  Serial.print(DATA_DIGI_1); // ส่งค่า Digital ที่อ่านได้ไปยัง Serial Port

  Serial.print("\n");

  delay(250);

}
