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
*                                          NETWORK IGMP LAYER
*                                 (INTERNET GROUP MANAGEMENT PROTOCOL)
*
* Filename      : net_igmp.h
* Version       : V2.11.02
* Programmer(s) : SR
*********************************************************************************************************
* Note(s)       : (1) Internet Group Management Protocol ONLY required for network interfaces that require
*                     reception of IP class-D (multicast) packets (see RFC #1112, Section 3 'Levels of 
*                     Conformance : Level 2').
*
*                     (a) IGMP is NOT required for the transmission of IP class-D (multicast) packets 
*                         (see RFC #1112, Section 3 'Levels of Conformance : Level 1').
*
*                 (2) Supports Internet Group Management Protocol version 1, as described in RFC #1112
*                     with the following restrictions/constraints :
*
*                     (a) Only one socket may receive datagrams for a specific host group address & port
*                         number at any given time.
*
*                         See also 'net_sock.c  Note #1e'.
*
*                     (b) #### Since sockets do NOT automatically leave IGMP host groups when closed, 
*                         it is the application's responsibility to leave each host group once it is 
*                         no longer needed by the application.
*
*                     (c) #### Transmission of IGMP Query Messages NOT currently supported.
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) IGMP Layer module is required only for IP multicast reception & IGMP group management 
*               (see 'net_igmp.h  Note #1').
*
*           (2) The following IGMP-module-present configuration value MUST be pre-#define'd 
*               in 'net_cfg_net.h' PRIOR to all other network modules that require IGMP Layer 
*               configuration (see 'net_cfg_net.h  IGMP LAYER CONFIGURATION  Note #2b') :
*
*                   NET_IGMP_MODULE_PRESENT
*********************************************************************************************************
*/

#ifdef   NET_IGMP_MODULE_PRESENT                                /* See Note #2.                                         */


/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/

#if ((defined(NET_IGMP_MODULE)) && \
     (defined(NET_GLOBALS_EXT)))
#define  NET_IGMP_EXT
#else
#define  NET_IGMP_EXT  extern
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                         IGMP HEADER DEFINES
*********************************************************************************************************
*/

#define  NET_IGMP_HDR_VER_MASK                          0xF0u
#define  NET_IGMP_HDR_VER_SHIFT                            4u
#define  NET_IGMP_HDR_VER                                  1u   /* Supports IGMPv1 ONLY (see 'net_igmp.h  Note #2').    */

#define  NET_IGMP_HDR_TYPE_MASK                         0x0Fu


/*
*********************************************************************************************************
*                                      IGMP MESSAGE SIZE DEFINES
*
* Note(s) : (1) RFC #1112, Appendix I, Section 'State Transition Diagram' states that "to be valid, the
*               ... [received] message[s] must be at least 8 octets long".
*********************************************************************************************************
*/

#define  NET_IGMP_HDR_SIZE                                 8
#define  NET_IGMP_MSG_SIZE_MIN             NET_IGMP_HDR_SIZE    /* See Note #1.                                         */

#define  NET_IGMP_MSG_LEN                  NET_IGMP_HDR_SIZE
#define  NET_IGMP_MSG_LEN_DATA                             0


/*
*********************************************************************************************************
*                                      IGMP MESSAGE TYPE DEFINES
*
* Note(s) : (1) RFC #1112, Appendix I, Section 'Type' states that "there are two types of IGMP message[s] 
*               ... to hosts" :
*
*               (a) 1 = Host Membership Query
*               (b) 2 = Host Membership Report
*********************************************************************************************************
*/

#define  NET_IGMP_MSG_TYPE_QUERY                           1u   /* See Note #1a.                                        */
#define  NET_IGMP_MSG_TYPE_REPORT                          2u   /* See Note #1b.                                        */


