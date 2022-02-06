#!/bin/bash

echo 'Meet Installer\n'

# camera workaround
# sudo apt install v4l2loopback-dkms -y
# Move File "meet/camera/CameraWoraround.desktop" to "/home/pi/.config/autostart"
# cp -r ./camera/CameraWoraround.desktop /home/pi/.config/autostart/

# LIRC
sudo apt-get install ir-keytable -y
# dtoverlay=gpio-ir,gpio_pin=15

# HDMI
# sudo sh -c "echo 'cec_osd_name=Meet' >> /boot/config.txt"
# cec_osd_name=Meet

# XDO and wiringPi
sudo apt-get install xdotool -y
sudo apt-get install wiringpi -y

# install Webserver and PHP
sudo apt-get install apache2 -y
sudo apt-get install php -y

# copy web files....
cp -r ./www/* /var/www/html

# To Autostart MeetApp, move File "meet/meet.desktop" to "/home/pi/.config/autostart"
cp -r ./meet.desktop /home/pi/.config/autostart/