#include <SoftwareSerial.h>
SoftwareSerial s(D6,D5);
#include <ArduinoJson.h>

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "smarthome-50b1d.firebaseio.com"
#define FIREBASE_AUTH "sdM7xgFeS8diy4hBjb4fjvAT1ye38N4oNsTQDvkp"
#define WIFI_SSID "KBU"
#define WIFI_PASSWORD "1952bible!"

int ON = 1;
int OFF = 0;

boolean LED1 = OFF;
boolean LED2 = OFF;
boolean LED3 = OFF;

void setup() {
  // Initialize Serial port
  Serial.begin(9600);
  
  pinMode(D7,OUTPUT);
  pinMode(D8,OUTPUT);
  pinMode(D1,OUTPUT);
   // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
  s.begin(115200);  
  while (!Serial) continue;

}
void loop() {
  
  StaticJsonBuffer<1000> RsjsonBuffer; //받는놈
  JsonObject& root = RsjsonBuffer.parseObject(s); //받는놈

  digitalWrite(D7,LED1);
  digitalWrite(D8,LED2);
  digitalWrite(D1,LED3);
  if (root == JsonObject::invalid())
  {
    return;
  }
  //Print the data in the serial monitor
  Serial.println("JSON received and parsed");
  root.prettyPrintTo(Serial);
  Serial.println("");
  Serial.print("Temperature ");
  int temp=root["temp"];
  Serial.println(temp);
  Serial.print("Humidity    ");
  int hum=root["hum"];
  Serial.println(hum);
  Serial.print("blind ");
  int blind=root["blind"];
  Serial.println(blind);
  Serial.print("TV  ");
  int tv=root["TV"];
  Serial.println(tv);
  Serial.println("");
  Serial.println("---------------------xxxxx--------------------");
 Serial.println("");


  // set value
  Firebase.setInt("HomeState/temp", temp);
  Firebase.setInt("HomeState/hum", hum);
  delay(1000);
  Firebase.setInt("HomeState/blind", blind);
  Firebase.setInt("HomeState/tv", tv);

  delay(1000);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
  temp = Firebase.getInt("HomeState/temp");
  hum = Firebase.getInt("HomeState/hum");
  delay(1000);
  blind = Firebase.getInt("HomeState/blind");
  tv = Firebase.getInt("HomeState/tv");
  
  if(Firebase.getString("HomeState/LED1")=="1"){
    LED1 = ON;
  }else if(Firebase.getString("HomeState/LED1")=="0"){

    LED1 = OFF;
  }
   if(Firebase.getString("HomeState/LED2")=="1"){
    LED2 = ON;
  }else if(Firebase.getString("HomeState/LED2")=="0"){
    LED2 = OFF;
  }
   if(Firebase.getString("HomeState/LED3")=="1"){
    LED3 = ON;
  }else if(Firebase.getString("HomeState/LED3")=="0"){
    LED3 = OFF;
  }

  
}
