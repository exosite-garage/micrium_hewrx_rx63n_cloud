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
*                                      NETWORK BUFFER MANAGEMENT
*
* Filename      : net_buf.h
* Version       : V2.11.02
* Programmer(s) : ITJ
*                 EHS
*                 FGK
*                 SR
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/

#if ((defined(NET_BUF_MODULE)) && \
     (defined(NET_GLOBALS_EXT)))
#define  NET_BUF_EXT
#else
#define  NET_BUF_EXT  extern
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/

#define  NET_BUF_ID_NONE                                   0u
#define  NET_BUF_ID_INIT                     NET_BUF_ID_NONE


/*
*********************************************************************************************************
*                                     NETWORK BUFFER FLAG DEFINES
*********************************************************************************************************
*/

                                                                /* ------------------- NET BUF FLAGS ------------------ */
#define  NET_BUF_FLAG_NONE                        DEF_BIT_NONE
#define  NET_BUF_FLAG_USED                        DEF_BIT_00    /* Buf cur used; i.e. NOT in free buf pool.             */
#define  NET_BUF_FLAG_CLR_MEM                     DEF_BIT_01    /* Buf mem clr'd.                                       */

#define  NET_BUF_FLAG_RX_BROADCAST                DEF_BIT_04    /* Indicates pkts rx'd via  broadcast.                  */
#define  NET_BUF_FLAG_RX_MULTICAST                DEF_BIT_05    /* Indicates pkts rx'd via  multicast.                  */
#define  NET_BUF_FLAG_RX_REMOTE                   DEF_BIT_06    /* Indicates pkts rx'd from remote host.                */
#define  NET_BUF_FLAG_RX_UDP_CHK_SUM_VALID        DEF_BIT_07    /* Indicates UDP  rx chk sum valid.                     */

#define  NET_BUF_FLAG_TX_BROADCAST                DEF_BIT_12    /* Indicates pkts to tx via broadcast.                  */
#define  NET_BUF_FLAG_TX_MULTICAST                DEF_BIT_13    /* Indicates pkts to tx via multicast.                  */

#define  NET_BUF_FLAG_TX_LOCK                     DEF_BIT_14    /* Protects  pkts from concurrent dev/hw tx.            */


/*
*********************************************************************************************************
*                                     NETWORK BUFFER TYPE DEFINES
*
* Note(s) : (1) NET_BUF_TYPE_&&& #define values specifically chosen as ASCII representations of the network
*               buffer types.  Memory displays of network buffers will display the network buffer TYPEs with
*               their chosen ASCII names.
*********************************************************************************************************
*/

#define  NET_BUF_TYPE_NONE                        CPU_TYPE_CREATE('N', 'O', 'N', 'E')
#define  NET_BUF_TYPE_BUF                         CPU_TYPE_CREATE('B', 'U', 'F', ' ')
#define  NET_BUF_TYPE_RX_LARGE                    CPU_TYPE_CREATE('R', 'X', 'L', 'G')
#define  NET_BUF_TYPE_TX_LARGE                    CPU_TYPE_CREATE('T', 'X', 'L', 'G')
#define  NET_BUF_TYPE_TX_SMALL                    CPU_TYPE_CREATE('T', 'X', 'S', 'M')


