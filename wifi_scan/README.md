
# Wifi Scan challenge

This directory contains a coding challenge that implements 
how to transmit wifi scans from one place to another in an efficient way.

## File structure

- wifi_scan.h  - See the notes section in the definition of the `WifiScan`.
- wifi_scan.c
- main.c
- makefile

## Run program

To run the program execute

```
make
./main
```

To clean the directory

```
make clean
```

## Output

The output of this program will be:

```

Scanning and transmitting.....

===================================
Processing Wifi Scan
===================================
Data to be processed
        Number of scans 2
        SSI list
                ssid[0] = abc
                ssid[1] = x
        BSSI list
                List - 0 
                0x1 0x2 0x3 0x4 0x5 0x6 
                List - 1 
                0x11 0x22 0x33 0x44 0x55 0x66 
        RSSI list
                rssi[0] = -48.000000
                rssi[1] = -50.500000

Finish encoding...

===================================
Transmitting packet
===================================

Wifi Scan - 0
        Name: abc
        Network Id: Ox1 Ox2 Ox3 Ox4 Ox5 Ox6 
        Signal Strength (SSID): -48.000000
        Hexadecimal 
                Ox61 Ox62 Ox63 Ox0 Ox0 Ox0 Ox0 Oxffffffc0 Ox0 Ox0 
                Ox0 Ox0 Ox0 Ox0 Ox0 Oxffffffc0 Ox6 Ox0 Ox0 Ox0 
                Ox0 Ox0 Ox0 Ox0 Ox0 Ox0 Ox0 Ox0 Ox0 Ox0 
                Ox0 Ox0 Ox1 Ox2 Ox3 Ox4 Ox5 Ox6 Oxffffff88 

Wifi Scan - 1
        Name: x
        Network Id: Ox11 Ox22 Ox33 Ox44 Ox55 Ox66 
        Signal Strength (SSID): -50.500000
        Hexadecimal 
                Ox78 Ox0 Ox0 Ox0 Ox0 Ox0 Ox0 Ox0 Ox0 Ox0 
                Ox0 Ox0 Ox0 Ox0 Ox0 Ox0 Ox0 Ox0 Ox0 Ox0 
                Ox0 Ox0 Ox0 Ox0 Ox0 Ox0 Ox0 Ox0 Ox0 Ox0 
                Ox0 Ox0 Ox11 Ox22 Ox33 Ox44 Ox55 Ox66 Oxffffff8d 

End of the transmission .....

```


