**For detailed info check description.pdf file**

**Dpenedencies:**  

    •Arduino IDE  
    •Thingspeak IoT platform.  
    •Any mobile app compatible to be used with Thingspeak serve
  
**A. NodeMCU Setup and Code Description**  
    
    •Pin D1 is Rx  
    •Pin D2 is Tx  
    
    Change following parameters in code before uploading it to your device:  

    •ssid : ssid of the wifi network  
    •password : password of your wifi network  
    •mqttUserName[] : your username  
    •mqttPass[] : thingspeak channel pass key  
    •writeAPIKey[] : thingspeak channel write keyB.  

**B. Arduino Mega Setup and Code Description**
  
    Pin Configuration  
    •Pin D1 is Rx  
    •Pin D2 is Tx  

    Change following parameters in code before uploading it to your device:  

    •ssid : ssid of the wifi network  
    •password : password of your wifi network  
    •mqttUserName[] : your username  
    •mqttPass[] : thingspeak channel pass key  
    •writeAPIKey[] : thingspeak channel write keyB.  

    •Pin 10 is Rx•Pin 11 is Tx  
    •For serial communication connect Pin 10, 11 of arduino to Pin D2, D1 of NodeMCU respectively.  
    •Pin (36, 38, 40, 42) are Red LEDs pin for lane 1, 2, 3, 4 respectively.  
    •Pin (37, 39, 41, 43) are Green LEDs pin for lane 1, 2, 3, 4 respectively.  
    •Pin 34 is sound sensor pin for lane 4.  
    •Pin (24, 26, 28, 30) are IR sensor incrementor pin for lane 1, 2, 3, 4 respectively.  
    •Pin (25, 27, 29, 31) are IR sensor decrementor pin for lane 1, 2, 3, 4 respectively.  
    •LCD pins are connected to SDA(20) and SCL(21)Code Description  
    •TIME : this it the time interval for which green light will remain on for any particular lane.  
    •UPDATESERVERTIME:  this  is  the  time  interval  at  which  arduino  sends  data  to  NodeMCU  via  serialcommunication.  
    •jsonserial() : this function is responsible for sending serial data.  
    •readsensor() : this function is responsible for taking input from sensors.  
    •selectLane() : this is function responsible for controlling LEDs based on density based algorithm.  
    •displayArray() : this function is responsible for displaying data on LCD screen connected to Arduino Board.  
    

**C. Thingspeak IoT platform setup**

    1)  Create new channel on Thingspeak.  
    2)  Channel should contain four field to take data of each lane.  
    3)  Update channel configurations in NodeMCU code to connect it.
