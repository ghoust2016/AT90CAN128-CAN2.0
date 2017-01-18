
/************************************************

文件：Util_bitfield.h
用途：单片机位定义
修改时间 :2015.06.04

************************************************/

#ifndef __UTIL_BITFIELD_H__
#define __UTIL_BITFIELD_H__

#define GET_BITFIELD(addr)         (*((bitfield volatile *)(addr)))
#define __GET_BIT(addr,b)          GET_BITFIELD(addr).Bit##b
#define GET_BIT(addr,b)            __GET_BIT(addr,b)
#define GET_Bitfield(addr)        (*(( bitfield *)(addr)))
#define __GET_Bit(addr,b)         GET_Bitfield(addr).Bit##b
#define GET_Bit(addr,b)           __GET_Bit(addr,b)
#define BIT_Alias(A,B)            GET_Bit(A,B)
#define BIT_ALIAS(A,B)            GET_BIT(A,B)


#define GET_BITFIELD8(addr)         (*((bitfield8 volatile *)(addr)))
#define __GET_BIT8(addr,b)          GET_BITFIELD8(addr).Bit##b
#define GET_BIT8(addr,b)            __GET_BIT8(addr,b)
#define GET_Bitfield8(addr)         (*(( bitfield8 *)(addr)))
#define __GET_Bit8(addr,b)          GET_Bitfield8(addr).bit##b
#define GET_Bit8(addr,b)            __GET_Bit8(addr,b)
#define BIT8_Alias(A,B)             GET_Bit8(A,B)
#define BIT8_ALIAS(A,B)             GET_BIT8(A,B)


#define GET_BITFIELD16(addr)         (*((bitfield16 volatile *)(addr)))
#define __GET_BIT16(addr,b)          GET_BITFIELD16(addr).Bit##b
#define GET_BIT16(addr,b)            __GET_BIT16(addr,b)
#define GET_Bitfield16(addr)         (*(( bitfield16 *)(addr)))
#define __GET_Bit16(addr,b)          GET_Bitfield16(addr).Bit##b
#define GET_Bit16(addr,b)           __GET_Bit16(addr,b)
#define BIT16_Alias(A,B)            GET_Bit16(A,B)
#define BIT16_ALIAS(A,B)            GET_BIT16(A,B)

#define GET_BITFIELD32(addr)        (*((bitfield32 volatile  *)(addr)))
#define __GET_BIT32(addr,b)         GET_BITFIELD32(addr).Bit##b
#define GET_BIT32(addr,b)           __GET_BIT32(addr,b)
#define GET_Bitfield32(addr)        (*(( bitfield32 *)(addr)))
#define __GET_Bit32(addr,b)        GET_Bitfield32(addr).Bit##b
#define GET_Bit32(addr,b)          __GET_Bit32(addr,b)
#define BIT32_Alias(A,B)           GET_Bit32(A,B)
#define BIT32_ALIAS(A,B)           GET_BIT32(A,B)

#define IO_BIT_ALIAS(A,B)          GET_BIT(A,B)
#define IO_BIT8_ALIAS(A,B)         GET_BIT8(A,B)
#define IO_BIT16_ALIAS(A,B)        GET_BIT16(A,B)
#define IO_BIT32_ALIAS(A,B)        GET_BIT32(A,B)

#ifdef  __AVR_IAR__
#undef  IO_BIT_ALIAS
#undef  IO_BIT8_ALIAS
#undef  IO_BIT16_ALIAS
#undef  IO_BIT32_ALIAS

#define GET_IO_BITFIELD(addr)        (*((bitfield volatile  __io*)(addr)))
#define __GET_IO_BIT(addr,b)         GET_IO_BITFIELD(addr).Bit##b
#define GET_IO_BIT(addr,b)           __GET_IO_BIT(addr,b)
#define GET_IO_BIT8(A,B)             __GET_IO_BIT(addr,b)

#define IO_BIT_ALIAS(A,B)            GET_IO_BIT(A,B)
#define IO_BIT8_ALIAS(A,B)           GET_IO_BIT8(A,B)

#endif

typedef union
{

     unsigned char Byte0;
	 unsigned char Byte1;
	 unsigned char Byte2;
	 unsigned char Byte3;
	 unsigned char Byte4;
	 unsigned char Byte5;
	 unsigned char Byte6;
	 unsigned char Byte7;
	 struct {
	                unsigned char Bit0:1;
	                unsigned char Bit1:1;
	                unsigned char Bit2:1;
	                unsigned char Bit3:1;
	                unsigned char Bit4:1;
	                unsigned char Bit5:1;
	                unsigned char Bit6:1;
	                unsigned char Bit7:1;
	         };

}bitfield8;

