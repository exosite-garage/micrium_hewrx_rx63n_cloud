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
*                                   NETWORK OPERATING SYSTEM LAYER
*
*                                          Micrium uC/OS-III
*
* Filename      : net_os.h
* Version       : V2.11.02
* Programmer(s) : ITJ
*                 EHS
*                 SL
*                 HS
*********************************************************************************************************
* Note(s)       : (1) Assumes uC/OS-III V3.01.0 (or more recent version) is included in the project build.
*
*                 (2) REQUIREs the following uC/OS-III feature(s) to be ENABLED :
*
*                         --------- FEATURE ----------    ---- MINIMUM CONFIGURATION FOR NET/OS PORT -----
*
*                     (a) Semaphores
*                         (1) OS_CFG_SEM_EN               Enabled
*                         (2) OS_CFG_SEM_SET_EN           Enabled
*                         (3) OS_CFG_SEM_PEND_ABORT_EN    Enabled
*
*                     (b) Task Queues
*                         (1) OS_CFG_TASK_Q_EN            Enabled
*
*                     (c) Messages                        OS_CFG_MSG_POOL_SIZE or OSCfg_MsgPoolSize 
*                                                             >= NET_OS_NBR_MSGS (see 'OS OBJECT DEFINES')
*
*                     (d) Multi-Pend
*                         (1) OS_CFG_PEND_MULTI_EN        Enabled -- required only if NET_SOCK_CFG_SEL_EN
*                                                             is DEF_ENABLED
*
*                     (e) Time Delay
*                         (1) OS_CFG_TIME_DLY_HMSM_EN     Enabled
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include  <os_cfg_app.h>
#include  <os.h>                                                /* See this 'net_os.h  Note #1'.                        */


/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/

#if ((defined(NET_OS_MODULE)) && \
     (defined(NET_GLOBALS_EXT)))
#define  NET_OS_EXT
#else
#define  NET_OS_EXT  extern
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                     OS TASK/OBJECT NAME DEFINES
*
* Note(s) : (1) The following OS task/object name abbreviated to enforce ANSI-compliance of 31-character
*               symbol length uniqueness :
*
*               (a) 'NET_OS_SOCK_CONN_ACCEPT_Q_NAME' abbreviated to 'NET_OS_SOCK_CONN_ACCEPT_NAME'
*********************************************************************************************************
*/

                                                                /* -------------------- TASK NAMES -------------------- */
                                          /*           1         2         3 */
                                          /* 0123456789012345678901234567890 */
#define  NET_OS_TMR_TASK_NAME               "Net Tmr Task"

#define  NET_OS_IF_RX_TASK_NAME             "Net IF Rx Task"
#define  NET_OS_IF_TX_DEALLOC_TASK_NAME     "Net IF Tx Dealloc Task"



                                                                /* -------------------- OBJ NAMES --------------------- */
                                          /*           1         2         3 */
                                          /* 0123456789012345678901234567890 */
#define  NET_OS_INIT_NAME                   "Net Init Signal"
#define  NET_OS_LOCK_NAME                   "Net Global Lock"

#define  NET_OS_DEV_TX_RDY_NAME             "Net Dev Tx Rdy #xxx"
#define  NET_OS_DEV_TX_RDY_NAME_SIZE                      20
#define  NET_OS_DEV_TX_RDY_NAME_IX_NBR                    16

#define  NET_OS_IF_RX_Q_NAME                "Net IF Rx Q"
#define  NET_OS_IF_TX_DEALLOC_Q_NAME        "Net IF Tx Dealloc Q"
#define  NET_OS_IF_TX_SUSPEND_NAME          "Net IF Tx Suspend #xxx"

#define  NET_OS_IF_TX_SUSPEND_NAME_SIZE                   23
#define  NET_OS_IF_TX_SUSPEND_NAME_IX_NBR                 19


#define  NET_OS_TCP_RX_Q_NAME               "Net TCP Rx Q #xxxxx"
#define  NET_OS_TCP_TX_Q_NAME               "Net TCP Tx Q #xxxxx"

#define  NET_OS_TCP_RX_Q_NAME_SIZE                        20
#define  NET_OS_TCP_TX_Q_NAME_SIZE                        20

#define  NET_OS_TCP_RX_Q_NAME_IX_ID                       14
#define  NET_OS_TCP_TX_Q_NAME_IX_ID                       14


