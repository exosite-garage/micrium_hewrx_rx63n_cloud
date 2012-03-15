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
*                                    NETWORK ERROR CODE MANAGEMENT
*
* Filename      : net_err.h
* Version       : V2.11.02
* Programmer(s) : ITJ
*                 SR
*                 SL
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/


#if ((defined(NET_ERR_MODULE)) && \
     (defined(NET_GLOBALS_EXT)))
#define  NET_ERR_EXT
#else
#define  NET_ERR_EXT  extern
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                         NETWORK ERROR CODES
*
* Note(s) : (1) All generic network error codes are #define'd in 'net_err.h';
*               Any port-specific   error codes are #define'd in port-specific header files.
*
*           (2) Network error codes are grouped in series of 1000 per module/layer.
*********************************************************************************************************
*/

#define  NET_ERR_NONE                                      0u

#define  NET_ERR_INIT_INCOMPLETE                          10u   /* Net init NOT completed.                              */
#define  NET_ERR_INVALID_PROTOCOL                         20u   /* Invalid/unknown/unsupported net protocol.            */
#define  NET_ERR_INVALID_TRANSACTION                      30u   /* Invalid transaction type.                            */

#define  NET_ERR_RX                                      400u   /* Rx err.                                              */
#define  NET_ERR_RX_DEST                                 450u   /* Invalid rx dest.                                     */

#define  NET_ERR_TX                                      500u   /* Tx err.                                              */


/*$PAGE*/
/*
*********************************************************************************************************
*                                    NETWORK-OS LAYER ERROR CODES
*
* Note(s) : (1) The following error codes abbreviated to enforce ANSI-compliance of 31-character symbol
*               length uniqueness :
*
*               (a) 'NET_OS_ERR_INIT_IF_TX_DEALLOC'        abbreviated to 'NET_OS_ERR_INIT_IF_DEALLC'
*
*               (b) (1) 'NET_OS_ERR_INIT_SOCK_CONN_REQ'    abbreviated to 'NET_OS_ERR_INIT_SOCK_CONN'
*                   (2) 'NET_OS_ERR_INIT_SOCK_CONN_ACCEPT' abbreviated to 'NET_OS_ERR_INIT_SOCK_ACCEPT'
*                   (3) 'NET_OS_ERR_INIT_SOCK_CONN_CLOSE'  abbreviated to 'NET_OS_ERR_INIT_SOCK_CLOSE'
*********************************************************************************************************
*/

#define  NET_OS_ERR_NONE                                1000u

#define  NET_OS_ERR_LOCK                                1010u
#define  NET_OS_ERR_TASK                                1020u

#define  NET_OS_ERR_INVALID_TIME                        1050u   /* Invalid time/tick val.                               */

#define  NET_OS_ERR_TIME_DLY_FAULT                      1060u   /* Time dly fault.                                      */
#define  NET_OS_ERR_TIME_DLY_MAX                        1061u   /* Time dly max'd.                                      */



#define  NET_OS_ERR_INVALID_CFG_NBR_SIGNALS             1100u   /* Invalid nbr cfg'd OS signals.                        */
#define  NET_OS_ERR_INVALID_CFG_NBR_EVENTS              1101u   /* Invalid nbr cfg'd OS events.                         */
#define  NET_OS_ERR_INVALID_CFG_NBR_MSGS                1102u   /* Invalid nbr cfg'd OS msgs.                           */

#define  NET_OS_ERR_INVALID_CFG_SEM                     1110u   /* Invalid OS sem cfg.                                  */
#define  NET_OS_ERR_INVALID_CFG_Q                       1111u   /* Invalid OS q   cfg.                                  */
#define  NET_OS_ERR_INVALID_CFG_ABORT                   1112u   /* Invalid OS abort      feature cfg.                   */
#define  NET_OS_ERR_INVALID_CFG_MULTI_PEND              1113u   /* Invalid OS multi-pend feature cfg.                   */

#define  NET_OS_ERR_INVALID_CFG_TICK_FREQ               1120u   /* Invalid OS tick freq cfg'd.                          */
#define  NET_OS_ERR_INVALID_CFG_TIME_DLY                1121u   /* Invalid OS time dly   feature cfg.                   */

#define  NET_OS_ERR_INVALID_CFG_TASK                    1130u   /* Invalid OS task          cfg.                        */
#define  NET_OS_ERR_INVALID_CFG_TASK_PRIO               1131u   /* Invalid OS task prio     cfg.                        */
#define  NET_OS_ERR_INVALID_CFG_TASK_STK_SIZE           1132u   /* Invalid OS task stk size cfg.                        */


/*$PAGE*/
#define  NET_OS_ERR_INIT                                1200u   /* Net init    signal          NOT rx'd by net task(s). */

#define  NET_OS_ERR_INIT_SIGNAL                         1210u   /* Net init    signal          NOT successfully init'd. */
#define  NET_OS_ERR_INIT_SIGNAL_NAME                    1211u   /* Net init    signal  name    NOT successfully cfg'd.  */
#define  NET_OS_ERR_INIT_SIGNALD                        1212u   /* Net init                    NOT successfully signl'd.*/
#define  NET_OS_ERR_INIT_LOCK                           1220u   /* Net lock    signal          NOT successfully init'd. */
#define  NET_OS_ERR_INIT_LOCK_NAME                      1221u   /* Net lock    signal  name    NOT successfully cfg'd.  */


#define  NET_OS_ERR_INIT_TMR_TASK                       1300u   /* Net tmr     task            NOT successfully init'd. */
#define  NET_OS_ERR_INIT_TMR_TASK_NAME                  1301u   /* Net tmr     task    name    NOT successfully cfg'd.  */


#define  NET_OS_ERR_INIT_DEV_TX_RDY                     1400u   /* Dev tx rdy  signal          NOT successfully init'd. */
#define  NET_OS_ERR_INIT_DEV_TX_RDY_NAME                1401u   /* Dev tx rdy  signal  name    NOT successfully cfg'd.  */
#define  NET_OS_ERR_INIT_DEV_TX_RDY_VAL                 1402u   /* Dev tx rdy  signal  cnt     NOT successfully cfg'd.  */


#define  NET_OS_ERR_INIT_IF_RX_Q                        1450u   /* IF rx Q     signal          NOT successfully init'd. */
#define  NET_OS_ERR_INIT_IF_RX_Q_NAME                   1451u   /* IF rx Q     signal  name    NOT successfully cfg'd.  */
#define  NET_OS_ERR_INIT_IF_RX_TASK                     1452u   /* IF rx       task            NOT successfully init'd. */
#define  NET_OS_ERR_INIT_IF_RX_TASK_NAME                1453u   /* IF rx       task    name    NOT successfully cfg'd.  */
                                                                /* IF tx dealloc errs (see Note #1a) :                  */
#define  NET_OS_ERR_INIT_IF_DEALLC_Q                    1460u   /* IF tx deallc signal         NOT successfully init'd. */
#define  NET_OS_ERR_INIT_IF_DEALLC_Q_NAME               1461u   /* IF tx deallc signal name    NOT successfully cfg'd.  */
#define  NET_OS_ERR_INIT_IF_DEALLC_TASK                 1462u   /* IF tx deallc task           NOT successfully init'd. */
#define  NET_OS_ERR_INIT_IF_DEALLC_TASK_NAME            1463u   /* IF tx deallc task   name    NOT successfully cfg'd.  */

#define  NET_OS_ERR_INIT_IF_TX_SUSPEND                  1470u   /* IF tx suspend               NOT successfully init'd. */
#define  NET_OS_ERR_INIT_IF_TX_SUSPEND_NAME             1471u   /* IF tx suspend       name    NOT successfully cfg'd.  */
#define  NET_OS_ERR_INIT_IF_TX_SUSPEND_TIMEOUT          1472u   /* IF tx suspend       timeout NOT successfully cfg'd.  */


#define  NET_OS_ERR_INIT_TCP_RX_Q                       1500u   /* TCP  rx Q's                 NOT successfully init'd. */
#define  NET_OS_ERR_INIT_TCP_RX_Q_NAME                  1501u   /* TCP  rx Q's         name    NOT successfully init'd. */
#define  NET_OS_ERR_INIT_TCP_RX_Q_TIMEOUT               1502u   /* TCP  rx Q's         timeout NOT successfully init'd. */
#define  NET_OS_ERR_INIT_TCP_TX_Q                       1510u   /* TCP  tx Q's                 NOT successfully init'd. */
#define  NET_OS_ERR_INIT_TCP_TX_Q_NAME                  1511u   /* TCP  tx Q's         name    NOT successfully init'd. */
#define  NET_OS_ERR_INIT_TCP_TX_Q_TIMEOUT               1512u   /* TCP  tx Q's         timeout NOT successfully init'd. */

                                                                /* Sock errs (see Note #1b) :                           */
