# Node-Red Flow
In this folder you have the [Node-Red](https://nodered.org/) flow of 3 main board: Arduino1 with 3 Modules, Arduino2 with 3 Modules, and Arduino 3 with 2 Modules.
You can replicate this flow simply with import function, modify accordingly with your setup needs.
You can set your server on any PC that you like, For first test I use a RaspberryPi with [RaspiOS](https://www.raspberrypi.com/software/operating-systems/#raspberry-pi-os-32-bit) with the help of [The Script of Peter Scargill](https://tech.scargill.net/the-script/) that install Node-Red with all needed modules and [Mosquitto](https://mosquitto.org/) MQTT Broker.
On a single line you can install ALL of that:
>wget https://bitbucket.org/api/2.0/snippets/scargill/kAR5qG/master/files/script.sh

>bash script.sh

or you can get a copy from this folder.
For production environment I create a [Debian](https://www.debian.org/distrib/) Virtual Machine with mosquitto and Node-Red installed.
In the flow we assume that the server IP is 192.168.1.100 and is configured a sample of smtp server in email sender module that is not connected.
