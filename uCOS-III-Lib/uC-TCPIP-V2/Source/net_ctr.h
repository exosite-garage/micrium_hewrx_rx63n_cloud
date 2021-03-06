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
*                                      NETWORK COUNTER MANAGEMENT
*
* Filename      : net_ctr.h
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

#if ((defined(NET_CTR_MODULE)) && \
     (defined(NET_GLOBALS_EXT)))
#define  NET_CTR_EXT
#else
#define  NET_CTR_EXT  extern
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             DATA TYPES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                      NETWORK COUNTER DATA TYPE
*
* Note(s) : (1) NET_CTR_MIN & NET_CTR_MAX  SHOULD be #define'd based on 'NET_CTR' data type declared.
*
*           (2) NET_CTR_PCT_NUMER_MAX_TH, NET_CTR_BIT_LO, & NET_CTR_BIT_HI  MUST be globally #define'd 
*               AFTER 'NET_CTR' data type declared.
*
*           (3) NET_CTR_PCT_NUMER_MAX_TH  #define's the maximum value for a counter that is used as a
*               numerator in a percentage calculation.  This threshold is required since the numerator in
*               a percentage calculation is multiplied by 100 (%) BEFORE division with the denominator :
*
*                                    Numerator * 100%
*                   Percentage (%) = ----------------
*                                      Denominator
*
*               Therefore, the numerator MUST be constrained by this threshold to prevent integer overflow
*               from the multiplication BEFORE the division.
*
*               (a) The percentage threshold value is calculated as follows :
*
*                                                N
*                                               2
*                       Percentage Threshold = ---
*                                              100
*
*               (b) To avoid macro integer overflow, the threshold value is modified by one less "divide-by-2"
*                   left-shift compensated by dividing the numerator by 50, instead of 100 :
*
*                                               N-1     N
*                                              2       2  / 2
*                       Percentage Threshold = ---- = -------
*                                               50    100 / 2
*********************************************************************************************************
*/

typedef  CPU_INT32U  NET_CTR;                                   /* Defines   max nbr of errs/stats to cnt.              */

#define  NET_CTR_MIN                    DEF_INT_32U_MIN_VAL     /* Define as min unsigned val (see Note #1).            */
#define  NET_CTR_MAX                    DEF_INT_32U_MAX_VAL     /* Define as max unsigned val (see Note #1).            */


#define  NET_CTR_PCT_NUMER_MAX_TH    (((NET_CTR)1u << ((sizeof(NET_CTR) * DEF_OCTET_NBR_BITS) - 1u)) / (NET_CTR)50u)

#define  NET_CTR_BIT_LO               ((NET_CTR)DEF_BIT_00)
#define  NET_CTR_BIT_HI               ((NET_CTR)1u << ((sizeof(NET_CTR) * DEF_OCTET_NBR_BITS) - 1u))


/*$PAGE*/
/*
*********************************************************************************************************
*                                NETWORK STATISTIC COUNTER DATA TYPES
*********************************************************************************************************
*/

#if (NET_CTR_CFG_STAT_EN == DEF_ENABLED)                /* ---------------------- NET STAT CTRS ----------------------- */

typedef  struct  net_ctr_if_stats {
    NET_CTR    NetIF_StatRxNbrOctets;                   /* Nbr      octets      rx'd      for a specific IF.           */
    NET_CTR    NetIF_StatRxNbrOctetsPrev;               /* Nbr      octets prev rx'd      for a specific IF.           */
    NET_CTR    NetIF_StatRxNbrOctetsPerSec;             /* Nbr rx'd octets per  sec       for a specific IF.           */
    NET_CTR    NetIF_StatRxNbrOctetsPerSecMax;          /* Nbr rx'd octets per  sec max   for a specific IF.           */
    NET_CTR    NetIF_StatRxNbrPktCtr;                   /* Nbr rx'd pkts                  for a specific IF.           */
    NET_CTR    NetIF_StatRxNbrPktCtrPerSec;             /* Nbr rx'd pkts   per  sec       for a specific IF.           */
    NET_CTR    NetIF_StatRxNbrPktCtrPerSecMax;          /* Nbr rx'd pkts   per  sec max   for a specific IF.           */
    NET_CTR    NetIF_StatRxNbrPktCtrProcessed;          /* Nbr rx'd pkts        processed for a specific IF.           */
    NET_CTR    NetIF_StatRxNbrPktCtrProcessedPrev;      /* Nbr rx'd pkts   prev processed for a specific IF.           */

    NET_CTR    NetIF_StatTxNbrOctets;                   /* Nbr      octets      tx'd      for a specific IF.           */
    NET_CTR    NetIF_StatTxNbrOctetsPrev;               /* Nbr      octets prev tx'd      for a specific IF.           */
    NET_CTR    NetIF_StatTxNbrOctetsPerSec;             /* Nbr tx'd octets per  sec       for a specific IF.           */
    NET_CTR    NetIF_StatTxNbrOctetsPerSecMax;          /* Nbr tx'd octets per  sec max   for a specific IF.           */
    NET_CTR    NetIF_StatTxNbrPktCtr;                   /* Nbr tx'd pkts                  for a specific IF.           */
    NET_CTR    NetIF_StatTxNbrPktCtrPerSec;             /* Nbr tx'd pkts   per  sec       for a specific IF.           */
    NET_CTR    NetIF_StatTxNbrPktCtrPerSecMax;          /* Nbr tx'd pkts   per  sec max   for a specific IF.           */
    NET_CTR    NetIF_StatTxNbrPktCtrProcessed;          /* Nbr tx'd pkts        processed for a specific IF.           */
    NET_CTR    NetIF_StatTxNbrPktCtrProcessedPrev;      /* Nbr tx'd pkts   prev processed for a specific IF.           */
} NET_CTR_IF_STATS;



