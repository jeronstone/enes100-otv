# Code for OTV  

This folder contains the code that runs on the OTV's Arduino UNO.  

## Classes  

The project's code has been set up to be object oriented. Our main object classes are:  
**ArmServo**, which represents the servo that lowers and raises the arm of our OTV.  
**Propulsion**, which represents our Dual HBridge Motorcontoller.  
**Sensors**, which represents our main senors, incuding our ultrasonic sensor, reed switch, and duty cycle reading.  
**MissionHelper**, a wrapper for the Enes100 object. The wrapper was needed to make this project easily object oriented.  

### ArmServo.cpp  

The main functions of **ArmServo.cpp** are:  

**void begin()**, which must be called before using the servo. This is **NOT** done on construction.  
**void end()**, which *should* be called when you no longer want to use servo (you will have to call begin() again to use servo again.  
**void runArm(bool dir, int time)**, which runs the arm in specified direction **DOWN** or **UP** for **time** milliseconds.  

### Propulsion.cpp  

Propulsion constructor takes MissionHelper object to use for turning.  

The main functions of **Propulsion.cpp** are:  

**void driveFwd()**, which sends the OTV forwards at a default speed (passing an integer param between 0-255 will change that speed).  
**void driveBackwd()**, same as above, but backwards.  
**void stopMotors()**, stops rotation of motors.  
**void turnTo(float targetTheta)**, turns OTV angle towards desired **targetTheta**.  

### Sensors.cpp  

The main functions of **Sensors.cpp** are:  

**float getUltrasonic()**, returns a float of the current ultrasonic sensor value.  
**bool getReed()**, returns a boolean of the current reed switch value (true if magnetic, false if not).  
**bool useReed()**, different from getReed() as it reads for 5 seconds and returns true if a magnetic material is ever detected in that 5 seconds. This is to be used in the mission itself.  
**float readDutyCycle()**, reads the duty cycle of the mission site by taking an average of the current values, using an algorithm to get rid of nonsensical values. This method may take a bit of time to run.   

### MissionHelper.cpp  

Wrapper for Enes100 object.  
The main functions of **Sensors.cpp** are:  

**bool start()**, wrapper for the Enes100.begin() function. Necessary values for the Enes100.begin() are in the wrapper itself.  
**void sendDutyCycle(float dutyCycle)**, wrapper for the Enes100.mission() function. Specifically, for the duty cycle.  
**void sendMagnetic(bool magnetic)**, wrapper for the Enes100.mission() function. Specifically, for the magnetic state of the material.  
**bool updateCurrLocation()**, wrapper for Enes100.updateLocation(). Returns same value.  
**float getX(), float getY(), float getTheta()**, gets current X, Y, and Theta values of OTV location.  
**void sendToVS(String in)**, wrapper for Enes100.println(). Sends param message to vision system console.  
