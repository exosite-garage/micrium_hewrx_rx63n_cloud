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
*                                       NETWORK INTERFACE LAYER
*
*                                              ETHERNET
*
* Filename      : net_if_ether.h
* Version       : V2.11.02
* Programmer(s) : ITJ
*                 EHS
*                 SR
*********************************************************************************************************
* Note(s)       : (1) Supports Ethernet as described in RFC #894; supports IEEE 802 as described in RFC #1042.
*
*                 (2) Ethernet implementation conforms to RFC #1122, Section 2.3.3, bullets (a) & (b), but
*                     does NOT implement bullet (c) :
*
*                     RFC #1122                  LINK LAYER                  October 1989
*
*                     2.3.3  ETHERNET (RFC-894) and IEEE 802 (RFC-1042) ENCAPSULATION
*
*                            Every Internet host connected to a 10Mbps Ethernet cable :
*
*                            (a) MUST be able to send and receive packets using RFC-894 encapsulation;
*
*                            (b) SHOULD be able to receive RFC-1042 packets, intermixed with RFC-894 packets; and
*
*                            (c) MAY be able to send packets using RFC-1042 encapsulation.
*
*                 (3) REQUIREs the following network protocol files in network directories :
*
*                     (a) Network Interface Layer           located in the following network directory :
*
*                             \<Network Protocol Suite>\IF\
*
*                     (b) Address Resolution Protocol Layer located in the following network directory :
*
*                             \<Network Protocol Suite>\
*
*                         See also 'net_arp.h  Note #1'.
*
*                              where
*                                      <Network Protocol Suite>    directory path for network protocol suite
*********************************************************************************************************
*/


/*$PAGE*/
/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) Ethernet Interface module is included only if Ethernet devices are configured (see
*               'net_cfg_net.h  NETWORK INTERFACE LAYER CONFIGURATION  Note #2a2').
*
*           (2) The following Ethernet-module-present configuration value MUST be pre-#define'd in
*               'net_cfg_net.h' PRIOR to all other network modules that require Ethernet configuration
*               (see 'net_cfg_net.h  NETWORK INTERFACE LAYER CONFIGURATION  Note #2a2') :
*
*                   NET_IF_MODULE_ETHER_PRESENT
*********************************************************************************************************
*/

#ifdef  NET_IF_MODULE_ETHER_PRESENT                             /* See Note #2.                                         */


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include  <net_arp.h>                                           /* See 'net_if_ether.h  Note #3b'.                      */


/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/

#if ((defined(NET_IF_MODULE_ETHER)) && \
     (defined(NET_GLOBALS_EXT)))
#define  NET_IF_ETHER_EXT
#else
#define  NET_IF_ETHER_EXT  extern
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                NETWORK INTERFACE / ETHERNET DEFINES
*
* Note(s) : (1) Ethernet address #define's should NOT be used since they will most likely be truncated to 
*               32 bits but are shown for completeness.
*********************************************************************************************************
*/

#define  NET_IF_ETHER_ADDR_SIZE                                    6    /* Size of 48-bit Ether MAC addr (in octets).   */
#define  NET_IF_ETHER_ADDR_SIZE_STR                              NET_ASCII_LEN_MAX_ADDR_MAC

                                                                        /* See Note #1.                                 */
#define  NET_IF_ETHER_ADDR_NULL                       0x000000000000u
#define  NET_IF_ETHER_ADDR_BROADCAST                  0xFFFFFFFFFFFFu

#define  NET_IF_ETHER_ADDR_MULTICAST_MASK             0x010000000000u
#define  NET_IF_ETHER_ADDR_MULTICAST_IPv4_MASK        0x01005E000000u


/*
*********************************************************************************************************
*                           NETWORK INTERFACE LAYER / ETHERNET ERROR CODES
*
* Note(s) : (1) (a) ALL IF-independent    error codes #define'd in 'net_err.h';
*               (b) ALL Ethernet-specific error codes #define'd in 'net_if_ether.h'.
*
*           (2) Network error code '11,000' series reserved for network interfaces.
*********************************************************************************************************
*/

