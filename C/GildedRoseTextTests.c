#include <stdio.h>
#include "GildedRose.h"

int
print_item(Item *item)
{
    return printf("%s, %d, %d\n", item->name, item->sellIn, item->quality);
}

int main()
{
    initialize(); 
    list_stock(); 
    simulate_time();
    return 0;
}
