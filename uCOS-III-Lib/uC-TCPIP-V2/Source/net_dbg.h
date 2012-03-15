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
*                                       NETWORK DEBUG MANAGEMENT
*
* Filename      : net_dbg.h
* Version       : V2.11.02
* Programmer(s) : ITJ
*                 SR
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/

#if ((defined(NET_DBG_MODULE)) && \
     (defined(NET_GLOBALS_EXT)))
#define  NET_DBG_EXT
#else
#define  NET_DBG_EXT  extern
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/

#if (NET_DBG_CFG_TEST_EN == DEF_ENABLED)
#define  NET_LOCAL
#else
#define  NET_LOCAL  static
#endif


/*
*********************************************************************************************************
*                                NETWORK DEBUG MONITOR STATUS DEFINES
*********************************************************************************************************
*/

#define  NET_DBG_RSRC_TH_LO_MIN_PCT                        5    /* Rsrc lo th   min  pct =  5%                          */
#define  NET_DBG_RSRC_TH_LO_MAX_PCT                       50    /* Rsrc lo th   max  pct = 50%                          */
#define  NET_DBG_RSRC_TH_LO_DFLT_PCT                       5    /* Rsrc lo th   dflt pct =  5%                          */

#define  NET_DBG_RSRC_TH_LO_HYST_MIN_PCT                   0    /* Rsrc lo hyst min  pct =  0%                          */
#define  NET_DBG_RSRC_TH_LO_HYST_MAX_PCT                  15    /* Rsrc lo hyst max  pct = 15%                          */
#define  NET_DBG_RSRC_TH_LO_HYST_DFLT_PCT                  3    /* Rsrc lo hyst dflt pct =  3%                          */


#define  NET_DBG_MON_TASK_TIME_MIN_SEC           ( 1                             )  /* Mon task time min  =   1 second  */
#define  NET_DBG_MON_TASK_TIME_MAX_SEC           (10  *  DEF_TIME_NBR_SEC_PER_MIN)  /* Mon task time max  = 600 seconds */
#define  NET_DBG_MON_TASK_TIME_DFLT_SEC          ( 1  *  DEF_TIME_NBR_SEC_PER_MIN)  /* Mon task time dflt =  60 seconds */


/*$PAGE*/
/*
*********************************************************************************************************
*                                    NETWORK DEBUG STATUS DEFINES
*
* Note(s) : (1) Network debug status codes currently #define'd for a maximum range of 32-bits.
*
*               See also 'NETWORK DEBUG STATUS DATA TYPE  Note #1'.
*
*           (2) 'STATUS_FAULT' abbreviated to 'SF' for some network debug status fault codes to enforce
*                ANSI-compliance of 31-character symbol length uniqueness.
*
*               (a) 'STATUS_FAULT' NOT abbreviated for overall  summary  network debug status fault codes.
*
*               (b) 'STATUS_FAULT'     abbreviated for specific modules' network debug status fault codes.
*
*           (3) 'NET_DBG_STATUS_FAULT_LOCK'/'NET_DBG_STATUS_FAULT_INIT' assigned to highest-order status 
*                code bits (see Note #1).
*
*               (a) Specific modules' network debug status fault codes MUST reserve the highest-order 
*                   status code bit(s) for certain 'STATUS_FAULT_LOCK' fault code(s).
*********************************************************************************************************
*/

#define  NET_DBG_STATUS_NONE                              DEF_BIT_NONE

#define  NET_DBG_STATUS_OK                                NET_DBG_STATUS_NONE

                                                                        /* See Note #2a.                                */
#define  NET_DBG_STATUS_FAULT                             DEF_BIT_00
#define  NET_DBG_STATUS_FAULT_LOCK                        DEF_BIT_30    /* Net lock NOT acquired (see Note #3).         */
#define  NET_DBG_STATUS_FAULT_INIT                        DEF_BIT_31    /* Net init NOT complete (see Note #3).         */


#define  NET_DBG_STATUS_FAULT_RSRC_LOST                   DEF_BIT_01    /* Net rsrc(s) lost.                            */
#define  NET_DBG_STATUS_FAULT_RSRC_LO                     DEF_BIT_02    /* Net rsrc(s) lo.                              */

#define  NET_DBG_STATUS_FAULT_BUF                         DEF_BIT_04    /* Net  buf   fault(s).                         */
#define  NET_DBG_STATUS_FAULT_TMR                         DEF_BIT_05    /* Net  tmr   fault(s).                         */
#define  NET_DBG_STATUS_FAULT_CONN                        DEF_BIT_06    /* Net  conn  fault(s).                         */
#define  NET_DBG_STATUS_FAULT_STAT                        DEF_BIT_07    /* Net  stat  fault(s).                         */

#define  NET_DBG_STATUS_FAULT_DEV                         DEF_BIT_08    /* Dev  layer fault(s).                         */
#define  NET_DBG_STATUS_FAULT_IF                          DEF_BIT_09    /* IF   layer fault(s).                         */
#define  NET_DBG_STATUS_FAULT_ARP                         DEF_BIT_10    /* ARP  layer fault(s).                         */
#define  NET_DBG_STATUS_FAULT_IP                          DEF_BIT_11    /* IP   layer fault(s).                         */
#define  NET_DBG_STATUS_FAULT_ICMP                        DEF_BIT_12    /* ICMP layer fault(s).                         */
#define  NET_DBG_STATUS_FAULT_UDP                         DEF_BIT_13    /* UDP  layer fault(s).                         */
#define  NET_DBG_STATUS_FAULT_TCP                         DEF_BIT_14    /* TCP  layer fault(s).                         */
#define  NET_DBG_STATUS_FAULT_SOCK                        DEF_BIT_15    /* Sock layer fault(s).                         */
#define  NET_DBG_STATUS_FAULT_APP                         DEF_BIT_16    /* App  layer fault(s).                         */


                                                                        /* See Note #2b.                                */
#define  NET_DBG_SF                                       NET_DBG_STATUS_FAULT
#define  NET_DBG_SF_LOCK                                  NET_DBG_STATUS_FAULT_LOCK
#define  NET_DBG_SF_INIT                                  NET_DBG_STATUS_FAULT_INIT


#define  NET_DBG_SF_RSRC_LOST                             DEF_BIT_00    /* Net              rsrc(s) lost.               */
#define  NET_DBG_SF_RSRC_LOST_BUF                         DEF_BIT_01    /* Net buf          rsrc(s) lost.               */
#define  NET_DBG_SF_RSRC_LOST_BUF_RX_LARGE                DEF_BIT_02    /* Net buf large rx rsrc(s) lost.               */
#define  NET_DBG_SF_RSRC_LOST_BUF_TX_LARGE                DEF_BIT_03    /* Net buf large tx rsrc(s) lost.               */
#define  NET_DBG_SF_RSRC_LOST_BUF_TX_SMALL                DEF_BIT_04    /* Net buf small tx rsrc(s) lost.               */
#define  NET_DBG_SF_RSRC_LOST_TMR                         DEF_BIT_05    /* Net tmr          rsrc(s) lost.               */
#define  NET_DBG_SF_RSRC_LOST_CONN                        DEF_BIT_06    /* Net conn         rsrc(s) lost.               */
#define  NET_DBG_SF_RSRC_LOST_ARP_CACHE                   DEF_BIT_08    /* ARP cache        rsrc(s) lost.               */
#define  NET_DBG_SF_RSRC_LOST_TCP_CONN                    DEF_BIT_10    /* TCP conn         rsrc(s) lost.               */
#define  NET_DBG_SF_RSRC_LOST_SOCK                        DEF_BIT_11    /* Sock             rsrc(s) lost.               */
#define  NET_DBG_SF_RSRC_LOST_RESERVED                    NET_DBG_SF_LOCK   /* Reserved; MUST NOT use (see Note #3a).   */


