#define BLYNK_TEMPLATE_ID "TMPL37trpYsQK"
#define BLYNK_TEMPLATE_NAME "Science project 2026"
#define BLYNK_AUTH_TOKEN "YEsgcapcOlKuTPionK3RGVVPF8k0wQ29"
#include <BlynkSimpleEsp32.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
Servo s1;
Servo s2;
Servo s3;
#define s1pin 12
#define s2pin 14
#define s3pin 27
#define IR1pin 26
#define IR2pin 25 
#define IR3pin 33
#define L1pin 5
#define L2pin 17
#define L3pin 19
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

//container variable
int c1,c2,c3;
int m1,m2,m3;
int pc1,pc2,pc3;
//time scale
int simtime = 24*60;//Write the mins which represent 24 hrs

int tscale = (24*3600)/simtime;//Scale of time
int t=0;
void setup() {
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  lcd.init();
  lcd.backlight();
  s1.attach(s1pin);
  s2.attach(s2pin);
  s3.attach(s3pin);
  pinMode(IR1pin, INPUT);
  pinMode(IR2pin, INPUT);
  pinMode(IR3pin, INPUT);
  pinMode(L1pin, OUTPUT);
  pinMode(L2pin, OUTPUT);
  pinMode(L3pin, OUTPUT);
  lcd.print("Smart Elder Assistance System");//Introductory words
  delay(500);
  lcd.clear();
  Serial.begin(9600);
}

void loop() {
  if(Serial.available())
    t=Serial.read();
  //-----------------------Medicine---------------------//
  //1st medicine at 8:00 am(open)
  if(t*tscale==8*7200)
  {
    c1=0;
    s1.write(90);
    digitalWrite(L1pin, HIGH);
  }
  if(t*tscale>=8*7200 && t*tscale<9*7200){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Aciloc RD 20 8AM");
    if(digitalRead(IR1pin)==HIGH && pc1 != digitalRead(IR1pin)){
      c1++;
      pc1=1;
    }
    if(digitalRead(IR1pin)==LOW && c1==1){
      c1++;
      pc1==0;
    }
    if(c1==3){
      m1++;
      Blynk.virtualWrite(V5, m1);
      delay(3000);
      s1.write(0);
      pc1=0;
      digitalWrite(L1pin, LOW);
    }
  }
  if(c1==0 && t*tscale==9*7200){
    Blynk.virtualWrite(V9, "Aciloc RD 20 has not been taken");
    s1.write(0);
    digitalWrite(L1pin, LOW);
  }
  //1st medicine at 8 AM ends

  //2nd medicine at 10:00 am(open)
  if(t*tscale==10*7200)
  {
    c2=0;
    s2.write(90);
    digitalWrite(L2pin, HIGH);
  }
  if(t*tscale>=10*7200 && t*tscale<11*7200){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("AMLOkind 5 10AM");
    if(digitalRead(IR2pin)==HIGH && pc2 != digitalRead(IR2pin)){
      c2++;
      pc2=1;
    }
    if(digitalRead(IR2pin)==LOW && c2==1){
      c2++;
      pc2==0;
    }
    if(c2==3){
      m2++;
      Blynk.virtualWrite(V6, m2);
      delay(3000);
      s2.write(0);
      pc2=0;
      digitalWrite(L2pin, LOW);
    }
  }
  if(c2==0 && t*tscale==11*7200){
    Blynk.virtualWrite(V9, "AMLOkind 5 has not been taken");
    s2.write(0);
    digitalWrite(L2pin, LOW);
  }
  //2nd medicine at 10 AM ends(close)

  //3rd medicine at 5 pm(open)
  if(t*tscale==17*7200)
  {
    c3=0;
    s3.write(90);
    digitalWrite(L3pin, HIGH);
  }
  if(t*tscale>=17*7200 && t*tscale<18*7200){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Qutipin 25mg 5PM");
    if(digitalRead(IR3pin)==HIGH && pc3 != digitalRead(IR3pin)){
      c3++;
      pc3=1;
    }
    if(digitalRead(IR3pin)==LOW && c3==1){
      c3++;
      pc3==0;
    }
    if(c3==3){
      m3++;
      Blynk.virtualWrite(V6, m3);
      delay(3000);
      s3.write(0);
      pc3=0;
      digitalWrite(L3pin, LOW);
    }
  }
  if(c3==0 && t*tscale==18*7200){
    Blynk.virtualWrite(V9, "Qutipin 25mg has not been taken");
    s3.write(0);
    digitalWrite(L3pin, LOW);
  }
  //1st medicine at 5 PM ends

  //4th medicine at 10 pm(open)
  if(t*tscale==22*7200)
  {
    c3=0;
    s3.write(90);
    digitalWrite(L3pin, HIGH);
  }
  if(t*tscale>=22*7200 && t*tscale<23*7200){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Alzolam 0.5 10PM");
    if(digitalRead(IR3pin)==HIGH && pc3 != digitalRead(IR3pin)){
      c3++;
      pc3=1;
    }
    if(digitalRead(IR3pin)==LOW && c3==1){
      c3++;
      pc3==0;
    }
    if(c3==3){
      m3++;
      Blynk.virtualWrite(V6, m3);
      delay(3000);
      s3.write(0);
      pc3=0;
      digitalWrite(L3pin, LOW);
    }
  }
  if(c3==0 && t*tscale==23*7200){
    Blynk.virtualWrite(V9, "Alzolam 0.5mg has not been taken");
    s3.write(0);
    digitalWrite(L3pin, LOW);
  }
  //4th medicine at 10 PM ends


  Blynk.run();
  //--------------Time clock-----------//
  t++;
  if(t==simtime*2){
    delay(500);
    t=0;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("New Day Begins..");
  }
  delay(500);
  lcd.clear();
}