#define  NET_OS_SOCK_RX_Q_NAME              "Net Sock Rx Q #xxxxx"
#define  NET_OS_SOCK_CONN_REQ_NAME          "Net Sock Conn Req #xxxxx"
#define  NET_OS_SOCK_CONN_ACCEPT_NAME       "Net Sock Conn Accept Q #xxxxx"
#define  NET_OS_SOCK_CONN_CLOSE_NAME        "Net Sock Conn Close #xxxxx"

#define  NET_OS_SOCK_RX_Q_NAME_SIZE                       21
#define  NET_OS_SOCK_CONN_REQ_NAME_SIZE                   25
#define  NET_OS_SOCK_CONN_ACCEPT_NAME_SIZE                30
#define  NET_OS_SOCK_CONN_CLOSE_NAME_SIZE                 27

#define  NET_OS_SOCK_RX_Q_NAME_IX_ID                      15
#define  NET_OS_SOCK_CONN_REQ_NAME_IX_ID                  19
#define  NET_OS_SOCK_CONN_ACCEPT_NAME_IX_ID               24
#define  NET_OS_SOCK_CONN_CLOSE_NAME_IX_ID                21


/*
*********************************************************************************************************
*                                          OS OBJECT DEFINES
*********************************************************************************************************
*/

#define  NET_OS_NBR_MSGS                                (NET_OS_CFG_IF_RX_Q_SIZE        + \
                                                         NET_OS_CFG_IF_TX_DEALLOC_Q_SIZE)


#define  NET_OS_NBR_EVENTS                               NET_OS_NBR_MSGS

#define  NET_OS_NBR_EVENTS_MIN                             1u
#define  NET_OS_NBR_EVENTS_MAX                           DEF_INT_16U_MAX_VAL


/*$PAGE*/
/*
*********************************************************************************************************
*                                   OS TIMEOUT & TIME DELAY DEFINES
*
* Note(s) : (1) uC/OS-III does NOT support microsecond time values :
*
*               (a) Microsecond timeout    values provided for network microsecond timeout values, but
*                   are rounded to millisecond timeout values.
*
*               (b) Microsecond time delay values NOT supported.
*
*           (2) To avoid macro integer overflow, an OS timeout tick threshold value MUST be configured
*               to avoid values that overflow the target CPU &/or compiler environment.
*
*               (a) (1) Ideally, 'NET_OS_TICK_RATE_MAX_HZ' would be based on &/or #define'd as uC/OS-III's 
*                       'OS_CFG_TICK_RATE_HZ'.  However, when uC/OS-III is provided as a linkable library, 
*                       application configuration constants (such as 'OS_CFG_TICK_RATE_HZ') are NOT 
*                       guaranteed to be available during later compilation.
*
*                   (2) Therefore, in order to #define maximum OS timeout values, the highest possible 
*                       (or likely) value for uC/OS-III's OS ticker frequency MUST be assumed in order 
*                       to avoid values that overflow the target CPU &/or compiler environment.
*********************************************************************************************************
*/

#define  NET_OS_TIMEOUT_MIN_TICK                           1u
#define  NET_OS_TIMEOUT_MAX_TICK                         DEF_INT_32U_MAX_VAL

#define  NET_OS_TICK_RATE_MAX_HZ                       25000u                       /* See Note #2a.                    */



#define  NET_OS_TIMEOUT_MIN_SEC                          DEF_INT_32U_MIN_VAL
#define  NET_OS_TIMEOUT_MIN_mS                           DEF_INT_32U_MIN_VAL
#define  NET_OS_TIMEOUT_MIN_uS                           DEF_INT_32U_MIN_VAL


#if     (NET_OS_TICK_RATE_MAX_HZ > 0)

#define  NET_OS_TIMEOUT_MAX_SEC                         (NET_OS_TIMEOUT_MAX_TICK / NET_OS_TICK_RATE_MAX_HZ)

                                                                                    /* See Note #2.                     */
#if     (NET_OS_TICK_RATE_MAX_HZ > (DEF_TIME_NBR_mS_PER_SEC / \
                                   (DEF_INT_32U_MAX_VAL     / \
                                    NET_OS_TIMEOUT_MAX_TICK)))
