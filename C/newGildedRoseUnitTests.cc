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

      result = add_stock("This is a new normal item", 19, 23, NORMAL);
      CHECK_EQUAL(SUCCESS,result);

  }
  void teardown() {
     zero_list_size();
  }
};






TEST(TestGildedRoseGroup, FirstTest)
{
     FAIL("Fail me\n");

}


int main(int ac, char** av)
{

   return CommandLineTestRunner::RunAllTests(ac, av);
}
