/*****************************************************************************
**											  								**
** project :  POPBL							 							  	**
** filename : Recepcion_Infrarrojos.h			  							**
** version : 1 									  							**
** date :  	2013-01-16		 		 									    **
** 											  								**
******************************************************************************
** 											  								**
** gpl2 license  2013, Irune Agirre, Aitor Arrieta & Ane Alberdi	  		**
**  								  					                    **
** 											  								**
******************************************************************************
**										        							**
**VERSION HISTORY:									  						**
**----------------									  						**
**Version : 1										  						**
**Date : 2013-01-16										 					**
**Revised by : 							  									**
**Description : Original version.							  				**
*****************************************************************************/
#ifndef _RECEPCION_INFRARROJOS_H
#define _RECEPCION_INFRARROJOS_H
/*****************************************************************************
** 																			**
** MODULES USED 															**
** 																			**
****************************************************************************/
#include "egoera_makina.h"
#include "stdio.h"
#include "FreeRTOS.h"
#include "task.h"
#include "consolaLCD\console.h"
#include "system_tick.h"
#include "display.h"
/*****************************************************************************
** 																			**
** DEFINITIONS AND MACROS 													**
** 																			**
******************************************************************************/
/*Máquina de estados*/
#define ACTIVAR_INFRARROJOS		0
/*Estados*/
#define ESPERAR		0
#define LEER_ON		1
#define LEER_OFF	2
#define LEER_ON_2	3
#define LEER_OFF_2	4
#define PREGUNTAR   5
#define ACTIVADO	6
#define LEER_OFF_3	7
#define LEER_ON_3	8
#define LEER_OFF_4	9
#define LEER_ON_4	10

/*Tiempos*/
#define PERIODO			80000
#define T_95_MS			720000 //oain 90 dao
#define T_105_MS		900000   //112.5
#define T_195_MS		1520000  //190ms
#define T_205_MS		1800000  // 225ms
#define TICKS_90MS		10
#define TICKS_190MS		20

/*Macros*/
#define		TIEMPO_ENTRE_FLANCOS	g_ul_xTimeTimerOn - g_ul_xTimeTimerOff1 + g_cycles*PERIODO
#define		DIBUJA_TIME				sprintf(str, "%f ms ", g_time);consolePrintStr(7, 7, str);refreshConsoleLine(7);
/*****************************************************************************
**	 																		**
** TYPEDEFS AND STRUCTURES 													**
** 																			**
*****************************************************************************/
#ifndef _RECEPCION_INFRARROJOS_C
#define PUB_RECEPCION_INFRARROJOS extern
#else
#define PUB_RECEPCION_INFRARROJOS
#endif
/*****************************************************************************
** 																			**
** PROTOTYPES OF GLOBAL FUNCTIONS											**
** 																			**
******************************************************************************/
/*****************************************************************************
**								 											**
** EXPORTED VARIABLES 														**
** 																			**
******************************************************************************/
extern tBoolean g_arriba;
extern tBoolean g_abajo;
extern tBoolean g_izquierda;
extern tBoolean g_derecha;
/*****************************************************************************
**					 														**
** EXPORTED FUNCTIONS 														**
** 																			**
******************************************************************************/
/*
 * Eventos
 */
tBoolean RECECPCION_INFRARROJOS_fev_flanco_positivo (void);
tBoolean RECECPCION_INFRARROJOS_fev_flanco_t_corto_min (void);
tBoolean RECECPCION_INFRARROJOS_fev_flanco_positivo_t_corto_ok (void);
tBoolean RECECPCION_INFRARROJOS_fev_flanco_t_largo_min (void);
tBoolean RECECPCION_INFRARROJOS_fev_flanco_positivo_t_largo_ok (void);
tBoolean RECECPCION_INFRARROJOS_fev_flanco_negativo (void);
tBoolean RECECPCION_INFRARROJOS_fev_flanco_negativo_t_corto_ok (void);
tBoolean RECECPCION_INFRARROJOS_fev_flanco_negativo_t_largo_ok (void);
tBoolean RECECPCION_INFRARROJOS_fev_t_corto (void);
tBoolean RECECPCION_INFRARROJOS_fev_t_largo (void);
tBoolean RECECPCION_INFRARROJOS_fev_derecha_pulsado();
tBoolean RECECPCION_INFRARROJOS_fev_izquierda_pulsado();
/*
 * Acciones
 */
void RECECPCION_INFRARROJOS_fac_leer_on (void);
void RECECPCION_INFRARROJOS_fac_leer_off (void);
void RECECPCION_INFRARROJOS_fac_leer_on_2 (void);
void RECECPCION_INFRARROJOS_fac_leer_off_2 (void);
void RECECPCION_INFRARROJOS_fac_leer_on_3 (void);
void RECECPCION_INFRARROJOS_fac_leer_off_3 (void);
void RECECPCION_INFRARROJOS_fac_leer_on_4 (void);
void RECECPCION_INFRARROJOS_fac_leer_off_4 (void);
void RECECPCION_INFRARROJOS_fac_activar (void);
void RECECPCION_INFRARROJOS_fac_desactivar (void);
void RECECPCION_INFRARROJOS_fac_cancelar (void);
void RECEPCION_INFRARROJOS_fac_borrar_inter(void);
void RECECPCION_INFRARROJOS_fac_preguntar(void);
/*
 *
 */
void RECEPCION_INFRARROJOS_coger_tiempo_actual(void);
void RECEPCION_INFRARROJOS_dormir_tarea_90ms();
void RECEPCION_INFRARROJOS_dormir_tarea_190ms();
tBoolean RECEPCION_INFRARROJOS_mirar_flanco_positivo();
tBoolean RECEPCION_INFRARROJOS_mirar_flanco_negativo();
/*****************************************************************************
** 																			**
** EOF 																		**
** 																			**
******************************************************************************/
#endif
