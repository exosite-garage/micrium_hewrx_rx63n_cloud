========================================
About RX63 NMicrium uCOS-III-ExN
========================================
This project contains one Micrium uC/OS-III project for the Renesas RX63N 
Renesas Development Kit (RDK) system.  The project includes cloud connectivity
that does the following things:<br>
1) Runs a provisioning routine at startup to ensure the kit is authenticated<br>
2) Writes a "ping" value to the cloud<br>
3) Reads a "led_ctrl" value from the cloud to control on-board LEDs<br>
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

2) Download Micrium ports on the RX63N
* HINT from http://micrium.com/download/Micrium-uCOS-III-TCPIP-USBD-USBH-YRDKRX63N-binaries.zip<br>

3) Extract the Micrium ports to c:\<br>

4) Download the repository as a zip file and extract the file into the path:<br>
   C:\Micrium\Software\EvalBoards\Renesas\YRDKRX63N\HEW<br>

5) Rename the extracted folder as "RX63N_EXAMPLE"<br>

6) Open workspace "RX63N_EXAMPLE.hws"<br>

5) Compile and download -> check https://renesas.exosite.com to see your data
in the cloud!<br>
* HINT: Your RDK must be connected to the Internet via the RJ-45 ethernet jack<br>
* HINT: If your network does not support DHCP, you will need to set static 
        values<br>


========================================
Release Info
========================================
----------------------------------------
Release 2012-03-15
----------------------------------------
--) Integrate project with new Micrium ports<br>

----------------------------------------
Release 2012-02-23
----------------------------------------
--) initial cloud-enabled version<br>