typedef  struct  net_ctr_stats {
                                                        /* --------------------- NET IF STAT CTRS --------------------- */
    NET_CTR_IF_STATS  NetIF_StatCtrs[NET_IF_NBR_IF_TOT];/* IF stat ctrs.                                                */

    NET_CTR  NetIF_StatRxPktCtr;                        /* Nbr rx'd IF pkts.                                            */

    NET_CTR  NetIF_StatTxPktCtr;                        /* Nbr tx'd IF pkts.                                            */
    NET_CTR  NetIF_StatTxPktDeallocCtr;                 /* Nbr tx'd IF pkts successfully dealloc'd.                     */



#ifdef  NET_IF_MODULE_LOOPBACK_PRESENT                  /* ---------------- NET LOOPBACK IF STAT CTRS ----------------- */
    NET_CTR  NetIF_Loopback_StatRxPktCtr;               /* Nbr rx'd loopback pkts.                                      */
    NET_CTR  NetIF_Loopback_StatRxPktProcessedCtr;      /* Nbr rx'd loopback pkts delivered to supported protocols.     */

    NET_CTR  NetIF_Loopback_StatTxPktCtr;               /* Nbr tx'd loopback pkts.                                      */
#endif



#ifdef  NET_IF_MODULE_ETHER_PRESENT                     /* ------------------ NET ETHER IF STAT CTRS ------------------ */
    NET_CTR  NetIF_Ether_StatRxPktCtr;                  /* Nbr rx'd Ether pkts.                                         */
    NET_CTR  NetIF_Ether_StatRxPktProcessedCtr;         /* Nbr rx'd Ether pkts delivered to supported protocols.        */
    NET_CTR  NetIF_Ether_StatRxPktBroadcastCtr;         /* Nbr rx'd Ether pkts broadcast to this     dest.              */
#ifdef  NET_MULTICAST_RX_PRESENT
    NET_CTR  NetIF_Ether_StatRxPktMulticastCtr;         /* Nbr rx'd Ether pkts multicast to this     dest.              */
#endif

    NET_CTR  NetIF_Ether_StatTxPktCtr;                  /* Nbr tx'd Ether pkts.                                         */
    NET_CTR  NetIF_Ether_StatTxPktBroadcastCtr;         /* Nbr tx'd Ether pkts broadcast to multiple dest(s).           */
#ifdef  NET_MULTICAST_PRESENT
    NET_CTR  NetIF_Ether_StatTxPktMulticastCtr;         /* Nbr tx'd Ether pkts multicast to multiple dest(s).           */
#endif
#endif



#ifdef  NET_ARP_MODULE_PRESENT                          /* -------------------- NET ARP STAT CTRS --------------------- */
    NET_CTR  NetARP_StatRxPktCtr;                       /* Nbr rx'd ARP       pkts.                                     */
    NET_CTR  NetARP_StatRxMsgProcessedCtr;              /* Nbr rx'd ARP       msgs successfully processed.              */
    NET_CTR  NetARP_StatRxMsgReqProcessedCtr;           /* Nbr rx'd ARP req   msgs successfully processed.              */
    NET_CTR  NetARP_StatRxMsgReplyProcessedCtr;         /* Nbr rx'd ARP reply msgs successfully processed.              */

    NET_CTR  NetARP_StatTxMsgCtr;                       /* Nbr tx'd ARP       msgs.                                     */
    NET_CTR  NetARP_StatTxMsgReqCtr;                    /* Nbr tx'd ARP req   msgs.                                     */
    NET_CTR  NetARP_StatTxMsgReplyCtr;                  /* Nbr tx'd ARP reply msgs.                                     */
#endif



/*$PAGE*/
                                                        /* -------------------- NET MGR STAT CTRS --------------------- */



                                                        /* --------------------- NET IP STAT CTRS --------------------- */
    NET_CTR  NetIP_StatRxPktCtr;                        /* Nbr rx'd IP datagrams.                                       */
    NET_CTR  NetIP_StatRxDatagramProcessedCtr;          /* Nbr rx'd IP datagrams delivered to supported protocols.      */

    NET_CTR  NetIP_StatRxDestLocalHostCtr;              /* Nbr rx'd IP datagrams from localhost.                        */
    NET_CTR  NetIP_StatRxDestBroadcastCtr;              /* Nbr rx'd IP datagrams via  broadcast.                        */
#ifdef  NET_IGMP_MODULE_PRESENT
    NET_CTR  NetIP_StatRxDestMulticastCtr;              /* Nbr rx'd IP datagrams via  multicast.                        */
#endif

    NET_CTR  NetIP_StatRxFragCtr;                       /* Nbr rx'd IP frags.                                           */
    NET_CTR  NetIP_StatRxFragDatagramReasmCtr;          /* Nbr rx'd IP frag'd datagrams reasm'd.                        */


    NET_CTR  NetIP_StatTxDatagramCtr;                   /* Nbr tx'd IP datagrams.                                       */
    NET_CTR  NetIP_StatTxDestThisHostCtr;               /* Nbr tx'd IP datagrams           to this host.                */
    NET_CTR  NetIP_StatTxDestLocalHostCtr;              /* Nbr tx'd IP datagrams           to localhost.                */
    NET_CTR  NetIP_StatTxDestLocalLinkCtr;              /* Nbr tx'd IP datagrams           to local  link addr(s).      */
    NET_CTR  NetIP_StatTxDestLocalNetCtr;               /* Nbr tx'd IP datagrams           to local  net.               */
    NET_CTR  NetIP_StatTxDestRemoteNetCtr;              /* Nbr tx'd IP datagrams           to remote net.               */
    NET_CTR  NetIP_StatTxDestBroadcastCtr;              /* Nbr tx'd IP datagrams broadcast to dest(s).                  */
#ifdef  NET_MULTICAST_PRESENT
    NET_CTR  NetIP_StatTxDestMulticastCtr;              /* Nbr tx'd IP datagrams multicast to dest(s).                  */
#endif


                                                        /* -------------------- NET ICMP STAT CTRS -------------------- */
    NET_CTR  NetICMP_StatRxMsgCtr;                      /* Nbr rx'd ICMP       msgs.                                    */
    NET_CTR  NetICMP_StatRxMsgProcessedCtr;             /* Nbr rx'd ICMP       msgs successfully processed.             */
    NET_CTR  NetICMP_StatRxMsgErrProcessedCtr;          /* Nbr rx'd ICMP err   msgs successfully processed.             */
    NET_CTR  NetICMP_StatRxMsgReqProcessedCtr;          /* Nbr rx'd ICMP req   msgs successfully processed.             */
    NET_CTR  NetICMP_StatRxMsgReplyProcessedCtr;        /* Nbr rx'd ICMP reply msgs successfully processed.             */

    NET_CTR  NetICMP_StatTxMsgCtr;                      /* Nbr tx'd ICMP       msgs.                                    */
    NET_CTR  NetICMP_StatTxMsgErrCtr;                   /* Nbr tx'd ICMP err   msgs.                                    */
    NET_CTR  NetICMP_StatTxMsgReqCtr;                   /* Nbr tx'd ICMP req   msgs.                                    */
    NET_CTR  NetICMP_StatTxMsgReplyCtr;                 /* Nbr tx'd ICMP reply msgs.                                    */



#ifdef  NET_IGMP_MODULE_PRESENT                         /* -------------------- NET IGMP STAT CTRS -------------------- */
    NET_CTR  NetIGMP_StatRxMsgCtr;                      /* Nbr rx'd IGMP        msgs.                                   */
    NET_CTR  NetIGMP_StatRxMsgProcessedCtr;             /* Nbr rx'd IGMP        msgs successfully processed.            */
    NET_CTR  NetIGMP_StatRxMsgQueryProcessedCtr;        /* Nbr rx'd IGMP query  msgs successfully processed.            */
    NET_CTR  NetIGMP_StatRxMsgReportProcessedCtr;       /* Nbr rx'd IGMP report msgs successfully processed.            */

    NET_CTR  NetIGMP_StatTxMsgCtr;                      /* Nbr tx'd IGMP        msgs.                                   */
    NET_CTR  NetIGMP_StatTxMsgReportCtr;                /* Nbr tx'd IGMP report msgs.                                   */
#endif



/*$PAGE*/
                                                        /* --------------------- NET UDP STAT CTRS -------------------- */
    NET_CTR  NetUDP_StatRxPktCtr;                       /* Nbr rx'd UDP datagrams.                                      */
    NET_CTR  NetUDP_StatRxDatagramProcessedCtr;         /* Nbr rx'd UDP datagrams delivered to app layer.               */

    NET_CTR  NetUDP_StatTxDatagramCtr;                  /* Nbr tx'd UDP datagrams.                                      */



#ifdef  NET_TCP_MODULE_PRESENT                          /* --------------------- NET TCP STAT CTRS -------------------- */
    NET_CTR  NetTCP_StatRxPktCtr;                       /* Nbr rx'd TCP segs.                                           */
    NET_CTR  NetTCP_StatRxSegProcessedCtr;              /* Nbr rx'd TCP segs demux'd to app conn.                       */

    NET_CTR  NetTCP_StatTxSegCtr;                       /* Nbr tx'd TCP              segs.                              */
    NET_CTR  NetTCP_StatTxSegConnSyncCtr;               /* Nbr tx'd TCP conn sync    segs.                              */
    NET_CTR  NetTCP_StatTxSegConnCloseCtr;              /* Nbr tx'd TCP conn close   segs.                              */
    NET_CTR  NetTCP_StatTxSegConnAckCtr;                /* Nbr tx'd TCP conn ack     segs.                              */
    NET_CTR  NetTCP_StatTxSegConnResetCtr;              /* Nbr tx'd TCP conn reset   segs.                              */
    NET_CTR  NetTCP_StatTxSegConnProbeCtr;              /* Nbr tx'd TCP conn probe   segs.                              */
    NET_CTR  NetTCP_StatTxSegConnTxQ_Ctr;               /* Nbr tx'd TCP conn    tx Q segs.                              */
    NET_CTR  NetTCP_StatTxSegConnReTxQ_Ctr;             /* Nbr tx'd TCP conn re-tx Q segs.                              */
#endif



#ifdef  NET_SOCK_MODULE_PRESENT                         /* -------------------- NET SOCK STAT CTRS -------------------- */
    NET_CTR  NetSock_StatRxPktCtr;                      /* Nbr rx'd sock pkts.                                          */
    NET_CTR  NetSock_StatRxPktProcessedCtr;             /* Nbr rx'd sock pkts delivered to apps.                        */
#endif


} NET_CTR_STATS;
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                  NETWORK ERROR COUNTER DATA TYPES
*********************************************************************************************************
*/

