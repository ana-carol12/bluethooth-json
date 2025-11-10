#ifndef LCD_H
#define LED_H

void setupLCD();
void displayData(float temperature, float humidity, float temperatureInF);
void displayConnection(bool sucess);

#endif