/*$PAGE*/
/*
*********************************************************************************************************
*                                 NETWORK BUFFER INDEX & SIZE DEFINES
*
* Note(s) : (1) (a) (1) NET_BUF_DATA_PROTOCOL_HDR_SIZE_MIN's  value is pre-#define'd in 'net_cfg_net.h' :
*
*                       (A) NET_BUF_DATA_PROTOCOL_HDR_SIZE_MIN's ideal #define'tion :
*
*                               (1) min(IF Headers)  +  min(Protocol Headers)
*
*                       (B) NET_BUF_DATA_PROTOCOL_HDR_SIZE_MIN  #define'd with hard-coded knowledge that IF &/or 
*                           ARP, IP/ICMP, IP/IGMP, IP/UDP headers have the smallest combined minimum size of all 
*                           the protocol headers :
*
*                             ARP Hdr   28       IP Hdr   20      IP Hdr   20      IP Hdr   20     IP Hdr   20
*                                              ICMP Hdr    8    IGMP Hdr    8     UDP Hdr    8    TCP Hdr   20
*                             ------------     -------------    -------------     ------------    ------------
*                             Total     28     Total      28    Total      28     Total     28    Total     40
*
*
*                   (2) NET_BUF_DATA_PROTOCOL_HDR_SIZE_MAX's  value is pre-#define'd in 'net_cfg_net.h' :
*
*                       (A) NET_BUF_DATA_PROTOCOL_HDR_SIZE_MAX's ideal #define'tion :
*
*                               (1) max(IF Headers)  +  max(Protocol Headers)
*
*                       (B) NET_BUF_DATA_PROTOCOL_HDR_SIZE_MAX  #define'd with hard-coded knowledge that IF, IP, 
*                           & TCP headers have the largest combined maximum size of all the protocol headers :
*
*                             ARP Hdr   68       IP Hdr   60      IP Hdr   60      IP Hdr   60     IP Hdr   60
*                                              ICMP Hdr   20    IGMP Hdr    8     UDP Hdr    8    TCP Hdr   60
*                             ------------     -------------    -------------     ------------    ------------
*                             Total     68     Total      80    Total      68     Total     68    Total    120
*
*
*               (b) (1) Assumes minimum ARP header size of 28 octets based on Ethernet hardware & IP protocol 
*                       addresses.  Actual ARP header size depends on actual hardware & protocol address lengths.
*
*                   (2) Assumes maximum ARP header size of 68 octets based on maximum length hardware & protocol 
*                       addresses.  Actual ARP header size depends on actual hardware & protocol address lengths.
*
*                   See 'net_arp.h  Note #2' for supported hardware & protocol types.
*
*               (c) The minimum network buffer size MUST be configured greater than the maximum network packet 
*                   header sizes so that the first of any fragmented packets always contains a complete receipt 
*                   of all frame & network packet headers.
*
*           (2) (a) Since network data value macro's appropriately convert data values from any CPU addresses,
*                   word-aligned or not; network receive & transmit packets are NOT required to ensure that
*                   network packet headers (ARP/IP/UDP/TCP/etc.) & header members will locate on CPU word-
*                   aligned addresses.  Therefore, network receive & transmit packets are NOT required to
*                   start on any specific network buffer indices.
*
*                   See also 'net_util.h  NETWORK DATA VALUE MACRO'S  Note #2b'.
*
*               (b) However, many processors & network devices may be more efficient & may even REQUIRE that 
*                   memory transfers occur on CPU word-aligned addresses or on device-specific word-aligned 
*                   addresses [e.g. processors or devices with direct memory access (DMA) capability].  
*                   Therefore, network receive & transmit packets SHOULD start at the device layer on CPU 
*                   word-aligned or device-specific word-aligned indices(/addresses) in network buffer data 
*                   areas.
*
*                   (1) (A) Receive packet   index SHOULD be configured to ensure that the device layer receive 
*                           packet is word-aligned, either CPU word-aligned or device-specific word-aligned.
*
*                       (B) Network transmit index SHOULD be configured to ensure that the device layer transmit 
*                           packet is word-aligned, either CPU word-aligned or device-specific word-aligned.
*
*                           (1) However, this assumes that a single data index may be configured that can handle 
*                               all possible combinations of network packet header lengths while still ensuring 
*                               that each device's transmit packets are word-aligned.
*
*                               This assumption is valid if & only if all combinations of network packet header 
*                               lengths are multiples of the CPU's data word size &/or specific device's word 
*                               aligment.
*
*                   (2) These data indices also assume that each interface's network buffer data area(s) are 
*                       configured to be aligned to either the CPU's data word size &/or the device-specific 
*                       word alignment.
*
*                   See also 'net_dev_cfg.c  EXAMPLE NETWORK DEVICE CONFIGURATION  Note #4'
*                          & 'lib_mem.h  MEMORY DATA VALUE MACRO'S  Note #1a'.
*********************************************************************************************************
*/

                                                                    /* ------------- NET BUF HDR/DATA IXs ------------- */
