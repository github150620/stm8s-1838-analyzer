# stm8s-1838-analyzer
## Features
* Analyse infrared remote controller
* Record pulse width

## What's 1838 ?
* Infrared Receiver Module, used in television and air condition and so on
* 38K carrier wave
* Typical model: HX1838, VS1838

## Wires
```
  1838       STM8S003F3P3     USBtoUART
+------+     +----------+     +-------+
|      |     |          |     |       |
|  Data|<--->|A2      D5|<--->|RX     |
|      |     |          |     |       |
|   GND|<--->|GND    GND|<--->|GND    |
|      |     |          |     |       |
+------+     +----------+     +-------+
```
