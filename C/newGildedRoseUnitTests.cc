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
      result = add_stock("Aged Brie", 5, 33, BRIE);
      CHECK_EQUAL(SUCCESS,result);
      result = add_stock("Sulfuras, Hand of Ragnaros", 0, 80, LEGENDARY);
      CHECK_EQUAL(SUCCESS,result);
      result = add_stock("Backstage passes to a Tom Waits concert", 12, 20, TICKETS);
      CHECK_EQUAL(SUCCESS,result);
      result = add_stock("Conjured Mana cake", 3, 6, CONJURED);
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
     CHECK_EQUAL(5,index);
}


int main(int ac, char** av)
{

   return CommandLineTestRunner::RunAllTests(ac, av);
}
