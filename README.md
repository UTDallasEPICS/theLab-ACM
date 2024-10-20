The project is an advanced Access Control Manager which supports 3 methods of access. The RFID Scanner and Fingerprint scanner have already been implemented, but their unification on a hardware and software level is required.
The third access method, which is a QR-Code Scanner has successfully been implemented. A magnetic sensor which will check if the door is closed before activating the ACM, has been implemented successfully too and it has been unified along with the QR-Code Scanner on a single ESP32.
Remaining Goals:
Unification of all codebase and hardware
Possible UPS using solar panels
Implementing CRUD on the fingerprint scanner


**ESP32-CAM**
Run the "qr-code-basic.ino" on the CAM connected to FTDI. The board should be selected to "AI Thinker ESP32-CAM" on Arduino IDE.

The ESP32-CAM connects to an FTDI module. The CAM works as a QR-Code Scanner and can detect QR-Codes from a decent range
Connect the ESP32-CAM to FTDI in the following way:

CAM -> FTDI

UOR - TXD

UOT - RXD

5V - VCC (jumper on FTDI set to 5V)

GND - GND

*NOTE*
Connect the IO0 pin of ESP32-CAM to common ground to enter flash mode. This allows to upload code to ESP32-CAM. Disconnect it after the code has been uploaded.


**ESP-WROOM-32**
Run the "esp32-receive.ino" on ESP32 with the board selected as "ESP32-WROOM-DA Module" on Arduino IDE.

The ESP32-CAM sends out the string read from the QR-Code, received by an ESP-WROOM-32.
The connections are as follows:

ESP32 -> CAM

IO16 - IO012

GND - GND


**MAGNETIC SENSOR**
The ESP32 also connects to a magnetic sensor which checks for the closure of the door using 2 magnets. It sends out a HIGH signal when the magnets are close beyond a threshold, otherwise a LOW signal.
The connections are:

ESP32 -> MAGNETIC SENSOR

GND - GND

GPIO12 - IO
