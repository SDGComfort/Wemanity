#include <CppUTest/TestHarness.h>
#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTestExt/MockSupport.h>

extern "C" {
#include "GildedRose.h"
}

static int stock_count = 0;

TEST_GROUP(TestGildedRoseGroup)
{
  void setup() {
      int result;

      result = add_stock("+5 Dexterity Vest", 19, 23, NORMAL);
      CHECK_EQUAL(SUCCESS,result);
      stock_count++;
      result = add_stock("Aged Brie", 5, 33, BRIE);
      CHECK_EQUAL(SUCCESS,result);
      stock_count++;
      result = add_stock("Sulfuras, Hand of Ragnaros", 0, 80, LEGENDARY);
      CHECK_EQUAL(SUCCESS,result);
      stock_count++;
      result = add_stock("Eye of Newt", 10, 10, NORMAL);
      CHECK_EQUAL(SUCCESS,result);
      stock_count++;
      result = add_stock("Backstage passes to a Tom Waits concert", 12, 20, TICKETS);
      CHECK_EQUAL(SUCCESS,result);
      stock_count++;
      result = add_stock("Conjured Mana cake", 3, 6, CONJURED);
      CHECK_EQUAL(SUCCESS,result);
      stock_count++;
  }
  void teardown() {
      int result;

      result = free_stock();
      CHECK_EQUAL(stock_count,result);
      stock_count = 0;
  }
};


TEST_GROUP(TestGildedRoseGroup2)
{
  void setup() {
  }
  void teardown() {
  }
};

TEST(TestGildedRoseGroup, FirstTest)
{
     int index; //The count of items

     printf("Added the stock listed below\n");
     printf("---------------------------------------------\n");
     index = print_stock();
     CHECK_EQUAL(stock_count,index);
}

TEST(TestGildedRoseGroup, SecondTest)
{
     int days = 12;
     int sellIn, quality;
     const char* name;

     printf("Simulating 12 days\n");
     printf("=============================================\n");
     simulate_time(days);


/* A long and tedious list of tests based entirely on the initial conditions and a 10 day sim */

     name = get_item_name(0);
     STRCMP_EQUAL("+5 Dexterity Vest", name);
     sellIn = get_item_sellIn(0);
     CHECK_EQUAL(7, sellIn);
     quality = get_item_quality(0);
     CHECK_EQUAL(11,quality);

/* Item 1 - Aged Brie  */

     name = get_item_name(1);
     STRCMP_EQUAL("Aged Brie", name);
     sellIn = get_item_sellIn(1);
     CHECK_EQUAL(-7, sellIn);
     quality = get_item_quality(1);
     CHECK_EQUAL(45,quality);

/* Item 2 Sulfuras blah di blah */

     name = get_item_name(2);
     STRCMP_EQUAL("Sulfuras, Hand of Ragnaros", name);
     sellIn = get_item_sellIn(2);
     CHECK_EQUAL(0, sellIn);
     quality = get_item_quality(2);
     CHECK_EQUAL(80,quality);

/* Item 3 Eye of Newt */

     name = get_item_name(3);
     STRCMP_EQUAL("Eye of Newt", name);
     sellIn = get_item_sellIn(3);
     CHECK_EQUAL(-2, sellIn);
     quality = get_item_quality(3);
     CHECK_EQUAL(0,quality);

/* Item 4 Backstage Passes */

     name = get_item_name(4);
     STRCMP_EQUAL("Backstage passes to a Tom Waits concert", name);
     sellIn = get_item_sellIn(4);
     CHECK_EQUAL(0, sellIn);
     quality = get_item_quality(4);
     CHECK_EQUAL(49,quality);

/* Item 5 Conjured Mana cake */

     name = get_item_name(5);
     STRCMP_EQUAL("Conjured Mana cake", name);
     sellIn = get_item_sellIn(5);
     CHECK_EQUAL(-9, sellIn);
     quality = get_item_quality(5);
     CHECK_EQUAL(0,quality); 
}


TEST(TestGildedRoseGroup2, validate_normal_rules)
{
     STOCK*  stock_ptr=NULL;
     int     sellIn, quality;
    
// Quality decreases by one per day */

     stock_ptr = test_business_rule("Wing of Bat", 1, 33, NORMAL);
     if (NULL != stock_ptr) {
        sellIn = stock_ptr->item.sellIn;
        quality = stock_ptr->item.quality;
        CHECK_EQUAL(0, sellIn);
        CHECK_EQUAL(32,quality);
        free(stock_ptr);
     }

// Quality cannot be < 0 */

     stock_ptr = test_business_rule("Wing of Bat", 1, 0, NORMAL);
     if (NULL != stock_ptr) {
        sellIn = stock_ptr->item.sellIn;
        quality = stock_ptr->item.quality;
        CHECK_EQUAL(0, sellIn);
        CHECK_EQUAL(0,quality);
        free(stock_ptr);
     }
}