/*$PAGE*/
/*
*********************************************************************************************************
*                                       IGMP HOST GROUP STATES
*
*                                         -------------------
*                                         |                 |
*                                         |                 |
*                                         |                 |
*                                         |                 |
*                            ------------>|      FREE       |<------------
*                            |            |                 |            |
*                            |            |                 |            |
*                            |            |                 |            |
*                            |            |                 |            |
*                            |            -------------------            | (1e) LEAVE GROUP
*                            |                     |                     |
*                            | (1e) LEAVE GROUP    | (1a) JOIN GROUP     |
*                            |                     |                     |
*                   -------------------            |            -------------------
*                   |                 |<------------            |                 |
*                   |                 |                         |                 |
*                   |                 |<------------------------|                 |
*                   |                 |  (1c) QUERY  RECEIVED   |                 |
*                   |    DELAYING     |                         |      IDLE       |
*                   |                 |------------------------>|                 |
*                   |                 |  (1b) REPORT RECEIVED   |                 |
*                   |                 |                         |                 |
*                   |                 |------------------------>|                 |
*                   -------------------  (1d) TIMER  EXPIRED    -------------------
*
*
* Note(s) : (1) RFC #1112, Appendix I, Sections 'Informal Protocol Description' & 'State Transition Diagram' 
*               outline the IGMP state diagram :
*
*               (a) An application performs a request to join a multicast group.  A new IGMP host group
*                   entry is allocated from the IGMP host group pool & inserted into the IGMP Host Group
*                   List in the 'DELAYING' state.  A timer is started to transmit a report to inform the
*                   IGMP enabled router.
*
*               (b) The host receives a valid IGMP Host Membership Report message, on the interface the
*                   host has joined the group on.  The timer is stopped & the host group transitions 
*                   into the 'IDLE' state.
*
*               (c) A query is received for that IGMP group.  The host group transitions into the 'DELAYING'
*                   state & a timer is started to transmit a report to inform the IGMP router.
*
*               (d) The report delay timer expires for the group & a report for that group is transmitted.
*                   The host group then transitions into the 'IDLE' state.
*
*               (e) The application leaves the group on the interface; the IGMP host group is then freed.
*
*           (2) RFC #1112, Section 7.2 states that "to support IGMP, every level 2 host must join the 
*               all-hosts group (address 224.0.0.1) ... and must remain a member for as long as the 
*               host is active".
*
*               (a) Therefore, the group 224.0.0.1 is considered a special group, & is always in the 
*                   'STATIC' state, meaning it neither can be deleted, nor be put in the 'IDLE' or 
*                   'DELAYING' state.
*
*               (b) However, since network interfaces are not yet enabled at IGMP initialization time, 
*                   the host delays joining the "all-hosts" group on an interface until the first group 
*                   membership is requested on an interface.
*********************************************************************************************************
*/

#define  NET_IGMP_HOST_GRP_STATE_NONE                      0u
#define  NET_IGMP_HOST_GRP_STATE_FREE                      1u
#define  NET_IGMP_HOST_GRP_STATE_DELAYING                  2u
#define  NET_IGMP_HOST_GRP_STATE_IDLE                      3u

#define  NET_IGMP_HOST_GRP_STATE_STATIC                   10u   /* See Note #2.                                         */


/*$PAGE*/
/*
*********************************************************************************************************
*                                         IGMP REPORT DEFINES
*
* Note(s) : (1) RFC #1112, Appendix I, Section 'Informal Protocol Description' states that :
*
*               (a) "When a host joins a new group, it should immediately transmit a Report for that
*                    group [...].  To cover the possibility of the initial Report being lost or damaged,
*                    it is recommended that it be repeated once or twice after short delays."
*
*                    The delay between the report transmissions is set to 2 seconds in this implementation.
*
*               (b) "When a host receives a Query [...] it starts a report delay timer for each of its
*                    group memberships on the network interface of the incoming Query.  Each timer is
*                    set to a different, randomly-chosen value between zero and [10] seconds."
*
*           (2) When a transmit error occurs when attempting to transmit an IGMP report, a new timer 
*               is set with a delay of NET_IGMP_HOST_GRP_REPORT_DLY_RETRY_SEC seconds to retransmit 
*               the report.
*********************************************************************************************************
*/

#define  NET_IGMP_HOST_GRP_REPORT_DLY_JOIN_SEC             2    /* See Note #1a.                                        */
                                                                /* See Note #1b.                                        */
#define  NET_IGMP_HOST_GRP_REPORT_DLY_MIN_SEC              0
#define  NET_IGMP_HOST_GRP_REPORT_DLY_MAX_SEC             10

#define  NET_IGMP_HOST_GRP_REPORT_DLY_RETRY_SEC            2    /* See Note #2.                                         */


/*
*********************************************************************************************************
*                                          IGMP FLAG DEFINES
*********************************************************************************************************
*/

                                                                /* ------------------ NET IGMP FLAGS ------------------ */
