sudo apt-get install -y mosquitto
sudo apt-get install -y mosquitto-clients

sudo nano /etc/mosquitto/mosquitto.conf

# Make sure to set up the needed config in the mosquitto config file

# Checking if mosquitto is running
sudo systemctl status mosquitto

# Starting MQTT broker
sudo systemctl start mosquitto

# Start MQTT broker at boot
# sudo systemctl enable mosquitto