TEST(TestGildedRoseGroup2, validate_brie_rules)
{
     STOCK*  stock_ptr=NULL;
     int     sellIn, quality;
    
// Quality increases by one per day */

     stock_ptr = test_business_rule("Test Aged Brie", 1, 33, BRIE);
     if (NULL != stock_ptr) {
        sellIn = stock_ptr->item.sellIn;
        quality = stock_ptr->item.quality;
        CHECK_EQUAL(0, sellIn);
        CHECK_EQUAL(34,quality);
        free(stock_ptr);
     }

// Quality cannot be > 50 */

     stock_ptr = test_business_rule("Test Aged Brie", 1, 50, BRIE);
     if (NULL != stock_ptr) {
        sellIn = stock_ptr->item.sellIn;
        quality = stock_ptr->item.quality;
        CHECK_EQUAL(0, sellIn);
        CHECK_EQUAL(50,quality);
        free(stock_ptr);
     }
}

TEST(TestGildedRoseGroup2, validate_backstage_rules)
{
     STOCK*  stock_ptr=NULL;
     int     sellIn, quality;
    
// Quality increases by one per day until 10 days to go */

     stock_ptr = test_business_rule("Backstage pass to Caetano Veloso concert", 12, 21, TICKETS);
     if (NULL != stock_ptr) {
        sellIn = stock_ptr->item.sellIn;
        quality = stock_ptr->item.quality;
        CHECK_EQUAL(11, sellIn);
        CHECK_EQUAL(22,quality);
        free(stock_ptr);
     }

// between 10 and 5 days, quality increases by 2 per day */

     stock_ptr = test_business_rule("Backstage pass to Caetano Veloso concert", 11, 24, TICKETS);
     if (NULL != stock_ptr) {
        sellIn = stock_ptr->item.sellIn;
        quality = stock_ptr->item.quality;
        CHECK_EQUAL(10, sellIn);
        CHECK_EQUAL(26,quality);
        free(stock_ptr);
     }
// From 5 to 0 days, quality increases by 3 per day */

     stock_ptr = test_business_rule("Backstage pass to Caetano Veloso concert", 6, 17, TICKETS);
     if (NULL != stock_ptr) {
        sellIn = stock_ptr->item.sellIn;
        quality = stock_ptr->item.quality;
        CHECK_EQUAL(5, sellIn);
        CHECK_EQUAL(20,quality);
        free(stock_ptr);
     }

// After show, quality is 0 */

     stock_ptr = test_business_rule("Backstage pass to Caetano Veloso concert", 0, 50, TICKETS);
     if (NULL != stock_ptr) {
        sellIn = stock_ptr->item.sellIn;
        quality = stock_ptr->item.quality;
        CHECK_EQUAL(-1, sellIn);
        CHECK_EQUAL(0,quality);
        free(stock_ptr);
     }

}

TEST(TestGildedRoseGroup2, validate_conjured_rules)
{
     STOCK*  stock_ptr=NULL;
     int     sellIn, quality;
    
// Quality decreases by 2 until seel by date */

     stock_ptr = test_business_rule("Djinn", 12, 10, CONJURED);
     if (NULL != stock_ptr) {
        sellIn = stock_ptr->item.sellIn;
        quality = stock_ptr->item.quality;
        CHECK_EQUAL(11, sellIn);
        CHECK_EQUAL(8,quality);
        free(stock_ptr);
     }

// After sell by date, quality decreases by 4 per day */

     stock_ptr = test_business_rule("Djinn", 0, 24, CONJURED);
     if (NULL != stock_ptr) {
        sellIn = stock_ptr->item.sellIn;
        quality = stock_ptr->item.quality;
        CHECK_EQUAL(-1, sellIn);
        CHECK_EQUAL(20,quality);
        free(stock_ptr);
     }

// Quality cannot be < 0 */

     stock_ptr = test_business_rule("Djinn", 0, 3, CONJURED);
     if (NULL != stock_ptr) {
        sellIn = stock_ptr->item.sellIn;
        quality = stock_ptr->item.quality;
        CHECK_EQUAL(-1, sellIn);
        CHECK_EQUAL(0,quality);
        free(stock_ptr);
     }
}

int main(int ac, char** av)
{

   return CommandLineTestRunner::RunAllTests(ac, av);
}