#if (NET_CTR_CFG_ERR_EN  == DEF_ENABLED)                /* ----------------------- NET ERR CTRS ----------------------- */

typedef  struct  net_ctr_if_errs {
    NET_CTR  NetIF_ErrRxInvalidProtocolCtr;             /* Nbr rx'd IF pkts with invalid/unsupported protocol.          */
    NET_CTR  NetIF_ErrRxInvalidBufIxCtr;                /* Nbr rx'd IF pkts with invalid buf ix.                        */
    NET_CTR  NetIF_ErrRxPktDiscardedCtr;                /* Nbr rx'd IF pkts discarded for a specific IF.                */

    NET_CTR  NetIF_ErrTxInvalidProtocolCtr;             /* Nbr tx   IF pkts with invalid/unsupported protocol.          */
    NET_CTR  NetIF_ErrTxInvalidBufIxCtr;                /* Nbr tx   IF pkts with invalid buf ix.                        */
    NET_CTR  NetIF_ErrTxPktDiscardedCtr;                /* Nbr tx   IF pkts discarded for a specific IF.                */

    NET_CTR  NetIF_ErrBufLostCtr;                       /* Nbr      IF net bufs lost/discarded.                         */
} NET_CTR_IF_ERRS;



typedef  struct  net_ctr_errs {
                                                        /* ----------------------- NET ERR CTRS ----------------------- */
    NET_CTR  Net_ErrInvalidTransactionTypeCtr;          /* Nbr invalid transaction type accesses.                       */


                                                        /* --------------------- NET STAT ERR CTRS -------------------- */
#if  (NET_ERR_CFG_ARG_CHK_DBG_EN == DEF_ENABLED)
    NET_CTR  NetStat_ErrNullPtrCtr;                     /* Nbr null    net stat ptr  accesses.                          */
    NET_CTR  NetStat_ErrInvalidTypeCtr;                 /* Nbr invalid net stat type accesses.                          */
#endif


                                                        /* --------------------- NET TMR  ERR CTRS -------------------- */
    NET_CTR  NetTmr_ErrNoneAvailCtr;                    /* Nbr unavail net tmr      accesses.                           */

#if  (NET_ERR_CFG_ARG_CHK_DBG_EN == DEF_ENABLED)
    NET_CTR  NetTmr_ErrNullPtrCtr;                      /* Nbr null    net tmr      accesses.                           */
    NET_CTR  NetTmr_ErrNullFnctCtr;                     /* Nbr null    net tmr fnct accesses.                           */
    NET_CTR  NetTmr_ErrNotUsedCtr;                      /* Nbr unused  net tmr      accesses.                           */

    NET_CTR  NetTmr_ErrInvalidTypeCtr;                  /* Nbr invalid net tmr type accesses.                           */
#endif


                                                        /* --------------------- NET BUF  ERR CTRS -------------------- */
    NET_CTR  NetBuf_ErrNoneAvailCtr;                    /* Nbr unavail net buf      accesses.                           */

    NET_CTR  NetBuf_ErrInvalidTypeCtr;                  /* Nbr invalid net buf type accesses.                           */

    NET_CTR  NetBuf_ErrSizeCtr;                         /* Nbr         net bufs with invalid size.                      */
    NET_CTR  NetBuf_ErrLenCtr;                          /* Nbr         net bufs with invalid len.                       */

#if  (NET_ERR_CFG_ARG_CHK_DBG_EN == DEF_ENABLED)
    NET_CTR  NetBuf_ErrNullPtrCtr;                      /* Nbr null    net buf      accesses.                           */
    NET_CTR  NetBuf_ErrNotUsedCtr;                      /* Nbr unused  net buf      accesses.                           */
    NET_CTR  NetBuf_ErrIxCtr;                           /* Nbr         net bufs with invalid ix.                        */
#endif



#ifdef  NET_CONN_MODULE_PRESENT                         /* --------------------- NET CONN ERR CTRS -------------------- */
    NET_CTR  NetConn_ErrNoneAvailCtr;                   /* Nbr unavail net conn      accesses.                          */
    NET_CTR  NetConn_ErrNotUsedCtr;                     /* Nbr unused  net conn      accesses.                          */

    NET_CTR  NetConn_ErrCloseCtr;                       /* Nbr         net conn closes.                                 */

    NET_CTR  NetConn_ErrInvalidConnCtr;                 /* Nbr invalid net conn ID   accesses.                          */
    NET_CTR  NetConn_ErrInvalidConnAddrLenCtr;          /* Nbr         net conns with invalid addr len.                 */
    NET_CTR  NetConn_ErrInvalidConnAddrInUseCtr;        /* Nbr         net conns with         addr already in use.      */

    NET_CTR  NetConn_ErrInvalidFamilyCtr;               /* Nbr         net conns with invalid conn family.              */
    NET_CTR  NetConn_ErrInvalidProtocolIxCtr;           /* Nbr         net conns with invalid protocol ix.              */

#if  (NET_ERR_CFG_ARG_CHK_DBG_EN == DEF_ENABLED)
    NET_CTR  NetConn_ErrNullPtrCtr;                     /* Nbr null    net conn      accesses.                          */

    NET_CTR  NetConn_ErrInvalidTypeCtr;                 /* Nbr invalid net conn type accesses.                          */
#endif

#endif



/*$PAGE*/
                                                        /* --------------------- NET IF ERR CTRS ---------------------- */
    NET_CTR_IF_ERRS  NetIF_ErrCtrs[NET_IF_NBR_IF_TOT];  /* IF err ctrs.                                                 */

    NET_CTR  NetIF_ErrRxPktDiscardedCtr;                /* Nbr rx'd IF pkts discarded.                                  */

    NET_CTR  NetIF_ErrTxPktDeallocCtr;                  /* Nbr tx'd IF pkts NOT sucessfully dealloc'd.                  */
    NET_CTR  NetIF_ErrTxPktDiscardedCtr;                /* Nbr tx'd IF pkts discarded.                                  */

#if ((NET_ERR_CFG_ARG_CHK_EXT_EN == DEF_ENABLED) || \
     (NET_ERR_CFG_ARG_CHK_DBG_EN == DEF_ENABLED))
    NET_CTR  NetIF_ErrNullPtrCtr;                       /* Nbr null IF ptr accesses.                                    */
