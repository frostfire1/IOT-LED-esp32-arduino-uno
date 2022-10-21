#include <SoftwareSerial.h>
SoftwareSerial Serial2 (2, 3);
int hijau = 10;
int biru = 11;
int merah = 12;
String data;
String statusled;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial2.begin(9600);
pinMode(hijau, OUTPUT);
pinMode(biru, OUTPUT);
pinMode(merah, OUTPUT);
}
void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available() > 0){
  delay(10);
  char d = Serial.read();
  data += d;
}
if (data.length() > 0){
  Serial2.print(data);
  data = "";
}
// berikut code untuk membaca data dari perangkat lain
while(Serial2.available() > 0){
  delay(10);
  char d = Serial2.read();
  data += d;
}
if (data.length() > 0){
  Serial.println(data);
  statusled = data;
  data = "";
}
if(statusled.equals("off")){
    digitalWrite(hijau, LOW);
    digitalWrite(biru, LOW);
    digitalWrite(merah, LOW);
  }
  if(statusled.equals("on")){
    digitalWrite(hijau, HIGH);
    digitalWrite(biru, HIGH);
    digitalWrite(merah, HIGH);    
  }
  if(statusled.equals("1")){
    digitalWrite(merah, LOW);
    digitalWrite(biru, LOW);
    digitalWrite(hijau, LOW);
    digitalWrite(hijau, HIGH);
    delay(1000);
    digitalWrite(biru, HIGH);
    delay(1000);
    digitalWrite(merah, HIGH);
    delay(1000);
    digitalWrite(merah, LOW);
    delay(1000);
    digitalWrite(biru, LOW);
    delay(1000);
    digitalWrite(hijau, LOW);
    delay(1000);
    digitalWrite(merah, LOW);
  }
  if(statusled.equals("2")){
    digitalWrite(merah, LOW);
    digitalWrite(biru, LOW);
    digitalWrite(hijau, LOW);
    digitalWrite(hijau, HIGH);
    delay(1000);
    digitalWrite(hijau, LOW);
    delay(1000);
    digitalWrite(hijau, HIGH);
    delay(1000);
    digitalWrite(biru, HIGH);
    delay(1000);
    digitalWrite(hijau, LOW);
    digitalWrite(biru, LOW);
    delay(1000);
    digitalWrite(hijau, HIGH);
    delay(1000);
    digitalWrite(biru, HIGH);
    delay(1000);
    digitalWrite(merah, HIGH);
    delay(1000);
    digitalWrite(merah, LOW);
    digitalWrite(biru, LOW);
    digitalWrite(hijau, LOW);  
  }
  if(statusled.equals("3")){
    digitalWrite(hijau, HIGH);
    delay(1000);
    digitalWrite(biru, HIGH);
    digitalWrite(hijau, LOW);
    delay(1000);
    digitalWrite(merah, HIGH);
    digitalWrite(biru, LOW);
    delay(1000);
    digitalWrite(merah, LOW);
  }
  if(statusled.equals("epilepsi")){
    digitalWrite(merah, LOW);
    digitalWrite(biru, LOW);
    digitalWrite(hijau, LOW);
    delay(100);    
    digitalWrite(merah, HIGH);
    digitalWrite(biru, HIGH);
    digitalWrite(hijau, HIGH);
    delay(100);    
  }
  else{
    digitalWrite(hijau, HIGH);
    digitalWrite(biru, HIGH);
    digitalWrite(merah, HIGH);
  }
}
