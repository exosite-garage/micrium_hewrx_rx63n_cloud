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
*                                          NETWORK UDP LAYER
*                                      (USER DATAGRAM PROTOCOL)
*
* Filename      : net_udp.h
* Version       : V2.11.02
* Programmer(s) : ITJ
*********************************************************************************************************
* Note(s)       : (1) Supports User Datagram Protocol as described in RFC #768.
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/

#if ((defined(NET_UDP_MODULE)) && \
     (defined(NET_GLOBALS_EXT)))
#define  NET_UDP_EXT
#else
#define  NET_UDP_EXT  extern
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                          UDP APPLICATION-PROTOCOL-INTERFACE SELECT DEFINES
*
* Note(s) : (1) The following UDP values MUST be pre-#define'd in 'net_def.h' PRIOR to 'net_cfg.h' so 
*               that the developer can configure UDP for the desired application receive demultiplex
*               selection (see 'net_def.h  UDP LAYER DEFINES  Note #1') :
*
*                   NET_UDP_APP_API_SEL_SOCK
*                   NET_UDP_APP_API_SEL_APP
*                   NET_UDP_APP_API_SEL_SOCK_APP
*********************************************************************************************************
*/

#if 0                                                           /* See Note #1.                                         */
#define  NET_UDP_APP_API_SEL_NONE                          0u
#define  NET_UDP_APP_API_SEL_SOCK                          1u
#define  NET_UDP_APP_API_SEL_APP                           2u
#define  NET_UDP_APP_API_SEL_SOCK_APP                      3u
#endif


/*
*********************************************************************************************************
*                                         UDP HEADER DEFINES
*
* Note(s) : (1) The following UDP values MUST be pre-#define'd in 'net_def.h' PRIOR to 'net_buf.h' so that
*               the Network Buffer Module can configure minimum/maximum buffer header sizes (see 'net_def.h  
*               UDP LAYER DEFINES' & 'net_buf.h  NETWORK BUFFER INDEX & SIZE DEFINES  Note #1a') :
*
*               (a) NET_UDP_HDR_SIZE_MIN                   8
*               (b) NET_UDP_HDR_SIZE_MAX                   8
*********************************************************************************************************
*/

#define  NET_UDP_HDR_SIZE                                  8    /*  = sizeof(NET_UDP_HDR)                               */
#if 0                                                           /* See Note #1.                                         */
#define  NET_UDP_HDR_SIZE_MIN                            NET_UDP_HDR_SIZE
#define  NET_UDP_HDR_SIZE_MAX                            NET_UDP_HDR_SIZE
#endif


#define  NET_UDP_PSEUDO_HDR_SIZE                          12    /*  = sizeof(NET_UDP_PSEUDO_HDR)                        */


#define  NET_UDP_PORT_NBR_RESERVED                       NET_PORT_NBR_RESERVED
#define  NET_UDP_PORT_NBR_NONE                           NET_UDP_PORT_NBR_RESERVED


#define  NET_UDP_HDR_CHK_SUM_POS_ZERO                 0x0000u
#define  NET_UDP_HDR_CHK_SUM_NEG_ZERO                 0xFFFFu
#define  NET_UDP_HDR_CHK_SUM_NONE                        NET_UDP_HDR_CHK_SUM_POS_ZERO


/*$PAGE*/
/*
*********************************************************************************************************
*                                    UDP DATA/TOTAL LENGTH DEFINES
*
* Note(s) : (1) (a) UDP total length #define's (NET_UDP_TOT_LEN)  relate to the total size of a complete
*                   UDP packet, including the packet's UDP header.  Note that a complete UDP packet MAY
*                   be fragmented in multiple Internet Protocol packets.
*
*               (b) UDP data  length #define's (NET_UDP_DATA_LEN) relate to the data  size of a complete
*                   UDP packet, equal to the total UDP packet length minus its UDP header size.  Note 
*                   that a complete UDP packet MAY be fragmented in multiple Internet Protocol packets.
*********************************************************************************************************
*/

                                                                                /* See Notes #1a & #1b.                 */
#define  NET_UDP_DATA_LEN_MIN                              0

#define  NET_UDP_TOT_LEN_MIN                            (NET_UDP_HDR_SIZE    + NET_UDP_DATA_LEN_MIN)
#define  NET_UDP_TOT_LEN_MAX                            (NET_IP_TOT_LEN_MAX  - NET_IP_HDR_SIZE_MIN )

