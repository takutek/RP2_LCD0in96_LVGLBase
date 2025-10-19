/*****************************************************************************
* | File      	:   DEV_Config.c
* | Author      :
* | Function    :   Hardware underlying interface
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2021-03-16
* | Info        :
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of theex Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
******************************************************************************/
#include "DEV_Config.h"

uint bl_slice_num;
uint dma_tx;
dma_channel_config c;

/**
 * delay x ms
 **/
void DEV_Delay_ms(uint32_t xms)
{
    sleep_ms(xms);
}

void DEV_GPIO_Init(void)
{
    DEV_GPIO_Mode(LCD_RST_PIN, 1);
    DEV_GPIO_Mode(LCD_DC_PIN, 1);
    DEV_GPIO_Mode(LCD_CS_PIN, 1);
    DEV_GPIO_Mode(LCD_BL_PIN, 1);

    DEV_Digital_Write(LCD_CS_PIN, 1);
    DEV_Digital_Write(LCD_DC_PIN, 0);
}

/**
 * GPIO read and write
 **/
void DEV_Digital_Write(uint16_t Pin, uint8_t Value)
{
    gpio_put(Pin, Value);
}

/**
 * SPI
 **/
void DEV_SPI_WriteByte(spi_inst_t *SPI_PORT,uint8_t Value)
{
    spi_write_blocking(SPI_PORT, &Value, 1);
}

void DEV_SPI_Write_nByte(spi_inst_t *SPI_PORT,uint8_t pData[], uint32_t Len)
{
    spi_write_blocking(SPI_PORT, pData, Len);
}

/**
 * GPIO Mode
 **/
void DEV_GPIO_Mode(uint16_t Pin, uint16_t Mode)
{
    gpio_init(Pin);
    if (Mode == 0 || Mode == GPIO_IN)
    {
        gpio_set_dir(Pin, GPIO_IN);
    }
    else
    {
        gpio_set_dir(Pin, GPIO_OUT);
    }
}
/*
** PWM
*/
void DEV_SET_PWM(uint8_t Value)
{
    if (Value < 0 || Value > 100)
    {
        //printf("DEV_SET_PWM Error \r\n");
    }
    else
    {
        pwm_set_chan_level(bl_slice_num, PWM_CHAN_B, Value);
    }
}

/******************************************************************************
function:	Module Initialize, the library and initialize the pins, SPI protocol
parameter:
Info:
******************************************************************************/
uint8_t DEV_Module_Init(void)
{
    // CLOCK Config
    set_sys_clock_khz(PLL_SYS_KHZ, true);
    clock_configure(
        clk_peri,
        0,                                                
        CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_CLKSRC_PLL_SYS, 
        PLL_SYS_KHZ * 1000,                               
        PLL_SYS_KHZ * 1000                              
    );

    // GPIO Config
    DEV_GPIO_Init();
    // PWM Config
    gpio_set_function(LCD_BL_PIN, GPIO_FUNC_PWM);
    bl_slice_num = pwm_gpio_to_slice_num(LCD_BL_PIN);
    pwm_set_wrap(bl_slice_num, 100);
    pwm_set_chan_level(bl_slice_num, PWM_CHAN_B, 40);
    pwm_set_clkdiv(bl_slice_num, 50);
    pwm_set_enabled(bl_slice_num, true);
    // SPI Config
    spi_init(LCD_SPI_PORT, 150 * 1000 * 1000);
    gpio_set_function(LCD_CLK_PIN, GPIO_FUNC_SPI);
    gpio_set_function(LCD_MOSI_PIN, GPIO_FUNC_SPI);
    // DMA Config
    dma_tx = dma_claim_unused_channel(true);
    c = dma_channel_get_default_config(dma_tx);
    channel_config_set_transfer_data_size(&c, DMA_SIZE_8); 
    channel_config_set_dreq(&c, spi_get_dreq(LCD_SPI_PORT, true));
    return 0;
}
