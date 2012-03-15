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
*                                        NETWORK DEVICE DRIVER
*
*                                            Renesas RX63N
*
* Filename      : net_dev_sh_ether_reg.h
* Version       : V2.11.02.00
* Programmer(s) : HMS
*********************************************************************************************************
* Note(s)       : (1) Assumes uC/TCP-IP V2.02 (or more recent version) is included in the project build.
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include  <cpu.h>


/*
*********************************************************************************************************
*                                        DESCRIPTOR DEFINITION
*********************************************************************************************************
*/

typedef  struct  dev_desc  DEV_DESC;

struct dev_desc
{
     CPU_REG32   status;                            /* DMA status register.                                 */
#if CPU_CFG_ENDIAN_TYPE == CPU_ENDIAN_TYPE_LITTLE
     CPU_REG16   size;                              /* DMA size                                             */
     CPU_REG16   bufsize;                           /* DMA buffer size.                                     */
#else
     CPU_REG16   bufsize;                           /* DMA buffer size.                                     */
     CPU_REG16   size;                              /* DMA size                                             */
#endif
    CPU_INT08U  *p_buf;                             /* DMA buffer pointer                                   */
    DEV_DESC    *next;                              /* DMA next descriptor pointer.                         */
};


/*
*********************************************************************************************************
*                                        REGISTER DEFINITIONS
*
* Note(s) : (1) The device register definition structure MUST take into account appropriate
*               register offsets and apply reserved space as required.  The registers listed
*               within the register definition structure MUST reflect the exact ordering and
*               data sizes illustrated in the device user guide. An example device register
*               structure is provided below.
*
*           (2) The device register definition structure is mapped over the corresponding base
*               address provided within the device configuration structure.  The device
*               configuration structure is provided by the application developer within
*               net_dev_cfg.c.  Refer to the Network Protocol Suite User Manual for more
*               information related to declaring device configuration structures.
*********************************************************************************************************
*/

typedef  struct  net_dev {
    CPU_REG32  EDMAC_EDMR;
    CPU_REG32  RESERVED0[0x01];
    CPU_REG32  EDMAC_EDTRR;
    CPU_REG32  RESERVED1[0x01];
    CPU_REG32  EDMAC_EDRRR;
    CPU_REG32  RESERVED2[0x01];
    CPU_REG32  EDMAC_TDLAR;
    CPU_REG32  RESERVED3[0x01];
    CPU_REG32  EDMAC_RDLAR;
    CPU_REG32  RESERVED4[0x01];
    CPU_REG32  EDMAC_EESR;
    CPU_REG32  RESERVED5[0x01];
    CPU_REG32  EDMAC_EESIPR;
    CPU_REG32  RESERVED6[0x01];
    CPU_REG32  EDMAC_TRSCER;
    CPU_REG32  RESERVED7[0x01];
    CPU_REG32  EDMAC_RMFCR;
    CPU_REG32  RESERVED8[0x01];
    CPU_REG32  EDMAC_TFTR;
    CPU_REG32  RESERVED9[0x01];
    CPU_REG32  EDMAC_FDR;
    CPU_REG32  RESERVED10[0x01];
    CPU_REG32  EDMAC_RMCR;
    CPU_REG32  RESERVED11[0x02];
    CPU_REG32  EDMAC_TFUCR;
    CPU_REG32  EDMAC_RFOCR;
    CPU_REG32  EDMAC_IOSR;
    CPU_REG32  EDMAC_FCFTR;
    CPU_REG32  RESERVED12[0x01];
    CPU_REG32  EDMAC_RPADIR;
    CPU_REG32  EDMAC_TRIMD;
    CPU_REG32  RESERVED13[0x12];
    CPU_REG32  EDMAC_RBWAR;
    CPU_REG32  EDMAC_RDFAR;
    CPU_REG32  RESERVED14[0x01];
    CPU_REG32  EDMAC_TBRAR;
    CPU_REG32  EDMAC_TDFAR;
    CPU_REG32  RESERVED15[0x09];

    CPU_REG32  ETHERC_ECMR;
    CPU_REG32  RESERVED17[0x01];
    CPU_REG32  ETHERC_RFLR;
    CPU_REG32  RESERVED18[0x01];
    CPU_REG32  ETHERC_ECSR;
    CPU_REG32  RESERVED19[0x01];
    CPU_REG32  ETHERC_ECSIPR;
    CPU_REG32  RESERVED20[0x01];
    CPU_REG32  ETHERC_PIR;
    CPU_REG32  RESERVED21[0x01];
    CPU_REG32  ETHERC_PSR;
    CPU_REG32  RESERVED22[0x05];
    CPU_REG32  ETHERC_RDMLR;
    CPU_REG32  RESERVED23[0x03];
    CPU_REG32  ETHERC_IPGR;
    CPU_REG32  ETHERC_APR;
    CPU_REG32  ETHERC_MPR;
    CPU_REG32  RESERVED24[0x01];
    CPU_REG32  ETHERC_RFCF;
    CPU_REG32  ETHERC_TPAUSER;
    CPU_REG32  ETHERC_TPAUSECR;
    CPU_REG32  ETHERC_BCFRR;
    CPU_REG32  RESERVED25[0x14];
    CPU_REG32  ETHERC_MAHR;
    CPU_REG32  RESERVED26[0x01];
    CPU_REG32  ETHERC_MALR;
    CPU_REG32  RESERVED27[0x01];
    CPU_REG32  ETHERC_TROCR;
    CPU_REG32  ETHERC_CDCR;
    CPU_REG32  ETHERC_LCCR;
    CPU_REG32  ETHERC_CNDCR;
    CPU_REG32  RESERVED28[0x01];
    CPU_REG32  ETHERC_CEFCR;
    CPU_REG32  ETHERC_FRECR;
    CPU_REG32  ETHERC_TSFRCR;
    CPU_REG32  ETHERC_TLFRCR;
    CPU_REG32  ETHERC_RFCR;
    CPU_REG32  ETHERC_MAFCR;
} NET_DEV;

