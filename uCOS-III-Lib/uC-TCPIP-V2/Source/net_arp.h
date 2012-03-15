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
*                                          NETWORK ARP LAYER
*                                    (ADDRESS RESOLUTION PROTOCOL)
*
* Filename      : net_arp.h
* Version       : V2.11.02
* Programmer(s) : ITJ
*                 SR
*********************************************************************************************************
* Note(s)       : (1) Address Resolution Protocol ONLY required for network interfaces that require
*                     network-address-to-hardware-address bindings (see RFC #826 'Abstract').
*
*                 (2) Supports Address Resolution Protocol as described in RFC #826 with the following
*                     restrictions/constraints :
*
*                     (a) ONLY supports the following hardware types :
*                         (1) 48-bit Ethernet
*
*                     (b) ONLY supports the following protocol types :
*                         (1) 32-bit IP
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) ARP Layer module is required for some network interfaces (see 'net_arp.h  Note #1').
*
*           (2) (a) The following ARP-module-present configuration value MUST be pre-#define'd 
*                   in 'net_cfg_net.h' PRIOR to all other network modules that require ARP Layer 
*                   configuration (see 'net_cfg_net.h  ARP LAYER CONFIGURATION  Note #2b' & 
*                   'net_cfg_net.h  NETWORK INTERFACE LAYER CONFIGURATION  Note #2b') :
*
*                       NET_ARP_MODULE_PRESENT
*
*               (b) Since ARP-module-present configuration is already pre-#define'd in 'net_cfg_net.h' 
*                   (see Note #2a), the ARP module is protected from multiple pre-processor inclusion 
*                   through use of a module-already-available pre-processor macro definition.
*********************************************************************************************************
*/

#ifdef   NET_ARP_MODULE_PRESENT                                 /* See Note #2a.                                        */
#ifndef  NET_ARP_MODULE_AVAIL                                   /* See Note #2b.                                        */
#define  NET_ARP_MODULE_AVAIL


/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/

#if ((defined(NET_ARP_MODULE)) && \
     (defined(NET_GLOBALS_EXT)))
#define  NET_ARP_EXT
#else
#define  NET_ARP_EXT  extern
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                          ARP CACHE DEFINES
*********************************************************************************************************
*/

#define  NET_ARP_CACHE_ACCESSED_TH_MIN                    10
#define  NET_ARP_CACHE_ACCESSED_TH_MAX                 65000
#define  NET_ARP_CACHE_ACCESSED_TH_DFLT                  100

#define  NET_ARP_CACHE_TIMEOUT_MIN_SEC           ( 1  *  DEF_TIME_NBR_SEC_PER_MIN)  /* Cache timeout min  =  1 minute   */
#define  NET_ARP_CACHE_TIMEOUT_MAX_SEC           (10  *  DEF_TIME_NBR_SEC_PER_MIN)  /* Cache timeout max  = 10 minutes  */
#define  NET_ARP_CACHE_TIMEOUT_DFLT_SEC          (10  *  DEF_TIME_NBR_SEC_PER_MIN)  /* Cache timeout dflt = 10 minutes  */


/*
*********************************************************************************************************
*                                         ARP REQUEST DEFINES
*
* Note(s) : (1) RFC #1122, Section 2.3.2.1 states that "a mechanism to prevent ARP flooding (repeatedly
*               sending an ARP Request for the same IP address, at a high rate) MUST be included.  The
*               recommended maximum rate is 1 per second per destination".
*********************************************************************************************************
*/

#define  NET_ARP_REQ_RETRY_MIN                             0
#define  NET_ARP_REQ_RETRY_MAX                             5
#define  NET_ARP_REQ_RETRY_DFLT                            3
                                                                /* ARP req retry timeouts (see Note #1).                */
#define  NET_ARP_REQ_RETRY_TIMEOUT_MIN_SEC                 1    /* ARP req retry timeout min  =  1 seconds              */
#define  NET_ARP_REQ_RETRY_TIMEOUT_MAX_SEC                10    /* ARP req retry timeout max  = 10 seconds              */
#define  NET_ARP_REQ_RETRY_TIMEOUT_DFLT_SEC                5    /* ARP req retry timeout dflt =  5 seconds              */


/*
*********************************************************************************************************
*                                          ARP FLAG DEFINES
*********************************************************************************************************
*/

                                                                /* ------------------ NET ARP FLAGS ------------------- */
