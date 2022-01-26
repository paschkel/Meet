#!/bin/bash

echo 'Meet Updater\n'

# Stop Application
sudo killall meet

# Update Files
git clone https://github.com/paschkel/Meet ../temp
cp -r ../temp/* .
rm -rf ../temp

# Restart Application
sudo ~/Meet/meet

# Reboot
# sudo reboot