#define  NET_DBG_SF_RSRC_LO                               DEF_BIT_00    /* Net              rsrc(s) lo.                 */
#define  NET_DBG_SF_RSRC_LO_BUF                           DEF_BIT_01    /* Net buf          rsrc(s) lo.                 */
#define  NET_DBG_SF_RSRC_LO_BUF_RX_LARGE                  DEF_BIT_02    /* Net buf large rx rsrc(s) lo.                 */
#define  NET_DBG_SF_RSRC_LO_BUF_TX_LARGE                  DEF_BIT_03    /* Net buf large tx rsrc(s) lo.                 */
#define  NET_DBG_SF_RSRC_LO_BUF_TX_SMALL                  DEF_BIT_04    /* Net buf small tx rsrc(s) lo.                 */
#define  NET_DBG_SF_RSRC_LO_TMR                           DEF_BIT_05    /* Net tmr          rsrc(s) lo.                 */
#define  NET_DBG_SF_RSRC_LO_CONN                          DEF_BIT_06    /* Net conn         rsrc(s) lo.                 */
#define  NET_DBG_SF_RSRC_LO_ARP_CACHE                     DEF_BIT_08    /* ARP cache        rsrc(s) lo.                 */
#define  NET_DBG_SF_RSRC_LO_TCP_CONN                      DEF_BIT_10    /* TCP conn         rsrc(s) lo.                 */
#define  NET_DBG_SF_RSRC_LO_SOCK                          DEF_BIT_11    /* Sock             rsrc(s) lo.                 */
#define  NET_DBG_SF_RSRC_LO_RESERVED                      NET_DBG_SF_LOCK   /* Reserved; MUST NOT use (see Note #3a).   */


/*$PAGE*/
#define  NET_DBG_SF_BUF                                   DEF_BIT_00    /* Net buf fault(s).                            */
#define  NET_DBG_SF_BUF_TYPE                              DEF_BIT_01    /* Net buf invalid type.                        */
#define  NET_DBG_SF_BUF_ID                                DEF_BIT_02    /* Net buf invalid ID.                          */
#define  NET_DBG_SF_BUF_LINK_TYPE                         DEF_BIT_03    /* Net buf invalid link type.                   */
#define  NET_DBG_SF_BUF_LINK_UNUSED                       DEF_BIT_04    /* Net buf         link unused.                 */
#define  NET_DBG_SF_BUF_LINK_BACK_TO_BUF                  DEF_BIT_05    /* Net buf invalid link     back to buf.        */
#define  NET_DBG_SF_BUF_LINK_NOT_TO_BUF                   DEF_BIT_06    /* Net buf invalid link NOT back to buf.        */
#define  NET_DBG_SF_BUF_LINK_TO_BUF                       DEF_BIT_07    /* Net buf invalid link          to buf.        */
#define  NET_DBG_SF_BUF_POOL_TYPE                         DEF_BIT_08    /* Net buf invalid pool type.                   */
#define  NET_DBG_SF_BUF_POOL_ID                           DEF_BIT_09    /* Net buf invalid pool id.                     */
#define  NET_DBG_SF_BUF_POOL_DUP                          DEF_BIT_10    /* Net buf invalid pool dup     buf.            */
#define  NET_DBG_SF_BUF_POOL_NBR_MAX                      DEF_BIT_11    /* Net buf invalid pool max nbr buf.            */
#define  NET_DBG_SF_BUF_USED_IN_POOL                      DEF_BIT_12    /* Net buf   used     in pool.                  */
#define  NET_DBG_SF_BUF_UNUSED_NOT_IN_POOL                DEF_BIT_13    /* Net buf unused NOT in pool.                  */
#define  NET_DBG_SF_BUF_RESERVED                          NET_DBG_SF_LOCK   /* Reserved; MUST NOT use (see Note #3a).   */


#define  NET_DBG_SF_TMR                                   DEF_BIT_00    /* Net tmr fault(s).                            */
#define  NET_DBG_SF_TMR_TYPE                              DEF_BIT_01    /* Net tmr invalid type.                        */
#define  NET_DBG_SF_TMR_ID                                DEF_BIT_02    /* Net tmr invalid ID.                          */
#define  NET_DBG_SF_TMR_LINK_TYPE                         DEF_BIT_03    /* Net tmr invalid link type.                   */
#define  NET_DBG_SF_TMR_LINK_UNUSED                       DEF_BIT_04    /* Net tmr         link unused.                 */
#define  NET_DBG_SF_TMR_LINK_BACK_TO_TMR                  DEF_BIT_05    /* Net tmr invalid link     back to tmr.        */
#define  NET_DBG_SF_TMR_LINK_TO_TMR                       DEF_BIT_06    /* Net tmr invalid link          to tmr.        */
#define  NET_DBG_SF_TMR_POOL_TYPE                         DEF_BIT_07    /* Net tmr invalid pool type.                   */
#define  NET_DBG_SF_TMR_POOL_ID                           DEF_BIT_08    /* Net tmr invalid pool id.                     */
#define  NET_DBG_SF_TMR_POOL_DUP                          DEF_BIT_09    /* Net tmr invalid pool dup     tmr.            */
#define  NET_DBG_SF_TMR_POOL_NBR_MAX                      DEF_BIT_10    /* Net tmr invalid pool max nbr tmr.            */
#define  NET_DBG_SF_TMR_LIST_TYPE                         DEF_BIT_11    /* Net tmr invalid list type.                   */
#define  NET_DBG_SF_TMR_LIST_ID                           DEF_BIT_12    /* Net tmr invalid list id.                     */
#define  NET_DBG_SF_TMR_LIST_DUP                          DEF_BIT_13    /* Net tmr invalid list dup      tmr.           */
#define  NET_DBG_SF_TMR_LIST_NBR_MAX                      DEF_BIT_14    /* Net tmr invalid list max  nbr tmr.           */
#define  NET_DBG_SF_TMR_LIST_NBR_USED                     DEF_BIT_15    /* Net tmr invalid list used nbr tmr.           */
#define  NET_DBG_SF_TMR_USED_IN_POOL                      DEF_BIT_16    /* Net tmr   used     in pool.                  */
#define  NET_DBG_SF_TMR_UNUSED_NOT_IN_POOL                DEF_BIT_17    /* Net tmr unused NOT in pool.                  */
#define  NET_DBG_SF_TMR_UNUSED_IN_LIST                    DEF_BIT_18    /* Net tmr unused     in list.                  */
#define  NET_DBG_SF_TMR_RESERVED                          NET_DBG_SF_LOCK   /* Reserved; MUST NOT use (see Note #3a).   */


