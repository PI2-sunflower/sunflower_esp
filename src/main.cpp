#include <PubSubClient.h>
#include <Wire.h>
#include <WiFi.h>
#include <UIPEthernet.h>


// Testing...
long lastMsg = 0;


// MOTOR LEVANTAMENTO
int a = 2, b = 16;
char ler;

int vel = 1024;
int upVel = 32;
int flag_dir = 0;


/* MOVEMENT FUNCTIONS */
void setup_up_down_movement();
void go_up();
void go_down();
void stop_up_down();


/* CONNECTION FUNCTIONS */
void setup_wifi(char* ssid, char* password);


/* MQTT FUNCTIONS */
void callback(char* topic, byte* message, unsigned int length) ;

//WiFiClient espClient;
EthernetClient espClient;
PubSubClient client(espClient);








void setup() {
  Serial.begin(115200);
  //setup_wifi("AndroidK", "senha123");


  uint8_t mac[6] = {0x00,0x01,0x02,0x03,0x04,0x05};
  Ethernet.begin(mac,IPAddress(192,168,1,140));

  const char* mqtt_server = "192.168.1.102";
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  setup_up_down_movement();
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
      go_up();
    }
    else if(messageTemp == "down"){
      go_down();
    }
    else if(messageTemp == "stop"){
      stop_up_down();
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











void setup_wifi(char* ssid, char* password) {
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










// UP AND DOWN MOVEMENT FUNCTIONS
void setup_up_down_movement() {

  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);

  ledcAttachPin(a, 0);//Atribuimos o pino 2 ao canal 0.
  ledcSetup(0, 1000, 10);//Atribuimos ao canal 0 a frequencia de 1000Hz com resolucao de 10bits.

  ledcAttachPin(b, 1);//Atribuimos o pino 2 ao canal 0.
  ledcSetup(0, 1000, 10);//Atribuimos ao canal 0 a frequencia de 1000Hz com resolucao de 10bits.

  ledcWrite(0, 0);
  ledcWrite(1, 0);
}

void go_up() {
  Serial.println("up");

  ledcWrite(1, 0);
  ledcWrite(0, vel);
  flag_dir = 0;
}

void go_down() {
  Serial.println("down");

  ledcWrite(0, 0);
  ledcWrite(1, vel);
  flag_dir = 1;
}

void stop_up_down() {
  Serial.println("stop up and down");

  ledcWrite(0, 0);
  ledcWrite(1, 0);
}
