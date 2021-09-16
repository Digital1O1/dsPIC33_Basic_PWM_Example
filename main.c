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
#define DELAY 10

/* ----------------------------------- [ Include files ] -----------------------------------*/

#include "mcc_generated_files/system.h"
#include "mcc_generated_files/pwm.h"
#include <libpic30.h> //Defines __delay32();
#include <stdio.h> // Defines printf("");

/* ----------------------------------- [ PWM functions ] -----------------------------------*/

uint16_t masterPeriod, masterDutyCycle, masterPhase;

void blink_LED() {
    PWM_GeneratorDisable(PWM_GENERATOR_1);
    masterDutyCycle = 0x00; // 0% 0
    PWM_MasterDutyCycleSet(masterDutyCycle);
    PWM_GeneratorEnable(PWM_GENERATOR_1);

    __delay_ms(300);

    PWM_GeneratorDisable(PWM_GENERATOR_1);
    masterDutyCycle = 0x3E8; // 15% 1000
    PWM_MasterDutyCycleSet(masterDutyCycle);
    PWM_GeneratorEnable(PWM_GENERATOR_1);

    __delay_ms(300);

    PWM_GeneratorDisable(PWM_GENERATOR_1);
    masterDutyCycle = 0x00; // 0% 0
    PWM_MasterDutyCycleSet(masterDutyCycle);
    PWM_GeneratorEnable(PWM_GENERATOR_1);

    __delay_ms(300);

    PWM_GeneratorDisable(PWM_GENERATOR_1);
    masterDutyCycle = 0xFFFF; // 100% 65535
    PWM_MasterDutyCycleSet(masterDutyCycle);
    PWM_GeneratorEnable(PWM_GENERATOR_1);

    __delay_ms(300);


}

/* ----------------------------------- [ Main application ] -----------------------------------*/
int main(void) {
    // initialize the device
    SYSTEM_Initialize();

    masterPeriod = 0x4E1F;
    masterDutyCycle = 0xFDE8;
    masterPhase = 0x0;

    PWM_MasterPeriodSet(masterPeriod);

    while (1) {
        //blink_LED();

        ///*
        for (uint16_t i = 0; i < 32500; i = i += 500) {
            PWM_GeneratorDisable(PWM_GENERATOR_1);
            PWM_MasterDutyCycleSet(i);
            printf("%d\r\n", i);
            PWM_GeneratorEnable(PWM_GENERATOR_1);
            __delay_ms(DELAY);
        }
        for (uint16_t i = 32500; i > 0; i = i -= 500) {
            PWM_GeneratorDisable(PWM_GENERATOR_1);
            PWM_MasterDutyCycleSet(i);
            printf("%d\r\n", i);
            PWM_GeneratorEnable(PWM_GENERATOR_1);
            __delay_ms(DELAY);
        }
        //*/
        
    }
    return 1;
}
/**
 End of File
 */