/*****************************************************************************
**											  								**
** project :  POPBL							 							  	**
** filename : display_generico.h				  							**
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
#ifndef _DISPLAY_GENERICO_H
#define _DISPLAY_GENERICO_H
#endif
/*****************************************************************************
** 																			**
** MODULES USED 															**
** 																			**
****************************************************************************/
#include "hw_types.h"
/*****************************************************************************
** 																			**
** PROTOTYPES OF GLOBAL FUNCTIONS											**
** 																			**
******************************************************************************/
void DISPLAY_GENERICO_dibuja_string(const char *pcStr, unsigned long ulX,
        unsigned long ulY, unsigned char ucLevel);
void DISPLAY_GENERICO_dibuja_imagen(const unsigned char *pucImage, unsigned long ulX,
        unsigned long ulY, unsigned long ulWidth,
        unsigned long ulHeight);
void DISPLAY_GENERICO_init();
/*****************************************************************************
**	 																		**
** TYPEDEFS AND STRUCTURES 													**
** 																			**
*****************************************************************************/
#ifndef DISPLAY_RIT_C
#define PUB_DISPLAY_RIT extern
#else
#define PUB_DISPLAY_RIT
#endif
/*****************************************************************************
** 																			**
** EOF 																		**
** 																			**
******************************************************************************/

