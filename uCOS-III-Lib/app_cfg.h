/*
*********************************************************************************************************
*                                               uC/OS-III
*                                       APPLICATION CONFIGURATION
*
*                             (c) Copyright 2011, Micrium, Inc., Weston, FL
*                                          All Rights Reserved
*
*
* File : APP_CFG.H
* By   : PC
*********************************************************************************************************
*/

#ifndef  __APP_CFG_H__
#define  __APP_CFG_H__

#include "lib_cfg.h"

/*
*********************************************************************************************************
*                                           TASK PRIORITIES
*********************************************************************************************************
*/

#define  APP_TASK_START_PRIO                            1u
#define  BLINKY_TASK_PRIO                               2u

#define  NET_OS_CFG_TMR_TASK_PRIO                       6u
#define  NET_OS_CFG_IF_TX_DEALLOC_TASK_PRIO             7u
#define  NET_OS_CFG_IF_LOOPBACK_TASK_PRIO               8u
#define  NET_OS_CFG_IF_RX_TASK_PRIO                     9u

#define  DHCPc_OS_CFG_TASK_PRIO                         10u
#define  DHCPc_OS_CFG_TMR_TASK_PRIO                     11u
#define  CLOUD_DATA_TASK_PRIO                           12u

/*
*********************************************************************************************************
*                                          TASK STACK SIZES
*********************************************************************************************************
*/

#define  APP_TASK_START_STK_SIZE                     1024u
#define  BLINKY_TASK_STK_SIZE                         512u
#define  CLOUD_DATA_TASK_STK_SIZE                     512u

#define  NET_OS_CFG_TMR_TASK_STK_SIZE                 768u
#define  NET_OS_CFG_IF_TX_DEALLOC_TASK_STK_SIZE       512u
#define  NET_OS_CFG_IF_LOOPBACK_TASK_STK_SIZE         512u
#define  NET_OS_CFG_IF_RX_TASK_STK_SIZE              1280u

#define  DHCPc_OS_CFG_TASK_STK_SIZE                     1024u
#define  DHCPc_OS_CFG_TMR_TASK_STK_SIZE                 1024u

/*
*********************************************************************************************************
*                                            uC/TCP-IP v2.0
*********************************************************************************************************
*/

#define  NET_OS_CFG_IF_LOOPBACK_Q_SIZE                  5u
#define  NET_OS_CFG_IF_RX_Q_SIZE                       10u
#define  NET_OS_CFG_IF_TX_DEALLOC_Q_SIZE               10u
#define  APP_CFG_TCPIP_MODULE_EN                        1u

#endif

/*$PAGE*/
/*
*********************************************************************************************************
*                                                 DHCPc
*
* Note(s) : (1) Default port for DHCP server is 67, and default port for DHCP client is 68.
*
*           (2) Configure DHCPc_CFG_BROADCAST_BIT_EN to DEF_ENABLED to instruct the contacted DHCP server
*               to use broadcast packets instead of unicast ones.  Used for TCP/IP stacks that cannot
*               receive unicast packets when not fully configured.  This is the case of the uC/TCPIP
*               stack, so this define MUST be set to DEF_ENABLED when this DHCP client is used with the
*               Micrium's uC/TCP-IP stack.
*
*           (3) Configure DHCPc_CFG_MAX_NBR_IF to the maximum number of interface this DHCP client will
*               be able to manage at a given time.
*
*           (4) Once the DHCP server has assigned the client an address, the later may perform a final
*               check prior to use this address in order to make sure it is not being used by another
*               host on the network.
*********************************************************************************************************
*/

#define  DHCPc_CFG_IP_PORT_SERVER                         67    /* Configure DHCP server port            (see Note #1). */
#define  DHCPc_CFG_IP_PORT_CLIENT                         68    /* Configure DHCP client port            (see Note #1). */

#define  DHCPc_CFG_MAX_RX_TIMEOUT_MS                    5000    /* Maximum inactivity time (ms) on receive.             */

