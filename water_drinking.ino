#define BLYNK_TEMPLATE_ID "Your_blynk_template_ID"
#define BLYNK_TEMPLATE_NAME "Your Template Name"
#define BLYNK_AUTH_TOKEN "Yourblynkauthtoken"
#include <BlynkSimpleEsp32.h>
#define DIR 32
char ssid[] = "Wokwi-GUEST";
char pass[] = "";
int water;
int wstate;
void setup(){
    pinMode(DIR, INPUT);
    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}
void loop(){
    if(digitalRead(DIR)==HIGH && wstate==0){
        wstate=1;
        water++;
    }
    if(digitalRead(DIR)==LOW && wstate==1){
        wstate=0;
    }
    Blynk.virtualWrite(V14, water);
    Blynk.run();
    delay(500);
}