#define  NET_OS_ERR_INIT_SOCK_RX_Q                      1600u   /* Sock rx Q's                 NOT successfully init'd. */
#define  NET_OS_ERR_INIT_SOCK_RX_Q_NAME                 1601u   /* Sock rx Q's         name    NOT successfully init'd. */
#define  NET_OS_ERR_INIT_SOCK_RX_Q_TIMEOUT              1602u   /* Sock rx Q's         timeout NOT successfully init'd. */
#define  NET_OS_ERR_INIT_SOCK_CONN                      1610u   /* Sock conn   signal          NOT successfully init'd. */
#define  NET_OS_ERR_INIT_SOCK_CONN_NAME                 1611u   /* Sock conn   signal  name    NOT successfully init'd. */
#define  NET_OS_ERR_INIT_SOCK_CONN_TIMEOUT              1612u   /* Sock conn   signal  timeout NOT successfully init'd. */
#define  NET_OS_ERR_INIT_SOCK_ACCEPT                    1620u   /* Sock accept signal          NOT successfully init'd. */
#define  NET_OS_ERR_INIT_SOCK_ACCEPT_NAME               1621u   /* Sock accept signal  name    NOT successfully init'd. */
#define  NET_OS_ERR_INIT_SOCK_ACCEPT_TIMEOUT            1622u   /* Sock accept signal  timeout NOT successfully init'd. */
#define  NET_OS_ERR_INIT_SOCK_CLOSE                     1630u   /* Sock close  signal          NOT successfully init'd. */
#define  NET_OS_ERR_INIT_SOCK_CLOSE_NAME                1631u   /* Sock close  signal  name    NOT successfully init'd. */
#define  NET_OS_ERR_INIT_SOCK_CLOSE_TIMEOUT             1632u   /* Sock close  signal  timeout NOT successfully init'd. */


/*$PAGE*/
/*
*********************************************************************************************************
*                                 NETWORK UTILITY LIBRARY ERROR CODES
*********************************************************************************************************
*/

#define  NET_UTIL_ERR_NONE                              2000u
#define  NET_UTIL_ERR_NULL_PTR                          2020u   /* Ptr arg(s) passed NULL ptr(s).                       */
#define  NET_UTIL_ERR_NULL_SIZE                         2021u
#define  NET_UTIL_ERR_INVALID_PROTOCOL                  2030u   /* Invalid/unknown/unsupported net protocol.            */


/*
*********************************************************************************************************
*                                      ASCII LIBRARY ERROR CODES
*********************************************************************************************************
*/

#define  NET_ASCII_ERR_NONE                             3000u
#define  NET_ASCII_ERR_NULL_PTR                         3020u   /* Ptr arg(s) passed NULL ptr(s).                       */

#define  NET_ASCII_ERR_INVALID_STR_LEN                  3100u   /* Invalid ASCII str  len.                              */
#define  NET_ASCII_ERR_INVALID_CHAR                     3200u   /* Invalid ASCII char.                                  */
#define  NET_ASCII_ERR_INVALID_CHAR_LEN                 3101u   /* Invalid ASCII char len.                              */
#define  NET_ASCII_ERR_INVALID_CHAR_VAL                 3102u   /* Invalid ASCII char val.                              */
#define  NET_ASCII_ERR_INVALID_CHAR_SEQ                 3103u   /* Invalid ASCII char seq.                              */


/*
*********************************************************************************************************
*                               NETWORK STATISTIC MANAGEMENT ERROR CODES
*********************************************************************************************************
*/

#define  NET_STAT_ERR_NONE                              4000u
#define  NET_STAT_ERR_NULL_PTR                          4020u   /* Ptr arg(s) passed NULL ptr(s).                       */
#define  NET_STAT_ERR_INVALID_TYPE                      4030u   /* Type specified invalid or unknown.                   */

#define  NET_STAT_ERR_POOL_NONE_AVAIL                   4200u   /* NO stat pool entries avail.                          */
#define  NET_STAT_ERR_POOL_NONE_USED                    4201u   /* NO stat pool entries used.                           */
#define  NET_STAT_ERR_POOL_NONE_REM                     4202u   /* NO stat pool entries rem'ing.                        */


/*
*********************************************************************************************************
*                                NETWORK TIMER MANAGEMENT ERROR CODES
*********************************************************************************************************
*/

#define  NET_TMR_ERR_NONE                               5000u
#define  NET_TMR_ERR_NONE_AVAIL                         5010u   /* NO net tmrs avail.                                   */
#define  NET_TMR_ERR_NULL_PTR                           5020u   /* Ptr arg(s) passed NULL ptr(s).                       */
#define  NET_TMR_ERR_NULL_FNCT                          5021u   /* Arg 'fnct' is a NULL ptr.                            */
#define  NET_TMR_ERR_INVALID_TYPE                       5030u   /* Type specified invalid or unknown.                   */


/*$PAGE*/
/*
*********************************************************************************************************
*                                NETWORK BUFFER MANAGEMENT ERROR CODES
*********************************************************************************************************
*/

#define  NET_BUF_ERR_NONE                               6000u
#define  NET_BUF_ERR_NONE_AVAIL                         6010u   /* NO net bufs of req'd size avail.                     */
#define  NET_BUF_ERR_NOT_USED                           6011u   /* Net buf NOT used.                                    */
#define  NET_BUF_ERR_NULL_PTR                           6020u   /* Ptr arg(s) passed NULL ptr(s).                       */

#define  NET_BUF_ERR_INVALID_TYPE                       6030u   /* Invalid buf type or unknown.                         */
#define  NET_BUF_ERR_INVALID_SIZE                       6031u   /* Invalid buf size.                                    */
#define  NET_BUF_ERR_INVALID_IX                         6032u   /* Invalid buf ix  outside DATA area.                   */
#define  NET_BUF_ERR_INVALID_LEN                        6033u   /* Invalid buf len outside DATA area.                   */


#define  NET_BUF_ERR_POOL_INIT                          6040u   /* Buf pool init      failed.                           */
#define  NET_BUF_ERR_POOL_MEM_ALLOC                     6041u   /* Buf pool mem alloc failed.                           */

#define  NET_BUF_ERR_INVALID_POOL_TYPE                  6050u   /* Invalid buf pool type.                               */
#define  NET_BUF_ERR_INVALID_POOL_QTY                   6051u   /* Invalid buf pool qty cfg'd.                          */


#define  NET_BUF_ERR_TX_LOCK                            6500u   /* Invalid tx buf access; tx is locked.                 */


/*
*********************************************************************************************************
*                              NETWORK CONNECTION MANAGEMENT ERROR CODES
*********************************************************************************************************
*/

#define  NET_CONN_ERR_NONE                              7000u
#define  NET_CONN_ERR_NONE_AVAIL                        7010u   /* NO net conns avail.                                  */
#define  NET_CONN_ERR_NOT_USED                          7011u   /* Net conn NOT used.                                   */
#define  NET_CONN_ERR_NULL_PTR                          7020u   /* Ptr arg(s) passed NULL ptr(s).                       */

#define  NET_CONN_ERR_INVALID_TYPE                      7050u   /* Invalid conn type.                                   */
#define  NET_CONN_ERR_INVALID_CONN                      7051u   /* Invalid conn id.                                     */
#define  NET_CONN_ERR_INVALID_FAMILY                    7052u   /* Invalid conn list family.                            */
#define  NET_CONN_ERR_INVALID_PROTOCOL_IX               7053u   /* Invalid conn list protocol ix.                       */
#define  NET_CONN_ERR_INVALID_ADDR                      7054u   /* Invalid conn addr.                                   */
#define  NET_CONN_ERR_INVALID_ADDR_LEN                  7055u   /* Invalid conn addr len.                               */

#define  NET_CONN_ERR_ADDR_NOT_USED                     7100u   /* Conn addr NOT    used.                               */
#define  NET_CONN_ERR_ADDR_IN_USE                       7101u   /* Conn addr cur in use.                                */

#define  NET_CONN_ERR_CONN_NONE                         7110u   /* NO   conn.                                           */
#define  NET_CONN_ERR_CONN_HALF                         7111u   /* Half conn (local                   addr valid).      */
#define  NET_CONN_ERR_CONN_HALF_WILDCARD                7112u   /* Half conn (local wildcard          addr valid).      */
#define  NET_CONN_ERR_CONN_FULL                         7113u   /* Full conn (local          & remote addr valid).      */
#define  NET_CONN_ERR_CONN_FULL_WILDCARD                7114u   /* Full conn (local wildcard & remote addr valid).      */


/*$PAGE*/
/*
*********************************************************************************************************
*                           NETWORK BOARD SUPPORT PACKAGE (BSP) ERROR CODES
*
* Note(s) : (1) Specific BSP error codes #define'd in their respective network-/board-specific header
*               files ('net_bsp.h').
*********************************************************************************************************
*/

