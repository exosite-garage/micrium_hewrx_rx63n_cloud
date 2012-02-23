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

3) Copy all files (if not already) into the path:<br>
* C:\Micrium\Software\EvalBoards\Renesas\YRDKRX63N\HEW<br>

4) Open workspace "uCOSIII_CLOUD_RX63N.hws"<br>

5) Compile and download -> check https://renesas.exosite.com to see your data
in the cloud!<br>
* HINT: Your RDK must be connected to the Internet via the RJ-45 ethernet jack<br>
* HINT: If your network does not support DHCP, you will need to set static 
        values<br>


========================================
Release Info
========================================
----------------------------------------
Release 2012-02-23
----------------------------------------
--) initial cloud-enabled version<br>