#define  NET_IF_ERR_INVALID_PROTOCOL                           11410u   /* Invalid protocol.                            */
#define  NET_IF_ERR_INVALID_ETHER_TYPE                         11411u   /* Invalid Ethernet type.                       */
#define  NET_IF_ERR_INVALID_LLC_DSAP                           11420u   /* Invalid IEEE 802.2 LLC  DSAP val.            */
#define  NET_IF_ERR_INVALID_LLC_SSAP                           11421u   /* Invalid IEEE 802.2 LLC  SSAP val.            */
#define  NET_IF_ERR_INVALID_LLC_CTRL                           11422u   /* Invalid IEEE 802.2 LLC  Ctrl val.            */
#define  NET_IF_ERR_INVALID_SNAP_CODE                          11430u   /* Invalid IEEE 802.2 SNAP OUI  val.            */
#define  NET_IF_ERR_INVALID_SNAP_TYPE                          11431u   /* Invalid IEEE 802.2 SNAP Type val.            */


/*$PAGE*/
/*
*********************************************************************************************************
*                                  NETWORK INTERFACE HEADER DEFINES
*
* Note(s) : (1) NET_IF_HDR_SIZE_ETHER_MAX's ideal #define'tion :
*
*                   (A) max( Ether Hdr, IEEE 802 Hdr )
*
*               (a) However, since NET_IF_HDR_SIZE_ETHER_MAX is used ONLY for network transmit & IEEE 802 
*                   is NEVER transmitted (see 'net_if_ether.h  Note #2'), NET_IF_HDR_SIZE_ETHER_MAX  MUST 
*                   be #define'd with hard-coded knowledge that Ethernet is the only supported frame 
*                   encapsulation for network transmit.
*
*           (2) The following network interface value MUST be pre-#define'd in 'net_def.h' PRIOR to
*               'net_cfg.h' so that the developer can configure the network interface for the correct
*               network interface link layer values (see 'net_def.h  NETWORK INTERFACE LAYER DEFINES'
*               & 'net_cfg_net.h  NETWORK INTERFACE LAYER CONFIGURATION  Note #4') :
*
*               (a) NET_IF_HDR_SIZE_ETHER                 14
*
*          !!!! Redesign for dynamically-configured network interface types?
*********************************************************************************************************
*/

#define  NET_IF_HDR_SIZE_BASE_ETHER                       14    /* Ethernet base hdr size.                              */
#define  NET_IF_HDR_SIZE_BASE_IEEE_802                     8    /* IEEE 802 base hdr size.                              */

#if 0                                                           /* See Note #2a.                                        */
#define  NET_IF_HDR_SIZE_ETHER                           NET_IF_HDR_SIZE_BASE_ETHER
#endif
#define  NET_IF_HDR_SIZE_IEEE_802                       (NET_IF_HDR_SIZE_BASE_ETHER + NET_IF_HDR_SIZE_BASE_IEEE_802)

#define  NET_IF_HDR_SIZE_ETHER_MIN              (DEF_MIN(NET_IF_HDR_SIZE_ETHER, NET_IF_HDR_SIZE_IEEE_802))
#define  NET_IF_HDR_SIZE_ETHER_MAX                       NET_IF_HDR_SIZE_ETHER


#define  NET_IF_HDR_SIZE_ADDR                            NET_IF_ETHER_ADDR_SIZE


/*
*********************************************************************************************************
*                       ETHERNET SIZE & MAXIMUM TRANSMISSION UNIT (MTU) DEFINES
*
* Note(s) : (1) (a) RFC #894, Section 'Frame Format' & RFC #1042, Section 'Frame Format and MAC Level Issues :
*                   For IEEE 802.3' specify the following range on Ethernet & IEEE 802 frame sizes :
*
*                   (1) Minimum frame size =   64 octets
*                   (2) Maximum frame size = 1518 octets
*
*               (b) Since the 4-octet CRC trailer included in the specified minimum & maximum frame sizes is 
*                   NOT necessarily included or handled by the network protocol suite, the minimum & maximum 
*                   frame sizes for receive & transmit packets is adjusted by the CRC size.
*********************************************************************************************************
*/

