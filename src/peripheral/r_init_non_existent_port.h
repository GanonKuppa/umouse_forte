/*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized. This
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2014 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/
/*******************************************************************************
* System Name  : RX71M initialization example
* File Name    : r_init_non_existent_port.h
* Version      : Ver 1.00
* Device       : R5F571MLCxFC(RX71M Group)
* Abstract     : Program example of RX71M initialization
* Tool-Chain   : e2 studio Version 3.1.0.24
*              : C/C++ Compiler Package for RX Family (V.2.02.00)
* OS           : not use
* H/W Platform : Renesas Starter Kit for RX71M
* Description  : Initialization of non-existent ports.
* Limitation   : none
*******************************************************************************/
/*******************************************************************************
* History      : DD.MM.YYYY Version  Description
*              : 05.01.2015 1.00     First Release
*******************************************************************************/

/* Guards against multiple inclusion */
#ifndef R_INIT_NON_EXISTENT_PORT_H
#define R_INIT_NON_EXISTENT_PORT_H

/*******************************************************************************
Macro definitions
*******************************************************************************/
#define PIN_SIZE    (100)

#if ((PIN_SIZE == 177) || (PIN_SIZE == 176))
 #define DEF_P0PDR        (0x00)        /* non-existent pin: none */
 #define DEF_P1PDR        (0x00)        /* non-existent pin: none */
 #define DEF_P2PDR        (0x00)        /* non-existent pin: none */
 #define DEF_P3PDR        (0x00)        /* non-existent pin: none */
 #define DEF_P4PDR        (0x00)        /* non-existent pin: none */
 #define DEF_P5PDR        (0x70)        /* non-existent pin: P54 to P56 */
 #define DEF_P6PDR        (0x00)        /* non-existent pin: none */
 #define DEF_P7PDR        (0x00)        /* non-existent pin: none */
 #define DEF_P8PDR        (0x00)        /* non-existent pin: none */
 #define DEF_P9PDR        (0x00)        /* non-existent pin: none */
 #define DEF_PAPDR        (0x00)        /* non-existent pin: none */
 #define DEF_PBPDR        (0x00)        /* non-existent pin: none */
 #define DEF_PCPDR        (0x00)        /* non-existent pin: none */
 #define DEF_PDPDR        (0x00)        /* non-existent pin: none */
 #define DEF_PEPDR        (0x00)        /* non-existent pin: none */
 #define DEF_PFPDR        (0x00)        /* non-existent pin: none */
 #define DEF_PGPDR        (0x00)        /* non-existent pin: none */
 #define DEF_PJPDR        (0x00)        /* non-existent pin: none */

#elif ((PIN_SIZE == 145) || (PIN_SIZE == 144))
 #define DEF_P0PDR        (0x00)        /* non-existent pin: none */
 #define DEF_P1PDR        (0x03)        /* non-existent pin: P10,P11 */
 #define DEF_P2PDR        (0x00)        /* non-existent pin: none */
 #define DEF_P3PDR        (0x00)        /* non-existent pin: none */
 #define DEF_P4PDR        (0x00)        /* non-existent pin: none */
 #define DEF_P5PDR        (0x00)        /* non-existent pin: none */
 #define DEF_P6PDR        (0x00)        /* non-existent pin: none */
 #define DEF_P7PDR        (0x00)        /* non-existent pin: none */
 #define DEF_P8PDR        (0x00)        /* non-existent pin: none */
 #define DEF_P9PDR        (0xF0)        /* non-existent pin: P94 to P97 */
 #define DEF_PAPDR        (0x00)        /* non-existent pin: none */
 #define DEF_PBPDR        (0x00)        /* non-existent pin: none */
 #define DEF_PCPDR        (0x00)        /* non-existent pin: none */
 #define DEF_PDPDR        (0x00)        /* non-existent pin: none */
 #define DEF_PEPDR        (0x00)        /* non-existent pin: none */
 #define DEF_PFPDR        (0x1F)        /* non-existent pin: PF0 to PF4 */
 #define DEF_PGPDR        (0xFF)        /* non-existent pin: PG0 to PG7 */
 #define DEF_PJPDR        (0x00)        /* non-existent pin: none */

#elif (PIN_SIZE == 100)
 #define DEF_P0PDR        (0x0F)        /* non-existent pin: P00 to P03 */
 #define DEF_P1PDR        (0x03)        /* non-existent pin: P10,P11 */
 #define DEF_P2PDR        (0x00)        /* non-existent pin: none */
 #define DEF_P3PDR        (0x00)        /* non-existent pin: none */
 #define DEF_P4PDR        (0x00)        /* non-existent pin: none */
 #define DEF_P5PDR        (0x40)        /* non-existent pin: P56 */
 #define DEF_P6PDR        (0xFF)        /* non-existent pin: P60 to P67 */
 #define DEF_P7PDR        (0xFF)        /* non-existent pin: P70 to P77 */
 #define DEF_P8PDR        (0xCF)        /* non-existent pin: P80 to P83,P86,P87 */
 #define DEF_P9PDR        (0xFF)        /* non-existent pin: P90 to P97 */
 #define DEF_PAPDR        (0x00)        /* non-existent pin: none */
 #define DEF_PBPDR        (0x00)        /* non-existent pin: none */
 #define DEF_PCPDR        (0x00)        /* non-existent pin: none */
 #define DEF_PDPDR        (0x00)        /* non-existent pin: none */
 #define DEF_PEPDR        (0x00)        /* non-existent pin: none */
 #define DEF_PFPDR        (0x3F)        /* non-existent pin: PF0 to PF5 */
 #define DEF_PGPDR        (0xFF)        /* non-existent pin: PG0 to PG7 */
 #define DEF_PJPDR        (0x20)        /* non-existent pin: PJ5 */

#else
#endif

/*******************************************************************************
Exported global variables and functions (to be accessed by other files)
*******************************************************************************/
void R_INIT_NonExistentPort(void);

#endif /* R_INIT_NON_EXISTENT_PORT_H */

/* End of File */
