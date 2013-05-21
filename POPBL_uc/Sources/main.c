/*********************************************************************
** 																	**
** project : POPBL			 										**
** filename : main.c 												**
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

#define _MAIN_C_SRC

/*********************************************************************
**																	**
** MODULES USED 													**
** 																	**
**********************************************************************/
/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Stellaris library includes. */
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "consolaLCD/console.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "keypad.h"
#include "hw_ints.h"

#include "clock.h"
#include "pines.h"
#include "display.h"
#include "system_tick.h"
/*********************************************************************
** 																	**
** GLOBAL VARIABLES 												**
** 																	**
**********************************************************************/
xTaskHandle xHandle_Task_Recibir_Infrarrojos; /*"Handle" de la tarea de
recibir infrarrojos*/
/*********************************************************************
** 																	**
** EXPORTED FUNCTIONS 												**
** 																	**
**********************************************************************/
/* The task functions. */
void vTask_Recibir_Infrarrojos( void *pvParameters );
void vTask_Idle( void *pvParameters );
/*********************************************************************
** 																	**
** LOCAL FUNCTIONS 													**
** 																	**
**********************************************************************/
int main( void )
{
	/*
	 * Se inicializan el cloak, el display, el teclado y los pines.
	 */
	CLOCK_inicializar_clock();
	DISPLAY_inicializar();
	KEYPAD_inicializacion_keypad();
	PINES_inicializar_puerto_b_pines_0_1();
	/*
	 * Se inicializan las interrupciones del puerto B
	 */
	PINES_inicializar_int_puerto_b_pines_0_1();
	/*
	 * Se crean las tareas
	 */
	xTaskCreate( vTask_Recibir_Infrarrojos,"vTask_Recibir_Infrarrojos",200, 1000 ,2, &xHandle_Task_Recibir_Infrarrojos );
	xTaskCreate( vTask_Idle,"vTask_Idle",200, 1000 ,1, NULL );
	/*
	 * Se suspende la tarea para recibir los infrarrojos
	 */
	vTaskSuspend(xHandle_Task_Recibir_Infrarrojos);
	/*
	 * Comienza el planeador
	 */
	vTaskStartScheduler();
	for (;;);
}
/*********************************************************************
** 																	**
** EOF 																**
** 																	**
**********************************************************************/
