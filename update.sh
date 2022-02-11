#!/bin/bash

echo 'Meet Updater\n'

# Stop Application
sudo killall meet

# Update Files
git clone https://github.com/paschkel/Meet ../temp

# Do not update 
rm -rf ../temp/www/rooms.txt

cp -r ../temp/* .
rm -rf ../temp

sudo cp -r ./www/* /var/www/html

# Restart Application
sudo ~/Meet/meet

# Reboot
# sudo reboot