#define  NET_ARP_FLAG_NONE                        DEF_BIT_NONE
#define  NET_ARP_FLAG_USED                        DEF_BIT_00    /* ARP cache cur used; i.e. NOT in free cache pool.     */


/*
*********************************************************************************************************
*                                          ARP TYPE DEFINES
*
* Note(s) : (1) NET_ARP_TYPE_&&& #define values specifically chosen as ASCII representations of the ARP
*               types.  Memory displays of ARP types will display with their chosen ASCII names.
*********************************************************************************************************
*/

#define  NET_ARP_TYPE_NONE                        CPU_TYPE_CREATE('N', 'O', 'N', 'E')
#define  NET_ARP_TYPE_CACHE                       CPU_TYPE_CREATE('A', 'R', 'P', ' ')


/*$PAGE*/
/*
*********************************************************************************************************
*                                   ARP HARDWARE & PROTOCOL DEFINES
*
* Note(s) : (1) The following ARP values MUST be pre-#define'd in 'net_def.h' PRIOR to 'net_cfg.h' so
*               that the developer can configure ARP for the correct network interface link layer &
*               network protocol layer (see 'net_def.h  ARP LAYER DEFINES' & 'net_cfg_net.h  ARP LAYER
*               CONFIGURATION') :
*
*               (a)                                                     -------- ARP HW TYPES --------
*                   (1) NET_ARP_HW_TYPE_NONE
*
*                   (2) (A) NET_ARP_HW_TYPE_ETHER
*                       (B) NET_ARP_HW_ADDR_LEN_ETHER
*
*
*               (b)                                                     ----- ARP PROTOCOL TYPES -----
*                   (1) NET_ARP_PROTOCOL_TYPE_NONE
*
*                   (2) (A) NET_ARP_PROTOCOL_TYPE_IP_V4
*                       (B) NET_ARP_PROTOCOL_ADDR_LEN_IP_V4
*********************************************************************************************************
*/

#if 0                                                           /* See Note #1.                                         */
                                                                /* ------------------- ARP HW TYPES ------------------- */
#define  NET_ARP_HW_TYPE_NONE                         0x0000u

#define  NET_ARP_HW_TYPE_ETHER                        0x0001u
#define  NET_ARP_HW_ADDR_LEN_ETHER                         6

                                                                /* ---------------- ARP PROTOCOL TYPES ---------------- */
#define  NET_ARP_PROTOCOL_TYPE_NONE                   0x0000u

#define  NET_ARP_PROTOCOL_TYPE_IP_V4                  0x0800u
#define  NET_ARP_PROTOCOL_ADDR_LEN_IP_V4                   4

#endif


/*
*********************************************************************************************************
*                                    ARP HEADER / MESSAGE DEFINES
*
* Note(s) : (1) See RFC #826, Section 'Packet Format' for ARP packet header format.
*
*               (a) ARP header includes two pairs of hardware & protocol type addresses--one each for the
*                   sender & the target.
*********************************************************************************************************
*/

#define  NET_ARP_HDR_SIZE_MIN                             12
#define  NET_ARP_HDR_SIZE_MAX                             68
#define  NET_ARP_HDR_SIZE_BASE                             8
                                                                /* See Note #1a.                                        */
#define  NET_ARP_HDR_SIZE                               (NET_ARP_HDR_SIZE_BASE              + \
                                                        (NET_ARP_CFG_HW_ADDR_LEN       * 2) + \
                                                        (NET_ARP_CFG_PROTOCOL_ADDR_LEN * 2))


#define  NET_ARP_HDR_OP_REQ                           0x0001u
#define  NET_ARP_HDR_OP_REPLY                         0x0002u


#define  NET_ARP_MSG_LEN                                 NET_ARP_HDR_SIZE
#define  NET_ARP_MSG_LEN_DATA                              0


