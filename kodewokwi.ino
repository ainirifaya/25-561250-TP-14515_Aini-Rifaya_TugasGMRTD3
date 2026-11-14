#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <ESP32Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
const int pinPIR = 13;

Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);

  if (!mpu.begin()) {
    Serial.println("Sensor tidak ditemukan.");
    while(1) {
      delay(10);
      }
  }

  servo1.attach(12);
  servo2.attach(14);
  servo3.attach(27);
  servo4.attach(26);
  servo5.attach(25);
  pinMode(pinPIR, INPUT_PULLDOWN);

}

void loop() {
  int statusPIR = digitalRead(pinPIR);

  if (statusPIR == HIGH) {
    servo1.write(90);
    servo2.write(90);
    servo3.write(90);
    servo4.write(90);
    servo5.write(90);
    delay(1000);
  } else{
    sensors_event_t akselerasi, giroskop, suhu_sensor;
    mpu.getEvent(&akselerasi, &giroskop, &suhu_sensor);
    
    int sudutRoll  = -(constrain((int)(akselerasi.acceleration.x * 10), -90, 90));
    int sudutPitch = constrain((int)(akselerasi.acceleration.y * 10), -90, 90);
    int sudutYaw   = constrain((int)(giroskop.gyro.z * 10), -90, 90);

    servo1.write(sudutRoll + 90);
    servo2.write(sudutRoll + 90);
    servo3.write(sudutPitch + 90);
    servo4.write(sudutPitch + 90);
    servo5.write(sudutYaw + 90);

    int pwm12 = map(sudutRoll, -90, 90, 1000, 2000);
    int pwm34 = map(sudutPitch, -90, 90, 1000, 2000);

    Serial.print("PWM Servo 1&2: "); 
    Serial.print(pwm12);
    Serial.print(" PWM Servo 3&4: "); 
    Serial.println(pwm34);

  }

  delay(50);
}
