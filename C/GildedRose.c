#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "GildedRose.h"
    

static void update_quality();
static void do_update(int, STOCK*);
static void update_normal_item(STOCK*);
static void update_aged_brie(STOCK*);
static void update_legendary_item(STOCK*);
static void update_backstage_pass(STOCK*);
static void update_conjured_item(STOCK*);

static STOCK* stock_ptr;
static STOCK* start_ptr;

int add_stock(const char* name, int sellIn, int quality, int type)
{
    if (NULL == stock_ptr) {
       stock_ptr = (STOCK*)malloc(sizeof(STOCK));
       start_ptr = stock_ptr;
    }
    else if (NULL == stock_ptr->next) {
       stock_ptr->next = (STOCK*)malloc(sizeof(STOCK));
       if (NULL != stock_ptr->next) {
          stock_ptr = stock_ptr->next;
       }
       else return FAILED;
    }
    if (NULL != stock_ptr){
       stock_ptr->item.name = strdup(name);
       stock_ptr->item.sellIn = sellIn;
       stock_ptr->item.quality = quality;
       stock_ptr->type = type;
       stock_ptr->next = NULL;
       return SUCCESS;
    }
    else return FAILED;
}

int free_stock()
{
    STOCK* next_ptr;
    STOCK* prev_ptr;
    int    count = 0;

    if (NULL!= start_ptr) {
       next_ptr = start_ptr -> next;
       free(start_ptr);
       count++;
       while (NULL != next_ptr) {
          prev_ptr = next_ptr;
          next_ptr = next_ptr -> next;
          free(prev_ptr);
          count++;
       }
       return (count);
    }
    else return FAILED;
}

int print_stock()
{
    int items = 0;

    stock_ptr = start_ptr;
    while (NULL != stock_ptr) {
       printf("Name = %s, Sellin = %d, Quality = %d, Type = %d\n",
               stock_ptr->item.name, stock_ptr->item.sellIn, stock_ptr->item.quality,stock_ptr->type);
       stock_ptr = stock_ptr->next;
       items++;
    }
    return items;
}


int initialize()
{
      int result;

      result = add_stock("+5 Dexterity Vest", 19, 23, NORMAL);
      result = add_stock("Aged Brie", 5, 33, BRIE);
      result = add_stock("Sulfuras, Hand of Ragnaros", 0, 80, LEGENDARY);
      result = add_stock("Backstage passes to a Tom Waits concert", 12, 20, TICKETS);
      result = add_stock("Conjured Mana cake", 3, 6, CONJURED);
      return result;
}


void simulate_time(int days)
{
    int day;

    for(day=0;day<days;day++){
       update_quality();
    }
    print_stock();
}

static void do_update(int type, STOCK* item_ptr)
{
   switch (type) {
      case NORMAL:    update_normal_item(item_ptr);break;
      case BRIE:      update_aged_brie(item_ptr);break;
      case LEGENDARY: update_legendary_item(item_ptr);break;
      case TICKETS:   update_backstage_pass(item_ptr);break;
      case CONJURED:  update_conjured_item(item_ptr);break;
      default:        break;
   }
}

static void update_quality()
{
    STOCK* next_ptr;
    int    type = -1;

    if (NULL!= start_ptr) {
       next_ptr = start_ptr->next;
       type = start_ptr->type; 
       do_update(type, start_ptr);
       while (NULL != next_ptr) {
          type = next_ptr->type;
          do_update(type, next_ptr);
          next_ptr = next_ptr->next;
       }  
    }
}

int get_item_sellIn (int i)
{
    int index =0;
    STOCK* item_ptr = start_ptr;

    if (0 == i) return item_ptr->item.sellIn;
    else {
       for (index=0; index<i;index++) {
          item_ptr = item_ptr -> next;
       }
    }
    return item_ptr->item.sellIn;
}

const char* get_item_name (int i)
{
    int index =0;
    STOCK* item_ptr = start_ptr;

    if (0 == i) return item_ptr->item.name;
    else {
       for (index=0; index<i;index++) {
          item_ptr = item_ptr -> next;
       }
    }
    return item_ptr->item.name;
}

int get_item_quality (int i)
{
    int index =0;
    STOCK* item_ptr = start_ptr;

    if (0 == i) return item_ptr->item.quality;
    else {
       for (index=0; index<i;index++) {
          item_ptr = item_ptr -> next;
       }
    }
    return item_ptr->item.quality;
}

static void update_normal_item(STOCK* item_ptr)
{
    item_ptr->item.sellIn--;
    if ((item_ptr->item.sellIn >= 0) && (item_ptr->item.quality > 0)) item_ptr->item.quality--;
    else if ((item_ptr->item.sellIn < 0) && (item_ptr->item.quality > 0)) item_ptr->item.quality -= 2;
    if (item_ptr->item.quality < 0) item_ptr->item.quality = 0;
}

static void update_aged_brie(STOCK* item_ptr)
{
    item_ptr->item.sellIn--;
    item_ptr->item.quality++;
    if (item_ptr->item.quality > 50) item_ptr->item.quality = 50;
}

static void update_legendary_item(STOCK* item_ptr)
{
    if (item_ptr->item.quality != 80) item_ptr->item.quality = 80;
}

static void update_backstage_pass(STOCK* item_ptr)
{
    item_ptr->item.sellIn--;
    if (item_ptr->item.sellIn > 10) item_ptr->item.quality++;
    else if ((item_ptr->item.sellIn <= 10) && (item_ptr->item.sellIn >= 6)) item_ptr->item.quality +=2;
    else if ((item_ptr->item.sellIn <=5) && (item_ptr->item.sellIn >= 0)) item_ptr->item.quality +=3;
    else if (item_ptr->item.sellIn < 0) item_ptr->item.quality = 0;
    if (item_ptr->item.quality > 50) item_ptr->item.quality = 50;
}

static void update_conjured_item(STOCK* item_ptr)
{
    item_ptr->item.sellIn--;
    if ((item_ptr->item.sellIn >= 0) && (item_ptr->item.quality > 0)) item_ptr->item.quality -= 2;
    else if ((item_ptr->item.sellIn < 0) && (item_ptr->item.quality > 0)) item_ptr->item.quality -=4;
    if (item_ptr->item.quality < 0) item_ptr->item.quality = 0;

}

