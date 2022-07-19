/*
 * hx711.c
 *
 *  Created on: Jul 3, 2022
 *      Author: prana
 */
#include "main.h"
#include <stdio.h>
#include <string.h>

#define clk		GPIO_PIN_9
#define data	GPIO_PIN_8

extern int32_t Read_weight (void);
extern void power_down(void);
extern void power_up(void);
extern void HX711_Init(void);
extern int32_t HX711_Value(uint8_t gain);
extern int HX711_Average_Value(uint8_t gain, uint8_t times);
extern int32_t HX711_Tare(uint8_t gain, uint8_t times);
extern int32_t hx711_calibration (int32_t Odata);

extern int32_t buffer, weight;
extern int32_t offset, Read_offset;
extern double Coef;
extern int32_t Read_Coef;


int32_t Read_weight (void)
{
	unsigned int i = 0;												// local deceleration for multiple addition for averaging
	int32_t weight_live = 0;
	int32_t tempAvg = 0;												// local deceleration to temporarily store the averaging value
	int32_t prev = 0;
	power_up();
	for (i = 0; i <= 4; i++)											// for loop for continuously  add the value 50 times.
	{												// Function call to start the ADC conversion
		prev = HX711_Value(128);
		tempAvg = tempAvg + prev;						// Adding the previous ADC converted value and the current ADC converted
	}
	// value
	buffer = tempAvg /5;
	buffer = buffer - Read_offset;
	weight_live = buffer / Read_Coef;
	power_down();
	return weight_live;
}

void HX711_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = clk;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = data;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);
	HAL_Delay(50);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);

}

int HX711_Average_Value(uint8_t gain, uint8_t times)
{
    int sum = 0;
    for (int i = 0; i < times; i++)
    {
        sum += HX711_Value(gain);
    }

    return sum / times;
}

int32_t HX711_Value(uint8_t gain)
{
    int buffer;
    buffer = 0;

    while (HAL_GPIO_ReadPin(GPIOA, data)==1);

    for (uint8_t i = 0; i < 24; i++)
    {
    	HAL_GPIO_WritePin(GPIOA, clk, GPIO_PIN_SET);
    	//delay_us(1);
        buffer = buffer << 1 ;
        //delay_us(1);
        if (HAL_GPIO_ReadPin(GPIOA, data))
        {
            buffer ++;
        }

        HAL_GPIO_WritePin(GPIOA, clk, GPIO_PIN_RESET);
        //delay_us(1);
    }

    for (int i = 0; i < gain; i++)
    {
    	HAL_GPIO_WritePin(GPIOA, clk, GPIO_PIN_SET);
    	HAL_GPIO_WritePin(GPIOA, clk, GPIO_PIN_RESET);
    }

    buffer = buffer ^ 0x800000;

    return buffer;
}

int32_t hx711_calibration (int32_t Odata)
{
	static int32_t loadRaw = 8130119;
	Coef = ((loadRaw - Odata) / 1000);
	return Coef;
}

int32_t HX711_Tare(uint8_t gain, uint8_t times)
{
    int sum = HX711_Average_Value(gain, times);
    offset = sum;
    return offset;
}

void power_down(void)
{
	HAL_GPIO_WritePin(GPIOA, clk, 0);
	HAL_GPIO_WritePin(GPIOA, clk, 1);
	HAL_Delay(1);
}

void power_up(void)
{
	HAL_GPIO_WritePin(GPIOA, clk, 0);
}

