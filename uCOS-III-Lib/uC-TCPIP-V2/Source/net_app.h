/*
*********************************************************************************************************
*                                             uC/TCP-IP V2
*                                      The Embedded TCP/IP Suite
*
*                          (c) Copyright 2003-2011; Micrium, Inc.; Weston, FL
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
*                        NETWORK APPLICATION PROGRAMMING INTERFACE (API) LAYER
*
* Filename      : net_app.h
* Version       : V2.11.02
* Programmer(s) : ITJ
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) Network Application Programming Interface (API) Layer module is required for :
*
*               (a) Applications that require network application programming interface (API) :
*                   (1) Network socket API with error handling
*                   (2) Network time delays
*
*               See also 'net_cfg.h  NETWORK APPLICATION PROGRAMMING INTERFACE (API) LAYER CONFIGURATION'.
*
*           (2) The following application-module-present configuration value MUST be pre-#define'd in 
*               'net_cfg_net.h' PRIOR to all other network modules that require Network Application 
*               Programming Interface (API) Layer configuration (see 'net_cfg_net.h  NETWORK APPLICATION 
*               PROGRAMMING INTERFACE (API) LAYER CONFIGURATION  Note #2b') :
*
*                   NET_APP_MODULE_PRESENT
*********************************************************************************************************
*/

#ifdef   NET_APP_MODULE_PRESENT                                 /* See Note #2.                                         */


/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/

#if ((defined(NET_APP_MODULE)) && \
     (defined(NET_GLOBALS_EXT)))
#define  NET_APP_EXT
#else
#define  NET_APP_EXT  extern
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                NETWORK APPLICATION TIME DELAY DEFINES
*********************************************************************************************************
*/

#define  NET_APP_TIME_DLY_MIN_SEC                        DEF_INT_32U_MIN_VAL
#define  NET_APP_TIME_DLY_MAX_SEC                        DEF_INT_32U_MAX_VAL

#define  NET_APP_TIME_DLY_MIN_mS                         DEF_INT_32U_MIN_VAL
#define  NET_APP_TIME_DLY_MAX_mS                        (DEF_TIME_NBR_mS_PER_SEC - 1u)


/*
*********************************************************************************************************
*                                             DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/


/*$PAGE*/
/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

#ifdef  NET_SOCK_MODULE_PRESENT                                             /* -------------- SOCK FNCTS -------------- */

NET_SOCK_ID  NetApp_SockOpen  (NET_SOCK_PROTOCOL_FAMILY   protocol_family,
                               NET_SOCK_TYPE              sock_type,
                               NET_SOCK_PROTOCOL          protocol,
                               CPU_INT16U                 retry_max,
                               CPU_INT32U                 time_dly_ms,
                               NET_ERR                   *perr);
                           
CPU_BOOLEAN  NetApp_SockClose (NET_SOCK_ID                sock_id,
                               CPU_INT32U                 timeout_ms,
                               NET_ERR                   *perr);


CPU_BOOLEAN  NetApp_SockBind  (NET_SOCK_ID                sock_id,
                               NET_SOCK_ADDR             *paddr_local,
                               NET_SOCK_ADDR_LEN          addr_len,
                               CPU_INT16U                 retry_max,
                               CPU_INT32U                 time_dly_ms,
                               NET_ERR                   *perr);

CPU_BOOLEAN  NetApp_SockConn  (NET_SOCK_ID                sock_id,
                               NET_SOCK_ADDR             *paddr_remote,
                               NET_SOCK_ADDR_LEN          addr_len,
                               CPU_INT16U                 retry_max,
                               CPU_INT32U                 timeout_ms,
                               CPU_INT32U                 time_dly_ms,
                               NET_ERR                   *perr);


CPU_BOOLEAN  NetApp_SockListen(NET_SOCK_ID                sock_id,
                               NET_SOCK_Q_SIZE            sock_q_size,
                               NET_ERR                   *perr);

NET_SOCK_ID  NetApp_SockAccept(NET_SOCK_ID                sock_id,
                               NET_SOCK_ADDR             *paddr_remote,
                               NET_SOCK_ADDR_LEN         *paddr_len,
                               CPU_INT16U                 retry_max,
                               CPU_INT32U                 timeout_ms,
                               CPU_INT32U                 time_dly_ms,
                               NET_ERR                   *perr);


CPU_INT16U   NetApp_SockRx    (NET_SOCK_ID                sock_id,
                               void                      *pdata_buf,
                               CPU_INT16U                 data_buf_len,
                               CPU_INT16U                 data_rx_th,
                               CPU_INT16S                 flags,
                               NET_SOCK_ADDR             *paddr_remote,
                               NET_SOCK_ADDR_LEN         *paddr_len,
                               CPU_INT16U                 retry_max,
                               CPU_INT32U                 timeout_ms,
                               CPU_INT32U                 time_dly_ms,
                               NET_ERR                   *perr);

CPU_INT16U   NetApp_SockTx    (NET_SOCK_ID                sock_id,
                               void                      *p_data,
                               CPU_INT16U                 data_len,
                               CPU_INT16S                 flags,
                               NET_SOCK_ADDR             *paddr_remote,
                               NET_SOCK_ADDR_LEN          addr_len,
                               CPU_INT16U                 retry_max,
                               CPU_INT32U                 timeout_ms,
                               CPU_INT32U                 time_dly_ms,
                               NET_ERR                   *perr);

#endif

                                                                            /* ------------ TIME DLY FNCTS ------------ */
void         NetApp_TimeDly_ms(CPU_INT32U                 time_dly_ms,
                               NET_ERR                   *perr);


/*$PAGE*/
/*
*********************************************************************************************************
*                                             MODULE END
*
* Note(s) : (1) The Network Application Programming Interface (API) Layer module include MUST end PRIOR 
*               to the validation of all API Layer configuration (see 'net_app.h  CONFIGURATION ERRORS' 
*               & 'net_cfg.h  NETWORK APPLICATION PROGRAMMING INTERFACE (API) LAYER CONFIGURATION').
*
*               See also 'net_app.h  MODULE'.
*********************************************************************************************************
*/

#endif                                                          /* End of net app module include (see Note #1).         */


/*
*********************************************************************************************************
*                                        CONFIGURATION ERRORS
*********************************************************************************************************
*/

#ifndef  NET_APP_CFG_API_EN
#error  "NET_APP_CFG_API_EN        not #define'd in 'net_cfg.h'"
#error  "                    [MUST be  DEF_DISABLED]           "
#error  "                    [     ||  DEF_ENABLED ]           "

#elif  ((NET_APP_CFG_API_EN != DEF_DISABLED) && \
        (NET_APP_CFG_API_EN != DEF_ENABLED ))
#error  "NET_APP_CFG_API_EN  illegally #define'd in 'net_cfg.h'"
#error  "                    [MUST be  DEF_DISABLED]           "
#error  "                    [     ||  DEF_ENABLED ]           "
#endif

