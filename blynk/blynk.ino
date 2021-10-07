#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "ACS712.h"
#include <Wire.h>

float volt1;
float volt;
ACS712 sensor(ACS712_05B, 35);

char auth[] = "o5xA27qevyQQBDLy-JBrMSP9FaEwV_0d";
char ssid[] = "Mi A1";
char pass[] = "12345678";

BlynkTimer timer;

void sendSensor()
{

volt1 = analogRead(34);
volt = ((volt1*0.00489));
float I = sensor.getCurrentDC();

Blynk.virtualWrite(V4, volt);
Blynk.virtualWrite(V5, I);
Serial.print(volt);
Serial.print("-----");
Serial.println(String("I = ") + I + " A");

}

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  // put your setup code here, to run once:
  Serial.println("Calibrating... Ensure that no current flows through the sensor at this moment");
  int zero = sensor.calibrate();
  Serial.println("Done!");
  Serial.println("Zero point for this sensor = " + zero);

  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}  
