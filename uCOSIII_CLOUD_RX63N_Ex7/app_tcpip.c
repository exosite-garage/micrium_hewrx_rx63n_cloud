/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                          (c) Copyright 2003-2009; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                              uC/TCP-IP
*                                           APPLICATION CODE
*
* Filename      : app_tcpip.c
* Version       : V1.00
* Programmer(s) : FT
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include <app_tcpip.h>
#include <dhcp-c.h>

/*
*********************************************************************************************************
*                                         LOCAL CONFIGURATION
*********************************************************************************************************
*/

#if     (NET_APP_CFG_API_EN == DEF_ENABLED)
#define  APP_DHCPc_EN                                    DEF_ENABLED
#else
#define  APP_DHCPc_EN                                    DEF_DISABLED   /* Do NOT modify.                                    */
#endif

#define  APP_CFG_GATEWAY_EN                              DEF_ENABLED

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

#define  APP_IP_ADDR_STR_NONE                           "0.0.0.0"
#define  APP_IP_ADDR_STR_UNKNOWN                        "xxx.xxx.xxx.xxx"

#define  APP_IP_ADDR_STR_HOST                           "10.10.1.125"
#define  APP_IP_ADDR_STR_NET_MASK                       "255.255.255.0"
#define  APP_IP_ADDR_STR_DFLT_GATEWAY                   "10.10.1.1"

#define  APP_IP_ADDR_STR_DFLT_DNS_SRVR                  "10.10.1.1"


/*$PAGE*/
/*
*********************************************************************************************************
*                                            LOCAL MACRO'S
*********************************************************************************************************
*/

#define  APP_TASK_STOP();                             { while (DEF_ON) { \
                                                            ;            \
                                                        }                \
                                                      }


#define  APP_TEST_ERR(err_var, err_code)              { if ((err_var) != (err_code)) {                                                               \
                                                            APP_TRACE_DBG(("    %s() error #%05d @ line #%05d\n\r", __func__, (err_var), __LINE__)); \
                                                        }                                                                                            \
                                                      }

#define  APP_TEST_FAULT(err_var, err_code)            { APP_TEST_ERR(err_var, err_code); \
                                                        if ((err_var) != (err_code)) {   \
                                                            APP_TASK_STOP();             \
                                                        }                                \
                                                      }



#define  APP_STR_TO_IP(addr, addr_str, err_var)       { (addr) = NetASCII_Str_to_IP((CPU_CHAR *) (addr_str), \
                                                                                    (NET_ERR  *)&(err_var)); \
                                                         APP_TEST_ERR(err_var, NET_ASCII_ERR_NONE);          \
                                                      }

#define  APP_IP_TO_STR(addr, addr_str, err_var)       {  NetASCII_IP_to_Str((NET_IP_ADDR) (addr),     \
                                                                            (CPU_CHAR  *) (addr_str), \
                                                                            (CPU_BOOLEAN)  DEF_NO,    \
                                                                            (NET_ERR   *)&(err_var)); \
                                                         APP_TEST_ERR(err_var, NET_ASCII_ERR_NONE);   \
                                                      }

#define  APP_IP_TO_STR_DBG(addr, addr_str, err_var)   {  NetASCII_IP_to_Str((NET_IP_ADDR) (addr),     \
                                                                            (CPU_CHAR  *) (addr_str), \
                                                                            (CPU_BOOLEAN)  DEF_NO,    \
                                                                            (NET_ERR   *)&(err_var)); \
                                                         APP_TRACE_DBG(("                    "));     \
                                                         APP_TEST_ERR(err_var, NET_ASCII_ERR_NONE);   \
                                                         APP_TRACE_DBG(("\r"));                       \
                                                      }

/*
*********************************************************************************************************
*                                           LOCAL VARIABLES
*********************************************************************************************************
*/

static  NET_IP_ADDR  App_IP_Addrs[NET_IF_CFG_MAX_NBR_IF + 1][NET_IP_CFG_IF_MAX_NBR_ADDR];
static  NET_IP_ADDR  App_IP_DNS_Srvr;


/*
*********************************************************************************************************
*                                          FUNCTION PROTOTYPES
*********************************************************************************************************
*/

#if    (APP_DHCPc_EN  == DEF_ENABLED)
static  void  App_TCPIP_Init_DHCPc(NET_IF_NBR  if_nbr);
#endif


