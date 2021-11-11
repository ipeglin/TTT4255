import paho.mqtt.client as mqtt
import typing

# Variables
mqtt_address = "192.168.37.205" # Broker IP address
mqtt_user = "root" # Broker IDpwsh
mqtt_password = "root" # Broker password
mqtt_topic = "ministudio/camera" # The topic of which to subscribe to
broker_listening_port = 1883

# Function that established connection to broker
def on_connect(client, userdata, flags, reponse_code: int) -> None:
    """Callback function for when client receives CONNACK from server."""
    print("Connected with result code" + str(reponse_code))
    client.subscribe(mqtt_topic)

# Function that prints the incoming message in a human readable way
def on_message(client, userdata, message) -> None:
    """Callback for when publish msg is received from server."""
    print(message.topic + ": " + str(message.payload))

# Main function wrapping program
def main() -> None:
    mqtt_client = mqtt.Client() # Creating a client instance of class Client
    mqtt_client.username_pw_set(mqtt_user, mqtt_password) # Setting username and password for broker
    
    # Defining functions for built-in client methods
    mqtt_client.on_connect = on_connect
    mqtt_client.on_message = on_message

    mqtt_client.connect(mqtt_address, broker_listening_port) # Establishing connection to broker
    mqtt_client.loop_forever()


# Don't run the script when used as module
if (__name__ == "__main__"):
    print("MQTT to broker bridge")
    main()