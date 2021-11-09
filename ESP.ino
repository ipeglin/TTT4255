#include "PubSubClient.h" // Connect and publish to the MQTT broker
#include "WiFi.h" // Enables ESP32 to connect to the local network

// Pins
const int INTLED = 2;

// Values
const int delayTime = 6 0; // The amount of seconds between each loop iterations

// WiFi
const char* ssid = "Kalifatet"; // Network SSID
const char* wifi_password = "SOLENYA22"; // Network password

// MQTT
const char* mqtt_server = "192.168.1.12"; // IP of the MQTT broker
const char* camera_topic = "ministudio/camera";
const char* mqtt_username = "root";
const char* mqtt_password = "root";
const char* clientID = "client_camera";

// Init WiFi and MQTT client
WiFiClient wifiClient;
// Listening on port 1883 for the broker
PubSubClient client(mqtt_server, 1883, wifiClient);


// Function to connect to MQTT broker
void connect_MQTT() {
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Connecting to WiFi
  WiFi.begin(ssid, wifi_password);

  // Waiting for connection
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (client.connect(clientID, mqtt_username, mqtt_password)) {
    Serial.println("Connected to MQTT Broker!");
  } else {
    Serial.println("Connection to MQTT Broker failed...");
  }
}

void startupConfirmation() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(INTLED, HIGH);
    delay(100);
    digitalWrite(INTLED, LOW);
    delay(100);
  }
}

void setup() {
  pinMode(INTLED, OUTPUT);
  startupConfirmation();
  Serial.begin(9600);
}

void loop() {
  connect_MQTT();
  Serial.setTimeout(2000);

  char* camera_choice = "Test data";

  // Publish to the MQTT Broker
  if (client.publish(camera_topic, String(camera_choice).c_str())) {
    Serial.println("Data sent!");
  } else {
    Serial.println("Data failed to send. Reconnection to broker and trying again");
    client.connect(clientID, mqtt_username, mqtt_password);
    delay(10);
    client.publish(camera_topic, String(camera_choice).c_str());
  }
  client.disconnect();
  delay(1000*delayTime);
}
