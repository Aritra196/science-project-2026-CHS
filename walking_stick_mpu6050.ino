#define BLYNK_TEMPLATE_ID "TMPL37trpYsQK"
#define BLYNK_TEMPLATE_NAME "Science project 2026"
#define BLYNK_AUTH_TOKEN "YEsgcapcOlKuTPionK3RGVVPF8k0wQ29"
#include <MPU6050.h>
#include <Wire.h>
#include <BlynkSimpleEsp32.h>
MPU6050 mpu;
char ssid[] = "Wokwi-GUEST";
char pass[] = "";
void setup() {
  mpu.initialize();
  Wire.begin(21, 22);
  //Serial.begin(9600);
  mpu.setFullScaleAccelRange(MPU6050_ACCEL_FS_4);//Acceleration detection range to +-4g
  mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_500);//Angular velocity detection range to +=500 degree/sec
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  int16_t ax, ay, az;
  int16_t gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);//Get raw value of acceleration along x,y and z axis and angular velocity along x,y and z axis
  float pax = ax/8192.0;
  float pay = ay/8192.0;
  float paz = az/8192.0;
  float pgx = gx/65.5;
  float pgy = gy/65.5;
  float pgz = gz/65.5;
  //Serial.print(pax); Serial.print(" "); Serial.print(pay); Serial.print(" "); Serial.print(paz); Serial.print(" ");
  //Serial.print(pgx); Serial.print(" "); Serial.print(pgy); Serial.print(" "); Serial.print(pgz);
  //Serial.println("");
  float A = sqrt(pax*pax + pay*pay + paz*paz);//Root Mean Square of processed value of acceleration along x,y and z axis
  float Va = abs(pgx) + abs(pgy) + abs(pgz);//Sum of absolute value of processed value of angular velocity along x, y and z axis
  if(A<= 0.4 || A>=2.5){
    if(Va>=250){
      Blynk.logEvent("fall_alert");//Send Alert(Email alert) to Blynk
    }
  }
  Blynk.run();
  delay(50);
}
