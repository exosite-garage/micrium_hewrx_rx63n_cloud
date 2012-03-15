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
*                                       NETWORK TIMER MANAGEMENT
*
* Filename      : net_tmr.h
* Version       : V2.11.02
* Programmer(s) : ITJ
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/

#if ((defined(NET_TMR_MODULE)) && \
     (defined(NET_GLOBALS_EXT)))
#define  NET_TMR_EXT
#else
#define  NET_TMR_EXT  extern
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                     NETWORK TIMER FLAG DEFINES
*********************************************************************************************************
*/

                                                                /* ------------------ NET TMR FLAGS ------------------- */
#define  NET_TMR_FLAG_NONE                        DEF_BIT_NONE
#define  NET_TMR_FLAG_USED                        DEF_BIT_00    /* Tmr cur used; i.e. NOT in free tmr pool.             */


/*
*********************************************************************************************************
*                                   NETWORK TIMER TASK TIME DEFINES
*
* Note(s) : (1) Time constants based on NET_TMR_CFG_TASK_FREQ, NetTmr_TaskHandler()'s frequency [i.e. how 
*               often NetTmr_TaskHandler() is scheduled to run per second as implemented in NetOS_Tmr_Task()].  
*
*           (2) NET_TMR_CFG_TASK_FREQ  MUST NOT be configured as a floating-point frequency.
*********************************************************************************************************
*/

#define  NET_TMR_TIME_0S                                   0
#define  NET_TMR_TIME_1S                                  (1  *  NET_TMR_CFG_TASK_FREQ)

#define  NET_TMR_TIME_TICK                                 1
#define  NET_TMR_TIME_TICK_PER_SEC                       NET_TMR_TIME_1S



#define  NET_TMR_TASK_PERIOD_SEC                                 NET_TMR_CFG_TASK_FREQ
#define  NET_TMR_TASK_PERIOD_mS     (DEF_TIME_NBR_mS_PER_SEC  /  NET_TMR_CFG_TASK_FREQ)
#define  NET_TMR_TASK_PERIOD_uS     (DEF_TIME_NBR_uS_PER_SEC  /  NET_TMR_CFG_TASK_FREQ)
#define  NET_TMR_TASK_PERIOD_nS     (DEF_TIME_NBR_nS_PER_SEC  /  NET_TMR_CFG_TASK_FREQ)


/*
*********************************************************************************************************
*                                     NETWORK TIMER TYPE DEFINES
*
* Note(s) : (1) NET_TMR_TYPE_&&& #define values specifically chosen as ASCII representations of the 
*               network timer types.  Memory displays of network timers will display the timer TYPEs 
*               with their chosen ASCII name.
*********************************************************************************************************
*/

#define  NET_TMR_TYPE_NONE                        CPU_TYPE_CREATE('N', 'O', 'N', 'E')
#define  NET_TMR_TYPE_TMR                         CPU_TYPE_CREATE('T', 'M', 'R', ' ')


/*$PAGE*/
/*
*********************************************************************************************************
*                                             DATA TYPES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                  NETWORK TIMER QUANTITY DATA TYPE
*
* Note(s) : (1) NET_TMR_NBR_MAX  SHOULD be #define'd based on 'NET_TMR_QTY' data type declared.
*********************************************************************************************************
*/

typedef  CPU_INT16U  NET_TMR_QTY;                               /* Defines max qty of net tmrs to support.              */

#define  NET_TMR_NBR_MIN                                  1
#define  NET_TMR_NBR_MAX                DEF_INT_16U_MAX_VAL     /* See Note #1.                                         */


/*
*********************************************************************************************************
*                                    NETWORK TIMER TICK DATA TYPE
*
* Note(s) : (1) 'NET_TMR_TIME_INFINITE_TICK' & 'NET_TMR_TIME_INFINITE'  MUST be globally #define'd AFTER
*               'NET_TMR_TICK' data type declared.
*********************************************************************************************************
*/

typedef  CPU_INT32U    NET_TMR_TICK;

#define  NET_TMR_TIME_INFINITE_TICK     DEF_INT_32U_MAX_VAL     /* Define as max unsigned val (see Note #1).            */
#define  NET_TMR_TIME_INFINITE          NET_TMR_TIME_INFINITE_TICK


