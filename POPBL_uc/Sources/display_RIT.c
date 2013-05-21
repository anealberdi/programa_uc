/*********************************************************************
** 																	**
** project : POPBL			 										**
** filename : display_RIT.c											**
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
#define DISPLAY_RIT_C
/*********************************************************************
**																	**
** MODULES USED 													**
** 																	**
**********************************************************************/
#include "display_generico.h"
#include "drivers\rit128x96x4.h"
#include "string.h"
/*********************************************************************
** 																	**
** LOCAL FUNCTIONS 													**
** 																	**
**********************************************************************/
/**
 * @brief  Función para escribir en pantalla.
 *
 * @return        -
 *
*/
void DISPLAY_GENERICO_dibuja_string(const char *pcStr, unsigned long ulX,
        unsigned long ulY, unsigned char ucLevel){
	RIT128x96x4StringDraw(pcStr,ulX,ulY,ucLevel);
}
/**
 * @brief  Función para dibujar en pantalla.
 *
 * @return        -
 *
*/
void DISPLAY_GENERICO_dibuja_imagen(const unsigned char *pucImage, unsigned long ulX,
        unsigned long ulY, unsigned long ulWidth,
        unsigned long ulHeight){
	RIT128x96x4ImageDraw(pucImage, ulX,ulY,ulWidth,ulHeight);
}
/**
 * @brief  Función para inicializar pantalla.
 *
 * @return        -
 *
*/
void DISPLAY_GENERICO_init(){
	RIT128x96x4Init(1000000);
}
/*********************************************************************
** 																	**
** EOF 																**
** 																	**
**********************************************************************/