#define  NET_BUF_DATA_BASE                         0
#define  NET_BUF_DATA_PROTOCOL_HDR_BASE          NET_BUF_DATA_BASE
                                                                    /* Data ix/sizes based on max pkt hdr sizes ...     */
                                                                    /* ... (see Note #1a2).                             */
#define  NET_BUF_DATA_IX                        (NET_BUF_DATA_PROTOCOL_HDR_BASE + NET_BUF_DATA_PROTOCOL_HDR_SIZE_MAX)
#define  NET_BUF_DATA_IX_RX                      NET_BUF_DATA_BASE  /* See Note #2b1A.                                  */
#define  NET_BUF_DATA_IX_TX                      NET_BUF_DATA_IX    /* See Note #2b1B.                                  */

#define  NET_BUF_DATA_SIZE_MIN                   NET_BUF_DATA_IX
#define  NET_BUF_DATA_PROTOCOL_HDR_SIZE          NET_BUF_DATA_IX


/*$PAGE*/
/*
*********************************************************************************************************
*                                             DATA TYPES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                  NETWORK BUFFER QUANTITY DATA TYPE
*
* Note(s) : (1) (a) 'NET_BUF_QTY' pre-defined in 'net_type.h' PRIOR to all other network modules that 
*                    require network interface queue size data type.
*
*               (b) The following network interface queue size values are pre-#define'd in 'net_type.h'
*                   PRIOR to all other network modules that require network interface numbers values :
*
*                   (1) NET_BUF_NBR_MIN
*                   (2) NET_BUF_NBR_MAX
*
*                       (A) NET_BUF_NBR_MAX  SHOULD be #define'd based on 'NET_BUF_QTY' data type declared.
*********************************************************************************************************
*/

#if 0                                                           /* See Note #1.                                         */
typedef  CPU_INT16U  NET_BUF_QTY;                               /* Defines max qty of net bufs to support.              */

#define  NET_BUF_NBR_MIN                                   1
#define  NET_BUF_NBR_MAX                 DEF_INT_16U_MAX_VAL    /* See Note #1b2A.                                      */
#endif

#define  NET_BUF_NBR_RX_LARGE_MIN            NET_BUF_NBR_MIN
#define  NET_BUF_NBR_RX_LARGE_MAX            NET_BUF_NBR_MAX

#define  NET_BUF_NBR_TX_MIN                  NET_BUF_NBR_MIN
#define  NET_BUF_NBR_TX_MAX                  NET_BUF_NBR_MAX

#define  NET_BUF_NBR_TX_LARGE_MIN        DEF_INT_16U_MIN_VAL
#define  NET_BUF_NBR_TX_LARGE_MAX            NET_BUF_NBR_MAX

#define  NET_BUF_NBR_TX_SMALL_MIN        DEF_INT_16U_MIN_VAL
#define  NET_BUF_NBR_TX_SMALL_MAX            NET_BUF_NBR_MAX


/*
*********************************************************************************************************
*                                    NETWORK BUFFER SIZE DATA TYPE
*
* Note(s) : (1) NET_BUF_IX_NONE  SHOULD be #define'd based on 'NET_BUF_SIZE' data type declared.
*********************************************************************************************************
*/

typedef  CPU_INT16U  NET_BUF_SIZE;                              /* Defines   max size of net buf data.                  */

#define  NET_BUF_IX_NONE                 DEF_INT_16U_MAX_VAL    /* Define as max unsigned val (see Note #1).            */


/*
*********************************************************************************************************
*                              NETWORK BUFFER FUNCTION POINTER DATA TYPE
*********************************************************************************************************
*/

typedef  void  (*NET_BUF_FNCT)(NET_BUF  *pbuf);


