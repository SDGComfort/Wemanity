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
      result = add_stock("Eye of Newt", 10, 10, NORMAL);
      CHECK_EQUAL(SUCCESS,result);
      result = add_stock("Backstage passes to a Tom Waits concert", 12, 20, TICKETS);
      CHECK_EQUAL(SUCCESS,result);
      result = add_stock("Conjured Mana cake", 3, 6, CONJURED);
      CHECK_EQUAL(SUCCESS,result);
  }
  void teardown() {
      int result;

      result = free_stock();
      CHECK_EQUAL(6,result);
  }
};

TEST(TestGildedRoseGroup, FirstTest)
{
     int index; //The count of items

     printf("Added the stock listed below\n");
     printf("---------------------------------------------\n");
     index = print_stock();
     CHECK_EQUAL(6,index);
}


TEST(TestGildedRoseGroup, SecondTest)
{
     int days = 5;
     int i;
     int sellIn, quality;
     const char* name;

     printf("Simulating 5 days\n");
     printf("=============================================\n");
     simulate_time(days);
     for (i=0; i<6;i++) {
         name = get_item_name(i);
         sellIn = get_item_sellIn(i);
         quality = get_item_quality(i);
         printf("Item %s: sellIn = %d,quality = %d\n",name, sellIn,quality);
     }
     
}



int main(int ac, char** av)
{

   return CommandLineTestRunner::RunAllTests(ac, av);
}