#define NET_OS_TIMEOUT_MAX_mS                           (NET_OS_TIMEOUT_MAX_SEC  * DEF_TIME_NBR_mS_PER_SEC)
#else
#define NET_OS_TIMEOUT_MAX_mS                            DEF_INT_32U_MAX_VAL
#endif


#if     (NET_OS_TICK_RATE_MAX_HZ > (DEF_TIME_NBR_uS_PER_SEC / \
                                   (DEF_INT_32U_MAX_VAL     / \
                                    NET_OS_TIMEOUT_MAX_TICK)))
#define  NET_OS_TIMEOUT_MAX_uS                          (NET_OS_TIMEOUT_MAX_SEC  * DEF_TIME_NBR_uS_PER_SEC)
#else
#define  NET_OS_TIMEOUT_MAX_uS                           DEF_INT_32U_MAX_VAL
#endif


#else
#define  NET_OS_TIMEOUT_MAX_SEC                          DEF_INT_32U_MIN_VAL
#define  NET_OS_TIMEOUT_MAX_mS                           DEF_INT_32U_MIN_VAL
#define  NET_OS_TIMEOUT_MAX_uS                           DEF_INT_32U_MIN_VAL
#endif



#define  NET_OS_TIME_DLY_MIN_SEC                         DEF_INT_32U_MIN_VAL
#define  NET_OS_TIME_DLY_MAX_SEC                       (( 999u * DEF_TIME_NBR_SEC_PER_HR ) + \
                                                        (9999u * DEF_TIME_NBR_SEC_PER_MIN) + \
                                                         DEF_INT_16U_MAX_VAL)

#define  NET_OS_TIME_DLY_MIN_mS                          DEF_INT_16U_MIN_VAL
#define  NET_OS_TIME_DLY_MAX_mS                         (DEF_TIME_NBR_mS_PER_SEC - 1u)
                                                                                    /* See Note #1b.                    */
#define  NET_OS_TIME_DLY_MIN_uS                            0u
#define  NET_OS_TIME_DLY_MAX_uS                            0u


/*$PAGE*/
/*
*********************************************************************************************************
*                                             DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*
* Note(s) : (1) (a) Signals & locks are implemented using binary   semaphores.
*
*               (b) (1) Some queues are implemented using counting semaphores.
*                   (2) Some queues are implemented using message queues.
*********************************************************************************************************
*/

                                                                            /* -------------- TASK TCBs --------------- */
NET_OS_EXT  OS_TCB     NetOS_Tmr_TaskTCB;

NET_OS_EXT  OS_TCB     NetOS_IF_RxTaskTCB;
NET_OS_EXT  OS_TCB     NetOS_IF_TxDeallocTaskTCB;

                                                                            /* ------------- TASK STACKS -------------- */
NET_OS_EXT  CPU_STK    NetOS_Tmr_TaskStk[NET_OS_CFG_TMR_TASK_STK_SIZE];

NET_OS_EXT  CPU_STK    NetOS_IF_RxTaskStk[NET_OS_CFG_IF_RX_TASK_STK_SIZE];
NET_OS_EXT  CPU_STK    NetOS_IF_TxDeallocTaskStk[NET_OS_CFG_IF_TX_DEALLOC_TASK_STK_SIZE];


                                                                            /* --------------- SIGNALS ---------------- */
NET_OS_EXT  OS_SEM     NetOS_InitSignalObj;
NET_OS_EXT  OS_SEM     NetOS_Dev_TxRdySignalObj[NET_IF_NBR_IF_TOT];

#if    (NET_CFG_LOAD_BAL_EN == DEF_ENABLED)
NET_OS_EXT  OS_SEM     NetOS_IF_TxSuspendSignalObj[NET_IF_NBR_IF_TOT];
#endif

#ifdef  NET_SOCK_MODULE_PRESENT
#if    (NET_SOCK_CFG_TYPE_STREAM_EN == DEF_ENABLED)
NET_OS_EXT  OS_SEM     NetOS_Sock_ConnReqSignalObj[NET_SOCK_CFG_NBR_SOCK];
NET_OS_EXT  OS_SEM     NetOS_Sock_ConnAcceptQ_SignalObj[NET_SOCK_CFG_NBR_SOCK];
NET_OS_EXT  OS_SEM     NetOS_Sock_ConnCloseSignalObj[NET_SOCK_CFG_NBR_SOCK];
#endif
#endif


                                                                            /* ---------------- LOCKS ----------------- */