/*$PAGE*/
#define  NET_DBG_SF_CONN                                  DEF_BIT_00    /* Net conn fault(s).                           */
#define  NET_DBG_SF_CONN_TYPE                             DEF_BIT_01    /* Net conn invalid type.                       */
#define  NET_DBG_SF_CONN_FAMILY                           DEF_BIT_02    /* Net conn invalid family.                     */
#define  NET_DBG_SF_CONN_PROTOCOL_IX_NBR_MAX              DEF_BIT_03    /* Net conn invalid protocol ix nbr.            */
#define  NET_DBG_SF_CONN_ID                               DEF_BIT_04    /* Net conn invalid ID.                         */
#define  NET_DBG_SF_CONN_ID_NONE                          DEF_BIT_05    /* Net conn         ID none.                    */
#define  NET_DBG_SF_CONN_ID_UNUSED                        DEF_BIT_06    /* Net conn         ID unused.                  */
#define  NET_DBG_SF_CONN_LINK_TYPE                        DEF_BIT_07    /* Net conn invalid link type.                  */
#define  NET_DBG_SF_CONN_LINK_UNUSED                      DEF_BIT_08    /* Net conn         link unused.                */
#define  NET_DBG_SF_CONN_LINK_BACK_TO_CONN                DEF_BIT_09    /* Net conn invalid link     back to conn.      */
#define  NET_DBG_SF_CONN_LINK_NOT_TO_CONN                 DEF_BIT_10    /* Net conn invalid link NOT back to conn.      */
#define  NET_DBG_SF_CONN_LINK_TO_CONN                     DEF_BIT_11    /* Net conn invalid link          to conn.      */
#define  NET_DBG_SF_CONN_LINK_NOT_IN_LIST                 DEF_BIT_12    /* Net conn         link NOT      in conn list. */
#define  NET_DBG_SF_CONN_POOL_TYPE                        DEF_BIT_13    /* Net conn invalid pool type.                  */
#define  NET_DBG_SF_CONN_POOL_ID                          DEF_BIT_14    /* Net conn invalid pool id.                    */
#define  NET_DBG_SF_CONN_POOL_DUP                         DEF_BIT_15    /* Net conn invalid pool dup     conn.          */
#define  NET_DBG_SF_CONN_POOL_NBR_MAX                     DEF_BIT_16    /* Net conn invalid pool max nbr conn.          */
#define  NET_DBG_SF_CONN_LIST_TYPE                        DEF_BIT_17    /* Net conn invalid list type.                  */
#define  NET_DBG_SF_CONN_LIST_ID                          DEF_BIT_18    /* Net conn invalid list id.                    */
#define  NET_DBG_SF_CONN_LIST_DUP                         DEF_BIT_19    /* Net conn invalid list dup      conn.         */
#define  NET_DBG_SF_CONN_LIST_NBR_MAX                     DEF_BIT_20    /* Net conn invalid list max  nbr conn.         */
#define  NET_DBG_SF_CONN_LIST_NBR_USED                    DEF_BIT_21    /* Net conn invalid list used nbr conn.         */
#define  NET_DBG_SF_CONN_LIST_NBR_NOT_SOLITARY            DEF_BIT_22    /* Net conn invalid list NOT solitary conn.     */
#define  NET_DBG_SF_CONN_USED_IN_POOL                     DEF_BIT_23    /* Net conn   used     in pool.                 */
#define  NET_DBG_SF_CONN_USED_NOT_IN_LIST                 DEF_BIT_24    /* Net conn   used NOT in list.                 */
#define  NET_DBG_SF_CONN_UNUSED_IN_LIST                   DEF_BIT_25    /* Net conn unused     in list.                 */
#define  NET_DBG_SF_CONN_UNUSED_NOT_IN_POOL               DEF_BIT_26    /* Net conn unused NOT in pool.                 */
#define  NET_DBG_SF_CONN_IN_LIST_IN_POOL                  DEF_BIT_27    /* Net conn     in list &     in pool.          */
#define  NET_DBG_SF_CONN_NOT_IN_LIST_NOT_IN_POOL          DEF_BIT_28    /* Net conn NOT in list & NOT in pool.          */
#define  NET_DBG_SF_CONN_RESERVED                         NET_DBG_SF_LOCK   /* Reserved; MUST NOT use (see Note #3a).   */


#define  NET_DBG_SF_TCP                                   DEF_BIT_00    /* TCP layer fault(s).                          */
#define  NET_DBG_SF_TCP_CONN_TYPE                         DEF_BIT_01    /* TCP conn invalid type.                       */
#define  NET_DBG_SF_TCP_CONN_ID                           DEF_BIT_02    /* TCP conn invalid ID.                         */
#define  NET_DBG_SF_TCP_CONN_LINK_TYPE                    DEF_BIT_03    /* TCP conn invalid link type.                  */
#define  NET_DBG_SF_TCP_CONN_LINK_UNUSED                  DEF_BIT_04    /* TCP conn         link unused.                */
#define  NET_DBG_SF_TCP_CONN_LINK_BACK_TO_CONN            DEF_BIT_05    /* TCP conn invalid link     back to conn.      */
#define  NET_DBG_SF_TCP_CONN_LINK_NOT_TO_CONN             DEF_BIT_06    /* TCP conn invalid link NOT back to conn.      */
#define  NET_DBG_SF_TCP_CONN_LINK_TO_CONN                 DEF_BIT_07    /* TCP conn invalid link          to conn.      */
#define  NET_DBG_SF_TCP_CONN_POOL_TYPE                    DEF_BIT_08    /* TCP conn invalid pool type.                  */
#define  NET_DBG_SF_TCP_CONN_POOL_ID                      DEF_BIT_09    /* TCP conn invalid pool id.                    */
#define  NET_DBG_SF_TCP_CONN_POOL_DUP                     DEF_BIT_10    /* TCP conn invalid pool dup     conn.          */
#define  NET_DBG_SF_TCP_CONN_POOL_NBR_MAX                 DEF_BIT_11    /* TCP conn invalid pool max nbr conn.          */
#define  NET_DBG_SF_TCP_CONN_USED_IN_POOL                 DEF_BIT_12    /* TCP conn   used     in pool.                 */
#define  NET_DBG_SF_TCP_CONN_UNUSED_NOT_IN_POOL           DEF_BIT_13    /* TCP conn unused NOT in pool.                 */
#define  NET_DBG_SF_TCP_CONN_Q                            DEF_BIT_16    /* TCP conn Q fault(s).                         */
#define  NET_DBG_SF_TCP_CONN_Q_BUF_TYPE                   DEF_BIT_17    /* TCP conn Q invalid buf      type.            */
#define  NET_DBG_SF_TCP_CONN_Q_BUF_UNUSED                 DEF_BIT_18    /* TCP conn Q         buf      unused.          */
#define  NET_DBG_SF_TCP_CONN_Q_BUF_DUP                    DEF_BIT_19    /* TCP conn Q invalid buf      dup.             */
#define  NET_DBG_SF_TCP_CONN_Q_LINK_TYPE                  DEF_BIT_20    /* TCP conn Q invalid buf link type.            */
#define  NET_DBG_SF_TCP_CONN_Q_LINK_UNUSED                DEF_BIT_21    /* TCP conn Q         buf link unused.          */
#define  NET_DBG_SF_TCP_RESERVED                          NET_DBG_SF_LOCK   /* Reserved; MUST NOT use (see Note #3a).   */


/*$PAGE*/
/*
*********************************************************************************************************
*                                             DATA TYPES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                   NETWORK DEBUG STATUS DATA TYPE
*
* Note(s) : (1) 'NET_DBG_STATUS' data type MUST be defined with an appropriate-sized CPU data type large
*               enough to handle the maximum range & resolution of ALL network debug status codes.
*
*               See also 'NETWORK DEBUG STATUS DEFINES  Note #1'.
*********************************************************************************************************
*/

