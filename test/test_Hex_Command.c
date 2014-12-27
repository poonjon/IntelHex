#include "Hex_Command.h"
#include "Intel_Hex.h"
#include "unity.h"

void setUp(void){}
void tearDown(void){}

void test_getNextAddressAndData_should_get_data(){
  int command;
  HexInfo hexinfo = {.length = 16, .data = {':',1,0,0,0,1,3,0,0,0xc,1,0xc,1,2,0xa,0xd,1,3,0xa,0xe,1,0,0xa,0xf,1,1,1,2,0,0,2,0xf,8,0xe,0,0xe,8,0xf,0,0xf,2,2,4,4}, .type = 0, .address = 0x0013};
  
  command = getNextAddressAndData(&hexinfo);

  TEST_ASSERT_EQUAL(0x0013, command);
}

//this test is linked to the next test
void test_getNextAddressAndData_should_linear_extend_address(){
  int command;
  HexInfo hexinfo = {.data = {':',0,2,0,0,0,0,0,4,2,0,0,0,0xd,0xa}, .length = 0x02 , .type = 0x04 ,.address = 0x0};
  
  command = getNextAddressAndData(&hexinfo);
  
  TEST_ASSERT_EQUAL(0x2000, command);

}

//this test is linked to the previous test
void test_getNextAddressAndData_should_add_extended_linear_address_to_original_address(){
  int command;
  HexInfo hexinfo = {.data = {':',1,0,1,2,3,4,0,0,5,4,6,8,6,9,7,3,2,0,7,0,6,1,7,2,7,4,2,0,6,9,7,3,2,0,6,9,6,0xe,2,0,2,8}, .length = 0x10 , .type = 0x00 ,.address = 0x1234};
  
  command = getNextAddressAndData(&hexinfo);
  
  TEST_ASSERT_EQUAL(0x20001234, command);

}

void test_getNextAddressAndData_should_extend_segment_address_and_add_to_original(){
  int command;
  HexInfo hexinfo = { .data = {':',0,2,0,0,0,0,0,2,2,0xb,0xc,0,1,1}, .length = 0x02, .type = 0x02, .address = 0}; 
  HexInfo hexinfo2 = { .data = {':',1,0,1,2,3,4,0,0,5,4,6,8,6,9,7,3,2,0,7,0,6,1,7,2,7,4,2,0,6,9,7,3,2,0,6,9,6,0xe,2,0,2,8}, .length = 0x10 , .type = 0x00, .address = 0x1234};

  command = getNextAddressAndData(&hexinfo);
  TEST_ASSERT_EQUAL(0x2bc0, command);
  
  command = getNextAddressAndData(&hexinfo2);
  TEST_ASSERT_EQUAL(0x2ce34, command);

}

void test_getNextAddressAndData_should_start_linear_address_and_replace_the_original(){
  int command;
  HexInfo hexinfo = { .data = {':',0,4,0,0,0,0,0,5,0,8,0,0,0,1,3,1,0xb,0xd}, .length = 0x04, .type = 0x05, .address = 0}; 
  HexInfo hexinfo2 = { .data = {':',1,0,1,2,3,4,0,0,5,4,6,8,6,9,7,3,2,0,7,0,6,1,7,2,7,4,2,0,6,9,7,3,2,0,6,9,6,0xe,2,0,2,8}, .length = 0x10 , .type = 0x00, .address = 0x1234};

  command = getNextAddressAndData(&hexinfo);
  TEST_ASSERT_EQUAL(0x08000131, command);
  
  command = getNextAddressAndData(&hexinfo2);
  TEST_ASSERT_EQUAL(0x08000131, command);

}

void test_getNextAddressAndData_should_start_segment_address_and_replace_the_original(){
  int command;
  HexInfo hexinfo = { .data = {':',0,4,0,0,0,0,0,3,0,2,0,0,0,1,3,0xa,0xb,0xc}, .length = 0x4, .type = 0x3, .address = 0}; 
  HexInfo hexinfo2 = { .data = {':',1,0,1,2,3,4,0,0,5,4,6,8,6,9,7,3,2,0,7,0,6,1,7,2,7,4,2,0,6,9,7,3,2,0,6,9,6,0xe,2,0,2,8}, .length = 0x10 , .type = 0x00, .address = 0x1234};

  command = getNextAddressAndData(&hexinfo);
  TEST_ASSERT_EQUAL(0x0200013a, command);
  
  command = getNextAddressAndData(&hexinfo2);
  TEST_ASSERT_EQUAL(0x0200013a, command);
}

void test_TLV_should_fascilitate_struct(){
  int command;
  HexInfo hexinfo = { .data = {':',0,4,0,0,0,0,0,3,0,2,0,0,0,1,3,0xa,0xb,0xc}, .length = 0x4, .type = 0x3, .address = 0}; 
  TLV tlv;
  command = getNextAddressAndData(&hexinfo);
  tlvData(&tlv, &hexinfo, command);
  
  TEST_ASSERT_EQUAL(0x03, tlv.type);
  TEST_ASSERT_EQUAL(0x04, tlv.length);
  TEST_ASSERT_EQUAL(0x0, tlv.data[0]);
  TEST_ASSERT_EQUAL(0x2, tlv.data[1]);
  TEST_ASSERT_EQUAL(0x0, tlv.data[2]);
  TEST_ASSERT_EQUAL(0x0, tlv.data[3]);
  TEST_ASSERT_EQUAL(0x0, tlv.data[4]);
  TEST_ASSERT_EQUAL(0x1, tlv.data[5]);
  TEST_ASSERT_EQUAL(0x3, tlv.data[6]);
  TEST_ASSERT_EQUAL(0xa, tlv.data[7]);
  
}


