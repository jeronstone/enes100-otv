# Interstellar OTV Electonics Subsytem 

## Battery/Power Details and Calculations

todo

## Ardunio Pinouts

2: Propulsion: DirB 1  
3: Ultrasonic TX  
4: Ultrasonic RX  
5: Arm Servo Signal  
6: Propulsion: DirA 2  
7: Propulsion: DirA 1  
8: WiFi RX  
9: WiFi TX  
10: Propulsion: ENA   
11: Propulsion: ENB  
12: DutyCycle  
13: Propulsion: DirB 2  
A0: Reed Switch (read as digital input in code)  

**HBRIDGE**: IN1 = DirA 1; IN2 = DirA 2; IN3 = DirB 1; IN4 = DirB 2  
OUT 1-4 to motors  

![Ardunio Pinout Chart](/Images/ARDUINOPINOUT.jpg "Ardunio Pinout Chart")

## Circuit Schematic

![OTV Circuit Schematic](/Images/circuitschem.png "OTV Circuit Schematic")

Battery is connected to breadboard, creating a 12V rail. Ardunio Vin will connect to this rail. Other breadboard rail will be 5V from Ardunio 5V.  

**The sensors/actuators connect to the rails as follows:**  
Ultrasonic Sensor to 5V rail  
Arm Servo to 5V rail  
WiFi module to 5V rail  
Reed Switch Module to 5V rail  
Dual HBridge Motorcontroller to 12V rail  
All of these components will also be connected to (any) ground rail.
