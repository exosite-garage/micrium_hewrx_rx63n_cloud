@ECHO OFF

CD                \MICRIUM\SOFTWARE\uC-TCPIP-V2\SOURCE
MD                \MICRIUM\SOFTWARE\uC-TCPIP-V2\SOURCE\ARCHIVE


DEL   /F /S /Q  ..\*.BAK
DEL   /F /S /Q  ..\*.BCK
DEL   /F /S /Q  ..\*.ERR


COPY  /Y         .\ARCHIVE\*.*                                  .\ARCHIVE\*.*.BCK

COPY  /Y         .\*.*                                          .\ARCHIVE
COPY  /Y        ..\Cfg\Template\net*.*                          .\ARCHIVE
COPY  /Y        ..\BSP\Template\net*.*                          .\ARCHIVE
COPY  /Y        ..\OS\uCOS-II\net*.*                            .\ARCHIVE\net_os_ii*.*
COPY  /Y        ..\OS\uCOS-III\net*.*                           .\ARCHIVE\net_os_iii*.*
COPY  /Y        ..\IF\net*.*                                    .\ARCHIVE
COPY  /Y        ..\Secure\net*.*                                .\ARCHIVE
COPY  /Y        ..\Secure\uC-SSL\net*.*                         .\ARCHIVE
COPY  /Y        ..\Secure\uC-SSL\OS\uCOS-II\net*.*              .\ARCHIVE\net_secure_os_ii*.*
COPY  /Y        ..\Secure\uC-SSL\OS\uCOS-III\net*.*             .\ARCHIVE\net_secure_os_iii*.*

COPY  /Y          \MICRIUM\SOFTWARE\uC-CPU\cpu*.*               .\ARCHIVE
COPY  /Y          \MICRIUM\SOFTWARE\uC-LIB\lib*.*               .\ARCHIVE


DEL   /F /S /Q  ..\*.BAK
DEL   /F /S /Q  ..\*.ERR
