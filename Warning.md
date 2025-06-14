# 13/6/2025
- The ESP32 kit used for the project is related to the specified ESP32 kit in [here](https://github.com/1811htsang/Guideline-for-ESP32-WROOM-32-DEVKIT-V1-30P-2ACC7-21116115.git). In Adruino IDE, the ESP32 kit will be named as *DOIT ESP32 DevKit V1*. 
- At first time install Adruino IDE, the ESP32 kit can't be found. Add "Adruino ESP32 Boards" board manager and other board managers to be able to select the ESP32 kit.
- Remember to add the CP210X Universial Windows 10 Driver to make code upload-able from Adruino IDE (COM-5 USB) to ESP32. 

# 14/6/2025
- With simple Wifi, it is possible to only use SSID & password to login. However, with Captive Portal Wifi, they need to use HTTPS method with account attached on payload (optional), specified BSSID and channel to make sure connect.
