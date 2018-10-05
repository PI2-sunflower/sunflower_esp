#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>

// Wifi settings and MQTT Broker IP address:
const char* ssid = "AndroidK";
const char* password =  "senha123";
const char* mqtt_server = "192.168.43.68";
WiFiClient espClient;
PubSubClient client(espClient);

// Testing...
long lastMsg = 0;



// MOTOR LEVANTAMENTO
int a = 2, b = 16;
char ler;

int vel = 1024;
int upVel = 32;
int flag_dir = 0;



/* FUNCTIONS */
void setup_wifi();
void callback(char* topic, byte* message, unsigned int length) ;
void setup_lifting_motor();




void setup() {
  Serial.begin(115200);

  setup_wifi();

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  setup_lifting_motor();
}

void setup_lifting_motor() {

  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);

  ledcAttachPin(a, 0);//Atribuimos o pino 2 ao canal 0.
  ledcSetup(0, 1000, 10);//Atribuimos ao canal 0 a frequencia de 1000Hz com resolucao de 10bits.

  ledcAttachPin(b, 1);//Atribuimos o pino 2 ao canal 0.
  ledcSetup(0, 1000, 10);//Atribuimos ao canal 0 a frequencia de 1000Hz com resolucao de 10bits.

  ledcWrite(0, 0);
  ledcWrite(1, 0);
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;

  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();


  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off".
  if (String(topic) == "movement/up_down") {
    Serial.print("Movement up_down: ");
    if(messageTemp == "up"){
      Serial.println("up");

      ledcWrite(1, 0);
      ledcWrite(0, vel);
      flag_dir = 0;
    }
    else if(messageTemp == "down"){
      Serial.println("down");

      ledcWrite(0, 0);
      ledcWrite(1, vel);
      flag_dir = 1;
    }
    else if(messageTemp == "stop"){
      Serial.println("stop");

      ledcWrite(0, 0);
      ledcWrite(1, 0);
    }
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Subscribe
      client.subscribe("movement/up_down");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;

    // Publish message to esp32/temperature
    const char* humString = "Not raining";
    Serial.print("Humidity: ");
    Serial.println(humString);
    client.publish("sensor/humidity", humString);

  }
}
