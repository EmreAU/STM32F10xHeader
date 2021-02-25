#include "stm32f103C8_gpio.h"

void GPIO_ClockCtrl(GPIO_TypeDef *pGPIOx, uint8_t EnOrDi){
	if (EnOrDi == ENABLE){
		if(pGPIOx==GPIOA)
		{
			RCC->APB2ENR |= (1<<2);
		}else if(pGPIOx==GPIOB){
			RCC->APB2ENR |= (1<<3);
		}else if(pGPIOx==GPIOC){
			RCC->APB2ENR |= (1<<4);
		}else if(pGPIOx==GPIOD){
			RCC->APB2ENR |= (1<<5);
		}else if(pGPIOx==GPIOE){
			RCC->APB2ENR |= (1<<6);
		}
	}else{
		if(pGPIOx==GPIOA)
		{
			RCC->APB2ENR &=~ (0<<2);
		}else if(pGPIOx==GPIOB){
			RCC->APB2ENR &=~ (0<<3);
		}else if(pGPIOx==GPIOC){
			RCC->APB2ENR &= (0<<4);
		}else if(pGPIOx==GPIOD){
			RCC->APB2ENR &=~ (0<<5);
		}else if(pGPIOx==GPIOE){
			RCC->APB2ENR &=~ (0<<6);
		}
	}
}

void GPIO_PinMode(GPIO_TypeDef *pGPIOx, uint16_t pinNumber, uint16_t pinMode, uint32_t pinSpeed){
	volatile uint32_t *SelectedRegister; // Pointer koji ce pokazivati na trazeni registar (CRH ili CRL)
	
	if (pinNumber > 7){ // Provjeravamo da li je broj pina veci od 7 ili manji od 7 da znamo hocemo li korisitit CRL ili CRH registar
		SelectedRegister = &(pGPIOx->CRH);
	}else{
		SelectedRegister = &(pGPIOx->CRL);
	}
	
	const short unsigned int BitShift = pinNumber * 4; // Koliko bitova moramo da se pomjerimo da bi dosli do zeljenog  registra
	
	*SelectedRegister &=~ (0 << BitShift);
	*SelectedRegister &=~ (0 << (BitShift + 2) );
	*SelectedRegister |= (pinMode << BitShift);
	*SelectedRegister |= (pinSpeed << (BitShift + 2));
}

void GPIO_ResetPort(GPIO_TypeDef *pGPIOx){
	pGPIOx->BSRR &= 0xFFFF;
}