/*$PAGE*/
/*
*********************************************************************************************************
*                                   NETWORK BUFFER HEADER DATA TYPE
*
*                                            NET_BUF_HDR
*                                          |-------------|
*                                          | Buffer Type |
*                                          |-------------|
*                                          | Buffer Size |
*                                          |-------------|
*                                          |    Flags    |
*                              Previous    |-------------|
*                               Buffer <----------O      |
*                                Lists     |-------------|      Next
*                                          |      O----------> Buffer
*                              Previous    |-------------|      Lists
*                               Buffer <----------O      |
*                                          |-------------|      Next
*                                          |      O----------> Buffer
*                                          |-------------|
*                                          |      O----------> Buffer
*                                          |-------------|      Timer
*                                          |             |
*                                          |      O----------> Unlink Fnct
*                                          |             |      & Obj Ptrs
*                                          |-------------|
*                                          |  Reference  |
*                                          |   Counter   |
*                                          |-------------|
*                                          |             |
*                                          |             |
*                                          |  Protocol   |
*                                          |   Header    |
*                                          |  Indices/   |
*                                          |  Lengths    |
*                                          |             |
*                                          |             |
*                                          |-------------|
*                                          |             |
*                                          |  Protocol   |
*                                          |  Controls   |
*                                          |             |
*                                          | ----------- |
*                                          |     ARP     |
*                                          | ----------- |
*                                          |     IP      |
*                                          | ----------- |
*                                          |   TCP/UDP   |
*                                          | ----------- |
*                                          |     TCP     |
*                                          | ----------- |
*                                          |    Conn     |
*                                          |-------------|
*
*
* Note(s) : (1) Protocol Header & Data indices into DATA area declared as 'CPU_INT16U' because current
*               TCP/IPv4 header sizes do NOT exceed 'CPU_INT16U' index space.
*
*           (2) 'TotLen'/'DataLen' calculate total buffer data length & 'Application' data length.
*
*               For received buffers, total buffer data length is set to the incoming packet length;
*               'Application' data length (& index) is calculated as total buffer data lengths minus
*               all protocol header lengths found in the buffer.
*
*               For transmitted buffers, 'Application' data length (& index) is set by higher-layer
*               network protocols or the application layer; total buffer data length is calculated
*               as the 'Application' data length plus all protocol header lengths inserted into the
*               buffer.
*
*           (3) The following variables ideally declared as specific TCP data types; declared as CPU
*               data types because TCP data types NOT defined until 'net_tcp.h' (see 'net.h  NETWORK
*               INCLUDE FILES') :
*
*               (a) TCP transmit acknowledgement code variables ideally declared as 'NET_TCP_ACK_CODE';
*                       declared as 'CPU_INT08U'.
*********************************************************************************************************
*/
/*$PAGE*/
                                                        /* ----------------------- NET BUF HDR ------------------------ */
