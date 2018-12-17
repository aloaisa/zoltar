#include <Wire.h>  // Comes with Arduino IDE
#include <LiquidCrystal_I2C.h>  //เรียกใช้ Library 


LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3,POSITIVE);  // Set the LCD I2C address กำหนดขาส่งข้อมูลจากไมโครคอนโทรเลอร์เข้าจอ LCD

int buttonPin =3;         //กำหนด เป็นขาที่รับข้อมูลจากเครื่องหยอดเหรียญ
int buttonState =0;         //กำหนดสถานะของ buttonPin
int A = 0;            //กำหนดตัวแปร เพื่อใช้แสดงผลรวม


void setup() 
{
  pinMode(buttonPin,INPUT);      //กำหนดหน้าที่ของขา butttonPin ให้เป็นขาอินพุท
  /*
  lcd.begin(16, 2);         //กำหนดการใช้คอลัมน์และแถวของ LCD
   lcd.setCursor(4,0);         //กำหนดตำแหน่งเริ่มต้นของcursorที่ตำแหน่ง(4,0)
   lcd.print("WELCOME");      //แสดงข้อความปรากฎหน้าจอ LCD
   lcd.setCursor(0,1);         //กำหนดตำแหน่งเริ่มต้นของcursorที่ตำแหน่ง(0,1)
   lcd.print("PLZ  INSERT COIN");      //แสดงข้อความปรากฎหน้าจอ LCD
   */
  Serial.begin(9600);  // Used to type in characters

  lcd.begin(16,2);   // initialize the lcd for 16 chars 2 lines, turn on backlight


  //-------- Write characters on the display ------------------
  // NOTE: Cursor Position: (CHAR, LINE) start at 0  
  lcd.setCursor(0,0); //Start at character 4 on line 0
  lcd.print("Welcome!");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("PLZ Insert Coin");
  delay(8000);  

  // Wait and then tell user they can start the Serial Monitor and type in characters to
  // Display. (Set Serial Monitor option to "No Line Ending")
  lcd.clear();
  lcd.setCursor(0,0); //Start at character 0 on line 0
}

void loop()
{
  buttonState = digitalRead(buttonPin);   //เก็บค่าbuttonPin ไว้ในbuttonState
  lcd.setCursor(0,0);         //กำหนดตำแหน่งเริ่มต้นของcursorที่ตำแหน่ง(0,0)
  if(buttonState==LOW)         //เงื่อนไข
  {
    A+=10;            //คำนวณเพิ่มค่าตัวแปร โดยจะเพิ่มครั้งละ 5
    delay(500);                        //กำหนดการถ่วงเวลา 500ms.
    lcd.clear();            //คำสั่ง clear หน้าจอ LCD  ทั้งหมด
    lcd.print("CREDIT");         //แสดงข้อความปรากฎหน้าจอ LCD
    lcd.setCursor(8,0);         //กำหนดตำแหน่งเริ่มต้นของcursorที่ตำแหน่ง(8,0)
    lcd.print(A);            //แสดงค่าของตัวแปร A ออกทางหน้าจอ LCD
    lcd.setCursor(12,0);         //กำหนดตำแหน่งเริ่มต้นของcursorที่ตำแหน่ง(8,0)
    lcd.print("BATH");          //แสดงข้อความปรากฎหน้าจอ LCD
  }
}

