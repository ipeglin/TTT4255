#!/bin/bash

# Navigating to correct repo directory on the RP
cd "/home/pi/Documents/Git/TTT4255---Elsys-GK-Innovasjonsprosjekt---Raspberry-Pi/"

<< comment 
Starting the camera with the following settings:
	--fullscreen: Setting the preview window to full screen
	--vstab: Enabling image stabilization
	--timeout 0: The time the camera takes to take a photo. This makes sure the preview stays open
	--flicker 60hz: Setting the camera refresh rate to 60hz to reduce camera flicker
	--encoding png: Saving each image as png to increase image quality
	-awb $1: Setting the white balance to whichever argument the user passed when calling the script
	--quality 100: Using max image quality
	-ISO 800: Setting additional digital lighting to the image
	--saturation -5: Washing out the image by reducing the saturation a bit
comment


sudo raspistill \
	--fullscreen \
	--vstab \
	--timeout 0 \
	--flicker 60hz \
	--encoding png \
	-awb $1 \
	--quality 100 \
	-ISO 800 \
	--saturation -5