typedef  struct  net_buf_hdr {
    NET_TYPE               Type;                        /* Buf type cfg'd @ init.                                       */
    NET_BUF_SIZE           Size;                        /* Buf size cfg'd @ init.                                       */
    CPU_INT16U             Flags;                       /* Buf flags.                                                   */

    NET_BUF_QTY            ID;                          /* Buf id.                                                      */
    CPU_INT08U             RefCtr;                      /* Nbr of ext refs pointing to this buf.                        */

    NET_IF_NBR             IF_Nbr;                      /* Buf's rx or base IF nbr.                                     */
    NET_IF_NBR             IF_NbrTx;                    /* Buf's tx         IF nbr.                                     */


    NET_BUF               *PrevPrimListPtr;             /* Ptr to PREV prim list.                                       */
    NET_BUF               *NextPrimListPtr;             /* Ptr to NEXT prim list.                                       */

    NET_BUF               *PrevSecListPtr;              /* Ptr to PREV sec  list.                                       */
    NET_BUF               *NextSecListPtr;              /* Ptr to NEXT sec  list.                                       */

    NET_BUF               *PrevTxListPtr;               /* Ptr to NEXT tx   list buf.                                   */
    NET_BUF               *NextTxListPtr;               /* Ptr to PREV tx   list buf.                                   */

    NET_BUF               *PrevBufPtr;                  /* Ptr to PREV buf.                                             */
    NET_BUF               *NextBufPtr;                  /* Ptr to NEXT buf.                                             */

    NET_TMR               *TmrPtr;                      /* Ptr to buf TMR.                                              */

    NET_BUF_FNCT           UnlinkFnctPtr;               /* Ptr to fnct used to unlink buf from multiple refs.           */
    void                  *UnlinkObjPtr;                /* Ptr to obj       to unlink buf from.                         */



    NET_PROTOCOL_TYPE      ProtocolHdrType;             /* Cur       hdr protocol type.                                 */
    NET_PROTOCOL_TYPE      ProtocolHdrTypeIF;           /* IF        hdr protocol type.                                 */
    NET_PROTOCOL_TYPE      ProtocolHdrTypeIF_Sub;       /* IF        sub-protocol type.                                 */
    NET_PROTOCOL_TYPE      ProtocolHdrTypeNet;          /* Net       hdr protocol type.                                 */
    NET_PROTOCOL_TYPE      ProtocolHdrTypeNetSub;       /* Net       sub-protocol type.                                 */
    NET_PROTOCOL_TYPE      ProtocolHdrTypeTransport;    /* Transport hdr protocol type.                                 */


    CPU_INT16U             IF_HdrIx;                    /* IF                   hdr  ix  (in DATA area).                */
    CPU_INT16U             IF_HdrLen;                   /* IF                   hdr  len (in octets   ).                */

#ifdef  NET_ARP_MODULE_PRESENT
    CPU_INT16U             ARP_MsgIx;                   /* ARP                  msg  ix  (in DATA area).                */
    CPU_INT16U             ARP_MsgLen;                  /* ARP                  msg  len (in octets   ).                */
#endif

    CPU_INT16U             IP_HdrIx;                    /* IP                   hdr  ix  (in DATA area).                */
    CPU_INT16U             IP_HdrLen;                   /* IP                   hdr  len (in octets   ).                */
    CPU_INT16U             IP_TotLen;                   /* IP                   tot  len (in octets   ).                */
    CPU_INT16U             IP_DataLen;                  /* IP pkt/frag          data len (in octets   ).                */
    CPU_INT16U             IP_DatagramLen;              /* IP complete datagram data len (in octets   ).                */

    CPU_INT16U             ICMP_MsgIx;                  /* ICMP                 msg  ix  (in DATA area).                */
    CPU_INT16U             ICMP_MsgLen;                 /* ICMP                 msg  len (in octets   ).                */
    CPU_INT16U             ICMP_HdrLen;                 /* ICMP                 hdr  len (in octets   ).                */

#ifdef  NET_IGMP_MODULE_PRESENT
    CPU_INT16U             IGMP_MsgIx;                  /* IGMP                 msg  ix  (in DATA area).                */
    CPU_INT16U             IGMP_MsgLen;                 /* IGMP                 msg  len (in octets   ).                */
#endif

    CPU_INT16U             TCP_UDP_HdrIx;               /* TCP/UDP              hdr  ix  (in DATA area).                */
    CPU_INT16U             TCP_UDP_HdrLen;              /* TCP/UDP              hdr  len (in octets   ).                */
    CPU_INT16U             TCP_UDP_TotLen;              /* TCP/UDP          tot      len (in octets   ).                */
    CPU_INT16U             TCP_UDP_DataLen;             /* TCP/UDP          tot data len (in octets   ).                */


    CPU_INT16U             DataIx;                      /* App                  DATA ix  (in DATA area).                */
    NET_BUF_SIZE           DataLen;                     /* App                  DATA len (in octets   ).                */

    NET_BUF_SIZE           TotLen;                      /* ALL                  DATA len (in octets   ).                */



#ifdef  NET_ARP_MODULE_PRESENT
    CPU_INT08U            *ARP_AddrHW_Ptr;              /* Ptr to ARP hw       addr.                                    */
    CPU_INT08U            *ARP_AddrProtocolPtr;         /* Ptr to ARP protocol addr.                                    */
#endif



    CPU_INT16U             IP_ID;                       /* IP datagram id.                                              */

    CPU_INT16U             IP_Flags_FragOffset;         /* IP rx flags/frag offset.                                     */

    CPU_INT16U             IP_FragSizeTot;              /* Tot IP rx frag size.                                         */
    CPU_INT16U             IP_FragSizeCur;              /* Cur IP rx frag size.                                         */

    NET_IP_ADDR            IP_AddrSrc;                  /* IP src             addr.                                     */
    NET_IP_ADDR            IP_AddrDest;                 /* IP dest            addr.                                     */
    NET_IP_ADDR            IP_AddrNextRoute;            /* IP tx 'Next-Route' addr.                                     */
    NET_IP_ADDR            IP_AddrNextRouteNetOrder;    /* IP tx 'Next-Route' addr in net-order.                        */

    NET_BUF               *IP_OptPtr;                   /* Ptr to IP rx opts.                                           */



/*$PAGE*/
    NET_PORT_NBR           TCP_UDP_PortSrc;             /* TCP/UDP rx src  port.                                        */
    NET_PORT_NBR           TCP_UDP_PortDest;            /* TCP/UDP rx dest port.                                        */


#ifdef  NET_TCP_MODULE_PRESENT
    CPU_INT16U             TCP_HdrLen_Flags;            /* TCP hdr len/flags.                                           */

    NET_TCP_SEG_SIZE       TCP_SegLenInit;              /* TCP init  seg len.                                           */
    NET_TCP_SEG_SIZE       TCP_SegLen;                  /* TCP       seg len [i.e. data len &/or sync/close ctrl(s)].   */
    NET_TCP_SEG_SIZE       TCP_SegLenLast;              /* TCP last  seg len [i.e. last len tx'd].                      */
    NET_TCP_SEG_SIZE       TCP_SegLenData;              /* TCP data  seg len [i.e. data len].                           */
    CPU_INT16U             TCP_SegReTxCtr;              /* Indicates nbr seg re-tx's.                                   */
    CPU_BOOLEAN            TCP_SegSync;                 /* Indicates TCP sync  seg.                                     */
    CPU_BOOLEAN            TCP_SegClose;                /* Indicates TCP close seg.                                     */
    CPU_BOOLEAN            TCP_SegReset;                /* Indicates TCP reset seg.                                     */
    CPU_BOOLEAN            TCP_SegAck;                  /* Indicates TCP ack   seg.                                     */
    CPU_BOOLEAN            TCP_SegAckTxd;               /* Indicates TCP ack tx'd        for rx'd seg.                  */
    CPU_INT08U             TCP_SegAckTxReqCode;         /* Indicates TCP ack tx req code for rx'd seg (see Note #3a).   */

    NET_TCP_SEQ_NBR        TCP_SeqNbrInit;              /* TCP init  seq nbr.                                           */
    NET_TCP_SEQ_NBR        TCP_SeqNbrLast;              /* TCP last  seq nbr                                            */
    NET_TCP_SEQ_NBR        TCP_SeqNbr;                  /* TCP       seq nbr                                            */
    NET_TCP_SEQ_NBR        TCP_AckNbr;                  /* TCP       ack nbr                                            */
    NET_TCP_SEQ_NBR        TCP_AckNbrLast;              /* TCP last  ack nbr                                            */
    NET_TCP_SEG_SIZE       TCP_MaxSegSize;              /* TCP max   seg size.                                          */
    NET_TCP_WIN_SIZE       TCP_WinSize;                 /* TCP       win size.                                          */
    NET_TCP_WIN_SIZE       TCP_WinSizeLast;             /* TCP last  win size.                                          */

    NET_TCP_TX_RTT_TS_MS   TCP_RTT_TS_Rxd_ms;           /* TCP RTT TS @ seg rx'd (in ms).                               */
    NET_TCP_TX_RTT_TS_MS   TCP_RTT_TS_Txd_ms;           /* TCP RTT TS @ seg tx'd (in ms).                               */

    CPU_INT16U             TCP_Flags;                   /* TCP tx flags.                                                */
#endif


#ifdef  NET_CONN_MODULE_PRESENT
    NET_CONN_ID            Conn_ID;                     /* Net             conn id.                                     */
    NET_CONN_ID            Conn_ID_Transport;           /* Transport layer conn id.                                     */
    NET_CONN_ID            Conn_ID_App;                 /* App       layer conn id.                                     */

    CPU_INT08U             ConnType;                    /* Conn type.                                                   */
#endif


} NET_BUF_HDR;


