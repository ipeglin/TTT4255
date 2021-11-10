import paho.mqtt.client as mqtt

# Variables
mqtt_address = "192.168.1.12" # Broker IP address
mqtt_user = "root" # Broker ID
mqtt_password = "root" # Broker password
mqtt_topic = "ministudio/camera" # The topic of which to subscribe to
broker_listening_port = 1883


def on_connect(client, userdata, flags, reponse_code):
    """Callback function for when client receives CONNACK from server."""
    print("Connected with result code" + str(reponse_code))
    client.subscribe(mqtt_topic)


def on_message(client, userdata, message):
    """Callback for when publish msg is received from server."""
    print(message.topic + "" + str(message.payload))


def main():
    mqtt_client = mqtt.Client()
    mqtt_client.username_pw_set(mqtt_user, mqtt_password)
    mqtt_client.on_connect = on_connect
    mqtt_client.on_message = on_message

    mqtt_client.connect(mqtt_address, broker_listening_port)
    mqtt_client.loop_forever()



if (__name__ == "__main__"):
    print("MQTT to broker bridge")
    main()