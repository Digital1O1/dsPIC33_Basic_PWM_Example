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
#define DELAY 7
/* ----------------------------------- [ Include files ] -----------------------------------*/

#include "mcc_generated_files/system.h"
#include "mcc_generated_files/pwm.h"
#include <libpic30.h> //Defines __delay32();
#include <stdio.h> // Defines printf("");

/* ----------------------------------- [ PWM functions ] -----------------------------------*/

uint16_t masterPeriod, masterDutyCycle, masterPhase;


void cycle_LEDS() {
    PWM_GeneratorDisable(PWM_GENERATOR_1); //RB14
    PWM_DutyCycleSet(PWM_GENERATOR_1, 0x4FB0);
    PWM_GeneratorEnable(PWM_GENERATOR_1);
    __delay_ms(DELAY);

    PWM_GeneratorDisable(PWM_GENERATOR_1);
    PWM_DutyCycleSet(PWM_GENERATOR_1, 0x27D8);
    PWM_GeneratorEnable(PWM_GENERATOR_1);
    __delay_ms(DELAY);

    PWM_GeneratorDisable(PWM_GENERATOR_1);
    PWM_DutyCycleSet(PWM_GENERATOR_1, 0x64);
    PWM_GeneratorEnable(PWM_GENERATOR_1);
    __delay_ms(DELAY);

    //-------------------------------------------

    PWM_GeneratorDisable(PWM_GENERATOR_2); //RB12
    PWM_DutyCycleSet(PWM_GENERATOR_2, 0x4FB0);
    PWM_GeneratorEnable(PWM_GENERATOR_2);
    __delay_ms(DELAY);

    PWM_GeneratorDisable(PWM_GENERATOR_2);
    PWM_DutyCycleSet(PWM_GENERATOR_2, 0x27D8);
    PWM_GeneratorEnable(PWM_GENERATOR_2);
    __delay_ms(DELAY);

    PWM_GeneratorDisable(PWM_GENERATOR_2);
    PWM_DutyCycleSet(PWM_GENERATOR_2, 0x64);
    PWM_GeneratorEnable(PWM_GENERATOR_2);
    __delay_ms(DELAY);

    //-------------------------------------------

    PWM_GeneratorDisable(PWM_GENERATOR_3);
    PWM_DutyCycleSet(PWM_GENERATOR_3, 0x4FB0); //RB10
    PWM_GeneratorEnable(PWM_GENERATOR_3);
    __delay_ms(DELAY);

    PWM_GeneratorDisable(PWM_GENERATOR_3);
    PWM_DutyCycleSet(PWM_GENERATOR_3, 0x27D8);
    PWM_GeneratorEnable(PWM_GENERATOR_3);
    __delay_ms(DELAY);

    PWM_GeneratorDisable(PWM_GENERATOR_3);
    PWM_DutyCycleSet(PWM_GENERATOR_3, 0x64);
    PWM_GeneratorEnable(PWM_GENERATOR_3);
    __delay_ms(DELAY);


    //-------------------------------------------
    PWM_GeneratorDisable(PWM_GENERATOR_4); //RC12
    PWM_DutyCycleSet(PWM_GENERATOR_4, 0x4FB0);
    PWM_GeneratorEnable(PWM_GENERATOR_4);
    __delay_ms(DELAY);

    PWM_GeneratorDisable(PWM_GENERATOR_4);
    PWM_DutyCycleSet(PWM_GENERATOR_4, 0x27D8);
    PWM_GeneratorEnable(PWM_GENERATOR_4);
    __delay_ms(DELAY);

    PWM_GeneratorDisable(PWM_GENERATOR_4);
    PWM_DutyCycleSet(PWM_GENERATOR_4, 0x64);
    PWM_GeneratorEnable(PWM_GENERATOR_4);
    __delay_ms(DELAY);
}

void fade_LEDs() {
    for(int i = PWM_GENERATOR_1; i <=PWM_GENERATOR_4; i++)
    {
        PWM_PeriodSet(i,0x4E1F);
    }

    for (uint16_t i = 0; i < 32500; i = i += 500) {

    for(int i = PWM_GENERATOR_1; i <=PWM_GENERATOR_4; i++)
    {
        PWM_GeneratorDisable(i);
    }
        PWM_DutyCycleSet(PWM_GENERATOR_1, i);
        PWM_DutyCycleSet(PWM_GENERATOR_2, i);
        PWM_DutyCycleSet(PWM_GENERATOR_3, i);
        PWM_DutyCycleSet(PWM_GENERATOR_4, i);

        printf("%d\r\n", i);
        
    for(int i = PWM_GENERATOR_1; i <=PWM_GENERATOR_4; i++)
    {
        PWM_GeneratorEnable(i);
    }

        __delay_ms(DELAY);
    }
    for (uint16_t i = 32500; i > 0; i = i -= 500) {
    for(int i = PWM_GENERATOR_1; i <=PWM_GENERATOR_4; i++)
    {
        PWM_GeneratorDisable(i);
    }

        PWM_DutyCycleSet(PWM_GENERATOR_1, i);
        PWM_DutyCycleSet(PWM_GENERATOR_2, i);
        PWM_DutyCycleSet(PWM_GENERATOR_3, i);
        PWM_DutyCycleSet(PWM_GENERATOR_4, i);

        printf("%d\r\n", i);

    for(int i = PWM_GENERATOR_1; i <=PWM_GENERATOR_4; i++)
    {
        PWM_GeneratorEnable(i);
    }
        __delay_ms(DELAY);
    }
}

/* ----------------------------------- [ Main application ] -----------------------------------*/
int main(void) {
    // initialize the device
    SYSTEM_Initialize();

    masterPeriod = 0x4E1F;
    masterDutyCycle = 0x00;
    masterPhase = 0x0;

    /*
     * Hex values and their corresponding voltage values
       - 0xFFFF == 3.254
       - 0x4FB0 --> 3.309
       - 0x9F60 --> 3.309
       - 0x27D8 --> 1.687
       - 0x64   --> 0.015
     */
    while (1) {
        //cycle_LEDS();
        fade_LEDs();
    }
    return 1;
}
/**
 End of File
 */