/*$PAGE*/
/*
*********************************************************************************************************
*                                      NETWORK BUFFER DATA TYPE
*
*                                              NET_BUF
*                                          |-------------|
*                                          |             |
*                                          |   Buffer    |
*                                          |   Header    |
*                                          |             |
*                                          |-------------|
*                                          |             |
*                                          |   Buffer    |
*                                          |    Data     |
*                                          |   Pointer   |
*                                          |             |
*                                          |-------------|
*
* Note(s) : (1) Forced (32-bit) word-alignment at start of network buffer NOT required since first data
*               member 'Hdr.Type' is is declared as 'NET_TYPE', equivalent to 'CPU_INT32U'.
*
*           (2) (a) 'DataPtr' buffer data area is storage for both Protocol Headers & Application data.
*
*               (b) 'DataPtr' buffer data area SHOULD be declared with an additional CPU data word size
*                    so that devices may efficiently & safely read or write data without overflowing the
*                    data area.
*
*                   This additional CPU data word size does NOT increase the overall useable network
*                   buffer 'Data' size (see also 'net_buf.c  NetBuf_GetMaxSize()  Note #1').
*********************************************************************************************************
*/

                                                                /* --------------------- NET BUF ---------------------- */
struct  net_buf {
    NET_BUF_HDR   Hdr;                                          /*        Net buf hdr.                                  */
    CPU_INT08U   *DataPtr;                                      /* Ptr to net buf data area (see Note #2).              */
};