#define  NET_BSP_ERR_NONE                              10000u


/*
*********************************************************************************************************
*                                     NETWORK DEVICE ERROR CODES
*
* Note(s) : (1) Specific device error codes #define'd in their respective network device driver header
*               files ('net_dev_&&&.h').
*********************************************************************************************************
*/

#define  NET_DEV_ERR_NONE                              11000u
#define  NET_DEV_ERR_INIT                              11010u   /* Dev init  failed.                                    */
#define  NET_DEV_ERR_FAULT                             11011u   /* Dev fault/failure.                                   */
#define  NET_DEV_ERR_NULL_PTR                          11020u   /* Ptr arg(s) passed NULL ptr(s).                       */
#define  NET_DEV_ERR_NULL_FNCT                         11021u   /* Invalid/NULL fnct ptr(s).                            */
#define  NET_DEV_ERR_MEM_ALLOC                         11030u   /* Mem alloc failed.                                    */
#define  NET_DEV_ERR_DEV_OFF                           11050u   /* Dev status is 'OFF' or 'DOWN'.                       */

#define  NET_DEV_ERR_INVALID_IF                        11100u   /* Invalid dev/IF nbr.                                  */
#define  NET_DEV_ERR_INVALID_CFG                       11110u   /* Invalid dev cfg.                                     */
#define  NET_DEV_ERR_INVALID_SIZE                      11120u   /* Invalid size.                                        */
#define  NET_DEV_ERR_INVALID_DATA_PTR                  11130u   /* Invalid dev drv data ptr.                            */

#define  NET_DEV_ERR_ADDR_MULTICAST_ADD                11200u   /* Multicast addr add    failed.                        */
#define  NET_DEV_ERR_ADDR_MULTICAST_REMOVE             11201u   /* Multicast addr remove failed.                        */


#define  NET_DEV_ERR_RX                                11400u   /* Dev rx failed or fault.                              */
#define  NET_DEV_ERR_RX_BUSY                           11410u   /* Rx'r busy -- cannot rx data.                         */

#define  NET_DEV_ERR_TX                                11500u   /* Dev tx failed or fault.                              */
#define  NET_DEV_ERR_TX_BUSY                           11510u   /* Tx'r busy -- cannot tx data.                         */
#define  NET_DEV_ERR_TX_RDY_SIGNAL                     11520u   /* Tx rdy signal failed.                                */
#define  NET_DEV_ERR_TX_RDY_SIGNAL_TIMEOUT             11521u   /* Tx rdy signal timeout; NO signal rx'd from dev.      */
#define  NET_DEV_ERR_TX_RDY_SIGNAL_FAULT               11522u   /* Tx rdy signal fault.                                 */


/*
*********************************************************************************************************
*                                 NETWORK PHYSICAL LAYER ERROR CODES
*
* Note(s) : (1) Specific physical layer error codes #define'd in their respective physical layer driver
*               header files ('net_phy_&&&.h').
*********************************************************************************************************
*/

#define  NET_PHY_ERR_NONE                              12000u
#define  NET_PHY_ERR_NULL_PTR                          12020u   /* Ptr arg(s) passed NULL ptr(s).                       */
#define  NET_PHY_ERR_NULL_FNCT                         12021u   /* Invalid/NULL fnct ptr(s).                            */

#define  NET_PHY_ERR_INVALID_CFG                       12100u   /* Invalid phy cfg.                                     */
#define  NET_PHY_ERR_INVALID_ADDR                      12101u   /* Invalid phy addr.                                    */
#define  NET_PHY_ERR_INVALID_BUS_MODE                  12102u   /* Invalid phy bus mode.                                */

#define  NET_PHY_ERR_TIMEOUT_REG_RD                    12200u   /* Phy reg rd           timeout.                        */
#define  NET_PHY_ERR_TIMEOUT_REG_WR                    12201u   /* Phy reg wr           timeout.                        */
#define  NET_PHY_ERR_TIMEOUT_AUTO_NEG                  12202u   /* Phy auto-negotiation timeout.                        */
#define  NET_PHY_ERR_TIMEOUT_RESET                     12203u   /* Phy reset            timeout.                        */
#define  NET_PHY_ERR_ADDR_PROBE                        12204u   /* Phy addr detection   failed.                         */


/*$PAGE*/
/*
*********************************************************************************************************
*                                 NETWORK INTERFACE LAYER ERROR CODES
*
* Note(s) : (1) Specific IF error codes #define'd in their respective network interface header files
*               ('net_if_&&&.h') since they are IF-dependent.
*
*           (2) The following error codes abbreviated to enforce ANSI-compliance of 31-character symbol
*               length uniqueness :
*
*               (a) 'NET_IF_ERR_TX_DEALLOC_Q'  abbreviated to 'NET_IF_ERR_TX_DEALLC_Q'
*********************************************************************************************************
*/

#define  NET_IF_ERR_NONE                               13000u
#define  NET_IF_ERR_NONE_AVAIL                         13010u   /* NO link layer/IF rsrc(s) avail.                      */
#define  NET_IF_ERR_NULL_PTR                           13020u   /* Ptr arg(s) passed NULL ptr(s).                       */
#define  NET_IF_ERR_NULL_FNCT                          13021u   /* Invalid/NULL fnct ptr(s).                            */
#define  NET_IF_ERR_API_DIS                            13025u   /* Disabled API fnct.                                   */
#define  NET_IF_ERR_LINK_DOWN                          13050u   /* Net IF link state down.                              */
#define  NET_IF_ERR_ALIGN_NOT_AVAIL                    13060u   /* App data buf alignment NOT possible.                 */


#define  NET_IF_ERR_INVALID_IF                         13100u   /* Invalid IF nbr.                                      */
#define  NET_IF_ERR_INVALID_CFG                        13101u   /* Invalid IF API/Cfg/Data.                             */
#define  NET_IF_ERR_INVALID_STATE                      13110u   /* Invalid IF state.                                    */
#define  NET_IF_ERR_INVALID_IO_CTRL_OPT                13120u   /* Invalid/unsupported IO ctrl opt.                     */
#define  NET_IF_ERR_INVALID_ISR_TYPE                   13130u   /* Invalid/unsupported ISR type.                        */

#define  NET_IF_ERR_INVALID_POOL_TYPE                  13150u   /* Invalid IF buf pool type.                            */
#define  NET_IF_ERR_INVALID_POOL_ADDR                  13151u   /* Invalid IF buf pool addr.                            */
#define  NET_IF_ERR_INVALID_POOL_SIZE                  13152u   /* Invalid IF buf pool size.                            */
#define  NET_IF_ERR_INVALID_POOL_QTY                   13153u   /* Invalid IF buf pool qty cfg'd.                       */


#define  NET_IF_ERR_INVALID_MTU                        13200u   /* Invalid MTU.                                         */
#define  NET_IF_ERR_INVALID_LEN_DATA                   13201u   /* Invalid data  len.                                   */
#define  NET_IF_ERR_INVALID_LEN_FRAME                  13202u   /* Invalid frame len.                                   */

#define  NET_IF_ERR_INVALID_ADDR                       13210u   /* Invalid addr.                                        */
#define  NET_IF_ERR_INVALID_ADDR_LEN                   13211u   /* Invalid addr len.                                    */
#define  NET_IF_ERR_INVALID_ADDR_DEST                  13212u   /* Invalid addr dest.                                   */
#define  NET_IF_ERR_INVALID_ADDR_SRC                   13213u   /* Invalid addr sec.                                    */


#define  NET_IF_ERR_RX                                 13400u   /* Rx failed or fault.                                  */
#define  NET_IF_ERR_RX_Q_EMPTY                         13410u   /* Rx Q empty; i.e.       NO rx'd pkt(s) in Q.          */
#define  NET_IF_ERR_RX_Q_FULL                          13411u   /* Rx Q full;  i.e. too many rx'd pkt(s) in Q.          */
#define  NET_IF_ERR_RX_Q_SIGNAL                        13415u   /* Rx Q signal failed.                                  */
#define  NET_IF_ERR_RX_Q_SIGNAL_TIMEOUT                13416u   /* Rx Q signal timeout; NO pkt(s) rx'd from dev.        */
#define  NET_IF_ERR_RX_Q_SIGNAL_FAULT                  13417u   /* Rx Q signal fault.                                   */


#define  NET_IF_ERR_LOOPBACK_DIS                       13450u   /* Loopback IF dis'd.                                   */
#define  NET_IF_ERR_LOOPBACK_RX_Q_EMPTY                13460u   /* Loopback rx Q empty; i.e.       NO rx'd pkt(s) in Q. */
#define  NET_IF_ERR_LOOPBACK_RX_Q_FULL                 13461u   /* Loopback rx Q full;  i.e. too many rx'd pkt(s) in Q. */