#define  NET_IF_ETHER_FRAME_CRC_SIZE                       4

#define  NET_IF_ETHER_FRAME_MIN_CRC_SIZE                  64    /* See Note #1a1.                                       */
#define  NET_IF_ETHER_FRAME_MIN_SIZE                    (NET_IF_ETHER_FRAME_MIN_CRC_SIZE - NET_IF_ETHER_FRAME_CRC_SIZE)

#define  NET_IF_ETHER_FRAME_MAX_CRC_SIZE                1518    /* See Note #1a2.                                       */
#define  NET_IF_ETHER_FRAME_MAX_SIZE                    (NET_IF_ETHER_FRAME_MAX_CRC_SIZE - NET_IF_ETHER_FRAME_CRC_SIZE)


#define  NET_IF_MTU_ETHER                               (NET_IF_ETHER_FRAME_MAX_CRC_SIZE - NET_IF_ETHER_FRAME_CRC_SIZE - NET_IF_HDR_SIZE_ETHER)
#define  NET_IF_MTU_IEEE_802                            (NET_IF_ETHER_FRAME_MAX_CRC_SIZE - NET_IF_ETHER_FRAME_CRC_SIZE - NET_IF_HDR_SIZE_IEEE_802)


#define  NET_IF_ETHER_BUF_SIZE_MIN                      (NET_IF_ETHER_FRAME_MIN_SIZE     + NET_BUF_DATA_SIZE_MIN       - NET_BUF_DATA_PROTOCOL_HDR_SIZE_MIN)


/*$PAGE*/
/*
*********************************************************************************************************
*                                          ETHERNET DEFINES
*********************************************************************************************************
*/

                                                                /* ---------------- ETHER FRAME TYPES ----------------- */
#define  NET_IF_ETHER_FRAME_TYPE_IP                   0x0800u
#define  NET_IF_ETHER_FRAME_TYPE_ARP                  0x0806u
#define  NET_IF_ETHER_FRAME_TYPE_RARP                 0x8035u   /* See 'net_def.h  NETWORK PROTOCOL TYPES  Note #1'.    */


/*
*********************************************************************************************************
*                                          IEEE 802 DEFINES
*
* Note(s) : (1) SNAP 'Organizational Unique Identifier' (OUI) abbreviated to 'SNAP' for some SNAP OUI
*               codes to enforce ANSI-compliance of 31-character symbol length uniqueness.
*
*           (2) Default SNAP 'Organizational Unique Identifier' (OUI) IEEE 802.2 frame type is ALWAYS
*               Ethernet frame type (see 'IEEE 802 HEADER / FRAME  Note #1').
*********************************************************************************************************
*/

#define  NET_IF_IEEE_802_FRAME_LEN_MAX                  (NET_IF_MTU_IEEE_802 + NET_IF_HDR_SIZE_BASE_IEEE_802)

                                                                /* ------- IEEE 802.2 LOGICAL LINK CONTROL (LLC) ------ */
#define  NET_IF_IEEE_802_LLC_DSAP                       0xAAu
#define  NET_IF_IEEE_802_LLC_SSAP                       0xAAu
#define  NET_IF_IEEE_802_LLC_CTRL                       0x03u

                                                                /* --- IEEE 802.2 SUB-NETWORK ACCESS PROTOCOL (SNAP) -- */
#define  NET_IF_IEEE_802_SNAP_CODE_SIZE                    3u   /*  3-octet SNAP org code         (see Note #1).        */
#define  NET_IF_IEEE_802_SNAP_CODE_ETHER            0x000000u   /*    Dflt  SNAP org code (Ether) [see Note #2].        */
#define  NET_IF_IEEE_802_SNAP_CODE_00                   0x00u   /*    Dflt  SNAP org code, octet #00.                   */
#define  NET_IF_IEEE_802_SNAP_CODE_01                   0x00u   /*    Dflt  SNAP org code, octet #01.                   */
#define  NET_IF_IEEE_802_SNAP_CODE_02                   0x00u   /*    Dflt  SNAP org code, octet #02.                   */

