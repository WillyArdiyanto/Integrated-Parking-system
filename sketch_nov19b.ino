#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "smart-parking-system-cef4b-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "xxxxxxxxx"
#define WIFI_SSID "xxxxxxxxxx"
#define WIFI_PASSWORD "xxxxxxxxx"

String fireAvailable = "";
String countYes = "";

int TRIG = D0; 
//ultrasonic trig pin

int ECHO = D1; 
// ultrasonic echo pin

int parking = D2;
// IR Sensor

long duration, distance;

void setup() {

delay(1000);

Serial.begin (9600); 
// serial debugging


pinMode(TRIG, OUTPUT); 
// trig pin as output


pinMode(ECHO, INPUT); 
// echo pin as input

pinMode(parking, INPUT); 
// IR as input


WiFi.begin(WIFI_SSID, WIFI_PASSWORD); 
//try to connect with wifi


Serial.print("Connecting to ");

Serial.print(WIFI_SSID); 
// display ssid


while (WiFi.status() != WL_CONNECTED) {

Serial.print("."); 
// if not connected print this


delay(500);

}

Serial.println();

Serial.print("Connected to ");

Serial.println(WIFI_SSID);

Serial.print("IP Address is : ");

Serial.println(WiFi.localIP()); 
//print local IP address


Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); 
// begin firebase authentication

}



void loop() 
{

digitalWrite(TRIG, LOW); 
// make trig pin low


delayMicroseconds(2);

digitalWrite(TRIG, HIGH); 
// make trig pin high


delayMicroseconds(10);

digitalWrite(TRIG, LOW);

duration = pulseIn(ECHO, HIGH);

distance = duration*0.0345/2; 
// take distance in cm


Serial.print("Jarak Parkiran 1: ");
Serial.println(distance);

int carEntry = digitalRead(parking);

Serial.print("Jarak Parkiran 1: ");
Serial.println(distance);

  
  // ULTRASONIC SENSOR
  if(distance<=4){
    countYes = "Terisi"; 
    
    Firebase.setString("/Parkiran 1/Status/" , countYes);
    // send string to firebase

  }
  
  else{
    countYes = "Kosong";
      
    Firebase.setString("/Parkiran 1/Status/", countYes);
    // send string to firebase
    
  }

  if (Firebase.failed()) {
      Serial.print("P1 - Firebase connecting failed:");
      Serial.println(Firebase.error());  
      return;
  }

  // IR SENSOR
  if(carEntry == LOW){
    countYes = "Terisi";
    
    Firebase.setString("/Parkiran 2/Status/" , countYes);
    // send string to firebase
  }
  else{
    countYes = "Kosong"; 

    Firebase.setString("/Parkiran 2/Status/" , countYes);
    // send string to firebase
  }

  if (Firebase.failed()) {
      Serial.print("P2 - Firebase connecting failed:");
      Serial.println(Firebase.error());  
      return;
  }

}
