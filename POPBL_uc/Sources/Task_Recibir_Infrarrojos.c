/*********************************************************************
** 																	**
** project : POPBL			 										**
** filename : Task_Recibir_Infrarrojos.c							**
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
#define _TASK_INFRARROJOS_C_SRC
/*********************************************************************
**																	**
** MODULES USED 													**
** 																	**
**********************************************************************/
#include "recepcion_infrarrojos.h"
#include "hw_types.h"
#include "systick.h"
#include "interrupt.h"
#include "sysctl.h"
#include "keypad.h"
/*********************************************************************
** 																	**
** EXPORTED VARIABLES 												**
** 																	**
*********************************************************************/
extern TS_AUTOMATA activar_infrarrojos;
/*********************************************************************
** 																	**
** GLOBAL VARIABLES 												**
** 																	**
**********************************************************************/
/*Variables para guardar las interrupciones*/
tBoolean g_arriba=0;
tBoolean g_abajo=0;
tBoolean g_izquierda=0;
tBoolean g_derecha=0;
tBoolean g_select=0;
/*********************************************************************
** 																	**
** LOCAL FUNCTIONS 													**
** 																	**
**********************************************************************/

void vTask_Recibir_Infrarrojos(void *pvParameters) {

	while (1) {
		/*
		 * Ejecutamos la máquina de estados del recorrido
		 */
		EjecutaAutomata(&activar_infrarrojos);
	}
}
/*********************************************************************
** 																	**
** EOF 																**
** 																	**
**********************************************************************/