#define  NET_IGMP_FLAG_NONE                       DEF_BIT_NONE
#define  NET_IGMP_FLAG_USED                       DEF_BIT_00    /* IGMP host grp cur used; i.e. NOT in free pool.       */


/*
*********************************************************************************************************
*                                          IGMP TYPE DEFINES
*
* Note(s) : (1) NET_IGMP_TYPE_&&& #define values specifically chosen as ASCII representations of the IGMP
*               types.  Memory displays of IGMP types will display with their chosen ASCII names.
*********************************************************************************************************
*/

#define  NET_IGMP_TYPE_NONE                       CPU_TYPE_CREATE('N', 'O', 'N', 'E')
#define  NET_IGMP_TYPE_HOST_GRP                   CPU_TYPE_CREATE('I', 'G', 'M', 'P')


/*$PAGE*/
/*
*********************************************************************************************************
*                                             DATA TYPES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                 IGMP HOST GROUP QUANTITY DATA TYPE
*
* Note(s) : (1) NET_IGMP_HOST_GRP_NBR_MAX  SHOULD be #define'd based on 'NET_IGMP_HOST_GRP_QTY' data type
*               declared.
*********************************************************************************************************
*/

typedef  CPU_INT16U  NET_IGMP_HOST_GRP_QTY;                     /* Defines max qty of IGMP host groups to support.      */

#define  NET_IGMP_HOST_GRP_NBR_MIN                         1
#define  NET_IGMP_HOST_GRP_NBR_MAX       DEF_INT_16U_MAX_VAL    /* See Note #1.                                         */


/*
*********************************************************************************************************
*                                   IGMP HOST GROUP STATE DATA TYPE
*********************************************************************************************************
*/

typedef  CPU_INT08U  NET_IGMP_HOST_GRP_STATE;


/*$PAGE*/
/*
*********************************************************************************************************
*                                             IGMP HEADER
*
* Note(s) : (1) See RFC #1112, Appendix I for IGMP packet header format.
*
*           (2) IGMP Version Number & Message Type are encoded in the first octet of an IGMP header as follows :
*
*                         7 6 5 4   3 2 1 0
*                       ---------------------
*                       |  V E R  | T Y P E |
*                       ---------------------
*
*                   where
*                           VER         IGMP version; currently 1 (see 'net_igmp.h  Note #2')
*                           TYPE        IGMP message type         (see 'net_igmp.h  IGMP MESSAGE TYPE DEFINES)
*********************************************************************************************************
*/

                                                                /* ------------------- NET IGMP HDR ------------------- */
typedef  struct  net_igmp_hdr {
    CPU_INT08U      Ver_Type;                                   /* IGMP pkt  ver/type (see Note #2).                    */
    CPU_INT08U      Unused;
    CPU_INT16U      ChkSum;                                     /* IGMP pkt  chk sum.                                   */
    NET_IP_ADDR     AddrGrp;                                    /* IP   host grp addr.                                  */
} NET_IGMP_HDR;


/*
*********************************************************************************************************
*                                     IGMP HOST GROUP DATA TYPES
*
*                                          NET_IGMP_HOST_GRP
*                                         |-----------------|
*                                         | Host Group Type |
*                           Previous      |-----------------|
*                          Host Group <------------O        |
*                                         |-----------------|        Next
*                                         |        O------------> Host Group
*                                         |-----------------|
*                                         |        O------------> Host Group
*                                         |-----------------|        Timer
*                                         |    Interface    |
*                                         |     Number      |
*                                         |-----------------|
*                                         |   IP Address    |
*                                         |-----------------|
*                                         |      State      |
*                                         |-----------------|
*                                         |    Reference    |
*                                         |     Counter     |
*                                         |-----------------|
*
*
* Note(s) : (1) Forced (32-bit) word-alignment at start of IGMP host group cache NOT required since first
*               data member 'Type' is is declared as 'NET_TYPE', equivalent to 'CPU_INT32U'.
*********************************************************************************************************
*/

                                                                /* ---------------- NET IGMP HOST GRP ----------------- */
typedef  struct  net_igmp_host_grp  NET_IGMP_HOST_GRP;

struct  net_igmp_host_grp {
    NET_TYPE                  Type;                             /* Type cfg'd @ init : NET_IGMP_TYPE_HOST_GRP.          */

