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
*                                  NETWORK LOOPBACK INTERFACE LAYER
*
* Filename      : net_if_loopback.h
* Version       : V2.11.02
* Programmer(s) : EHS
*                 ITJ
*********************************************************************************************************
* Note(s)       : (1) Supports internal loopback communication.
*
*                     (a) Internal loopback interface is NOT linked to, associated with, or handled by 
*                         any physical network device(s) & therefore has NO physical protocol overhead.
*
*                 (2) REQUIREs the following network protocol files in network directories :
*
*                     (a) Network Interface Layer located in the following network directory :
*
*                             \<Network Protocol Suite>\IF\
*
*                              where
*                                      <Network Protocol Suite>    directory path for network protocol suite
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) Loopback Interface Layer module is included regardless of whether the loopback interface 
*               is enabled (see 'net_cfg_net.h  NETWORK INTERFACE LAYER CONFIGURATION  Note #2a1').
*
*           (2) The following loopback-module-present configuration value MUST be pre-#define'd in
*               'net_cfg_net.h' PRIOR to all other network modules that require loopback configuration
*               (see 'net_cfg_net.h  NETWORK INTERFACE LAYER CONFIGURATION  Note #2a1') :
*
*                   NET_IF_MODULE_LOOPBACK_PRESENT
*********************************************************************************************************
*/

#ifdef  NET_IF_MODULE_LOOPBACK_PRESENT                          /* See Note #2.                                         */


/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/

#if ((defined(NET_IF_MODULE_LOOPBACK)) && \
     (defined(NET_GLOBALS_EXT)))
#define  NET_IF_LOOPBACK_EXT
#else
#define  NET_IF_LOOPBACK_EXT  extern
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                  NETWORK INTERFACE HEADER DEFINES
*
* Note(s) : (1) The following network interface value MUST be pre-#define'd in 'net_def.h' PRIOR to 
*               'net_cfg.h' so that the developer can configure the network interface for the correct 
*               network interface layer values (see 'net_def.h  NETWORK INTERFACE LAYER DEFINES' & 
*               'net_cfg_net.h  NETWORK INTERFACE LAYER CONFIGURATION  Note #4') :
*
*               (a) NET_IF_HDR_SIZE_LOOPBACK               0
*
*          !!!! Redesign for dynamically-configured network interface types?
*********************************************************************************************************
*/

#if 0                                                           
#define  NET_IF_HDR_SIZE_LOOPBACK                          0    /* See Note #1a.                                        */
#endif

#define  NET_IF_HDR_SIZE_LOOPBACK_MIN                    NET_IF_HDR_SIZE_LOOPBACK
#define  NET_IF_HDR_SIZE_LOOPBACK_MAX                    NET_IF_HDR_SIZE_LOOPBACK


/*
*********************************************************************************************************
*              NETWORK LOOPBACK INTERFACE SIZE & MAXIMUM TRANSMISSION UNIT (MTU) DEFINES
*
* Note(s) : (1) The loopback interface is NOT linked to, associated with, or handled by any physical 
*               network device(s) & therefore has NO physical protocol overhead.
*
*               See also 'net_if_loopback.h  Note #1a'.
*********************************************************************************************************
*/
                                                                /* See Note #1.                                         */
#define  NET_IF_MTU_LOOPBACK                             NET_MTU_MAX_VAL
#define  NET_IF_LOOPBACK_SIZE_MIN                          0

#define  NET_IF_LOOPBACK_BUF_SIZE_MIN                   (NET_IF_LOOPBACK_SIZE_MIN + NET_BUF_DATA_SIZE_MIN - NET_BUF_DATA_PROTOCOL_HDR_SIZE_MIN)


/*$PAGE*/
/*
*********************************************************************************************************
*                                             DATA TYPES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                          NETWORK LOOPBACK INTERFACE CONFIGURATION DATA TYPE
*
* Note(s) : (1) The network loopback interface configuration data type is a specific instantiation of a 
*               network device configuration data type.  ALL specific network device configuration data 
*               types MUST be defined with ALL of the generic network device configuration data type's 
*               configuration parameters, synchronized in both the sequential order & data type of each 
*               parameter.
*
*               Thus, ANY modification to the sequential order or data types of generic configuration 
*               parameters MUST be appropriately synchronized between the generic network device 
*               configuration data type & the network loopback interface configuration data type.
*
*               See also 'net_if.h  GENERIC NETWORK DEVICE CONFIGURATION DATA TYPE  Note #1'.
*********************************************************************************************************
*/

                                                    /* --------------------- NET LOOPBACK IF CFG ---------------------- */
