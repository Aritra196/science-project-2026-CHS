#define BLYNK_TEMPLATE_ID "TMPL37trpYsQK"
#define BLYNK_TEMPLATE_NAME "Science project 2026"
#define BLYNK_AUTH_TOKEN "YEsgcapcOlKuTPionK3RGVVPF8k0wQ29"
#include <BlynkSimpleEsp32.h>
char ssid[] = "Wokwi-GUEST";
char pass[] = "";
int HIRout = 36;
int HIRin = 39;
int simtime = 24*60;//Write the mins which represent 24 hrs

int tscale = (24*3600)/simtime;//Scale of time
int t=0;
int hatht=0, haths=0, phaths=0, hpre=0;
void setup() {
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  pinMode(HIRout, INPUT);
  pinMode(HIRin, INPUT);
  //Serial.begin(9600);
}

void loop() {
  if(digitalRead(HIRin)==HIGH && haths==0){
    haths++;
    phaths=HIRin;
  }
  if(digitalRead(HIRout)==HIGH && haths==0){
    haths++;
    phaths=HIRout;
  }

  if(phaths==HIRin && haths==1 && digitalRead(HIRout)==HIGH){
    haths=2;
    hpre++;
  }
  if(phaths==HIRout && haths==1 && digitalRead(HIRin)==HIGH){
    haths=2;
    hpre--;
  }
  if(digitalRead(HIRin==LOW && HIRout==LOW && haths==2))
    haths=0;
  if(hpre>0 && ((t*tscale/2)%60)==0 && t>0){
    hatht+=60/tscale;
  }
  if(hpre==0)
    hatht=0;
  //-------------------------Serial Output------------------------//
  //Serial.print("Outside home:");
  //if(hpre>0)
  //  Serial.print("Yes");
  //if(hpre==0)
  //  Serial.print("No");
  //Serial.println("No. of person outside home:");
  //Serial.print(hpre);
  //if(hpre>0){
  //  Serial.println("Time of absence:");
  //  Serial.print(hatht);
  //}
  //-----------------------Blynk Output---------------------------//
  Blynk.virtualWrite(V12, hpre);
  Blynk.virtualWrite(V13, hatht);
  if(batht>60){
    String hmessage="It has been recorded that there is no one in home for "+String(hatht)+" min";
    Blynk.logEvent("home_time", hmessage);
  }
  t++;
  Blynk.run();
  delay(500);
}