#endif



#ifdef  NET_IF_MODULE_LOOPBACK_PRESENT                  /* ----------------- NET LOOPBACK IF ERR CTRS ----------------- */

    NET_CTR  NetIF_Loopback_ErrRxPktDiscardedCtr;       /* Nbr rx'd loopback pkts discarded.                            */

    NET_CTR  NetIF_Loopback_ErrTxPktDiscardedCtr;       /* Nbr tx   loopback pkts discarded.                            */

#if  (NET_ERR_CFG_ARG_CHK_DBG_EN == DEF_ENABLED)
    NET_CTR  NetIF_Loopback_ErrNullPtrCtr;              /* Nbr null loopback IF ptr accesses.                           */
#endif

#endif



#ifdef  NET_IF_MODULE_ETHER_PRESENT                     /* ------------------ NET ETHER IF ERR CTRS ------------------- */
    NET_CTR  NetIF_Ether_ErrNullPtrCtr;                 /* Nbr null Ether IF ptr accesses.                              */


    NET_CTR  NetIF_Ether_ErrRxInvalidFrameCtr;          /* Nbr rx'd Ether pkts with invalid frame.                      */
    NET_CTR  NetIF_Ether_ErrRxInvalidAddrDestCtr;       /* Nbr rx'd Ether pkts with invalid dest addr.                  */
    NET_CTR  NetIF_Ether_ErrRxInvalidAddrSrcCtr;        /* Nbr rx'd Ether pkts with invalid src  addr.                  */

    NET_CTR  NetIF_Ether_ErrRxInvalidProtocolCtr;       /* Nbr rx'd Ether pkts with invalid/unsupported protocol.       */
    NET_CTR  NetIF_Ether_ErrRxPktDiscardedCtr;          /* Nbr rx'd Ether pkts discarded.                               */


    NET_CTR  NetIF_Ether_ErrTxInvalidBufLenCtr;

    NET_CTR  NetIF_Ether_ErrTxInvalidProtocolCtr;       /* Nbr tx   Ether pkts with invalid/unsupported protocol.       */
    NET_CTR  NetIF_Ether_ErrTxPktDiscardedCtr;          /* Nbr tx   Ether pkts discarded.                               */


#if  (NET_ERR_CFG_ARG_CHK_DBG_EN == DEF_ENABLED)
    NET_CTR  NetIF_Ether_ErrRxInvalidBufIxCtr;          /* Nbr rx'd Ether pkts with invalid buf ix.                     */


    NET_CTR  NetIF_Ether_ErrTxInvalidBufIxCtr;          /* Nbr tx   Ether pkts with invalid buf ix.                     */

    NET_CTR  NetIF_Ether_ErrTxHdrDataLenCtr;
#endif

#endif



#ifdef  NET_ARP_MODULE_PRESENT                          /* --------------------- NET ARP ERR CTRS --------------------- */

    NET_CTR  NetARP_ErrNoneAvailCtr;                    /* Nbr unavail ARP cache      accesses.                         */


    NET_CTR  NetARP_ErrRxHdrHW_TypeCtr;                 /* Nbr rx'd ARP msgs with invalid hw       type.                */
    NET_CTR  NetARP_ErrRxHdrHW_AddrLenCtr;              /* Nbr rx'd ARP msgs with invalid hw       addr len.            */
    NET_CTR  NetARP_ErrRxHdrHW_AddrCtr;                 /* Nbr rx'd ARP msgs with invalid hw       addr.                */
    NET_CTR  NetARP_ErrRxHdrProtocolTypeCtr;            /* Nbr rx'd ARP msgs with invalid protocol type.                */
    NET_CTR  NetARP_ErrRxHdrProtocolAddrLenCtr;         /* Nbr rx'd ARP msgs with invalid protocol addr len.            */
    NET_CTR  NetARP_ErrRxHdrProtocolAddrCtr;            /* Nbr rx'd ARP msgs with invalid protocol addr.                */
    NET_CTR  NetARP_ErrRxHdrOpCodeCtr;                  /* Nbr rx'd ARP msgs with invalid op code.                      */
    NET_CTR  NetARP_ErrRxHdrOpAddrCtr;                  /* Nbr rx'd ARP msgs with invalid op code/addr.                 */
    NET_CTR  NetARP_ErrRxHdrMsgLenCtr;                  /* Nbr rx'd ARP msgs with invalid msg len.                      */

    NET_CTR  NetARP_ErrRxPktTargetReplyCtr;             /* Nbr rx'd ARP msgs for  invalid reply msg dest.               */
    NET_CTR  NetARP_ErrRxPktTargetNotThisHostCtr;       /* Nbr rx'd ARP msgs for  invalid           dest.               */

    NET_CTR  NetARP_ErrRxPktDiscardedCtr;               /* Nbr rx'd ARP pkts discarded.                                 */


    NET_CTR  NetARP_ErrTxInvalidBufIxCtr;               /* Nbr tx   ARP pkts with invalid buf ix.                       */
    NET_CTR  NetARP_ErrTxPktDiscardedCtr;               /* Nbr tx   ARP pkts discarded.                                 */


#if ((NET_ERR_CFG_ARG_CHK_EXT_EN == DEF_ENABLED) || \
     (NET_ERR_CFG_ARG_CHK_DBG_EN == DEF_ENABLED))
    NET_CTR  NetARP_ErrNullPtrCtr;                      /* Nbr null    ARP ptr        accesses.                         */
#endif

#if  (NET_ERR_CFG_ARG_CHK_DBG_EN == DEF_ENABLED)
    NET_CTR  NetARP_ErrNotUsedCtr;                      /* Nbr unused  ARP cache      accesses.                         */

    NET_CTR  NetARP_ErrInvalidTypeCtr;                  /* Nbr invalid ARP cache type accesses.                         */


    NET_CTR  NetARP_ErrRxInvalidProtocolCtr;            /* Nbr rx'd ARP pkts with invalid/unsupported protocol.         */
    NET_CTR  NetARP_ErrRxInvalidBufIxCtr;               /* Nbr rx   ARP pkts with invalid buf ix.                       */

    NET_CTR  NetARP_ErrTxHdrOpCodeCtr;                  /* Nbr tx   ARP msgs with invalid op code.                      */
#endif

#endif