#define  NET_IF_ERR_TX                                 13500u   /* Tx failed or fault.                                  */
#define  NET_IF_ERR_TX_RDY                             13510u   /* Tx to dev rdy.                                       */
#define  NET_IF_ERR_TX_BROADCAST                       13511u   /* Tx broadcast on local net.                           */
#define  NET_IF_ERR_TX_MULTICAST                       13512u   /* Tx multicast on local net.                           */
#define  NET_IF_ERR_TX_ADDR_REQ                        13520u   /* Tx req  for hw addr.                                 */
#define  NET_IF_ERR_TX_ADDR_PEND                       13521u   /* Tx pend on  hw addr.                                 */

                                                                /* Tx dealloc Q errs (see Note #2a) :                   */
#define  NET_IF_ERR_TX_DEALLC_Q_EMPTY                  13550u   /* Tx dealloc Q empty; i.e.       NO tx completed pkts. */
#define  NET_IF_ERR_TX_DEALLC_Q_FULL                   13551u   /* Tx dealloc Q full;  i.e. too many tx completed pkts. */
#define  NET_IF_ERR_TX_DEALLC_Q_SIGNAL                 13555u   /* Tx dealloc Q signal failed.                          */
#define  NET_IF_ERR_TX_DEALLC_Q_SIGNAL_TIMEOUT         13556u   /* Tx dealloc Q signal timeout.                         */
#define  NET_IF_ERR_TX_DEALLC_Q_SIGNAL_FAULT           13557u   /* Tx dealloc Q signal fault.                           */


/*$PAGE*/
/*
*********************************************************************************************************
*                                        ARP LAYER ERROR CODES
*
* Note(s) : (1) The following error codes abbreviated to enforce ANSI-compliance of 31-character symbol
*               length uniqueness :
*
*               (a) 'NET_ARP_ERR_INVALID_PROTOCOL_ADDR_LEN' abbreviated to 'NET_ARP_ERR_INVALID_PROTOCOL_LEN'
*********************************************************************************************************
*/

#define  NET_ARP_ERR_NONE                              15000u
#define  NET_ARP_ERR_NULL_PTR                          15020u   /* Ptr arg(s) passed NULL ptr(s).                       */


#define  NET_ARP_ERR_INVALID_HW_TYPE                   15100u   /* Invalid ARP hw       type.                           */
#define  NET_ARP_ERR_INVALID_HW_ADDR                   15101u   /* Invalid ARP hw       addr.                           */
#define  NET_ARP_ERR_INVALID_HW_ADDR_LEN               15102u   /* Invalid ARP hw       addr len.                       */
#define  NET_ARP_ERR_INVALID_PROTOCOL_TYPE             15103u   /* Invalid ARP protocol type.                           */
#define  NET_ARP_ERR_INVALID_PROTOCOL_ADDR             15104u   /* Invalid ARP protocol addr.                           */
#define  NET_ARP_ERR_INVALID_PROTOCOL_LEN              15105u   /* Invalid ARP protocol addr len (see Note #1a).        */
#define  NET_ARP_ERR_INVALID_OP_CODE                   15106u   /* Invalid ARP op code.                                 */
#define  NET_ARP_ERR_INVALID_OP_ADDR                   15107u   /* Invalid ARP op code  addr.                           */
#define  NET_ARP_ERR_INVALID_LEN_MSG                   15108u   /* Invalid ARP msg len.                                 */


#define  NET_ARP_ERR_CACHE_NONE_AVAIL                  15150u   /* NO ARP caches avail.                                 */
#define  NET_ARP_ERR_CACHE_INVALID_TYPE                15151u   /* ARP cache type invalid or unknown.                   */
#define  NET_ARP_ERR_CACHE_NOT_FOUND                   15155u   /* ARP cache NOT found.                                 */
#define  NET_ARP_ERR_CACHE_PEND                        15156u   /* ARP cache hw addr pending.                           */
#define  NET_ARP_ERR_CACHE_RESOLVED                    15157u   /* ARP cache hw addr resolved.                          */


#define  NET_ARP_ERR_RX_TARGET_THIS_HOST               15400u   /* Rx ARP msg     for this host.                        */
#define  NET_ARP_ERR_RX_TARGET_NOT_THIS_HOST           15401u   /* Rx ARP msg NOT for this host.                        */
#define  NET_ARP_ERR_RX_TARGET_REPLY                   15402u   /* Rx ARP Reply   for this host NOT in ARP cache.       */

#define  NET_ARP_ERR_RX_REQ_TX_REPLY                   15450u   /* Rx'd ARP Req;   tx ARP Reply.                        */
#define  NET_ARP_ERR_RX_REPLY_TX_PKTS                  15451u   /* Rx'd ARP Reply; tx ARP cache pkts.                   */


/*$PAGE*/
/*
*********************************************************************************************************
*                                NETWORK LAYER MANAGEMENT ERROR CODES
*
* Note(s) : (1) The following error codes abbreviated to enforce ANSI-compliance of 31-character symbol
*               length uniqueness :
*
*               (a) 'NET_MGR_ERR_INVALID_PROTOCOL_ADDR_LEN' abbreviated to 'NET_MGR_ERR_INVALID_PROTOCOL_LEN'
*********************************************************************************************************
*/

#define  NET_MGR_ERR_NONE                              20000u
#define  NET_MGR_ERR_FAULT                             20010u   /* Unknown fault.                                       */
#define  NET_MGR_ERR_NULL_PTR                          20020u   /* Ptr arg(s) passed NULL ptr(s).                       */

#define  NET_MGR_ERR_INVALID_PROTOCOL                  20100u   /* Invalid/unsupported protocol.                        */
#define  NET_MGR_ERR_INVALID_PROTOCOL_ADDR             20101u   /* Invalid protocol addr.                               */
#define  NET_MGR_ERR_INVALID_PROTOCOL_LEN              20102u   /* Invalid protocol addr len (see Note #1a).            */

#define  NET_MGR_ERR_ADDR_CFG_IN_PROGRESS              20202u   /*      IF addr cfg in progress.                        */
#define  NET_MGR_ERR_ADDR_TBL_SIZE                     20220u   /* Invalid addr tbl size.                               */


/*$PAGE*/
/*
*********************************************************************************************************
*                                        IP LAYER ERROR CODES
*********************************************************************************************************
*/

#define  NET_IP_ERR_NONE                               21000u
#define  NET_IP_ERR_NULL_PTR                           21020u   /* Ptr arg(s) passed NULL ptr(s).                       */


#define  NET_IP_ERR_INVALID_VER                        21100u   /* Invalid IP ver.                                      */
#define  NET_IP_ERR_INVALID_LEN_HDR                    21101u   /* Invalid IP hdr  len.                                 */
#define  NET_IP_ERR_INVALID_TOS                        21102u   /* Invalid IP TOS.                                      */
#define  NET_IP_ERR_INVALID_LEN_TOT                    21103u   /* Invalid IP tot  len.                                 */
#define  NET_IP_ERR_INVALID_LEN_DATA                   21104u   /* Invalid IP data len.                                 */
#define  NET_IP_ERR_INVALID_FLAG                       21105u   /* Invalid IP flags.                                    */
#define  NET_IP_ERR_INVALID_FRAG                       21106u   /* Invalid IP fragmentation.                            */
#define  NET_IP_ERR_INVALID_TTL                        21107u   /* Invalid IP TTL.                                      */
#define  NET_IP_ERR_INVALID_PROTOCOL                   21108u   /* Invalid/unknown protocol type.                       */
#define  NET_IP_ERR_INVALID_CHK_SUM                    21109u   /* Invalid IP chk sum.                                  */
#define  NET_IP_ERR_INVALID_ADDR_LEN                   21110u   /* Invalid IP           addr len.                       */
#define  NET_IP_ERR_INVALID_ADDR_SRC                   21111u   /* Invalid IP src       addr.                           */
#define  NET_IP_ERR_INVALID_ADDR_DEST                  21112u   /* Invalid IP dest      addr.                           */
#define  NET_IP_ERR_INVALID_ADDR_BROADCAST             21113u   /* Invalid IP broadcast addr.                           */
#define  NET_IP_ERR_INVALID_ADDR_HOST                  21115u   /* Invalid IP host      addr.                           */
#define  NET_IP_ERR_INVALID_ADDR_NET                   21116u   /* Invalid IP net       addr.                           */
#define  NET_IP_ERR_INVALID_ADDR_GATEWAY               21117u   /* Invalid IP gateway   addr.                           */
#define  NET_IP_ERR_INVALID_OPT                        21120u   /* Invalid IP opt.                                      */
#define  NET_IP_ERR_INVALID_OPT_PTR                    21121u   /* Invalid IP opt ptr.                                  */
#define  NET_IP_ERR_INVALID_OPT_LEN                    21122u   /* Invalid IP opt len.                                  */
#define  NET_IP_ERR_INVALID_OPT_TYPE                   21123u   /* Invalid IP opt type.                                 */
#define  NET_IP_ERR_INVALID_OPT_NBR                    21124u   /* Invalid IP opt nbr same opt.                         */
#define  NET_IP_ERR_INVALID_OPT_CFG                    21125u   /* Invalid IP opt cfg.                                  */
#define  NET_IP_ERR_INVALID_OPT_FLAG                   21126u   /* Invalid IP opt flag.                                 */
#define  NET_IP_ERR_INVALID_OPT_ROUTE                  21127u   /* Invalid IP opt route.                                */
#define  NET_IP_ERR_INVALID_OPT_END                    21128u   /* Invalid IP opt list ending.                          */


