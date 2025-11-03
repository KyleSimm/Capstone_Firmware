/*
� [2025] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include "mcc_generated_files/system/system.h"

//Custom Classes

/*
    Main application
*/

#include "xc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Header/Custom Files
#include "vfd_Control_Loop.h"
#include "../CapstoneFirmware256.X/spi_client.h" //Fix Path for Other Processor

/* PIN MAPPING FOR dsPIC33CK1024MP710 && dsPIC33CK256MP508
 * ---|-------------|------------------|------------------|-----------------------------------------*
 * ---|  Pin Number |Pin Number: 256   |   Pin Type       |---Purpose------------------------------*
 * ---|-------------|------------------|------------------|----------------------------------------*
 * ---|     91      |        40        | SPI Input CLK    |----------------------------------------*
 * ---|-------------|------------------|------------------|----------------------------------------*
 * ---|     90      |        46        | SPI Input DSI1   |----------------------------------------*
 * ---|-------------|------------------|------------------|----------------------------------------*
 * ---|     89      |        47        | SPI Output SDO1  |----------------------------------------*
 * ---|-------------|------------------|------------------|----------------------------------------*
 * ---|     86      |        66        | SPI Input SS1    |----------------------------------------*
 * ---|-------------|------------------|------------------|----------------------------------------*
 * ---|     43      |        34        | Clock Out        |----------------------------------------*
 * ---|-------------|------------------|------------------|----------------------------------------*
 * ---|     42      |        35        | Clock IN         |----------------------------------------*
 * ---|-------------|------------------|------------------|----------------------------------------*
 * ---|     17      |        15        | ADC              |----------------------------------------*
 * ---|-------------|------------------|------------------|----------------------------------------*
 * ---|     36      |        33        | ADC              |----------------------------------------*
 * ---|-------------|------------------|------------------|----------------------------------------*
 * ---|     37      |        41        | ADC-RB2          |----------------------------------------*
 * ---|-------------|------------------|------------------|----------------------------------------*
 * ---|     41      |        43        | ADC-RB3          |----------------------------------------*
 * ---|-------------|------------------|------------------|----------------------------------------*
 * ---|     38      |        28        | ADC              |----------------------------------------*
 * ---|-------------|------------------|------------------|----------------------------------------*
 * ---|     50      |        29        | ADC              |----------------------------------------*
 * ---|-------------|------------------|------------------|----------------------------------------*
 * ---|     1       |        1         | PWM1H-RB14       |----------------------------------------*
 * ---|-------------|------------------|------------------|----------------------------------------*
 * ---|     3       |        3         | PWM1L-RB15       |----------------------------------------*
 * ---|-------------|------------------|------------------|----------------------------------------*
 * ---|     97      |        78        | PWM2H-RB12       |----------------------------------------*
 * ---|-------------|------------------|------------------|----------------------------------------*
 * ---|     100     |        80        | PWM2L-RB13       |----------------------------------------*
 * ---|-------------|------------------|------------------|----------------------------------------*
 * ---|     92      |        75        | PWM3H-RB10       |----------------------------------------*
 * ---|-------------|------------------|------------------|----------------------------------------*
 * ---|     93      |        76        | PWM3L-RB11       |----------------------------------------*
 * ---|-------------|------------------|------------------|----------------------------------------*
 * ---|     77      |        61        | PGCx Input       |----------------------------------------*
 * ---|-------------|------------------|------------------|----------------------------------------*
 * ---|     75      |        60        | PGDx Input       |----------------------------------------*
 * ---|-------------|------------------|------------------|----------------------------------------*
 * ---|     51      |        5         | GPIO             |----------------------------------------*
 * ---|------------ |------------------|------------------|----------------------------------------*
 * ---|     20      |        6         | GPIO             |----------------------------------------*
 * ---|-------------|------------------|------------------|----------------------------------------*
 * ---| 64,39,88,14 |  31,12,51,71     | VDD              |----------------------------------------*
 * ---|-------------|------------------|------------------|----------------------------------------*
 * ---| 13,87,40,63 |  11,32,50,70     | VSS              |----------------------------------------*
 * ---|-------------|------------------|------------------|----------------------------------------*
 */

/* PWM Current Settings
 *    Master Input Frequency: 8 MHz
 *    Requested Frequency 15 kHz
 *    Operation Mode: Center-Aligned
 *    PWM Output Mode: Complementary 
 *    Calculated Period: 66.671 us
 *    Calculated Frequency: 16 KHz
 *    Dead Time Low: 200ns
 *    Dead Time High: 200ns
 *    Data Update Settings: Immediate
 *    
 */

/* Host SPI Pins
 
 */
int main(void)
{
    SYSTEM_Initialize();
    vfd_Init();
    SPI_Client_Initialize();
    

    //Testing Code
    SPI_Master_Init();
    printf("\r\nSPI Host/Client Test Start\r\n");

    uint8_t freq_cmd[2] = {0x01, 0x32}; // Frequency = 50
    uint8_t on_cmd[2]   = {0x02, 0x01}; // Turn ON

    while(1) //Will Be Changing Logic Later
     {
        // Send frequency command
        SPI_Master_SendCommand(freq_cmd, 2);

        // Let client task parse received bytes
        SPI_Client_Task();

        __delay_ms(1000);

        // Send ON command
        SPI_Master_SendCommand(on_cmd, 2);

        SPI_Client_Task();

        __delay_ms(2000);
    }
        

    
    return 0;    
}


