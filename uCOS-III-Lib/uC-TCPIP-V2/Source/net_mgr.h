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
*                                      NETWORK LAYER MANAGEMENT
*
* Filename      : net_mgr.h
* Version       : V2.11.02
* Programmer(s) : SR
*********************************************************************************************************
* Note(s)       : (1) #### Network layer manager MAY eventually maintain each interface's network address(s)
*                     & address configuration.
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/

#if ((defined(NET_MGR_MODULE)) && \
     (defined(NET_GLOBALS_EXT)))
#define  NET_MGR_EXT
#else
#define  NET_MGR_EXT  extern
#endif


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
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/


/*$PAGE*/
/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void         NetMgr_Init                     (NET_ERR            *perr);


                                                                                    /* ------ NET MGR ADDR FNCTS ------ */
void         NetMgr_GetHostAddrProtocol      (NET_PROTOCOL_TYPE   protocol_type,
                                              NET_IF_NBR          if_nbr,
                                              CPU_INT08U         *paddr_protocol_tbl,
                                              CPU_INT08U         *paddr_protocol_tbl_qty,
                                              CPU_INT08U         *paddr_protocol_len,
                                              NET_ERR            *perr);

NET_IF_NBR   NetMgr_GetHostAddrProtocolIF_Nbr(NET_PROTOCOL_TYPE   protocol_type,
                                              CPU_INT08U         *paddr_protocol,
                                              CPU_INT08U          addr_protocol_len,
                                              NET_ERR            *perr);


CPU_BOOLEAN  NetMgr_IsValidAddrProtocol      (NET_PROTOCOL_TYPE   protocol_type,
                                              CPU_INT08U         *paddr_protocol,
                                              CPU_INT08U          addr_protocol_len);

CPU_BOOLEAN  NetMgr_IsAddrsCfgdOnIF          (NET_IF_NBR          if_nbr,
                                              NET_ERR            *perr);

CPU_BOOLEAN  NetMgr_IsAddrProtocolInit       (NET_PROTOCOL_TYPE   protocol_type,
                                              CPU_INT08U         *paddr_protocol,
                                              CPU_INT08U          addr_protocol_len);

#ifdef  NET_MULTICAST_PRESENT
CPU_BOOLEAN  NetMgr_IsAddrProtocolMulticast  (NET_PROTOCOL_TYPE   protocol_type,
                                              CPU_INT08U         *paddr_protocol,
                                              CPU_INT08U          addr_protocol_len);
#endif


CPU_BOOLEAN  NetMgr_IsAddrProtocolConflict   (NET_IF_NBR          if_nbr);

void         NetMgr_ChkAddrProtocolConflict  (NET_PROTOCOL_TYPE   protocol_type,
                                              NET_IF_NBR          if_nbr,
                                              CPU_INT08U         *paddr_protocol,
                                              CPU_INT08U          addr_protocol_len,
                                              NET_ERR            *perr);


/*
*********************************************************************************************************
*                                        CONFIGURATION ERRORS
*********************************************************************************************************
*/