typedef  CPU_INT32U         NET_DBG_STATUS;                         /* See Note #1.                                     */


/*
*********************************************************************************************************
*                              NETWORK DEBUG RESOURCE QUANTITY DATA TYPE
*********************************************************************************************************
*/

typedef  NET_STAT_POOL_QTY  NET_DBG_RSRC_QTY;


/*$PAGE*/
/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/

#if (NET_DBG_CFG_STATUS_RSRC_LO_EN == DEF_ENABLED)                  /* ----------- DBG LO RSRC's VARIABLES ------------ */
                                                                    /* Pct of          bufs used to trip lo rsrc's.     */
                                                                    /* Pct of          bufs used to clr  lo rsrc's.     */
NET_DBG_EXT  CPU_INT08U       NetDbg_RsrcBufThLo_pct[NET_IF_NBR_IF_TOT];
NET_DBG_EXT  CPU_INT08U       NetDbg_RsrcBufThLoHyst_pct[NET_IF_NBR_IF_TOT];
                                                                    /* Pct of large rx bufs used to trip lo rsrc's.     */
                                                                    /* Pct of large rx bufs used to clr  lo rsrc's.     */
NET_DBG_EXT  CPU_INT08U       NetDbg_RsrcBufRxLargeThLo_pct[NET_IF_NBR_IF_TOT];
NET_DBG_EXT  CPU_INT08U       NetDbg_RsrcBufRxLargeThLoHyst_pct[NET_IF_NBR_IF_TOT];
                                                                    /* Pct of large tx bufs used to trip lo rsrc's.     */
                                                                    /* Pct of large tx bufs used to clr  lo rsrc's.     */
NET_DBG_EXT  CPU_INT08U       NetDbg_RsrcBufTxLargeThLo_pct[NET_IF_NBR_IF_TOT];
NET_DBG_EXT  CPU_INT08U       NetDbg_RsrcBufTxLargeThLoHyst_pct[NET_IF_NBR_IF_TOT];
                                                                    /* Pct of small tx bufs used to trip lo rsrc's.     */
                                                                    /* Pct of small tx bufs used to clr  lo rsrc's.     */
NET_DBG_EXT  CPU_INT08U       NetDbg_RsrcBufTxSmallThLo_pct[NET_IF_NBR_IF_TOT];
NET_DBG_EXT  CPU_INT08U       NetDbg_RsrcBufTxSmallThLoHyst_pct[NET_IF_NBR_IF_TOT];



NET_DBG_EXT  CPU_INT08U       NetDbg_RsrcTmrThLo_pct;               /* Pct of net tmrs      used to trip lo rsrc's.     */
NET_DBG_EXT  CPU_INT08U       NetDbg_RsrcTmrThLoHyst_pct;           /* Pct of net tmrs      used to clr  lo rsrc's.     */

#ifdef  NET_CONN_MODULE_PRESENT
NET_DBG_EXT  CPU_INT08U       NetDbg_RsrcConnThLo_pct;              /* Pct of net conns     used to trip lo rsrc's.     */
NET_DBG_EXT  CPU_INT08U       NetDbg_RsrcConnThLoHyst_pct;          /* Pct of net conns     used to clr  lo rsrc's.     */
#endif

#ifdef  NET_ARP_MODULE_PRESENT
NET_DBG_EXT  CPU_INT08U       NetDbg_RsrcARP_CacheThLo_pct;         /* Pct of ARP cache     used to trip lo rsrc's.     */
NET_DBG_EXT  CPU_INT08U       NetDbg_RsrcARP_CacheThLoHyst_pct;     /* Pct of ARP cache     used to clr  lo rsrc's.     */
#endif

#ifdef  NET_TCP_MODULE_PRESENT
NET_DBG_EXT  CPU_INT08U       NetDbg_RsrcTCP_ConnThLo_pct;          /* Pct of TCP conns     used to trip lo rsrc's.     */
NET_DBG_EXT  CPU_INT08U       NetDbg_RsrcTCP_ConnThLoHyst_pct;      /* Pct of TCP conns     used to clr  lo rsrc's.     */
#endif

#ifdef  NET_SOCK_MODULE_PRESENT
NET_DBG_EXT  CPU_INT08U       NetDbg_RsrcSockThLo_pct;              /* Pct of net socks     used to trip lo rsrc's.     */
NET_DBG_EXT  CPU_INT08U       NetDbg_RsrcSockThLoHyst_pct;          /* Pct of net socks     used to clr  lo rsrc's.     */
#endif

#endif


#if (NET_DBG_CFG_MON_TASK_EN == DEF_ENABLED) 
NET_DBG_EXT  NET_TMR         *NetDbg_MonTaskTmr;                    /* Dbg Mon Task tmr.                                */
NET_DBG_EXT  CPU_INT16U       NetDbg_MonTaskTime_sec;               /* Dbg Mon Task timeout (in secs ).                 */
NET_DBG_EXT  NET_TMR_TICK     NetDbg_MonTaskTime_tick;              /* Dbg Mon Task timeout (in ticks).                 */

NET_DBG_EXT  NET_DBG_STATUS   NetDbg_MonTaskStatusRsrcLost;         /* Indicates net rsrc(s) lost status.               */
NET_DBG_EXT  NET_DBG_STATUS   NetDbg_MonTaskStatusRsrcLo;           /* Indicates net rsrc(s) lo   status.               */
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                          GLOBAL NETWORK MODULE DEBUG INFORMATION EXTERNALS
*
* Note(s) : (1) Many data-size constants ideally defined with network data-type sizes; defined as CPU
*               data types because many network data-type sizes NOT defined at time of declaration
*               (see 'net.h  NETWORK INCLUDE FILES').
*********************************************************************************************************
*/

extern  const  CPU_INT16U  Net_Version;


#if    (NET_DBG_CFG_INFO_EN == DEF_ENABLED)

                                                                                /* -------- NET MISC MODULE(S) -------- */
extern  const  CPU_INT08U  Net_CfgInitCfgVals;
extern  const  CPU_INT08U  Net_CfgOptimize;
extern  const  CPU_INT08U  Net_CfgOptimizeAsmEn;
extern  const  CPU_INT08U  Net_CfgBuildLibEn;

                                                                                /* --------- NET DBG  MODULE ---------- */
extern  const  CPU_INT08U  NetDbg_CfgInfoEn;
extern  const  CPU_INT08U  NetDbg_CfgStatusEn;
extern  const  CPU_INT08U  NetDbg_CfgStatusRsrcLostEn;
extern  const  CPU_INT08U  NetDbg_CfgStatusRsrcLoEn;
extern  const  CPU_INT08U  NetDbg_CfgMemClrEn;
extern  const  CPU_INT08U  NetDbg_CfgTestEn;
extern  const  CPU_INT08U  NetDbg_CfgMonTaskEn;

                                                                                /* --------- NET ERR  MODULE ---------- */
extern  const  CPU_INT08U  NetErr_CfgArgChkExtEn;
extern  const  CPU_INT08U  NetErr_CfgArgChkDbgEn;

                                                                                /* --------- NET CTR  MODULE ---------- */
extern  const  CPU_INT08U  NetCtr_CfgStatEn;
extern  const  CPU_INT08U  NetCtr_CfgErrEn;

                                                                                /* --------- NET TMR  MODULE ---------- */
extern  const  CPU_INT16U  NetTmr_CfgNbrTmr;
extern  const  CPU_INT16U  NetTmr_CfgTaskFreq;

                                                                                /* --------- NET BUF  MODULE ---------- */


