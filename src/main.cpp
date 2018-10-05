/*
#include <WiFi.h>

//const char* ssid = "AndroidK";
//const char* password =  "senha123";

const char* ssid = "Net_5";
const char* password =  "1a2b3c4d";

void setup() {

  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println("Connected to the WiFi network");

}


void loop() {
  IPAddress ip;
  ip = WiFi.localIP();
  Serial.println(ip);
  delay(1000);
}
*/



#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>

// Wifi settings and MQTT Broker IP address:
//const char* ssid = "Net_5";
//const char* password =  "1a2b3c4d";
const char* ssid = "AndroidK";
const char* password =  "senha123";

const char* mqtt_server = "192.168.43.68";


WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0;
//char msg[50];
//int value = 0;


// LED Pin
//const int ledPin = 4;


void setup_wifi();
void callback(char* topic, byte* message, unsigned int length) ;


void setup() {
  Serial.begin(115200);

  setup_wifi();

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  // pinMode (LED_BUILTIN, OUTPUT);
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
      //digitalWrite(LED_BUILTIN, HIGH);
    }
    else if(messageTemp == "down"){
      Serial.println("down");
      //digitalWrite(LED_BUILTIN, LOW);
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
