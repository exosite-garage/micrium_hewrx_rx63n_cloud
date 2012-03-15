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
*                                    NETWORK INTERFACE MANAGEMENT
*
* Filename      : net_if.h
* Version       : V2.11.02
* Programmer(s) : ITJ
*                 EHS
*                 FGK
*                 SR
*********************************************************************************************************
* Note(s)       : (1) Network Interface modules located in the following network directory :
*
*                     (a) \<Network Protocol Suite>\IF\net_if.*
*                                                      net_if_*.*
*
*                             where
*                                     <Network Protocol Suite>      directory path for network protocol suite
*                                      net_if.*                     Generic  Network Interface Management
*                                                                       module files
*                                      net_if_*.*                   Specific Network Interface(s) module files
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*
* Note(s) : (1) (a) Loopback Interface Layer module is included regardless of whether the loopback interface
*                   is enabled (see 'net_cfg_net.h  NETWORK INTERFACE LAYER CONFIGURATION  Note #2a1').
*
*               (b) Specific interface module(s) are included only if devices for the interface(s) are
*                   configured (see 'net_cfg_net.h  NETWORK INTERFACE LAYER CONFIGURATION  Note #2a2').
*********************************************************************************************************
*/

#include  <net_if_loopback.h>                                   /* See Note #1a.                                        */
                                                                /* See Note #1b.                                        */
#ifdef     NET_IF_MODULE_ETHER_PRESENT
#include  <net_if_ether.h>
#endif


/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/

#if ((defined(NET_IF_MODULE)) && \
     (defined(NET_GLOBALS_EXT)))
#define  NET_IF_EXT
#else
#define  NET_IF_EXT  extern
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/

#define  NET_IF_MEM_TYPE_NONE                              0u
#define  NET_IF_MEM_TYPE_MAIN                              1u   /* Create dev's net bufs in main      mem.              */
#define  NET_IF_MEM_TYPE_DEDICATED                         2u   /* Create dev's net bufs in dedicated mem.              */


#define  NET_IF_PHY_LINK_TIMEOUT_MIN_MS                   50
#define  NET_IF_PHY_LINK_TIMEOUT_MAX_MS                60000
#define  NET_IF_PHY_LINK_TIMEOUT_DFLT_MS                 250

#define  NET_IF_PERF_MON_TIMEOUT_MIN_MS                   50
#define  NET_IF_PERF_MON_TIMEOUT_MAX_MS                60000
#define  NET_IF_PERF_MON_TIMEOUT_DFLT_MS                 250


#define  NET_IF_TX_SUSPEND_TIMEOUT_MIN_MS                  0
#define  NET_IF_TX_SUSPEND_TIMEOUT_MAX_MS                100



#define  NET_IF_LINK_UP                                  DEF_ON
#define  NET_IF_LINK_DOWN                                DEF_OFF


/*
*********************************************************************************************************
*                                NETWORK INTERFACE I/O CONTROL DEFINES
*********************************************************************************************************
*/

#define  NET_IF_IO_CTRL_NONE                               0u
#define  NET_IF_IO_CTRL_LINK_STATE_GET                    10u   /* Get        link state.                               */
#define  NET_IF_IO_CTRL_LINK_STATE_GET_INFO               11u   /* Get        link state info.                          */
#define  NET_IF_IO_CTRL_LINK_STATE_UPDATE                 12u   /* Update dev link state regs.                          */


/*
*********************************************************************************************************
*                         NETWORK INTERFACE PERFORMANCE MONITOR STATE DEFINES
*********************************************************************************************************
*/

#define  NET_IF_PERF_MON_STATE_NONE                        0u
#define  NET_IF_PERF_MON_STATE_STOP                       10u
#define  NET_IF_PERF_MON_STATE_START                      20u
#define  NET_IF_PERF_MON_STATE_RUN                        30u


/*
*********************************************************************************************************
*                                   NETWORK INTERFACE INDEX DEFINES
*
* Note(s) : (1) Since network data value macro's appropriately convert data values from any CPU addresses,
*               word-aligned or not; network receive & transmit packets are NOT required to ensure that
*               network packet headers (ARP/IP/UDP/TCP/etc.) & header members will locate on CPU word-
*               aligned addresses.  Therefore, network interface packets are NOT required to start on
*               any specific buffer indices.
*
*               See also 'net_util.h  NETWORK DATA VALUE MACRO'S           Note #2b'
*                      & 'net_buf.h   NETWORK BUFFER INDEX & SIZE DEFINES  Note #2'.
*********************************************************************************************************
*/
                                                                            /* See Note #1.                             */
#define  NET_IF_IX_RX                                    NET_BUF_DATA_IX_RX
#define  NET_IF_RX_IX                                    NET_IF_IX_RX       /* Req'd for backwards-compatibility.       */


/*$PAGE*/
/*
*********************************************************************************************************
*                                   NETWORK INTERFACE TYPE DEFINES
*
* Note(s) : (1) NET_IF_TYPE_&&& #define values specifically chosen as ASCII representations of the network
*               interface types.  Memory displays of network interfaces will display the network interface
*               TYPEs with their chosen ASCII names.
*********************************************************************************************************
*/

