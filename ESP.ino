#include "PubSubClient.h" // Connect and publish to the MQTT broker
#include "WiFi.h" // Enables ESP32 to connect to the local network

class Button {
  private:
    bool _state;
    uint8_t _pin;

  public:
    Button(uint8_t pin) : _pin(pin) {}

    void begin() {
      pinMode(_pin, INPUT_PULLUP);
      _state = digitalRead(_pin);
    }

    bool isPressed() {
      bool v = digitalRead(_pin);
      if (v != _state) {
        _state = v;
        if (_state) {
          return true; 
        }
    }
    return false;
  }

  bool isActive() {
    if (_state) {
      return true;
    }
    return false;
  }
};

// Pins
const int INTLED = 2;
Button CAM1_BTN(25);
Button CAM2_BTN(26);

// Values
char* active_camera = "1";
int failed_attempts = 0;

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

void publishData(const char* topic, char* camera) {
  connect_MQTT();
  Serial.setTimeout(2000);

  if (client.publish(topic, String(camera).c_str())) {
    Serial.println("Data sent!");
    failed_attempts = 0;
  } else {
    failed_attempts++;
    Serial.println("Data failed to send. Reconnection to broker and trying again");
    client.connect(clientID, mqtt_username, mqtt_password);
    delay(10);
    client.publish(topic, String(camera).c_str());
    if (failed_attempts < 2) {
      publishData(topic, camera);
    }
  }
  client.disconnect();
}

void setup() {
  pinMode(INTLED, OUTPUT);
  CAM1_BTN.begin();
  CAM2_BTN.begin();
  startupConfirmation();
  Serial.begin(9600);
}

void loop() {
  if (CAM1_BTN.isPressed() && active_camera != "1") {
    active_camera = "1";
    Serial.print("Active Camera is now: ");
    Serial.println(active_camera);
    publishData(camera_topic, active_camera);
  } else if (CAM2_BTN.isPressed() && active_camera != "2") {
    active_camera = "2";
    Serial.print("Active Camera is now: ");
    Serial.println(active_camera);
    publishData(camera_topic, active_camera);
  }
}