/*$PAGE*/
                                                        /* --------------------- NET MGR ERR CTRS --------------------- */



                                                        /* --------------------- NET IP  ERR CTRS --------------------- */
    NET_CTR  NetIP_ErrNullPtrCtr;                       /* Nbr null IP ptr accesses.                                    */


    NET_CTR  NetIP_ErrCfgAddrHostCfgdCtr;               /* Nbr invalid IP host         addr cfg attempts.               */
    NET_CTR  NetIP_ErrCfgAddrDfltGatewayCtr;            /* Nbr invalid IP dflt gateway addr cfg attempts.               */

    NET_CTR  NetIP_ErrCfgAddrHostCfgdInUseCtr;          /* Nbr in use  IP host         addr cfg attempts.               */

    NET_CTR  NetIP_ErrCfgAddrStateCtr;                  /* Nbr invalid IP addr cfg state     accesses.                  */
    NET_CTR  NetIP_ErrCfgAddrNotFoundCtr;               /* Nbr invalid IP addr NOT found     accesses.                  */
    NET_CTR  NetIP_ErrCfgAddrTblSizeCtr;                /* Nbr invalid IP addr cfg tbl size  accesses.                  */
    NET_CTR  NetIP_ErrCfgAddrTblEmptyCtr;               /* Nbr invalid IP addr cfg tbl empty accesses.                  */
    NET_CTR  NetIP_ErrCfgAddrTblFullCtr;                /* Nbr invalid IP addr cfg tbl full  accesses.                  */


    NET_CTR  NetIP_ErrRxHdrVerCtr;                      /* Nbr rx'd IP datagrams with invalid IP ver.                   */
    NET_CTR  NetIP_ErrRxHdrLenCtr;                      /* Nbr rx'd IP datagrams with invalid hdr len.                  */
    NET_CTR  NetIP_ErrRxHdrTotLenCtr;                   /* Nbr rx'd IP datagrams with invalid/inconsistent tot len.     */
    NET_CTR  NetIP_ErrRxHdrFlagsCtr;                    /* Nbr rx'd IP datagrams with invalid flags.                    */
    NET_CTR  NetIP_ErrRxHdrFragCtr;                     /* Nbr rx'd IP datagrams with invalid fragmentation.            */
    NET_CTR  NetIP_ErrRxHdrProtocolCtr;                 /* Nbr rx'd IP datagrams with invalid/unsupported protocol.     */
    NET_CTR  NetIP_ErrRxHdrChkSumCtr;                   /* Nbr rx'd IP datagrams with invalid chk sum.                  */
    NET_CTR  NetIP_ErrRxHdrAddrSrcCtr;                  /* Nbr rx'd IP datagrams with invalid src addr.                 */
    NET_CTR  NetIP_ErrRxHdrOptsCtr;                     /* Nbr rx'd IP datagrams with unknown/invalid opts.             */
    NET_CTR  NetIP_ErrRxHdrOptsBufNoneAvailCtr;         /* Nbr rx'd IP datagrams with no options buf avail.             */
    NET_CTR  NetIP_ErrRxHdrOptsBufWrCtr;                /* Nbr rx'd IP datagrams with wr options buf err.               */

    NET_CTR  NetIP_ErrRxDestCtr;                        /* Nbr rx'd IP datagrams NOT for this IP dest.                  */
    NET_CTR  NetIP_ErrRxDestBroadcastCtr;               /* Nbr rx'd IP datagrams illegally broadcast to this dest.      */

    NET_CTR  NetIP_ErrRxFragSizeCtr;                    /* Nbr rx'd IP frags with invalid size.                         */
    NET_CTR  NetIP_ErrRxFragDiscardedCtr;               /* Nbr rx'd IP frags            discarded.                      */
    NET_CTR  NetIP_ErrRxFragDatagramDiscardedCtr;       /* Nbr rx'd IP frag'd datagrams discarded.                      */
    NET_CTR  NetIP_ErrRxFragDatagramTimeoutCtr;         /* Nbr rx'd IP frag'd datagrams timed out.                      */

    NET_CTR  NetIP_ErrRxInvalidProtocolCtr;             /* Nbr rx'd IP pkts with invalid/unsupported protocol.          */
    NET_CTR  NetIP_ErrRxPktDiscardedCtr;                /* Nbr rx'd IP pkts discarded.                                  */


    NET_CTR  NetIP_ErrTxInvalidProtocolCtr;             /* Nbr tx   IP pkts with invalid/unsupported protocol.          */
    NET_CTR  NetIP_ErrTxOptTypeCtr;                     /* Nbr tx   IP pkts with invalid opt type.                      */

    NET_CTR  NetIP_ErrTxDestCtr;                        /* Nbr tx   IP datagrams with invalid dest addr.                */

    NET_CTR  NetIP_ErrTxPktDiscardedCtr;                /* Nbr tx   IP pkts discarded.                                  */


#if ((NET_ERR_CFG_ARG_CHK_EXT_EN == DEF_ENABLED) || \
     (NET_ERR_CFG_ARG_CHK_DBG_EN == DEF_ENABLED))
    NET_CTR  NetIP_ErrTxInvalidBufIxCtr;                /* Nbr tx   IP pkts  with invalid buf ix.                       */

    NET_CTR  NetIP_ErrTxHdrTOS_Ctr;                     /* Nbr tx   IP datagrams with invalid TOS.                      */
    NET_CTR  NetIP_ErrTxHdrTTL_Ctr;                     /* Nbr tx   IP datagrams with invalid TTL.                      */
    NET_CTR  NetIP_ErrTxHdrDataLenCtr;                  /* Nbr tx   IP datagrams with invalid protocol/data len.        */
    NET_CTR  NetIP_ErrTxHdrAddrSrcCtr;                  /* Nbr tx   IP datagrams with invalid src  addr.                */
    NET_CTR  NetIP_ErrTxHdrAddrDestCtr;                 /* Nbr tx   IP datagrams with invalid dest addr.                */
    NET_CTR  NetIP_ErrTxHdrFlagsCtr;                    /* Nbr tx   IP datagrams with invalid flags.                    */
    NET_CTR  NetIP_ErrTxHdrOptLenCtr;                   /* Nbr tx   IP datagrams with invalid opt len.                  */
    NET_CTR  NetIP_ErrTxHdrOptCfgCtr;                   /* Nbr tx   IP datagrams with invalid opt cfg.                  */
#endif

#if  (NET_ERR_CFG_ARG_CHK_DBG_EN == DEF_ENABLED)
    NET_CTR  NetIP_ErrRxInvalidBufIxCtr;                /* Nbr rx   IP pkts  with invalid buf ix.                       */

    NET_CTR  NetIP_ErrRxHdrDataLenCtr;                  /* Nbr rx'd IP datagrams with invalid data len.                 */

    NET_CTR  NetIP_ErrRxFragFlagsCtr;                   /* Nbr rx'd IP frags with invalid flag(s).                      */
    NET_CTR  NetIP_ErrRxFragOffsetCtr;                  /* Nbr rx'd IP frags with invalid offset.                       */
#endif

#if 0                                                   /* #### NOT currently implemented (see 'net_ip.h  Note #1d').   */
    NET_CTR  NetIP_ErrTxFragDiscardedCtr;               /* Nbr tx IP pseudo-frags discarded (lack resources).           */
    NET_CTR  NetIP_ErrTxFragDiscardedDontFragCtr;       /* Nbr tx IP pseudo-frags discarded ('Don't Frag' set).         */
#endif



/*$PAGE*/
                                                        /* -------------------- NET ICMP ERR CTRS --------------------- */
    NET_CTR  NetICMP_ErrRxHdrTypeCtr;                   /* Nbr rx'd ICMP msgs with unknown/invalid      msg type.       */
    NET_CTR  NetICMP_ErrRxHdrCodeCtr;                   /* Nbr rx'd ICMP msgs with unknown/invalid      msg code.       */
    NET_CTR  NetICMP_ErrRxHdrMsgLenCtr;                 /* Nbr rx'd ICMP msgs with invalid/inconsistent msg len.        */
    NET_CTR  NetICMP_ErrRxHdrPtrCtr;                    /* Nbr rx'd ICMP msgs with invalid              msg ptr.        */
    NET_CTR  NetICMP_ErrRxHdrChkSumCtr;                 /* Nbr rx'd ICMP msgs with invalid chk sum.                     */

    NET_CTR  NetICMP_ErrRxBroadcastCtr;                 /* Nbr rx'd ICMP msg  reqs rx'd via broadcast.                  */
    NET_CTR  NetICMP_ErrRxMulticastCtr;                 /* Nbr rx'd ICMP msg  reqs rx'd via multicast.                  */

    NET_CTR  NetICMP_ErrRxPktDiscardedCtr;              /* Nbr rx'd ICMP pkts discarded.                                */


    NET_CTR  NetICMP_ErrTxInvalidLenCtr;                /* Nbr tx   ICMP pkts discarded for invalid len.                */

    NET_CTR  NetICMP_ErrTxHdrTypeCtr;                   /* Nbr tx   ICMP msgs with unknown/invalid msg type.            */
    NET_CTR  NetICMP_ErrTxHdrCodeCtr;                   /* Nbr tx   ICMP msgs with unknown/invalid msg code.            */

    NET_CTR  NetICMP_ErrTxPktDiscardedCtr;              /* Nbr tx   ICMP pkts discarded.                                */


