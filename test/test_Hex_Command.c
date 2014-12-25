#include "Hex_Command.h"
#include "Intel_Hex.h"
#include "unity.h"

void setUp(void){}
void tearDown(void){}

void test_getNextAddressAndData_should_get_data(){
  int command;
  HexInfo hexinfo = {.length = 16, .data = {':',1,0,0,0,1,3,0,0,0xc,1,0xc,1,2,0xa,0xd,1,3,0xa,0xe,1,0,0xa,0xf,1,1,1,2,0,0,2,0xf,8,0xe,0,0xe,8,0xf,0,0xf,2,2,4,4}, .type = 0, .address = 0x0013};
  
  command = getNextAddressAndData(&hexinfo);

  TEST_ASSERT_EQUAL(1, command);
}

void test_getNextAddressAndData_should_get_extend_address(){
  int command;
  HexInfo hexinfo = {.data = {':',0,2,0,0,0,0,0,4,0,0,2,0,0xd,0xa}, .length = 0x02 , .type = 0x04 ,.address = 0x0};
  
  command = getNextAddressAndData(&hexinfo);
  
  TEST_ASSERT_EQUAL(0x0020, command);

}