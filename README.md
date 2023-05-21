# Projeto ESP32 + DTH22 + PIR on wifi
## Descrição do Projeto

O código fornecido é um exemplo de um projeto que utiliza um microcontrolador ESP8266 para coletar dados de um sensor de temperatura e um sensor PIR (Passive Infrared Sensor), exibir as informações em um display LCD e enviar os dados via MQTT para um servidor MQTT. O projeto também inclui a funcionalidade de detecção de movimento usando o sensor PIR e controle de um LED.

## Documentação e Bibliotecas usadas

O código começa importando as bibliotecas necessárias, como "EspMQTTClient.h" para a comunicação MQTT, "DHTesp.h" para interagir com o sensor de temperatura DHT22 e "LiquidCrystal.h" para controlar o display LCD. Em seguida, são definidas as configurações iniciais, como as informações de conexão WiFi e do servidor MQTT.

### Sobre o codigo:

A função setup() é responsável por inicializar o ambiente, configurando os pinos e os dispositivos, como o display LCD. Também é configurada a depuração MQTT, o web updater e o suporte a atualizações OTA (Over The Air).

A função lerEnviarDados() é responsável por ler os dados do sensor PIR e do sensor de temperatura, exibir as informações no monitor serial e publicar os dados via MQTT nos tópicos correspondentes.

A função onConnectionEstablished() é chamada quando a conexão WiFi e MQTT são estabelecidas com sucesso. Nesse exemplo, ela se inscreve em um tópico MQTT para receber mensagens e exibi-las no monitor serial.

No loop principal loop(), o código verifica o estado do sensor PIR e do sensor de temperatura, atualiza o display LCD com as informações de temperatura e umidade e controla o LED com base no estado do sensor PIR. Além disso, conta o número de acionamentos do sensor PIR e exibe o valor no display LCD.

## Hardware utilizado
O hardware utilizado neste projeto é o microcontrolador ESP8266, que é compatível com a plataforma Arduino. Além disso, são utilizados os seguintes componentes:

Sensor de temperatura DHT22: É um sensor digital que mede a temperatura e a umidade relativa do ar.
Sensor PIR (Passive Infrared Sensor): É um sensor que detecta movimento com base em mudanças no ambiente infravermelho.
Display LCD: É utilizado para exibir informações, como temperatura, umidade e contagem de acionamentos.
LED: É controlado pelo sensor PIR para indicar a detecção de movimento.

## Documentação das interfaces, protocolos e módulos de comunicação
O projeto utiliza a comunicação via internet TCP/IP e o protocolo MQTT para enviar os dados coletados pelos sensores. O módulo ESP8266 se conecta a uma rede WiFi usando as informações fornecidas (SSID e senha) e se conecta a um servidor MQTT (broker) hospedado em "test.mosquitto.org" na porta 1883.

## Comunicação/Controle via internet  
O projeto possui comunicação e controle via internet usando o protocolo MQTT. Os dados coletados pelo sensor de temperatura e o sensor PIR são publicados nos tópicos MQTT "topicowokwi/Temp", "topicowokwi/Humidade" e "topicowokwi/PIR", respectivamente. Além disso, o código também se inscreve no tópico "topicowokwi/msgRecebida/#" para receber mensagens e exibi-las no monitor serial. Isso permite que o dispositivo envie informações e receba comandos ou mensagens do servidor MQTT
