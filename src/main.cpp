// If you want to run in WOKWi
// change pin and wifi
#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Bounce2.h>
#include "traffic.h"

#define red 26
#define yellow 25
#define green 33
#define ldr 34
#define button 27

int state = 1;
int count = 1;
Bounce debouncer = Bounce();

void Connect_Wifi();

void setup()
{
  Serial.begin(115200);
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(ldr, INPUT);
  debouncer.attach(button, INPUT_PULLUP);
  debouncer.interval(25);
  Connect_Wifi();

  delay(200);
  // start LED with GREEN and POST to database
  digitalWrite(green, HIGH);
  // POST_traffic("green");
}

void loop()
{
  // *** write your code here ***
  // Your can change everything that you want
  int light = map(analogRead(ldr),2000,4700,0,255);

  debouncer.update();
    if ( debouncer.fell() ) { 
      if (state == 1){
        state++;
      }
    }

  if (state == 1)
  {
    // while led GREEN
    digitalWrite(red, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(green, HIGH);
    if (count == 1){
      POST_traffic("green");
      GET_traffic();
      count++;
    }
  }
  if (state == 2)
  {
    // while led YELLOW
    digitalWrite(red, LOW);
    digitalWrite(green, LOW);
    digitalWrite(yellow, HIGH);
    POST_traffic("yellow");
    delay(8000);
    state = 3;
  }
  if (state == 3)
  {
    // while led RED
    digitalWrite(yellow, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
    if (count == 2){
      POST_traffic("red");
      GET_traffic();
      count ++;
    }
    
    if (light < 150){
      state = 1;
      count = 1;
    }
  }
}

void Connect_Wifi()
{
  const char *ssid = "Illya";
  const char *password = "teen12345";
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.print("OK! IP=");
  Serial.println(WiFi.localIP());
  Serial.println("----------------------------------");
}