typedef  struct  net_if_cfg_loopback {
                                                    /* ---------------- GENERIC  LOOPBACK CFG MEMBERS ----------------- */
    NET_TYPE            RxBufPoolType;              /* Rx buf mem pool type :                                           */
                                                    /*   NET_IF_MEM_TYPE_MAIN        bufs alloc'd from main      mem    */
                                                    /*   NET_IF_MEM_TYPE_DEDICATED   bufs alloc'd from dedicated mem    */
    NET_BUF_SIZE        RxBufLargeSize;             /* Size  of loopback IF large buf data areas     (in octets).       */
    NET_BUF_QTY         RxBufLargeNbr;              /* Nbr   of loopback IF large buf data areas.                       */
    NET_BUF_SIZE        RxBufAlignOctets;           /* Align of loopback IF       buf data areas     (in octets).       */
    NET_BUF_SIZE        RxBufIxOffset;              /* Offset from base ix to rx data into data area (in octets).       */


    NET_TYPE            TxBufPoolType;              /* Tx buf mem pool type :                                           */
                                                    /*   NET_IF_MEM_TYPE_MAIN        bufs alloc'd from main      mem    */
                                                    /*   NET_IF_MEM_TYPE_DEDICATED   bufs alloc'd from dedicated mem    */
    NET_BUF_SIZE        TxBufLargeSize;             /* Size  of loopback IF large buf data areas     (in octets).       */
    NET_BUF_QTY         TxBufLargeNbr;              /* Nbr   of loopback IF large buf data areas.                       */
    NET_BUF_SIZE        TxBufSmallSize;             /* Size  of loopback IF small buf data areas     (in octets).       */
    NET_BUF_QTY         TxBufSmallNbr;              /* Nbr   of loopback IF small buf data areas.                       */
    NET_BUF_SIZE        TxBufAlignOctets;           /* Align of loopback IF       buf data areas     (in octets).       */
    NET_BUF_SIZE        TxBufIxOffset;              /* Offset from base ix to tx data from data area (in octets).       */


    CPU_ADDR            MemAddr;                    /* Base addr of (loopback IF's) dedicated mem, if avail.            */
    CPU_ADDR            MemSize;                    /* Size      of (loopback IF's) dedicated mem, if avail.            */


    NET_DEV_CFG_FLAGS   Flags;                      /* Opt'l bit flags.                                                 */

                                                    /* ---------------- SPECIFIC LOOPBACK CFG MEMBERS ----------------- */

} NET_IF_CFG_LOOPBACK;


/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/

#if (NET_IF_CFG_LOOPBACK_EN == DEF_ENABLED)
NET_IF_LOOPBACK_EXT  NET_BUF        *NetIF_Loopback_RxQ_Head;   /* Ptr to loopback IF rx Q head.                        */
NET_IF_LOOPBACK_EXT  NET_BUF        *NetIF_Loopback_RxQ_Tail;   /* Ptr to loopback IF rx Q tail.                        */

NET_IF_LOOPBACK_EXT  NET_STAT_CTR    NetIF_Loopback_RxQ_PktCtr; /*    Net loopback IF rx pkts ctr.                      */


extern  const  NET_IF_CFG_LOOPBACK   NetIF_Cfg_Loopback;        /*    Net loopback IF cfg.                              */
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void          NetIF_Loopback_Init(NET_ERR  *perr);


                                                                /* --------------------- RX FNCTS --------------------- */
NET_BUF_SIZE  NetIF_Loopback_Rx  (NET_IF   *pif,
                                  NET_ERR  *perr);

                                                                /* --------------------- TX FNCTS --------------------- */
NET_BUF_SIZE  NetIF_Loopback_Tx  (NET_IF   *pif,
                                  NET_BUF  *pbuf_tx,
                                  NET_ERR  *perr);


/*
*********************************************************************************************************
*                                        CONFIGURATION ERRORS
*********************************************************************************************************
*/

#ifndef  NET_IF_CFG_LOOPBACK_EN
#error  "NET_IF_CFG_LOOPBACK_EN        not #define'd in 'net_cfg.h'"
#error  "                        [MUST be  DEF_DISABLED]           "
#error  "                        [     ||  DEF_ENABLED ]           "

#elif  ((NET_IF_CFG_LOOPBACK_EN != DEF_DISABLED) && \
        (NET_IF_CFG_LOOPBACK_EN != DEF_ENABLED ))
#error  "NET_IF_CFG_LOOPBACK_EN  illegally #define'd in 'net_cfg.h'"
#error  "                        [MUST be  DEF_DISABLED]           "
#error  "                        [     ||  DEF_ENABLED ]           "
#endif


/*
*********************************************************************************************************
*                                             MODULE END
*
* Note(s) : (1) See 'net_if_loopback.h  MODULE'.
*********************************************************************************************************
*/

#endif                                                          /* End of loopback IF module include (see Note #1).     */

