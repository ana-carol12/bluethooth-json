#include <Arduino.h>
#include <ArduinoJson.h>

String parseToJson(float humidity, float temperatureInC, float temperatureInF) {
	JsonDocument doc;

	doc["humidity"] = humidity;
	doc["temperatureInC"] = temperatureInC;
	doc["temperatureInF"] = temperatureInF;

	String jsonString;
	serializeJson(doc, jsonString);

	return jsonString;
}

JsonDocument parseToString(String data) {
  JsonDocument doc;

  DeserializationError erro = deserializeJson(doc, data);

  if (erro)
  {
    Serial.print("Erro ao interpretar JSON: ");
    Serial.println(erro.c_str());
	doc.clear();
  }

  return doc;
}
