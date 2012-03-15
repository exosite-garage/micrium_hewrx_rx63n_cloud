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
*                                         NETWORK DATA TYPES
*
* Filename      : net_type.h
* Version       : V2.11.02
* Programmer(s) : ITJ
*                 SR
*********************************************************************************************************
*/


/*$PAGE*/
/*
*********************************************************************************************************
*                                             DATA TYPES
*
* Note(s) : (1) Ideally, each network module &/or protocol layer would define all its own data types.  
*               However, some network module &/or protocol layer data types MUST be defined PRIOR to 
*               all other network modules/layers that require their definitions.
*
*               See also 'net.h  NETWORK INCLUDE FILES'.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            NETWORK TYPE
*
* Note(s) : (1) 'NET_TYPE' declared as 'CPU_INT32U' & all 'NET_TYPE's #define'd with large, non-trivial
*               values to trap & discard invalid/corrupted network objects based on 'NET_TYPE'.
*********************************************************************************************************
*/

typedef  CPU_INT32U  NET_TYPE;


/*
*********************************************************************************************************
*                                    NETWORK TRANSACTION DATA TYPE
*********************************************************************************************************
*/

typedef  CPU_INT08U  NET_TRANSACTION;


/*
*********************************************************************************************************
*                          NETWORK MAXIMUM TRANSMISSION UNIT (MTU) DATA TYPE
*
* Note(s) : (1) NET_MTU_MIN_VAL & NET_MTU_MAX_VAL  SHOULD be #define'd based on 'NET_MTU' data type declared.
*********************************************************************************************************
*/

typedef  CPU_INT16U  NET_MTU;
                                                                /* See Note #1.                                         */
#define  NET_MTU_MIN_VAL                DEF_INT_16U_MIN_VAL
#define  NET_MTU_MAX_VAL                DEF_INT_16U_MAX_VAL


/*
*********************************************************************************************************
*                                     NETWORK CHECK-SUM DATA TYPE
*********************************************************************************************************
*/

typedef  CPU_INT16U  NET_CHK_SUM;


/*
*********************************************************************************************************
*                                    NETWORK TIMESTAMP DATA TYPES
*
* Note(s) : (1) RFC #791, Section 3.1 'Options : Internet Timestamp' states that "the Timestamp is a
*               right-justified, 32-bit timestamp in milliseconds since midnight UT [Universal Time]".
*********************************************************************************************************
*/

typedef  CPU_INT32U  NET_TS;
typedef  NET_TS      NET_TS_MS;


/*
*********************************************************************************************************
*                                      NETWORK BUFFER DATA TYPES
*
* Note(s) : (1) NET_BUF_NBR_MAX  SHOULD be #define'd based on 'NET_BUF_QTY' data type declared.
*********************************************************************************************************
*/

typedef  CPU_INT16U  NET_BUF_QTY;                               /* Defines max qty of net bufs to support.              */

#define  NET_BUF_NBR_MIN                                   1
#define  NET_BUF_NBR_MAX                 DEF_INT_16U_MAX_VAL    /* See Note #1.                                         */


typedef  struct  net_buf  NET_BUF;


/*
*********************************************************************************************************
*                                    NETWORK CONNECTION DATA TYPES
*********************************************************************************************************
*/

typedef  CPU_INT16S  NET_CONN_ID;


/*$PAGE*/
/*
*********************************************************************************************************
*                                     NETWORK PROTOCOL DATA TYPE
*********************************************************************************************************
*/

typedef  CPU_INT16U  NET_PROTOCOL_TYPE;


/*
*********************************************************************************************************
*                            NETWORK TRANSPORT LAYER PORT NUMBER DATA TYPE
*
* Note(s) : (1) NET_PORT_NBR_MAX  SHOULD be #define'd based on 'NET_PORT_NBR' data type declared.
*********************************************************************************************************
*/

typedef  CPU_INT16U  NET_PORT_NBR;

#define  NET_PORT_NBR_MAX               DEF_INT_16U_MAX_VAL     /* See Note #1.                                         */


/*
*********************************************************************************************************
*                        NETWORK TRANSPORT LAYER PORT NUMBER QUANTITY DATA TYPE
*********************************************************************************************************
*/

typedef  CPU_INT16U  NET_PORT_NBR_QTY;                          /* Defines max qty of port nbrs to support.             */


/*
*********************************************************************************************************
*                                NETWORK INTERFACE & DEVICE DATA TYPES
*
* Note(s) : (1) NET_IF_NBR_MIN_VAL & NET_IF_NBR_MAX_VAL  SHOULD be #define'd based on 'NET_IF_NBR'
*               data type declared.
*********************************************************************************************************
*/

typedef  CPU_INT08U   NET_IF_NBR;
                                                                /* See Note #1.                                         */
#define  NET_IF_NBR_MIN_VAL             DEF_INT_08U_MIN_VAL
#define  NET_IF_NBR_MAX_VAL             DEF_INT_08U_MAX_VAL


typedef  NET_BUF_QTY  NET_IF_Q_SIZE;                            /* Defines max size of net IF q's to support.           */

#define  NET_IF_Q_SIZE_MIN              NET_BUF_NBR_MIN
#define  NET_IF_Q_SIZE_MAX              NET_BUF_NBR_MAX



typedef  struct  net_if       NET_IF;
typedef  struct  net_if_api   NET_IF_API;


typedef  struct  net_dev_cfg  NET_DEV_CFG;

typedef  CPU_INT32U  NET_DEV_CFG_FLAGS;
typedef  CPU_INT08U  NET_DEV_ISR_TYPE;


/*
*********************************************************************************************************
*                                     NETWORK IP LAYER DATA TYPES
*********************************************************************************************************
*/

typedef  CPU_INT32U  NET_IP_ADDR;                               /* Defines IPv4 IP addr size.                           */


/*
*********************************************************************************************************
*                                    NETWORK TCP LAYER DATA TYPES
*********************************************************************************************************
*/

typedef  CPU_INT32U  NET_TCP_SEQ_NBR;
typedef  CPU_INT16U  NET_TCP_SEG_SIZE;
typedef  CPU_INT16U  NET_TCP_WIN_SIZE;

typedef  NET_TS_MS   NET_TCP_TX_RTT_TS_MS;

