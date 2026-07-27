#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Address may vary (usually 0x27)
#include "DHT.h"

#define DHTPIN 2 
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);



#define FIREBASE_HOST "verticleiot-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "YxIMRh1CrMA937wZB8zKpOJA5WKKJOBzilhzOV2e"
#define WIFI_SSID "iotproject"
#define WIFI_PASSWORD "iotproject01"
float Voltage,Voltage1;


int mot=D7;
int water=A0;
int ldr=D5;
int led=D6;
String data_v,msg,data_b;
int k,i,mode_v,f_v,fn_v,s_v,sn_v,a_v,an_v,a,s;   
                                   
void setup()
{
Serial.begin(9600);


pinMode(ldr,INPUT);
pinMode(water,INPUT);
pinMode(mot,OUTPUT);
pinMode(led,OUTPUT);


digitalWrite(mot,LOW);
digitalWrite(led,LOW);

 dht.begin();
  // Setup LCD
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("VERTICAL FARMING ");
  lcd.setCursor(0, 1);
  lcd.print(" Monitring  ");
delay(1000);
    Serial.print("Connecting");
    while(WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(500);
      }
      Serial.println();
      Serial.print("connected: ");
      Serial.println(WiFi.localIP());

      
Firebase.setFloat ("KITS_AGG/AMODE",a);
a++;
delay(2000);
}


void loop()
{
   
   
if(digitalRead(ldr)==0)
{
  Serial.println("LIGHT ON DAY TIME");
  digitalWrite(led,LOW);

 
}
if(digitalRead(ldr)==1)
{
  Serial.println("LIGHT OFF NIGHT TIME");
  digitalWrite(led,HIGH);

   
  
}
   float h = dht.readHumidity();
     float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Firebase.setFloat ("KITS_AGG/TEMP",t);
  Firebase.setFloat ("KITS_AGG/HUM",h);
 
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TEMP:");
  lcd.setCursor(6, 0);
  lcd.print(t);
  lcd.setCursor(0, 1);
  lcd.print("HUMIDITY:");
  lcd.setCursor(10, 1);
  lcd.print(h);
  
Firebase.setFloat ("KITS_AGG/TEMP",t);
Firebase.setFloat ("KITS_AGG/HUMIDITY",h);
         
data_v=Firebase("KITS_AGG/device");

Serial.print("cloud_data:");
Serial.println(data_v);

Serial.print("water:");

Serial.println(analogRead(water));

int sen_v=analogRead(water);


if(data_v =="\"MANUAL\"")
{
mode_v=1;
Serial.println("MANUAL-SELECTED");
}


if(data_v =="\"AUTOMATIC\"")
{
mode_v=0;
Serial.println("AUTOMATIC-SELECTED");
}
if(mode_v==0)
{
  
 if(sen_v<800)
{
  
digitalWrite(mot,LOW);

     Firebase.setFloat ("KITS_AGG/FWATER",i);
     i++;
Serial.println("Full Water  DETECTED PUMP OFF");
delay(1000);
 

 }
 
if(sen_v>800 )
{
digitalWrite(mot,HIGH);

 Firebase.setFloat ("KITS_AGG/NWATER",i);
     i++;
Serial.println("NO Water PUMP ON:");
 }
}

if(mode_v==1)
{
if(data_v == "\"ON\"")
{
  Serial.println("MANUAL-ON");
digitalWrite(mot,HIGH);
}
if(data_v == "\"OFF\"")
{
  Serial.println("MANUAL-OFF");
digitalWrite(mot,LOW);
}

}

}