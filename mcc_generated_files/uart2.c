/**
  UART2 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    uart2.c

  @Summary
    This is the generated driver implementation file for the UART2 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This header file provides implementations for driver APIs for UART2.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.170.0
        Device            :  dsPIC33CH512MP508
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.61
        MPLAB             :  MPLAB X v5.45
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/
#include <xc.h>
#include "uart2.h"

/**
  Section: UART2 APIs
*/

void UART2_Initialize(void)
{
/**    
     Set the UART2 module to the options selected in the user interface.
     Make sure to set LAT bit corresponding to TxPin as high before UART initialization
*/
    // URXEN disabled; RXBIMD RXBKIF flag when Break makes low-to-high transition after being low for at least 23/11 bit periods; UARTEN enabled; MOD Asynchronous 8-bit UART; UTXBRK disabled; BRKOVR TX line driven by shifter; UTXEN disabled; USIDL disabled; WAKE disabled; ABAUD disabled; BRGH enabled; 
    // Data Bits = 8; Parity = None; Stop Bits = 1 Stop bit sent, 1 checked at RX;
    U2MODE = (0x8080 & ~(1<<15));  // disabling UARTEN bit
    // STSEL 1 Stop bit sent, 1 checked at RX; BCLKMOD disabled; SLPEN disabled; FLO Off; BCLKSEL FOSC/2; C0EN disabled; RUNOVF disabled; UTXINV disabled; URXINV disabled; HALFDPLX disabled; 
    U2MODEH = 0x00;
    // OERIE disabled; RXBKIF disabled; RXBKIE disabled; ABDOVF disabled; OERR disabled; TXCIE disabled; TXCIF disabled; FERIE disabled; TXMTIE disabled; ABDOVE disabled; CERIE disabled; CERIF disabled; PERIE disabled; 
    U2STA = 0x00;
    // URXISEL RX_ONE_WORD; UTXBE enabled; UTXISEL TX_BUF_EMPTY; URXBE enabled; STPMD disabled; TXWRE disabled; 
    U2STAH = 0x22;
    // BaudRate = 9600; Frequency = 4000000 Hz; BRG 103; 
    U2BRG = 0x67;
    // BRG 0; 
    U2BRGH = 0x00;
    // P1 0; 
    U2P1 = 0x00;
    // P2 0; 
    U2P2 = 0x00;
    // P3 0; 
    U2P3 = 0x00;
    // P3H 0; 
    U2P3H = 0x00;
    // TXCHK 0; 
    U2TXCHK = 0x00;
    // RXCHK 0; 
    U2RXCHK = 0x00;
    // T0PD 1 ETU; PTRCL disabled; TXRPT Retransmit the error byte once; CONV Direct logic; 
    U2SCCON = 0x00;
    // TXRPTIF disabled; TXRPTIE disabled; WTCIF disabled; WTCIE disabled; BTCIE disabled; BTCIF disabled; GTCIF disabled; GTCIE disabled; RXRPTIE disabled; RXRPTIF disabled; 
    U2SCINT = 0x00;
    // ABDIF disabled; WUIF disabled; ABDIE disabled; 
    U2INT = 0x00;
    
    U2MODEbits.UARTEN = 1;   // enabling UART ON bit
    U2MODEbits.UTXEN = 1;
    U2MODEbits.URXEN = 1;
}

uint8_t UART2_Read(void)
{
    while((U2STAHbits.URXBE == 1))
    {
        
    }

    if ((U2STAbits.OERR == 1))
    {
        U2STAbits.OERR = 0;
    }
    
    return U2RXREG;
}

void UART2_Write(uint8_t txData)
{
    while(U2STAHbits.UTXBF == 1)
    {
        
    }

    U2TXREG = txData;    // Write the data byte to the USART.
}

bool UART2_IsRxReady(void)
{
    return (U2STAHbits.URXBE == 0);
}

bool UART2_IsTxReady(void)
{
    return ((!U2STAHbits.UTXBF) && U2MODEbits.UTXEN );
}

bool UART2_IsTxDone(void)
{
    return U2STAbits.TRMT;
}

int __attribute__((__section__(".libc.write"))) write(int handle, void *buffer, unsigned int len) 
{
    unsigned int i;

    for (i = len; i; --i)
    {
        UART2_Write(*(char*)buffer++);
    }
    return(len);
}

/*******************************************************************************

  !!! Deprecated API !!!
  !!! These functions will not be supported in future releases !!!

*******************************************************************************/

uint32_t __attribute__((deprecated)) UART2_StatusGet (void)
{
    uint32_t statusReg = U2STAH;
    return ((statusReg << 16 ) | U2STA);
}

void __attribute__((deprecated)) UART2_Enable(void)
{
    U2MODEbits.UARTEN = 1;
    U2MODEbits.UTXEN = 1; 
    U2MODEbits.URXEN = 1;
}

void __attribute__((deprecated)) UART2_Disable(void)
{
    U2MODEbits.UARTEN = 0;
    U2MODEbits.UTXEN = 0; 
    U2MODEbits.URXEN = 0;
}


