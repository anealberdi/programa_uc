/*********************************************************************
** 																	**
** project : POPBL			 										**
** filename : egoera_makina.c										**
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
/*********************************************************************
**																	**
** MODULES USED 													**
** 																	**
**********************************************************************/
#include "egoera_makina.h"
#include "stdio.h"
#include "hw_types.h"
/*********************************************************************
** 																	**
** PROTOTYPES OF LOCAL FUNCTIONS 									**
** 																	**
*********************************************************************/
void EjecutaEstadoVertical(TS_ESTADO *elEstado);
/*********************************************************************
** 																	**
** GLOBAL VARIABLES 												**
** 																	**
**********************************************************************/
unsigned char fms_mv = 0; /*Variable que indica el estado actual*/
unsigned char fms_mv_anterior= 0; /*Variable que indica el estado anterior*/
/*********************************************************************
** 																	**
** LOCAL FUNCTIONS 													**
** 																	**
**********************************************************************/
/**
 * @brief  Función para ejecutar la máquina de estados.
 *
 * @return        -
 * Se recorren los estados de la máquina de éstados, entrando cada vez
 * en el estado que indica el índice del estado actual.
 *
*/
void EjecutaAutomata(TS_AUTOMATA *elAutomata)
{
	TS_ESTADO **Indx;    /* Valor indice rastreador */

	//if (elAutomata->StopCond())  return;
	Indx = elAutomata -> estado;
	for (Indx = elAutomata->estado; *Indx != NULL; ++Indx)
	{
		  if (fms_mv == (*Indx)->id)
	    {
	    	EjecutaEstadoVertical(*Indx);
			return;
	    }
	}
}
/**
 * @brief  Función para ejecutar cada estado.
 *
 * @return        -
 * Se miran uno a uno los eventos correspondientes a las transiciones de cada
 * estado. Si alguna de ellas se ha cumplido, se ejecuta la acción que le toca,
 * y cambia el índice que indica el estado actual al índice que indica la transi-
 * ción que se ha realizado.
 *
*/
void EjecutaEstadoVertical(TS_ESTADO *elEstado)
{
	TS_EVEACC *Indx;   /* Indice de rastreo */

//	(*elEstado->controles)();

	for (Indx = elEstado->funcion; Indx->evento != NULL; ++Indx)
	{
		if (Indx->evento() == true)
		{
			if (Indx->accion != NULL)
			{
				Indx->accion();
			}
			if (Indx->id != fms_mv)
			{
				fms_mv_anterior = fms_mv;
				fms_mv = Indx->id;

				return;
			}
		}
	}
}
/*********************************************************************
** 																	**
** EOF 																**
** 																	**
**********************************************************************/
