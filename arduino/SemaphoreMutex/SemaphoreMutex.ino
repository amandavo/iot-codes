TaskHandle_t task1;
TaskHandle_t task2;

SemaphoreHandle_t mutex;

float temp = 0.0;
float umi = 0.0;

void minhaTask1(void *pvParameters){
  Serial.println("Começou a task 1");
  while(true){
    xSemaphoreTake(mutex, portMAX_DELAY);
    temp = temp + 0.24;
    umi = umi + 0.51;
    xSemaphoreGive(mutex);
    delay(1300);
  }
}

void minhaTask2(void *pvParameters){
  Serial.println("Começou a task 2");
  while(true){
    temp = temp - 0.09;
    umi = umi - 0.31;
    delay(800);
  }
}

void setup(){
  Serial.begin(115200);

  mutex = xSemaphoreCreateMutex();
  if(mutex == NULL){
    Serial.println("Erro ao criar mutex");
  }

  Serial.println("Criando task 1");
  xTaskCreatePinnedToCore(
    minhaTask1, //funcao da task
    "MinhaTask1", //nome da task
    1000, //tamanho
    NULL, //parametro
    1, //prioridade
    &task1, //task handle
    0 //core (loop = 1)
   );

   Serial.println("Criando a task 2");
    xTaskCreatePinnedToCore(
    minhaTask2,
    "MinhaTask2",
    1000,
    NULL,
    1,
    &task2,
    1
    );

}

void loop(){ 
  xSemaphoreTake(mutex,portMAX_DELAY);
  
  Serial.println("Temperatura");
  Serial.println(temp);
  
  Serial.println("Umidade");
  Serial.println(umi);
  
  //xSemaphoreGive(mutex);
  delay(1000);
}
