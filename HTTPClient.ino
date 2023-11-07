#include <WiFi.h>
#include "time.h"
#include <HTTPClient.h>

String uid;

char *ssid = "nao tem wifi";
char *pwd = "40028922";

char *ntpServer = "br.pool.ntp.org";
long gmtOffset = -3;
int daylight = 0;
time_t now;
struct tm timeinfo;

String serverName = "http://postman-echo.com/Post";

void connectWiFi()
{
  Serial.print("Conectando ");
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Conectado com sucesso, com o IP ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  uid = WiFi.macAddress();
  uid.replace(":", "");
  WiFi.begin(ssid, pwd);
  connectWiFi();
  configTime(gmtOffset, daylight, ntpServer);
  if (!getLocalTime(&timeinfo))
  {
    Serial.println("Erro ao acessar o servidor NTP"); 
  }
  else
  {
    Serial.print("A hora agora eh ");
    Serial.println(time(&now));
  }
}

float t = 12.0;
float u = 27.0;

void loop() {
  if (WiFi.status() == WL_CONNECTED)
  {
    if(!getLocalTime(&timeinfo))
    {
      Serial.println("Erro ao coletar data/hora");
    }
    WiFiClient wclient;
    HTTPClient http_post;

    http_post.begin(wclient, serverName);
    http_post.addHeader("Content-Type", "application/json");
    http_post.addHeader("x-api-key", "4554545sdsdsd5454");
    
    
    String tmp = "{\"uid\":\"" + uid + "\",\"unx\":" + time(&now) + ",\"temp\":" + t + ",\"umi\":" + u + "}";

    
    int http_get_code = http_post.POST(tmp.c_str());

    Serial.println("");
    Serial.println(http_get_code);
    if (http_get_code > 0)
    {
      Serial.println(tmp);
      Serial.println(http_post.getString());
    }
    else
    {
      Serial.println("Erro ao executar o GET");
    }
  }
  else 
  {
    Serial.println("Na Fatec nunca tem internet...");
    connectWiFi();
  }
  t = t + 0.25;
  u = u + 0.09;
  delay(30000);
}