/*$PAGE*/
/*
*********************************************************************************************************
*                                   NETWORK BUFFER POOLS DATA TYPE
*
* Note(s) : (1) Each network interface & device configures & maintains its own network buffer pools.
*********************************************************************************************************
*/

                                                                /* ------------------ NET BUF POOLS ------------------- */
typedef  struct  net_buf_pools {
    MEM_POOL       NetBufPool;                                  /* Net buf                         pool.                */
    MEM_POOL       RxBufLargePool;                              /* Net buf rx large data area      pool.                */
    MEM_POOL       TxBufLargePool;                              /* Net buf tx large data area      pool.                */
    MEM_POOL       TxBufSmallPool;                              /* Net buf tx small data area      pool.                */

    NET_STAT_POOL  NetBufStatPool;                              /* Net buf                    stat pool.                */
    NET_STAT_POOL  RxBufLargeStatPool;                          /* Net buf rx large data area stat pool.                */
    NET_STAT_POOL  TxBufLargeStatPool;                          /* Net buf tx large data area stat pool.                */
    NET_STAT_POOL  TxBufSmallStatPool;                          /* Net buf tx small data area stat pool.                */
} NET_BUF_POOLS;


/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/

NET_BUF_EXT  NET_BUF_POOLS  NetBuf_PoolsTbl[NET_IF_NBR_IF_TOT];

NET_BUF_EXT  NET_BUF_QTY    NetBuf_ID_Ctr;                      /* Global buf ID ctr.                                   */


/*$PAGE*/
/*
*********************************************************************************************************
*                                               MACRO'S
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                           NET_BUF_GET_ID()
*
* Description : Get next network buffer identification number.
*
* Argument(s) : id      Variable that will receive the returned identification number.
*
* Return(s)   : none.
*
* Caller(s)   : NetBuf_Get().
*
*               This macro is an INTERNAL network buffer suite macro & SHOULD NOT be called by
*               application function(s).
*
* Note(s)     : (1) Network buffer identification number is returned in host-order.
*********************************************************************************************************
*/

#define  NET_BUF_GET_ID(id)                     do { NET_UTIL_VAL_COPY_16(&(id), &NetBuf_ID_Ctr); \
                                                     NetBuf_ID_Ctr++;                             } while (0)


/*$PAGE*/
/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void           NetBuf_Init                       (void);


                                                                            /* ----------- BUF ALLOC FNCTS ------------ */
void           NetBuf_PoolInit                   (NET_IF_NBR        if_nbr,
                                                  NET_TYPE          type,
                                                  void             *pmem_base_addr,
                                                  CPU_SIZE_T        mem_size,
                                                  CPU_SIZE_T        blk_nbr,
                                                  CPU_SIZE_T        blk_size,
                                                  CPU_SIZE_T        blk_align,
                                                  CPU_SIZE_T       *poctets_reqd,
                                                  NET_ERR          *perr);

void           NetBuf_PoolCfgValidate            (NET_DEV_CFG      *pdev_cfg,
                                                  NET_ERR          *perr);