NET_OS_EXT  OS_MUTEX   NetOS_LockObj;
#if (NET_ERR_CFG_ARG_CHK_DBG_EN == DEF_ENABLED)
NET_OS_EXT  OS_TCB    *NetOS_LockTaskPtr;
#endif


                                                                            /* ---------------- QUEUES ---------------- */
#ifdef  NET_TCP_MODULE_PRESENT
NET_OS_EXT  OS_SEM     NetOS_TCP_RxQ_SignalObj[NET_TCP_CFG_NBR_CONN];
NET_OS_EXT  OS_SEM     NetOS_TCP_TxQ_SignalObj[NET_TCP_CFG_NBR_CONN];
#endif

#ifdef  NET_SOCK_MODULE_PRESENT
NET_OS_EXT  OS_SEM     NetOS_Sock_RxQ_SignalObj[NET_SOCK_CFG_NBR_SOCK];
#endif


/*$PAGE*/
                                                                            /* ---------------- TIMERS ---------------- */
#ifdef  NET_OS_TIMEOUT_PRESENT

#if    (NET_CFG_LOAD_BAL_EN == DEF_ENABLED)
NET_OS_EXT  OS_TICK    NetOS_IF_TxSuspendTimeout_tick[NET_IF_NBR_IF_TOT];
#endif

#ifdef  NET_TCP_MODULE_PRESENT
NET_OS_EXT  OS_TICK    NetOS_TCP_RxQ_TimeoutTbl_tick[NET_TCP_CFG_NBR_CONN];
NET_OS_EXT  OS_TICK    NetOS_TCP_TxQ_TimeoutTbl_tick[NET_TCP_CFG_NBR_CONN];
#endif

#ifdef  NET_SOCK_MODULE_PRESENT
NET_OS_EXT  OS_TICK    NetOS_Sock_RxQ_TimeoutTbl_tick[NET_SOCK_CFG_NBR_SOCK];

#if    (NET_SOCK_CFG_TYPE_STREAM_EN == DEF_ENABLED)
NET_OS_EXT  OS_TICK    NetOS_Sock_ConnReqTimeoutTbl_tick[NET_SOCK_CFG_NBR_SOCK];
NET_OS_EXT  OS_TICK    NetOS_Sock_ConnAcceptQ_TimeoutTbl_tick[NET_SOCK_CFG_NBR_SOCK];
NET_OS_EXT  OS_TICK    NetOS_Sock_ConnCloseTimeoutTbl_tick[NET_SOCK_CFG_NBR_SOCK];
#endif
#endif

#endif


                                                                            /* ---------------- NAMES ----------------- */
NET_OS_EXT  CPU_CHAR   NetOS_Dev_TxRdySignalName[NET_IF_NBR_IF_TOT][NET_OS_DEV_TX_RDY_NAME_SIZE];

#if    (NET_CFG_LOAD_BAL_EN == DEF_ENABLED)
NET_OS_EXT  CPU_CHAR   NetOS_IF_TxSuspendSignalName[NET_IF_NBR_IF_TOT][NET_OS_IF_TX_SUSPEND_NAME_SIZE];
#endif

#ifdef  NET_TCP_MODULE_PRESENT
NET_OS_EXT  CPU_CHAR   NetOS_TCP_RxQ_SignalName[NET_TCP_CFG_NBR_CONN][NET_OS_TCP_RX_Q_NAME_SIZE];
NET_OS_EXT  CPU_CHAR   NetOS_TCP_TxQ_SignalName[NET_TCP_CFG_NBR_CONN][NET_OS_TCP_TX_Q_NAME_SIZE];
#endif

#ifdef  NET_SOCK_MODULE_PRESENT
NET_OS_EXT  CPU_CHAR   NetOS_Sock_RxQ_SignalName[NET_SOCK_CFG_NBR_SOCK][NET_OS_SOCK_RX_Q_NAME_SIZE];

