/*
  CANSAT 2021
  Equipo Canned Universe
  IES Andres de Vandelvira e IES Ramon y Cajal (Albacete)
  DATE:25-01-2021

  Placa ESP32 DEVKIT V1
  PINOUT:

  I2C
  SDA      GPIO 21
  SCL      GPIO 22

  SD CARD
  SPI_MOSI GPIO 23
  SPI_MISO GPIO 19
  SPI_CLK  GPIO 18
  SPI_CSO  GPIO 05

  RADIO
  RX  TX0
  TX  RX0

  GPS
  TX  RX2
  RX  TX2

  DS18b20
  DATA D4
*/

#include "libPressTemp.h"
#include "libGPS.h"
#include "libOLED.h"
#include "libSDcard.h"
#include "libGyro.h"

long flag = millis();
long flag2 = millis();
boolean ultimoEnvio = false;
boolean envio = false;
boolean ultimoSalvaSD = false;
boolean salvaSD = false;
String datos;

void setup() {

  Serial.begin(9600);
  Wire.begin();
  initGPS();
  initPressTemp();
  initOLED();
  initSD();
  initMPU();

}

void loop() {
  mpu.update();
  if (millis() - flag > 1000)//Se envia cada 1000ms
  {
    envio  = !envio;
    flag = millis();
  }
  if (millis() - flag2 > 200)//se guarda en SD cada 200 ms
  {
    salvaSD = ! salvaSD;
    flag2 = millis();
  }

  if (ultimoSalvaSD != salvaSD) {

    float tempOLED = tempForOLED();
    float pressOLED = pressForOLED();

    //Compone la cadena de texto para grabar datos en SD
    //Componer con cadenas independientes tipo pressTemp = getDataPressTem()
    //si falla uno de los "get" la cadena datos puede quedar vacía.
    datos = getDataPressTemp() + "," + getGPS() + "," + getYPR() + "," + getAcc();
    logSDCard(datos);
    displayTemperatura(tempOLED);
    displayPressure(pressOLED);
    ultimoSalvaSD = salvaSD;

  }

  if (ultimoEnvio != envio)
  {
    // Envio por radio de datos

    ultimoEnvio = envio;
    Serial.println(datos);

  }
}