#define  NET_IF_TYPE_NONE                         CPU_TYPE_CREATE('N', 'O', 'N', 'E')
#define  NET_IF_TYPE_LOOPBACK                     CPU_TYPE_CREATE('L', 'P', 'B', 'K')
#define  NET_IF_TYPE_SERIAL                       CPU_TYPE_CREATE('S', 'E', 'R', ' ')
#define  NET_IF_TYPE_PPP                          CPU_TYPE_CREATE('P', 'P', 'P', ' ')
#define  NET_IF_TYPE_ETHER                        CPU_TYPE_CREATE('E', 'T', 'H', 'R')


/*
*********************************************************************************************************
*                              NETWORK DEVICE CONFIGURATION FLAG DEFINES
*
* Note(s) : (1) The following network device configuration flags are currently supported :
*
*********************************************************************************************************
*/
                                                                /* See Note #1.                                         */
#define  NET_DEV_CFG_FLAG_NONE                           DEF_BIT_NONE
#define  NET_DEV_CFG_FLAG_SWAP_OCTETS                    DEF_BIT_00

#define  NET_DEV_CFG_FLAG_MASK                          (NET_DEV_CFG_FLAG_NONE       | \
                                                         NET_DEV_CFG_FLAG_SWAP_OCTETS)


/*
*********************************************************************************************************
*                     NETWORK DEVICE INTERRUPT SERVICE ROUTINE (ISR) TYPE DEFINES
*
* Note(s) : (1) The following network device interrupt service routine (ISR) types are currently supported.
*
*               However, this may NOT be a complete or exhaustive list of device ISR type(s).  Therefore,
*               ANY addition, modification, or removal of network device ISR types SHOULD be appropriately
*               synchronized &/or updated with (ALL) device driver ISR handlers.
*********************************************************************************************************
*/

                                                                /* ---------------- NET DEV ISR TYPES ----------------- */
#define  NET_DEV_ISR_TYPE_NONE                             0u
#define  NET_DEV_ISR_TYPE_UNKNOWN                          1u   /* Dev                     ISR unknown.                 */

#define  NET_DEV_ISR_TYPE_RX                              10u   /* Dev rx                  ISR.                         */
#define  NET_DEV_ISR_TYPE_RX_RUNT                         11u   /* Dev rx runt             ISR.                         */
#define  NET_DEV_ISR_TYPE_RX_OVERRUN                      12u   /* Dev rx overrun          ISR.                         */

#define  NET_DEV_ISR_TYPE_TX_RDY                          20u   /* Dev tx rdy              ISR.                         */
#define  NET_DEV_ISR_TYPE_TX_COMPLETE                     21u   /* Dev tx complete         ISR.                         */
#define  NET_DEV_ISR_TYPE_TX_COLLISION_LATE               25u   /* Dev tx late   collision ISR.                         */
#define  NET_DEV_ISR_TYPE_TX_COLLISION_EXCESS             26u   /* Dev tx excess collision ISR.                         */

#define  NET_DEV_ISR_TYPE_JABBER                          30u   /* Dev jabber              ISR.                         */
#define  NET_DEV_ISR_TYPE_BABBLE                          31u   /* Dev babble              ISR.                         */

#define  NET_DEV_ISR_TYPE_PHY                             40u   /* Dev phy                 ISR.                         */


#define  NET_DEV_ISR_TYPE_TX_DONE                        NET_DEV_ISR_TYPE_TX_COMPLETE


/*$PAGE*/
/*
*********************************************************************************************************
*                                             DATA TYPES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                             NETWORK INTERFACE NUMBER QUANTITY DATA TYPE
*********************************************************************************************************
*/

typedef  CPU_INT08U  NET_IF_QTY;                                /* Defines max qty of net IFs to support.               */


/*
*********************************************************************************************************
*                    NETWORK DEVICE INTERRUPT SERVICE ROUTINE (ISR) TYPE DATA TYPE
*
* Note(s) : (1) 'NET_DEV_ISR_TYPE' pre-defined in 'net_type.h' PRIOR to all other network modules that
*                require network device ISR data type.
*********************************************************************************************************
*/

#if 0                                                           /* See Note #1.                                         */
typedef  CPU_INT08U  NET_DEV_ISR_TYPE;
#endif


/*
*********************************************************************************************************
*                        NETWORK INTERFACE PERFORMANCE MONITOR STATE DATA TYPE
*********************************************************************************************************
*/

typedef  CPU_INT08U  NET_IF_PERF_MON_STATE;


/*$PAGE*/
/*
*********************************************************************************************************
*                                 NETWORK INTERFACE NUMBER DATA TYPE
*
* Note(s) : (1) 'NET_IF_NBR' pre-defined in 'net_type.h' PRIOR to all other network modules that require
*                network interface number data type.
*
*           (2) (a) The following network interface number values are pre-#define'd in 'net_type.h'
*                   PRIOR to all other network modules that require network interface numbers values :
*
*                   (1) NET_IF_NBR_MIN
*                   (2) NET_IF_NBR_MIN
*
*               (b) The following network interface number values are pre-#define'd in 'net_cfg_net.h'
*                   PRIOR to all other network modules that require network interface number values :
*
*                   (1) NET_IF_NBR_IF_RESERVED
*                   (2) NET_IF_NBR_IF_TOT
*
*                   See also 'net_cfg_net.h  NETWORK INTERFACE LAYER CONFIGURATION  Note #3'.
*********************************************************************************************************
*/

#if 0                                                                           /* See Note #1.                         */
typedef  CPU_INT08U  NET_IF_NBR;
                                                                                /* See Note #2a.                        */
