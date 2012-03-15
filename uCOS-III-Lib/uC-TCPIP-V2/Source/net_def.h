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
*                                           NETWORK DEFINES
*
* Filename      : net_def.h
* Version       : V2.11.02
* Programmer(s) : ITJ
*                 SR
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                           NETWORK DEFINES
*********************************************************************************************************
*/

#define  NET_TRANSACTION_NONE                              0u
#define  NET_TRANSACTION_RX                              100u
#define  NET_TRANSACTION_TX                              200u

#define  NET_FLAG_NONE                                   DEF_BIT_NONE

#define  NET_TS_NONE                                       0u


/*
*********************************************************************************************************
*                                    NETWORK PROTOCOL TYPE DEFINES
*
* Note(s) : (1) See 'net.h  Note #2'.
*********************************************************************************************************
*/

                                                                /* ---------------- NET PROTOCOL TYPES ---------------- */
#define  NET_PROTOCOL_TYPE_NONE                            0u
#define  NET_PROTOCOL_TYPE_ALL                             1u

                                                                /* --------------- LINK LAYER PROTOCOLS --------------- */
#define  NET_PROTOCOL_TYPE_LINK                           10u

                                                                /* -------------- NET IF LAYER PROTOCOLS -------------- */
#define  NET_PROTOCOL_TYPE_IF                             20u
#define  NET_PROTOCOL_TYPE_IF_FRAME                       21u

#define  NET_PROTOCOL_TYPE_IF_ETHER                       25u
#define  NET_PROTOCOL_TYPE_IF_IEEE_802                    26u

#define  NET_PROTOCOL_TYPE_ARP                            30u

                                                                /* ---------------- NET LAYER PROTOCOLS --------------- */
#define  NET_PROTOCOL_TYPE_IP_V4                          40u
#define  NET_PROTOCOL_TYPE_IP_V4_OPT                      41u
#define  NET_PROTOCOL_TYPE_ICMP                           42u
#define  NET_PROTOCOL_TYPE_IGMP                           43u

                                                                /* ------------- TRANSPORT LAYER PROTOCOLS ------------ */
#define  NET_PROTOCOL_TYPE_UDP                            50u
#define  NET_PROTOCOL_TYPE_TCP                            51u

                                                                /* ---------------- APP LAYER PROTOCOLS --------------- */
#define  NET_PROTOCOL_TYPE_APP                            60u
#define  NET_PROTOCOL_TYPE_SOCK                           61u


/*$PAGE*/
/*
*********************************************************************************************************
*                               PARAMETER CONFIGURATION INITIALIZATION
*
* Note(s) : (1) (a) Configure NET_CFG_INIT_CFG_VALS in 'net_cfg.h' with the desired configuration for the
*                   initialization of network protocol suite configurable parameters  :
*
*                       NET_INIT_CFG_VALS_DFLT          Configure network parameters with default values
*                       NET_INIT_CFG_VALS_APP_INIT      Configure network parameters with application-
*                                                           initialized values (recalled from non-volatile
*                                                           memory &/or hard-coded in product's application)
*
*               (b) (1) When NET_CFG_INIT_CFG_VALS is configured as NET_INIT_CFG_VALS_DFLT, the network
*                       protocol suite's configurable parameters are configured with default values.
*
*                       The application need only call Net_Init() to initialize both the network protocol
*                       suite & its configurable parameters.
*
*                   (2) When NET_CFG_INIT_CFG_VALS is configured as NET_INIT_CFG_VALS_APP_INIT, the
*                       application MUST ...
*
*                       (A) Initialize ALL network protocol suite configurable parameters from values
*                           recalled from non-volatile memory &/or hard-coded application values :
*
*                           (1) Call each of the configuration functions in Net_InitDflt() passing the
*                               application-recalled &/or hard-coded values
*                                 OR
*                           (2) Call Net_InitDflt() to initialize ALL network protocol suite configurable
*                               parameters to their default values & then call any of the configuration
*                               functions in Net_InitDflt() passing the recalled &/or hard-coded values
*
*                       (B) Call Net_Init()
*
*               See also 'net.c  Net_InitDflt()  Notes #1 & #2'
*                      & 'net_cfg.h  NETWORK CONFIGURATION  Note #1'.
*********************************************************************************************************
*/

#define  NET_INIT_CFG_VALS_NONE                            0u
#define  NET_INIT_CFG_VALS_DFLT                            1u
#define  NET_INIT_CFG_VALS_APP_INIT                        2u


/*
*********************************************************************************************************
*                                     OPTIMIZATION CONFIGURATION
*
* Note(s) : (1) Configure NET_CFG_OPTIMIZE in 'net_cfg.h' with the desired network performance optimization :
*
*                   NET_OPTIMIZE_SPD            Optimizes network protocol suite for speed performance
*                   NET_OPTIMIZE_SIZE           Optimizes network protocol suite for binary image size
*********************************************************************************************************
*/

#define  NET_OPTIMIZE_NONE                                 0u
#define  NET_OPTIMIZE_SPD                                  1u
#define  NET_OPTIMIZE_SIZE                                 2u


