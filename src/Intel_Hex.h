#ifndef Intel_Hex_H
#define Intel_Hex_H
#include "Type.h"

typedef struct{
  uint32 length;
  uint32 address;
  uint32 type;
  uint32 data[255];
  uint32 checkSum;
  uint32 start;
  uint32 value;
}HexInfo;

uint32 sumData(HexInfo *hexinfo);
uint32 sumAddress(HexInfo *hexinfo);
uint32 verifyAndRead(char *line, HexInfo *hexinfo);
void catchError(int error);
uint32 readHexNumber(char *str, int numOfDigits);
void assertHexNumber(char *str, int numOfDigits);
#endif // Intel_Hex_H