#define  NET_IF_IEEE_802_SNAP_TYPE_IP                    NET_IF_ETHER_FRAME_TYPE_IP
#define  NET_IF_IEEE_802_SNAP_TYPE_ARP                   NET_IF_ETHER_FRAME_TYPE_ARP


/*
*********************************************************************************************************
*                                   ETHERNET PHYSICAL LAYER DEFINES
*********************************************************************************************************
*/

#define  NET_PHY_SPD_0                                     0u   /* Link speed unknown, or link down.                    */
#define  NET_PHY_SPD_10                                   10u   /* Link speed = 10mbps.                                 */
#define  NET_PHY_SPD_100                                 100u   /* Link speed = 100mbps.                                */
#define  NET_PHY_SPD_1000                               1000u   /* Link speed = 1000mbps.                               */
#define  NET_PHY_SPD_AUTO                             0xFFFFu   /* Initial link spd determined by auto-negotiation.     */


#define  NET_PHY_DUPLEX_UNKNOWN                            0u   /* Duplex uknown or auto-neg incomplete.                */
#define  NET_PHY_DUPLEX_HALF                               1u   /* Duplex = Half Duplex.                                */
#define  NET_PHY_DUPLEX_FULL                               2u   /* Duplex = Full Duplex.                                */
#define  NET_PHY_DUPLEX_AUTO                               3u   /* Initial duplex   determined by auto-negotiation.     */

#define  NET_PHY_BUS_MODE_MII                              0u   /* Phy attached to MAC via  MII bus.                    */
#define  NET_PHY_BUS_MODE_RMII                             1u   /* Phy attached to MAC via RMII bus.                    */
#define  NET_PHY_BUS_MODE_SMII                             2u   /* Phy attached to MAC via SMII bus.                    */

#define  NET_PHY_TYPE_INT                                  0u   /* Internal Phy attached to MAC.                        */
#define  NET_PHY_TYPE_EXT                                  1u   /* External Phy attached to MAC.                        */

#define  NET_PHY_ADDR_AUTO                              0xFFu   /* Detect   Phy addr automatically.                     */


/*$PAGE*/
/*
*********************************************************************************************************
*                                     ETHERNET DEVICE DATA TYPES
*
* Note(s) : (1) The Ethernet interface configuration data type is a specific definition of a network 
*               device configuration data type.  Each specific network device configuration data type 
*               MUST define ALL generic network device configuration parameters, synchronized in both 
*               the sequential order & data type of each parameter.
*
*               Thus, ANY modification to the sequential order or data types of generic configuration 
*               parameters MUST be appropriately synchronized between the generic network device 
*               configuration data type & the Ethernet interface configuration data type.
*
*               See also 'net_if.h  GENERIC NETWORK DEVICE CONFIGURATION DATA TYPE  Note #1'.
*********************************************************************************************************
*/

                                                    /* ---------------------- NET ETHER DEV CFG ----------------------- */