NET_BUF       *NetBuf_Get                        (NET_IF_NBR        if_nbr,
                                                  NET_TRANSACTION   transaction,
                                                  NET_BUF_SIZE      size,
                                                  NET_BUF_SIZE      ix,
                                                  NET_BUF_SIZE     *pix_offset,
                                                  CPU_INT16U        flags,
                                                  NET_ERR          *perr);

CPU_INT08U    *NetBuf_GetDataPtr                 (NET_IF           *pif,
                                                  NET_TRANSACTION   transaction,
                                                  NET_BUF_SIZE      size,
                                                  NET_BUF_SIZE      ix_start,
                                                  NET_BUF_SIZE     *pix_offset,
                                                  NET_BUF_SIZE     *p_data_size,
                                                  NET_TYPE         *ptype,
                                                  NET_ERR          *perr);

NET_BUF_SIZE   NetBuf_GetMaxSize                 (NET_IF_NBR        if_nbr,
                                                  NET_TRANSACTION   transaction,
                                                  NET_BUF          *pbuf,
                                                  NET_BUF_SIZE      ix_start);


void           NetBuf_Free                       (NET_BUF          *pbuf);

NET_BUF_QTY    NetBuf_FreeBuf                    (NET_BUF          *pbuf,
                                                  NET_CTR          *pctr);


NET_BUF_QTY    NetBuf_FreeBufList                (NET_BUF          *pbuf_list,
                                                  NET_CTR          *pctr);

NET_BUF_QTY    NetBuf_FreeBufQ_PrimList          (NET_BUF          *pbuf_q,
                                                  NET_CTR          *pctr);

NET_BUF_QTY    NetBuf_FreeBufQ_SecList           (NET_BUF          *pbuf_q,
                                                  NET_CTR          *pctr,
                                                  NET_BUF_FNCT      pfnct_unlink);


void           NetBuf_FreeBufDataAreaRx          (NET_IF_NBR        if_nbr,
                                                  CPU_INT08U       *pbuf_data);


/*$PAGE*/
                                                                            /* ------------ BUF API FNCTS ------------- */
void           NetBuf_DataRd                     (NET_BUF          *pbuf,
                                                  NET_BUF_SIZE      ix,
                                                  NET_BUF_SIZE      len,
                                                  CPU_INT08U       *pdest,
                                                  NET_ERR          *perr);

void           NetBuf_DataWr                     (NET_BUF          *pbuf,
                                                  NET_BUF_SIZE      ix,
                                                  NET_BUF_SIZE      len,
                                                  CPU_INT08U       *psrc,
                                                  NET_ERR          *perr);

void           NetBuf_DataCopy                   (NET_BUF          *pbuf_dest,
                                                  NET_BUF          *pbuf_src,
                                                  NET_BUF_SIZE      ix_dest,
                                                  NET_BUF_SIZE      ix_src,
                                                  NET_BUF_SIZE      len,
                                                  NET_ERR          *perr);


                                                                            /* ----------- BUF STATUS FNCTS ----------- */
CPU_BOOLEAN    NetBuf_IsUsed                     (NET_BUF          *pbuf);



NET_STAT_POOL  NetBuf_PoolStatGet                (NET_IF_NBR        if_nbr);

void           NetBuf_PoolStatResetMaxUsed       (NET_IF_NBR        if_nbr);


NET_STAT_POOL  NetBuf_RxLargePoolStatGet         (NET_IF_NBR        if_nbr);

void           NetBuf_RxLargePoolStatResetMaxUsed(NET_IF_NBR        if_nbr);


NET_STAT_POOL  NetBuf_TxLargePoolStatGet         (NET_IF_NBR        if_nbr);

void           NetBuf_TxLargePoolStatResetMaxUsed(NET_IF_NBR        if_nbr);


NET_STAT_POOL  NetBuf_TxSmallPoolStatGet         (NET_IF_NBR        if_nbr);

void           NetBuf_TxSmallPoolStatResetMaxUsed(NET_IF_NBR        if_nbr);


/*$PAGE*/
/*
*********************************************************************************************************
*                                        CONFIGURATION ERRORS
*********************************************************************************************************
*/

