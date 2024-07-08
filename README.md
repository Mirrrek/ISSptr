# ISSptr

A lil thing that points towards the ISS.

## Required hardware

- [The PCB](https://github.com/Mirrrek/ISSptr/tree/main/schematic), obviously, including:
  - [ESP32-WROOM-32-N4](https://jlcpcb.com/partdetail/EspressifSystems-ESP32_WROOM_32N4/C82899) Microcontroller
  - [QMC5883L](https://jlcpcb.com/partdetail/Qst-QMC5883L/C976032) Magnetometer
  - [ULN2003AD](https://jlcpcb.com/partdetail/TexasInstruments-ULN2003AD/C908113) Transistor Array
  - [AMS1117-3.3](https://jlcpcb.com/partdetail/Advanced_MonolithicSystems-AMS1117_33/C6186) Voltage Regulator
  - [BC817](https://jlcpcb.com/partdetail/Shikues-BC817/C475629) NPN Transistors
  - [TYPE-C-31-M-12](https://jlcpcb.com/partdetail/Korean_HropartsElec-TYPE_C_31_M12/C165948) USB-C Connector
  - [B5B-XH-A(LF)(SN)](https://jlcpcb.com/partdetail/Jst-B5B_XH_A_LF_SN/C157991) Connector
  - Some 0603 resistors and capacitors
- A servo motor (e.g. _SG90_)
- An unipolar stepper motor (e.g. _28BYJ-48_)
- 6-Channel slip ring
