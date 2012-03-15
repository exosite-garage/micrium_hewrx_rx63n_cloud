/*
*********************************************************************************************************
*                                            Renesas YRDKRX62N
*                                      uC/OS-III Board Support Package
*
*                          (c) Copyright 2004-2010; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*
*               uC/CPU is provided in source form to registered licensees ONLY.  It is 
*               illegal to distribute this source code to any third party unless you receive 
*               written permission by an authorized Micrium representative.  Knowledge of 
*               the source code may NOT be used to develop a similar product.
*
*               Please help us continue to provide the Embedded community with the finest 
*               software available.  Your honesty is greatly appreciated.
*
*               You can contact us at www.micrium.com.
*
* File          : BSP_OS.H
* Programmer(s) : ITH
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               MODULE
*********************************************************************************************************
*/

#ifndef  BSP_OS_MODULE_PRESENT
#define  BSP_OS_MODULE_PRESENT

/*
*********************************************************************************************************
*                                               PROTOTYPES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

CPU_BOOLEAN  BSP_OS_RIIC0_MutexCreate(void);
void         BSP_OS_RIIC0_MutexPend  (void);
void         BSP_OS_RIIC0_MutexPost  (void);

CPU_BOOLEAN  BSP_OS_RSPI0_MutexCreate(void);
void         BSP_OS_RSPI0_MutexPend  (void);
void         BSP_OS_RSPI0_MutexPost  (void);

CPU_BOOLEAN  BSP_OS_GLCD_MutexCreate (void);
void         BSP_OS_GLCD_MutexPend   (void);
void         BSP_OS_GLCD_MutexPost   (void);

#endif