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
*                                         NETWORK HEADER FILE
*
* Filename      : net.h
* Version       : V2.11.02
* Programmer(s) : ITJ
*                 SR
*                 EHS
*                 FGK
*                 SL
*********************************************************************************************************
* Note(s)       : (1) Assumes the following versions (or more recent) of software modules are included in
*                     the project build :
*
*                     (a) uC/CPU V1.27
*                     (b) uC/LIB V1.35.00
*
*                     See also 'NETWORK INCLUDE FILES  Notes #2 & #3'.
*
*
*                 (2) (a) The following network protocols are supported/implemented :
*
*                                                                             ---- LINK LAYER PROTOCOLS -----
*                         (1) (A) ARP   Address Resolution Protocol
*                                                                             --- NETWORK LAYER PROTOCOLS ---
*                         (2) (A) IP    Internet Protocol
*                             (B) ICMP  Internet Control Message    Protocol
*                             (C) IGMP  Internet Group   Management Protocol
*                                                                             -- TRANSPORT LAYER PROTOCOLS --
*                         (3) (A) UDP   User Datagram Protocol
*                             (B) TCP   Transmission Control Protocol
*
*                     (b) The following network protocols are intentionally NOT supported/implemented :
*
*                                                                             ---- LINK LAYER PROTOCOLS -----
*                         (1) (A) RARP  Reverse Address Resolution Protocol
*
*
*                 (3) To protect the validity & prevent the corruption of shared network protocol resources,
*                     the primary tasks of the network protocol suite are prevented from running concurrently
*                     through the use of a global network lock implementing protection by mutual exclusion.
*
*                     (a) The mechanism of protected mutual exclusion is irrelevant but MUST be implemented
*                         in the following two functions :
*
*                             NetOS_Lock()                          acquire access to network protocol suite
*                             NetOS_Unlock()                        release access to network protocol suite
*
*                         implemented in
*
*                             \<Network Protocol Suite>\OS\<os>\net_os.*
*
*                             where
*                                     <Network Protocol Suite>      directory path for network protocol suite
*                                     <os>                          directory name for specific OS
*
*                     (b) Since this global lock implements mutual exclusion at the network protocol suite
*                         task level, critical sections are NOT required to prevent task-level concurrency
*                         in the network protocol suite.
*********************************************************************************************************
*/


/*$PAGE*/
/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This main network protocol suite header file is protected from multiple pre-processor
*               inclusion through use of the network module present pre-processor macro definition.
*
*               See also 'NETWORK INCLUDE FILES  Note #5'.
*********************************************************************************************************
*/

#ifndef  NET_MODULE_PRESENT                                     /* See Note #1.                                         */
#define  NET_MODULE_PRESENT


/*
*********************************************************************************************************
*                                       NETWORK VERSION NUMBER
*
* Note(s) : (1) (a) The network protocol suite software version is denoted as follows :
*
*                       Vx.yy.zz
*
*                           where
*                                   V               denotes 'Version' label
*                                   x               denotes     major software version revision number
*                                   yy              denotes     minor software version revision number
*                                   zz              denotes sub-minor software version revision number
*
*               (b) The software version label #define is formatted as follows :
*
*                       ver = x.yyzz * 100 * 100
*
*                           where
*                                   ver             denotes software version number scaled as an integer value
*                                   x.yyzz          denotes software version number, where the unscaled integer 
*                                                       portion denotes the major version number & the unscaled 
*                                                       fractional portion denotes the (concatenated) minor 
*                                                       version numbers
*********************************************************************************************************
*/

#define  NET_VERSION                                   21102u   /* See Note #1.                                         */


