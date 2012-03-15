/*
*********************************************************************************************************
*                                             uC/TCP-IP V2
*                                      The Embedded TCP/IP Suite
*
*                          (c) Copyright 2003-2011; Micrium, Inc.; Weston, FL
*                             (c) Copyright 2008; Renesas Technology Corp.
*
*               All rights reserved.  Protected by international copyright laws.
*
*               uC/TCP-IP is provided in source form to registered licensees ONLY.  It is
*               illegal to distribute this source code to any third party unless you receive
*               written permission by an authorized Micrium representative.  Knowledge of
*               the source code may NOT be used to develop a similar product.
*
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*
*               You can contact us at www.micrium.com.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                        NETWORK DEVICE DRIVER
*
*                                          Renesas RX-EtherC
*
* Filename      : net_dev_rx_etherc.h
* Version       : V2.11.02.00
* Programmer(s) : FGK
*********************************************************************************************************
* Note(s)       : (1) Assumes uC/TCP-IP V2.02 (or more recent version) is included in the project build.
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               MODULE
*********************************************************************************************************
*/

#ifndef  NET_DEV_RX_ETHERC_MODULE_PRESENT
#define  NET_DEV_RX_ETHERC_MODULE_PRESENT


/*
*********************************************************************************************************
*                                      DEVICE DRIVER ERROR CODES
*
* Note(s) : (1) ALL device-independent error codes #define'd in      'net_err.h';
*               ALL device-specific    error codes #define'd in this 'net_dev_&&&.h'.
*
*           (2) Network error code '11,000' series reserved for network device drivers.
*               See 'net_err.h  NETWORK DEVICE ERROR CODES' to ensure that device-specific
*               error codes do NOT conflict with device-independent error codes.
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/

extern  const  NET_DEV_API_ETHER  NetDev_API_RX_EtherC;


/*
*********************************************************************************************************
*                                        CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif                                                          /* End of RX-EtherC module include.                     */

