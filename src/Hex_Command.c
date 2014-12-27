#include "Hex_Command.h"
#include "Intel_Hex.h"
#include <stdio.h>

int getNextAddressAndData(HexInfo *hexinfo){
  static uint16 extendAddr = 0;
  static uint32 startAddr = 0;
  static uint32 newAddr = 0;
  static int extendLinearFlag = 0;
  static int extendSegmentFlag = 0;
  static int startAddrFlag = 0;
  uint32 addrAdd;
  int i, j = 9;
  
  switch(hexinfo->type){
  
    case 0:      

      if(startAddrFlag == 1){
        startAddrFlag = 0;
        return startAddr;
      }
      else if(extendLinearFlag == 1 && extendSegmentFlag == 0){
        addrAdd = extendAddr << 16;
        newAddr = hexinfo->address + addrAdd;
        return newAddr;
      }
      else if(extendLinearFlag == 0 && extendSegmentFlag == 1){
        addrAdd = extendAddr << 4;
        newAddr = hexinfo->address + addrAdd;
        return newAddr;
      }
      else
        return hexinfo->address;
      
      break;
    
    case 1:
      return 0;
      break;
    
    case 2:
    case 4:

      if(hexinfo->type == 2){
        extendSegmentFlag = 1;
        extendLinearFlag = 0;
        extendAddr = 0;
      }
      else if(hexinfo->type == 4){
        extendSegmentFlag = 0;
        extendLinearFlag = 1;
        extendAddr = 0;
      }
      
      //move in binary form
      for(i = 0 ; i < 4 ; i++){
        extendAddr = extendAddr<<4 | hexinfo->data[j];
        j++;
      }

      return extendAddr;
      break;
    
    case 3:
    case 5:
    
      startAddrFlag = 1;
      extendLinearFlag = 0; 
      extendSegmentFlag = 0;
      
      for(i = 0 ; i < 8 ; i++){
        startAddr = startAddr<<4 | hexinfo->data[j];
        j++;
      }
      return startAddr;

      break;
  }
}
  
void tlvData(TLV *tlv, HexInfo *hexinfo, uint32 address){
  int i, k=0, j = 9;
  tlv->address = address;
  tlv->type = hexinfo->type;
  tlv->length = hexinfo->length;
  
  for(i = 0 ; i < hexinfo->length ; i++){
    tlv->data[k] = hexinfo->data[j];
    j++;
    k++;
    tlv->data[k] = hexinfo->data[j];
    j++;
    k++;
  }
  
}