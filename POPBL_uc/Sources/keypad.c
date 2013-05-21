/*********************************************************************
** 																	**
** project : POPBL			 										**
** filename : keypad.c 												**
** version : 1 														**
** date : January 16, 2013 											**
** 																	**
**********************************************************************
** 																	**
** Copyright (c) 2003, 					 							**
** All rights reserved. 											**
** 																	**
**********************************************************************
**																	**
**VERSION HISTORY:													**
**----------------													**
**Version : 1														**
**Date : January 16, 2013											**
**Revised by :														**
**Description : Original version. 									**
*********************************************************************/
#define _KEYPAD_C_SRC
/*********************************************************************
**																	**
** MODULES USED 													**
** 																	**
**********************************************************************/
#include "hw_types.h"
#include "hw_memmap.h"
#include "FreeRTOS.h"
#include "task.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "keypad.h"
#include "hw_ints.h"
#include "interrupt.h"
#include "consolaLCD/console.h"
/*********************************************************************
** 																	**
** DEFINITIONS AND MACROS 											**
** 																	**
**********************************************************************/
#define TRUE 1
/*********************************************************************
** 																	**
** EXPORTED VARIABLES 												**
** 																	**
*********************************************************************/
extern xTaskHandle xHandle_Task_Recibir_Infrarrojos;
/*********************************************************************
** 																	**
** GLOBAL VARIABLES 												**
** 																	**
**********************************************************************/
unsigned long g_ul_keypad_switches = 0x1f; /*Valor leído en los botones*/

/*Variables globales que indican las interrupciones de los botones y de los pines*/
extern tBoolean g_arriba;
extern tBoolean g_abajo;
extern tBoolean g_izquierda;
extern tBoolean g_derecha;
extern tBoolean g_select;
/*********************************************************************
** 																	**
** LOCAL FUNCTIONS 													**
** 																	**
**********************************************************************/
/**
 * @brief  Inicializamos el teclado (los botones)y sus interrupciones.
 *
 * @return      -
 * Inicializamos todos los botones de la placa y las configuramos para
 * que dén una interrupción con el franco de subida.
*/
void KEYPAD_inicializacion_keypad() {
	//Activamos pines del puerto F (botón select)
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_1); /*pin 1*/
	GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_STRENGTH_2MA,
			GPIO_PIN_TYPE_STD_WPU);
	//Activamos y configuramos las interrupciones del puerto F
	IntEnable(INT_GPIOF);
	GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_RISING_EDGE);
	GPIOPinIntEnable(GPIO_PORTF_BASE, GPIO_PIN_1);
	//Activamos pines del puerto E (botones up, down, right, left)
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_0); /*pin 0*/
	GPIOPadConfigSet(GPIO_PORTE_BASE, GPIO_PIN_0, GPIO_STRENGTH_2MA,
			GPIO_PIN_TYPE_STD_WPU);
	GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_1); /*pin 1*/
	GPIOPadConfigSet(GPIO_PORTE_BASE, GPIO_PIN_1, GPIO_STRENGTH_2MA,
			GPIO_PIN_TYPE_STD_WPU);
	GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_2); /*pin 2*/
	GPIOPadConfigSet(GPIO_PORTE_BASE, GPIO_PIN_2, GPIO_STRENGTH_2MA,
			GPIO_PIN_TYPE_STD_WPU);
	GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_3); /*pin 3*/
	GPIOPadConfigSet(GPIO_PORTE_BASE, GPIO_PIN_3, GPIO_STRENGTH_2MA,
			GPIO_PIN_TYPE_STD_WPU);
	//Activamos y configuramos las interrupciones del puerto E
	IntEnable(INT_GPIOE);
	GPIOIntTypeSet(GPIO_PORTE_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2
			| GPIO_PIN_3, GPIO_RISING_EDGE);
	GPIOPinIntEnable(GPIO_PORTE_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2
			| GPIO_PIN_3);
}
/**
 * @brief  Rutina de interrupción para saber qué botón ha producido
 * la interrupción del puerto E.
 *
 * @return      -
 * Se lee el valor del estado de las interrupciones y se miran uno
 * a uno los pines para comprobar cuál ha sido el que ha producido
 * la interrupción.
*/
void __attribute__((interrupt)) PortEInterruptHandler(void){
	unsigned long ul_port;
	unsigned char uc_pin;
	/*
	 * Guardamos el valor de la interrupción
	 */
	long temp = GPIOPinIntStatus( GPIO_PORTE_BASE, TRUE);
	/*
	 * Miramos si la interrupción ha sido provocada por el pin 0
	 */
	if( temp & GPIO_PIN_0)
	{
		ul_port=GPIO_PORTE_BASE;
		uc_pin=GPIO_PIN_0;
		g_arriba=1;
		g_abajo = 0;
		if ((xTaskIsTaskSuspended( xHandle_Task_Recibir_Infrarrojos ))==true){
			vTaskResume( xHandle_Task_Recibir_Infrarrojos );
		}


	}
	/*
	 * Miramos si la interrupción ha sido provocada por el pin 1
	 */
	if( temp & GPIO_PIN_1)
	{
		ul_port=GPIO_PORTE_BASE;
		uc_pin=GPIO_PIN_1;
		g_abajo = 1;
		g_arriba = 0;

	}
	/*
	 * Miramos si la interrupción ha sido provocada por el pin 2
	 */
	if( temp & GPIO_PIN_2)
	{
		ul_port=GPIO_PORTE_BASE;
		uc_pin=GPIO_PIN_2;
		g_izquierda=1;

	}
	/*
	 * Miramos si la interrupción ha sido provocada por el pin 3
	 */
	if( temp & GPIO_PIN_3)
	{
		ul_port=GPIO_PORTE_BASE;
		uc_pin=GPIO_PIN_3;
		g_derecha=1;
	}
	/*
	 * Limpiamos la interrupción
	 */
	GPIOPinIntClear(ul_port, uc_pin);
}
/**
 * @brief  Rutina de interrupción para saber si el botoón select ha producido la
 * interrupción del puerto F.
 *
 * @return      -
 * Se lee el valor del estado de las interrupciones y se mira si ha
 * sido el botón select quien ha provocado la interrupción.
*/
void __attribute__((interrupt)) PortFInterruptHandler(void){
	unsigned long ul_port;
	unsigned char uc_pin;
	/*
	 * Guardamos el valor de la interrupción
	 */
	long temp = GPIOPinIntStatus( GPIO_PORTF_BASE, TRUE);

	/*
	 * Miramos si la interrupción ha sido provocada por el pin 1
	 */
	if( temp & GPIO_PIN_1)
	{
		ul_port=GPIO_PORTF_BASE;
		uc_pin=GPIO_PIN_1;
		g_select = 1;
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
