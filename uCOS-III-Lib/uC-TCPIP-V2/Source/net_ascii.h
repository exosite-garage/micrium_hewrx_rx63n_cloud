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
*                                         NETWORK ASCII LIBRARY
*
* Filename      : net_ascii.h
* Version       : V2.11.02
* Programmer(s) : ITJ
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/

#if ((defined(NET_ASCII_MODULE)) && \
     (defined(NET_GLOBALS_EXT)))
#define  NET_ASCII_EXT
#else
#define  NET_ASCII_EXT  extern
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/

#define  NET_ASCII_CHAR_LEN_DOT                            1u
#define  NET_ASCII_CHAR_LEN_HYPHEN                         1u
#define  NET_ASCII_CHAR_LEN_COLON                          1u
#define  NET_ASCII_CHAR_LEN_NUL                            1u


#define  NET_ASCII_CHAR_MIN_OCTET                          1u

#define  NET_ASCII_CHAR_MAX_OCTET_08                     DEF_INT_08U_NBR_DIG_MAX
#define  NET_ASCII_CHAR_MAX_OCTET_16                     DEF_INT_16U_NBR_DIG_MAX
#define  NET_ASCII_CHAR_MAX_OCTET_32                     DEF_INT_32U_NBR_DIG_MAX


/*
*********************************************************************************************************
*                                    NETWORK ASCII ADDRESS DEFINES
*
* Note(s) : (1) #### ONLY supports 48-bit Ethernet MAC addresses.
*********************************************************************************************************
*/

#define  NET_ASCII_NBR_OCTET_ADDR_MAC                      6u   /* See Note #1.                                         */
#define  NET_ASCII_CHAR_MAX_OCTET_ADDR_MAC                 2u

#define  NET_ASCII_LEN_MAX_ADDR_MAC                    ((NET_ASCII_NBR_OCTET_ADDR_MAC       * NET_ASCII_CHAR_MAX_OCTET_ADDR_MAC) + \
                                                       ((NET_ASCII_NBR_OCTET_ADDR_MAC - 1u) * NET_ASCII_CHAR_LEN_HYPHEN        ) + \
                                                         NET_ASCII_CHAR_LEN_NUL                                                )


#define  NET_ASCII_CHAR_MAX_OCTET_ADDR_IP                  3u
#define  NET_ASCII_VAL_MAX_OCTET_ADDR_IP                 255u

#define  NET_ASCII_NBR_OCTET_ADDR_IP             (sizeof(NET_IP_ADDR))


#define  NET_ASCII_LEN_MAX_ADDR_IP                     ((NET_ASCII_NBR_OCTET_ADDR_IP        * NET_ASCII_CHAR_MAX_OCTET_ADDR_IP)  + \
                                                       ((NET_ASCII_NBR_OCTET_ADDR_IP  - 1u) * NET_ASCII_CHAR_LEN_DOT          )  + \
                                                         NET_ASCII_CHAR_LEN_NUL                                               )


/*$PAGE*/
/*
*********************************************************************************************************
*                                             DATA TYPES
*********************************************************************************************************
*/


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

void         NetASCII_Str_to_MAC(CPU_CHAR     *paddr_mac_ascii,
                                 CPU_INT08U   *paddr_mac,
                                 NET_ERR      *perr);

void         NetASCII_MAC_to_Str(CPU_INT08U   *paddr_mac,
                                 CPU_CHAR     *paddr_mac_ascii,
                                 CPU_BOOLEAN   hex_lower_case,
                                 CPU_BOOLEAN   hex_colon_sep,
                                 NET_ERR      *perr);


NET_IP_ADDR  NetASCII_Str_to_IP (CPU_CHAR     *paddr_ip_ascii,
                                 NET_ERR      *perr);

void         NetASCII_IP_to_Str (NET_IP_ADDR   addr_ip,
                                 CPU_CHAR     *paddr_ip_ascii,
                                 CPU_BOOLEAN   lead_zeros,
                                 NET_ERR      *perr);


/*$PAGE*/
/*
*********************************************************************************************************
*                                        CONFIGURATION ERRORS
*********************************************************************************************************
*/

