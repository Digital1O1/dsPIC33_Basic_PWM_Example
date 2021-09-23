# Overview of Repository
- Provide insight and a guide on how to generate a Pulse-Width-Modulation (PWM) signal using the [MPLABX IDE](https://www.microchip.com/en-us/development-tools-tools-and-software/mplab-x-ide) and the [MPLAB Code Configurator](https://www.microchip.com/en-us/development-tools-tools-and-software/embedded-software-center/mplab-code-configurator) after spending two months trying to figure it out on my own and being told on the Mircochip fourms to "read the datasheets"


# Items Used
- (1) [dspic33CH512MP508 Curiosity development board](https://www.microchip.com/en-us/development-tool/DM330028-2) 
- (4) 100 Ohm resistors, or any value resistors you have
- (5) Jumper cables

# Step By Step Instructions for the PWM Peripheral
1. Open MPLAB Code Configurator by clicking on the icon circled in red.

![image](https://user-images.githubusercontent.com/39348633/134432527-5ea6fc8c-0f07-456c-8262-15f8ffb6adae.png)

2. Enable the PWM and UART2 peripherals that are listed under 'Device Resources. Enabling the UART peripheral will allow us to monitor the PWM signal being generated in real time.

![image](https://user-images.githubusercontent.com/39348633/134433781-b929281f-6a6e-40a8-9b06-1b115939ee2a.png)

3. Double click on the 'PWM' Peripheral and you'll see the 'Hardware Settings' window pop up
    - Under 'Select Required PWM Generators' enable all the PWM_Generators that are listed by clicking on them

![image](https://user-images.githubusercontent.com/39348633/134434529-f34b83c0-77b4-4afc-8057-497a54787644.png)

4. Make sure :
   - 'Enable PWM Generator' is checked
   - 'PWM Operation Mode' is set to Independent Edge
   - 'PWM Output Mode' is set to Complementary

5. Under PWM Frequency Settings :
   - Set PWM Input Clock Selection to 4000000
   - Under the Period settings set :
     - Requested frequency : 235.29412 kHz
     - Requested period    : 4.25 us
   - Under Duty Cycle set : 
     -  PWM Duty Cycle : 0
     -  PWM Phase      : 0 ns
   - Under Trigger Control Settings set :
      - Start of Cycle Trigger : Self-Trigger
      - Trigger Output Selection : EOC event
   - Under ADC Trigger set :
      - ADC Trigger 1/2 : None
      - Trigger A/B/C compare : 0 ns
   - Under Dead Time and Override Settings set :
      - PWM L/H Dead Time Delay : 0 ns
      - PWM L/H Override : disabled
   - Under Data Update Settings set :
      - Update Trigger : Manual
      - Update Mode : SOC Update

Here's also a screenshot that you can also follow along with the mentioned settings

![image](https://user-images.githubusercontent.com/39348633/134454108-a020d7f1-4ae6-463c-8c02-fa000fb29615.png)

![image](https://user-images.githubusercontent.com/39348633/134454142-8cd6472e-dda4-4476-b1f9-f3d50af1dcc8.png)

# Step By Step Instructions for the UART2 Peripheral
The most crucial step is to ensure that the 'Redirect Printf to UART' is enabled so we can check/watch the values being generated for the PWM signal 
![image](https://user-images.githubusercontent.com/39348633/134455533-7a4c4664-0d60-417f-8004-cfdc9a3fd5b3.png)

# Generate Code

Under 'Project Resources' click 'Generate' to, quite literally, generate the code we've configurated for through the MCC GUI.

![image](https://user-images.githubusercontent.com/39348633/134539724-2610f924-0dc0-4d8d-945d-146c5a7b4167.png)

# Pin Manager

While the MPLABX Code Configurator is still open, on the right hand side of the IDE is the 'Pin Manager : Package View' window.

Since we're controlling four EXTERNAL LEDs and the on-board RGB LED, right click on the corresponding green boxes as indicated on the screenshot below and change them to the values listed.

For example, when you right click on port RB10 a drop down menu will pop up and will allow you to designate that port as PWM3-H

![image](https://user-images.githubusercontent.com/39348633/134537220-67af762f-8906-46a9-9b19-4a34684255ec.png)
![image](https://user-images.githubusercontent.com/39348633/134537459-e7ff64ae-0d2c-4a20-af40-2ac8958606d9.png)

# Overview of MCC Generated Code

## Generating the PWM Signal

If you go to the project folder --> Header Files --> MCC Generated Files --> There's a pwm.h file that shows what each function does and the parameters needed per function.

For example, the following code snippet is to change the PWM duty cycle

```C
/**
  @Summary
    Enables the specific PWM generator.

  @Description
    This routine is used to enable the specific PWM generator selected by the argument PWM_GENERATOR.

  @Param
    genNum - PWM generator number.

  @Returns
    None
 
  @Example 
    <code>
    PWM_GeneratorEnable(PWM_GENERATOR_1);
    </code>
*/
PWM_GeneratorEnable(PWM_GENERATOR genNum)
{
    switch(genNum) { 
        case PWM_GENERATOR_1:
                PG1CONLbits.ON = 1;              
                break;       
        case PWM_GENERATOR_2:
                PG2CONLbits.ON = 1;              
                break;       
        case PWM_GENERATOR_3:
                PG3CONLbits.ON = 1;              
                break;       
        case PWM_GENERATOR_4:
                PG4CONLbits.ON = 1;              
                break;       
        default:break;    
    }     
}

```

My intial thoughts was that the PWM_GeneratorEnable() function was all that I needed.

After spending two months and reading any datasheet that was related to generating a PWM signal, I was dead wrong.

I posted my woes in the Microchip fourms and was forunate enough to have a [solution](https://www.microchip.com/forums/m1180923-p2.aspx) provided to me by @GettinBetter whom used the 'MasterPWM' settings to change the duty cycle of the blue on-board RGB LED.

The TL;DR version of his post is as follows
- In pwm.h has a section that outlines how to use the 'Master PWM' settings which will be used as a guide to generate a PWM signal from one of the four PWM generators
- An outline of the mentioned Master PWM settings can be found below

```C
  @Summary
    Initializes PWM module.

  @Description
    This routine initializes PWM module, using the given initialization data. 

  @Param
    None.

  @Returns
    None
 
  @Example 
    <code>
    uint16_t masterPeriod,masterDutyCycle,masterPhase;

    masterPeriod = 0xFFFF;
    masterDutyCycle = 0xFF;
    masterPhase = 0xF;

    PWM_Initialize();
 
    PWM_GeneratorDisable();

    PWM_MasterPeriodSet(masterPeriod);
    PWM_MasterDutyCycleSet(masterDutyCycle);
    PWM_MasterPhaseSet(masterPhase);
 
    PWM_GeneratorEnable(PWM_GENERATOR_1);

    </code>
```
- So in order to use the PWM_Generator_1 to generate the PWM signal, you just have to swap the following functions      
  - PWM_MasterPeriodSet(masterPeriod) --> PWM_PeriodSet(PWM_GENERATOR_1,0x4E20)
---
## Basic example how to generate a PWM signal from PWM_GENERATOR_1

This snippet of code will dim an LED that's attached to Pin RB14 in accordance to the hex value being passed in the PWM_DutyCycleSet() function.
- Decimal values such as Unsigned Ints up to 32500 can be used instead of Hex values

```C
    while(true)
    {
        PWM_PeriodSet(PWM_GENERATOR_1,0x4E20);        //Decimal value : 20000
        PWM_GeneratorDisable(PWM_GENERATOR_1);        //Pin : RB14
        PWM_DutyCycleSet(PWM_GENERATOR_1, 0x4FB0);    //Decimal value : 20400
        PWM_GeneratorEnable(PWM_GENERATOR_1);
        __delay_ms(300);

        PWM_GeneratorDisable(PWM_GENERATOR_1);
        PWM_DutyCycleSet(PWM_GENERATOR_1, 0x27D8);    //Decimal value : 10200
        PWM_GeneratorEnable(PWM_GENERATOR_1);
        __delay_ms(300);

        PWM_GeneratorDisable(PWM_GENERATOR_1);
        PWM_DutyCycleSet(PWM_GENERATOR_1, 0x64);      //Decimal value : 100
        PWM_GeneratorEnable(PWM_GENERATOR_1);
        __delay_ms(300);
    }

```
## Basic example to toggle on-board RGB LED

The pins corresponding to the on-board RGB LED are :
- RB14 : BLUE
- RD5  : RED
- RD7  : Green

When we enable PWM_GENERATOR_1 and PWM_GENERATOR_4 we can send a PWM signal to pin(s) RB14, RD5 and RD7.

However when right clicking pins like RB14, I'm currently not sure what the difference is between PWM4H and PWM4L
- As of 9/22/2021 I'm under the assumption that the designated pin will 'Start' the PWM signal high or low depending if it's assigned PWM4H or PWM4L
  - Example : If RB14 was designated as PWM4H, the PWM signal will start HIGH at 3.3 volts
    - If the same pin was assigned PWM4L, the PWM signal will start LOW, or at 0 volts

![image](https://user-images.githubusercontent.com/39348633/134592211-402ae4c7-5218-4359-a8f6-d4dcf9620270.png)

## Setting up UART 

For troulbeshooting/sanity checks, we'll be using the printf() function to ensure the PWM signal is being generated when the fade_LEDs() function is enabled/uncommented in the main function loop

For the dsPIC33CH512MP508 Curiosity board pin(s) RC10/RC11 are the perspective TX/RX pins.

To enable them :
- Go to the pin manager
- Right click on pin RC11 and set it to U2TX
  - Under the pin module, ensure RC11 the box for 'Start High' is checked
- Do the same with pin RC10 and set it to U2RX

![image](https://user-images.githubusercontent.com/39348633/134595394-c95101a6-8b03-4716-ba5c-40330e019ae0.png)


Since there was no sort of documentation on how to generate a basic PWM signal and reading the [ High-Resolution PWM with Fine Edge Placement
](https://ww1.microchip.com/downloads/en/DeviceDoc/dsPIC33-PIC24-FRM-High-Resolution-PWM-with-Fine-Edge-Placement-70005320b.pdf) or the [High-Speed PWM Module](https://ww1.microchip.com/downloads/en/DeviceDoc/70000323h.pdf#page=17&zoom=100,106,96) raised more questions than answers lead/motivated me to creating this repository with hopes of helping others.

