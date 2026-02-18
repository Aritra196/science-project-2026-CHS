#define BLYNK_TEMPLATE_ID "TMPL37trpYsQK"
#define BLYNK_TEMPLATE_NAME "Science project 2026"
#define BLYNK_AUTH_TOKEN "tmoubT4AhCYCm9SL--77ijyNDOaP5DkC"
#include <BlynkSimpleEsp8266.h>
MPU6050 mpu;
char ssid[] = "Wokwi-GUEST";
char pass[] = "";
void setup() {
  //Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  int rax = analogRead(12);
  int ray = analogRead(14);
  int raz = analogRead(27);
  float ax = rax*3.3/4095.0;
  float ay = ray*3.3/4095.0;
  float az = raz*3.3/4095.0;
  float pax = ax-1.65/0.3;
  float pay = ay-1.65/0.3;
  float paz = az-1.65/0.3;
  //Serial.print(pax); Serial.print(" "); Serial.print(pay); Serial.print(" "); Serial.print(paz); Serial.print(" ");
  //Serial.print(pgx); Serial.print(" "); Serial.print(pgy); Serial.print(" "); Serial.print(pgz);
  //Serial.println("");
  float A = sqrt(pax*pax + pay*pay + paz*paz);//Root Mean Square of processed value of acceleration along x,y and z axis
  if(A<= 0.4 || A>=2.5)
      BLynk.logEvent("fall_alert");//Send Alert(Email alert) to Blynk
  Blynk.run();
  delay(50);
}
