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
Define pin 15 for IR
```sh
dtoverlay=gpio-ir,gpio_pin=15
```

Install IR-Keytable
```sh
sudo apt-get install ir-keytable
```


## Microphone

## MeetApp
- Move File Application Files (*.c & *.h) to "/home/pi/MeetApp"

### Autostart MeetApp
Move File "CameraWoraround.desktop" to "/home/pi/.config/autostart"

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
