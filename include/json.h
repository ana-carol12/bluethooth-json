#include <Arduino.h>
#include <ArduinoJson.h>

#ifndef JSON_H
#define JSON_H

String parseToJson(float humidity, float temperatureInC, float temperatureInF);
JsonDocument parseToString(String data);

#endif