#define  NET_IF_NBR_MIN_VAL                              DEF_INT_08U_MIN_VAL
#define  NET_IF_NBR_MAX_VAL                              DEF_INT_08U_MAX_VAL
#endif

#if 0                                                                           /* See Note #2b.                        */
#define  NET_IF_NBR_IF_RESERVED                            1
#define  NET_IF_NBR_IF_TOT                              (NET_IF_CFG_MAX_NBR_IF + NET_IF_NBR_IF_RESERVED)
#endif

#define  NET_IF_NBR_BASE                                   0
#define  NET_IF_NBR_BASE_CFGD                           (NET_IF_NBR_BASE       + NET_IF_NBR_IF_RESERVED)


#define  NET_IF_NBR_NONE                                 NET_IF_NBR_MAX_VAL
#define  NET_IF_NBR_MIN                                  NET_IF_NBR_IF_RESERVED
#define  NET_IF_NBR_MAX                                 (NET_IF_NBR_NONE - 1)

                                                                                /* Reserved net IF nbrs :               */
#define  NET_IF_NBR_LOOPBACK                            (NET_IF_NBR_BASE + 0)
#define  NET_IF_NBR_LOCAL_HOST                           NET_IF_NBR_LOOPBACK
#define  NET_IF_NBR_WILDCARD                             NET_IF_NBR_NONE



/*
*********************************************************************************************************
*                               NETWORK INTERFACE QUEUE SIZE DATA TYPE
*
* Note(s) : (1) (a) 'NET_IF_Q_SIZE' pre-defined in 'net_type.h' PRIOR to all other network modules that 
*                    require network interface queue size data type.
*
*               (b) The following network interface queue size values are pre-#define'd in 'net_type.h'
*                   PRIOR to all other network modules that require network interface numbers values :
*
*                   (1) NET_IF_Q_SIZE_MIN
*                   (2) NET_IF_Q_SIZE_MAX
*********************************************************************************************************
*/

#if 0                                                           /* See Note #1.                                         */
typedef  NET_BUF_QTY  NET_IF_Q_SIZE;                            /* Defines max size of net IF q's to support.           */

#define  NET_IF_Q_SIZE_MIN                               NET_BUF_NBR_MIN
#define  NET_IF_Q_SIZE_MAX                               NET_BUF_NBR_MAX
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                     NETWORK INTERFACE DATA TYPE
*
* Note(s) : (1) A network interface's hardware MTU is computed as the minimum of the largest buffer size
*               configured for a specific interface & the configured MTU for the interface device.
*
*           (2) Network interface initialization flag set when an interface has been successfully added
*               & initialized to the interface table.  Once set, this flag is never cleared since the
*               removal of interfaces is currently not allowed.
*
*           (3) Network interface enable/disable independent of physical hardware link state of the
*               interface's associated device.
**********************************************************************************************************
*/

                                                    /* ---------------------------- NET IF ---------------------------- */
struct  net_if {
    NET_TYPE                Type;                   /* IF type (Loopback, Ethernet, PPP, Serial device, etc.).          */
    NET_IF_NBR              Nbr;                    /* IF nbr.                                                          */

    CPU_BOOLEAN             Init;                   /* IF init     status (see Note #2).                                */
    CPU_BOOLEAN             En;                     /* IF en/dis   status (see Note #3).                                */

    CPU_BOOLEAN             Link;                   /* IF Phy link status.                                              */
    NET_MTU                 TOER;                    /* IF MTU             (see Note #1).                                */

    void                   *IF_API;                 /* Ptr to IF's     API  fnct tbl.                                   */
    void                   *IF_Data;                /* Ptr to IF's     data area.                                       */
    void                   *Dev_API;                /* Ptr to IF's dev API  fnct tbl.                                   */
    void                   *Dev_BSP;                /* Ptr to IF's dev BSP  fnct tbl.                                   */
    void                   *Dev_Cfg;                /* Ptr to IF's dev cfg       tbl.                                   */
    void                   *Dev_Data;               /* Ptr to IF's dev data area.                                       */
    void                   *Phy_API;                /* Ptr to IF's phy API  fnct tbl.                                   */
    void                   *Phy_Cfg;                /* Ptr to IF's phy cfg       tbl.                                   */

#if (NET_CTR_CFG_STAT_EN == DEF_ENABLED)
    NET_IF_PERF_MON_STATE   PerfMonState;           /* Perf mon state.                                                  */
    NET_TS_MS               PerfMonTS_Prev_ms;      /* Perf mon prev TS (in ms).                                        */
#endif

#if (NET_CFG_LOAD_BAL_EN == DEF_ENABLED)
    NET_STAT_CTR            RxPktCtr;               /* Indicates nbr of rx pkts q'd to IF but NOT yet handled.          */
    NET_STAT_CTR            TxSuspendCtr;           /* Indicates nbr of tx conn's for  IF currently suspended.          */
#endif
};


/*$PAGE*/
/*
*********************************************************************************************************
*                           GENERIC NETWORK DEVICE CONFIGURATION DATA TYPE
*
* Note(s) : (1) The generic network device configuration data type is a template/subset for all specific 
*               network device configuration data types.  Each specific network device configuration 
*               data type MUST define ALL generic network device configuration parameters, synchronized 
*               in both the sequential order & data type of each parameter.
*
*               Thus, ANY modification to the sequential order or data types of generic configuration 
*               parameters MUST be appropriately synchronized between the generic network device 
*               configuration data type & ALL specific network device configuration data types.
*********************************************************************************************************
*/

                                                    /* ------------------------- NET DEV CFG -------------------------- */
