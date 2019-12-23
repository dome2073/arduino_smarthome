/* "setting.h"
 * 스마트홈에 들어가는 센서, 모듈, LED의 핀 번호, 기준값, 수치를 세팅하는 헤더파일입니다. 
 * 
 * 스마트홈 완성코드를 사용할 경우 이쪽에 있는 값만 변경해주시면 됩니다.
 * 14 ~ 17번 째 줄 : 각 센서별 제어를 위해 필요한 수치값.
 * 20번 째 줄 : i2c LCD 주소값. 0x27 또는 0x3F값 
 * 24 ~ 29번 째 줄 : 센서 핀 번호.
 * 30 ~ 35번 째 줄 : RGB LED 핀 번호.
 */

int ON = 1;
int OFF = 0;

long interval = 2000;            //온습도 센서값 측정 주기. 2000ms = 2초
int blindOpen = 50;          //서보모터 열렸을 때 각도값 
int blindClose = 360;         //서보모터 닫혔을 때 각도값(Open일때보다 각도가 커야함)
int refVal = 400;            //조도센서 기준값.

//i2c_LCD address//
int lcdAddr = 0x27;          // I2C LCD 주소. 변경 필수


//아두이노 핀 세팅//
int cdsPin = A0;            // 조도센서모듈(블라인드)
int IRPin = A1;              // 적외선장애물감지센서 핀
int cdsPin2 = A2;            // 조도센서(침대알람)
int piezoPin = 3;            // 피에조부저 핀
int dhtPin = 4;              // 온습도센서 핀
int servoPin = 7;            // 서보모터
int led = 9;                 // LED(가스, 에어컨)
int ledR1 = 10;              //침대
int ledG1 = 11;              //TV왼쪽
int ledB1 = 12;              //TV오른쪽
int ledR2 = 13;
int ledG2 = 14;
//int ledB2 = 13;
