#!/bin/bash

echo 'Meet Updater\n'

sudo killall meet
git clone https://github.com/paschkel/Meet
sudo reboot
