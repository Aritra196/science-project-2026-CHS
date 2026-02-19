#define BLYNK_TEMPLATE_ID "TMPL37trpYsQK"
#define BLYNK_TEMPLATE_NAME "Science project 2026"
#define BLYNK_AUTH_TOKEN "YEsgcapcOlKuTPionK3RGVVPF8k0wQ29"
#include <BlynkSimpleEsp32.h>
#include <LiquidCrystal_I2C.h>
#include <ESP32Servo.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo s1;
Servo s2;
Servo s3;
#define s1pin 4
#define s2pin 14
#define s3pin 27
#define IR1pin 26
#define IR2pin 25 
#define IR3pin 33
#define L1pin 5
#define L2pin 17
#define L3pin 19
#define mini 500
#define maxi 2400
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

//container variable
int c1=0,c2=0,c3=0;
int m1=0,m2=0,m3=0,m4=0;
int pc1=0,pc2=0,pc3=0;
//time scale
int simtime = 24*60;//Write the mins which represent 24 hrs

int tscale = (24*3600)/simtime;//Scale of time
int t=0;

BLYNK_CONNECTED(){
  Blynk.syncVirtual(V5);
  Blynk.syncVirtual(V6);
  Blynk.syncVirtual(V7);
  Blynk.syncVirtual(V8);
}
BLYNK_WRITE(V5){
  m1=param.asInt();
}
BLYNK_WRITE(V6){
  m2=param.asInt();
}
BLYNK_WRITE(V7){
  m3=param.asInt();
}
BLYNK_WRITE(V8){
  m4=param.asInt();
}
void setup() {
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  lcd.init();
  lcd.backlight();
  s1.setPeriodHertz(50);
  s1.attach(s1pin, mini, maxi);
  s2.setPeriodHertz(50);
  s2.attach(s2pin, mini, maxi);
  s3.setPeriodHertz(50);
  s3.attach(s3pin, mini, maxi);
  pinMode(IR1pin, INPUT);
  pinMode(IR2pin, INPUT);
  pinMode(IR3pin, INPUT);
  pinMode(L1pin, OUTPUT);
  pinMode(L2pin, OUTPUT);
  pinMode(L3pin, OUTPUT);
  lcd.print("Smart Elder");//Introductory words
  lcd.setCursor(0,1);
  lcd.print("Assistance System");
  delay(500);
  lcd.clear();
  Serial.begin(9600);
  s1.write(90);
  s2.write(90);
  s3.write(90);
}

