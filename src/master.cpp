#include <Arduino.h>
#include <BluetoothSerial.h>
#include <Sensor.h>
#include <Lcd.h>
#include <json.h>

BluetoothSerial BTSerial;

float lastHumidity = 0;
float lastTemperature = 0;

u_int8_t slaveAddress[] = {0x14, 0x33, 0x5C, 0x0B, 0x2B, 0x76};

void setupMaster(){
    Serial.begin(9600);
    Serial.setTimeout(5000);

    setupLCD();

    if (BTSerial.begin("webvinicDevice", true))
    {
        Serial.println("Bluetooth (Master) iniciado com sucesso");
    } else
    {
        Serial.println("Erro ao iniciar o bluetooth");
    }

    Serial.println("Tentando conectar ao Slave...");
    if (BTSerial.connect(slaveAddress))
    {
        Serial.println("Conectado com sucesso");
    } else {
        Serial.println("Falha ao conectar");
    }

    setupSensor();
    setupLCD();
}

void loopMaster(){

    float temperature = getTemperatureAsFloat();
    float humidity = getRelativeHumidity();

    if (BTSerial.available())
    {
        String receivedMessage = BTSerial.readStringUntil('\n');
        receivedMessage.trim();
        Serial.printf("Mensagem recebida: %s\n", receivedMessage.c_str());
    }

    if (Serial.available())
    {
        String messageToSend = Serial.readStringUntil('\n');
        messageToSend.trim();
        BTSerial.println(messageToSend);
    }

    if (temperature != lastTemperature) {
        String message = "[TEMPERATURA] " + String(temperature, 2);

        Serial.println(message);

        float temperatureInF = (temperature * 1.8) + 32; 
        String data = parseToJson(humidity, temperature, temperatureInF);
        Serial.println(data);

        lastTemperature = temperature;
        lastHumidity = humidity;

        BTSerial.println(data);
        displayData(temperature, humidity, temperatureInF);
    }

    if (humidity != lastHumidity) {
        String message = "[UMIDADE] " + String(humidity, 2);

        Serial.println(message);

        float temperatureInF = (temperature * 1.8) + 32; 
        String data = parseToJson(humidity, temperature, temperatureInF);
        Serial.println(data);

        lastTemperature = temperature;
        lastHumidity = humidity;

        BTSerial.println(data);


        displayData(temperature, humidity, temperatureInF);
    }
}