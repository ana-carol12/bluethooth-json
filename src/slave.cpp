#include <Arduino.h>
#include <BluetoothSerial.h>
#include "led.h"
#include "slave.h"
#include <Lcd.h>
#include <json.h>

BluetoothSerial BTSlave;

String prefix_temp = "[TEMPERATURA]";
String prefix_humd = "[UMIDADE]";

float temperature = -999;
float temperatureInF = -999;
float humidity = -999;

void setupSlave() {
    Serial.begin(9600);
    Serial.setTimeout(5000);

    setupLCD();

    if (BTSlave.begin("webvinicDevice"))
    {
        Serial.println("Bluetooth iniciado com sucesso");
        Serial.print("ESP MAC Address: ");

        Serial.println(BTSlave.getBtAddressString());
        displayConnection(true);
    } else
    {
        Serial.println("Error para iniciar o Bluetooth");
        displayConnection(false);
    }
}

void loopSlave() {
    if (BTSlave.available())
    {

        String receivedMessage = BTSlave.readStringUntil('\n');
        receivedMessage.trim();
        Serial.printf("Evento Recebido: %s\n", receivedMessage.c_str());

        JsonDocument doc = parseToString(receivedMessage);

        if (!doc.isNull()) {
            if (doc.containsKey("umidity") && doc.containsKey("temperatureInC")) {

                humidity = doc["humidity"];
                temperature = doc["temperatureInC"];
                temperatureInF = doc["temperatureInF"];

                Serial.printf("Umid: %.2f, TempC: %.2f, tempF: %.2f\n", humidity, temperature, temperatureInF);

                displayData(temperature, humidity, temperatureInF);
            } else {
                Serial.println("Erro: JSON recebido não contém as chaves 'umidity' ou 'temperatureInC'");
            }
        }

        displayData(temperature, humidity, temperatureInF);
    }

}