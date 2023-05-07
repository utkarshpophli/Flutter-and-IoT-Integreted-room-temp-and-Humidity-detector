#include <IOXhop_FirebaseESP32.h>
#include <WiFi.h>
#include "DHT.h"
#define DHTPIN 5
#define DHTTYPE DHT11
DHT dht(DHTPIN ,DHTTYPE);

#define WIFI_SSID "OnePlus Nord 2"
#define WIFI_PASSWORD "1234567i9"
#define FIREBASE_AUTH "https://flutter-iot-db8a4-default-rtdb.firebaseio.com/"
#define FIREBASE_HOST "OZVVPkUlVatb8fllU29Y82MQtDEgb7PSSjtb1ic3"

void setup(){
  Serial.begin(115200);
  Serial.print("DHT TEST");
  dht.begin();

  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED){
    Serial.println(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Connected");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_AUTH,FIREBASE_HOST);
}

int n = 0;

void loop(){
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if(isnan(h)|| isnan(t)){
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");

  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C");

  Firebase.setFloat("Humidity: ", h);
  if(Firebase.failed()){
    Serial.print("Setting/number failed: ");
    Serial.println(Firebase.error());
    return;
  }
  delay(1000);
  Firebase.setFloat("Temperature: ", t);
  if(Firebase.failed()){
    Serial.print("Setting/number failed: ");
    Serial.println(Firebase.error());
    return;
  }
  Serial.println("       Temperature and Humidity Data Sent Successfully");
  delay(1000);
}