#ifdef  NET_CONN_MODULE_PRESENT                                                 /* --------- NET CONN MODULE ---------- */
extern  const  CPU_INT16U  NetConn_CfgNbrConn;
#endif


                                                                                /* --------- NET IF   MODULE ---------- */
extern  const  CPU_INT08U  NetIF_CfgMaxNbrIF;
extern  const  CPU_INT08U  NetIF_CfgLoopbackEn;
extern  const  CPU_INT08U  NetIF_CfgEtherEn;

extern  const  CPU_INT08U  NetIF_CfgAddrFltrEn;
extern  const  CPU_INT32U  NetIF_CfgTxSuspendTimeout_ms;


#ifdef  NET_ARP_MODULE_PRESENT                                                  /* --------- NET ARP  MODULE ---------- */
extern  const  CPU_INT16U  NetARP_CfgNbrCache;
extern  const  CPU_INT08U  NetARP_CfgAddrFltrEn;
#endif


                                                                                /* --------- NET IP   MODULE ---------- */
extern  const  CPU_INT08U  NetIP_CfgIF_MaxNbrAddr;
extern  const  CPU_INT08U  NetIP_CfgMulticastSel;

                                                                                /* --------- NET ICMP MODULE ---------- */
extern  const  CPU_INT08U  NetICMP_CfgTxSrcQuenchEn;
#if    (NET_ICMP_CFG_TX_SRC_QUENCH_EN == DEF_ENABLED)
extern  const  CPU_INT16U  NetICMP_CfgTxSrcQuenchNbr;
#endif


#ifdef  NET_IGMP_MODULE_PRESENT                                                 /* --------- NET IGMP MODULE ---------- */
extern  const  CPU_INT16U  NetIGMP_CfgMaxNbrHostGrp;
#endif


/*$PAGE*/
                                                                                /* --------- NET UDP  MODULE ---------- */
extern  const  CPU_INT08U  NetUDP_CfgAppAPI_Sel;
extern  const  CPU_INT08U  NetUDP_CfgRxChkSumDiscardEn;
extern  const  CPU_INT08U  NetUDP_CfgTxChkSumEn;


#ifdef  NET_TCP_MODULE_PRESENT                                                  /* --------- NET TCP  MODULE ---------- */
extern  const  CPU_INT16U  NetTCP_CfgNbrConn;

extern  const  CPU_INT16U  NetTCP_CfgRxWinSize_octet;
extern  const  CPU_INT16U  NetTCP_CfgTxWinSize_octet;

extern  const  CPU_INT32U  NetTCP_CfgTimeoutConnMaxSeg_sec;
extern  const  CPU_INT32U  NetTCP_CfgTimeoutConnAckDly_ms;
extern  const  CPU_INT32U  NetTCP_CfgTimeoutConnRxQ_ms;
extern  const  CPU_INT32U  NetTCP_CfgTimeoutConnTxQ_ms;
#endif


#ifdef  NET_SOCK_MODULE_PRESENT                                                 /* --------- NET SOCK MODULE ---------- */
extern  const  CPU_INT16U  NetSock_CfgNbrSock;

extern  const  CPU_INT08U  NetSock_CfgBlockSel;

extern  const  CPU_INT08U  NetSock_CfgSelEn;
extern  const  CPU_INT08U  NetSock_CfgSelNbrEventsMax;

extern  const  CPU_INT16U  NetSock_CfgRandomPortNbrBase;
extern  const  CPU_INT16U  NetSock_NbrRandomPortNbr;

extern  const  CPU_INT32U  NetSock_CfgTimeoutRxQ_ms;

extern  const  CPU_INT08U  NetSock_CfgStreamTypeEn;
#if    (NET_SOCK_CFG_TYPE_STREAM_EN == DEF_ENABLED)
extern  const  CPU_INT16U  NetSock_CfgConnAcceptQ_MaxSize;
extern  const  CPU_INT32U  NetSock_CfgTimeoutConnReq_ms;
extern  const  CPU_INT32U  NetSock_CfgTimeoutConnAccept_ms;
extern  const  CPU_INT32U  NetSock_CfgTimeoutConnClose_ms;
#endif
#endif



#ifdef  NET_SECURE_MODULE_PRESENT                                               /* -------- NET SECURE MODULE --------- */
extern  const  CPU_INT08U  NetSecure_CfgEn;
extern  const  CPU_INT08U  NetSecure_CfgFS_En;

extern  const  CPU_INT08U  NetSecure_CfgVer;
extern  const  CPU_INT08U  NetSecure_CfgWordSize;

extern  const  CPU_INT08U  NetSecure_CfgClientDowngradeEn;
extern  const  CPU_INT08U  NetSecure_CfgServerDowngradeEn;

extern  const  CPU_INT16U  NetSecure_CfgMaxNbrSock;
extern  const  CPU_INT32U  NetSecure_CfgMaxNbrCA;
extern  const  CPU_INT32U  NetSecure_CfgMaxKeyLen;
extern  const  CPU_INT32U  NetSecure_CfgMaxIssuerCN_Len;
extern  const  CPU_INT32U  NetSecure_CfgMaxPublicKeyLen;
#endif


                                                                                /* --------- NET BSD  MODULE ---------- */
extern  const  CPU_INT08U  NetBSD_API_En;

                                                                                /* --------- NET APP  MODULE ---------- */
extern  const  CPU_INT08U  NetApp_API_En;

#ifdef  NET_APP_MODULE_PRESENT
extern  const  CPU_INT32U  NetApp_TimeDlyMin_sec;
extern  const  CPU_INT32U  NetApp_TimeDlyMax_sec;
extern  const  CPU_INT32U  NetApp_TimeDlyMin_ms;
extern  const  CPU_INT32U  NetApp_TimeDlyMax_ms;
#endif


                                                                                /* --------- NET OS   MODULE ---------- */
extern  const  CPU_INT32U  NetOS_TimeoutMin_tick;
extern  const  CPU_INT32U  NetOS_TimeoutMax_tick;
extern  const  CPU_INT32U  NetOS_TimeoutMin_sec;
extern  const  CPU_INT32U  NetOS_TimeoutMax_sec;
extern  const  CPU_INT32U  NetOS_TimeoutMin_ms;
extern  const  CPU_INT32U  NetOS_TimeoutMax_ms;
extern  const  CPU_INT32U  NetOS_TimeoutMin_us;
extern  const  CPU_INT32U  NetOS_TimeoutMax_us;

extern  const  CPU_INT32U  NetOS_TimeDlyMin_sec;
extern  const  CPU_INT32U  NetOS_TimeDlyMax_sec;
extern  const  CPU_INT32U  NetOS_TimeDlyMin_ms;
extern  const  CPU_INT32U  NetOS_TimeDlyMax_ms;