#define  DHCPc_CFG_BROADCAST_BIT_EN              DEF_ENABLED    /* Configure broadcast bit               (see Note #2) :*/
                                                                /*   DEF_DISABLED  Broadcast bit NOT set                */
                                                                /*   DEF_ENABLED   Broadcast bit     set                */

#define  DHCPc_CFG_PARAM_REQ_TBL_SIZE                      5    /* Configure requested parameter table size.            */

#define  DHCPc_CFG_MAX_NBR_IF                              1    /* Configure maximum number of interface (see Note #3). */

#define  DHCPc_CFG_ADDR_VALIDATE_EN              DEF_ENABLED    /* Configure final check on assigned address ...        */
                                                                /* ... (see Note #4) :                                  */
                                                                /*   DEF_DISABLED  Validation NOT performed             */
                                                                /*   DEF_ENABLED   Validation     performed             */

#define  DHCPc_CFG_DYN_LOCAL_LINK_ADDR_EN        DEF_ENABLED    /* Configure dynamic link-local address configuration : */
                                                                /*   DEF_DISABLED  local-link configuration DISABLED    */
                                                                /*   DEF_ENABLED   local-link configuration ENABLED     */

#define  DHCPc_CFG_LOCAL_LINK_MAX_RETRY                    3    /* Configure maximum number of retry to get a           */
                                                                /* link-local address.                                  */


/*
*********************************************************************************************************
*                                 DHCPc ARGUMENT CHECK CONFIGURATION
*
* Note(s) : (1) Configure DHCPc_CFG_ARG_CHK_EXT_EN to enable/disable the DHCP client external argument
*               check feature :
*
*               (a) When ENABLED,  ALL arguments received from any port interface provided by the developer
*                   or application are checked/validated.
*
*               (b) When DISABLED, NO  arguments received from any port interface provided by the developer
*                   or application are checked/validated.
*
*           (2) Configure DHCPc_CFG_ARG_CHK_DBG_EN to enable/disable the DHCP client internal debug
*               argument check feature :
*
*               (a) When ENABLED,     internal arguments are checked/validated to debug the DHCP client.
*
*               (b) When DISABLED, NO internal arguments are checked/validated to debug the DHCP client.
*
*           (3) Configure DHCPc_DBG_CFG_MEM_CLR_EN to enable/disable the DHCP client from clearing
*               internal data structure memory buffers; a convenient feature while debugging.
*********************************************************************************************************
*/
                                                                /* Configure external argument check feature ...        */
                                                                /* ... (see Note #1) :                                  */
#define  DHCPc_CFG_ARG_CHK_EXT_EN                DEF_ENABLED
                                                                /*   DEF_DISABLED     Argument check DISABLED           */
                                                                /*   DEF_ENABLED      Argument check ENABLED            */

                                                                /* Configure internal argument check feature ...        */
                                                                /* ... (see Note #2) :                                  */
#define  DHCPc_CFG_ARG_CHK_DBG_EN                DEF_DISABLED
                                                                /*   DEF_DISABLED     Argument check DISABLED           */
                                                                /*   DEF_ENABLED      Argument check ENABLED            */

                                                                /* Configure memory clear feature  (see Note #3) :      */
#define  DHCPc_DBG_CFG_MEM_CLR_EN                DEF_ENABLED
                                                                /*   DEF_DISABLED     Data structure clears DISABLED    */
                                                                /*   DEF_ENABLED      Data structure clears ENABLED     */
																



/*
*********************************************************************************************************
*                                     TRACE / DEBUG CONFIGURATION
*********************************************************************************************************
*/

#define  TRACE_LEVEL_OFF                                   0u

#define  APP_TRACE_LEVEL                    TRACE_LEVEL_OFF
#define  APP_TRACE                          TRACE_LEVEL_OFF
#define  APP_CFG_TRACE                      



#define  APP_CFG_TRACE_LEVEL                    TRACE_LEVEL_OFF


#define  APP_TRACE_INFO(x)                     TRACE_LEVEL_OFF
#define  APP_TRACE_DBG(x)                      TRACE_LEVEL_OFF