#if  (NET_ERR_CFG_ARG_CHK_DBG_EN == DEF_ENABLED)
    NET_CTR  NetICMP_ErrNullPtrCtr;                     /* Nbr null    ICMP ptr                      accesses.          */
    NET_CTR  NetICMP_ErrNotUsedCtr;                     /* Nbr unused  ICMP tx src quench entry      accesses.          */

    NET_CTR  NetICMP_ErrInvalidTypeCtr;                 /* Nbr invalid ICMP tx src quench entry type accesses.          */


    NET_CTR  NetICMP_ErrRxInvalidProtocolCtr;           /* Nbr rx'd ICMP pkts with invalid/unsupported protocol.        */
    NET_CTR  NetICMP_ErrRxInvalidBufIxCtr;              /* Nbr rx   ICMP pkts with invalid buf ix.                      */

    NET_CTR  NetICMP_ErrRxHdrDataLenCtr;                /* Nbr rx'd ICMP msgs with invalid msg data len.                */


    NET_CTR  NetICMP_ErrTxInvalidBufIxCtr;              /* Nbr tx   ICMP pkts with invalid buf ix.                      */

    NET_CTR  NetICMP_ErrTxHdrPtrCtr;                    /* Nbr tx   ICMP msgs with invalid msg ptr.                     */
#endif

#if (NET_ICMP_CFG_TX_SRC_QUENCH_EN == DEF_ENABLED)
    NET_CTR  NetICMP_ErrNoneAvailCtr;                   /* Nbr unavail ICMP tx src quench entry      accesses.          */
#endif



#ifdef  NET_IGMP_MODULE_PRESENT                         /* -------------------- NET IGMP ERR CTRS --------------------- */
    NET_CTR  NetIGMP_ErrNoneAvailCtr;                   /* Nbr unavail IGMP host group accesses.                        */

    NET_CTR  NetIGMP_ErrRxHdrTypeCtr;                   /* Nbr rx'd IGMP msgs with unknown/invalid msg type.            */
    NET_CTR  NetIGMP_ErrRxHdrVerCtr;                    /* Nbr rx'd IGMP msgs with invalid IGMP ver.                    */
    NET_CTR  NetIGMP_ErrRxHdrMsgLenCtr;                 /* Nbr rx'd IGMP msgs with invalid msg len.                     */
    NET_CTR  NetIGMP_ErrRxHdrChkSumCtr;                 /* Nbr rx'd IGMP msgs with invalid chk sum.                     */

    NET_CTR  NetIGMP_ErrRxPktInvalidAddrDestCtr;        /* Nbr rx'd IGMP msgs with invalid dest addr.                   */

    NET_CTR  NetIGMP_ErrRxPktDiscardedCtr;              /* Nbr rx'd IGMP pkts discarded.                                */


    NET_CTR  NetIGMP_ErrTxInvalidBufIxCtr;              /* Nbr rx   IGMP pkts with invalid buf ix.                      */

    NET_CTR  NetIGMP_ErrTxPktDiscardedCtr;              /* Nbr tx   IGMP pkts discarded.                                */


#if  (NET_ERR_CFG_ARG_CHK_DBG_EN == DEF_ENABLED)
    NET_CTR  NetIGMP_ErrNullPtrCtr;                     /* Nbr null    IGMP ptr           accesses.                     */

    NET_CTR  NetIGMP_ErrInvalidTypeCtr;                 /* Nbr invalid IGMP host grp type accesses.                     */


    NET_CTR  NetIGMP_ErrRxInvalidProtocolCtr;           /* Nbr rx'd IGMP pkts with invalid/unsupported protocol.        */
    NET_CTR  NetIGMP_ErrRxInvalidBufIxCtr;              /* Nbr rx   IGMP pkts with invalid buf ix.                      */
#endif

#endif



/*$PAGE*/
                                                        /* --------------------- NET UDP ERR CTRS --------------------- */
    NET_CTR  NetUDP_ErrNullPtrCtr;                      /* Nbr null UDP ptr accesses.                                   */
    NET_CTR  NetUDP_ErrInvalidFlagsCtr;                 /* Nbr reqs           for  invalid UDP flags.                   */


    NET_CTR  NetUDP_ErrRxHdrDatagramLenCtr;             /* Nbr rx'd UDP datagrams with invalid len.                     */
    NET_CTR  NetUDP_ErrRxHdrPortSrcCtr;                 /* Nbr rx'd UDP datagrams with invalid src  port.               */
    NET_CTR  NetUDP_ErrRxHdrPortDestCtr;                /* Nbr rx'd UDP datagrams with invalid dest port.               */
    NET_CTR  NetUDP_ErrRxHdrChkSumCtr;                  /* Nbr rx'd UDP datagrams with invalid chk sum.                 */

    NET_CTR  NetUDP_ErrRxDestCtr;                       /* Nbr rx'd UDP datagrams for  unavail dest.                    */

    NET_CTR  NetUDP_ErrRxPktDiscardedCtr;               /* Nbr rx'd UDP pkts discarded.                                 */


    NET_CTR  NetUDP_ErrTxPktDiscardedCtr;               /* Nbr tx   UDP pkts discarded.                                 */


#if ((NET_ERR_CFG_ARG_CHK_EXT_EN == DEF_ENABLED) || \
     (NET_ERR_CFG_ARG_CHK_DBG_EN == DEF_ENABLED))
    NET_CTR  NetUDP_ErrTxInvalidSizeCtr;                /* Nbr tx   UDP reqs      with invalid data size.               */
#endif

#if  (NET_ERR_CFG_ARG_CHK_DBG_EN == DEF_ENABLED)
    NET_CTR  NetUDP_ErrRxInvalidProtocolCtr;            /* Nbr rx'd UDP pkts      with invalid/unsupported protocol.    */
    NET_CTR  NetUDP_ErrRxInvalidBufIxCtr;               /* Nbr rx   UDP pkts      with invalid buf ix.                  */

    NET_CTR  NetUDP_ErrRxHdrDataLenCtr;                 /* Nbr rx'd UDP datagrams with invalid data len.                */


    NET_CTR  NetUDP_ErrTxInvalidProtocolCtr;            /* Nbr tx   UDP pkts      with invalid/unsupported protocol.    */
    NET_CTR  NetUDP_ErrTxInvalidBufIxCtr;               /* Nbr tx   UDP pkts      with invalid buf ix.                  */

    NET_CTR  NetUDP_ErrTxHdrDataLenCtr;                 /* Nbr tx   UDP datagrams with invalid protocol/data len.       */
    NET_CTR  NetUDP_ErrTxHdrPortSrcCtr;                 /* Nbr tx   UDP datagrams with invalid src  port.               */
    NET_CTR  NetUDP_ErrTxHdrPortDestCtr;                /* Nbr tx   UDP datagrams with invalid dest port.               */
    NET_CTR  NetUDP_ErrTxHdrFlagsCtr;                   /* Nbr tx   UDP datagrams with invalid flags.                   */
