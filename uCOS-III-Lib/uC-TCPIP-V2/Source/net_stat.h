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
*                                     NETWORK STATISTICS MANAGEMENT
*
* Filename      : net_stat.h
* Version       : V2.11.02
* Programmer(s) : ITJ
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/

#if ((defined(NET_STAT_MODULE)) && \
     (defined(NET_GLOBALS_EXT)))
#define  NET_STAT_EXT
#else
#define  NET_STAT_EXT  extern
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                NETWORK STATISTICS POOL TYPE DEFINES
*
* Note(s) : (1) NET_STAT_TYPE_&&& #define values specifically chosen as ASCII representations of the network
*               statistics pool types.  Memory displays of statistics pools will display the statistics pool 
*               TYPEs with their chosen ASCII names.
*********************************************************************************************************
*/

#define  NET_STAT_TYPE_NONE                       CPU_TYPE_CREATE('N', 'O', 'N', 'E')
#define  NET_STAT_TYPE_CTR                        CPU_TYPE_CREATE('C', 'T', 'R', ' ')
#define  NET_STAT_TYPE_POOL                       CPU_TYPE_CREATE('P', 'O', 'O', 'L')


/*$PAGE*/
/*
*********************************************************************************************************
*                                             DATA TYPES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                              NETWORK STATISTICS POOL QUANTITY DATA TYPE
*
* Note(s) : (1) Statistics pool quantity data type MUST be configured with an appropriate-sized network 
*               data type large enough to perform calculations on the following data types :
*
*               (a) NET_BUF_QTY
*               (b) NET_TMR_QTY
*               (c) NET_CONN_QTY
*               (d) NET_CONN_LIST_QTY
*               (e) NET_ARP_CACHE_QTY
*               (f) NET_ICMP_SRC_QUENCH_QTY
*               (g) NET_TCP_CONN_QTY
*               (h) NET_SOCK_QTY
*
*           (2) NET_STAT_POOL_NBR_MAX  SHOULD be #define'd based on 'NET_STAT_POOL_QTY' data type declared.
*********************************************************************************************************
*/

typedef  CPU_INT16U  NET_STAT_POOL_QTY;                         /* Defines max qty of stat pool entries to support.     */

#define  NET_STAT_POOL_NBR_MIN                             1
#define  NET_STAT_POOL_NBR_MAX           DEF_INT_16U_MAX_VAL    /* See Note #2.                                         */

#define  NET_STAT_POOL_MIN_VAL                             0
#define  NET_STAT_POOL_MAX_VAL    (NET_STAT_POOL_NBR_MAX - 1)


/*$PAGE*/
/*
*********************************************************************************************************
*                                NETWORK STATISTICS COUNTER DATA TYPE
*
* Note(s) : (1) Forced (32-bit) word-alignment at start of statistics counter NOT required since first 
*               data member 'Type' is is declared as 'NET_TYPE', equivalent to 'CPU_INT32U'.
*
*           (2) Counter statistic entries MUST ALWAYS be accessed exclusively in critical sections.
*
*           (3) (a) 'CurCtr' tracks the current counter value; & ...
*               (b) 'MaxCtr' tracks the maximum counter value at any one time.
*********************************************************************************************************
*/

                                                                /* ------------------- NET STAT CTR ------------------- */
typedef  struct  net_stat_ctr {
    NET_TYPE            Type;                                   /* Type cfg'd @ init : NET_STAT_TYPE_CTR.               */

    NET_CTR             CurCtr;                                 /* Cur ctr val.                                         */
    NET_CTR             MaxCtr;                                 /* Max ctr val.                                         */
} NET_STAT_CTR;


