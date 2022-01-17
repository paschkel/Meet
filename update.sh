#!/bin/bash

echo 'Meet Updater\n'

# Stop Application
sudo killall meet

# Update Files
git clone https://github.com/paschkel/Meet ../temp
cp -r ../temp/* .
rm -rf ../temp

# Reboot
#sudo reboot