/*$PAGE*/
/*
*********************************************************************************************************
*                                          ARP CACHE STATES
*
*                          (1a)                            (1b)
*                            ARP REQUEST                     ARP REPLY
*              ----------    FETCHES NEW     -----------     RESOLVES       ------------
*              |        |     ARP CACHE      |         |     ARP CACHE      |          |
*              |  FREE  | -----------------> | PENDING | -----------------> | RESOLVED |
*              |        |                    |         |                    |          |
*              ----------  (1c)              -----------                    ------------
*                 ^  ^       ARP REQUEST          |                               |
*                 |  |        TIMES OUT           |                               |
*                 |  |      AFTER RETRIES         |        (1d)                   |
*                 |  ------------------------------          ARP CACHE            |
*                 |                                          TIMES OUT            |
*                 -----------------------------------------------------------------
*
*
* Note(s) : (1) (a) ARP cache lookup fails to find the ARP cache with corresponding protocol address.  
*                   A new ARP cache is allocated from the ARP cache pool & inserted into the ARP Cache 
*                   List in the 'PENDING' state.  An ARP Request is generated & transmitted to resolve 
*                   the pending ARP cache.
*
*               (b) An ARP Reply resolves the pending ARP cache's hardware address.
*
*               (c) Alternatively, no corresponding ARP Reply is received after the maximum number of 
*                   ARP Request retries & the ARP cache is freed.
*
*               (d) ARP cache times out & is freed.
*********************************************************************************************************
*/

#define  NET_ARP_CACHE_STATE_NONE                          0u
#define  NET_ARP_CACHE_STATE_FREE                          1u
#define  NET_ARP_CACHE_STATE_PEND                          2u
#define  NET_ARP_CACHE_STATE_RESOLVED                      3u


/*$PAGE*/
/*
*********************************************************************************************************
*                                             DATA TYPES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                    ARP CACHE QUANTITY DATA TYPE
*
* Note(s) : (1) NET_ARP_CACHE_NBR_MAX  SHOULD be #define'd based on 'NET_ARP_CACHE_QTY' data type declared.
*********************************************************************************************************
*/

typedef  CPU_INT16U  NET_ARP_CACHE_QTY;                         /* Defines max qty of ARP caches to support.            */

#define  NET_ARP_CACHE_NBR_MIN                             1
#define  NET_ARP_CACHE_NBR_MAX           DEF_INT_16U_MAX_VAL    /* See Note #1.                                         */


/*
*********************************************************************************************************
*                                     ARP CACHE STATE DATA TYPE
*********************************************************************************************************
*/

typedef  CPU_INT08U  NET_ARP_CACHE_STATE;


/*
*********************************************************************************************************
*                                    ARP ADDRESS LENGTH DATA TYPE
*********************************************************************************************************
*/

typedef  CPU_INT08U  NET_ARP_ADDR_LEN;


/*$PAGE*/
/*
*********************************************************************************************************
*                                            ARP HEADER
*
* Note(s) : (1) See RFC #826, Section 'Packet Format' for ARP packet header format.
*
*           (2) See 'ARP HEADER / MESSAGE DEFINES'.
*********************************************************************************************************
*/

                                                                        /* --------------- NET ARP HDR ---------------- */
typedef  struct  net_arp_hdr {
    CPU_INT16U      HW_Type;                                            /* ARP pkt hw       type.                       */
    CPU_INT16U      ProtocolType;                                       /* ARP pkt protocol type.                       */

    CPU_INT08U      HW_AddrLen;                                         /* ARP pkt hw       addr len (in octets).       */
    CPU_INT08U      ProtocolAddrLen;                                    /* ARP pkt protocol addr len (in octets).       */

    CPU_INT16U      OpCode;                                             /* ARP op code (see Note #2).                   */

    CPU_INT08U      HW_AddrSender[NET_ARP_CFG_HW_ADDR_LEN];             /* Sender hw       addr.                        */
    CPU_INT08U      ProtocolAddrSender[NET_ARP_CFG_PROTOCOL_ADDR_LEN];  /* Sender protocol addr.                        */

    CPU_INT08U      HW_AddrTarget[NET_ARP_CFG_HW_ADDR_LEN];             /* Target hw       addr.                        */
    CPU_INT08U      ProtocolAddrTarget[NET_ARP_CFG_PROTOCOL_ADDR_LEN];  /* Target protocol addr.                        */
} NET_ARP_HDR;