#if    (NET_SOCK_CFG_TYPE_STREAM_EN == DEF_ENABLED)
NET_OS_EXT  CPU_CHAR   NetOS_Sock_ConnReqSignalName[NET_SOCK_CFG_NBR_SOCK][NET_OS_SOCK_CONN_REQ_NAME_SIZE];
NET_OS_EXT  CPU_CHAR   NetOS_Sock_ConnAcceptQ_SignalName[NET_SOCK_CFG_NBR_SOCK][NET_OS_SOCK_CONN_ACCEPT_NAME_SIZE];
NET_OS_EXT  CPU_CHAR   NetOS_Sock_ConnCloseSignalName[NET_SOCK_CFG_NBR_SOCK][NET_OS_SOCK_CONN_CLOSE_NAME_SIZE];
#endif
#endif


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/


/*$PAGE*/
/*
*********************************************************************************************************
*                                        CONFIGURATION ERRORS
*
* Note(s) : (1) See also this 'net_os.c  NetOS_Init()      Note #1a'
*                      & this 'net_os.c  NetOS_Tmr_Init()  Note #1a'.
*********************************************************************************************************
*/

                                                                                    /* See this 'net_os.h  Note #1'.    */
#if     (OS_VERSION < 3010u)
#error  "OS_VERSION                              [SHOULD be >= V3.01.0]"
#endif



                                                                                    /* See this 'net_os.h  Note #2a'.   */
#if     (OS_CFG_SEM_EN < 1)
#error  "OS_CFG_SEM_EN                           illegally #define'd in 'os_cfg.h'          "
#error  "                                        [MUST be  > 0, (see 'net_os.h  Note #2a1')]"
#endif

#if     (OS_CFG_SEM_SET_EN < 1)
#error  "OS_CFG_SEM_SET_EN                       illegally #define'd in 'os_cfg.h'          "
#error  "                                        [MUST be  > 0, (see 'net_os.h  Note #2a2')]"
#endif

#if     (OS_CFG_SEM_PEND_ABORT_EN < 1)
#error  "OS_CFG_SEM_PEND_ABORT_EN                illegally #define'd in 'os_cfg.h'          "
#error  "                                        [MUST be  > 0, (see 'net_os.h  Note #2a3')]"
#endif



                                                                                    /* See this 'net_os.h  Note #2b'.   */
#if     (OS_CFG_TASK_Q_EN < 1)
#error  "OS_CFG_TASK_Q_EN                        illegally #define'd in 'os_cfg.h'          "
#error  "                                        [MUST be  > 0, (see 'net_os.h  Note #2b1')]"
#endif




#if     (NET_SOCK_CFG_SEL_EN == DEF_ENABLED)
                                                                                    /* See this 'net_os.h  Note #2d'.   */
#if     (OS_CFG_PEND_MULTI_EN < 1)
#error  "OS_CFG_PEND_MULTI_EN                    illegally #define'd in 'os_cfg.h'                    "
#error  "                                        [MUST be  > 0, if NET_SOCK_CFG_SEL_EN is DEF_ENABLED]"
#error  "                                        [           (see 'net_os.h  Note #2d1')             ]"
#endif

#endif



                                                                                    /* See this 'net_os.h  Note #2e'.   */
#if     (OS_CFG_TIME_DLY_HMSM_EN < 1)
#error  "OS_CFG_TIME_DLY_HMSM_EN                 illegally #define'd in 'os_cfg.h'          "
#error  "                                        [MUST be  > 0, (see 'net_os.h  Note #2e1')]"
#endif




/*$PAGE*/
#ifndef  NET_OS_CFG_IF_RX_TASK_PRIO
#error  "NET_OS_CFG_IF_RX_TASK_PRIO                    not #define'd in 'app_cfg.h'"
#error  "                                        [MUST be  >= 0]                   "

#elif   (NET_OS_CFG_IF_RX_TASK_PRIO < 0)
#error  "NET_OS_CFG_IF_RX_TASK_PRIO              illegally #define'd in 'app_cfg.h'"
#error  "                                        [MUST be  >= 0]                   "
#endif


#ifndef  NET_OS_CFG_IF_TX_DEALLOC_TASK_PRIO
#error  "NET_OS_CFG_IF_TX_DEALLOC_TASK_PRIO            not #define'd in 'app_cfg.h'"
#error  "                                        [MUST be  >= 0]                   "

