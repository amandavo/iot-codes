#include <WiFi.h>

String uid;
char *ssid = "Galaxy";
char *pwd = "12345678";

void connectWiFI() {
  Serial.print("Conectando...");
  while(WiFi.status() != WL_CONNECTED){
    dalay(500);
    Serial.print(":");
  }
  Serial.println("");
  Serial.print("Conectado com sucesso, com o IP ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  uid = WiFi.macAddress();
  uid.replace(":","");
  WiFi.begin(ssid,pwd);
  pinMode(LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

}