typedef  struct  net_dev_cfg_ether {
                                                    /* ----------------- GENERIC  NET DEV CFG MEMBERS ----------------- */
    NET_TYPE            RxBufPoolType;              /* Rx buf mem pool type :                                           */
                                                    /*   NET_IF_MEM_TYPE_MAIN        bufs alloc'd from main      mem    */
                                                    /*   NET_IF_MEM_TYPE_DEDICATED   bufs alloc'd from dedicated mem    */
    NET_BUF_SIZE        RxBufLargeSize;             /* Size  of dev rx large buf data areas (in octets).                */
    NET_BUF_QTY         RxBufLargeNbr;              /* Nbr   of dev rx large buf data areas.                            */
    NET_BUF_SIZE        RxBufAlignOctets;           /* Align of dev rx       buf data areas (in octets).                */
    NET_BUF_SIZE        RxBufIxOffset;              /* Offset from base ix to rx data into data area (in octets).       */


    NET_TYPE            TxBufPoolType;              /* Tx buf mem pool type :                                           */
                                                    /*   NET_IF_MEM_TYPE_MAIN        bufs alloc'd from main      mem    */
                                                    /*   NET_IF_MEM_TYPE_DEDICATED   bufs alloc'd from dedicated mem    */
    NET_BUF_SIZE        TxBufLargeSize;             /* Size  of dev tx large buf data areas (in octets).                */
    NET_BUF_QTY         TxBufLargeNbr;              /* Nbr   of dev tx large buf data areas.                            */
    NET_BUF_SIZE        TxBufSmallSize;             /* Size  of dev tx small buf data areas (in octets).                */
    NET_BUF_QTY         TxBufSmallNbr;              /* Nbr   of dev tx small buf data areas.                            */
    NET_BUF_SIZE        TxBufAlignOctets;           /* Align of dev tx       buf data areas (in octets).                */
    NET_BUF_SIZE        TxBufIxOffset;              /* Offset from base ix to tx data from data area (in octets).       */


    CPU_ADDR            MemAddr;                    /* Base addr of (Ether dev's) dedicated mem, if avail.              */
    CPU_ADDR            MemSize;                    /* Size      of (Ether dev's) dedicated mem, if avail.              */


    NET_DEV_CFG_FLAGS   Flags;                      /* Opt'l bit flags.                                                 */

                                                    /* ----------------- SPECIFIC NET DEV CFG MEMBERS ----------------- */
    NET_BUF_QTY         RxDescNbr;                  /* Nbr rx dev desc's.                                               */
    NET_BUF_QTY         TxDescNbr;                  /* Nbr tx dev desc's.                                               */


    CPU_ADDR            BaseAddr;                   /* Base addr of Ether dev hw/regs.                                  */

    CPU_DATA            DataBusSizeNbrBits;         /* Size      of Ether dev's data bus (in bits), if avail.           */

    CPU_CHAR            HW_AddrStr[NET_IF_ETHER_ADDR_SIZE_STR]; /*  Ether IF's dev hw addr str.                         */

} NET_DEV_CFG_ETHER;


                                                    /* ---------------------- NET ETHER PHY CFG ----------------------- */
typedef  struct  net_phy_cfg_ether {
    CPU_INT08U      BusAddr;                        /* Phy bus  addr.                                                   */
    CPU_INT08U      BusMode;                        /* Phy bus  mode.                                                   */
    CPU_INT08U      Type;                           /* Phy      type.                                                   */
    CPU_INT16U      Spd;                            /* Phy link spd.                                                    */
    CPU_INT08U      Duplex;                         /* Phy link duplex.                                                 */
} NET_PHY_CFG_ETHER;


                                                    /* ---------------------- NET ETHER IF DATA ----------------------- */
typedef  struct  net_if_data_ether {
    CPU_INT08U      HW_Addr[NET_IF_ETHER_ADDR_SIZE];/*              Ether IF's dev hw addr.                             */
    CPU_INT08U      Phy_Addr;                       /* Base addr of Ether IF's Phy hw addr.                             */
} NET_IF_DATA_ETHER;


                                                    /* ------------------- NET ETHER DEV LINK STATE ------------------- */
typedef  struct net_dev_link_state_ether {
    CPU_INT16U      Spd;                            /* Link spd.                                                        */
    CPU_INT08U      Duplex;                         /* Link duplex.                                                     */
} NET_DEV_LINK_ETHER;


/*$PAGE*/
/*
*********************************************************************************************************
*                                   ETHERNET DEVICE API DATA TYPES
*
* Note(s) : (1) (a) The Ethernet device application programming interface (API) data type is a specific 
*                   network device API data type definition which MUST define ALL generic network device 
*                   API functions, synchronized in both the sequential order of the functions & argument 
*                   lists for each function.
*
*                   Thus, ANY modification to the sequential order or argument lists of the generic API 
*                   functions MUST be appropriately synchronized between the generic network device API 
*                   data type & the Ethernet device API data type definition/instantiations.
*
*                   However, specific Ethernet device API data type definitions/instantiations MAY include 
*                   additional API functions after all generic Ethernet device API functions.
*
*               (b) ALL API functions MUST be defined with NO NULL functions for all specific Ethernet 
*                   device API instantiations.  Any specific Ethernet device API instantiation that does 
*                   NOT require a specific API's functionality MUST define an empty API function which 
*                   may need to return an appropriate error code.
*
*               See also 'net_if.h  GENERIC NETWORK DEVICE API DATA TYPE  Note #1'.
*********************************************************************************************************
*/

                                                                        /* ------------ NET ETHER DEV API ------------- */
                                                                        /* Net Ether dev API fnct ptrs :                */