struct  net_dev_cfg {
    NET_TYPE            RxBufPoolType;              /* Rx buf mem pool type :                                           */
                                                    /*   NET_IF_MEM_TYPE_MAIN        bufs alloc'd from main      mem    */
                                                    /*   NET_IF_MEM_TYPE_DEDICATED   bufs alloc'd from dedicated mem    */
    NET_BUF_SIZE        RxBufLargeSize;             /* Size  of dev rx large buf data areas (in octets).                */
    NET_BUF_QTY         RxBufLargeNbr;              /* Nbr   of dev rx large buf data areas.                            */
    NET_BUF_SIZE        RxBufAlignOctets;           /* Align of dev rx       buf data areas (in octets).                */
    NET_BUF_SIZE        RxBufIxOffset;              /* Offset from base ix to rx data into data area (in octets).       */


    NET_TYPE            TxBufPoolType;              /* Tx buf mem pool type :                                           */
                                                    /*   NET_IF_MEM_TYPE_MAIN        bufs alloc'd from main      mem    */
                                                    /*   NET_IF_MEM_TYPE_DEDICATED   bufs alloc'd from dedicated mem    */
    NET_BUF_SIZE        TxBufLargeSize;             /* Size  of dev tx large buf data areas (in octets).                */
    NET_BUF_QTY         TxBufLargeNbr;              /* Nbr   of dev tx large buf data areas.                            */
    NET_BUF_SIZE        TxBufSmallSize;             /* Size  of dev tx small buf data areas (in octets).                */
    NET_BUF_QTY         TxBufSmallNbr;              /* Nbr   of dev tx small buf data areas.                            */
    NET_BUF_SIZE        TxBufAlignOctets;           /* Align of dev tx       buf data areas (in octets).                */
    NET_BUF_SIZE        TxBufIxOffset;              /* Offset from base ix to tx data from data area (in octets).       */


    CPU_ADDR            MemAddr;                    /* Base addr of (dev's) dedicated mem, if avail.                    */
    CPU_ADDR            MemSize;                    /* Size      of (dev's) dedicated mem, if avail.                    */


    NET_DEV_CFG_FLAGS   Flags;                      /* Opt'l bit flags.                                                 */
};


/*$PAGE*/
/*
*********************************************************************************************************
*                               GENERIC NETWORK INTERFACE API DATA TYPE
*
* Note(s) : (1) The generic network interface application programming interface (API) data type is a 
*               template/subset for all specific network interface API data types.
*
*               (a) Each specific network interface API data type definition MUST define ALL generic 
*                   network interface API functions, synchronized in both the sequential order of the 
*                   functions & argument lists for each function.
*
*                   Thus, ANY modification to the sequential order or argument lists of the generic API 
*                   functions MUST be appropriately synchronized between the generic network interface 
*                   API data type & ALL specific network interface API data type definitions/instantiations.
*
*               (b) ALL API functions SHOULD be defined with NO NULL functions for all specific network 
*                   interface API instantiations.  Any specific network interface API instantiation that 
*                   does define any NULL API functions MUST ensure that NO NULL API functions are called 
*                   for the specific network interface.
*
*                   Instead of  NULL functions, a specific network interface API instantiation COULD 
*                   define empty API functions that return error code 'NET_IF_ERR_API_DIS'.
*********************************************************************************************************
*/

                                                                                    /* ---------- NET IF API ---------- */
                                                                                    /* Net IF API fnct ptrs :           */
struct  net_if_api {
                                                                                    /*   Init/add                       */
    void         (*Add)                      (NET_IF             *pif,
                                              NET_ERR            *perr);

                                                                                    /*   Start                          */
    void         (*Start)                    (NET_IF             *pif,
                                              NET_ERR            *perr);

                                                                                    /*   Stop                           */
    void         (*Stop)                     (NET_IF             *pif,
                                              NET_ERR            *perr);


                                                                                    /*   Rx                             */
    void         (*Rx)                       (NET_IF             *pif,
                                              NET_BUF            *pbuf,
                                              NET_ERR            *perr);

                                                                                    /*   Tx                             */
    void         (*Tx)                       (NET_IF             *pif,
                                              NET_BUF            *pbuf,
                                              NET_ERR            *perr);


/*$PAGE*/
                                                                                    /*   Hw addr get                    */
    void         (*AddrHW_Get)               (NET_IF             *pif,
                                              CPU_INT08U         *paddr,
                                              CPU_INT08U         *addr_len,
                                              NET_ERR            *perr);

                                                                                    /*   Hw addr set                    */
    void         (*AddrHW_Set)               (NET_IF             *pif,
                                              CPU_INT08U         *paddr,
                                              CPU_INT08U          addr_len,
                                              NET_ERR            *perr);

                                                                                    /*   Hw addr valid                  */
    CPU_BOOLEAN  (*AddrHW_IsValid)           (NET_IF             *pif,
                                              CPU_INT08U         *paddr_hw);


                                                                                    /*   Multicast addr add             */
    void         (*AddrMulticastAdd)         (NET_IF             *pif,
                                              CPU_INT08U         *paddr_protocol,
                                              CPU_INT08U          paddr_protocol_len,
                                              NET_PROTOCOL_TYPE   addr_protocol_type,
                                              NET_ERR            *perr);

