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
* File Name    : r_init_non_existent_port.c
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

/*******************************************************************************
Includes <System Includes> , "Project Includes"
*******************************************************************************/
#include <stdint.h>
#include "iodefine.h"
#include "r_init_non_existent_port.h"


/*******************************************************************************
* Outline      : Initialization of non-existent ports
* Header       : r_init_non_existent_port.h
* Function Name: R_INIT_NonExistentPort
* Description  : Initialize non-existent ports.
* Arguments    : none
* Return Value : none
*******************************************************************************/
void R_INIT_NonExistentPort (void)
{
    /* PDR - Port Direction Register
       0:Input(Function as an input pin.)
       1:Output(Function as an output pin.)*/

#if (DEF_P0PDR != 0x00)
    /* ---- Set the PORT0.PDR register ---- */
    /* Casting the 8bit,because an operation result is 32bit. */
    PORT0.PDR.BYTE = (uint8_t)(PORT0.PDR.BYTE | DEF_P0PDR);
#endif

#if (DEF_P1PDR != 0x00)
    /* ---- Set the PORT1.PDR register ---- */
    /* Casting the 8bit,because an operation result is 32bit. */
    PORT1.PDR.BYTE = (uint8_t)(PORT1.PDR.BYTE | DEF_P1PDR);
#endif

#if (DEF_P2PDR != 0x00)
    /* ---- Set the PORT2.PDR register ---- */
    /* Casting the 8bit,because an operation result is 32bit. */
    PORT2.PDR.BYTE = (uint8_t)(PORT2.PDR.BYTE | DEF_P2PDR);
#endif

#if (DEF_P3PDR != 0x00)
    /* ---- Set the PORT3.PDR register ---- */
    /* Casting the 8bit,because an operation result is 32bit. */
    PORT3.PDR.BYTE = (uint8_t)(PORT3.PDR.BYTE | DEF_P3PDR);
#endif

#if (DEF_P4PDR != 0x00)
    /* ---- Set the PORT4.PDR register ---- */
    /* Casting the 8bit,because an operation result is 32bit. */
    PORT4.PDR.BYTE = (uint8_t)(PORT4.PDR.BYTE | DEF_P4PDR);
#endif

#if (DEF_P5PDR != 0x00)
    /* ---- Set the PORT5.PDR register ---- */
    /* Casting the 8bit,because an operation result is 32bit. */
     PORT5.PDR.BYTE = (uint8_t)(PORT5.PDR.BYTE | DEF_P5PDR);
 #endif

#if (DEF_P6PDR != 0x00)
    /* ---- Set the PORT6.PDR register ---- */
    /* Casting the 8bit,because an operation result is 32bit. */
    PORT6.PDR.BYTE = (uint8_t)(PORT6.PDR.BYTE | DEF_P6PDR);
#endif

#if (DEF_P7PDR != 0x00)
    /* ---- Set the PORT7.PDR register ---- */
    /* Casting the 8bit,because an operation result is 32bit. */
    PORT7.PDR.BYTE = (uint8_t)(PORT7.PDR.BYTE | DEF_P7PDR);
#endif

#if (DEF_P8PDR != 0x00)
    /* ---- Set the PORT8.PDR register ---- */
    /* Casting the 8bit,because an operation result is 32bit. */
    PORT8.PDR.BYTE = (uint8_t)(PORT8.PDR.BYTE | DEF_P8PDR);
#endif

#if (DEF_P9PDR != 0x00)
    /* ---- Set the PORT9.PDR register ---- */
    /* Casting the 8bit,because an operation result is 32bit. */
    PORT9.PDR.BYTE = (uint8_t)(PORT9.PDR.BYTE | DEF_P9PDR);
#endif

#if (DEF_PAPDR != 0x00)
    /* ---- Set the PORTA.PDR register ---- */
    /* Casting the 8bit,because an operation result is 32bit. */
    PORTA.PDR.BYTE = (uint8_t)(PORTA.PDR.BYTE | DEF_PAPDR);
#endif

#if (DEF_PBPDR != 0x00)
    /* ---- Set the PORTB.PDR register ---- */
    /* Casting the 8bit,because an operation result is 32bit. */
    PORTB.PDR.BYTE = (uint8_t)(PORTB.PDR.BYTE | DEF_PBPDR);
#endif

#if (DEF_PCPDR != 0x00)
    /* ---- Set the PORTC.PDR register ---- */
    /* Casting the 8bit,because an operation result is 32bit. */
    PORTC.PDR.BYTE = (uint8_t)(PORTC.PDR.BYTE | DEF_PCPDR);
#endif

#if (DEF_PDPDR != 0x00)
    /* ---- Set the PORTD.PDR register ---- */
    /* Casting the 8bit,because an operation result is 32bit. */
    PORTD.PDR.BYTE = (uint8_t)(PORTD.PDR.BYTE | DEF_PDPDR);
#endif

#if (DEF_PEPDR != 0x00)
    /* ---- Set the PORTE.PDR register ---- */
    /* Casting the 8bit,because an operation result is 32bit. */
    PORTE.PDR.BYTE = (uint8_t)(PORTE.PER.BYTE | DEF_PEPDR);
#endif

#if (DEF_PFPDR != 0x00)
    /* ---- Set the PORTF.PDR register ---- */
    /* Casting the 8bit,because an operation result is 32bit. */
    PORTF.PDR.BYTE = (uint8_t)(PORTF.PDR.BYTE | DEF_PFPDR);
#endif

#if (DEF_PGPDR != 0x00)
    /* ---- Set the PORTG.PDR register ---- */
    /* Casting the 8bit,because an operation result is 32bit. */
    PORTG.PDR.BYTE = (uint8_t)(PORTG.PDR.BYTE | DEF_PGPDR);
#endif

#if (DEF_PJPDR != 0x00)
    /* ---- Set the PORTJ.PDR register ---- */
    PORTJ.PDR.BYTE = (uint8_t)(PORTJ.PDR.BYTE | DEF_PJPDR);
#endif

}

/* End of File */

