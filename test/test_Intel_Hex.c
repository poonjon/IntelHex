#include "Intel_Hex.h"
#include <stdio.h>
#include "Type.h"
#include "CException.h"
#include "ErrorCode.h"
#include "unity.h"

void setUp(void){}
void tearDown(void){}
void test_explore_sscanf(){
 char sentence []="Rudolph is years 12 old";
  char name [20];
  char year [20];
  char old [20];
  int i;
  int value;
  
  value = sscanf (&sentence[0],"%2s %s %s ",name, year, old );
  printf ("%s %s %s \n",name, year, old );
  printf("%d", value);
}

void test_assertHexNumber_read_8a_should_not_throw(){
  char data[20] = ":1230148ab";
  CEXCEPTION_T e;
  int numOfCharToRead = 2;
  Try{
    assertHexNumber(&data[7], numOfCharToRead);
  }Catch(e){
    TEST_ASSERT_EQUAL(ERR_NOT_DIGIT, e);
  }
}

void test_assertHexNumber_read_8ah_should_throw(){
  char data[20] = ":1230148ahb";
  CEXCEPTION_T e;
  int numOfCharToRead = 4;
  Try{
    assertHexNumber(&data[7], numOfCharToRead);
  }Catch(e){
    TEST_ASSERT_EQUAL(ERR_NOT_DIGIT, e);
  }
}

void test_assertHexNumber_read_abcdef_should_pass(){
  char data[20] = ":abcd";
  CEXCEPTION_T e;
  int numOfCharToRead = 4;
  Try{
    assertHexNumber(&data[1], numOfCharToRead);
  }Catch(e){
    TEST_ASSERT_EQUAL(ERR_NOT_DIGIT, e);
  }
}

void test_assertHexNumber_read_8a56bd_should_not_throw(){
  char data[20] = ":8A56BD";
  CEXCEPTION_T e;
  int numOfCharToRead = 4;
  Try{
    assertHexNumber(&data[1], numOfCharToRead);
  }Catch(e){
    TEST_ASSERT_EQUAL(ERR_NOT_DIGIT, e);
  }
}

void test_assertHexNumber_read_y8a56bd_should_throw(){
  char data[20] = ":y8a56bd";
  CEXCEPTION_T e;
  int numOfCharToRead = 7;
  Try{
    assertHexNumber(&data[1], numOfCharToRead);
  }Catch(e){
    TEST_ASSERT_EQUAL(ERR_NOT_DIGIT, e);
  }
}

void test_readHexNumber_should_read_12_return_12(){
  char data[20] = ":12";
  CEXCEPTION_T e;
  uint16 numOfCharToRead = 2, value;
  
  Try{
    value = readHexNumber(&data[1], numOfCharToRead);
    TEST_ASSERT_EQUAL(18, value);
  }Catch(e){
    TEST_ASSERT_EQUAL(ERR_NOT_DIGIT, e);
  }

}

void test_readHexNumber_should_read_654abc_return_0x654abc(){
  char data[20] = ":654abc";
  CEXCEPTION_T e;
  uint16 value, numOfCharToRead = 4;
  
  Try{
    value = readHexNumber(&data[1], numOfCharToRead);
    TEST_ASSERT_EQUAL(0x654a, value);
  }Catch(e){
    TEST_ASSERT_EQUAL(ERR_NOT_DIGIT, e);
  }
}

void test_readHexNumber_should_read_6a8c55b_return_8c(){
  char data[20] = ":6a8c55b";
  CEXCEPTION_T e;
  uint16 value, numOfCharToRead = 2;
  
  Try{
    value = readHexNumber(&data[3], numOfCharToRead);
    TEST_ASSERT_EQUAL(0x8c, value);
  }Catch(e){
    TEST_ASSERT_EQUAL(ERR_NOT_DIGIT, e);
  }
}

void test_verifyAndRead_should_read_10001300AC12AD13AE10AF1112002F8E0E8F0F2244(){
  HexInfo hexinfo;
    CEXCEPTION_T e;
  char str[] = ":10001300AC12AD13AE10AF1112002F8E0E8F0F2244"; 
  Try{
    verifyAndRead(str, &hexinfo);
    TEST_ASSERT_EQUAL(0x10,hexinfo.length);
    TEST_ASSERT_EQUAL(0x00,hexinfo.type);
    TEST_ASSERT_EQUAL(0x0013,hexinfo.address);
    TEST_ASSERT_EQUAL(0x44,hexinfo.checkSum);
    
  }Catch(e){
    TEST_ASSERT_EQUAL(8, e);
  }
}

 void test_verifyAndRead_should_read_020000021200EA(){
  HexInfo hexinfo;
    CEXCEPTION_T e;

  char str[] = ":020000021200EA"; 
  Try{
    verifyAndRead(str, &hexinfo);
    TEST_ASSERT_EQUAL(0x2,hexinfo.length);
    TEST_ASSERT_EQUAL(0x2,hexinfo.type);
    TEST_ASSERT_EQUAL(0x0,hexinfo.address);
    TEST_ASSERT_EQUAL(0xea,hexinfo.checkSum);
    
  }Catch(e){
    TEST_ASSERT_EQUAL(8, e);
  }
}

void test_sumData_should_return_16(){
  int sum; 
  HexInfo hexinfo = {.length = 4};
  hexinfo.data[0] = 2;
  hexinfo.data[1] = 5;
  hexinfo.data[2] = 6;
  hexinfo.data[3] = 3;
  sum = sumData(&hexinfo);
  
  TEST_ASSERT_EQUAL(0x10, sum);
  
}

void test_sumAddress_should_return_16(){
  int sum; 
  HexInfo hexinfo = {.address = 0x0808};

  sum = sumAddress(&hexinfo);
  
  TEST_ASSERT_EQUAL(16, sum);
  
}

 //:10204E0029D00229D6022A1402287D02284302270B
 // ^ ^   ^ ^                               ^
 // | |   | |                               |
 // | |   | |       checksum----------------+
 // | |   | +-------data bytes
 // | |   +---------record type (00=data, 01=end of file) 
 // | +-------------address for this line of data
 // +---------------number of bytes of data in this line
 