/*$PAGE*/
/*
*********************************************************************************************************
*                                        NETWORK INCLUDE FILES
*
* Note(s) : (1) The network protocol suite files are located in the following directories :
*
*               (a) (1) \<Your Product Application>\app_cfg.h
*                   (2)                            \net_cfg.h
*                   (3)                            \net_dev_cfg.*
*                   (4)                            \net_bsp.*
*
*               (b) \<Network Protocol Suite>\Source\net.h
*                                                   \net_*.*
*
*               (c) \<Network Protocol Suite>\Ports\<cpu>\<compiler>\net_*_a.*
*
*               (d) \<Network Protocol Suite>\OS\<os>\net_os.*
*
*               (e) (1) \<Network Protocol Suite>\IF\net_if.*
*                   (2)                             \net_if_*.*
*
*               (f) \<Network Protocol Suite>\Dev\<if>\<dev>\net_dev_*.*
*
*               (g) (1)     \<Network Protocol Suite>\Secure\net_secure_*.*
*                   (2) (A) \<Network Protocol Suite>\Secure\<secure>\net_secure.*
*                       (B)                                 \<secure>\<os>\net_secure_os.*
*
*                       where
*                               <Your Product Application>      directory path for Your Product's Application
*                               <Network Protocol Suite>        directory path for network protocol suite
*                               <cpu>                           directory name for specific processor         (CPU)
*                               <compiler>                      directory name for specific compiler
*                               <os>                            directory name for specific operating system  (OS)
*                               <if>                            directory name for specific network interface (IF)
*                               <dev>                           directory name for specific network device
*                               <secure>                        directory name for specific security layer
*
*           (2) CPU-configuration software files are located in the following directories :
*
*               (a) \<CPU-Compiler Directory>\cpu_*.*
*
*               (b) \<CPU-Compiler Directory>\<cpu>\<compiler>\cpu*.*
*
*                       where
*                               <CPU-Compiler Directory>        directory path for common CPU-compiler software
*                               <cpu>                           directory name for specific processor (CPU)
*                               <compiler>                      directory name for specific compiler
*
*           (3) NO compiler-supplied standard library functions are used by the network protocol suite.
*
*               (a) Standard library functions are implemented in the custom library module(s) :
*
*                       \<Custom Library Directory>\lib_*.*
*
*                           where
*                                   <Custom Library Directory>      directory path for custom library software
*
*               (b) Network-specific library functions are implemented in the Network Utility module,
*                   'net_util.*' (see 'net_util.h  Note #1').
*$PAGE*
*           (4) (a) Compiler MUST be configured to include as additional include path directories :
*
*                   (1) '\<Your Product Application>\' directory                                See Note #1a
*
*                   (2) '\<Network Protocol Suite>\'   directory                                See Note #1b
*
*                   (3) '\<Custom Library Directory>\' directory                                See Note #3a
*
*                   (4) Specific port directories :
*
*                       (A) (1) '\<CPU-Compiler Directory>\'                    directory       See Note #2a
*                           (2) '\<CPU-Compiler Directory>\<cpu>\<compiler>\'   directory       See Note #2b
*
*                       (B) '\<Network Protocol Suite>\Ports\<cpu>\<compiler>\' directory       See Note #1c
*
*                       (C) '\<Network Protocol Suite>\OS\<os>\'                directory       See Note #1d
*
*                       (D) '\<Network Protocol Suite>\IF\'                     directory       See Note #1e
*
*                       (E) '\<Network Protocol Suite>\Dev\<if>\<dev>\'         directory(s)    See Note #1f
*
*                       where
*                               <Your Product Application>      directory path for Your Product's Application
*                               <Network Protocol Suite>        directory path for network protocol suite
*                               <Custom Library Directory>      directory path for custom  library software
*                               <CPU-Compiler Directory>        directory path for common  CPU-compiler software
*                               <cpu>                           directory name for specific processor         (CPU)
*                               <compiler>                      directory name for specific compiler
*                               <os>                            directory name for specific operating system  (OS)
*                               <if>                            directory name for specific network interface (IF)
*                               <dev>                           directory name for specific network device
*
*               (b) Compiler MUST be configured to include as additional include path directories the 
*                   following direcories when their corresponding (optional) feature(s) are enabled :
*
*                   (1)     '\<Network Protocol Suite>\Secure\'                 directory       See Note #1g1
*                   (2) (A) '\<Network Protocol Suite>\Secure\<secure>\'        directory       See Note #1g2A
*                       (B)                                  \<secure>\<os>\'   directory       See Note #1g2B
*
*                           See 'net_cfg.h  NETWORK SECURITY MANAGER CONFIGURATION  Note #1'.
*
*                       where
*                               <Network Protocol Suite>        directory path for network protocol suite
*                               <secure>                        directory name for specific security layer
*                               <os>                            directory name for specific operating system (OS)
*
*           (5) An application MUST pre-processor include ONLY this main network protocol suite
*               header file, 'net.h'.  All other network protocol suite files are included via
*               this main network header file.
*
*               See also 'MODULE  Note #1'.
*********************************************************************************************************
*/
/*$PAGE*/
#include  <cpu.h>                                       /* CPU Configuration       (see Note #2b)                       */
#include  <cpu_core.h>                                  /* CPU Core Library        (see Note #2a)                       */

