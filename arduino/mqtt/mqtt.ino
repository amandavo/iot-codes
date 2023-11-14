#include <WiFi.h>
#include <PubSubClient.h>
#include "time.h"

String uid;
char *ssid = "iPhone S2";
char *pwd = "12345678";

WiFiClient wclient;
PubSubClient mqttClient(wclient);

char *mqtt_server = "test.mosquitto.org";

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
  Serial.println("Conectado com sucesso!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void connectMqtt(){
  if(!mqttClient.connected()){
    if(mqttClient.connect(uid.c_str())){
      Serial.println("Conectou ao MQTT");
    }else{
      Serial.println("Mqtt offline");
      delay(5000);
    }
  }
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
  mqttClient.setServer(mqtt_server, 1883);
}

void sincronizaTempo(void){
  configTime(gmtOffset, daylight, ntpServer);
  if (!getLocalTime(&timeinfo)){
    Serial.println("Erro ao acessar o servidor NTP"); 
  }else{
    Serial.println("Data/Hora configurada:");
    Serial.print(time(&now));
  }
}

void loop(){

  if(!mqttClient.connected()){
    connectMqtt();
  }
  mqttClient.loop();
  
  if((time(&now) % 120) == 0){
    sincronizaTempo();
    Serial.print("Enviar dados pelo MQTT");
    mqttClient.publish("fatec/iot/","@15;23;87");
  }
}
