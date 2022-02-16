# Meet - TV video call system using Raspberry PI
Meet is a video call client running on a Raspberry Pi. The idea is to use a TV and an IR-controller for easy usage, so grandma can see the kids. It is using jitsi (and can be extended to others). The software is simply starting chromium in kiosk mode and translating IR controller commands to the browser. Settings can be done on local webpage of device (http://meet/).
<br><br>
For easy modification, the setup is descriped step by step for each Hardware module. First clone Repo:

```sh
git clone https://github.com/paschkel/Meet
```

## Camera
Meet is using standard raspberry pi camera.
Enable camera and increade GPU Mem to 128 or 256

Raspberry Pi Camera worked directly in Chromium till Version 88. For latest Version of Chromium, following workaround is required:
You can test, if that workaround is needed, by starting webrtc testpage or starting a jitsi meeting in chromium. If camera is working, skip next steps.

Install v4l2 Loopback:
```sh
sudo apt install v4l2loopback-dkms
```
Autostart script for Workaround:
- Move File "meet/camera/CameraWoraround.desktop" to "/home/pi/.config/autostart"


## IR Controller
Hardware: TSOP4838 or similar, data pin connected to pin 15.<br>
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
Hardware: I2S microphone, like SPH0645LM4H or INMP441
Installation of I2S Microphone
Microphone in browser is not working with Pulseausio, just ALSA is required. So first step is to remove Pulseaudio:
```sh
sudo apt-get --purge remove pulseaudio
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
Install Microphone [1]
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
Create Volume Controll for new Input. Add folloing file and paste content off "meet/audio/asound.conf". Save and exit file.
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

## HDMI
To see device name on TV for port selection, define OSD name in config.txt:
```sh
sudo nano /boot/config.txt
```
```sh
cec_osd_name=Meet
```
Work in Process
- Hotplug???

## MeetApp
To Autostart MeetApp, move File "meet/meet.desktop" to "/home/pi/.config/autostart"

Install XDO-Tool (used to send Keys to browser for Mute, Video Off, etc.)
```sh
sudo apt-get install xdotool
```

Install WiringPi (if not already there). Wiring Pi is required to driver LED and Fan.
```sh
sudo apt-get install wiringpi
```


## OnOff
Work in Process
- ON via remote controll


Define OFF-Pin in "/boot/config.txt"
```sh
sudo nano /boot/config.txt
```

<br><br>
<hr>
[1]   Adafruit Website: https://learn.adafruit.com/adafruit-i2s-mems-microphone-breakout/raspberry-pi-wiring-test <br>
[2]   ..