    NET_IGMP_HOST_GRP        *PrevPtr;                          /* Ptr to PREV IGMP host grp.                           */
    NET_IGMP_HOST_GRP        *NextPtr;                          /* Ptr to NEXT IGMP host grp.                           */

    NET_TMR                  *TmrPtr;                           /* Ptr to host grp TMR.                                 */

    NET_IF_NBR                IF_Nbr;                           /* IGMP   host grp IF nbr.                              */
    NET_IP_ADDR               AddrGrp;                          /* IGMP   host grp IP addr.                             */

    NET_IGMP_HOST_GRP_STATE   State;                            /* IGMP   host grp state.                               */
    CPU_INT16U                RefCtr;                           /* IGMP   host grp ref ctr.                             */
    CPU_INT16U                Flags;                            /* IGMP   host grp flags.                               */
};


/*$PAGE*/
/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/

NET_IGMP_EXT  NET_IGMP_HOST_GRP   NetIGMP_HostGrpTbl[NET_IGMP_CFG_MAX_NBR_HOST_GRP];
NET_IGMP_EXT  NET_IGMP_HOST_GRP  *NetIGMP_HostGrpPoolPtr;        /* Ptr to pool of free host grp.                       */
NET_IGMP_EXT  NET_STAT_POOL       NetIGMP_HostGrpPoolStat;

NET_IGMP_EXT  NET_IGMP_HOST_GRP  *NetIGMP_HostGrpListHead;       /* Ptr to head of IGMP Host Grp List.                  */

NET_IGMP_EXT  CPU_BOOLEAN         NetIGMP_AllHostsJoinedOnIF[NET_IF_NBR_IF_TOT];

NET_IGMP_EXT  RAND_NBR            NetIGMP_RandSeed;


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void         NetIGMP_Init               (void);



                                                                    /* ------------- GRP MEMBERSHIP FNCTS ------------- */
CPU_BOOLEAN  NetIGMP_HostGrpJoin        (NET_IF_NBR    if_nbr,
                                         NET_IP_ADDR   addr_grp,
                                         NET_ERR      *perr);

CPU_BOOLEAN  NetIGMP_HostGrpJoinHandler (NET_IF_NBR    if_nbr,
                                         NET_IP_ADDR   addr_grp,
                                         NET_ERR      *perr);


CPU_BOOLEAN  NetIGMP_HostGrpLeave       (NET_IF_NBR    if_nbr,
                                         NET_IP_ADDR   addr_grp,
                                         NET_ERR      *perr);

CPU_BOOLEAN  NetIGMP_HostGrpLeaveHandler(NET_IF_NBR    if_nbr,
                                         NET_IP_ADDR   addr_grp,
                                         NET_ERR      *perr);


CPU_BOOLEAN  NetIGMP_IsGrpJoinedOnIF    (NET_IF_NBR    if_nbr,
                                         NET_IP_ADDR   addr_grp);



                                                                    /* ------------------- RX FNCTS ------------------- */
void         NetIGMP_Rx                 (NET_BUF      *pbuf,
                                         NET_ERR      *perr);


/*$PAGE*/
/*
*********************************************************************************************************
*                                        CONFIGURATION ERRORS
*********************************************************************************************************
*/

#ifndef  NET_IGMP_CFG_MAX_NBR_HOST_GRP
#error  "NET_IGMP_CFG_MAX_NBR_HOST_GRP        not #define'd in 'net_cfg.h'     "
#error  "                               [MUST be  >= NET_IGMP_HOST_GRP_NBR_MIN]"
#error  "                               [     &&  <= NET_IGMP_HOST_GRP_NBR_MAX]"

#elif   (DEF_CHK_VAL(NET_IGMP_CFG_MAX_NBR_HOST_GRP,      \
                     NET_IGMP_HOST_GRP_NBR_MIN,          \
                     NET_IGMP_HOST_GRP_NBR_MAX) != DEF_OK)
#error  "NET_IGMP_CFG_MAX_NBR_HOST_GRP  illegally #define'd in 'net_cfg.h'     "
#error  "                               [MUST be  >= NET_IGMP_HOST_GRP_NBR_MIN]"
#error  "                               [     &&  <= NET_IGMP_HOST_GRP_NBR_MAX]"
#endif


/*
*********************************************************************************************************
*                                             MODULE END
*
* Note(s) : (1) See 'net_igmp.h  MODULE'.
*********************************************************************************************************
*/

#endif                                                          /* End of IGMP module include (see Note #1).            */

