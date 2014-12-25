#include "Intel_Hex.h"
#include <stdio.h>
#include "Type.h"
#include "ErrorCode.h"
#include "CException.h"

uint32 readHexNumber(char *str, int numOfDigits){
  int i;
  char buffer[16];
  uint16 value = 0;
  
  if(numOfDigits == 1 || numOfDigits == 2 || numOfDigits == 4){
    assertHexNumber(str, numOfDigits);
    if(numOfDigits == 1)
      sscanf(str, "%01x", &value);
    else if(numOfDigits == 2)
      sscanf(str, "%02x", &value);
    else if(numOfDigits == 4)
      sscanf(str, "%04x", &value);
  }
  else
    catchError(ERR_NOT_DIGIT);
    
  return value;
}

uint32 verifyAndRead(char *line, HexInfo *hexinfo){
  int i= 0;
  int ptr = 9;
  
  //check colon
  if(line[0] != ':')
    catchError(ERR_NOT_COLON);
  
  //check length
  if(readHexNumber(&line[1], 2) > 0x10)
    catchError(ERR_WRONG_LENGTH);
  else
    hexinfo->length = readHexNumber(&line[1], 2);
  
  //check address
  if(readHexNumber(&line[3], 4) > 0x7530)
    catchError(ERR_WRONG_ADDRESS);
  else 
    hexinfo->address = readHexNumber(&line[3], 4);
  
  //check type
  if(readHexNumber(&line[7], 2) > 0x04)
    catchError(ERR_WRONG_TYPE);
  else 
    hexinfo->type = readHexNumber(&line[7], 2);
  
  while(i < (hexinfo->length)){
    
    hexinfo->data[i] = readHexNumber(&line[ptr], 2);
    i++;
    ptr = ptr + 2;
    
  }
  
  hexinfo->checkSum = 0x01 + (~((hexinfo->length) + sumData(hexinfo) + (hexinfo->type) + sumAddress(hexinfo))& 0x00ff);
  
  //check checksum
  if(hexinfo->checkSum != readHexNumber(&line[(((hexinfo->length)*2)+9)], 2)){
    catchError(ERR_WRONG_CHECKSUM);
  }
  
}

uint32 sumData(HexInfo *hexinfo){
  int i = 0;
  uint32 sum = 0;
  
  while(i < hexinfo->length){
    sum = hexinfo->data[i] + sum;
    i++;
  }
  
  return sum;

}

uint32 sumAddress(HexInfo *hexinfo){
  uint32 sum; 
  
  sum = ((hexinfo->address) >> 8) & 0x00ff;
  sum = sum + ((hexinfo->address) & 0x00ff);
  
  return sum;
}

void assertHexNumber(char *str, int numOfDigits){
  int i;
  char max = 'f';
  char min = '0';
 
  for(i = 0 ; i < numOfDigits ; i++){
    if((str[i] <= max) && (str[i] >= min)){}
    else{
      Throw(ERR_NOT_DIGIT);
      break;
    }
  }
}

void catchError(int error){
  switch(error){
    case ERR_NOT_DIGIT:
      printf("ERROR NOT DIGIT");
      break;
    case ERR_NOT_COLON:
      printf("ERROR NOT COLON");
      break;
    case ERR_WRONG_LENGTH:
      printf("ERROR WRONG LENGTH");
      break;
    case ERR_WRONG_ADDRESS:
      printf("ERROR WRONG ADDRESS");
      break;
    case ERR_WRONG_TYPE:
      printf("ERROR WRONG TYPE");
      break;
    case ERR_WRONG_CHECKSUM:
      printf("ERROR WRONG CHECKSUM");
      break; 
  
  }
}






