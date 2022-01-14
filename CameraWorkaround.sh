#!/bin/bash

echo 'Workaround for chromium camera input\n'

sudo modprobe v4l2loopback exclusive_caps=1
ffmpeg -i /dev/video0 -f v4l2 /dev/video1