#include<SoftwareSerial.h>  // 블루투스 통신을 위한 SoftwareSerial 라이브러리를 불러온다.
#include<Servo.h>
byte buffer[1024]; // 데이터 수신 버퍼
int bufferPosition; // 버퍼에 기록할 위치

Servo servo;

int motorAngle = 0;
int servoVal = 0;
int servoAngle = 90;

void setup () {
  servo.attach(2);
  boolean start=false;
  Serial.begin(9600);
  int startValue=0;
}

void loop () {
  if (Serial.available()) {
//    byte data = Serial.read();
//    //buffer[bufferPosition++] = data; 

    byte data=0;
    int val= Serial.parseInt();

    if(val<360 && val>0) angleSet(val);
    Serial.println(val);
      
         
  }
}

void angleSet(int motorAngle){ // 안드로이드 기울기값을 통해 서보모터를 제어하는 함수
  
    Serial.print("motorAngle = ");
    Serial.println(motorAngle);

    servo.write(motorAngle);
    
}

void angleWrite(int angle){  // 버튼을 통해 서보모터를 제어하는 함수
   
  servo.write(angle); 
}

