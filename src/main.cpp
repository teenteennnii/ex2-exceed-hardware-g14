// If you want to run in WOKWi
// change pin and wifi
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Bounce2.h>

const String baseUrl = "https://exceed-hardware-stamp465.koyeb.app";

#define red <led red pin>
#define yellow <led yellow pin>
#define green <led green pin>
#define ldr <ldr pin>
#define button <button pin>

#define light <แสดงมันมืด มีค่าเท่าไหร่>

const String point = "กลุ่มที่";
const int nearby_1 = "กลุ่มใกล้เคียง (กลุ่มที่ +-1)";
const int nearby_2 = "กลุ่มใกล้เคียง (กลุ่มที่ +-1)";

int state = 1;
int count = 0;
Bounce debouncer = Bounce();

void Connect_Wifi();

void GET_traffic()
{
  DynamicJsonDocument doc(65536);
  HTTPClient http;
  const String url = baseUrl + "/all_traffic";
  http.begin(url);

  Serial.println("Nearby traffic");
  int httpResponseCode = http.GET();
  if (httpResponseCode > 0)
  {
    String payload = http.getString();
    deserializeJson(doc, payload);

    // *** write your code here ***
    // set up JSON
    // .
    // .
    // .
    // .
    // .
    // .
    // .
    // .
    // .
    // .
    // .
    // .
    // .
    // .
    // .
    
  }
  else
  {
    Serial.print("Error ");
    Serial.println(httpResponseCode);
  }

  Serial.println("----------------------------------");
}

void POST_traffic(String led)
{
  const String url = baseUrl + "/my_traffic?point=" + point;
  String json;
  HTTPClient http;
  http.begin(url);
  http.addHeader("Content-Type", "application/json");

  DynamicJsonDocument doc(2048);
  // *** write your code here ***
  // set up JSON
  // .
  // .
  // .
  serializeJson(doc, json);

  // Serial.println("POST " + led);
  int httpResponseCode = http.POST(json);
  if (httpResponseCode == 200)
  {
    Serial.print("Done");
    Serial.println();
  }
  else
  {
    Serial.print("Error ");
    Serial.println(httpResponseCode);
  }

  Serial.println("----------------------------------");
}

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
  POST_traffic("green");
}

void loop()
{
  // *** write your code here ***
  // Your can change everything that you want
  if (state == 1)
  {
    // while led GREEN
  }
  else if (state == 2)
  {
    // while led YELLOW
  }
  else if (state == 3)
  {
    // while led RED
  }
}

void Connect_Wifi()
{
  const char *ssid = "Your Wifi Name";
  const char *password = "Your Wifi Password";
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