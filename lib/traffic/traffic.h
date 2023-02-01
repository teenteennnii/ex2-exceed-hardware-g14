#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Bounce2.h>

const String baseUrl = "https://exceed-hardware-stamp465.koyeb.app";

const String point = "กลุ่มที่";
const int nearby_1 = "กลุ่มใกล้เคียง (กลุ่มที่ +-1)";
const int nearby_2 = "กลุ่มใกล้เคียง (กลุ่มที่ +-1)";

void GET_traffic();
void POST_traffic(String led);