#define bitfield bitfield8

typedef union{
              unsigned short Word;
              struct {
                                unsigned char Bit0:1;
                                unsigned char Bit1:1;
                                unsigned char Bit2:1;
                                unsigned char Bit3:1;
                                unsigned char Bit4:1;
                                unsigned char Bit5:1;
                                unsigned char Bit6:1;
                                unsigned char Bit7:1;
                                unsigned char Bit8:1;
                                unsigned char Bit9:1;
                                unsigned char Bit10:1;
                                unsigned char Bit11:1;
                                unsigned char Bit12:1;
                                unsigned char Bit13:1;
                                unsigned char Bit14:1;
                                unsigned char Bit15:1;
                      } ;
}bitfield16;

typedef     union{
                   unsigned long Dword;
                   struct {
                                unsigned char Bit0:1;
                                unsigned char Bit1:1;
                                unsigned char Bit2:1;
                                unsigned char Bit3:1;
                                unsigned char Bit4:1;
                                unsigned char Bit5:1;
                                unsigned char Bit6:1;
                                unsigned char Bit7:1;
                                unsigned char Bit8:1;
                                unsigned char Bit9:1;
                                unsigned char Bit10:1;
                                unsigned char Bit11:1;
                                unsigned char Bit12:1;
                                unsigned char Bit13:1;
                                unsigned char Bit14:1;
                                unsigned char Bit15:1;
                                unsigned char Bit16:1;
                                unsigned char Bit17:1;
                                unsigned char Bit18:1;
                                unsigned char Bit19:1;
                                unsigned char Bit20:1;
                                unsigned char Bit21:1;
                                unsigned char Bit22:1;
                                unsigned char Bit23:1;
                                unsigned char Bit24:1;
                                unsigned char Bit25:1;
                                unsigned char Bit26:1;
                                unsigned char Bit27:1;
                                unsigned char Bit28:1;
                                unsigned char Bit29:1;
                                unsigned char Bit30:1;
                                unsigned char Bit31:1;
                   };


} bitfield32;

#define uint8_bits_def(x) union \
{\
  unsigned char x;\
  struct\
   {\
     unsigned char x##_Bit0:1,\
                   x##_Bit1:1,\
                   x##_Bit2:1,\
                   x##_Bit3:1,\
                   x##_Bit4:1,\
                   x##_Bit5:1,\
                   x##_Bit6:1,\
                   x##_Bit7:1;\
   };\
}\

#define uint16_bits_def(x) union \
{\
  unsigned char x;\
  struct\
   {\
     unsigned char x##_Bit0:1,\
                   x##_Bit1:1,\
                   x##_Bit2:1,\
                   x##_Bit3:1,\
                   x##_Bit4:1,\
                   x##_Bit5:1,\
                   x##_Bit6:1,\
                   x##_Bit7:1,\
                   x##_Bit8:1,\
                   x##_Bit9:1,\
                   x##_Bit10:1,\
                   x##_Bit11:1,\
                   x##_Bit12:1,\
                   x##_Bit13:1,\
                   x##_Bit14:1,\
                   x##_Bit15:1;\
   };\
}\

#define uint32_bits_def(x) union \
{\
  unsigned char x;\
  struct\
   {\
     unsigned char x##_Bit0:1,\
                   x##_Bit1:1,\
                   x##_Bit2:1,\
                   x##_Bit3:1,\
                   x##_Bit4:1,\
                   x##_Bit5:1,\
                   x##_Bit6:1,\
                   x##_Bit7:1,\
                   x##_Bit8:1,\
                   x##_Bit9:1,\
                   x##_Bit10:1,\
                   x##_Bit11:1,\
                   x##_Bit12:1,\
                   x##_Bit13:1,\
                   x##_Bit14:1,\
                   x##_Bit15:1,\
                   x##_Bit16:1,\
                   x##_Bit17:1,\
                   x##_Bit18:1,\
                   x##_Bit19:1,\
                   x##_Bit20:1,\
                   x##_Bit21:1,\
                   x##_Bit22:1,\
                   x##_Bit23:1,\
                   x##_Bit24:1,\
                   x##_Bit25:1,\
                   x##_Bit26:1,\
                   x##_Bit27:1,\
                   x##_Bit28:1,\
                   x##_Bit29:1,\
                   x##_Bit30:1,\
                   x##_Bit31:1;\
                             };\
}\



#endif