typedef  struct  net_dev_api_ether {
                                                                        /* ------- GENERIC  NET DEV API MEMBERS ------- */
                                                                        /*   Init/add                                   */
    void  (*Init)               (NET_IF              *pif,
                                 NET_ERR             *perr);
                                                                        /*   Start                                      */
    void  (*Start)              (NET_IF              *pif,
                                 NET_ERR             *perr);
                                                                        /*   Stop                                       */
    void  (*Stop)               (NET_IF              *pif,
                                 NET_ERR             *perr);

                                                                        /*   Rx                                         */
    void  (*Rx)                 (NET_IF              *pif,
                                 CPU_INT08U         **p_data,
                                 CPU_INT16U          *size,
                                 NET_ERR             *perr);
                                                                        /*   Tx                                         */
    void  (*Tx)                 (NET_IF              *pif,
                                 CPU_INT08U          *p_data,
                                 CPU_INT16U           size,
                                 NET_ERR             *perr);

                                                                        /* ------- SPECIFIC NET DEV API MEMBERS ------- */
                                                                        /*   Multicast addr add                         */
    void  (*AddrMulticastAdd)   (NET_IF              *pif,
                                 CPU_INT08U          *paddr_hw,
                                 CPU_INT08U           addr_hw_len,
                                 NET_ERR             *perr);
                                                                        /*   Multicast addr remove                      */
    void  (*AddrMulticastRemove)(NET_IF              *pif,
                                 CPU_INT08U          *paddr_hw,
                                 CPU_INT08U           addr_hw_len,
                                 NET_ERR             *perr);

                                                                        /*   ISR handler                                */
    void  (*ISR_Handler)        (NET_IF              *pif,
                                 NET_DEV_ISR_TYPE     type);

                                                                        /*   I/O ctrl                                   */
    void  (*IO_Ctrl)            (NET_IF              *pif,
                                 CPU_INT08U           opt,
                                 void                *p_data,
                                 NET_ERR             *perr);

                                                                        /*   Phy reg rd                                 */
    void  (*Phy_RegRd)          (NET_IF              *pif,
                                 CPU_INT08U           phy_addr,
                                 CPU_INT08U           reg_addr,
                                 CPU_INT16U          *p_data,
                                 NET_ERR             *perr);
                                                                        /*   Phy reg wr                                 */
    void  (*Phy_RegWr)          (NET_IF              *pif,
                                 CPU_INT08U           phy_addr,
                                 CPU_INT08U           reg_addr,
                                 CPU_INT16U           reg_data,
                                 NET_ERR             *perr);
} NET_DEV_API_ETHER;


/*$PAGE*/
                                                                        /* ------------ NET ETHER PHY API ------------- */
                                                                        /* Net Ether phy API fnct ptrs :                */
typedef  struct  net_phy_api_ether {
                                                                        /*   Init                                       */
    void  (*Init)               (NET_IF              *pif,
                                 NET_ERR             *perr);
                                                                        /*   En/dis                                     */
    void  (*EnDis)              (NET_IF              *pif,
                                 CPU_BOOLEAN          en,
                                 NET_ERR             *perr);

                                                                        /*   Link state get                             */
    void  (*LinkStateGet)       (NET_IF              *pif,
                                 NET_DEV_LINK_ETHER  *plink_state,
                                 NET_ERR             *perr);
                                                                        /*   Link state set                             */
    void  (*LinkStateSet)       (NET_IF              *pif,                 
                                 NET_DEV_LINK_ETHER  *plink_state,  
                                 NET_ERR             *perr);

                                                                        /*   ISR                                        */
    void  (*ISR_Handler)        (NET_IF              *pif);
} NET_PHY_API_ETHER;