#define  NET_IP_ERR_ADDR_CFG                           21200u   /* Invalid IP addr cfg.                                 */
#define  NET_IP_ERR_ADDR_CFG_STATE                     21201u   /* Invalid IP addr cfg state.                           */
#define  NET_IP_ERR_ADDR_CFG_IN_PROGRESS               21202u   /*         IF addr cfg in progress.                     */
#define  NET_IP_ERR_ADDR_CFG_IN_USE                    21203u   /*         IP addr cur in use.                          */
#define  NET_IP_ERR_ADDR_NONE_AVAIL                    21210u   /* NO      IP addr(s)  cfg'd.                           */
#define  NET_IP_ERR_ADDR_NOT_FOUND                     21211u   /*         IP addr NOT found.                           */
#define  NET_IP_ERR_ADDR_TBL_SIZE                      21220u   /* Invalid IP addr tbl size.                            */
#define  NET_IP_ERR_ADDR_TBL_EMPTY                     21221u   /*         IP addr tbl empty.                           */
#define  NET_IP_ERR_ADDR_TBL_FULL                      21222u   /*         IP addr tbl full.                            */


#define  NET_IP_ERR_RX_FRAG_NONE                       21400u   /* Rx'd datagram NOT frag'd.                            */
#define  NET_IP_ERR_RX_FRAG_OFFSET                     21401u   /* Invalid frag offset.                                 */
#define  NET_IP_ERR_RX_FRAG_SIZE                       21402u   /* Invalid frag     size.                               */
#define  NET_IP_ERR_RX_FRAG_SIZE_TOT                   21403u   /* Invalid frag tot size.                               */
#define  NET_IP_ERR_RX_FRAG_LEN_TOT                    21404u   /* Invalid frag tot len.                                */
#define  NET_IP_ERR_RX_FRAG_DISCARD                    21405u   /* Invalid frag(s) discarded.                           */
#define  NET_IP_ERR_RX_FRAG_REASM                      21410u   /* Frag'd datagram reasm in progress.                   */
#define  NET_IP_ERR_RX_FRAG_COMPLETE                   21411u   /* Frag'd datagram reasm'd.                             */

#define  NET_IP_ERR_RX_OPT_BUF_NONE_AVAIL              21420u   /* No bufs avail for IP opts.                           */
#define  NET_IP_ERR_RX_OPT_BUF_LEN                     21421u   /* IP opt buf len err.                                  */
#define  NET_IP_ERR_RX_OPT_BUF_WR                      21422u   /* IP opt buf wr  err.                                  */


#define  NET_IP_ERR_TX_PKT                             21500u   /* Tx pkt err.                                          */
#define  NET_IP_ERR_TX_DEST_NONE                       21510u   /* NO      tx dest.                                     */
#define  NET_IP_ERR_TX_DEST_INVALID                    21511u   /* Invalid tx dest.                                     */
#define  NET_IP_ERR_TX_DEST_LOCAL_HOST                 21512u   /* Tx to local host   addr.                             */
#define  NET_IP_ERR_TX_DEST_BROADCAST                  21513u   /* Tx to local net broadcast.                           */
#define  NET_IP_ERR_TX_DEST_MULTICAST                  21514u   /* Tx to local net multicast.                           */
#define  NET_IP_ERR_TX_DEST_HOST_THIS_NET              21515u   /* Tx to local net host.                                */
#define  NET_IP_ERR_TX_DEST_DFLT_GATEWAY               21516u   /* Tx to local net dflt gateway.                        */


/*$PAGE*/
/*
*********************************************************************************************************
*                                       ICMP LAYER ERROR CODES
*********************************************************************************************************
*/

#define  NET_ICMP_ERR_NONE                             22000u
#define  NET_ICMP_ERR_NONE_AVAIL                       22001u   /* NO ICMP data type avail.                             */


#define  NET_ICMP_ERR_INVALID_TYPE                     22100u   /* Invalid ICMP msg  type / ICMP data type.             */
#define  NET_ICMP_ERR_INVALID_CODE                     22101u   /* Invalid ICMP msg  code.                              */
#define  NET_ICMP_ERR_INVALID_PTR                      22102u   /* Invalid ICMP msg  ptr.                               */
#define  NET_ICMP_ERR_INVALID_LEN                      22103u   /* Invalid ICMP msg  len.                               */
#define  NET_ICMP_ERR_INVALID_LEN_DATA                 22104u   /* Invalid ICMP data len.                               */
#define  NET_ICMP_ERR_INVALID_CHK_SUM                  22105u   /* Invalid ICMP chk  sum.                               */

#define  NET_ICMP_ERR_MSG_TYPE_ERR                     22150u   /* ICMP err   msg type.                                 */
#define  NET_ICMP_ERR_MSG_TYPE_REQ                     22151u   /* ICMP req   msg type.                                 */
#define  NET_ICMP_ERR_MSG_TYPE_REPLY                   22152u   /* ICMP reply msg type.                                 */


#define  NET_ICMP_ERR_RX_BROADCAST                     22400u   /* ICMP rx invalid broadcast.                           */
#define  NET_ICMP_ERR_RX_MULTICAST                     22401u   /* ICMP rx invalid multicast.                           */


#define  NET_ICMP_ERR_TX_INVALID_BROADCAST             22500u   /* ICMP tx invalid broadcast.                           */
#define  NET_ICMP_ERR_TX_INVALID_MULTICAST             22501u   /* ICMP tx invalid multicast.                           */
#define  NET_ICMP_ERR_TX_INVALID_FRAG                  22502u   /* ICMP tx invalid frag.                                */
#define  NET_ICMP_ERR_TX_INVALID_ADDR_SRC              22503u   /* ICMP tx invalid addr src.                            */
#define  NET_ICMP_ERR_TX_INVALID_ERR_MSG               22504u   /* ICMP tx invalid err msg.                             */


/*
*********************************************************************************************************
*                                       IGMP LAYER ERROR CODES
*********************************************************************************************************
*/

#define  NET_IGMP_ERR_NONE                             23000u

#define  NET_IGMP_ERR_INVALID_VER                      23100u   /* Invalid IGMP ver.                                    */
#define  NET_IGMP_ERR_INVALID_TYPE                     23101u   /* Invalid IGMP msg  type.                              */
#define  NET_IGMP_ERR_INVALID_LEN                      23102u   /* Invalid IGMP msg  len.                               */
#define  NET_IGMP_ERR_INVALID_CHK_SUM                  23103u   /* Invalid IGMP chk  sum.                               */
#define  NET_IGMP_ERR_INVALID_ADDR_SRC                 23104u   /* Invalid IGMP src  addr.                              */
#define  NET_IGMP_ERR_INVALID_ADDR_DEST                23105u   /* Invalid IGMP dest addr                               */
#define  NET_IGMP_ERR_INVALID_ADDR_GRP                 23106u   /* Invalid IGMP grp  addr.                              */

#define  NET_IGMP_ERR_MSG_TYPE_QUERY                   23150u   /* IGMP query  msg type.                                */
#define  NET_IGMP_ERR_MSG_TYPE_REPORT                  23151u   /* IGMP report msg type.                                */


#define  NET_IGMP_ERR_HOST_GRP_NONE_AVAIL              23200u   /* NO IGMP host grp avail.                              */
#define  NET_IGMP_ERR_HOST_GRP_NOT_FOUND               23202u   /*    IGMP host grp NOT found.                          */
#define  NET_IGMP_ERR_HOST_GRP_INVALID_TYPE            23201u   /*    IGMP host grp type invalid or unknown.            */


/*$PAGE*/
/*
*********************************************************************************************************
*                                        UDP LAYER ERROR CODES
*********************************************************************************************************
*/

#define  NET_UDP_ERR_NONE                              30000u
#define  NET_UDP_ERR_NULL_PTR                          30020u   /* Ptr arg(s) passed NULL ptr(s).                       */