                                                                                    /*   Multicast addr remove          */  
    void         (*AddrMulticastRemove)      (NET_IF             *pif,
                                              CPU_INT08U         *paddr_protocol,
                                              CPU_INT08U          paddr_protocol_len,
                                              NET_PROTOCOL_TYPE   addr_protocol_type,
                                              NET_ERR            *perr);

                                                                                    /*   Multicast addr protocol-to-hw  */
    void         (*AddrMulticastProtocolToHW)(NET_IF             *pif,
                                              CPU_INT08U         *paddr_protocol,
                                              CPU_INT08U          addr_protocol_len,
                                              NET_PROTOCOL_TYPE   addr_protocol_type,
                                              CPU_INT08U         *paddr_hw,
                                              CPU_INT08U         *paddr_hw_len,
                                              NET_ERR            *perr);


                                                                                    /*   Buf cfg validation             */
    void         (*BufPoolCfgValidate)       (NET_IF             *pif,
                                              NET_ERR            *perr);


                                                                                    /*   MTU set                        */
    void         (*MTU_Set)                  (NET_IF             *pif,
                                              NET_MTU             mtu,
                                              NET_ERR            *perr);


                                                                                    /*   Get pkt hdr size               */
    CPU_INT16U   (*GetPktSizeHdr)            (NET_IF             *pif);

                                                                                    /*   Get pkt min size               */
    CPU_INT16U   (*GetPktSizeMin)            (NET_IF             *pif);



                                                                                    /*   ISR handler                    */
    void         (*ISR_Handler)              (NET_IF             *pif,
                                              NET_DEV_ISR_TYPE    type,
                                              NET_ERR            *perr);


                                                                                    /*   I/O ctrl                       */
    void         (*IO_Ctrl)                  (NET_IF             *pif,
                                              CPU_INT08U          opt,
                                              void               *p_data,
                                              NET_ERR            *perr);
};


/*$PAGE*/
/*
*********************************************************************************************************
*                                GENERIC NETWORK DEVICE API DATA TYPE
*
* Note(s) : (1) The generic network device application programming interface (API) data type is a template/
*               subset for all specific network device API data types.
*
*               (a) Each specific network device API data type definition MUST define ALL generic network 
*                   device API functions, synchronized in both the sequential order of the functions & 
*                   argument lists for each function.
*
*                   Thus, ANY modification to the sequential order or argument lists of the generic API 
*                   functions MUST be appropriately synchronized between the generic network device API 
*                   data type & ALL specific network device API data type definitions/instantiations.
*
*                   However, specific network device API data type definitions/instantiations MAY include 
*                   additional API functions after all generic network device API functions.
*
*               (b) ALL API functions MUST be defined with NO NULL functions for all specific network 
*                   device API instantiations.  Any specific network device API instantiation that does 
*                   NOT require a specific API's functionality MUST define an empty API function which 
*                   may need to return an appropriate error code.
*********************************************************************************************************
*/

                                                                /* -------------------- NET DEV API ------------------- */
                                                                /* Net dev API fnct ptrs :                              */
typedef  struct  net_dev_api {
                                                                /*   Init                                               */
    void  (*Init) (NET_IF       *pif,
                   NET_ERR      *perr);
                                                                /*   Start                                              */
    void  (*Start)(NET_IF       *pif,
                   NET_ERR      *perr);
                                                                /*   Stop                                               */
    void  (*Stop) (NET_IF       *pif,
                   NET_ERR      *perr);

                                                                /*   Rx                                                 */
    void  (*Rx)   (NET_IF       *pif,
                   CPU_INT08U  **p_data,
                   CPU_INT16U   *size,
                   NET_ERR      *perr);
                                                                /*   Tx                                                 */
    void  (*Tx)   (NET_IF       *pif,
                   CPU_INT08U   *p_data,
                   CPU_INT16U    size,
                   NET_ERR      *perr);
} NET_DEV_API;


/*$PAGE*/
/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/

NET_IF_EXT  NET_IF          NetIF_Tbl[NET_IF_NBR_IF_TOT];       /* Net IF tbl.                                          */
NET_IF_EXT  NET_IF_NBR      NetIF_NbrBase;                      /* Net IF tbl base nbr.                                 */
NET_IF_EXT  NET_IF_NBR      NetIF_NbrNext;                      /* Net IF tbl next nbr to cfg.                          */


NET_IF_EXT  NET_STAT_CTR    NetIF_RxTaskPktCtr;                 /*        Net IF rx task q'd pkts ctr.                  */

NET_IF_EXT  NET_IF_Q_SIZE   NetIF_RxQ_SizeCfgd;                 /*        Net IF rx q cfg'd size.                       */
NET_IF_EXT  NET_IF_Q_SIZE   NetIF_RxQ_SizeCfgdRem;              /*        Net IF rx q cfg'd size rem'ing.               */


NET_IF_EXT  NET_BUF        *NetIF_TxListHead;                   /* Ptr to net IF tx list head.                          */
NET_IF_EXT  NET_BUF        *NetIF_TxListTail;                   /* Ptr to net IF tx list tail.                          */

NET_IF_EXT  NET_IF_Q_SIZE   NetIF_TxDeallocQ_SizeCfgd;          /*        Net IF tx dealloc cfg'd size.                 */
NET_IF_EXT  NET_IF_Q_SIZE   NetIF_TxDeallocQ_SizeCfgdRem;       /*        Net IF tx dealloc cfg'd size rem'ing.         */


