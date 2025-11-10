#include "lcd.h"
#include <Wire.h>               
#include <LiquidCrystal_I2C.h>    

#define SDA_PIN    21
#define SCL_PIN    22

LiquidCrystal_I2C lcd(0x27, 16, 2);


void setupLCD() {
    Wire.begin(SDA_PIN, SCL_PIN);

    lcd.init();
    
    lcd.backlight();

    lcd.clear();
    lcd.setCursor(0, 0); 
    lcd.clear();
    lcd.printf("Conectando...");

    delay(1000); 
}

void displayConnection(bool sucess) {
    lcd.clear();
    lcd.setCursor(0, 0);

    if (sucess) { 
        lcd.print("Conectado com sucesso.");
    } else {
        lcd.print("Falha na conexão.");
    }
}

void displayData(float temperature, float umidity, float temperatureInF) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp. C: ");
    lcd.setCursor(0, 1);

    lcd.print("Temp. F: ");

    lcd.setCursor(0, 2);
    lcd.print("Umidade: ");

    if (temperature == -999) {
        lcd.setCursor(9, 0);
        lcd.print("N/A");
    } else {
        lcd.setCursor(9, 0);
        lcd.print(temperature);

        lcd.setCursor(15, 0);
        lcd.write(0xDF); 
        lcd.print("F");
    }

    if (temperatureInF == -999) {
        lcd.setCursor(9, 1);
        lcd.print("N/A");
    } else {
        lcd.setCursor(9, 1);
        lcd.print(temperatureInF);

        lcd.setCursor(15, 1);
        lcd.write(0xDF); 
        lcd.print("F");
    }

    if (umidity == -999) {
        lcd.setCursor(9, 2);
        lcd.print("N/A");
    } else {
        lcd.setCursor(9, 2);
        lcd.print(umidity);

        lcd.setCursor(13, 2);
        lcd.print("%");
    }
    
}