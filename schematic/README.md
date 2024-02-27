# Schematics
In this folder you can view schematic made with [Fritzing](https://fritzing.org/) and ready exported Gerber to upload for production facilities like JLCPCB, the size of the PCB was designed for this [DIN Rail Box](https://ebmstore.it/index.php?route=product/product&product_id=643&search=DIN).
for select the module address you have to set the jumpers like reported on image below:

![collegamenti dei moduli](https://github.com/studiociodo/Gestione-Allarmi-Arduino/assets/150088592/5fa78a74-da98-4ff4-8380-93887a325a14)

The main board is "modulo MCU" that use:

1X [Arduino Nano](https://ebmstore.it/index.php?route=product/product&product_id=2233)

1X [Step Down Module fixed to 5V](https://ebmstore.it/index.php?route=product/product&product_id=64)

1X [Ethernet module W5100 mini](https://it.aliexpress.com/item/32216878864.html)

1X Transistor NPN like BC337

2X Capacitors 10uF

3X Power Diode like BY399

2X Resistor 4700 Ohm 1/4W

1X Resistor 2200 Ohm 1/4W

1X Resistor 4,7 Ohm 1W

3X [2 pole Screw Connector with pitch 5mm](https://ebmstore.it/index.php?route=product/product&product_id=600)

3X [2 pole Screw Connector with pitch 2,54mm](https://ebmstore.it/index.php?route=product/product&product_id=601)




The module "module ingressi" where you can connect 16 normally closed dry contact use:

1X  [MCP23017-E/SP IC package DIP-28](https://it.aliexpress.com/item/1005005363863079.html)

16X [PC817 Optocoupler](https://it.aliexpress.com/item/1005006422922859.html)

16X Resistor 1000 Ohm 1/4W

1X  Resistor 10K Ohm 1/4W

10X [2 pole Screw Connector with pitch 5mm](https://ebmstore.it/index.php?route=product/product&product_id=600)

3X  [2 pole Screw Connector with pitch 2,54mm](https://ebmstore.it/index.php?route=product/product&product_id=601)


This board is in production environment and works fine, but in one case the W5100 does not work well with some Cisco switch. So I develop a solution with a Raspberry type B that autobootup and execute a Python Script to do the same job of Arduino.


