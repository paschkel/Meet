#!/bin/bash

echo 'Workaround for chromium camera input\n'

sudo modprobe v4l2loopback exclusive_caps=1
sudo ~/v4l2tools/v4l2copy
