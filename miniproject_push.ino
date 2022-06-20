#include <SoftwareSerial.h>
SoftwareSerial bt(5, 4);
#include <Servo.h>
Servo servoLeft;
Servo servoRight;

char message; // 블루투스 수신 변수

int trig = 8;
int echo = 6; // 초음파 센서 핀 번호

float Length, distance; // 초음파 센서로 측정한 값 

int self = 0; // self가 1일 때 수동 조종으로 변환

void setup()
{
  pinMode(3, INPUT); pinMode(2, OUTPUT); // 오른쪽 적외선 송수신기
  pinMode(7, OUTPUT); pinMode(9, OUTPUT); // 각각 적외선 송수신기, 초음파 센서 체크용 LED
  
  servoLeft.attach(12);
  servoRight.attach(13); // 서보모터 실행
  
  Serial.begin(9600); // 시리얼 연결
  bt.begin(9600); // 블루투스 연결
  
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT); // 초음파 센서 설정
}

void loop()
{
  if (self == 0) {

    digitalWrite(trig, LOW); 
    digitalWrite(echo, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW); //초음파 센서 작동

    Length = pulseIn(echo, HIGH);
    distance = Length / 29.0 / 2.0; // cm 단위로 측정

    if (distance > 10)
    {
      main_loop();
    } else if (distance < 10) { // 10cm 전방 장애물 감지
      digitalWrite(9, HIGH); // LED 켬
      maneuver(0, 0, 1000); // 회전하기 전에 멈춤
      maneuver(50, -50, 1200); // 일정량 회전
      digitalWrite(9, LOW); // LED 끔
    }
  }
  if (bt.available() > 0) { // 블루투스 연결 확인용 코드
    message = bt.read(); // 블루투스에서 보낸 값 선언
  
    Serial.println(message);
    switch (message) {
      case 0: self = 1;
        self_maneuver(0, 0); break;
        break; // 직접 조종하기 on
      case 1: self = 0; break; // 직접 조종하기 off
      case 2: self_maneuver(50, 50); break; // 전진 on
      case 3: self_maneuver(-30, 30); break; // 좌회전 on
      case 4: self_maneuver(30, -30); break; // 우회전 on
      case 5: self_maneuver(-50, -50); break; // 후진 on
      case 6: self_maneuver(0, 0); break; // 일시정지 on
    }
  }

}

int irDetect(int irLedPin, int irReceiverPin, long frequency) {
  tone(irLedPin, frequency, 8);
  delay(1);
  int ir = digitalRead(irReceiverPin);
  delay(1);
  return ir;
} // 감지 여부 출력

void maneuver(int speedLeft, int speedRight, int msTime)
{
  servoLeft.writeMicroseconds(1500 + speedLeft);
  servoRight.writeMicroseconds(1500 - speedRight);
  if (msTime == -1) {
    servoLeft.detach();
    servoRight.detach();
  }
  delay(msTime);
} // 서보모터 움직임

void self_maneuver(int speedLeft, int speedRight)
{
  servoLeft.writeMicroseconds(1500 + speedLeft);
  servoRight.writeMicroseconds(1500 - speedRight);
} // 서보모터 수동 움직임

void main_loop()
{
  int irRight = irDetect(2, 3, 38000); // 오른쪽 감지 여부 선언

  digitalWrite(7, irRight); // 위와 동일

  if (irRight == 0) { // 둘 다 감지 X
    maneuver(50, 50, 10);
  } else { // 둘 다 감지
    maneuver(50, 50, 200); // 우선 앞으로 조금 전진
    maneuver(0, 0, 1000); // 뒤로 가기 전에 잠깐 멈춤
    maneuver(-50, -50, 500); // 뒤로 충분히 후진
    maneuver(50, -50, 1200); // 여유롭게 시계방향으로 135도 회전
  }
}
