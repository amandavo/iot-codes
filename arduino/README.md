# Arduino
A cada arquivo, aprendizados foram adquiridos e gradualmente integrados. A evolução permitiu a criação de um arquivo que incorpora todas as funcionalidades aprendidas ao longo do caminho.

A seguir, contém a lista de arquivos com explicações para facilitar a compreensão e o uso do código.

<br>

- **macAddress:** Configura uma conexão Wi-Fi que pisca um LED a cada 1 segundo, alternando entre ligado e desligado. Útil para testar a conectividade Wi-Fi e verificar se o dispositivo está funcionando.

- **localIP:** Conecta a uma rede Wi-Fi e obtém o endereço MAC do dispositivo, além de configurar a comunicação serial.

- **BluetoothSerialBLE:** O código aguarda dados da conexão Bluetooth para quando os receber, acender o LED e os imprimir no console.

- **ntpServer_time:** Sincroniza o dispositivo com a hora atual de um servidor de tempo NTP (Network Time Protocol)  e imprime a hora a cada minuto.

- **HTTPClient:** Além de conectar o Wi-Fi, obtém a hora atual. O código realiza uma solicitação HTTP POST para um servidor externo a cada 30 segundos. Ela se comunica com o servidor especificado em "serverName," envia informações, como o endereço MAC, a hora atual, a temperatura e a umidade, e imprime a resposta recebida.

- **SemaphoreMutex:** Utiliza tarefas (tasks) concorrentes com semáforos para compartilhar dados, para simular a alteração das variáveis "temp" e "umi" por diferentes processos. Ilustrando a importância de usar semáforos para proteger recursos compartilhados, que garante que as alterações ocorram de forma segura.

- **taskStation:** Simula a coleta de dados ambientais com as medidas de temperatura, umidade, direção do vento, velocidade do vento e pressão que são geradas aleatoriamente e os envia para um servidor externo através de uma solicitação HTTP POST a cada 2 minutos, enquanto monitora a conexão Wi-Fi e com sincronização de tempo via NTP. 