NET_IF_EXT  NET_TMR        *NetIF_PhyLinkStateTmr;              /* Phy link state tmr.                                  */
NET_IF_EXT  CPU_INT16U      NetIF_PhyLinkStateTimeout_ms;       /* Phy link state timeout (in ms).                      */

#if (NET_CTR_CFG_STAT_EN == DEF_ENABLED)
NET_IF_EXT  NET_TMR        *NetIF_PerfMonTmr;                   /* Perf mon       tmr.                                  */
NET_IF_EXT  CPU_INT16U      NetIF_PerfMonTimeout_ms;            /* Perf mon       timeout (in ms).                      */
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/


void          NetIF_Init                     (NET_ERR            *perr);


                                                                            /* -------------- CFG FNCTS --------------- */

CPU_BOOLEAN   NetIF_CfgPhyLinkPeriod         (CPU_INT16U          timeout_ms);

#if (NET_CTR_CFG_STAT_EN == DEF_ENABLED)
CPU_BOOLEAN   NetIF_CfgPerfMonPeriod         (CPU_INT16U          timeout_ms);
#endif



                                                                            /* -------------- API FNCTS --------------- */

NET_IF_NBR    NetIF_Add                      (void               *if_api,
                                              void               *dev_api,
                                              void               *dev_bsp,
                                              void               *dev_cfg,
                                              void               *phy_api,
                                              void               *phy_cfg,
                                              NET_ERR            *perr);


void          NetIF_Start                    (NET_IF_NBR          if_nbr,
                                              NET_ERR            *perr);

void          NetIF_Stop                     (NET_IF_NBR          if_nbr,
                                              NET_ERR            *perr);



NET_IF       *NetIF_Get                      (NET_IF_NBR          if_nbr,
                                              NET_ERR            *perr);

NET_IF_NBR    NetIF_GetDflt                  (void);


void         *NetIF_GetRxDataAlignPtr        (NET_IF_NBR          if_nbr,
                                              void               *p_data,
                                              NET_ERR            *perr);

void         *NetIF_GetTxDataAlignPtr        (NET_IF_NBR          if_nbr,
                                              void               *p_data,
                                              NET_ERR            *perr);



                                                                            /* ------------- STATUS FNCTS ------------- */

CPU_BOOLEAN   NetIF_IsValid                  (NET_IF_NBR          if_nbr,
                                              NET_ERR            *perr);

CPU_BOOLEAN   NetIF_IsValidHandler           (NET_IF_NBR          if_nbr,
                                              NET_ERR            *perr);


CPU_BOOLEAN   NetIF_IsValidCfgd              (NET_IF_NBR          if_nbr,
                                              NET_ERR            *perr);

CPU_BOOLEAN   NetIF_IsValidCfgdHandler       (NET_IF_NBR          if_nbr,
                                              NET_ERR            *perr);


CPU_BOOLEAN   NetIF_IsEn                     (NET_IF_NBR          if_nbr,
                                              NET_ERR            *perr);

CPU_BOOLEAN   NetIF_IsEnHandler              (NET_IF_NBR          if_nbr,
                                              NET_ERR            *perr);


CPU_BOOLEAN   NetIF_IsEnCfgd                 (NET_IF_NBR          if_nbr,
                                              NET_ERR            *perr);

CPU_BOOLEAN   NetIF_IsEnCfgdHandler          (NET_IF_NBR          if_nbr,
                                              NET_ERR            *perr);



/*$PAGE*/
                                                                            /* -------------- MGMT FNCTS -------------- */

void          NetIF_AddrHW_Get               (NET_IF_NBR          if_nbr,
                                              CPU_INT08U         *paddr_hw,
                                              CPU_INT08U         *paddr_len,
                                              NET_ERR            *perr);

void          NetIF_AddrHW_GetHandler        (NET_IF_NBR          if_nbr,
                                              CPU_INT08U         *paddr_hw,
                                              CPU_INT08U         *paddr_len,
                                              NET_ERR            *perr);


void          NetIF_AddrHW_Set               (NET_IF_NBR          if_nbr,
                                              CPU_INT08U         *paddr_hw,
                                              CPU_INT08U          addr_len,
                                              NET_ERR            *perr);

void          NetIF_AddrHW_SetHandler        (NET_IF_NBR          if_nbr,
                                              CPU_INT08U         *paddr_hw,
                                              CPU_INT08U          addr_len,
                                              NET_ERR            *perr);


CPU_BOOLEAN   NetIF_AddrHW_IsValid           (NET_IF_NBR          if_nbr,
                                              CPU_INT08U         *paddr_hw,
                                              NET_ERR            *perr);

CPU_BOOLEAN   NetIF_AddrHW_IsValidHandler    (NET_IF_NBR          if_nbr,
                                              CPU_INT08U         *paddr_hw,
                                              NET_ERR            *perr);


#ifdef  NET_MULTICAST_PRESENT
void          NetIF_AddrMulticastAdd         (NET_IF_NBR          if_nbr,
                                              CPU_INT08U         *paddr_protocol,
                                              CPU_INT08U          addr_protocol_len,
                                              NET_PROTOCOL_TYPE   addr_protocol_type,
                                              NET_ERR            *perr);

void          NetIF_AddrMulticastRemove      (NET_IF_NBR          if_nbr,
                                              CPU_INT08U         *paddr_protocol,
                                              CPU_INT08U          addr_protocol_len,
                                              NET_PROTOCOL_TYPE   addr_protocol_type,
                                              NET_ERR            *perr);

