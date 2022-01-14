# Meet
Steps to install Meet
- Download all Files
- Create folder "/home/pi/MeetApp"


## Camera
Enable camera and increade GPU Mem to 128 or 256

Raspberry Pi Camera worked directly in Chromium till Version 88. For latest Version of Chromium, following workaround ir required:
You can test, if that workaround ir required, by starting webrtc testpage or starting a jitsi meeting in chromium. If camera is working, no workaround is required.

Install v4l2 Loopback:
```sh
sudo apt install v4l2loopback-dkms
```
Autostart script for Workaround:
- Move File "CameraWoraround.desktop" to "/home/pi/.config/autostart"
- Move File "CameraWorkaround.sh" to "/home/pi/MeetApp"



## IR Controller
Define IR-Pin in "/boot/config.txt"
```sh
sudo nano /boot/config.txt
```
Define pin 15 for IR-Receiver
```sh
dtoverlay=gpio-ir,gpio_pin=15
```

Install IR-Keytable
```sh
sudo apt-get install ir-keytable
```


## Microphone
Installation of I2S Microphone
Microphone in browser is not working with Pulseausio, just ALSA is required. So first step is to remove Pulseaudio:
```sh
sudo apt-get –-purge remove pulseaudio
```
```sh
sudo reboot
```
Install ALSA (maybe it is already there)
```sh
sudo apt-get install libasound2 alsa-utils alsa-oss
```
```sh
sudo reboot
```
Install Microphone
```sh
sudo apt install python3-pip
```
```sh
sudo pip3 install --upgrade adafruit-python-shell
```
```sh
wget https://raw.githubusercontent.com/adafruit/Raspberry-Pi-Installer-Scripts/master/i2smic.py
```
```sh
sudo python3 i2smic.py
```
```sh
sudo reboot
```
Create Volume Controll for new Input. Add folloing file and paste content off "asound.conf". Save and exit file.
```sh
sudo nano /etc/asound.conf
```
Before volume controll is operating you need to acces input first. You can stop recording  with CTL-Break.
```sh
arecord -D dmic_sv -c2 -r 44100 -f S32_LE -t wav -V mono -v file.wav
```
User Mixer to adjust Volume. Press F6 to selct Sound card and F4 to selct capture. Adjust voluem to 9dB
```sh
alsamixer
```
<br><br>
After system update, it could be that microphone is not working. Please run following script to reinstall it.
```sh
sudo ./i2smic.sh
```

## MeetApp
 Move File Application Files (*.c & *.h) to "/home/pi/MeetApp"<br>

To Autostart MeetApp, move File "CameraWoraround.desktop" to "/home/pi/.config/autostart"

Install XDO-Tool (used to send Keys to browser for Mute, Video Off, etc.)
```sh
sudo apt-get install xdotool
```


Install WiringPi (if not already there). Wiring Pi is required to driver LED and Fan.
```sh
sudo apt-get install wiringpi
```


# OnOff
Define OFF-Pin in "/boot/config.txt"
```sh
sudo nano /boot/config.txt
```