void loop() {
  if(Serial.available()>1)
    t=Serial.parseInt();
  Serial.println(t*tscale/7200);
  //-----------------------Medicine---------------------//
  //1st medicine at 8:00 am(open)
  if(t*tscale==8*7200)
  {
    c1=0;
    s1.write(0);
    digitalWrite(L1pin, HIGH);
  }
  if(t*tscale>=8*7200 && t*tscale<9*7200){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Aciloc RD 20 8AM");
    lcd.setCursor(0,1);
    lcd.print("AMLOkind 5 10AM");
    if(digitalRead(IR1pin)==HIGH && pc1 != digitalRead(IR1pin)){
      c1++;
      pc1=1;
    }
    if(digitalRead(IR1pin)==LOW && c1==1){
      c1++;
      pc1=0;
    }
    if(c1==3 && digitalRead(IR1pin)==LOW && pc1==1){
      m1++;
      Blynk.virtualWrite(V5, m1);
      s1.write(90);
      pc1=0;
      digitalWrite(L1pin, LOW);
    }
  }
  if(c1==0 && t*tscale==9*7200){
    Blynk.virtualWrite(V9, "Aciloc RD 20 has not been taken");
    s1.write(90);
    digitalWrite(L1pin, LOW);
  }
  //Loop-hole fixing mechanism
  if(digitalRead(IR1pin)==HIGH && pc1 == digitalRead(IR1pin) && t*tscale>=9*7200 && t*tscale<=9.5*7200 && c1==2){
      c1++;
      pc1=1;
    }
  if(c1==3 && digitalRead(IR1pin)==LOW && t*tscale>=9*7200 && t*tscale<=9.5*7200){
      m1++;
      Blynk.virtualWrite(V5, m1);
      s1.write(90);
      pc1=0;
      digitalWrite(L1pin, LOW);
    }
  //Loop-hole fixing mechanism ends
  //1st medicine at 8 AM ends

  //2nd medicine at 10:00 am(open)
  if(t*tscale==10*7200)
  {
    c2=0;
    s2.write(0);
    digitalWrite(L2pin, HIGH);
  }
  if(t*tscale>=10*7200 && t*tscale<11*7200){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("AMLOkind 5 10AM");
    lcd.setCursor(0,1);
    lcd.print("Qutipin 25mg 5PM");
    if(digitalRead(IR2pin)==HIGH && pc2 != digitalRead(IR2pin)){
      c2++;
      pc2=1;
    }
    if(digitalRead(IR2pin)==LOW && c2==1){
      c2++;
      pc2=0;
    }
    if(c2==3 && digitalRead(IR2pin)==LOW && pc2==1){
      m2++;
      Blynk.virtualWrite(V6, m2);
      s2.write(90);
      pc2=0;
      digitalWrite(L2pin, LOW);
    }
  }
  if(c2==0 && t*tscale==11*7200){
    Blynk.virtualWrite(V9, "AMLOkind 5 has not been taken");
    s2.write(90);
    digitalWrite(L2pin, LOW);
  }
  //Loop-hole fixing mechanism
  if(digitalRead(IR2pin)==HIGH && pc2 == digitalRead(IR2pin) && t*tscale>=11*7200 && t*tscale<=11.5*7200 && c2==2){
      c2++;
      pc2=1;
    }
  if(c2==3 && digitalRead(IR2pin)==LOW && t*tscale>=11*7200 && t*tscale<=11.5*7200){
      m2++;
      Blynk.virtualWrite(V6, m2);
      s2.write(90);
      pc2=0;
      digitalWrite(L2pin, LOW);
    }
  //Loop-hole fixing mechanism ends
  //2nd medicine at 10 AM ends(close)

  //3rd medicine at 5 pm(open)
  if(t*tscale==17*7200)
  {
    c3=0;
    s3.write(0);
    digitalWrite(L3pin, HIGH);
  }
  if(t*tscale>=17*7200 && t*tscale<18*7200){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Qutipin 25mg 5PM");
    lcd.setCursor(0,1);
    lcd.print("Alzolam 0.5 10PM");
    if(digitalRead(IR3pin)==HIGH && pc3 != digitalRead(IR3pin)){
      c3++;
      pc3=1;
    }
    if(digitalRead(IR3pin)==LOW && c3==1){
      c3++;
      pc3=0;
    }
    if(c3==3 && digitalRead(IR3pin)==LOW && pc3==1){
      m3++;
      Blynk.virtualWrite(V7, m3);
      s3.write(90);
      pc3=0;
      digitalWrite(L3pin, LOW);
    }
  }
  if(c3==0 && t*tscale==18*7200){
    Blynk.virtualWrite(V9, "Qutipin 25mg has not been taken");
    s3.write(90);
    digitalWrite(L3pin, LOW);
  }
  //Loop-hole fixing mechanism
  if(digitalRead(IR3pin)==HIGH && pc3 == digitalRead(IR3pin) && t*tscale>=18*7200 && t*tscale<=18.5*7200 && c3==2){
      c3++;
      pc3=1;
    }
  if(c3==3 && digitalRead(IR3pin)==LOW && t*tscale>=18*7200 && t*tscale<=18.5*7200){
      m3++;
      Blynk.virtualWrite(V7, m3);
      s3.write(90);
      pc3=0;
      digitalWrite(L3pin, LOW);
    }
  //Loop-hole fixing mechanism ends
  //1st medicine at 5 PM ends

  //4th medicine at 10 pm(open)
  if(t*tscale==22*7200)
  {
    c3=0;
    s3.write(0);
    digitalWrite(L3pin, HIGH);
  }
  if(t*tscale>=22*7200 && t*tscale<23*7200){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Alzolam 0.5 10PM");
    lcd.setCursor(0,1);
    lcd.print("Aciloc RD 20 8AM");
    if(digitalRead(IR3pin)==HIGH && pc3 != digitalRead(IR3pin)){
      c3++;
      pc3=1;
    }
    if(digitalRead(IR3pin)==LOW && c3==1){
      c3++;
      pc3=0;
    }
    if(c3==3 && digitalRead(IR3pin)==LOW && pc3==1){
      m4++;
      Blynk.virtualWrite(V8, m4);
      s3.write(90);
      pc3=0;
      digitalWrite(L3pin, LOW);
    }
  }
  if(c3==0 && t*tscale==23*7200){
    Blynk.virtualWrite(V9, "Alzolam 0.5mg has not been taken");
    s3.write(90);
    digitalWrite(L3pin, LOW);
  }
  //Loop-hole fixing mechanism
  if(digitalRead(IR3pin)==HIGH && pc3 == digitalRead(IR3pin) && t*tscale>=23*7200 && t*tscale<=23.5*7200 && c3==2){
      c3++;
      pc3=1;
    }
  if(c3==3 && digitalRead(IR3pin)==LOW && t*tscale>=23*7200 && t*tscale<=23.5*7200){
      m4++;
      Blynk.virtualWrite(V8, m4);
      s3.write(90);
      pc3=0;
      digitalWrite(L3pin, LOW);
    }
  //Loop-hole fixing mechanism ends
  //4th medicine at 10 PM ends


  Blynk.run();
  //--------------Time clock-----------//
  t++;
  if(t==simtime*2){
    delay(500);
    t=0;
  }
  delay(500);
  lcd.clear();
}