void          NetIF_AddrMulticastProtocolToHW(NET_IF_NBR          if_nbr,
                                              CPU_INT08U         *paddr_protocol,
                                              CPU_INT08U          addr_protocol_len,
                                              NET_PROTOCOL_TYPE   addr_protocol_type,
                                              CPU_INT08U         *paddr_hw,
                                              CPU_INT08U         *paddr_hw_len,
                                              NET_ERR            *perr);
#endif



NET_MTU       NetIF_MTU_Get                  (NET_IF_NBR          if_nbr,
                                              NET_ERR            *perr);

NET_MTU       NetIF_MTU_GetProtocol          (NET_IF_NBR          if_nbr,
                                              NET_PROTOCOL_TYPE   protocol,
                                              NET_ERR            *perr);

void          NetIF_MTU_Set                  (NET_IF_NBR          if_nbr,
                                              NET_MTU             mtu,
                                              NET_ERR            *perr);


CPU_INT16U    NetIF_GetPktSizeMin            (NET_IF_NBR          if_nbr,
                                              NET_ERR            *perr);



void          NetIF_ISR_Handler              (NET_IF_NBR          if_nbr,
                                              NET_DEV_ISR_TYPE    type,
                                              NET_ERR            *perr);


CPU_BOOLEAN   NetIF_LinkStateGet             (NET_IF_NBR          if_nbr,
                                              NET_ERR            *perr);

CPU_BOOLEAN   NetIF_LinkStateWaitUntilUp     (NET_IF_NBR          if_nbr,
                                              CPU_INT16U          retry_max,
                                              CPU_INT32U          time_dly_ms,
                                              NET_ERR            *perr);


void          NetIF_IO_Ctrl                  (NET_IF_NBR          if_nbr,
                                              CPU_INT08U          opt,
                                              void               *p_data,
                                              NET_ERR            *perr);


/*$PAGE*/
                                                                            /* --------------- RX FNCTS --------------- */

void          NetIF_RxTaskHandler            (void);

void          NetIF_RxQ_SizeCfg              (NET_IF_Q_SIZE       size);


void          NetIF_RxPktInc                 (NET_IF_NBR          if_nbr);

CPU_BOOLEAN   NetIF_RxPktIsAvail             (NET_IF_NBR          if_nbr,
                                              NET_CTR             rx_chk_nbr);


                                                                            /* --------------- TX FNCTS --------------- */

void          NetIF_Tx                       (NET_BUF            *pbuf_list,
                                              NET_ERR            *perr);

void          NetIF_TxDeallocTaskHandler     (void);

void          NetIF_TxDeallocQ_SizeCfg       (NET_IF_Q_SIZE       size);


void          NetIF_TxSuspend                (NET_IF_NBR          if_nbr);


/*$PAGE*/
/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*                                      DEFINED IN OS'S  net_os.c
*********************************************************************************************************
*/

                                                                            /* ----------- NET DEV OS FNCTS ----------- */
void          NetOS_Dev_Init                 (NET_IF_NBR   if_nbr,          /* Create dev objs & tasks.                 */
                                              NET_ERR     *perr);


void          NetOS_Dev_CfgTxRdySignal       (NET_IF_NBR   if_nbr,          /* Cfg     dev tx rdy sem cnt.              */
                                              CPU_INT16U   cnt,
                                              NET_ERR     *perr);

void          NetOS_Dev_TxRdyWait            (NET_IF_NBR   if_nbr,          /* Wait on dev tx empty signal.             */
                                              NET_ERR     *perr);

void          NetOS_Dev_TxRdySignal          (NET_IF_NBR   if_nbr);         /* Signal  dev tx empty.                    */



                                                                            /* ----------- NET IF  OS FNCTS ----------- */
void          NetOS_IF_Init                  (NET_ERR     *perr);           /* Create net IF objs & tasks.              */


NET_IF_NBR    NetOS_IF_RxTaskWait            (NET_ERR     *perr);           /* Wait for  rx signal from dev rx ISR(s).  */

void          NetOS_IF_RxTaskSignal          (NET_IF_NBR   if_nbr,          /* Signal IF rx rdy    from dev rx ISR(s).  */
                                              NET_ERR     *perr);


CPU_INT08U   *NetOS_IF_TxDeallocTaskWait     (NET_ERR     *perr);           /* Wait for dev tx comp signal.             */

void          NetOS_IF_TxDeallocTaskPost     (CPU_INT08U  *pbuf_data,       /* Post to tx dealloc Q.                    */
                                              NET_ERR     *perr);



#if (NET_CFG_LOAD_BAL_EN == DEF_ENABLED)
void          NetOS_IF_TxSuspendWait         (NET_IF_NBR   if_nbr);         /* Wait until tx suspend is signaled.       */

void          NetOS_IF_TxSuspendSignal       (NET_IF_NBR   if_nbr);         /* Signal     tx suspend.                   */


void          NetOS_IF_TxSuspendTimeoutSet   (NET_IF_NBR   if_nbr,          /* Set        tx suspend timeout.           */
                                              CPU_INT32U   timeout_ms,
                                              NET_ERR     *perr);

CPU_INT32U    NetOS_IF_TxSuspendTimeoutGet_ms(NET_IF_NBR   if_nbr,          /* Get        tx suspend timeout.           */
                                              NET_ERR     *perr);
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                        CONFIGURATION ERRORS
*********************************************************************************************************
*/