#include  <lib_def.h>                                   /* Standard        Defines (see Note #3a)                       */
#include  <lib_mem.h>                                   /* Standard Memory Library (see Note #3a)                       */
#include  <lib_math.h>                                  /* Standard Math   Library (see Note #3a)                       */



#include  <net_def.h>                                   /* Network      Defines                                         */
#include  <net_type.h>                                  /* Network Data Types                                           */

#include  <app_cfg.h>                                   /* Application  Configuration File (see Note #1a1)              */
#include  <net_cfg.h>                                   /* Network      Configuration File (see Note #1a2)              */
#include  <net_cfg_net.h>                               /* Network      Configuration (based on 'net_cfg.h' settings)   */



#include  <net_err.h>                                   /* Network Error Code Management                                */
#include  <net_ctr.h>                                   /* Network Counter    Management                                */
#include  <net_stat.h>                                  /* Network Statistics Management                                */

#include  <net_tmr.h>                                   /* Network Timer      Management                                */
#include  <net_buf.h>                                   /* Network Buffer     Management                                */
#include  <net_conn.h>                                  /* Network Connection Management                                */
#include  <net_dbg.h>                                   /* Network Debug      Management                                */

#include  <net_ascii.h>                                 /* Network ASCII   Library                                      */
#include  <net_util.h>                                  /* Network Utility Library (see Note #3b)                       */



#include  <net_os.h>                                    /* Network-OS Interface (see Note #1d)                          */


#include  <net_if.h>                                    /* Network Interface Layer Management (see Note #1e)            */

#include  <net_mgr.h>                                   /* Network      Layer Management                                */
#include  <net_ip.h>                                    /* Network IP   Layer                                           */
#include  <net_icmp.h>                                  /* Network ICMP Layer                                           */
#include  <net_igmp.h>                                  /* Network IGMP Layer                                           */

#include  <net_udp.h>                                   /* Network UDP  Layer                                           */
#include  <net_tcp.h>                                   /* Network TCP  Layer                                           */


#include  <net_bsd.h>                                   /* Network BSD              Layer                               */
#include  <net_sock.h>                                  /* Network Socket           Layer                               */



#include  <net_app.h>                                   /* Network Application Programming Interface (API) Layer        */


/*$PAGE*/
/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/

#if ((defined(NET_MODULE)) && \
     (defined(NET_GLOBALS_EXT)))
#define  NET_EXT
#else
#define  NET_EXT  extern
#endif


/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/

#define  NET_TASK_NBR_IF                                   2u
#define  NET_TASK_NBR_TMR                                  1u

#define  NET_TASK_NBR                                   (NET_TASK_NBR_IF + \
                                                         NET_TASK_NBR_TMR)


/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/

NET_EXT  CPU_BOOLEAN  Net_InitDone;                         /* Indicates when network initialization is complete.       */


/*$PAGE*/
/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

NET_ERR     Net_Init      (void);                           /* Network startup function.                                */

void        Net_InitDflt  (void);                           /* Initialize default values for configurable parameters.   */


CPU_INT16U  Net_VersionGet(void);                           /* Get network protocol suite software version.             */


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*                                      DEFINED IN OS'S  net_os.c
*********************************************************************************************************
*/

void        NetOS_Init      (NET_ERR     *perr);            /* Create network objects.                                  */


void        NetOS_InitWait  (NET_ERR     *perr);            /* Wait  until network initialization is complete.          */

void        NetOS_InitSignal(NET_ERR     *perr);            /* Signal that network initialization is complete.          */


void        NetOS_Lock      (NET_ERR     *perr);            /* Acquire access to network protocol suite.                */

void        NetOS_Unlock    (void);                         /* Release access to network protocol suite.                */


#ifdef  NET_OS_TIME_DLY_PRESENT
void        NetOS_TimeDly   (CPU_INT32U   time_dly_sec,     /* Time delay of seconds & microseconds.                    */
                             CPU_INT32U   time_dly_us,
                             NET_ERR     *perr);
#endif

void        NetOS_TimeDly_ms(CPU_INT32U   time_dly_ms,      /* Time delay of milliseconds.                              */
                             NET_ERR     *perr);