#endif



/*$PAGE*/
#ifdef  NET_TCP_MODULE_PRESENT                          /* --------------------- NET TCP ERR CTRS --------------------- */
    NET_CTR  NetTCP_ErrNullPtrCtr;                      /* Nbr null    TCP conn ptr  accesses.                          */

    NET_CTR  NetTCP_ErrNoneAvailCtr;                    /* Nbr unavail TCP conn      accesses.                          */
    NET_CTR  NetTCP_ErrNotUsedCtr;                      /* Nbr unused  TCP conn      accesses.                          */


    NET_CTR  NetTCP_ErrRxHdrLenCtr;                     /* Nbr rx'd TCP segs with invalid hdr len.                      */
    NET_CTR  NetTCP_ErrRxHdrSegLenCtr;                  /* Nbr rx'd TCP segs with invalid seg len.                      */
    NET_CTR  NetTCP_ErrRxHdrPortSrcCtr;                 /* Nbr rx'd TCP segs with invalid src  port.                    */
    NET_CTR  NetTCP_ErrRxHdrPortDestCtr;                /* Nbr rx'd TCP segs with invalid dest port.                    */
    NET_CTR  NetTCP_ErrRxHdrFlagsCtr;                   /* Nbr rx'd TCP segs with invalid flags.                        */
    NET_CTR  NetTCP_ErrRxHdrChkSumCtr;                  /* Nbr rx'd TCP segs with invalid chk sum.                      */
    NET_CTR  NetTCP_ErrRxHdrOptsCtr;                    /* Nbr rx'd TCP segs with unknown/invalid opts.                 */

    NET_CTR  NetTCP_ErrRxDestCtr;                       /* Nbr rx'd TCP segs for  unavail dest.                         */

    NET_CTR  NetTCP_ErrRxPktDiscardedCtr;               /* Nbr rx'd TCP pkts discarded.                                 */


    NET_CTR  NetTCP_ErrTxOptTypeCtr;                    /* Nbr tx   TCP pkts with invalid opt type.                     */

    NET_CTR  NetTCP_ErrTxPktDiscardedCtr;               /* Nbr tx   TCP pkts discarded.                                 */


    NET_CTR  NetTCP_ErrConnInvalidCtr;                  /* Nbr invalid TCP conn ID   accesses.                          */
    NET_CTR  NetTCP_ErrConnInvalidOpCtr;                /* Nbr invalid TCP conn ops.                                    */
    NET_CTR  NetTCP_ErrConnInvalidStateCtr;             /* Nbr invalid TCP conn states.                                 */

    NET_CTR  NetTCP_ErrConnCloseCtr;                    /* Nbr fault   TCP conn closes.                                 */


#if  (NET_ERR_CFG_ARG_CHK_DBG_EN == DEF_ENABLED)
    NET_CTR  NetTCP_ErrRxInvalidProtocolCtr;            /* Nbr rx'd TCP pkts with invalid/unsupported protocol.         */
    NET_CTR  NetTCP_ErrRxInvalidBufIxCtr;               /* Nbr rx   TCP pkts with invalid buf ix.                       */

    NET_CTR  NetTCP_ErrRxHdrDataLenCtr;                 /* Nbr rx'd TCP segs with invalid data len.                     */


    NET_CTR  NetTCP_ErrTxInvalidProtocolCtr;            /* Nbr tx   TCP pkts with invalid/unsupported protocol.         */
    NET_CTR  NetTCP_ErrTxInvalidSizeCtr;                /* Nbr tx   TCP reqs with invalid data size.                    */
    NET_CTR  NetTCP_ErrTxInvalidBufIxCtr;               /* Nbr tx   TCP pkts with invalid buf ix.                       */

    NET_CTR  NetTCP_ErrTxHdrDataLenCtr;                 /* Nbr tx   TCP segs with invalid protocol/data len.            */
    NET_CTR  NetTCP_ErrTxHdrPortSrcCtr;                 /* Nbr tx   TCP segs with invalid src  port.                    */
    NET_CTR  NetTCP_ErrTxHdrPortDestCtr;                /* Nbr tx   TCP segs with invalid dest port.                    */
    NET_CTR  NetTCP_ErrTxHdrFlagsCtr;                   /* Nbr tx   TCP segs with invalid flags.                        */
    NET_CTR  NetTCP_ErrTxHdrOptLenCtr;                  /* Nbr tx   TCP segs with invalid opt len.                      */
    NET_CTR  NetTCP_ErrTxHdrOptCfgCtr;                  /* Nbr tx   TCP segs with invalid opt cfg.                      */


    NET_CTR  NetTCP_ErrConnInvalidTypeCtr;              /* Nbr invalid TCP conn type accesses.                          */
#endif

#endif



/*$PAGE*/
#ifdef  NET_SOCK_MODULE_PRESENT                         /* -------------------- NET SOCK ERR CTRS --------------------- */
    NET_CTR  NetSock_ErrNullPtrCtr;                     /* Nbr null    sock ptr  accesses.                              */
    NET_CTR  NetSock_ErrNullSizeCtr;

    NET_CTR  NetSock_ErrNoneAvailCtr;                   /* Nbr unavail sock      accesses.                              */
    NET_CTR  NetSock_ErrNotUsedCtr;                     /* Nbr unused  sock      accesses.                              */

    NET_CTR  NetSock_ErrCloseCtr;                       /* Nbr fault   sock closes.                                     */


    NET_CTR  NetSock_ErrInvalidFamilyCtr;               /* Nbr socks with invalid sock family.                          */
    NET_CTR  NetSock_ErrInvalidProtocolCtr;             /* Nbr socks with invalid sock protocol.                        */
    NET_CTR  NetSock_ErrInvalidSockTypeCtr;             /* Nbr socks with invalid sock type.                            */
    NET_CTR  NetSock_ErrInvalidSockCtr;                 /* Nbr            invalid sock ID accesses.                     */

    NET_CTR  NetSock_ErrInvalidFlagsCtr;                /* Nbr socks with invalid flags.                                */
    NET_CTR  NetSock_ErrInvalidOpCtr;                   /* Nbr socks with invalid op.                                   */
    NET_CTR  NetSock_ErrInvalidStateCtr;                /* Nbr socks with invalid state.                                */

    NET_CTR  NetSock_ErrInvalidAddrCtr;                 /* Nbr socks with invalid addr.                                 */
    NET_CTR  NetSock_ErrInvalidAddrLenCtr;              /* Nbr socks with invalid addr len.                             */
    NET_CTR  NetSock_ErrInvalidAddrInUseCtr;            /* Nbr socks with         addr already in use.                  */

    NET_CTR  NetSock_ErrInvalidPortNbrCtr;              /* Nbr socks with invalid port nbr.                             */

    NET_CTR  NetSock_ErrInvalidConnInUseCtr;            /* Nbr socks with         conn already in use.                  */


#if (NET_SOCK_CFG_TYPE_STREAM_EN == DEF_ENABLED)
    NET_CTR  NetSock_ErrConnAcceptQ_NoneAvailCtr;       /* Nbr unavail sock accept Q conn   accesses.                   */
#endif

    NET_CTR  NetSock_ErrRandomPortNbrNoneAvailCtr;      /* Nbr unavail sock random port nbr accesses.                   */


    NET_CTR  NetSock_ErrRxDestCtr;                      /* Nbr rx'd sock pkts for unavail dest.                         */

    NET_CTR  NetSock_ErrRxPktDiscardedCtr;              /* Nbr rx'd sock pkts discarded.                                */


