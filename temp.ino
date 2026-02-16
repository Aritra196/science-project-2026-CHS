#define BLYNK_TEMPLATE_ID "TMPL37trpYsQK"
#define BLYNK_TEMPLATE_NAME "Science project 2026"
#define BLYNK_AUTH_TOKEN "YEsgcapcOlKuTPionK3RGVVPF8k0wQ29"
#include <DHTesp.h>
#include <BlynkSimpleEsp32.h>

DHTesp dht;
int temp;
#define heater 2
#define fan 18
int mheater = 0;
int mfan = 0;
char ssid[] = "Wokwi-GUEST";
char pass[] = "";
BLYNK_WRITE(V1){
  int hstate = param.asInt();
  if(hstate<2){
    digitalWrite(heater, hstate);
    Blynk.virtualWrite(V3, hstate);
    mheater=1;
  }
  if(hstate == 2)
    mheater=0;
}
BLYNK_WRITE(V2){
  int fstate = param.asInt();
  if(fstate<2){
    digitalWrite(fan, fstate);
    Blynk.virtualWrite(V4, fstate);
    mfan=1;
  }
  if(fstate==2)
    mfan=0;
}
void setup() {
  dht.setup(16, DHTesp::DHT22);
  pinMode(heater, OUTPUT);
  pinMode(fan, OUTPUT);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  temp=dht.getTemperature();
  if(temp<24 && mheater==0){
    digitalWrite(heater, HIGH);
    Blynk.virtualWrite(V3, 1);
  }  
  if(temp>=24 && mheater==0){
    digitalWrite(heater, LOW);
    Blynk.virtualWrite(V3, 0);
  }
  if(temp <=30 && mfan==0){
    digitalWrite(fan, LOW);
    Blynk.virtualWrite(V4, 0);
  }
  if(temp>30 && mfan==0){
    digitalWrite(fan, HIGH);
    Blynk.virtualWrite(V4, 1);
  }
  Blynk.run();
  Blynk.virtualWrite(V0, temp);
  delay(500);
}