#ifndef  NET_IF_CFG_MAX_NBR_IF
#error  "NET_IF_CFG_MAX_NBR_IF                   not #define'd in 'net_cfg.h'"
#error  "                                  [MUST be  >= NET_IF_NBR_MIN_VAL]  "

#elif   (DEF_CHK_VAL_MIN(NET_IF_CFG_MAX_NBR_IF,       \
                         NET_IF_NBR_MIN_VAL) != DEF_OK)
#error  "NET_IF_CFG_MAX_NBR_IF             illegally #define'd in 'net_cfg.h'"
#error  "                                  [MUST be  >= NET_IF_NBR_MIN_VAL]  "
#endif


                                                            /* Correctly configured in 'net_cfg_net.h'; DO NOT MODIFY.  */
#ifndef  NET_IF_NBR_IF_TOT
#error  "NET_IF_NBR_IF_TOT                       not #define'd in 'net_cfg_net.h'"
#error  "                                  [MUST be  >= NET_IF_NBR_MIN]          "
#error  "                                  [     &&  <= NET_IF_NBR_MAX]          "

#elif   (DEF_CHK_VAL(NET_IF_NBR_IF_TOT,       \
                     NET_IF_NBR_MIN,          \
                     NET_IF_NBR_MAX) != DEF_OK)
#error  "NET_IF_NBR_IF_TOT                 illegally #define'd in 'net_cfg_net.h'"
#error  "                                  [MUST be  >= NET_IF_NBR_MIN]          "
#error  "                                  [     &&  <= NET_IF_NBR_MAX]          "
#endif




#if    ((NET_IF_CFG_LOOPBACK_EN == DEF_DISABLED) && \
        (NET_IF_CFG_ETHER_EN    == DEF_DISABLED))
#error  "NET_IF_CFG_LOOPBACK_EN &&                                           "
#error  "NET_IF_CFG_ETHER_EN               illegally #define'd in 'net_cfg.h'"
#error  "NET_IF_CFG_LOOPBACK_EN ||                                           "
#error  "NET_IF_CFG_ETHER_EN               [MUST be  DEF_ENABLED ]           "
#endif




#ifndef  NET_IF_CFG_ADDR_FLTR_EN
#error  "NET_IF_CFG_ADDR_FLTR_EN                 not #define'd in 'net_cfg.h'"
#error  "                                  [MUST be  DEF_DISABLED]           "
#error  "                                  [     ||  DEF_ENABLED ]           "

#elif  ((NET_IF_CFG_ADDR_FLTR_EN != DEF_DISABLED) && \
        (NET_IF_CFG_ADDR_FLTR_EN != DEF_ENABLED ))
#error  "NET_IF_CFG_ADDR_FLTR_EN           illegally #define'd in 'net_cfg.h'"
#error  "                                  [MUST be  DEF_DISABLED]           "
#error  "                                  [     ||  DEF_ENABLED ]           "
#endif




#if     (NET_CFG_LOAD_BAL_EN == DEF_ENABLED)

#ifndef  NET_IF_CFG_TX_SUSPEND_TIMEOUT_MS
#error  "NET_IF_CFG_TX_SUSPEND_TIMEOUT_MS        not #define'd in 'net_cfg.h'            "
#error  "                                  [MUST be  >= NET_IF_TX_SUSPEND_TIMEOUT_MIN_MS]"
#error  "                                  [     &&  <= NET_IF_TX_SUSPEND_TIMEOUT_MAX_MS]"

#elif   (DEF_CHK_VAL(NET_IF_CFG_TX_SUSPEND_TIMEOUT_MS,          \
                     NET_IF_TX_SUSPEND_TIMEOUT_MIN_MS,          \
                     NET_IF_TX_SUSPEND_TIMEOUT_MAX_MS) != DEF_OK)
#error  "NET_IF_CFG_TX_SUSPEND_TIMEOUT_MS  illegally #define'd in 'net_cfg.h'            "
#error  "                                  [MUST be  >= NET_IF_TX_SUSPEND_TIMEOUT_MIN_MS]"
#error  "                                  [     &&  <= NET_IF_TX_SUSPEND_TIMEOUT_MAX_MS]"
#endif

#endif



/*$PAGE*/
                                                            /* Correctly configured in 'net_cfg_net.h'; DO NOT MODIFY.  */
#ifndef  NET_IF_HDR_SIZE_MIN
#error  "NET_IF_HDR_SIZE_MIN                     not #define'd in 'net_cfg_net.h'"
#error  "                                  [MUST be  >= 0]                       "

#elif   (DEF_CHK_VAL_MIN(NET_IF_HDR_SIZE_MIN, 0) != DEF_OK)
#error  "NET_IF_HDR_SIZE_MIN               illegally #define'd in 'net_cfg_net.h'"
#error  "                                  [MUST be  >= 0]                       "
#endif


#ifndef  NET_IF_HDR_SIZE_MAX
#error  "NET_IF_HDR_SIZE_MAX                     not #define'd in 'net_cfg_net.h'"
#error  "                                  [MUST be  >= 0]                       "

#elif   (DEF_CHK_VAL_MIN(NET_IF_HDR_SIZE_MAX, 0) != DEF_OK)
#error  "NET_IF_HDR_SIZE_MAX               illegally #define'd in 'net_cfg_net.h'"
#error  "                                  [MUST be  >= 0]                       "
#endif

