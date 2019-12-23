
#include <SoftwareSerial.h>
#include <Servo.h>
#include <Wire.h>
#include <ArduinoJson.h>
#include "LiquidCrystal_I2C.h"
#include "DHT.h"
#include "melody.h"


DHT dht(dhtPin, DHT11);
LiquidCrystal_I2C lcd(lcdAddr, 16, 2);
SoftwareSerial s(5,6);
SoftwareSerial bluetooth(2,3);  //시리얼 통신을 위한 객체선언

Servo myservo;

unsigned long previousMillis = 0;
String val = "";
boolean blind = OFF;
boolean TV = OFF;
boolean LED1 = OFF;
boolean LED2 = OFF;
boolean LED3 = OFF;
// 현재 LED의 상태를 저장하는 배열. 0일경우 OFF, 1일 경우 ON
byte sensor[] = {0, 0, 0, 0, 0, 0, 0};

float temperature = 0;
float humidity = 0;


void setup() {

  s.begin(115200);
  bluetooth.begin(9600);
  Serial.begin(9600);
  
  dht.begin();
  lcd.init();

  pinMode (9, OUTPUT );  
  pinMode (10, OUTPUT );
  
}

StaticJsonBuffer<220> RqjsonBuffer; //주는놈
JsonObject& root = RqjsonBuffer.createObject(); //주는놈(root)


void loop() {
 
  //================2초마다 온습도 측정================//
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {   //interval(2s)마다 온습도 측정
    previousMillis = currentMillis;
    temperature = dht.readTemperature();
    humidity = dht.readHumidity();

    if (TV == ON) {                                  //TV가 ON상태이면 온습도 값 갱신
      lcd.setCursor(0, 0);
      lcd.print("Temp : ");
      lcd.print(temperature);
      lcd.setCursor(0, 1);
      lcd.print("humi : ");
      lcd.print(humidity);

    }
  }
  //===================================================//
  
  //================블라인드 제어================//
  int cdsVal = analogRead(cdsPin);
//  Serial.println(cdsVal);
  if (cdsVal > refVal && blind == OFF) {      //현재 어둡고, 블라인드가 닫혀있다면 블라인드 Open
    ascMelody();
    moveBlind(blindOpen);
    blind = ON;
    
  }
  else if (cdsVal < refVal && blind == ON) {   //현재 밝고, 블라인드가 열려있다면 블라인드 Close
    dscMelody();
    moveBlind(blindClose);
    blind = OFF;
  }
  //================블라인드 제어 끝================//

  //================TV 제어================//
  int IRval = analogRead(IRPin);
  if (IRval < 100 && TV == ON) {          //TV가 켜져있고, 거리가 가깝다면 TV OFF
    TV = OFF;
    lcd.clear();
    lcd.noBacklight();
  }

  else if (IRval > 900 && TV == OFF) {    //TV가 꺼져있고, 거리가 멀다면 TV ON
    TV = ON;
    lcd.backlight();
  }
  //================TV 제어 끝================//
   
  //노드MCU에게 데이터를 주는 부분
    root["temp"] = temperature;
    root["hum"] = humidity;
    root["blind"] = blind;
    root["TV"]= TV;
    root.printTo(s);


  ///블루투스
  if(bluetooth.available())
  {
    val = (String)bluetooth.readString();
    Serial.print(val);

    if(val.equals("R1")){
      digitalWrite(9,HIGH);
      digitalWrite(10,LOW);
    }
    if(val.equals("G1")){
      digitalWrite(10,HIGH);
      digitalWrite(9,LOW);
    }
    if(val.equals("R0")){
      digitalWrite(9,LOW);
    }
    if(val.equals("G0")){
      digitalWrite(10,LOW);
    }
  }
  
}

//LED 토글함수
void setToggle(int PIN, byte& stat) {
  if (stat == OFF) {
    digitalWrite(PIN, HIGH);
    stat = ON;
  }
  else {
    digitalWrite(PIN, LOW);
    stat = OFF;
  }
}

//블라인드 제어
void moveBlind(int angle) {
  myservo.attach(servoPin);
  myservo.write(angle);
  delay(300);
  myservo.detach();
}
