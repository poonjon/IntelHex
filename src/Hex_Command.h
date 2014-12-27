#ifndef Hex_Command_H
#define Hex_Command_H
#include "Intel_Hex.h"

typedef struct{
  uint32 length;
  uint32 address;
  uint32 type;
  uint32 data[255];
}TLV;


int getNextAddressAndData(HexInfo *hexinfo);
void tlvData(TLV *tlv, HexInfo *hexinfo, uint32 address);
#endif //Hex_Command_H