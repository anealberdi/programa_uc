/*****************************************************************************
**											  								**
** project :  POPBL							 							  	**
** filename : framebuffer.h						  							**
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
#ifndef CONSOLE_H
#define CONSOLE_H
/*****************************************************************************
** 																			**
** MODULES USED 															**
** 																			**
****************************************************************************/
#include "hw_types.h"
/*****************************************************************************
** 																			**
** DEFINITIONS AND MACROS 													**
** 																			**
******************************************************************************/
#define MAX_ROWS 11
#define MAX_LINES 12
#define MAX_ELEMS 20
/*****************************************************************************
** 																			**
** PROTOTYPES OF GLOBAL FUNCTIONS											**
** 																			**
******************************************************************************/
void FRAME_BUFFER_init();
int FRAME_BUFFER_insert_image(char *puc, int x, int y, int w, int h);
int FRAME_BUFFER_insert_text(char *texto, int x, int y);
int FRAME_BUFFER_delete_element(int id);
void FRAME_BUFFER_actualiza_posicion_elemento(int id, int x, int y);
void FRAME_BUFFER_write_to_display(void);
void FRAME_BUFFER_change_text(char *texto, int id);
/*****************************************************************************
**	 																		**
** TYPEDEFS AND STRUCTURES 													**
** 																			**
*****************************************************************************/
#ifndef CONSOLE_C
#define PUB_CONSOLE extern
#else
#define PUB_CONSOLE
#endif
/*Creamos la estructura del buffer*/
struct Tipo_DISPLAY_ELEMENT{
	int id;
	int x;
	int y;
	int xOld;
	int yOld;
	int width;
	int height;
	char* picture_or_text;
	int what; /*0=IMAGE, 1=TEXT*/
};
/*Creamos un buffer: DISPLAY_ELEMENT*/
typedef struct Tipo_DISPLAY_ELEMENT DISPLAY_ELEMENT;

/*****************************************************************************
** 																			**
** EOF 																		**
** 																			**
******************************************************************************/
#endif