#define  NET_UDP_ERR_INVALID_DATA_SIZE                 30040u   /* Invalid UDP data size.                               */

#define  NET_UDP_ERR_INVALID_LEN                       30100u   /* Invalid UDP datagram len.                            */
#define  NET_UDP_ERR_INVALID_LEN_DATA                  30101u   /* Invalid UDP data     len.                            */
#define  NET_UDP_ERR_INVALID_ADDR_SRC                  30102u   /* Invalid UDP src  addr.                               */
#define  NET_UDP_ERR_INVALID_PORT_NBR                  30103u   /* Invalid UDP port nbr.                                */
#define  NET_UDP_ERR_INVALID_CHK_SUM                   30104u   /* Invalid UDP chk  sum.                                */
#define  NET_UDP_ERR_INVALID_FLAG                      30105u   /* Invalid UDP flags.                                   */


/*
*********************************************************************************************************
*                                        TCP LAYER ERROR CODES
*********************************************************************************************************
*/

#define  NET_TCP_ERR_NONE                              31000u
#define  NET_TCP_ERR_NONE_AVAIL                        31010u   /* NO TCP conns avail.                                  */
#define  NET_TCP_ERR_NULL_PTR                          31020u   /* Ptr arg(s) passed NULL ptr(s).                       */

#define  NET_TCP_ERR_INVALID_DATA_SIZE                 31040u   /* Invalid TCP data size.                               */
#define  NET_TCP_ERR_INVALID_ARG                       31106u   /* Invalid TCP arg.                                     */


#define  NET_TCP_ERR_INVALID_LEN_HDR                   31100u   /* Invalid TCP hdr  len.                                */
#define  NET_TCP_ERR_INVALID_LEN_SEG                   31101u   /* Invalid TCP seg  len.                                */
#define  NET_TCP_ERR_INVALID_LEN_DATA                  31102u   /* Invalid TCP data len.                                */
#define  NET_TCP_ERR_INVALID_PORT_NBR                  31103u   /* Invalid TCP port nbr.                                */
#define  NET_TCP_ERR_INVALID_FLAG                      31104u   /* Invalid TCP flags.                                   */
#define  NET_TCP_ERR_INVALID_CHK_SUM                   31105u   /* Invalid TCP chk sum.                                 */

#define  NET_TCP_ERR_INVALID_OPT                       31110u   /* Invalid TCP opt.                                     */
#define  NET_TCP_ERR_INVALID_OPT_TYPE                  31111u   /* Invalid TCP opt type.                                */
#define  NET_TCP_ERR_INVALID_OPT_NBR                   31112u   /* Invalid TCP opt nbr same opt.                        */
#define  NET_TCP_ERR_INVALID_OPT_LEN                   31113u   /* Invalid TCP opt len.                                 */
#define  NET_TCP_ERR_INVALID_OPT_CFG                   31114u   /* Invalid TCP opt cfg.                                 */
#define  NET_TCP_ERR_INVALID_OPT_END                   31115u   /* Invalid TCP opt list ending.                         */

/*$PAGE*/
#define  NET_TCP_ERR_INVALID_CONN_TYPE                 31200u   /* Invalid   TCP conn type.                             */
#define  NET_TCP_ERR_INVALID_CONN                      31201u   /* Invalid   TCP conn/id.                               */
#define  NET_TCP_ERR_INVALID_CONN_ID                   31202u   /* Invalid   TCP conn's conn id.                        */
#define  NET_TCP_ERR_INVALID_CONN_OP                   31203u   /* Invalid   TCP conn op.                               */
#define  NET_TCP_ERR_INVALID_CONN_STATE                31204u   /* Invalid   TCP conn state.                            */

#define  NET_TCP_ERR_CONN_NONE                         31210u   /* NO        TCP conn.                                  */
#define  NET_TCP_ERR_CONN_NOT_USED                     31211u   /*           TCP conn NOT used.                         */
#define  NET_TCP_ERR_CONN_CLOSED                       31220u   /*           TCP conn successfully closed.              */
#define  NET_TCP_ERR_CONN_CLOSE                        31221u   /*           TCP conn abort        closed.              */
#define  NET_TCP_ERR_CONN_FAULT                        31222u   /*           TCP conn fault        closed.              */
#define  NET_TCP_ERR_CONN_FAIL                         31225u   /*           TCP conn op failed.                        */
#define  NET_TCP_ERR_CONN_LISTEN_Q_MAX                 31230u   /*           TCP conn listen Q max lim.                 */

#define  NET_TCP_ERR_CONN_SEQ_NONE                     31250u   /* NO        TCP conn seq.                              */
#define  NET_TCP_ERR_CONN_SEQ_SYNC                     31251u   /*   Valid   TCP conn sync.                             */
#define  NET_TCP_ERR_CONN_SEQ_SYNC_INVALID             31252u   /* Invalid   TCP conn sync.                             */
#define  NET_TCP_ERR_CONN_SEQ_VALID                    31253u   /*   Valid   TCP conn seq.                              */
#define  NET_TCP_ERR_CONN_SEQ_INVALID                  31254u   /* Invalid   TCP conn seq.                              */
#define  NET_TCP_ERR_CONN_SEQ_FIN_VALID                31255u   /*   Valid   TCP conn fin.                              */
#define  NET_TCP_ERR_CONN_SEQ_FIN_INVALID              31256u   /* Invalid   TCP conn fin.                              */

#define  NET_TCP_ERR_CONN_ACK_NONE                     31260u   /* NO        TCP conn ack.                              */
#define  NET_TCP_ERR_CONN_ACK_VALID                    31261u   /*   Valid   TCP conn ack.                              */
#define  NET_TCP_ERR_CONN_ACK_INVALID                  31262u   /* Invalid   TCP conn ack.                              */
#define  NET_TCP_ERR_CONN_ACK_DUP                      31263u   /* Duplicate TCP conn ack.                              */
#define  NET_TCP_ERR_CONN_ACK_DLYD                     31265u   /* Dly'd     TCP conn ack.                              */
#define  NET_TCP_ERR_CONN_ACK_PREVLY_TXD               31266u   /*           TCP conn ack prev'ly tx'd.                 */

#define  NET_TCP_ERR_CONN_RESET_NONE                   31270u   /* NO        TCP conn reset.                            */
#define  NET_TCP_ERR_CONN_RESET_VALID                  31271u   /*   Valid   TCP conn reset.                            */
#define  NET_TCP_ERR_CONN_RESET_INVALID                31272u   /* Invalid   TCP conn reset.                            */

#define  NET_TCP_ERR_CONN_PROBE_INVALID                31282u   /* Invalid   TCP conn probe.                            */

#define  NET_TCP_ERR_CONN_DATA_NONE                    31290u   /* NO        TCP conn data.                             */
#define  NET_TCP_ERR_CONN_DATA_VALID                   31291u   /*   Valid   TCP conn data.                             */
#define  NET_TCP_ERR_CONN_DATA_INVALID                 31292u   /* Invalid   TCP conn data.                             */
#define  NET_TCP_ERR_CONN_DATA_DUP                     31293u   /* Duplicate TCP conn data.                             */


#define  NET_TCP_ERR_RX                                31400u   /*    Rx err.                                           */
#define  NET_TCP_ERR_RX_Q_CLOSED                       31410u   /*    Rx Q closed; i.e.   do NOT rx   pkt(s) to Q.      */
#define  NET_TCP_ERR_RX_Q_EMPTY                        31411u   /*    Rx Q empty;  i.e.      NO  rx'd pkt(s) in Q.      */
#define  NET_TCP_ERR_RX_Q_FULL                         31412u   /*    Rx Q full;   i.e. too many rx'd pkt(s) in Q.      */
#define  NET_TCP_ERR_RX_Q_ABORT                        31415u   /*    Rx Q abort      failed.                           */
#define  NET_TCP_ERR_RX_Q_SIGNAL                       31420u   /*    Rx Q signal     failed.                           */
#define  NET_TCP_ERR_RX_Q_SIGNAL_CLR                   31421u   /*    Rx Q signal clr failed.                           */
#define  NET_TCP_ERR_RX_Q_SIGNAL_TIMEOUT               31422u   /*    Rx Q signal timeout.                              */
#define  NET_TCP_ERR_RX_Q_SIGNAL_ABORT                 31423u   /*    Rx Q signal aborted.                              */
#define  NET_TCP_ERR_RX_Q_SIGNAL_FAULT                 31424u   /*    Rx Q signal fault.                                */

