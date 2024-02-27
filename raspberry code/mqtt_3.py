#!python3
import paho.mqtt.client as mqtt
import time
import smbus


datainput= "FFFFFFFFFFFF"
pinstatus= "FFFFFFFFFFFF"



def on_disconnect(client, userdata,rc=0):
	client.will_set("/arduino5/status","OFFLINE", 1)
	client.publish("/arduino5/status","OK", 1)
	client.subscribe("/arduino5/check", 1)
	time.sleep(1)

def on_message(client, userdata, message):
	received=str(message.payload.decode("utf-8"))
	global pinstatus
	global datainput
	if received == pinstatus:
		datainput = pinstatus
		print("OK")   
	





bus = smbus.SMBus(1)
bus.write_byte_data(0x20,0x00,0xFF)
bus.write_byte_data(0x20,0x0C,0xff)
bus.write_byte_data(0x20,0x01,0xFF)
bus.write_byte_data(0x20,0x0D,0xff)
bus.write_byte_data(0x21,0x00,0xFF)
bus.write_byte_data(0x21,0x0C,0xff)
bus.write_byte_data(0x21,0x01,0xFF)
bus.write_byte_data(0x21,0x0D,0xff)
bus.write_byte_data(0x22,0x00,0xFF)
bus.write_byte_data(0x22,0x0C,0xff)
bus.write_byte_data(0x22,0x01,0xFF)
bus.write_byte_data(0x22,0x0D,0xff)

client = mqtt.Client("arduino5",False) 
client.connect("192.168.1.100",1883,5) 
client.will_set("/arduino5/status","OFFLINE", 1)
client.publish("/arduino5/status","OK", 1)
client.subscribe("/arduino5/check", 1)
client.on_disconnect = on_disconnect
client.on_message=on_message
client.loop_start()

while(True):
	inA_1 = hex(bus.read_byte_data(0x20,0x12))
	inA_1=inA_1.upper()
	inA_1=inA_1[2:]
	inB_1 = hex(bus.read_byte_data(0x20,0x13))
	inB_1=inB_1.upper()
	inB_1=inB_1[2:]
	inA_2 = hex(bus.read_byte_data(0x21,0x12))
	inA_2=inA_2.upper()
	inA_2=inA_2[2:]
	inB_2 = hex(bus.read_byte_data(0x21,0x13))
	inB_2=inB_2.upper()
	inB_2=inB_2[2:]
	inA_3 = hex(bus.read_byte_data(0x22,0x12))
	inA_3=inA_3.upper()
	inA_3=inA_3[2:]
	inB_3 = hex(bus.read_byte_data(0x22,0x13))
	inB_3=inB_3.upper()
	inB_3=inB_3[2:]
	pinstatus=inA_1 + inB_1 +inA_2 + inB_2 +inA_3 + inB_3


	if pinstatus != datainput:
			print("Sending " + pinstatus)
			client.will_set("/arduino5/status","OFFLINE", 1)
			client.publish("/arduino5/pinout",pinstatus, 1)
			time.sleep(0.5)

