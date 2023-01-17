# IPS
Github for Project carrier course, part 1. IPS.

### Libraries  

**DW3000**  
**ESPAsyncWebServer-master**  
**AsyncTCP-master**  


### Prototypes

Currently using Prototype 2.1. 

**Tag_Responder_module**  
Responder that acts as a TAG.

**UWB_WiFi_Anchor_AP**  
Initator that acts as ANCHOR and access point (AP).
Sends distance data on request to station.

**UWB_WiFi_Anchor_Station**  
Initator that acts as ANCHOR and station.
Requests distance data from AP anchors with WiFi. 
Sends distance data to device connected on the same WiFi network thought its IP address.
Sends webpage that calculates location and displays it. 

**Instructions**  
Upload the Tag_Responder_module to a singular UWB ESP32 v1.0 microcontroller. 
Upload the UWB_WiFi_Anchor_AP to a two UWB ESP32 v1.0 microcontrollers. 

Upload the UWB_WiFi_Anchor_Station to a singular UWB ESP32 v1.0 microcontroller.
Make sure to press *tools* and select *ESP32 Sketch data upload* before in order to upload the html file to the board.
(Need to close the Arduino IDE everytime the html file is changed for the change to take place. Make sure to use ESP32 board manager in the Arduino IDE.)

Decide on coordinates of all anchors, insert them into the html file in the UWB_WiFi_Anchor_Station. 
Change the code so that the correct IP address of all anchors are correct.
Change the code so that all the anchors connect to the same WiFi network. 
Insert the IP address of the station in a browser of the device which is inteded to display the information.

The ranging is performed using code developed by NConcepts, https://github.com/Makerfabs/Makerfabs-ESP32-UWB-DW3000.


### Modules  

Indoor positing system modules for testing.

**Initator**  
Displays distance data, currently used as ANCHOR.  

**Responder**  
Sends a UWB signal, currently used as TAG

**WiFi module**  
Connect ESP32 to 2.4 GHz WiFi and display data at local IP.  
Currently only displays randomly generated value.  
Generates the HTML file.

**WiFi module 2**  
Connect ESP32 to 2.4 GHz WiFi and display data at local IP.  
Currently only displays randomly generated value.  
Does not generate HTML file, sends data on client side request.  
Requires **ESPAsyncWebServer-master** and **AsyncTCP-master** libraries.

**AnchorServer**  
A module that receives UWB signal, calculates distance while sending data via WiFi to Client module.

**MTO UWB module**  
"Many-To-One" module that sends/receives data from many ANCHORS/INITATORS to a single ANCHOR/INITATOR while it receives a UWB signal.


**WiFi_computer_module** 
Connects to a network and sends continous data packs to computer though the boards ip address.