#define  NET_TCP_ERR_TX_PKT                            31500u   /*    Tx pkt err.                                       */
#define  NET_TCP_ERR_TX_Q_CLOSED                       31510u   /*    Tx Q closed; i.e.   do NOT Q tx   pkt(s) to Q.    */
#define  NET_TCP_ERR_TX_Q_EMPTY                        31511u   /*    Tx Q empty;  i.e.      NO    tx   pkt(s) in Q.    */
#define  NET_TCP_ERR_TX_Q_FULL                         31512u   /*    Tx Q full;   i.e. too many   tx'd pkt(s) in Q.    */
#define  NET_TCP_ERR_TX_Q_ABORT                        31515u   /*    Tx Q abort      failed.                           */
#define  NET_TCP_ERR_TX_Q_SUSPEND                      31516u   /*    Tx Q suspended.                                   */
#define  NET_TCP_ERR_TX_Q_SIGNAL                       31520u   /*    Tx Q signal     failed.                           */
#define  NET_TCP_ERR_TX_Q_SIGNAL_CLR                   31521u   /*    Tx Q signal clr failed.                           */
#define  NET_TCP_ERR_TX_Q_SIGNAL_TIMEOUT               31522u   /*    Tx Q signal timeout.                              */
#define  NET_TCP_ERR_TX_Q_SIGNAL_ABORT                 31523u   /*    Tx Q signal aborted.                              */
#define  NET_TCP_ERR_TX_Q_SIGNAL_FAULT                 31524u   /*    Tx Q signal fault.                                */

#define  NET_TCP_ERR_RE_TX_SEG_TH                      31550u   /* Re-tx Q seg(s) re-tx'd > th.                         */


/*$PAGE*/
/*
*********************************************************************************************************
*                                    APPLICATION LAYER ERROR CODES
*********************************************************************************************************
*/

#define  NET_APP_ERR_NONE                              40000u
#define  NET_APP_ERR_NONE_AVAIL                        40010u   /* NO app rsrc(s) avail.                                */
#define  NET_APP_ERR_NULL_PTR                          40020u   /* Ptr arg(s) passed NULL ptr(s).                       */
#define  NET_APP_ERR_INVALID_ARG                       40030u   /* Invalid app arg(s).                                  */
#define  NET_APP_ERR_INVALID_OP                        40031u   /* Invalid app op(s).                                   */
#define  NET_APP_ERR_FAULT                             40050u   /* App fatal      fault.                                */
#define  NET_APP_ERR_FAULT_TRANSITORY                  40051u   /* App transitory fault.                                */

#define  NET_APP_ERR_CONN_CLOSED                       40100u   /* App conn closed.                                     */

#define  NET_APP_ERR_DATA_BUF_OVF                      40200u   /* App data buf ovf; some data MAY have been discarded. */


/*$PAGE*/
/*
*********************************************************************************************************
*                                  NETWORK SOCKET LAYER ERROR CODES
*********************************************************************************************************
*/

#define  NET_SOCK_ERR_NONE                             41000u
#define  NET_SOCK_ERR_NONE_AVAIL                       41010u   /* NO socks avail.                                      */
#define  NET_SOCK_ERR_NOT_USED                         41011u   /* Sock NOT used.                                       */
#define  NET_SOCK_ERR_CLOSED                           41020u   /* Sock       closed.                                   */
#define  NET_SOCK_ERR_FAULT                            41021u   /* Sock fault closed.                                   */
#define  NET_SOCK_ERR_TIMEOUT                          41022u   /* Sock op(s) timeout.                                  */
#define  NET_SOCK_ERR_NULL_PTR                         41030u   /* Ptr  arg(s) passed NULL ptr(s).                      */
#define  NET_SOCK_ERR_NULL_SIZE                        41031u   /* Size arg(s) passed NULL size(s).                     */

#define  NET_SOCK_ERR_INVALID_DATA_SIZE                41040u   /* Invalid sock data size.                              */
#define  NET_SOCK_ERR_INVALID_ARG                      41041u   /* Invalid sock arg.                                    */


#define  NET_SOCK_ERR_INVALID_FAMILY                   41050u   /* Invalid sock protocol family.                        */
#define  NET_SOCK_ERR_INVALID_PROTOCOL                 41051u   /* Invalid sock protocol.                               */
#define  NET_SOCK_ERR_INVALID_TYPE                     41052u   /* Invalid sock type.                                   */
#define  NET_SOCK_ERR_INVALID_SOCK                     41053u   /* Invalid sock      id.                                */
#define  NET_SOCK_ERR_INVALID_DESC                     41054u   /* Invalid sock desc id(s).                             */
#define  NET_SOCK_ERR_INVALID_CONN                     41055u   /* Invalid sock conn/id.                                */
#define  NET_SOCK_ERR_INVALID_STATE                    41056u   /* Invalid sock state.                                  */
#define  NET_SOCK_ERR_INVALID_OP                       41057u   /* Invalid sock op.                                     */

#define  NET_SOCK_ERR_INVALID_OPT                      41060u   /* Invalid sock opt.                                    */
#define  NET_SOCK_ERR_INVALID_FLAG                     41061u   /* Invalid sock flag.                                   */
#define  NET_SOCK_ERR_INVALID_TIMEOUT                  41062u   /* Invalid sock timeout val.                            */

#define  NET_SOCK_ERR_INVALID_ADDR                     41070u   /* Invalid sock addr.                                   */
#define  NET_SOCK_ERR_INVALID_ADDR_LEN                 41071u   /* Invalid sock addr len.                               */
#define  NET_SOCK_ERR_ADDR_IN_USE                      41072u   /* Sock addr cur in use.                                */

#define  NET_SOCK_ERR_INVALID_PORT_NBR                 41080u   /* Invalid port nbr.                                    */
#define  NET_SOCK_ERR_INVALID_PORT_Q_NBR_USED          41081u   /* Invalid nbr Q entries used.                          */
#define  NET_SOCK_ERR_PORT_NBR_NONE_AVAIL              41085u   /* Port nbr(s) NOT avail.                               */
#define  NET_SOCK_ERR_PORT_NBR_IN_Q                    41086u   /* Port nbr cur in Q.                                   */

#define  NET_SOCK_ERR_INVALID_EVENT                    41090u   /* Invalid sock event.                                  */
#define  NET_SOCK_ERR_EVENTS_NBR_MAX                   41091u   /* Sock nbr events max'd.                               */


#define  NET_SOCK_ERR_CONN_IN_USE                      41100u   /* Sock conn cur in use.                                */
#define  NET_SOCK_ERR_CONN_IN_PROGRESS                 41101u   /* Sock conn        NOT complete.                       */
#define  NET_SOCK_ERR_CONN_CLOSED                      41105u   /* Sock conn closed.                                    */
#define  NET_SOCK_ERR_CONN_CLOSE_IN_PROGRESS           41106u   /* Sock conn close  NOT complete.                       */
#define  NET_SOCK_ERR_CONN_FAIL                        41110u   /* Sock conn op         failed.                         */
#define  NET_SOCK_ERR_CONN_ABORT                       41112u   /* Sock conn abort      failed.                         */
#define  NET_SOCK_ERR_CONN_SIGNAL                      41120u   /* Sock conn signal     failed.                         */
#define  NET_SOCK_ERR_CONN_SIGNAL_CLR                  41121u   /* Sock conn signal clr failed.                         */
#define  NET_SOCK_ERR_CONN_SIGNAL_TIMEOUT              41122u   /* Sock conn signal timeout.                            */
#define  NET_SOCK_ERR_CONN_SIGNAL_ABORT                41123u   /* Sock conn signal aborted.                            */
#define  NET_SOCK_ERR_CONN_SIGNAL_FAULT                41124u   /* Sock conn signal fault.                              */
#define  NET_SOCK_ERR_CONN_ACCEPT_Q_NONE_AVAIL         41130u   /* Sock conn accept Q conn id's NOT avail.              */
#define  NET_SOCK_ERR_CONN_ACCEPT_Q_MAX                41132u   /* Sock conn accept Q max  lim.                         */
#define  NET_SOCK_ERR_CONN_ACCEPT_Q_DUP                41133u   /* Sock conn accept Q conn id dup.                      */


#define  NET_SOCK_ERR_RX_Q_CLOSED                      41400u   /* Rx Q closed; i.e.   do NOT rx   pkt(s) to Q.         */
#define  NET_SOCK_ERR_RX_Q_EMPTY                       41401u   /* Rx Q empty;  i.e.      NO  rx'd pkt(s) in Q.         */
#define  NET_SOCK_ERR_RX_Q_FULL                        41402u   /* Rx Q full;   i.e. too many rx'd pkt(s) in Q.         */
#define  NET_SOCK_ERR_RX_Q_ABORT                       41405u   /* Rx Q abort      failed.                              */
#define  NET_SOCK_ERR_RX_Q_SIGNAL                      41410u   /* Rx Q signal     failed.                              */
#define  NET_SOCK_ERR_RX_Q_SIGNAL_CLR                  41411u   /* Rx Q signal clr failed.                              */
#define  NET_SOCK_ERR_RX_Q_SIGNAL_TIMEOUT              41412u   /* Rx Q signal timeout.                                 */
#define  NET_SOCK_ERR_RX_Q_SIGNAL_ABORT                41413u   /* Rx Q signal aborted.                                 */
#define  NET_SOCK_ERR_RX_Q_SIGNAL_FAULT                41414u   /* Rx Q signal fault.                                   */

