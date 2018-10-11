#include <CppUTest/TestHarness.h>
#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTestExt/MockSupport.h>

extern "C" {
#include "GildedRose.h"
}

/* MAX_LIST must be set to 5 for these tests to work. */ 
/* We have to check business rules for 5 items. These tests are still a bit clunky
   e.g. Should not have hard coded array indices based on prior knowledge */
/* Repetitive tests should be in a loop with some if else logic - leaving as is for simplicity */

TEST_GROUP(TestGildedRoseGroup)
{
  void setup() {
     int list_size = 0;

     list_size = test_add_item("+5 Dexterity Vest",5,7);
     list_size = test_add_item("Aged Brie", 2, 0); 
     list_size = test_add_item("Sulfuras, Hand of Ragnaros", 0, 80);
     list_size = test_add_item("Backstage passes to a TAFKAL80ETC concert", 15, 20);
     list_size = test_add_item("Conjured Mana cake",3,6);
  }
  void teardown() {
     zero_list_size();
  }
};

TEST(TestGildedRoseGroup, FirstTest)
{
    int list_size;

/* We expect FAILED (-1) when adding the another item */

    list_size = test_add_item("This should fail", 0, 80);
    CHECK_EQUAL(FAILED, list_size);
}

TEST(TestGildedRoseGroup, SecondTest)
{
/* Normal Item Quality decreases linearly, cannot be below 0 */
/* When sellby date is passed, quality degrades twice as fast. */

   int sellIn;
   int quality;

   test_update_normal_item(0);
   sellIn = get_item_sellIn(0);
   CHECK_EQUAL(4,sellIn);
   quality = get_item_quality(0);
   CHECK_EQUAL(6,quality);

   test_update_normal_item(0);
   sellIn = get_item_sellIn(0);
   CHECK_EQUAL(3,sellIn);
   quality = get_item_quality(0);
   CHECK_EQUAL(5,quality);

   test_update_normal_item(0);
   sellIn = get_item_sellIn(0);
   CHECK_EQUAL(2,sellIn);
   quality = get_item_quality(0);
   CHECK_EQUAL(4,quality);

   test_update_normal_item(0);
   sellIn = get_item_sellIn(0);
   CHECK_EQUAL(1,sellIn);
   quality = get_item_quality(0);
   CHECK_EQUAL(3,quality);

   test_update_normal_item(0);
   sellIn = get_item_sellIn(0);
   CHECK_EQUAL(0,sellIn);
   quality = get_item_quality(0);
   CHECK_EQUAL(2,quality);

   test_update_normal_item(0);
   sellIn = get_item_sellIn(0);
   CHECK_EQUAL(-1,sellIn);
   quality = get_item_quality(0);
   CHECK_EQUAL(0,quality);

   test_update_normal_item(0);
   sellIn = get_item_sellIn(0);
   CHECK_EQUAL(-2,sellIn);
   quality = get_item_quality(0);
   CHECK_EQUAL(0,quality);
}

int main(int ac, char** av)
{
  return CommandLineTestRunner::RunAllTests(ac, av);
}
