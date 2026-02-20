#define BLYNK_TEMPLATE_ID "TMPL37trpYsQK"
#define BLYNK_TEMPLATE_NAME "Science project 2026"
#define BLYNK_AUTH_TOKEN "YEsgcapcOlKuTPionK3RGVVPF8k0wQ29"
#include <BlynkSimpleEsp32.h>
char ssid[] = "Wokwi-GUEST";
char pass[] = "";
int BIRout = 35;
int BIRin = 34;
int simtime = 24*60;//Write the mins which represent 24 hrs

int tscale = (24*3600)/simtime;//Scale of time
int t=0;
int batht=0, baths=0, pbaths=0, bpre=0;
void setup() {
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  pinMode(BIRout, INPUT);
  pinMode(BIRin, INPUT);
  //Serial.begin(9600);
}

void loop() {
  if(digitalRead(BIRin)==HIGH && baths==0 && digitalRead(BIRout)==LOW){
    baths=1;
    pbaths=BIRin;
  }
  if(digitalRead(BIRout)==HIGH && baths==0 && digitalRead(BIRin)==LOW){
    baths=1;
    pbaths=BIRout;
  }

  if(pbaths==BIRout && baths==1 && digitalRead(BIRin)==HIGH){
    baths=2;
    bpre=bpre+1;
  }
  if(pbaths==BIRin && baths==1 && digitalRead(BIRout)==HIGH){
    baths=2;
    bpre=bpre-1;
  }
  if(digitalRead(BIRin)==LOW && digitalRead(BIRout)==LOW && baths==2)
    baths=0;
  if(bpre>0 && ((t*tscale/2)%60)==0 && t>0){
    batht+=60/tscale;
  }
  if(bpre==0)
    batht=0;
  //-------------------------Serial Output------------------------//
  //Serial.print("Bathroom present:");
  //if(bpre>0)
  //  Serial.print("Yes");
  //if(bpre==0)
  //  Serial.print("No");
  //Serial.println("No. of person in bathroom:");//Maybe more than 1 maybe maybe. It isn't impossible right??
  //Serial.print(bpre);
  //if(bpre>0){
  //  Serial.println("Time of presence:");
  //  Serial.print(batht);
  //}
  //-----------------------Blynk Output---------------------------//
  Blynk.virtualWrite(V10, bpre);
  Blynk.virtualWrite(V11, batht);
  if(batht>60){
    String message="It has been recorded that a person is in bathroom for "+String(batht)+" min";
    Blynk.logEvent("bath_time", message);
  }
  t++;
  Blynk.run();
  delay(500);
}
