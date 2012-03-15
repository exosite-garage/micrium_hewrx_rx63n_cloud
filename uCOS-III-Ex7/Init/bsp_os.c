/*
*********************************************************************************************************
*                                                Renesas
*                                         Board Support Package
*                                               RDKRX62N
*
*                             (c) Copyright 2010, Micrium, Weston, FL
*                                           All Rights Reserved
*
*
* File         : BSP_OS.C
* Originally by: Jean J. Labrosse
*
* RDKRX62N Expansion Board modification by Ian Hall
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "includes.h"

/*
*********************************************************************************************************
*                                           LOCAL VARIABLES
*********************************************************************************************************
*/

static  OS_MUTEX  RIIC0_Mutex;
static  OS_MUTEX  RSPI0_Mutex;
static  OS_MUTEX  GLCD_Mutex;


/*
*********************************************************************************************************
*                                     BSP_OS_RIIC0_MutexCreate()
*
* Description : Creates a Mutex used to protect access at a low level to the RIIC ch 0 interface.
*               Allows RIIC0 connected peripherals to be accessed by multiple tasks.
*
* Argument(s) : none.
*
* Return(s)   : DEF_OK,   if successful.
*               DEF_FAIL, otherwise.
*
* Caller(s)   : BSP RIIC0 initialization.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_BOOLEAN  BSP_OS_RIIC0_MutexCreate (void)
{
    OS_ERR  err;

    
    OSMutexCreate(&RIIC0_Mutex,
                  "RIIC0 Mutex",
                  &err);
                    
    if (err != OS_ERR_NONE) {
        return (DEF_FAIL);
    }
    
    return (DEF_OK);
}


/*
*********************************************************************************************************
*                                      BSP_OS_RIIC0_MutexPend()
*
* Description : Obtain mutex. Block if the mutex is not available.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : BSP RIIC0 read/write code.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_OS_RIIC0_MutexPend (void)
{
    OS_ERR  err;
    CPU_TS  ts;


    OSMutexPend(&RIIC0_Mutex,
                 0u,                                            /* no timeout                         */
                 OS_OPT_PEND_BLOCKING,                          /* block if not available             */
                &ts,                                            /* timestamp                          */
                &err);
}


/*
*********************************************************************************************************
*                                      BSP_OS_RIIC0_MutexPost()
*
* Description : Return ownership of mutex back to the RTOS.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : BSP RIIC0 read/write code.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_OS_RIIC0_MutexPost (void)
{
    OS_ERR  err;


    OSMutexPost(&RIIC0_Mutex,
                 OS_OPT_POST_NONE,
                &err);
}

/*
*********************************************************************************************************
*                                     BSP_OS_RSPI0_MutexCreate()
*
* Description : Creates a Mutex used to protect access at a low level to the RSPI ch 0 interface.
*               Allows RSPI0 connected peripherals to be accessed by multiple tasks.
*
* Argument(s) : none.
*
* Return(s)   : DEF_OK,   if successful.
*               DEF_FAIL, otherwise.
*
* Caller(s)   : BSP RSPI0 initialization.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_BOOLEAN  BSP_OS_RSPI0_MutexCreate (void)
{
    OS_ERR  err;


    OSMutexCreate(&RSPI0_Mutex,
                  "RSPI0 Mutex",
                  &err);

    if (err != OS_ERR_NONE) {
        return (DEF_FAIL);
    }

    return (DEF_OK);
}


/*
*********************************************************************************************************
*                                      BSP_OS_RSPI0_MutexPend()
*
* Description : Obtain mutex. Block if the mutex is not available.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : BSP RSPI0 read/write code.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_OS_RSPI0_MutexPend (void)
{
    OS_ERR  err;
    CPU_TS  ts;


    OSMutexPend(&RSPI0_Mutex,
                 0u,                                            /* no timeout                         */
                 OS_OPT_PEND_BLOCKING,                          /* block if not available             */
                &ts,                                            /* timestamp                          */
                &err);
}


/*
*********************************************************************************************************
*                                      BSP_OS_RSPI0_MutexPost()
*
* Description : Return ownership of mutex back to the RTOS.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : BSP RSPI0 read/write code.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_OS_RSPI0_MutexPost (void)
{
    OS_ERR  err;


    OSMutexPost(&RSPI0_Mutex,
                 OS_OPT_POST_NONE,
                &err);
}


/*
*********************************************************************************************************
*                                      BSP_OS_GLCD_MutexCreate()
*
* Description : Creates a Mutex used to protect access at a low level to the graph LCD. Allows graph LCD
*               to be accessed by multiple tasks.
*
* Argument(s) : none.
*
* Return(s)   : DEF_OK,   if successful.
*               DEF_FAIL, otherwise.
*
* Caller(s)   : BSP graph LCD initialization.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_BOOLEAN  BSP_OS_GLCD_MutexCreate (void)
{
    OS_ERR  err;


    OSMutexCreate(&GLCD_Mutex,
                  "GLCD Mutex",
                  &err);

    if (err != OS_ERR_NONE) {
        return (DEF_FAIL);
    }

    return (DEF_OK);
}


/*
*********************************************************************************************************
*                                       BSP_OS_GLCD_MutexPend()
*
* Description : Obtain mutex. Block if the mutex is not available.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : BSP graph LCD read/write code.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_OS_GLCD_MutexPend (void)
{
    OS_ERR  err;
    CPU_TS  ts;


    OSMutexPend(&GLCD_Mutex,
                 0u,                                            /* no timeout                         */
                 OS_OPT_PEND_BLOCKING,                          /* block if not available             */
                &ts,                                            /* timestamp                          */
                &err);
}


/*
*********************************************************************************************************
*                                       BSP_OS_GLCD_MutexPost()
*
* Description : Return ownership of mutex back to the RTOS.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : BSP graph LCD read/write code.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_OS_GLCD_MutexPost (void)
{
    OS_ERR  err;


    OSMutexPost(&GLCD_Mutex,
                 OS_OPT_POST_NONE,
                &err);
}
