#define BLYNK_TEMPLATE_ID "Your_blynk_template_ID"
#define BLYNK_TEMPLATE_NAME "Your Template Name"
#define BLYNK_AUTH_TOKEN "Yourblynkauthtoken"
#include <BlynkSimpleEsp32.h>
char ssid[] = "Esp32Network";
char pass[] = "scienceproject";
int state=0,pm=0;
void setup() {
 Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
 pm = millis();
}

void loop() {
  int rax = analogRead(32);
  int ray = analogRead(35);
  int raz = analogRead(34);
  float ax = rax*3.3/4095.0;
  float ay = ray*3.3/4095.0;
  float az = raz*3.3/4095.0;
  float pax = (ax-1.5)/0.33;
  float pay = (ay-1.5)/0.33;
  float paz = (az-1.5)/0.33;
  float A = sqrt(pax*pax + pay*pay + paz*paz);//Resultant acceleration{using vector addition}
  if(A<= 0.4 || A>=2.5){
    if((millis()-pm)>200){
      Blynk.logEvent("fall_alert");//Send Alert(Email alert) to Blynk
      pm=millis();
    }
  }
     
  Blynk.run();
  delay(20);
}