/*$PAGE*/
/*
*********************************************************************************************************
*                                    NETWORK CONFIGURATION ERRORS
*
* Note(s) : (1) See 'NETWORK INCLUDE FILES  Note #1a2'.
*********************************************************************************************************
*/

#ifndef  NET_CFG_INIT_CFG_VALS
#error  "NET_CFG_INIT_CFG_VALS          not #define'd in 'net_cfg.h'   "
#error  "                         [MUST be  NET_INIT_CFG_VALS_DFLT    ]"
#error  "                         [     ||  NET_INIT_CFG_VALS_APP_INIT]"

#elif  ((NET_CFG_INIT_CFG_VALS != NET_INIT_CFG_VALS_DFLT    ) && \
        (NET_CFG_INIT_CFG_VALS != NET_INIT_CFG_VALS_APP_INIT))
#error  "NET_CFG_INIT_CFG_VALS    illegally #define'd in 'net_cfg.h'   "
#error  "                         [MUST be  NET_INIT_CFG_VALS_DFLT    ]"
#error  "                         [     ||  NET_INIT_CFG_VALS_APP_INIT]"
#endif




#ifndef  NET_CFG_OPTIMIZE
#error  "NET_CFG_OPTIMIZE               not #define'd in 'net_cfg.h'"
#error  "                         [MUST be  NET_OPTIMIZE_SPD ]      "
#error  "                         [     ||  NET_OPTIMIZE_SIZE]      "

#elif  ((NET_CFG_OPTIMIZE != NET_OPTIMIZE_SPD ) && \
        (NET_CFG_OPTIMIZE != NET_OPTIMIZE_SIZE))
#error  "NET_CFG_OPTIMIZE         illegally #define'd in 'net_cfg.h'"
#error  "                         [MUST be  NET_OPTIMIZE_SPD ]      "
#error  "                         [     ||  NET_OPTIMIZE_SIZE]      "
#endif


#ifndef  NET_CFG_OPTIMIZE_ASM_EN
#error  "NET_CFG_OPTIMIZE_ASM_EN        not #define'd in 'net_cfg.h'"
#error  "                         [MUST be  DEF_DISABLED]           "
#error  "                         [     ||  DEF_ENABLED ]           "

#elif  ((NET_CFG_OPTIMIZE_ASM_EN != DEF_DISABLED) && \
        (NET_CFG_OPTIMIZE_ASM_EN != DEF_ENABLED ))
#error  "NET_CFG_OPTIMIZE_ASM_EN  illegally #define'd in 'net_cfg.h'"
#error  "                         [MUST be  DEF_DISABLED]           "
#error  "                         [     ||  DEF_ENABLED ]           "
#endif




#ifndef  NET_CFG_BUILD_LIB_EN
#error  "NET_CFG_BUILD_LIB_EN           not #define'd in 'net_cfg.h'"
#error  "                         [MUST be  DEF_DISABLED]           "
#error  "                         [     ||  DEF_ENABLED ]           "

#elif  ((NET_CFG_BUILD_LIB_EN != DEF_DISABLED) && \
        (NET_CFG_BUILD_LIB_EN != DEF_ENABLED ))
#error  "NET_CFG_BUILD_LIB_EN     illegally #define'd in 'net_cfg.h'"
#error  "                         [MUST be  DEF_DISABLED]           "
#error  "                         [     ||  DEF_ENABLED ]           "
#endif


/*
*********************************************************************************************************
*                                    LIBRARY CONFIGURATION ERRORS
*********************************************************************************************************
*/

                                                                /* See 'net.h  Note #1a'.                               */
#if     (CPU_CORE_VERSION < 127u)
#error  "CPU_CORE_VERSION      [SHOULD be >= V1.27]"
#endif


                                                                /* See 'net.h  Note #1b'.                               */
#if     (LIB_VERSION < 13500u)
#error  "LIB_VERSION           [SHOULD be >= V1.35.00]"
#endif


#if     (LIB_MEM_CFG_ALLOC_EN != DEF_ENABLED)
#error  "LIB_MEM_CFG_ALLOC_EN  illegally #define'd in 'app_cfg.h'"
#error  "                      [MUST be  DEF_ENABLED]            "
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                             MODULE END
*
* Note(s) : (1) See 'net.h  MODULE'.
*********************************************************************************************************
*/

#endif                                                          /* End of net module include.                           */

