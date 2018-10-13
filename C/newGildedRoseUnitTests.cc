#include <CppUTest/TestHarness.h>
#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTestExt/MockSupport.h>

extern "C" {
#include "GildedRose.h"
}

TEST_GROUP(TestGildedRoseGroup)
{
  void setup() {
      int result;

      result = add_stock("+5 Dexterity Vest", 19, 23, NORMAL);
      CHECK_EQUAL(SUCCESS,result);
      result = add_stock("Aged Brie", 19, 23, BRIE);
      CHECK_EQUAL(SUCCESS,result);


  }
  void teardown() {
     zero_list_size();
  }
};






TEST(TestGildedRoseGroup, FirstTest)
{
     int index; //The count of items

     index = print_stock();
     CHECK_EQUAL(2,index);
}


int main(int ac, char** av)
{

   return CommandLineTestRunner::RunAllTests(ac, av);
}