#if ((NET_ERR_CFG_ARG_CHK_EXT_EN == DEF_ENABLED) || \
     (NET_ERR_CFG_ARG_CHK_DBG_EN == DEF_ENABLED))
    NET_CTR  NetSock_ErrTxInvalidSizeCtr;               /* Nbr tx   sock reqs with invalid data size.                   */
#endif

#if  (NET_ERR_CFG_ARG_CHK_DBG_EN == DEF_ENABLED)
    NET_CTR  NetSock_ErrInvalidTypeCtr;                 /* Nbr invalid sock type accesses.                              */
    NET_CTR  NetSock_ErrInvalidConnCtr;

    NET_CTR  NetSock_ErrRxInvalidProtocolCtr;           /* Nbr rx'd sock pkts with invalid/unsupported protocol.        */
    NET_CTR  NetSock_ErrRxInvalidBufIxCtr;              /* Nbr rx   sock pkts with invalid buf ix.                      */

#if (NET_SOCK_CFG_TYPE_STREAM_EN == DEF_ENABLED)
    NET_CTR  NetSock_ErrConnAcceptQ_MaxCtr;
#endif

    NET_CTR  NetSock_ErrRandomPortNbrQ_UsedCtr;
    NET_CTR  NetSock_ErrRandomPortNbrQ_NbrInQ_Ctr;
#endif

#endif


} NET_CTR_ERRS;
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/

#if (NET_CTR_CFG_STAT_EN == DEF_ENABLED)                        /* ------------------ NET STAT CTRS ------------------- */
NET_CTR_EXT  NET_CTR_STATS  Net_StatCtrs;
#endif

#if (NET_CTR_CFG_ERR_EN  == DEF_ENABLED)                        /* ------------------ NET ERRS CTRS ------------------- */
NET_CTR_EXT  NET_CTR_ERRS   Net_ErrCtrs;
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                               MACRO'S
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                       NETWORK COUNTER MACRO'S
*
* Description : Handle network counter(s).
*
* Argument(s) : Various network counter variable(s) & values.
*
* Return(s)   : none.
*
* Caller(s)   : various.
*
*               These macro's are INTERNAL network protocol suite macro's & SHOULD NOT be called by
*               application function(s).
*
* Note(s)     : (1) Network counter variables MUST ALWAYS be accessed exclusively in critical sections.
*
*                   Therefore, local variable 'cpu_sr' MUST be declared via the CPU_SR_ALLOC() macro 
*                   in the following functions in case the CPU critical section method is configured 
*                   as 'CPU_CRITICAL_METHOD_STATUS_LOCAL' :
*
*                   (a) NetCtr_Inc()
*                   (b) ALL functions which call NET_CTR_&&&_INC_LARGE() macro's 
*********************************************************************************************************
*/

#define  NET_CTR_INC(ctr)                                       NetCtr_Inc(&(ctr));

#define  NET_CTR_INC_LARGE(ctr_hi, ctr_lo)                do {  CPU_CRITICAL_ENTER();       \
                                                                NetCtr_IncLarge(&(ctr_hi),  \
                                                                                &(ctr_lo)); \
                                                                CPU_CRITICAL_EXIT();        } while (0)


#define  NET_CTR_ADD(ctr, val)                            do { (ctr) += (val); } while (0)



#if     (NET_CTR_CFG_STAT_EN == DEF_ENABLED)

#define  NET_CTR_STAT_INC(stat_ctr)                             NET_CTR_INC(stat_ctr)
#define  NET_CTR_STAT_INC_LARGE(stat_ctr_hi, stat_ctr_lo)       NET_CTR_INC_LARGE(stat_ctr_hi, stat_ctr_lo)

#define  NET_CTR_STAT_ADD(stat_ctr, val)                        NET_CTR_ADD(stat_ctr, val)

#else

#define  NET_CTR_STAT_INC(stat_ctr)
#define  NET_CTR_STAT_INC_LARGE(stat_ctr_hi, stat_ctr_lo)

#define  NET_CTR_STAT_ADD(stat_ctr, val)

#endif


#if     (NET_CTR_CFG_ERR_EN == DEF_ENABLED)

#define  NET_CTR_ERR_INC(err_ctr)                               NET_CTR_INC(err_ctr)
#define  NET_CTR_ERR_INC_LARGE(err_ctr_hi, err_ctr_lo)          NET_CTR_INC_LARGE(err_ctr_hi,  err_ctr_lo)

#else

#define  NET_CTR_ERR_INC(err_ctr)
#define  NET_CTR_ERR_INC_LARGE(err_ctr_hi, err_ctr_lo)

#endif


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void        NetCtr_Init        (void);


                                                                        /* -------------- CTR API FNCTS --------------- */
#if (NET_CTR_CFG_CTR_EN  == DEF_ENABLED)
void        NetCtr_Inc         (NET_CTR  *pctr);

void        NetCtr_IncLarge    (NET_CTR  *pctr_hi,
                                NET_CTR  *pctr_lo);
#endif

#if (NET_CTR_CFG_STAT_EN == DEF_ENABLED)
CPU_INT08U  NetCtr_CalcPctLarge(NET_CTR   pct_numer_hi,
                                NET_CTR   pct_numer_lo,
                                NET_CTR   pct_denom_hi,
                                NET_CTR   pct_denom_lo);
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                        CONFIGURATION ERRORS
*********************************************************************************************************
*/

#ifndef  NET_CTR_CFG_STAT_EN
#error  "NET_CTR_CFG_STAT_EN        not #define'd in 'net_cfg.h'"
#error  "                     [MUST be  DEF_DISABLED]           "
#error  "                     [     ||  DEF_ENABLED ]           "

#elif  ((NET_CTR_CFG_STAT_EN != DEF_DISABLED) && \
        (NET_CTR_CFG_STAT_EN != DEF_ENABLED ))
#error  "NET_CTR_CFG_STAT_EN  illegally #define'd in 'net_cfg.h'"
#error  "                     [MUST be  DEF_DISABLED]           "
#error  "                     [     ||  DEF_ENABLED ]           "
#endif



#ifndef  NET_CTR_CFG_ERR_EN
#error  "NET_CTR_CFG_ERR_EN         not #define'd in 'net_cfg.h'"
#error  "                     [MUST be  DEF_DISABLED]           "
#error  "                     [     ||  DEF_ENABLED ]           "

#elif  ((NET_CTR_CFG_ERR_EN != DEF_DISABLED) && \
        (NET_CTR_CFG_ERR_EN != DEF_ENABLED ))
#error  "NET_CTR_CFG_ERR_EN   illegally #define'd in 'net_cfg.h'"
#error  "                     [MUST be  DEF_DISABLED]           "
#error  "                     [     ||  DEF_ENABLED ]           "
#endif


                                                            /* Correctly configured in 'net_cfg_net.h'; DO NOT MODIFY.  */
#ifndef  NET_CTR_CFG_CTR_EN
#error  "NET_CTR_CFG_CTR_EN         not #define'd in 'net_cfg_net.h'"
#error  "                     [MUST be  DEF_DISABLED]               "
#error  "                     [     ||  DEF_ENABLED ]               "

#elif  ((NET_CTR_CFG_CTR_EN != DEF_DISABLED) && \
        (NET_CTR_CFG_CTR_EN != DEF_ENABLED ))
#error  "NET_CTR_CFG_CTR_EN   illegally #define'd in 'net_cfg_net.h'"
#error  "                     [MUST be  DEF_DISABLED]               "
#error  "                     [     ||  DEF_ENABLED ]               "
#endif

