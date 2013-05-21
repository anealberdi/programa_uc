/*********************************************************************
 ** 																**
 ** project : POPBL			 										**
 ** filename : pines.c												**
 ** version : 1 													**
 ** date : January 16, 2013 										**
 ** 																**
 **********************************************************************
 ** 																**
 ** Copyright (c) 2003, 					 						**
 ** All rights reserved. 											**
 ** 																**
 **********************************************************************
 **																	**
 **VERSION HISTORY:													**
 **----------------													**
 **Version : 1														**
 **Date : January 16, 2013											**
 **Revised by :														**
 **Description : Original version. 									**
 *********************************************************************/
#define _PINES_C_SRC
/*********************************************************************
 **																	**
 ** MODULES USED 													**
 ** 																**
 **********************************************************************/
#include "pines.h"
/*********************************************************************
 ** 																**
 ** DEFINITIONS AND MACROS 											**
 ** 																**
 **********************************************************************/
#define TRUE 1
/*********************************************************************
 ** 																**
 ** EXPORTED VARIABLES 												**
 ** 																**
 *********************************************************************/
/*Variables globales que indican las interrupciones de los botones y de los pines*/
extern tBoolean g_arriba;
extern tBoolean g_abajo;
extern tBoolean g_izquierda;
extern tBoolean g_derecha;
extern tBoolean g_select;
/*********************************************************************
 ** 																**
 ** LOCAL FUNCTIONS 												**
 ** 																**
 **********************************************************************/
/**
 * @brief  Función para inicializar el pin 0 y el pin 1 del puerto B.
 *
 * @return      -
 *
*/
void PINES_inicializar_puerto_b_pines_0_1(void) {
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1,
			GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);

}
/**
 * @brief  Función para inicializar la interrupción del pin 0 y el pin 1 del puerto B.
 *
 * @return      -
 *
*/
void PINES_inicializar_int_puerto_b_pines_0_1() {
	IntEnable(INT_GPIOB);
	GPIOIntTypeSet(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1, GPIO_BOTH_EDGES);
	GPIOPinIntEnable(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);
}
/**
 * @brief  Rutina de interrupción de los pines del puerto B.
 *
 * @return      -
 *
 * Se mira qué pin ha provocado la interrupción y estado en el que se encuentra ese pin
 * para saber si ha habido un flanco positivo o un flanco negativo.
*/
void __attribute__((interrupt)) PortBInterruptHandler(void) {
	unsigned long ul_port;
	unsigned char uc_pin;
	/*
	 * Guardamos el valor de la interrupción
	 */
	long temp = GPIOPinIntStatus(GPIO_PORTB_BASE, TRUE);

	/*
	 * Miramos si la interrupción ha sido provocada por el pin 0
	 */
	if (temp & GPIO_PIN_0) {
		unsigned long estado_pin;
		ul_port = GPIO_PORTB_BASE;
		uc_pin = GPIO_PIN_0;
		estado_pin = GPIOPinRead(ul_port, uc_pin);
		estado_pin = estado_pin & 0x1f;
		/*
		 * Si el flanco ha sido positivo
		 */
		if (estado_pin == 1) {
			g_arriba = 1;
			if ((xTaskIsTaskSuspended(xHandle_Task_Recibir_Infrarrojos))
					== true) {
				vTaskResume(xHandle_Task_Recibir_Infrarrojos);
			}
		}
		/*
		 * Si el flanco ha sido negativo
		 */
		else {
			g_abajo = 1;
		}
	}
	/*
	 * Miramos si la interrupción ha sido provocada por el pin 1
	 */
	if (temp & GPIO_PIN_1) {
		unsigned long estado_pin;
		ul_port = GPIO_PORTB_BASE;
		uc_pin = GPIO_PIN_1;
		estado_pin = GPIOPinRead(ul_port, uc_pin);
		estado_pin = estado_pin & 0x1f;
		/*
		 * Si el flanco ha sido positivo
		 */
		if (estado_pin == 1) {
			g_arriba = 1;
			if ((xTaskIsTaskSuspended(xHandle_Task_Recibir_Infrarrojos))
					== true) {
				vTaskResume(xHandle_Task_Recibir_Infrarrojos);
			}
		}
		/*
		 * Si el flanco ha sido negativo
		 */
		else {
			g_abajo = 1;
		}

	}
	/*
	 * Limpiamos la interrupción
	 */
	GPIOPinIntClear(ul_port, uc_pin);
}

/*********************************************************************
 ** 																	**
 ** EOF 																**
 ** 																	**
 **********************************************************************/