#elif   (NET_OS_CFG_IF_TX_DEALLOC_TASK_PRIO < 0)
#error  "NET_OS_CFG_IF_TX_DEALLOC_TASK_PRIO      illegally #define'd in 'app_cfg.h'"
#error  "                                        [MUST be  >= 0]                   "
#endif


#ifndef  NET_OS_CFG_TMR_TASK_PRIO
#error  "NET_OS_CFG_TMR_TASK_PRIO                      not #define'd in 'app_cfg.h'"
#error  "                                        [MUST be  >= 0]                   "

#elif   (NET_OS_CFG_TMR_TASK_PRIO < 0)
#error  "NET_OS_CFG_TMR_TASK_PRIO                illegally #define'd in 'app_cfg.h'"
#error  "                                        [MUST be  >= 0]                   "
#endif




#ifndef  NET_OS_CFG_IF_RX_TASK_STK_SIZE
#error  "NET_OS_CFG_IF_RX_TASK_STK_SIZE                not #define'd in 'app_cfg.h'"
#error  "                                        [MUST be  > 0]                    "

#elif   (NET_OS_CFG_IF_RX_TASK_STK_SIZE < 1)
#error  "NET_OS_CFG_IF_RX_TASK_STK_SIZE          illegally #define'd in 'app_cfg.h'"
#error  "                                        [MUST be  > 0]                    "
#endif


#ifndef  NET_OS_CFG_IF_TX_DEALLOC_TASK_STK_SIZE
#error  "NET_OS_CFG_IF_TX_DEALLOC_TASK_STK_SIZE        not #define'd in 'app_cfg.h'"
#error  "                                        [MUST be  > 0]                    "

#elif   (NET_OS_CFG_IF_TX_DEALLOC_TASK_STK_SIZE < 1)
#error  "NET_OS_CFG_IF_TX_DEALLOC_TASK_STK_SIZE  illegally #define'd in 'app_cfg.h'"
#error  "                                        [MUST be  > 0]                    "
#endif


#ifndef  NET_OS_CFG_TMR_TASK_STK_SIZE
#error  "NET_OS_CFG_TMR_TASK_STK_SIZE                  not #define'd in 'app_cfg.h'"
#error  "                                        [MUST be  > 0]                    "

#elif   (NET_OS_CFG_TMR_TASK_STK_SIZE < 1)
#error  "NET_OS_CFG_TMR_TASK_STK_SIZE            illegally #define'd in 'app_cfg.h'"
#error  "                                        [MUST be  > 0]                    "
#endif




#ifndef  NET_OS_CFG_IF_RX_Q_SIZE
#error  "NET_OS_CFG_IF_RX_Q_SIZE                       not #define'd in 'app_cfg.h'"
#error  "                                        [MUST be  >= NET_IF_Q_SIZE_MIN]   "
#error  "                                        [     &&  <= NET_IF_Q_SIZE_MAX]   "

#elif   (DEF_CHK_VAL(NET_OS_CFG_IF_RX_Q_SIZE,    \
                     NET_IF_Q_SIZE_MIN,          \
                     NET_IF_Q_SIZE_MAX) != DEF_OK)
#error  "NET_OS_CFG_IF_RX_Q_SIZE                 illegally #define'd in 'app_cfg.h'"
#error  "                                        [MUST be  >= NET_IF_Q_SIZE_MIN]   "
#error  "                                        [     &&  <= NET_IF_Q_SIZE_MAX]   "
#endif


#ifndef  NET_OS_CFG_IF_TX_DEALLOC_Q_SIZE
#error  "NET_OS_CFG_IF_TX_DEALLOC_Q_SIZE               not #define'd in 'app_cfg.h'"
#error  "                                        [MUST be  >= NET_IF_Q_SIZE_MIN]   "
#error  "                                        [     &&  <= NET_IF_Q_SIZE_MAX]   "

#elif   (DEF_CHK_VAL(NET_OS_CFG_IF_TX_DEALLOC_Q_SIZE, \
                     NET_IF_Q_SIZE_MIN,               \
                     NET_IF_Q_SIZE_MAX) != DEF_OK)
#error  "NET_OS_CFG_IF_TX_DEALLOC_Q_SIZE         illegally #define'd in 'app_cfg.h'"
#error  "                                        [MUST be  >= NET_IF_Q_SIZE_MIN]   "
#error  "                                        [     &&  <= NET_IF_Q_SIZE_MAX]   "
#endif

