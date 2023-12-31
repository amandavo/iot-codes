#include <WiFi.h>
#include "time.h"

String uid;
char *ssid = "iPhone S2";
char *pwd = "12345678";

char *ntpServer = "br.pool.ntp.org";
long gmtOffset = -3;
int daylight = 0;
time_t now;
struct tm timeinfo;

void connectWiFi(){
  Serial.print("Conectando ");
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Conectado com sucesso, com o IP ");
  Serial.println(WiFi.localIP());
}

void setup(){
  Serial.begin(115200);
  uid = WiFi.macAddress();
  uid.replace(":", "");
  WiFi.begin(ssid, pwd);
  connectWiFi();
  configTime(gmtOffset, daylight, ntpServer);
  if (!getLocalTime(&timeinfo)){
    Serial.println("Erro ao acessar o servidor NTP"); 
  }else{
    Serial.print("Hora: ");
    Serial.println(time(&now));
  }
}

int jaentrei = 0;
void loop(){
  if((time(&now) % 60) == 0){
    if(!jaentrei){
      jaentrei = 1;
      Serial.print("Transmitir -> ");
      Serial.println(time(&now));
    }
  }else{
    jaentrei = 0;
  }
}
