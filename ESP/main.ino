#include <WiFi.h>
#include <PubSubClient.h>


#define LED_PIN 4

// Wifi InFo
const char* ssid = "VOLLY-TECH";
const char* password = "prof1907";

// MQTT Broker server info
const char* mqtt_server = "185.122.200.9";
const int mqtt_port = 1883;

// MQTT topics
const char* topic_led = "esp32/led";
const char* topic_status = "esp32/led/status";

// WiFi and MQTT clients 
WiFiClient espClient;
PubSubClient client(espClient);

// connect to wifi 
void setup_wifi() {
  delay(10);
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi!");
}

// handle MQTT messages
void callback(char* topic, byte* payload, unsigned int length) {
  String message = "";
  for (int i = 0; i<length; i++) {
    message += (char)payload[i];
  }
  Serial.print("Received message: ");
  Serial.println(message);

  if (String(topic) == topic_led) {
    if (message == "ON"){
      digitalWrite(LED_PIN, HIGH);
      Serial.println("LED turned ON");
      client.publish(topic_status, "ON");
    }else if (message == "OFF") {
      digitalWrite(LED_PIN, LOW);
      Serial.println("LED turned OFF");
      client.publish(topic_status, "OFF");
    }
  }
}

// connect to MQTT broker
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32Client")) {
      Serial.println("Connected!");
      client.subscribe(topic_led);
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" Trying again in 5 seconds...");
      delay(5000);
    }
  }
}


void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