#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                              GLOBAL NETWORK MODULE DATA SIZE EXTERNALS
*
* Note(s) : (1) Many data-size constants ideally defined with network data-type sizes; defined as 
*               'CPU_INT32U' because many network data-type sizes NOT defined at time of declaration
*               (see 'net.h  NETWORK INCLUDE FILES').
*
*           (2) Network protocol suite total data size does NOT include data sizes from the following 
*               network files :
*
*               (a) Custom Library Files                See 'net.h  NETWORK INCLUDE FILES  Note #3a'
*               (b) BSP      Port  Files                See 'net.h  NETWORK INCLUDE FILES  Note #1a4'
*               (c) CPU      Port  Files                See 'net.h  NETWORK INCLUDE FILES  Note #1c'
*               (d) OS       Port  Files                See 'net.h  NETWORK INCLUDE FILES  Note #1d'
*               (e) IF       Port  Files                See 'net.h  NETWORK INCLUDE FILES  Note #1e'
*               (f) Device   Port  Files                See 'net.h  NETWORK INCLUDE FILES  Note #1f'
*               (g) Security Port  Files                See 'net.h  NETWORK INCLUDE FILES  Note #1g'
*********************************************************************************************************
*/

#if (NET_DBG_CFG_INFO_EN   == DEF_ENABLED)
                                                                                    /* ---------- NET MODULE ---------- */
extern  const  CPU_INT32U  Net_DataSize;

                                                                                    /* ------ NET MISC MODULE(S) ------ */
extern  const  CPU_INT32U  NetTS_Size;


                                                                                    /* ------- NET DBG  MODULE -------- */
extern  const  CPU_INT32U  NetDbg_StatusSize;

extern  const  CPU_INT32U  NetDbg_DataSize;


                                                                                    /* ------- NET ERR  MODULE -------- */
extern  const  CPU_INT32U  NetErr_Size;


                                                                                    /* ------- NET CTR  MODULE -------- */
extern  const  CPU_INT32U  NetCtr_Size;

#if (NET_CTR_CFG_STAT_EN   == DEF_ENABLED)
extern  const  CPU_INT32U  NetCtr_StatCtrsSize;
#endif
#if (NET_CTR_CFG_ERR_EN    == DEF_ENABLED)
extern  const  CPU_INT32U  NetCtr_ErrCtrsSize;
#endif

extern  const  CPU_INT32U  NetCtr_DataSize;


                                                                                    /* ------- NET STAT MODULE -------- */
extern  const  CPU_INT32U  NetStat_PoolSize;

extern  const  CPU_INT32U  NetStat_DataSize;


                                                                                    /* ------- NET TMR  MODULE -------- */
extern  const  CPU_INT32U  NetTmr_TickSize;

extern  const  CPU_INT32U  NetTmr_Size;
extern  const  CPU_INT32U  NetTmr_TblSize;

extern  const  CPU_INT32U  NetTmr_DataSize;


                                                                                    /* ------- NET BUF  MODULE -------- */
extern  const  CPU_INT32U  NetBuf_HdrSize;
extern  const  CPU_INT32U  NetBuf_Size;

extern  const  CPU_INT32U  NetBuf_PoolsSize;
extern  const  CPU_INT32U  NetBuf_PoolsTblSize;

extern  const  CPU_INT32U  NetBuf_DataSize;



#ifdef  NET_CONN_MODULE_PRESENT                                                     /* ------- NET CONN MODULE -------- */
extern  const  CPU_INT32U  NetConn_ID_Size;
extern  const  CPU_INT32U  NetConn_AddrLenSize;

extern  const  CPU_INT32U  NetConn_Size;
extern  const  CPU_INT32U  NetConn_TblSize;

extern  const  CPU_INT32U  NetConn_ConnListTblSize;

extern  const  CPU_INT32U  NetConn_AddrWildCardSize;

extern  const  CPU_INT32U  NetConn_DataSize;
#endif
                     

/*$PAGE*/
                                                                                    /* ------- NET IF   MODULE -------- */
extern  const  CPU_INT32U  NetIF_Size;
extern  const  CPU_INT32U  NetIF_TblSize;

extern  const  CPU_INT32U  NetIF_DataSize;



                                                                                    /* ---- NET IF LOOPBACK MODULE ---- */
extern  const  CPU_INT32U  NetIF_Loopback_DataSize;




#ifdef  NET_ARP_MODULE_PRESENT                                                      /* ------- NET ARP  MODULE -------- */
extern  const  CPU_INT32U  NetARP_HdrSize;

extern  const  CPU_INT32U  NetARP_CacheSize;
extern  const  CPU_INT32U  NetARP_CacheTblSize;

extern  const  CPU_INT32U  NetARP_DataSize;
#endif


                                                                                    /* ------- NET IP   MODULE -------- */
extern  const  CPU_INT32U  NetIP_HdrSize;

extern  const  CPU_INT32U  NetIP_TOS_Size;
extern  const  CPU_INT32U  NetIP_TTL_Size;
extern  const  CPU_INT32U  NetIP_AddrSize;

extern  const  CPU_INT32U  NetIP_OptSize;
extern  const  CPU_INT32U  NetIP_OptSrcRouteSize;
extern  const  CPU_INT32U  NetIP_OptTS_RouteSize;
extern  const  CPU_INT32U  NetIP_OptTS_Size;

extern  const  CPU_INT32U  NetIP_IF_CfgSize;
extern  const  CPU_INT32U  NetIP_IF_CfgTblSize;

extern  const  CPU_INT32U  NetIP_DataSize;


                                                                                    /* ------- NET ICMP MODULE -------- */
extern  const  CPU_INT32U  NetICMP_HdrSize;
extern  const  CPU_INT32U  NetICMP_HdrErrSize;
extern  const  CPU_INT32U  NetICMP_HdrParamProbSize;
extern  const  CPU_INT32U  NetICMP_HdrEchoSize;
extern  const  CPU_INT32U  NetICMP_HdrTS_Size;
extern  const  CPU_INT32U  NetICMP_HdrAddrMaskSize;

#if (NET_ICMP_CFG_TX_SRC_QUENCH_EN == DEF_ENABLED)
extern  const  CPU_INT32U  NetICMP_TxSrcQuenchSize;
extern  const  CPU_INT32U  NetICMP_TxSrcQuenchTblSize;
#endif

extern  const  CPU_INT32U  NetICMP_DataSize;


#ifdef  NET_IGMP_MODULE_PRESENT                                                     /* ------- NET IGMP MODULE -------- */
extern  const  CPU_INT32U  NetIGMP_HostGrpSize;
extern  const  CPU_INT32U  NetIGMP_HostGrpTblSize;
extern  const  CPU_INT32U  NetIGMP_AllHostsJoinedOnIF_TblSize;

extern  const  CPU_INT32U  NetIGMP_DataSize;
#endif


/*$PAGE*/
                                                                                    /* ------- NET UDP  MODULE -------- */
extern  const  CPU_INT32U  NetUDP_HdrSize;
extern  const  CPU_INT32U  NetUDP_PseudoHdrSize;

extern  const  CPU_INT32U  NetUDP_PortNbrSize;

extern  const  CPU_INT32U  NetUDP_DataSize;



#ifdef  NET_TCP_MODULE_PRESENT                                                      /* ------- NET TCP  MODULE -------- */
extern  const  CPU_INT32U  NetTCP_HdrSize;
extern  const  CPU_INT32U  NetTCP_PseudoHdrSize;

extern  const  CPU_INT32U  NetTCP_PortNbrSize;
extern  const  CPU_INT32U  NetTCP_SeqNbrSize;
extern  const  CPU_INT32U  NetTCP_SegLenSize;
extern  const  CPU_INT32U  NetTCP_WinSize;
extern  const  CPU_INT32U  NetTCP_OptSize;

extern  const  CPU_INT32U  NetTCP_ConnID_Size;
extern  const  CPU_INT32U  NetTCP_ConnSize;
extern  const  CPU_INT32U  NetTCP_ConnTblSize;

