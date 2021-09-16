/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.170.0
        Device            :  dsPIC33CH512MP508
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.61
        MPLAB 	          :  MPLAB X v5.45
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

#define FCY 8000000UL // defines __delay_ms()
/**
  Section: Included Files
*/
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/pwm.h"
#include <libpic30.h> //Defines __delay32();
#include <stdio.h> // Defines printf("");

    // SYSTEMS USED & PROJECT AIMS
    // printf("Explorer 16/32 v3 DM240001-3, ICD4, dsPIC33CH128MP508 PIM\n\r");
    // printf("MPLABX v5.5, MCC v4.1.0, XC16 v1.70\n\r");
    // printf("Setup PWN Basic \n\n\r"); 
    // printf("LED alternates from 10% to 80% @ 300ms \n\n\r"); 
/*
                         Main application
 */
int main(void)
{
    // initialize the device
    SYSTEM_Initialize(); 
    
    uint16_t masterPeriod,masterDutyCycle,masterPhase;
    

    masterPeriod = 0x4E1F;
    masterDutyCycle = 0x7D0;
    masterPhase = 0x0;

    //PWM_Initialize(); // Commented out in SYSTEM_Initilize
    PWM_MasterPeriodSet(masterPeriod);

    while (1)
    {
    PWM_GeneratorDisable(PWM_GENERATOR_1);
    masterDutyCycle = 0x7D0; // ~10%
    PWM_MasterDutyCycleSet(masterDutyCycle);
    PWM_GeneratorEnable(PWM_GENERATOR_1);
    
    __delay_ms(300);
    
    PWM_GeneratorDisable(PWM_GENERATOR_1);
    masterDutyCycle = 0x3E80; // ~80%
    PWM_MasterDutyCycleSet(masterDutyCycle);
    PWM_GeneratorEnable(PWM_GENERATOR_1);
    
    __delay_ms(300);
    
    }
    return 1; 
}
/**
 End of File
*/