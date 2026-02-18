#define BLYNK_TEMPLATE_ID "TMPL37trpYsQK"
#define BLYNK_TEMPLATE_NAME "Science project 2026"
#define BLYNK_AUTH_TOKEN "YEsgcapcOlKuTPionK3RGVVPF8k0wQ29"
#include <BlynkSimpleEsp32.h>
#define DIR 32
char ssid[] = "Wokwi-GUEST";
char pass[] = "";
int water;
int wstate:
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