extern  const  CPU_INT32U  NetTCP_DataSize;
#endif



#ifdef  NET_SOCK_MODULE_PRESENT                                                     /* ------- NET SOCK MODULE -------- */
extern  const  CPU_INT32U  NetSock_ID_Size;
extern  const  CPU_INT32U  NetSock_RtnCodeSize;

extern  const  CPU_INT32U  NetSock_AddrLenSize;
extern  const  CPU_INT32U  NetSock_SockAddrSize;

extern  const  CPU_INT32U  NetSock_Size;
extern  const  CPU_INT32U  NetSock_TblSize;

extern  const  CPU_INT32U  NetSock_Q_LenSize;
extern  const  CPU_INT32U  NetSock_RandomPortNbrQ_Size;

extern  const  CPU_INT32U  NetSock_DataSize;
#endif



#ifdef  NET_SECURE_MODULE_PRESENT                                                   /* ------ NET SECURE MODULE ------- */

#endif


                                                                                    /* ------- NET BSD  MODULE -------- */
#if    (NET_BSD_CFG_API_EN  == DEF_ENABLED)
#ifdef  NET_SOCK_MODULE_PRESENT
#if    (NET_SOCK_CFG_FAMILY == NET_SOCK_FAMILY_IP_V4)
extern  const  CPU_INT32U  NetBSD_IP_to_Str_ArraySize;
#endif
#endif
#endif

extern  const  CPU_INT32U  NetBSD_DataSize;


                                                                                    /* ------- NET APP  MODULE -------- */



                                                                                    /* ----- NET TOTAL DATA SIZE ------ */
extern  const  CPU_INT32U  Net_DataSizeTot;

#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void         NetDbg_Init                 (void);


                                                                                    /* -------- DBG CFG FNCTS --------- */
#if (NET_DBG_CFG_STATUS_RSRC_LO_EN == DEF_ENABLED)

CPU_BOOLEAN  NetDbg_CfgRsrcBufThLo       (NET_IF_NBR  if_nbr,
                                          CPU_INT08U  th_pct,
                                          CPU_INT08U  hyst_pct);

CPU_BOOLEAN  NetDbg_CfgRsrcBufRxLargeThLo(NET_IF_NBR  if_nbr,
                                          CPU_INT08U  th_pct,
                                          CPU_INT08U  hyst_pct);

CPU_BOOLEAN  NetDbg_CfgRsrcBufTxLargeThLo(NET_IF_NBR  if_nbr,
                                          CPU_INT08U  th_pct,
                                          CPU_INT08U  hyst_pct);

CPU_BOOLEAN  NetDbg_CfgRsrcBufTxSmallThLo(NET_IF_NBR  if_nbr,
                                          CPU_INT08U  th_pct,
                                          CPU_INT08U  hyst_pct);


CPU_BOOLEAN  NetDbg_CfgRsrcTmrThLo       (CPU_INT08U  th_pct,
                                          CPU_INT08U  hyst_pct);


#ifdef  NET_CONN_MODULE_PRESENT
CPU_BOOLEAN  NetDbg_CfgRsrcConnThLo      (CPU_INT08U  th_pct,
                                          CPU_INT08U  hyst_pct);
#endif

#ifdef  NET_ARP_MODULE_PRESENT
CPU_BOOLEAN  NetDbg_CfgRsrcARP_CacheThLo (CPU_INT08U  th_pct,
                                          CPU_INT08U  hyst_pct);
#endif

#ifdef  NET_TCP_MODULE_PRESENT
CPU_BOOLEAN  NetDbg_CfgRsrcTCP_ConnThLo  (CPU_INT08U  th_pct,
                                          CPU_INT08U  hyst_pct);
#endif

#ifdef  NET_SOCK_MODULE_PRESENT
CPU_BOOLEAN  NetDbg_CfgRsrcSockThLo      (CPU_INT08U  th_pct,
                                          CPU_INT08U  hyst_pct);
#endif

#endif


#if (NET_DBG_CFG_MON_TASK_EN == DEF_ENABLED)
CPU_BOOLEAN  NetDbg_CfgMonTaskTime       (CPU_INT16U  time_sec);
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                               NETWORK DEBUG STATUS FUNCTION PROTOTYPES
*
* Note(s) : (1) (a) Network debug status API     functions MAY        be called by application function(s).
*
*               (b) Network debug status handler functions SHOULD NOT be called by application function(s).
*
*           (2) 'NetDbg_MonTaskStatusGetHandlerRsrc' network debug function names abbreviated to
*               'NetDbg_MonTaskStatGetHandler' to enforce ANSI-compliance of 31-character symbol
*                length uniqueness.
*********************************************************************************************************
*/

                                                                                    /* ----- DBG STATUS API FNCTS ----- */
                                                                                    /* See Note #1a.                    */
#if  (NET_DBG_CFG_STATUS_EN == DEF_ENABLED)
NET_DBG_STATUS  NetDbg_ChkStatus                (void);


NET_DBG_STATUS  NetDbg_ChkStatusBufs            (void);

NET_DBG_STATUS  NetDbg_ChkStatusTmrs            (void);
#endif

#if ((NET_DBG_CFG_STATUS_EN == DEF_ENABLED) && \
     (defined(NET_CONN_MODULE_PRESENT)))
NET_DBG_STATUS  NetDbg_ChkStatusConns           (void);
#endif

#if ((NET_DBG_CFG_STATUS_EN == DEF_ENABLED) && \
     (defined(NET_TCP_MODULE_PRESENT)))
NET_DBG_STATUS  NetDbg_ChkStatusTCP             (void);
#endif


#if  (NET_DBG_CFG_STATUS_RSRC_LOST_EN == DEF_ENABLED)
NET_DBG_STATUS  NetDbg_ChkStatusRsrcLost        (void);
#endif

#if  (NET_DBG_CFG_STATUS_RSRC_LO_EN   == DEF_ENABLED)
NET_DBG_STATUS  NetDbg_ChkStatusRsrcLo          (void);
#endif


#if  (NET_DBG_CFG_MON_TASK_EN == DEF_ENABLED)
NET_DBG_STATUS  NetDbg_MonTaskStatusGetRsrcLost (void);

NET_DBG_STATUS  NetDbg_MonTaskStatusGetRsrcLo   (void);
#endif



#if ((NET_DBG_CFG_STATUS_EN == DEF_ENABLED) && \
     (defined(NET_CONN_MODULE_PRESENT)))
void            NetDbg_GetInfoConn              (NET_CONN_ID            conn_id,
                                                 NET_CONN_FAMILY       *pconn_family,
                                                 NET_CONN_PROTOCOL_IX  *pconn_protocol_ix,
                                                 NET_CONN_LIST_IX      *pconn_ix_chain,
                                                 NET_CONN_LIST_IX      *pconn_ix,
                                                 NET_ERR               *perr);
#endif


/*$PAGE*/
                                                                                    /* --- DBG STATUS HANDLER FNCTS --- */
                                                                                    /* See Note #1b.                    */
#if  (NET_DBG_CFG_STATUS_EN == DEF_ENABLED)
NET_DBG_STATUS  NetDbg_ChkStatusHandler         (void);


NET_DBG_STATUS  NetDbg_ChkStatusHandlerBufs     (void);

NET_DBG_STATUS  NetDbg_ChkStatusHandlerTmrs     (void);
#endif

#if ((NET_DBG_CFG_STATUS_EN == DEF_ENABLED) && \
     (defined(NET_CONN_MODULE_PRESENT)))