/*$PAGE*/
/*
*********************************************************************************************************
*********************************************************************************************************
*                                NETWORK MODULE & LAYER GLOBAL DEFINES
*********************************************************************************************************
*********************************************************************************************************
*
* Note(s) : (1) These module & layer global #define's are required PRIOR to network configuration.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                   NETWORK INTERFACE LAYER DEFINES
*
* Note(s) : (1) See specific 'net_if_&&&.h  NETWORK INTERFACE HEADER DEFINES'.
*
*          !!!! Redesign for dynamically-configured network interface types?
*********************************************************************************************************
*/
                                                                /* See Note #1.                                         */
#define  NET_IF_HDR_SIZE_LOOPBACK                          0
#define  NET_IF_HDR_SIZE_ETHER                            14


/*
*********************************************************************************************************
*                                          ARP LAYER DEFINES
*
* Note(s) : (1) See 'net_arp.h  ARP HARDWARE & PROTOCOL DEFINES  Note #1'.
*********************************************************************************************************
*/
                                                                /* ------------------- ARP HW TYPES ------------------- */
#define  NET_ARP_HW_TYPE_NONE                         0x0000u

#define  NET_ARP_HW_TYPE_ETHER                        0x0001u
#define  NET_ARP_HW_ADDR_LEN_ETHER                         6

                                                                /* ---------------- ARP PROTOCOL TYPES ---------------- */
#define  NET_ARP_PROTOCOL_TYPE_NONE                   0x0000u

#define  NET_ARP_PROTOCOL_TYPE_IP_V4                  0x0800u
#define  NET_ARP_PROTOCOL_ADDR_LEN_IP_V4                   4


/*
*********************************************************************************************************
*                                          IP LAYER DEFINES
*
* Note(s) : (1) See 'net_ip.h  IP MULTICAST SELECT DEFINES  Note #1'.
*********************************************************************************************************
*/

#define  NET_IP_HDR_SIZE_MIN                              20    /* See 'net_ip.h  IP HEADER DEFINES  Note #1a'.         */
#define  NET_IP_HDR_SIZE_MAX                              60    /* See 'net_ip.h  IP HEADER DEFINES  Note #1b'.         */

                                                                /* ----------------- IP MULTICAST SEL ----------------- */
                                                                /* See Note #1.                                         */
#define  NET_IP_MULTICAST_SEL_NONE                         0u
#define  NET_IP_MULTICAST_SEL_TX                           1u
#define  NET_IP_MULTICAST_SEL_TX_RX                        2u


/*$PAGE*/
/*
*********************************************************************************************************
*                                       TRANSPORT LAYER DEFINES
*
* Note(s) : (1) The following transport layer values are pre-#define'd in 'net_type.h' (see 'net_type.h
*               NETWORK TRANSPORT LAYER PORT NUMBER DATA TYPE  Note #1') :
*
*               (a) NET_PORT_NBR_MAX                     DEF_INT_16U_MAX_VAL
*********************************************************************************************************
*/

                                                                /* ------------- NET TRANSPORT LAYER SEL -------------- */
#define  NET_TRANSPORT_LAYER_SEL_NONE                      0u
#define  NET_TRANSPORT_LAYER_SEL_UDP                       1u
#define  NET_TRANSPORT_LAYER_SEL_UDP_TCP                   2u


                                                                /* ------------------ NET PORT NBRS ------------------- */
#define  NET_PORT_NBR_RESERVED                             0u
#define  NET_PORT_NBR_NONE                               NET_PORT_NBR_RESERVED

#define  NET_PORT_NBR_MIN                                  1u
#if 0                                                           /* See Note #1a.                                        */
#define  NET_PORT_NBR_MAX                                DEF_INT_16U_MAX_VAL
#endif


/*
*********************************************************************************************************
*                                          UDP LAYER DEFINES
*
* Note(s) : (1) See 'net_udp.h  UDP APPLICATION-PROTOCOL-INTERFACE SELECT DEFINES  Note #1'.
*********************************************************************************************************
*/

#define  NET_UDP_HDR_SIZE_MIN                              8    /* See 'net_udp.h  UDP HEADER DEFINES  Note #1a'.       */
#define  NET_UDP_HDR_SIZE_MAX                              8    /* See 'net_udp.h  UDP HEADER DEFINES  Note #1b'.       */


                                                                /* ----------------- UDP/APP API SEL ------------------ */
                                                                /* See Note #1.                                         */
#define  NET_UDP_APP_API_SEL_NONE                          0u
#define  NET_UDP_APP_API_SEL_SOCK                          1u
#define  NET_UDP_APP_API_SEL_APP                           2u
#define  NET_UDP_APP_API_SEL_SOCK_APP                      3u


/*
*********************************************************************************************************
*                                          TCP LAYER DEFINES
*********************************************************************************************************
*/

#define  NET_TCP_HDR_SIZE_MAX                             60    /* See 'net_tcp.h  TCP HEADER DEFINES  Note #1'.        */