/*$PAGE*/
/*
*********************************************************************************************************
*                                      ARP CACHE ENTRY DATA TYPE
*
*                                  NET_ARP_CACHE
*                                 |-------------|
*                                 | Cache Type  |
*                      Previous   |-------------|
*                       Cache <----------O      |
*                                 |-------------|     Next
*                                 |      O----------> Cache      Buffer Queue
*                                 |-------------|                    Head       -------
*                                 |      O------------------------------------> |     |
*                                 |-------------|                               |     |
*                                 |      O----------------------                -------
*                                 |-------------|              |                  | ^
*                                 |      O----------> Cache    |                  v |
*                                 |-------------|     Timer    |                -------
*                                 |  Hardware:  |              |                |     |
*                                 |    Type     |              |                |     |
*                                 |   Length    |              |                -------
*                                 |   Address   |              |                  | ^
*                                 |-------------|              | Buffer Queue     v |
*                                 |  Protocol:  |              |     Tail       -------
*                                 |    Type     |              ---------------> |     |
*                                 |   Length    |                               |     |
*                                 |   Address   |                               -------
*                                 |-------------|
*                                 |    Flags    |
*                                 |-------------|
*                                 |   Accessed  |
*                                 |   Counter   |
*                                 |-------------|
*                                 |   Request   |
*                                 |   Counter   |
*                                 |-------------|
*                                 |    State    |
*                                 |-------------|
*
*
* Note(s) : (1) Forced (32-bit) word-alignment at start of ARP cache NOT required since first data 
*               member 'Type' is is declared as 'NET_TYPE', equivalent to 'CPU_INT32U'.
*
*           (2) Configured by the developer via 'net_cfg.h' & 'net_cfg_net.h' at compile time.
*
*               See 'net_arp.h  Note #2' & 'ARP HARDWARE & PROTOCOL DEFINES  Note #1' for supported
*               hardware & protocol types.
*********************************************************************************************************
*/

                                                                        /* --------------- NET ARP CACHE -------------- */
typedef  struct  net_arp_cache  NET_ARP_CACHE;

struct  net_arp_cache {
    NET_TYPE              Type;                                         /* Type cfg'd @ init : NET_ARP_TYPE_CACHE.      */

    NET_ARP_CACHE        *PrevPtr;                                      /* Ptr to PREV ARP cache.                       */
    NET_ARP_CACHE        *NextPtr;                                      /* Ptr to NEXT ARP cache.                       */

    NET_BUF              *BufQ_Head;                                    /* Ptr to head of cache's buf Q.                */
    NET_BUF              *BufQ_Tail;                                    /* Ptr to tail of cache's buf Q.                */

    NET_TMR              *TmrPtr;                                       /* Ptr to cache TMR.                            */


    NET_IF_NBR            IF_Nbr;                                       /* IF nbr of ARP cache addr.                    */


    CPU_INT16U            HW_Type;                                      /* Remote hw       type     (see Note #2).      */
    CPU_INT08U            HW_AddrLen;                                   /* Remote hw       addr len (see Note #2).      */
    CPU_INT08U            HW_Addr[NET_ARP_CFG_HW_ADDR_LEN];             /* Remote hw       addr.                        */

    CPU_INT16U            ProtocolType;                                 /* Remote protocol type     (see Note #2).      */
    CPU_INT08U            ProtocolAddrLen;                              /* Remote protocol addr len (see Note #2).      */
    CPU_INT08U            ProtocolAddr[NET_ARP_CFG_PROTOCOL_ADDR_LEN];  /* Remote protocol addr.                        */

                                                                        /* Sender protocol addr.                        */
    CPU_INT08U            SenderProtocolAddr[NET_ARP_CFG_PROTOCOL_ADDR_LEN];


    CPU_INT16U            AccessedCtr;                                  /* Nbr successful srchs.                        */
    CPU_INT08U            ReqAttemptsCtr;                               /* ARP req attempts ctr.                        */


    NET_ARP_CACHE_STATE   State;                                        /* ARP cache state.                             */

    CPU_INT16U            Flags;                                        /* ARP cache flags.                             */
};


/*$PAGE*/
/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/

NET_ARP_EXT  NET_ARP_CACHE   NetARP_CacheTbl[NET_ARP_CFG_NBR_CACHE];
NET_ARP_EXT  NET_ARP_CACHE  *NetARP_CachePoolPtr;                       /* Ptr to pool of free ARP caches.              */
NET_ARP_EXT  NET_STAT_POOL   NetARP_CachePoolStat;

#if (NET_CTR_CFG_STAT_EN  == DEF_ENABLED)
NET_ARP_EXT  NET_CTR         NetARP_CacheSrchCtr_lo;                    /* Inc'd for EVERY cache lookup (lo ctr).       */
NET_ARP_EXT  NET_CTR         NetARP_CacheSrchCtr_hi;                    /*                 Cache lookup  hi ctr.        */
NET_ARP_EXT  NET_CTR         NetARP_CacheFoundCtr_lo;                   /* Inc'd for EVERY cache found  (lo ctr).       */
NET_ARP_EXT  NET_CTR         NetARP_CacheFoundCtr_hi;                   /*                 Cache found   hi ctr.        */
NET_ARP_EXT  CPU_INT08U      NetARP_CacheFoundPct;                      /* Found % = (FoundCtr / SrchCtr) * 100%        */
#endif