/*$PAGE*/
/*
*********************************************************************************************************
*                                       NETWORK TIMER DATA TYPE
*
*                                    NET_TMR
*                                |-------------|
*                                | Timer Type  |
*                     Previous   |-------------|
*                      Timer <----------O      |
*                                |-------------|     Next
*                                |      O----------> Timer
*                                |-------------|                    ------------- 
*                                |      O-------------------------> |           |
*                                |-------------|       Object       |  Object   |
*                                |      O----------> Expiration     |   that    |
*                                |-------------|      Function      | requested |
*                                |   Current   |                    |   Timer   |
*                                | Timer value |                    |           |
*                                |-------------|                    -------------
*                                |    Flags    |
*                                |-------------|
*
*
* Note(s) : (1) Forced (32-bit) word-alignment at start of network timer NOT required since first data 
*               member 'Type' is is declared as 'NET_TYPE', equivalent to 'CPU_INT32U'.
*********************************************************************************************************
*/

                                                                /* --------------------- NET TMR ---------------------- */
typedef  struct  net_tmr  NET_TMR;

struct  net_tmr {
    NET_TYPE        Type;                                       /* Type cfg'd @ init : NET_TMR_TYPE_TMR.                */

    NET_TMR        *PrevPtr;                                    /* Ptr to PREV tmr.                                     */
    NET_TMR        *NextPtr;                                    /* Ptr to NEXT tmr.                                     */

    void           *Obj;                                        /* Ptr to obj  using TMR.                               */
    CPU_FNCT_PTR    Fnct;                                       /* Ptr to fnct used on obj when TMR expires.            */

    NET_TMR_TICK    TmrVal;                                     /* Cur tmr val (in NET_TMR_TICK ticks).                 */

    NET_TMR_QTY     ID;                                         /* Tmr id.                                              */
    CPU_INT16U      Flags;                                      /* Tmr flags.                                           */
};


/*$PAGE*/
/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/

NET_TMR_EXT  NET_TMR         NetTmr_Tbl[NET_TMR_CFG_NBR_TMR];
NET_TMR_EXT  NET_TMR        *NetTmr_PoolPtr;                    /* Ptr to pool of free net tmrs.                        */
NET_TMR_EXT  NET_STAT_POOL   NetTmr_PoolStat;

NET_TMR_EXT  NET_TMR        *NetTmr_TaskListHead;               /* Ptr to head of Tmr Task List.                        */
NET_TMR_EXT  NET_TMR        *NetTmr_TaskListPtr;                /* Ptr to cur     Tmr Task List tmr to update.          */


/*$PAGE*/
/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void            NetTmr_Init                (NET_ERR       *perr);

void            NetTmr_TaskHandler         (void);


                                                                        /* ----------- TMR ALLOCATION FNCTS ----------- */
NET_TMR        *NetTmr_Get                 (CPU_FNCT_PTR   fnct,
                                            void          *obj,
                                            NET_TMR_TICK   time,
                                            CPU_INT16U     flags,
                                            NET_ERR       *perr);

void            NetTmr_Free                (NET_TMR       *ptmr);


                                                                        /* -------------- TMR API FNCTS --------------- */
void            NetTmr_Set                 (NET_TMR       *ptmr,
                                            CPU_FNCT_PTR   fnct,
                                            NET_TMR_TICK   time,
                                            NET_ERR       *perr);


                                                                        /* ------------- TMR STATUS FNCTS ------------ */
NET_STAT_POOL   NetTmr_PoolStatGet         (void);

void            NetTmr_PoolStatResetMaxUsed(void);


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*                                      DEFINED IN OS'S  net_os.c
*********************************************************************************************************
*/

void            NetOS_Tmr_Init             (NET_ERR       *perr);       /* Create & start Tmr Task.                     */


/*$PAGE*/
/*
*********************************************************************************************************
*                                        CONFIGURATION ERRORS
*********************************************************************************************************
*/

#ifndef  NET_TMR_CFG_NBR_TMR
#error  "NET_TMR_CFG_NBR_TMR          not #define'd in 'net_cfg.h'"
#error  "                       [MUST be  >= NET_TMR_NBR_MIN]     "
#error  "                       [     &&  <= NET_TMR_NBR_MAX]     "

#elif   (DEF_CHK_VAL(NET_TMR_CFG_NBR_TMR,      \
                     NET_TMR_NBR_MIN,          \
                     NET_TMR_NBR_MAX) != DEF_OK)
#error  "NET_TMR_CFG_NBR_TMR    illegally #define'd in 'net_cfg.h'"
#error  "                       [MUST be  >= NET_TMR_NBR_MIN]     "
#error  "                       [     &&  <= NET_TMR_NBR_MAX]     "
#endif




#ifndef  NET_TMR_CFG_TASK_FREQ
#error  "NET_TMR_CFG_TASK_FREQ        not #define'd in 'net_cfg.h'"
#error  "                       [MUST be  > 0 Hz]                 "

#elif   (DEF_CHK_VAL_MIN(NET_TMR_CFG_TASK_FREQ, 1) != DEF_OK)
#error  "NET_TMR_CFG_TASK_FREQ  illegally #define'd in 'net_cfg.h'"
#error  "                       [MUST be  > 0 Hz]                 "
#endif