NET_DBG_STATUS  NetDbg_ChkStatusHandlerConns    (void);
#endif

#if ((NET_DBG_CFG_STATUS_EN == DEF_ENABLED) && \
     (defined(NET_TCP_MODULE_PRESENT)))
NET_DBG_STATUS  NetDbg_ChkStatusHandlerTCP      (void);
#endif


#if  (NET_DBG_CFG_STATUS_RSRC_LOST_EN == DEF_ENABLED)
NET_DBG_STATUS  NetDbg_ChkStatusHandlerRsrcLost (void);
#endif

#if  (NET_DBG_CFG_STATUS_RSRC_LO_EN   == DEF_ENABLED)
NET_DBG_STATUS  NetDbg_ChkStatusHandlerRsrcLo   (void);
#endif


#if  (NET_DBG_CFG_MON_TASK_EN == DEF_ENABLED)                                   /* See Note #2.                         */
NET_DBG_STATUS  NetDbg_MonTaskStatGetHandlerLost(void);

NET_DBG_STATUS  NetDbg_MonTaskStatGetHandlerLo  (void);
#endif



#if ((NET_DBG_CFG_STATUS_EN == DEF_ENABLED) && \
     (defined(NET_CONN_MODULE_PRESENT)))
void            NetDbg_GetInfoHandlerConn       (NET_CONN_ID            conn_id,
                                                 NET_CONN_FAMILY       *pconn_family,
                                                 NET_CONN_PROTOCOL_IX  *pconn_protocol_ix,
                                                 NET_CONN_LIST_IX      *pconn_ix_chain,
                                                 NET_CONN_LIST_IX      *pconn_ix,
                                                 NET_ERR               *perr);
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                        CONFIGURATION ERRORS
*********************************************************************************************************
*/

#ifndef  NET_DBG_CFG_INFO_EN
#error  "NET_DBG_CFG_INFO_EN                    not #define'd in 'net_cfg.h'"
#error  "                                 [MUST be  DEF_DISABLED]           "
#error  "                                 [     ||  DEF_ENABLED ]           "

#elif  ((NET_DBG_CFG_INFO_EN != DEF_DISABLED) && \
        (NET_DBG_CFG_INFO_EN != DEF_ENABLED ))
#error  "NET_DBG_CFG_INFO_EN              illegally #define'd in 'net_cfg.h'"
#error  "                                 [MUST be  DEF_DISABLED]           "
#error  "                                 [     ||  DEF_ENABLED ]           "
#endif




#ifndef  NET_DBG_CFG_STATUS_EN
#error  "NET_DBG_CFG_STATUS_EN                  not #define'd in 'net_cfg.h'"
#error  "                                 [MUST be  DEF_DISABLED]           "
#error  "                                 [     ||  DEF_ENABLED ]           "

#elif  ((NET_DBG_CFG_STATUS_EN != DEF_DISABLED) && \
        (NET_DBG_CFG_STATUS_EN != DEF_ENABLED ))
#error  "NET_DBG_CFG_STATUS_EN            illegally #define'd in 'net_cfg.h'"
#error  "                                 [MUST be  DEF_DISABLED]           "
#error  "                                 [     ||  DEF_ENABLED ]           "
#endif


                                                            /* Correctly configured in 'net_cfg_net.h'; DO NOT MODIFY.  */
#ifndef  NET_DBG_CFG_STATUS_RSRC_LOST_EN
#error  "NET_DBG_CFG_STATUS_RSRC_LOST_EN        not #define'd in 'net_cfg_net.h'"
#error  "                                 [MUST be  DEF_DISABLED]               "
#error  "                                 [     ||  DEF_ENABLED ]               "

#elif  ((NET_DBG_CFG_STATUS_RSRC_LOST_EN != DEF_DISABLED) && \
        (NET_DBG_CFG_STATUS_RSRC_LOST_EN != DEF_ENABLED ))
#error  "NET_DBG_CFG_STATUS_RSRC_LOST_EN  illegally #define'd in 'net_cfg_net.h'"
#error  "                                 [MUST be  DEF_DISABLED]               "
#error  "                                 [     ||  DEF_ENABLED ]               "
#endif


                                                            /* Correctly configured in 'net_cfg_net.h'; DO NOT MODIFY.  */
#ifndef  NET_DBG_CFG_STATUS_RSRC_LO_EN
#error  "NET_DBG_CFG_STATUS_RSRC_LO_EN          not #define'd in 'net_cfg_net.h'"
#error  "                                 [MUST be  DEF_DISABLED]               "
#error  "                                 [     ||  DEF_ENABLED ]               "

#elif  ((NET_DBG_CFG_STATUS_RSRC_LO_EN != DEF_DISABLED) && \
        (NET_DBG_CFG_STATUS_RSRC_LO_EN != DEF_ENABLED ))
#error  "NET_DBG_CFG_STATUS_RSRC_LO_EN    illegally #define'd in 'net_cfg_net.h'"
#error  "                                 [MUST be  DEF_DISABLED]               "
#error  "                                 [     ||  DEF_ENABLED ]               "
#endif




/*$PAGE*/
#ifndef  NET_DBG_CFG_MEM_CLR_EN
#error  "NET_DBG_CFG_MEM_CLR_EN                 not #define'd in 'net_cfg.h'"
#error  "                                 [MUST be  DEF_DISABLED]           "
#error  "                                 [     ||  DEF_ENABLED ]           "

#elif  ((NET_DBG_CFG_MEM_CLR_EN != DEF_DISABLED) && \
        (NET_DBG_CFG_MEM_CLR_EN != DEF_ENABLED ))
#error  "NET_DBG_CFG_MEM_CLR_EN           illegally #define'd in 'net_cfg.h'"
#error  "                                 [MUST be  DEF_DISABLED]           "
#error  "                                 [     ||  DEF_ENABLED ]           "
#endif



#ifndef  NET_DBG_CFG_TEST_EN
#error  "NET_DBG_CFG_TEST_EN                    not #define'd in 'net_cfg.h'"
#error  "                                 [MUST be  DEF_DISABLED]           "
#error  "                                 [     ||  DEF_ENABLED ]           "

#elif  ((NET_DBG_CFG_TEST_EN != DEF_DISABLED) && \
        (NET_DBG_CFG_TEST_EN != DEF_ENABLED ))
#error  "NET_DBG_CFG_TEST_EN              illegally #define'd in 'net_cfg.h'"
#error  "                                 [MUST be  DEF_DISABLED]           "
#error  "                                 [     ||  DEF_ENABLED ]           "
#endif



                                                            /* Correctly configured in 'net_cfg_net.h'; DO NOT MODIFY.  */
#ifndef  NET_DBG_CFG_MON_TASK_EN
#error  "NET_DBG_CFG_MON_TASK_EN                not #define'd in 'net_cfg_net.h'"
#error  "                                 [MUST be  DEF_DISABLED]               "
#error  "                                 [     ||  DEF_ENABLED ]               "

#elif  ((NET_DBG_CFG_MON_TASK_EN != DEF_DISABLED) && \
        (NET_DBG_CFG_MON_TASK_EN != DEF_ENABLED ))
#error  "NET_DBG_CFG_MON_TASK_EN          illegally #define'd in 'net_cfg_net.h'"
#error  "                                 [MUST be  DEF_DISABLED]               "
#error  "                                 [     ||  DEF_ENABLED ]               "
#endif

