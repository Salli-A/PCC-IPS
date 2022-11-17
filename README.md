# IPS
Github for Project carrier course, part 1. IPS.

### Libraries  

**DW3000**  
**ESPAsyncWebServer-master**  
**AsyncTCP-master**  


### PCC-IPS  

Indoor positing system files.

**Initator**  
Displays distance data.  
Currently only calculates distance from a single device.


**Responder**  
Works with Initator.  
Does not currently have a ID.

**WiFi module**  
Connect ESP32 to 2.4 GHz WiFi and display data at local IP.  
Currently only displays randomly generated value.  
Generates the HTML file.

**WiFi module 2**  
Connect ESP32 to 2.4 GHz WiFi and display data at local IP.  
Currently only displays randomly generated value.  
Does not generate HTML file, sends data on client side request.  
Requires **ESPAsyncWebServer-master** and **AsyncTCP-master** libraries.




