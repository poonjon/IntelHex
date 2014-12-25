#include "Hex_Command.h"
#include "Intel_Hex.h"
#include <stdio.h>

int getNextAddressAndData(HexInfo *hexinfo){
static uint16 extendAddr = 0;
  if(hexinfo->type == 0){
    return 1;
  }
  else if(hexinfo->type == 4){
    extendAddr = extendAddr | hexinfo->data[9]<<12;
    extendAddr = extendAddr | hexinfo->data[10]<<8;
    extendAddr = extendAddr | hexinfo->data[11]<<4;
    extendAddr = extendAddr | hexinfo->data[12];
    return extendAddr;
  }
}
  