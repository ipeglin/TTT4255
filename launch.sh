#!/bin/bash

cd ~/Documents/Git/TTT4255---Elsys-GK-Innovasjonsprosjekt---Raspberry-Pi/
echo "You chose White Balance Mode: $1"
sudo raspistill \
	--fullscreen \
	--vstab \
	--keypress \
	--timeout 0 \
	--flicker 60hz \
	--encoding png \
	-awb $1 \
	--quality 100 \
	-ISO 800 \
	--saturation -5
