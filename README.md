# Microcontrollers Eindopdracht

# Software Components
	- Remote Protocol Encoder (Encodes commands to IR codes then receiver can use)
	- HTTP API exposing functionality over a network (Integratable with OS/Linux project; Receive commands on microcontroller & Send updates(New Remote Protocol learned))
	- Remote Protocol Encoding Learner Module (Learns a command mapping using an IR receiver and a set of standerdised commands the user needs to follow)
	
# Hardware Components
	- Infrared LED
	- Infrared Receiver
	- WiFi Module
	
# Description
	The Atmel AtMega 128 will be able to connect to a network and receive commands over HTTP using a WiFi module.
	Furthermore the microcontroller can decode these commands and emit them with an IR LED.
	Lastly the microcontroller will be able to "learn" a new set of Remote commands & Send an update to the registry service (& event service)
	
# Definitions
	Remote = A Remote control device (To control a tv for example)
