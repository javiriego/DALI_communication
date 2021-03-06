/****************************************************************************************************
*                                      DEFINICIONES GLOBALES                                        *
*****************************************************************************************************/
/**
 *****************************************************************************************************
 * @file 		global_def.h
 * @author 	Javier Riego Barcia
 * @date 		23-Marzo-2021
 * @brief		Global macros and definitions
 *****************************************************************************************************
 *
 *
 *****************************************************************************************************
 */
 
#define BIT(x) (1 << (x))
#define SETBITS(x,y) ((x) |= (y))
#define CLEARBITS(x,y) ((x) &= (~(y)))
#define SETBIT(x,y) SETBITS((x), (BIT((y))))
#define CLEARBIT(x,y) CLEARBITS((x), (BIT((y))))
#define BITSET(x,y) ((x) & (BIT(y)))
#define BITCLEAR(x,y) !BITSET((x), (y))
#define BITSSET(x,y) (((x) & (y)) == (y))
#define BITSCLEAR(x,y) (((x) & (y)) == 0)
#define BITVAL(x,y) (((x)>>(y)) & 1)

#define ON  1
#define OFF 0

#define TRUE  1
#define FALSE 0

#define ENABLED  1
#define DISABLED 0