NET_ARP_EXT  NET_ARP_CACHE  *NetARP_CacheListHead;                      /* Ptr to head of ARP Cache List.               */
NET_ARP_EXT  NET_ARP_CACHE  *NetARP_CacheListTail;                      /* Ptr to tail of ARP Cache List.               */


NET_ARP_EXT  CPU_INT16U      NetARP_CacheTimeout_sec;                   /* ARP cache timeout              (in secs ).   */
NET_ARP_EXT  NET_TMR_TICK    NetARP_CacheTimeout_tick;                  /* ARP cache timeout              (in ticks).   */

NET_ARP_EXT  CPU_INT16U      NetARP_CacheAccessedTh_nbr;                /* Nbr successful srch's to promote ARP cache.  */

NET_ARP_EXT  CPU_INT08U      NetARP_ReqMaxAttempts_nbr;                 /* ARP req max nbr of attempts.                 */
NET_ARP_EXT  CPU_INT08U      NetARP_ReqTimeout_sec;                     /* ARP req wait-for-reply timeout (in secs ).   */
NET_ARP_EXT  NET_TMR_TICK    NetARP_ReqTimeout_tick;                    /* ARP req wait-for-reply timeout (in ticks).   */


/*$PAGE*/
/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void              NetARP_Init                     (void);


                                                                                    /* ---------- CFG FNCTS ----------- */
CPU_BOOLEAN       NetARP_CfgCacheTimeout          (CPU_INT16U          timeout_sec);

CPU_BOOLEAN       NetARP_CfgCacheAccessedTh       (CPU_INT16U          nbr_access);

CPU_BOOLEAN       NetARP_CfgReqTimeout            (CPU_INT08U          timeout_sec);

CPU_BOOLEAN       NetARP_CfgReqMaxRetries         (CPU_INT08U          max_nbr_retries);


                                                                                    /* --------- STATUS FNCTS --------- */
void              NetARP_ProbeAddrOnNet           (NET_PROTOCOL_TYPE   protocol_type,
                                                   CPU_INT08U         *paddr_protocol_sender,
                                                   CPU_INT08U         *paddr_protocol_target,
                                                   NET_ARP_ADDR_LEN    addr_protocol_len,
                                                   NET_ERR            *perr);

CPU_BOOLEAN       NetARP_IsAddrProtocolConflict   (NET_IF_NBR          if_nbr,
                                                   NET_ERR            *perr);



                                                                                    /* ------- ARP CACHE FNCTS -------- */
void              NetARP_CacheHandler             (NET_BUF            *pbuf,
                                                   NET_ERR            *perr);

                                                                                    /* ---- ARP CACHE STATUS FNCTS ---- */
NET_ARP_ADDR_LEN  NetARP_CacheGetAddrHW           (CPU_INT08U         *paddr_hw,
                                                   NET_ARP_ADDR_LEN    addr_hw_len_buf,
                                                   CPU_INT08U         *paddr_protocol,
                                                   NET_ARP_ADDR_LEN    addr_protocol_len,
                                                   NET_ERR            *perr);


CPU_INT08U        NetARP_CacheCalcStat            (void);


NET_STAT_POOL     NetARP_CachePoolStatGet         (void);

void              NetARP_CachePoolStatResetMaxUsed(void);



                                                                                    /* ----------- RX FNCTS ----------- */
void              NetARP_Rx                       (NET_BUF            *pbuf,
                                                   NET_ERR            *perr);


                                                                                    /* ----------- TX FNCTS ----------- */
void              NetARP_TxReqGratuitous          (NET_PROTOCOL_TYPE   protocol_type,
                                                   CPU_INT08U         *paddr_protocol,
                                                   NET_ARP_ADDR_LEN    addr_protocol_len,
                                                   NET_ERR            *perr);


/*$PAGE*/
/*
*********************************************************************************************************
*                                        CONFIGURATION ERRORS
*********************************************************************************************************
*/

#ifndef  NET_ARP_CFG_HW_TYPE
#error  "NET_ARP_CFG_HW_TYPE                  not #define'd in 'net_cfg.h'"
#error  "                               [MUST be  NET_ARP_HW_TYPE_ETHER]  "

