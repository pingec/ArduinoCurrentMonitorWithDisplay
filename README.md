ArduinoCurrentMonitorWithDisplay
===================

Arduino 3phase AC current monitor with 16x2 LCD display (uses EmonLib), outputs to 16x2 LCD display and serial port (if needed)

##Dependencies
Depends on EmonLib and LiquidCrystal (working versions are included and should be copied wherever your IDE setup expects libs).

##Setup
Calibration constants in main.ino should be adjusted to suit the actual current sensors. LCD pins might need reconfiguration as well.

##Output
Measured data will be output shown on LCD dislay and sent to serial port.

![Monitor in action](/images/working.jpg?raw=true "Monitor in action")