/*$PAGE*/
/*
*********************************************************************************************************
*                              ETHERNET DEVICE BSP INTERFACE DATA TYPE
*
* Note(s) : (1) The generic Ethernet device board-support package (BSP) interface data type is a template/
*               subset for all specific Ethernet device BSP interface data types.
*
*               (a) Each specific Ethernet device BSP interface data type definition SHOULD define ALL 
*                   generic Ethernet device BSP functions, synchronized in both the sequential order of 
*                   the functions & argument lists for each function.
*
*                   Thus, ANY modification to the sequential order or argument lists of the generic BSP 
*                   functions SHOULD be appropriately synchronized between the generic Ethernet device 
*                   BSP interface data type & ALL specific Ethernet device BSP interface data type 
*                   definitions/instantiations.
*
*                   However, specific Ethernet device BSP interface data type definitions/instantiations 
*                   MAY include additional BSP functions after all generic Ethernet device BSP functions.
*
*               (b) (1) A specific Ethernet device BSP interface instantiation MAY define NULL functions 
*                       for any (or all) generic BSP functions provided that the specific Ethernet device 
*                       driver does NOT require those specific generic BSP function(s).
*
*                   (2) However, a specific Ethernet device driver that includes additional BSP functions 
*                       into its specific BSP interface data type definition SHOULD NOT then define any 
*                       NULL functions for these additional functions.
*********************************************************************************************************
*/

                                                                        /* ------------ NET ETHER DEV BSP ------------- */
                                                                        /* Net Ether dev BSP fnct ptrs :                */
typedef  struct  net_dev_bsp_ether {
    void        (*CfgClk)    (NET_IF   *pif,                            /* Cfg dev clk(s).                              */
                              NET_ERR  *perr);

    void        (*CfgIntCtrl)(NET_IF   *pif,                            /* Cfg dev int ctrl(s).                         */
                              NET_ERR  *perr);

    void        (*CfgGPIO)   (NET_IF   *pif,                            /* Cfg dev GPIO.                                */
                              NET_ERR  *perr);


    CPU_INT32U  (*ClkFreqGet)(NET_IF   *pif,                            /* Get dev clk freq.                            */
                              NET_ERR  *perr);
} NET_DEV_BSP_ETHER;


/*$PAGE*/
/*
*********************************************************************************************************
*                             NETWORK INTERFACE HEADER / FRAME DATA TYPES
*********************************************************************************************************
*/

                                                                /* -------------------- NET IF HDR -------------------- */
typedef  struct  net_if_hdr {
    CPU_INT08U          AddrDest[NET_IF_HDR_SIZE_ADDR];         /*       Ethernet dest  addr.                           */
    CPU_INT08U          AddrSrc[NET_IF_HDR_SIZE_ADDR];          /*       Ethernet src   addr.                           */
    CPU_INT16U          FrameType_Len;                          /* Demux Ethernet frame type vs. IEEE 802.3 frame len.  */
} NET_IF_HDR;


/*
*********************************************************************************************************
*                                 ETHERNET HEADER / FRAME DATA TYPES
*
* Note(s) : (1) Frame 'Data' buffer CANNOT be declared to force word-alignment.  'Data' buffer MUST immediately
*               follow frame 'Hdr' since Ethernet frames are contiguous, non-aligned data packets.
*
*           (2) 'Data' declared with 1 entry; prevents removal by compiler optimization.
*
*           (3) Frame CRC's are computed/validated by an Ethernet device.  NO software CRC is handled for
*               receive or transmit.
*********************************************************************************************************
*/

                                                                /* ----------------- NET IF ETHER HDR ----------------- */
typedef  struct  net_if_hdr_ether {
    CPU_INT08U          AddrDest[NET_IF_HDR_SIZE_ADDR];         /* Ethernet dest  addr.                                 */
    CPU_INT08U          AddrSrc[NET_IF_HDR_SIZE_ADDR];          /* Ethernet src   addr.                                 */
    CPU_INT16U          FrameType;                              /* Ethernet frame type.                                 */
} NET_IF_HDR_ETHER;


                                                                /* ---------------- NET IF ETHER FRAME ---------------- */
typedef  struct  net_if_frame_ether {
    NET_IF_HDR_ETHER    Hdr;
    CPU_INT08U          Data[1];                                /* See Note #2.                                         */
} NET_IF_FRAME_ETHER;


