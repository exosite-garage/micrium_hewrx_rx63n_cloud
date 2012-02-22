========================================
About RX63 NMicrium uCOS-III-ExN
========================================
This project contains one Micrium uC/OS-III projects for the Renesas RX63N 
Renesas Development Kit (RDK) system.  The project includes cloud connectivity
that does the following things:<br>
1) Runs a provisioning routine at startup to ensure the kit is authenticated<br>
2) Writes a "ping" value to the cloud<br>
3) Reads a "ledctrl" value from the cloud to control on-board LEDs<br>
4) Outputs cloud status on the LCD screen<br>
5) Outputs MAC address & IP address on the LCD after boot<br>

License of all cloud-specific components is BSD, Copyright 2012, Exosite LLC 
(see LICENSE file)<br>

Tested with HEW version 4.09.00.007, including:<br>
Compiler RX Stander Toolchain v1.2.0.0  (7-20-2011)<br>
Renesas Demonstration Kit (RDK) RX63N Rev 2

========================================
Project Descriptions
========================================
----------------------------------------
uCOS-III-Ex7
----------------------------------------
* Blinks the LEDs in different patterns<br>

========================================
Quick Start
========================================
1) Install C/C++ Compiler Package for RX Family V.1.02 Release 00  
* HINT from http://www.renesas.com/request?SCREEN_ID=ViewGRSDownloadSearch&EXECUTE_ACTION=search#<br>

2) open HEW and create a new project workspace of RX63N

3) under Debug->Debug Sessions, select the J-Link session as the Current Session<br>

4) Plug kit to your PC<br>

5) When the RDK is connected, a new option under the File menu will appear:<br>
   “Download a New Module”.  Select that item and choose the option “S-Record”<br>
   for File format. For Filename, use the Browse… button to select the .mot<br>
   pre-built binary image you want to download. <br>

========================================
Release Info
========================================
----------------------------------------
Release 2012-02-22
----------------------------------------
--) initial cloud-enabled version<br>
