#include <LPC17xx.h>
#include <lpc17xx_pinsel.h>
#include <lpc17xx_gpio.h>
#include <lpc17xx_gpdma.h>

void configPin(void);
void configDMA(void);
void configDAC(void);

#define DMA_SIZE 60;
#define NUM_SINE_SAMPLE 60;
#define SIN_FREQ_IN_HZ 50;
#define PCLK_DAC_IN_MHZ 25; //clk div by 4.


GPDMA_Channel_CFG_Type GPDMACfg;
uint32_t dac_sine_lut[NUM_SINE_SAMPLE];

int main(void){
	uint32_t i;
	uint32_t sin_0_90_16_samples[16] = {
		/*
		muchos valores que dan paja copiar a mano
		*/
	}
	configPin();
	configDAC();
	for (i = 0; i < count; ++i)
	{
		/* code */
	}
}

void configPin(){
	PINSEL_CFG_Type pinsel_cfg;

	pinsel_cfg.Portnum = 0;
	pinsel_cfg.Pinnum = 26;
	pinsel_cfg.Funcnum = 2;
	pinsel_cfg.Pinmode = 0;
	pinsel_cfg.OpenDrain = 0;

	PINSEL_ConfigPin(&pinsel_cfg);
	return;
}

void configDAC(void){
	uint32_t tmp;
	DAC_CONVERTER_CFG_Type DAC_ConverterConfigStruct;
	DAC_ConverterConfigStruct.DNI_ENA = SET;
	DAC_ConverterConfigStruct.DMA_ENA = SET;
	DAC_Init(LPC_DAC);
	//set timeout for dac
	tmp = (PCLK_DAC_IN_MHZ * 100000)/(SIN_FREQ_IN_HZ * NUM_SINE_SAMPLE);
	DAC_SetDMATimeOut(LPC_DAC, tmp);
	DAC_ConfigDAConverterControl(LPC_DAC, &DAC_ConverterConfigStruct);
	return;
}

void configDMA(void){
	GPDMA_LLI_Type DMA_LLI_Strct;
	//prepare DMA link list item structure
	DMA_LLI_Strct.AscAddr = (uint32_t) dac_sine_lut;
	DMA_LLI_Strct.DstAddr = (uint32_t)&(LPC_DAC->DACR);
	DMA_LLI_Strct.NextLLI = (uint32_t)&DMA_LLI_Strct;
	DMA_LLI_Strct.Control = DMA_SIZE

	| (2<<18) //source width 32 bits
	| (2<<21) //des. width 32 bits
	| (2<<26); /source increment

	//termianr codigo
}