/*$PAGE*/
/*
*********************************************************************************************************
*                                 IEEE 802 HEADER / FRAME DATA TYPES
*
* Note(s) : (1) Header 'SNAP_OrgCode' defines the SNAP 'Organizational Unique Identifier' (OUI).  The OUI
*               indicates the various organization/vendor/manufacturer with each organization then defining
*               their respective frame types.
*
*               However, the default SNAP OUI indicates Ethernet frame types & is ALWAYS used.  ALL other
*               OUI's are discarded as invalid.
*
*               See also 'IEEE 802 DEFINES  Notes #1 & #2'.
*
*           (2) Frame 'Data' buffer CANNOT be declared to force word-alignment.  'Data' buffer MUST immediately
*               follow frame 'Hdr' since Ethernet frames are contiguous, non-aligned data packets.
*
*           (3) 'Data' declared with 1 entry; prevents removal by compiler optimization.
*
*           (4) Frame CRC's are computed/validated by an Ethernet device.  NO software CRC is handled for
*               receive or transmit.
*********************************************************************************************************
*/

                                                                /* --------------- NET IF IEEE 802 HDR ---------------- */
typedef  struct  net_if_hdr_ieee_802 {
    CPU_INT08U              AddrDest[NET_IF_HDR_SIZE_ADDR];     /* IEEE 802.3 dest  addr.                               */
    CPU_INT08U              AddrSrc[NET_IF_HDR_SIZE_ADDR];      /* IEEE 802.3 src   addr.                               */
    CPU_INT16U              FrameLen;                           /* IEEE 802.3 frame len.                                */

                                                                /* ------ IEEE 802.2 LOGICAL LINK CONTROL (LLC) ------- */
    CPU_INT08U              LLC_DSAP;                           /* Dest Serv Access Pt.                                 */
    CPU_INT08U              LLC_SSAP;                           /* Src  Serv Access Pt.                                 */
    CPU_INT08U              LLC_Ctrl;                           /* Ctrl Field.                                          */

                                                                /* -- IEEE 802.2 SUB-NETWORK ACCESS PROTOCOL (SNAP) --- */
    CPU_INT08U              SNAP_OrgCode[NET_IF_IEEE_802_SNAP_CODE_SIZE];       /* Org code (see Note #1).              */
    CPU_INT16U              SNAP_FrameType;                                     /* IEEE 802.2 frame type.               */
} NET_IF_HDR_IEEE_802;


                                                                /* -------------- NET IF IEEE 802 FRAME --------------- */
typedef  struct  net_if_frame_ieee_802 {
    NET_IF_HDR_IEEE_802     Hdr;
    CPU_INT08U              Data[1];                            /* See Note #3.                                         */
} NET_IF_FRAME_IEEE_802;


/*$PAGE*/
/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/

extern  const  NET_IF_API  NetIF_API_Ether;                     /* Ether IF API fnct ptr(s).                            */


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void  NetIF_Ether_Init(NET_ERR  *perr);


/*$PAGE*/
/*
*********************************************************************************************************
*                                        CONFIGURATION ERRORS
*********************************************************************************************************
*/

#ifndef  NET_IF_CFG_ETHER_EN
#error  "NET_IF_CFG_ETHER_EN        not #define'd in 'net_cfg.h'"
#error  "                     [MUST be  DEF_DISABLED]           "
#error  "                     [     ||  DEF_ENABLED ]           "

#elif  ((NET_IF_CFG_ETHER_EN != DEF_DISABLED) && \
        (NET_IF_CFG_ETHER_EN != DEF_ENABLED ))
#error  "NET_IF_CFG_ETHER_EN  illegally #define'd in 'net_cfg.h'"
#error  "                     [MUST be  DEF_DISABLED]           "
#error  "                     [     ||  DEF_ENABLED ]           "
#endif


/*
*********************************************************************************************************
*                                             MODULE END
*
* Note(s) : (1) See 'net_if_ether.h  MODULE'.
*********************************************************************************************************
*/

#endif                                                          /* End of Ether IF module include (see Note #1).        */