/*
*********************************************************************************************************
*                                    LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                      App_TCPIP_Init()
*
* Description : uC/TCP-IP Application initialization.
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : Application
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_BOOLEAN  App_TCPIP_Init (void)
{
#if (NET_VERSION >= 21002)
    CPU_BOOLEAN        link_state;
    CPU_INT32U         retry_dly_ms;
    CPU_INT16U         retry_sec;
    CPU_INT16U         retry_max;
#else
    INT8U              dly_sec;
#endif

#if (APP_DHCPc_EN != DEF_ENABLED)
    NET_IP_ADDRS_QTY   addr_ix;
    NET_IP_ADDR        addr_ip;
    NET_IP_ADDR        addr_mask;
    NET_IP_ADDR        addr_dflt_gateway;
    CPU_CHAR          *paddr;
    CPU_CHAR          *paddr_mask;
    CPU_CHAR          *paddr_dflt_gateway;
#endif

    NET_IF_NBR         if_nbr;
    NET_IF_QTY         i;
    NET_IP_ADDRS_QTY   j;
    CPU_INT08U         addr_hw_len;
    CPU_INT08U         addr_hw[NET_IF_ETHER_ADDR_SIZE];
    CPU_CHAR           addr_hw_str[NET_IF_ETHER_ADDR_SIZE_STR];
    CPU_CHAR           addr_ip_str[NET_ASCII_LEN_MAX_ADDR_IP];
    NET_ERR            net_err;


                                                                                /* ----------- INIT TCP/IP ------------ */
    

    for (i = 0; i < (NET_IF_CFG_MAX_NBR_IF + 1); i++) {
        for (j = 0; j < (NET_IP_CFG_IF_MAX_NBR_ADDR + 1); j++) {
            App_IP_Addrs[i][j] = NET_IP_ADDR_NONE;
        }
    }

    APP_STR_TO_IP(App_IP_DNS_Srvr, APP_IP_ADDR_STR_DFLT_DNS_SRVR, net_err);

   (void)&App_IP_Addrs;                                                         /* Prevent possible compiler warnings.  */
   (void)&App_IP_DNS_Srvr;


    net_err = Net_Init();
    APP_TEST_FAULT(net_err, NET_ERR_NONE);

   (void)NetARP_CfgCacheTimeout(2 * DEF_TIME_NBR_SEC_PER_MIN);


    if_nbr  = NetIF_Add((void    *)&NetIF_API_Ether,                /* Ethernet interface API.                          */
                        (void    *)&NetDev_API_RX_EtherC,           /* Device API.                                      */
                        (void    *)&NetDev_BSP_YRDK_RX63N,          /* Device BSP.                                      */
                        (void    *)&NetDev_Cfg_RX_Ether_0,          /* Device configuration.                            */
                        (void    *)&NetPhy_API_DP83640,             /* Generic Phy API.                                 */
                        (void    *)&NetPhy_Cfg_Generic_0,           /* PHY configuration.                               */
                        (NET_ERR *) &net_err);
						
    APP_TEST_FAULT(net_err, NET_IF_ERR_NONE);
    APP_TRACE_INFO(("  IF #%2d   added\n\r",   if_nbr));

    NetIF_Start(if_nbr, &net_err);
    APP_TEST_FAULT(net_err, NET_IF_ERR_NONE);
    APP_TRACE_INFO(("  IF #%2d   started\n\r", if_nbr));


#if (NET_VERSION >= 21002)                                                      /* Some PHYs require dly after powerup. */
    retry_dly_ms =  50u;
    retry_sec    =   5u;
    retry_max    = (retry_sec * DEF_TIME_NBR_mS_PER_SEC) / retry_dly_ms;
    link_state   =  NetIF_LinkStateWaitUntilUp(if_nbr, retry_max, retry_dly_ms, &net_err);
    APP_TEST_FAULT(net_err,    NET_IF_ERR_NONE);
    APP_TEST_FAULT(link_state, NET_IF_LINK_UP);

#else
    dly_sec = 2u;
    APP_TRACE_INFO(("  IF #%2d   PHY delay %d seconds\n\r", if_nbr, dly_sec));
    OSTimeDlyHMSM(0, 0, dly_sec, 0);
#endif


    addr_hw_len = sizeof(addr_hw);
    NetIF_AddrHW_Get(if_nbr, &addr_hw[0], &addr_hw_len, &net_err);
    APP_TEST_FAULT(net_err, NET_IF_ERR_NONE);
    NetASCII_MAC_to_Str(&addr_hw[0], &addr_hw_str[0], DEF_NO, DEF_YES, &net_err);
    APP_TEST_FAULT(net_err, NET_ASCII_ERR_NONE);
    APP_TRACE_INFO(("  IF #%2d   HW address = %s\n\r", if_nbr, &addr_hw_str[0]));


/*$PAGE*/
#if (APP_DHCPc_EN == DEF_ENABLED)                                               /* --------- CFG DHCP IP ADDR --------- */
    APP_TRACE_INFO(("\n\r"));
    App_TCPIP_Init_DHCPc(if_nbr);


