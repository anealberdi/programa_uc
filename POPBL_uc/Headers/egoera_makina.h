/*****************************************************************************
**											  								**
** project :  POPBL							 							  	**
** filename : egoera_makina.h					  							**
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
#ifndef _EGOERA_MAKINA_H
#define _EGOERA_MAKINA_H
/*****************************************************************************
** 																			**
** MODULES USED 															**
** 																			**
****************************************************************************/
#include "hw_types.h"
/*****************************************************************************
**	 																		**
** TYPEDEFS AND STRUCTURES 													**
** 																			**
*****************************************************************************/
typedef void            (*TPFN_ACC)(void); /* Puntero a una función acción */
typedef tBoolean         (*TPFN_EVE)(void); /* Puntero a una función evento */

typedef struct {
	  unsigned char          id;             /* Identificador del estado destino */
	  char        * nombre;         /* Nombre identificativo de depuraci¢n */
	  TPFN_EVE      evento;         /* Puntero a la funci¢n evento */
	  TPFN_ACC      accion;         /* Puntero a la funci¢n acci¢n */
}TS_EVEACC;

typedef struct {
	  unsigned char          id;             /* Identificador del estado */
	  char        * nombre;         /* Nombre identificativo de depuraci¢n */
	  TPFN_ACC      controles;      /* Funci¢n de control del estado */
	  TS_EVEACC   * funcion;        /* Punteros las funciones del estado */
}TS_ESTADO;

typedef struct {
	  unsigned char          id;             /* Identificador del automata */
	  char        * nombre;         /* Nombre identificativo de depuraci¢n */
	  TPFN_EVE      StopCond;       /* Condici¢n necesaria para la ejecuci¢n */
	  TS_ESTADO   **estado;         /* Matriz de punteros a los ESTADOS */
}TS_AUTOMATA;
/*****************************************************************************
** 																			**
** DEFINITIONS AND MACROS 													**
** 																			**
******************************************************************************/
/*
 * Macros de la máquina de estados
 */
#define ITEM_EAC(ident, event, acci)	{ident, #event, event, acci},
#define ESTADO(nombre) \
const TS_EVEACC x##nombre[] = {
#define FIN_ESTADO(nombre, ident, control) \
{0,NULL,NULL,NULL} }; \
const TS_ESTADO nombre = \
{ident, #ident, control, (TS_EVEACC *)x##nombre};
#define AUTOMATA(nombre) \
const TS_ESTADO*(x##nombre[]) ={
#define FIN_AUTOMATA(nombre,ident, StopC) \
,NULL}; \
const TS_AUTOMATA nombre = \
{ident, #nombre, StopC, (TS_ESTADO**)x##nombre};
/*****************************************************************************
**								 											**
** EXPORTED VARIABLES 														**
** 																			**
******************************************************************************/

/*****************************************************************************
**					 														**
** EXPORTED FUNCTIONS 														**
** 																			**
******************************************************************************/
void EjecutaAutomata(TS_AUTOMATA *elAutomata);
/*****************************************************************************
** 																			**
** EOF 																		**
** 																			**
******************************************************************************/
#endif
