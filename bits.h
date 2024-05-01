#ifndef _bits_
#define _bits_


#define SET_BIT(reg,bitNo)  reg|= (1<<bitNo)
#define CLR_BIT(reg,bitNo)  reg&=~ (1<<bitNo)
#define GET_BIT(reg,bitNo) ((reg>>bitNo) & 1)

#define SET(reg, val) reg|=val 
#define CLR(reg, val) reg&=~val

#define GET_REG(reg)         (reg&0xff)

#endif