#define  NET_UDP_DATA_LEN_MAX                           (NET_UDP_TOT_LEN_MAX - NET_UDP_HDR_SIZE    )


/*
*********************************************************************************************************
*                                          UDP FLAG DEFINES
*********************************************************************************************************
*/

                                                                /* ------------------ NET UDP FLAGS ------------------- */
#define  NET_UDP_FLAG_NONE                        DEF_BIT_NONE

                                                                /* ------------------ UDP TX  FLAGS ------------------- */
#define  NET_UDP_FLAG_TX_CHK_SUM_DIS              DEF_BIT_00    /* DISABLE tx        chk sums.                          */
#define  NET_UDP_FLAG_TX_BLOCK                    DEF_BIT_07

                                                                /* ------------------ UDP RX  FLAGS ------------------- */
#define  NET_UDP_FLAG_RX_CHK_SUM_NONE_DISCARD     DEF_BIT_08    /* Discard rx'd NULL chk sum UDP datagrams.             */
#define  NET_UDP_FLAG_RX_DATA_PEEK                DEF_BIT_09
#define  NET_UDP_FLAG_RX_BLOCK                    DEF_BIT_15


/*$PAGE*/
/*
*********************************************************************************************************
*                                             DATA TYPES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                      UDP PORT NUMBER DATA TYPE
*********************************************************************************************************
*/

typedef  NET_PORT_NBR  NET_UDP_PORT_NBR;                        /* Defines UDP port nbr size.                           */


/*$PAGE*/
/*
*********************************************************************************************************
*                                             UDP HEADER
*
* Note(s) : (1) See RFC #768, Section 'Format' for UDP datagram header format.
*********************************************************************************************************
*/

                                                                /* ------------------- NET UDP HDR -------------------- */
typedef  struct  net_udp_hdr {
    NET_UDP_PORT_NBR        PortSrc;                            /* UDP datagram src  port.                              */
    NET_UDP_PORT_NBR        PortDest;                           /* UDP datagram dest port.                              */
    CPU_INT16U              DatagramLen;                        /* UDP datagram msg len.                                */
    NET_CHK_SUM             ChkSum;                             /* UDP datagram chk sum.                                */
} NET_UDP_HDR;


/*
*********************************************************************************************************
*                                          UDP PSEUDO-HEADER
*
* Note(s) : (1) See RFC #768, Section 'Fields : Checksum' for UDP datagram pseudo-header format.
*********************************************************************************************************
*/

                                                                /* ---------------- NET UDP PSEUDO-HDR ---------------- */
typedef  struct  net_udp_pseudo_hdr {
    NET_IP_ADDR             AddrSrc;                            /* UDP datagram src  addr.                              */
    NET_IP_ADDR             AddrDest;                           /* UDP datagram dest addr.                              */
    CPU_INT08U              Zero;                               /* Field MUST be zero'd; i.e. ALL bits clr'd.           */
    CPU_INT08U              Protocol;                           /* UDP datagram protocol.                               */
    CPU_INT16U              DatagramLen;                        /* UDP datagram tot len.                                */
} NET_UDP_PSEUDO_HDR;


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


void        NetUDP_Init            (void);


                                                                /* --------------------- RX FNCTS --------------------- */
void        NetUDP_Rx              (NET_BUF           *pbuf,
                                    NET_ERR           *perr);

CPU_INT16U  NetUDP_RxAppData       (NET_BUF           *pbuf,
                                    void              *pdata_buf,
                                    CPU_INT16U         data_buf_len,
                                    CPU_INT16U         flags,
                                    void              *pip_opts_buf,
                                    CPU_INT08U         ip_opts_buf_len,
                                    CPU_INT08U        *pip_opts_len,
                                    NET_ERR           *perr);


                                                                /* --------------------- TX FNCTS --------------------- */
CPU_INT16U  NetUDP_TxAppData       (void              *p_data,
                                    CPU_INT16U         data_len,
                                    NET_IP_ADDR        src_addr,
                                    NET_UDP_PORT_NBR   src_port,
                                    NET_IP_ADDR        dest_addr,
                                    NET_UDP_PORT_NBR   dest_port,
                                    NET_IP_TOS         TOS,
                                    NET_IP_TTL         TTL,
                                    CPU_INT16U         flags_udp,
                                    CPU_INT16U         flags_ip,
                                    void              *popts_ip,
                                    NET_ERR           *perr);