/*$PAGE*/
/*
*********************************************************************************************************
*                                BSD 4.x & NETWORK SOCKET LAYER DEFINES
*
* Note(s) : (1) (a) See 'net_sock.h  NETWORK SOCKET FAMILY & PROTOCOL DEFINES  Note #1' &
*                       'net_sock.h  NETWORK SOCKET ADDRESS DEFINES'.
*
*               (b) See 'net_sock.h  NETWORK SOCKET BLOCKING MODE SELECT DEFINES  Note #1'.
*
*           (2) Ideally, AF_&&& constants SHOULD be defined as unsigned constants since AF_&&& constants 
*               are used with the unsigned socket address family data type (see 'net_bsd.h  BSD 4.x SOCKET 
*               DATA TYPES  Note #2a1A').  However, since PF_&&& constants are typically defined to their 
*               equivalent AF_&&& constants BUT PF_&&& constants are used with the signed socket protocol 
*               family data types; AF_&&& constants are defined as signed constants.
*
*           (3) 'NET_SOCK_PROTOCOL_MAX' abbreviated to 'NET_SOCK_PROTO_MAX' to enforce ANSI-compliance of 
*                31-character symbol length uniqueness.
*********************************************************************************************************
*/

                                                                /* ------------ SOCK FAMILY/PROTOCOL TYPES ------------ */
                                                                /* See Note #1a.                                        */
#define  NET_SOCK_FAMILY_NONE                              0 
#define  NET_SOCK_PROTOCOL_FAMILY_NONE                   NET_SOCK_FAMILY_NONE
#define  NET_SOCK_ADDR_FAMILY_NONE                       NET_SOCK_FAMILY_NONE

                                                                /* ------------------- TCP/IP SOCKS ------------------- */
                                                                /* See Note #2.                                         */
#ifdef   AF_INET
#undef   AF_INET
#endif
#define  AF_INET                                           2

#ifdef   PF_INET
#undef   PF_INET
#endif
#define  PF_INET                                     AF_INET


#define  NET_SOCK_PROTOCOL_FAMILY_IP_V4              PF_INET    /* TCP/IP sock protocol family type.                    */
#define  NET_SOCK_ADDR_FAMILY_IP_V4                  AF_INET    /* TCP/IP sock addr     family type.                    */
#define  NET_SOCK_FAMILY_IP_V4                           NET_SOCK_PROTOCOL_FAMILY_IP_V4

#define  NET_SOCK_ADDR_LEN_IP_V4                           6    /* TCP/IP sock addr len =                               */
                                                                /*             2-octet TCP/UDP port val                 */
                                                                /*             4-octet IP      addr val                 */

                                                                /* See Note #3.                                         */
#define  NET_SOCK_PROTO_MAX_MIN                            1

#define  NET_SOCK_PROTO_MAX_IP_V4_UDP                      1
#define  NET_SOCK_PROTO_MAX_IP_V4_UDP_TCP                  2
#define  NET_SOCK_PROTO_MAX_IP_V4                        NET_SOCK_PROTO_MAX_IP_V4_UDP_TCP



                                                                /* ------------------ SOCK BLOCK SEL ------------------ */
#define  NET_SOCK_BLOCK_SEL_NONE                           0u
#define  NET_SOCK_BLOCK_SEL_DFLT                           1u   /* Sock ops block by dflt (see Note #1b).               */
#define  NET_SOCK_BLOCK_SEL_BLOCK                          2u
#define  NET_SOCK_BLOCK_SEL_NO_BLOCK                       3u


/*$PAGE*/
/*
*********************************************************************************************************
*                                  NETWORK SECURITY MANAGER DEFINES
*
* Note(s) : (1) See 'net_secure_mgr.h  NETWORK SECURITY MANAGER PROTOCOL VERSION DEFINES  Note #1'.
*********************************************************************************************************
*/

                                                                /* ------------- NET SECURE PROTOCOL VER -------------- */
                                                                /* See Note #1.                                         */
#define  NET_SECURE_NONE                                   0u
#define  NET_SECURE_SSL_V2_0                              10u
#define  NET_SECURE_SSL_V3_0                              11u
#define  NET_SECURE_TLS_V1_0                              20u
#define  NET_SECURE_TLS_V1_1                              21u
#define  NET_SECURE_TLS_V1_2                              22u


/*
*********************************************************************************************************
*                                NETWORK CONNECTION MANAGEMENT DEFINES
*********************************************************************************************************
*/

                                                                /* ---------------- CONN FAMILY TYPES ----------------- */
#define  NET_CONN_FAMILY_NONE                              0
                                                                /* Net sock cfg :                                       */
#define  NET_CONN_FAMILY_IP_V4_SOCK                      NET_SOCK_FAMILY_IP_V4
#define  NET_CONN_ADDR_LEN_IP_V4_SOCK                    NET_SOCK_ADDR_LEN_IP_V4
#define  NET_CONN_PROTOCOL_MAX_IP_V4_SOCK                NET_SOCK_PROTO_MAX_IP_V4

