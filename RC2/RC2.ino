
#include <ESPAsyncWebServer.h>
/*
while(Serial.available() > 0) {
delay(10);
char d = Serial.read();
data += d;  
}
if (data.length() > 0){
  Serial2.println(data);
data = "";
}
*/

#include "SD.h"
#include "SPI.h"

#include "WIFI.h"
//17 tx2
//16 rx2
#define RXD2 16
#define TXD2 17
#define SD_CS 5
const char* ssid = "Kelompok RC2";
const char* password = "jossnak9j";
AsyncWebServer server(80);
File file;
String statusled;
String ledinfo;
String data;
IPAddress local_IP(192,168,0,1);
IPAddress gateway(192,168,1,5);
IPAddress subnet(255,255,255,0);

void MenulisDataFileSD(const char* pesanlog){
  file = SD.open("/rc2/LOG.txt", FILE_APPEND);
  if(!file){
        Serial.println("Gagal Membuka File");
        return;
    }
    if(file.println(pesanlog)){
        ;
    } else {
        Serial.println("Gagal menambah data");
    }
    file.close();
}
String proses(const String& var){
  Serial.println(var);
  if(var == "STATUS"){
    if(statusled.equals("on")){
      ledinfo = "Menyala Semua";
    }
    else if(statusled.equals("2")){
      ledinfo = "2";
    }
    else if(statusled.equals("3")){
      ledinfo = "3";
    }
    else if(statusled.equals("epilepsi")){
      ledinfo = "epilepsi";
    }
    else if(statusled.equals("off")){
      ledinfo = "Mati Semua";
    }
    else{
      ledinfo = "None";
    }
    return ledinfo;
  }
}
void finalLOG(String pesan) {
  Serial.println(pesan);
  MenulisDataFileSD(pesan.c_str());
}
void WebServer(){
server.serveStatic("/", SD, "/");
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SD, "/rc2/index.html",String(), false, proses);
  });
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SD, "/rc2/style.css", "text/css");
  });
  server.on("/log", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SD, "/rc2/LOG.txt", "text/plain");
  });
  server.on("/LOG.txt", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SD, "/rc2/LOG.txt", "text/plain");
  });
  server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SD, "/rc2/index.html",String(), false, proses);
    statusled = "on";
    Serial2.print("on");     
    finalLOG("Dari website : Menyalakan Semua LED");
  });
   server.on("/1", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SD, "/rc2/index.html",String(), false, proses);
    statusled = "1";
    Serial2.print("1");     
    finalLOG("Dari website : Menyalakan Animasi 1");
  });
    server.on("/2", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SD, "/rc2/index.html",String(), false, proses);
    statusled = "2";
    Serial2.print("2"); 
    finalLOG("Dari website : Menyalakan Animasi LED 2");
  });
    server.on("/3", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SD, "/rc2/index.html",String(), false, proses);
    statusled = "3";
    Serial2.print("3"); 
    finalLOG("Dari website : Menyalakan Animasi LED 3");
  });
    server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SD, "/rc2/index.html",String(), false, proses);
    statusled = "off";
    Serial2.print("off");  
    finalLOG("Dari website : Mematikan semua LED");
  });
  server.on("/epilepsi", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SD, "/rc2/index.html",String(), false, proses);
    statusled = "epilepsi";
    Serial2.print("epilepsi");  
    finalLOG("Dari website : Epilepsi LED");
  });
}
void setup() {
  // put your setup code here, to run once:
  
  Serial.print("MenSetup Access Point ");
  Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Siap" : "Gagal");
  Serial.print("Memulai Access Point ... ");
  Serial.println(WiFi.softAP(ssid, password, 1, 0, 1, false) ? "Siap" : "Gagal");
  Serial.print("IP address = ");
  Serial.println(WiFi.softAPIP());
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  SD.begin(SD_CS);
  if (!SD.begin(SD_CS)) {
    Serial.println(+ "Gagal Memuat Kartu SD");
    return;
  }
  uint8_t cardType = SD.cardType();
  if (cardType == CARD_NONE) {
    Serial.println("Tidak Ada Kartu SD");
    return;
  }
  
  if(!SD.exists("/rc2")){
    Serial.println("Folder tidak ditemukan");
    if(SD.mkdir("/rc2")){
      Serial.println("Folder Berhasil dibuat");
    }
    else{
      Serial.println("Folder Gagal Dibuat");
    }
  }
  if(!SD.exists("/rc2/LOG.txt")){
     Serial.println("LOG file tidak ditemukan");
    file = SD.open("/rc2/LOG.txt", FILE_WRITE);
    if(!file){
        Serial.println("Gagal membuka File");
        return;
    }
    if(file.print("LOG file telah dibuat")){
        Serial.println("LOG File telah di tulis");
    } else {
        Serial.println("LOG File Gagal di tulis");
    }
  }
  
  WebServer();
  server.begin();
  finalLOG("ESP32 Siap");
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
  data = "";
}
}