CPU_INT16U  NetUDP_TxAppDataHandler(void              *p_data,
                                    CPU_INT16U         data_len,
                                    NET_IP_ADDR        src_addr,
                                    NET_UDP_PORT_NBR   src_port,
                                    NET_IP_ADDR        dest_addr,
                                    NET_UDP_PORT_NBR   dest_port,
                                    NET_IP_TOS         TOS,
                                    NET_IP_TTL         TTL,
                                    CPU_INT16U         flags_udp,
                                    CPU_INT16U         flags_ip,
                                    void              *popts_ip,
                                    NET_ERR           *perr);


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*                                   DEFINED IN PRODUCT'S  net_bsp.c
*********************************************************************************************************
*/

#if ((NET_UDP_CFG_APP_API_SEL == NET_UDP_APP_API_SEL_APP     ) || \
     (NET_UDP_CFG_APP_API_SEL == NET_UDP_APP_API_SEL_SOCK_APP))
void        NetUDP_RxAppDataHandler(NET_BUF           *pbuf,
                                    NET_IP_ADDR        src_addr,
                                    NET_UDP_PORT_NBR   src_port,
                                    NET_IP_ADDR        dest_addr,
                                    NET_UDP_PORT_NBR   dest_port,
                                    NET_ERR           *perr);
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                        CONFIGURATION ERRORS
*********************************************************************************************************
*/

#ifndef  NET_UDP_CFG_APP_API_SEL
#error  "NET_UDP_CFG_APP_API_SEL                  not #define'd in 'net_cfg.h'     "
#error  "                                   [MUST be  NET_UDP_APP_API_SEL_SOCK    ]"
#error  "                                   [     ||  NET_UDP_APP_API_SEL_APP     ]"
#error  "                                   [     ||  NET_UDP_APP_API_SEL_SOCK_APP]"

#elif  ((NET_UDP_CFG_APP_API_SEL != NET_UDP_APP_API_SEL_SOCK    ) && \
        (NET_UDP_CFG_APP_API_SEL != NET_UDP_APP_API_SEL_APP     ) && \
        (NET_UDP_CFG_APP_API_SEL != NET_UDP_APP_API_SEL_SOCK_APP))
#error  "NET_UDP_CFG_APP_API_SEL            illegally #define'd in 'net_cfg.h'     "
#error  "                                   [MUST be  NET_UDP_APP_API_SEL_SOCK    ]"
#error  "                                   [     ||  NET_UDP_APP_API_SEL_APP     ]"
#error  "                                   [     ||  NET_UDP_APP_API_SEL_SOCK_APP]"
#endif




#ifndef  NET_UDP_CFG_RX_CHK_SUM_DISCARD_EN
#error  "NET_UDP_CFG_RX_CHK_SUM_DISCARD_EN        not #define'd in 'net_cfg.h'"
#error  "                                   [MUST be  DEF_DISABLED]           "
#error  "                                   [     ||  DEF_ENABLED ]           "

#elif  ((NET_UDP_CFG_RX_CHK_SUM_DISCARD_EN != DEF_DISABLED) && \
        (NET_UDP_CFG_RX_CHK_SUM_DISCARD_EN != DEF_ENABLED ))
#error  "NET_UDP_CFG_RX_CHK_SUM_DISCARD_EN  illegally #define'd in 'net_cfg.h'"
#error  "                                   [MUST be  DEF_DISABLED]           "
#error  "                                   [     ||  DEF_ENABLED ]           "
#endif



#ifndef  NET_UDP_CFG_TX_CHK_SUM_EN
#error  "NET_UDP_CFG_TX_CHK_SUM_EN                not #define'd in 'net_cfg.h'"
#error  "                                   [MUST be  DEF_DISABLED]           "
#error  "                                   [     ||  DEF_ENABLED ]           "

#elif  ((NET_UDP_CFG_TX_CHK_SUM_EN != DEF_DISABLED) && \
        (NET_UDP_CFG_TX_CHK_SUM_EN != DEF_ENABLED ))
#error  "NET_UDP_CFG_TX_CHK_SUM_EN          illegally #define'd in 'net_cfg.h'"
#error  "                                   [MUST be  DEF_DISABLED]           "
#error  "                                   [     ||  DEF_ENABLED ]           "
#endif