#else                                                                           /* ---------- ADD IP ADDR(s) ---------- */
    addr_ix = 0;

    paddr      = (CPU_CHAR *)APP_IP_ADDR_STR_HOST;
    paddr_mask = (CPU_CHAR *)APP_IP_ADDR_STR_NET_MASK;

    APP_STR_TO_IP(addr_ip,   paddr,      net_err);
    APP_STR_TO_IP(addr_mask, paddr_mask, net_err);

#if (APP_CFG_GATEWAY_EN == DEF_ENABLED)
    paddr_dflt_gateway = (CPU_CHAR *)APP_IP_ADDR_STR_DFLT_GATEWAY;
    APP_STR_TO_IP(addr_dflt_gateway, paddr_dflt_gateway, net_err);
#else
     addr_dflt_gateway =  NET_IP_ADDR_NONE;
    APP_IP_TO_STR(addr_dflt_gateway, &addr_ip_str[0], net_err);
    paddr_dflt_gateway = &addr_ip_str[0];
#endif

    NetIP_CfgAddrAdd(if_nbr, addr_ip, addr_mask, addr_dflt_gateway, &net_err);

    if (net_err == NET_IP_ERR_NONE) {
        APP_TRACE_INFO(("  IF #%2d   IP address = %s\n\r", if_nbr, paddr             ));
        APP_TRACE_INFO(( "           IP mask    = %s\n\r",         paddr_mask        ));
        APP_TRACE_INFO(( "           IP gateway = %s\n\r",         paddr_dflt_gateway));
        App_IP_Addrs[if_nbr][addr_ix] = addr_ip;
        addr_ix++;

    } else {
        APP_TRACE_INFO(("  IF #%2d   IP address   %s NOT configured\n\r", if_nbr, paddr));
    }
#endif

                                                                                /* ------- DISP DNS SERVER INFO ------- */
    APP_TRACE_INFO(("  IF #%2d   ", if_nbr));
#if (APP_DHCPc_EN == DEF_ENABLED)
    APP_TRACE_INFO(("DNS  server  "));
#else
    APP_TRACE_INFO(("DNS server "));
#endif

    if (App_IP_DNS_Srvr != NET_IP_ADDR_NONE) {
        APP_IP_TO_STR(App_IP_DNS_Srvr, &addr_ip_str[0], net_err);
        APP_TRACE_INFO(("= %s\n\r",    &addr_ip_str[0]));
    } else {
        APP_TRACE_INFO(("unavailable\n\r"));
    }

    APP_TRACE_INFO(("\n\r"));

    return (DEF_OK);
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                       App_TCPIP_Init_DHCPc()
*
* Description : Initialize DHCP client for specified interface.
*
* Argument(s) : if_nbr      Interface number to start DHCP management.
*
* Return(s)   : none.
*
* Caller(s)   : App_TCPIP_Init().
*
* Note(s)     : none.
*********************************************************************************************************
*/