#elif   (NET_ARP_CFG_HW_TYPE != NET_ARP_HW_TYPE_ETHER)
#error  "NET_ARP_CFG_HW_TYPE            illegally #define'd in 'net_cfg.h'"
#error  "                               [MUST be  NET_ARP_HW_TYPE_ETHER]  "

#else
                                                            /* Correctly configured in 'net_cfg_net.h'; DO NOT MODIFY.  */
#ifndef  NET_ARP_CFG_HW_ADDR_LEN
#error  "NET_ARP_CFG_HW_ADDR_LEN              not #define'd in 'net_cfg_net.h'"
#error  "                               [MUST be  NET_ARP_HW_ADDR_LEN_ETHER]  "

#elif   (NET_ARP_CFG_HW_ADDR_LEN != NET_ARP_HW_ADDR_LEN_ETHER)
#error  "NET_ARP_CFG_HW_ADDR_LEN        illegally #define'd in 'net_cfg_net.h'"
#error  "                               [MUST be  NET_ARP_HW_ADDR_LEN_ETHER]  "
#endif

#endif



#ifndef  NET_ARP_CFG_PROTOCOL_TYPE
#error  "NET_ARP_CFG_PROTOCOL_TYPE            not #define'd in 'net_cfg.h'    "
#error  "                               [MUST be  NET_ARP_PROTOCOL_TYPE_IP_V4]"

#elif   (NET_ARP_CFG_PROTOCOL_TYPE != NET_ARP_PROTOCOL_TYPE_IP_V4)
#error  "NET_ARP_CFG_PROTOCOL_TYPE      illegally #define'd in 'net_cfg.h'    "
#error  "                               [MUST be  NET_ARP_PROTOCOL_TYPE_IP_V4]"

#else
                                                            /* Correctly configured in 'net_cfg_net.h'; DO NOT MODIFY.  */
#ifndef  NET_ARP_CFG_PROTOCOL_ADDR_LEN
#error  "NET_ARP_CFG_PROTOCOL_ADDR_LEN        not #define'd in 'net_cfg_net.h'    "
#error  "                               [MUST be  NET_ARP_PROTOCOL_ADDR_LEN_IP_V4]"

#elif   (NET_ARP_CFG_PROTOCOL_ADDR_LEN != NET_ARP_PROTOCOL_ADDR_LEN_IP_V4)
#error  "NET_ARP_CFG_PROTOCOL_ADDR_LEN  illegally #define'd in 'net_cfg_net.h'    "
#error  "                               [MUST be  NET_ARP_PROTOCOL_ADDR_LEN_IP_V4]"
#endif

#endif




#ifndef  NET_ARP_CFG_NBR_CACHE
#error  "NET_ARP_CFG_NBR_CACHE                not #define'd in 'net_cfg.h' "
#error  "                               [MUST be  >= NET_ARP_CACHE_NBR_MIN]"
#error  "                               [     &&  <= NET_ARP_CACHE_NBR_MAX]"

#elif   (DEF_CHK_VAL(NET_ARP_CFG_NBR_CACHE,          \
                     NET_ARP_CACHE_NBR_MIN,          \
                     NET_ARP_CACHE_NBR_MAX) != DEF_OK)
#error  "NET_ARP_CFG_NBR_CACHE          illegally #define'd in 'net_cfg.h' "
#error  "                               [MUST be  >= NET_ARP_CACHE_NBR_MIN]"
#error  "                               [     &&  <= NET_ARP_CACHE_NBR_MAX]"
#endif




#ifndef  NET_ARP_CFG_ADDR_FLTR_EN
#error  "NET_ARP_CFG_ADDR_FLTR_EN             not #define'd in 'net_cfg.h'"
#error  "                               [MUST be  DEF_DISABLED]           "
#error  "                               [     ||  DEF_ENABLED ]           "

#elif  ((NET_ARP_CFG_ADDR_FLTR_EN != DEF_DISABLED) && \
        (NET_ARP_CFG_ADDR_FLTR_EN != DEF_ENABLED ))
#error  "NET_ARP_CFG_ADDR_FLTR_EN       illegally #define'd in 'net_cfg.h'"
#error  "                               [MUST be  DEF_DISABLED]           "
#error  "                               [     ||  DEF_ENABLED ]           "
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                             MODULE END
*
* Note(s) : (1) See 'net_arp.h  MODULE'.
*********************************************************************************************************
*/

#endif                                                          /* End of ARP module include (see Note #1).             */
#endif

