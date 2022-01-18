#!/bin/bash

echo 'Meet Updater\n'

# Stop Application
sudo killall meet

# Update Files
git clone https://github.com/paschkel/Meet ../temp
# Not overide user files
# rm -rf ../temp/MeetingRooms.txt
# rm -rf ../temp/Settings.txt
cp -r ../temp/* .
rm -rf ../temp

# Restart Application
./meet

# Reboot
# sudo reboot
