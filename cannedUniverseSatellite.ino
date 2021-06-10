/*
  CANSAT 2021
  Equipo Canned Universe
  IES Andres de Vandelvira e IES Ramon y Cajal(Albacete)
  DATE:25-01-2020
*/


#include "libPressTemp.h"
#include "libGPS.h"
#include "libOLED.h"
#include "libSDcard.h"
#include "libGyro.h"

//unsigned double packetsSend = 1;// change data type from long to double, to avoid errors in a later division
//unsigned long double a;// to store millis() as a double, to avoid losing information in a later division

double packetsSend = 1;
long double a;

bool SDcardWorking = false;// this is then set to true when the SDcard starts working, we assume it doesn't stop working during the program.

long flag = millis();
long flag2 = millis();
boolean ultimoEnvio = false;
boolean envio = false;
boolean ultimoSalvaSD = false;
boolean salvaSD = false;
String dataPressTemp;
String datos;


void setup() {
  Serial.begin(9600);
  initGPS();// starts the GPS from its .h file
  initPressTemp();// starts the BMP180 from its .h file
  initOLED();// starts the display from the .h file
  initSD();

}

void loop() {

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

    //dataPressTemp = getDataPressTemp();
    float tempOLED = tempForOLED();
    float pressOLED = pressForOLED();
    //int metersHigh = gps.altitude.meters();
    
    //Compone la cadena para grabar datos en SD
    //Pendiente de terminar
    //String datosGPS = String(gps.location.lat()) + String(gps.location.lng()) + String(gps.altitude.meters());
    //String datosGPS = getGPS();
    //String datosAngulos = getYPR();
    //datos = dataPressTemp + datosGPS + datosAngulos ;
    datos = getDataPressTemp() + getGPS() + getYPR();
    logSDCard(datos);
    displayTemperatura(tempOLED);
    displayPressure(pressOLED);
    //displayAltitude(metersHigh);
    ultimoSalvaSD = salvaSD;

  }

  if (ultimoEnvio != envio)
  {
    // Envio por radio de datos de mision primaria

    ultimoEnvio = envio;
    Serial.println(datos);

  }

}