/*$PAGE*/
/*
*********************************************************************************************************
*                                  NETWORK STATISTICS POOL DATA TYPE
*
* Note(s) : (1) Forced (32-bit) word-alignment at start of statistics pool NOT required since first 
*               data member 'Type' is is declared as 'NET_TYPE', equivalent to 'CPU_INT32U'.
*
*           (2) Pool statistic entries MUST ALWAYS be accessed exclusively in critical sections.
*
*           (3) (a) 'EntriesInit'/'EntriesTot' indicate the initial/current total number of entries in 
*                    the statistics pool.
*
*               (b) 'EntriesAvail'/'EntriesUsed' track the current number of entries available/used 
*                    from the statistics pool, while 'EntriesUsedMax' tracks the maximum number of 
*                    entries used at any one time.
*
*               (c) 'EntriesLostCur'/'EntriesLostTot' track the current/total number of unrecoverable 
*                    invalid/corrupted entries lost from the statistics pool.  Lost entries MUST be 
*                    determined by the owner of the statistics pool.
*
*               (d) 'EntriesAllocCtr'/'EntriesDeallocCtr' track the current number of allocated/
*                    deallocated entries in the statistics pool.
*
*           (4) Assuming statistics pool are always accessed in critical sections (see Note #2), the 
*               following equations for statistics pools are true at all times :
*
*                       EntriesInit = EntriesTot   + EntriesLostTot
*
*                       EntriesTot  = EntriesAvail + EntriesUsed
*
*                       EntriesUsed = EntriesAllocCtr - EntriesDeallocCtr - EntriesLostCur
*********************************************************************************************************
*/

                                                                /* ------------------- NET STAT POOL ------------------ */
typedef  struct  net_stat_pool {
    NET_TYPE            Type;                                   /* Type cfg'd @ init : NET_STAT_TYPE_POOL.              */

    NET_STAT_POOL_QTY   EntriesInit;                            /* Init  nbr entries      in   pool.                    */
    NET_STAT_POOL_QTY   EntriesTot;                             /* Tot   nbr entries      in   pool.                    */
    NET_STAT_POOL_QTY   EntriesAvail;                           /* Avail nbr entries      in   pool.                    */
    NET_STAT_POOL_QTY   EntriesUsed;                            /* Used  nbr entries      from pool.                    */
    NET_STAT_POOL_QTY   EntriesUsedMax;                         /* Max   nbr entries used from pool.                    */
    NET_STAT_POOL_QTY   EntriesLostCur;                         /* Cur   nbr entries lost from pool.                    */
    NET_STAT_POOL_QTY   EntriesLostTot;                         /* Tot   nbr entries lost from pool.                    */

    NET_CTR             EntriesAllocCtr;                        /* Tot   nbr entries successfully   alloc'd.            */
    NET_CTR             EntriesDeallocCtr;                      /* Tot   nbr entries successfully dealloc'd.            */
} NET_STAT_POOL;


/*$PAGE*/
/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void  NetStat_Init            (void);



                                                                            /* --------- NET STAT CTR  FNCTS ---------- */
void  NetStat_CtrInit         (NET_STAT_CTR       *pstat_ctr,
                               NET_ERR            *perr);

void  NetStat_CtrClr          (NET_STAT_CTR       *pstat_ctr,
                               NET_ERR            *perr);


void  NetStat_CtrReset        (NET_STAT_CTR       *pstat_ctr,
                               NET_ERR            *perr);

void  NetStat_CtrResetMax     (NET_STAT_CTR       *pstat_ctr,
                               NET_ERR            *perr);


void  NetStat_CtrInc          (NET_STAT_CTR       *pstat_ctr,
                               NET_ERR            *perr);

void  NetStat_CtrDec          (NET_STAT_CTR       *pstat_ctr,
                               NET_ERR            *perr);



                                                                            /* --------- NET STAT POOL FNCTS ---------- */
void  NetStat_PoolInit        (NET_STAT_POOL      *pstat_pool,
                               NET_STAT_POOL_QTY   nbr_avail,
                               NET_ERR            *perr);

void  NetStat_PoolClr         (NET_STAT_POOL      *pstat_pool,
                               NET_ERR            *perr);


void  NetStat_PoolReset       (NET_STAT_POOL      *pstat_pool,
                               NET_ERR            *perr);

void  NetStat_PoolResetUsedMax(NET_STAT_POOL      *pstat_pool,
                               NET_ERR            *perr);


void  NetStat_PoolEntryUsedInc(NET_STAT_POOL      *pstat_pool,
                               NET_ERR            *perr);

void  NetStat_PoolEntryUsedDec(NET_STAT_POOL      *pstat_pool,
                               NET_ERR            *perr);

void  NetStat_PoolEntryLostInc(NET_STAT_POOL      *pstat_pool,
                               NET_ERR            *perr);


/*$PAGE*/
/*
*********************************************************************************************************
*                                        CONFIGURATION ERRORS
*********************************************************************************************************
*/