#define  NET_SOCK_ERR_TX_Q_CLOSED                      41500u   /* Tx Q closed; i.e. do NOT Q pkt(s) to tx.             */

#define  NET_SOCK_ERR_LINK_DOWN                        41510u   /* Link down on IF used to reach dest.                  */


/*$PAGE*/
/*
*********************************************************************************************************
*                                NETWORK SECURITY MANAGER ERROR CODES
*********************************************************************************************************
*/

#define  NET_SECURE_MGR_ERR_NONE                       50000u
#define  NET_SECURE_MGR_ERR_INIT                       50001u   /* Failed to init security mgr.                         */
#define  NET_SECURE_MGR_ERR_NOT_AVAIL                  50010u   /* Network security mgr NOT avail.                      */
#define  NET_SECURE_MGR_ERR_NULL_PTR                   50020u   /* Ptr arg(s) passed NULL ptr(s).                       */

#define  NET_SECURE_MGR_ERR_TYPE                       50050u   /* Invalid keying material type.                        */
#define  NET_SECURE_MGR_ERR_FMT                        50051u   /* Invalid keying material fmt.                         */


/*
*********************************************************************************************************
*                                    NETWORK SECURITY ERROR CODES
*********************************************************************************************************
*/

#define  NET_SECURE_ERR_NONE                           51000u
#define  NET_SECURE_ERR_INIT_POOL                      51001u   /* Failed to init mem pool.                             */
#define  NET_SECURE_ERR_INIT_OS                        51002u   /* Failed to init OS  rsrc(s).                          */
#define  NET_SECURE_ERR_NOT_AVAIL                      51010u   /* Failed to get secure obj(s) from mem pool.           */
#define  NET_SECURE_ERR_NULL_PTR                       51020u   /* Ptr arg(s) passed NULL ptr(s).                       */

#define  NET_SECURE_ERR_BLK_GET                        51050u   /* Failed to get  blk from mem pool.                    */
#define  NET_SECURE_ERR_BLK_FREE                       51051u   /* Failed to free blk to   mem pool.                    */

#define  NET_SECURE_ERR_LOCK_CREATE                    51060u   /* Failed to create  lock.                              */
#define  NET_SECURE_ERR_LOCK_DEL                       51061u   /* Failed to del     lock.                              */
#define  NET_SECURE_ERR_LOCK                           51062u   /* Failed to acquire lock.                              */
#define  NET_SECURE_ERR_UNLOCK                         51063u   /* Failed to release lock.                              */

#define  NET_SECURE_ERR_HANDSHAKE                      51100u   /* Failed to perform secure handshake.                  */

#define  NET_SECURE_ERR_INSTALL                        51110u   /* Keying material failed to install.                   */
#define  NET_SECURE_ERR_INSTALL_NOT_TRUSTED            51111u   /* Keying material is NOT trusted.                      */
#define  NET_SECURE_ERR_INSTALL_DATE_EXPIRATION        51112u   /* Keying material is expired.                          */
#define  NET_SECURE_ERR_INSTALL_DATE_CREATION          51113u   /* Keying material creation date invalid.               */
#define  NET_SECURE_ERR_INSTALL_CA_SLOT                51114u   /* No more CA slot available.                           */


/*$PAGE*/
/*
*********************************************************************************************************
*                                             DATA TYPES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                    NETWORK ERROR CODES DATA TYPE
*********************************************************************************************************
*/

typedef  CPU_INT16U  NET_ERR;


/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/


/*$PAGE*/
/*
*********************************************************************************************************
*                                              MACRO'S
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                               NETWORK ARGUMENT CHECK FAILURE MACRO'S
*
* Description : Call application-specific handler function(s) to monitor, log, & handle network error(s).
*
* Argument(s) : id      Specific network error code ID.
*
* Return(s)   : none.
*
* Caller(s)   : various.
*
*               These macro's are INTERNAL network protocol suite macro's & SHOULD NOT be called by
*               application function(s).
*
* Note(s)     : (1) (a) When NET_ERR_CFG_ARG_CHK_EXT_EN is ENABLED, ALL arguments received from any port interface
*                       provided by the developer or application are checked/validated.
*
*                       To provide feedback to an application on any port interface argument check failures, the
*                       developer MUST implement the failure hook function, NetErr_FailArgChkExt(), in
*
*                           \<Your Product Application>\net_bsp.c
*
*                               where
*                                       <Your Product Application>    directory path for Your Product's Application
*
*
*                   (b) When NET_ERR_CFG_ARG_CHK_DBG_EN is ENABLED, internal arguments are checked/validated to
*                       debug the network protocol suite.
*
*                       To provide feedback to an application on any internal network argument check failures, the
*                       developer MUST implement the failure hook function, NetErr_FailArgChkDbg(), in
*
*                           \<Your Product Application>\net_bsp.c
*
*                               where
*                                       <Your Product Application>    directory path for Your Product's Application
*
*
*               (2) When argument check failure macro's are used in conjunction with network counter macro's
*                   (see 'net_ctr.h  NETWORK COUNTER MACRO'S'), argument check failure macro MUST be called
*                   AFTER network counter macro.  This ensures that the network counter is adjusted BEFORE
*                   the failure hook function is called (see Notes #1 & #2).
*
*               (3) Argument check identification numbers (id's) are grouped in series of 1000 per module/layer.
*
*               (4) (a) #### Argument check failure macro's     NOT yet implemented.
*
*                   (b) #### Argument check failure macro's may NOT be necessary (remove if unnecessary).
*********************************************************************************************************
*/

#if (NET_ERR_CFG_ARG_CHK_EXT_EN == DEF_ENABLED)
#define  NET_ERR_FAIL_ARG_CHK_EXT(id)            do { NetErr_FailArgChkExt((CPU_INT16U)id); } while (0)
#else
#define  NET_ERR_FAIL_ARG_CHK_EXT(id)
#endif

#if (NET_ERR_CFG_ARG_CHK_DBG_EN == DEF_ENABLED)
#define  NET_ERR_FAIL_ARG_CHK_DBG(id)            do { NetErr_FailArgChkDbg((CPU_INT16U)id); } while (0)
#else
#define  NET_ERR_FAIL_ARG_CHK_DBG(id)
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

#if (NET_DBG_CFG_TEST_EN == DEF_ENABLED)
CPU_CHAR  *NetErr_GetStr  (NET_ERR     err_code);
#endif


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*                                   DEFINED IN PRODUCT'S  net_bsp.c
*********************************************************************************************************
*/

#if (NET_ERR_CFG_ARG_CHK_EXT_EN == DEF_ENABLED)
void  NetErr_FailArgChkExt(CPU_INT16U  id);
#endif

#if (NET_ERR_CFG_ARG_CHK_DBG_EN == DEF_ENABLED)
void  NetErr_FailArgChkDbg(CPU_INT16U  id);
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                        CONFIGURATION ERRORS
*********************************************************************************************************
*/

#ifndef  NET_ERR_CFG_ARG_CHK_EXT_EN
#error  "NET_ERR_CFG_ARG_CHK_EXT_EN        not #define'd in 'net_cfg.h'"
#error  "                            [MUST be  DEF_DISABLED]           "
#error  "                            [     ||  DEF_ENABLED ]           "

#elif  ((NET_ERR_CFG_ARG_CHK_EXT_EN != DEF_DISABLED) && \
        (NET_ERR_CFG_ARG_CHK_EXT_EN != DEF_ENABLED ))
#error  "NET_ERR_CFG_ARG_CHK_EXT_EN  illegally #define'd in 'net_cfg.h'"
#error  "                            [MUST be  DEF_DISABLED]           "
#error  "                            [     ||  DEF_ENABLED ]           "
#endif



#ifndef  NET_ERR_CFG_ARG_CHK_DBG_EN
#error  "NET_ERR_CFG_ARG_CHK_DBG_EN        not #define'd in 'net_cfg.h'"
#error  "                            [MUST be  DEF_DISABLED]           "
#error  "                            [     ||  DEF_ENABLED ]           "

#elif  ((NET_ERR_CFG_ARG_CHK_DBG_EN != DEF_DISABLED) && \
        (NET_ERR_CFG_ARG_CHK_DBG_EN != DEF_ENABLED ))
#error  "NET_ERR_CFG_ARG_CHK_DBG_EN  illegally #define'd in 'net_cfg.h'"
#error  "                            [MUST be  DEF_DISABLED]           "
#error  "                            [     ||  DEF_ENABLED ]           "
#endif