#if (APP_DHCPc_EN == DEF_ENABLED)
static  void  App_TCPIP_Init_DHCPc (NET_IF_NBR  if_nbr)
{
    DHCPc_OPT_CODE    req_param[DHCPc_CFG_PARAM_REQ_TBL_SIZE];
    CPU_INT08U        req_param_qty;
    CPU_BOOLEAN       cfg_done;
    CPU_BOOLEAN       chk_dly;
    DHCPc_STATUS      dhcp_status;
    DHCPc_ERR         dhcp_err;
    CPU_INT08U        opt_buf[5 * sizeof(NET_IP_ADDR)];
    CPU_INT16U        opt_buf_len;
    NET_IP_ADDRS_QTY  addr_ip_tbl_qty;
    NET_IP_ADDR       addr_ip_tbl[NET_IP_CFG_IF_MAX_NBR_ADDR];
    NET_IP_ADDR       addr_ip;
    CPU_CHAR          addr_ip_str[NET_ASCII_LEN_MAX_ADDR_IP];
    NET_ERR           net_err;
    OS_ERR            os_err;


                                                                                /* --------- INIT DHCP CLIENT --------- */
    APP_TRACE_INFO(("Initialize DHCP client ...\n\r"));

    dhcp_err = DHCPc_Init();
    APP_TEST_FAULT(dhcp_err, DHCPc_ERR_NONE);

                                                                                /* ------- START IF's DHCPc CFG ------- */
    req_param[0]  = DHCP_OPT_DOMAIN_NAME_SERVER;                                /* Req'd param(s).                      */
    req_param_qty = 1;

    DHCPc_Start((NET_IF_NBR      ) if_nbr,
                (DHCPc_OPT_CODE *)&req_param[0],
                (CPU_INT08U      ) req_param_qty,
                (DHCPc_ERR      *)&dhcp_err);
    APP_TEST_FAULT(dhcp_err, DHCPc_ERR_NONE);
    APP_TRACE_INFO(("  IF #%2d   DHCP address configuration started\n\r", if_nbr));

                                                                                /* ---- CHK IF's DHCPc CFG STATUS ----- */
    dhcp_status = DHCP_STATUS_NONE;
    cfg_done    = DEF_NO;
    chk_dly     = DEF_NO;

    while (cfg_done != DEF_YES) {
        if (chk_dly == DEF_YES) {
            OSTimeDlyHMSM((CPU_INT16U) 0,
                          (CPU_INT16U) 0,
                          (CPU_INT16U) 0,
                          (CPU_INT32U) 125,
                          (OS_OPT    ) OS_OPT_TIME_HMSM_STRICT,
                          (OS_ERR   *)&os_err);
        }

        dhcp_status = DHCPc_ChkStatus(if_nbr, &dhcp_err);
        switch (dhcp_status) {
            case DHCP_STATUS_CFGD:
                 APP_TRACE_INFO(("  IF #%2d   DHCP address configured\n\r",              if_nbr));
                 cfg_done = DEF_YES;
                 break;


            case DHCP_STATUS_CFGD_NO_TMR:
                 APP_TRACE_INFO(("  IF #%2d   DHCP address configured (no timer)\n\r",   if_nbr));
                 cfg_done = DEF_YES;
                 break;


            case DHCP_STATUS_CFGD_LOCAL_LINK:
                 APP_TRACE_INFO(("  IF #%2d   DHCP address configured (link-local)\n\r", if_nbr));
                 cfg_done = DEF_YES;
                 break;


            case DHCP_STATUS_FAIL:
                 APP_TRACE_INFO(("  IF #%2d   DHCP address configuration failed\n\r",    if_nbr));
                 cfg_done = DEF_YES;
                 break;


            case DHCP_STATUS_CFG_IN_PROGRESS:
            default:
                 chk_dly  = DEF_YES;
                 break;
        }
    }


/*$PAGE*/
    if (dhcp_status != DHCP_STATUS_FAIL) {
                                                                                /* ------- DISP IF's DHCPc ADDR ------- */
        addr_ip_tbl_qty = sizeof(addr_ip_tbl) / sizeof(NET_IP_ADDR);
       (void)NetIP_GetAddrHost((NET_IF_NBR        ) if_nbr,
                               (NET_IP_ADDR      *)&addr_ip_tbl[0],
                               (NET_IP_ADDRS_QTY *)&addr_ip_tbl_qty,
                               (NET_ERR          *)&net_err);
        switch (net_err) {
            case NET_IP_ERR_NONE:
                 addr_ip                 =   addr_ip_tbl[0];
                 App_IP_Addrs[if_nbr][0] =   addr_ip;
                 APP_IP_TO_STR_DBG(addr_ip, &addr_ip_str[0], net_err);
                 break;


            case NET_IF_ERR_INVALID_IF:
            case NET_IP_ERR_NULL_PTR:
            case NET_IP_ERR_ADDR_CFG_IN_PROGRESS:
            case NET_IP_ERR_ADDR_TBL_SIZE:
            case NET_IP_ERR_ADDR_NONE_AVAIL:
            default:
                (void)Str_Copy((CPU_CHAR *)&addr_ip_str[0],
                               (CPU_CHAR *) APP_IP_ADDR_STR_UNKNOWN);
                 break;
        }

        APP_TRACE_INFO(("  IF #%2d   DHCP address = %s\n\r", if_nbr, &addr_ip_str[0]));
		
		lcd_display(LCD_LINE8, (void *)&addr_ip_str[0]);

        printf("  IF #%2d   DHCP address = %s\n\r", if_nbr, &addr_ip_str[0]);

                                                                                /* ---- GET IF's DHCPc OPTs/PARAMs ---- */
        opt_buf_len = sizeof(opt_buf);
        DHCPc_GetOptVal((NET_IF_NBR    ) if_nbr,
                        (DHCPc_OPT_CODE) DHCP_OPT_DOMAIN_NAME_SERVER,           /* Get DNS server.                      */
                        (CPU_INT08U   *)&opt_buf[0],
                        (CPU_INT16U   *)&opt_buf_len,
                        (DHCPc_ERR    *)&dhcp_err);
        if (dhcp_err == DHCPc_ERR_NONE) {
            if (opt_buf_len >= sizeof(addr_ip)) {
                Mem_Copy((void     *)&addr_ip,
                         (void     *)&opt_buf[0],
                         (CPU_SIZE_T) sizeof(addr_ip));
                addr_ip = NET_UTIL_NET_TO_HOST_32(addr_ip);
                if (addr_ip != NET_IP_ADDR_NONE) {
                    App_IP_DNS_Srvr = addr_ip;
                }
            }
        }
    }
}
#endif
