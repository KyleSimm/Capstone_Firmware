#include "mcc_generated_files/spi_client/spi1.h"
#include "spi_client.h"

// Internal test data to send back to host
#define TEST_DATA_SIZE 8
static uint8_t testData[TEST_DATA_SIZE] = {10, 20, 30, 40, 50, 60, 70, 80};
static uint8_t sendIndex = 0;

uint8_t SPI_Client_ReceivedData[10];
uint8_t SPI_Client_ReceivedCount = 0;
bool SPI_Client_OutputEnabled = false;
uint8_t SPI_Client_Frequency = 0;


void SPI_Client_Initialize(void)
{
    
    SPI1_Open(0);   // Initialize SPI client (from MCC)
}

/**
 * @brief Main SPI task called from main loop.
 * Checks for new data and handles message parsing.
 */
void SPI_Client_Task(void)
{
    // If host sent a byte, read it
    while (SPI1_IsRxReady())
    {
        uint8_t byte = SPI1_ByteRead();
        SPI_Client_ReceivedData[SPI_Client_ReceivedCount++] = byte;

        printf("Client received byte: 0x%02X\r\n", byte);

        // Simple parser: first byte = command
        if (SPI_Client_ReceivedCount == 2)
        {
            uint8_t cmd = SPI_Client_ReceivedData[0];
            uint8_t val = SPI_Client_ReceivedData[1];

            if (cmd == 0x01) // Frequency
            {
                SPI_Client_Frequency = val;
                printf("Client: Frequency set to %u\r\n", val);
            }
            else if (cmd == 0x02) // ON/OFF
            {
                SPI_Client_OutputEnabled = (val != 0);
                printf("Client: Output %s\r\n", SPI_Client_OutputEnabled ? "ON" : "OFF");
            }

            // Reset buffer
            SPI_Client_ReceivedCount = 0;
        }
    

        // Prepare response for master (just test data for now)
        uint8_t nextByte = testData[sendIndex];
        sendIndex = (sendIndex + 1) % TEST_DATA_SIZE;

        SPI1_ByteWrite(nextByte);
    }
}



//Testing Code for SPI (NOT DONE) 

/* -------------------------------
   SPI HOST TEST FUNCTIONS
   Put these at the bottom of spi_client.c
---------------------------------*/
#ifdef SPI_HOST_TEST

// Initialize "host" SPI (using SPI2 in MCC)
#include "mcc_generated_files/spi2.h"

void SPI_Master_Init(void)
{
    SPI2_Initialize();
}

uint8_t SPI_Master_SendByte(uint8_t data)
{
    return SPI2_ByteExchange(data);
}

void SPI_Master_SendCommand(uint8_t *cmd, uint8_t len)
{
    for (uint8_t i=0; i<len; i++)
    {
        uint8_t resp = SPI_Master_SendByte(cmd[i]);
        printf("Master sent: 0x%02X | Client responded: 0x%02X\r\n", cmd[i], resp);
    }
}

#endif