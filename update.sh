#!/bin/bash

# Navigating to correct repo directory on the RP
cd "/home/pi/Documents/Git/TTT4255/"

# Pulling the newest version from the remote GitHub repo
git pull origin master

# Copying the files to the users home directory so they can be used without navigating to repo dir.
sudo cp * ~
