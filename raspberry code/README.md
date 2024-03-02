# Raspberry variant
In the vast majority of installation the main board with Arduino and W5100 works fine, but on an environment with Cisco switch I have notice some disconnections, So I develop a variation of the Mainboard module that use a Raspberry model B instead of Arduino.
You do not need much cpu power, version 2 or 3 works fine.
You need to enable SPI bus on raspi-config, and on boot auto execute this Python script, on this folder there is 3 variation for main board this 1 to 3 module respectivly.
On system you nedd to install python and realtive depencies, like this:

> apt-get install python3 python3-pip

> pip3 install paho-mqtt

> pip3 install smbus
