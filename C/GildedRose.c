#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "GildedRose.h"



static int size = 0;
static Item items[MAX_ITEMS];
static int add_item(const char*, int, int);
static void print_item(Item);
static void update_quality();
static int identify_item(Item);
static void update_normal_item(int);
static void update_aged_brie(int);
static void update_legendary_item(int);
static void update_backstage_pass(int);
static void update_conjured_item(int);


void initialize()
{
    add_item("+5 Dexterity Vest",10,20);
    add_item("Aged Brie", 2, 0); 
    add_item("Elixir of the Mongoose", 5, 7);
    add_item("Sulfuras, Hand of Ragnaros", 0, 80);
    add_item("Sulfuras, Hand of Ragnaros", -1, 80);
    add_item("Backstage passes to a TAFKAL80ETC concert", 15,20);
    add_item("Backstage passes to a TAFKAL80ETC concert", 10, 49);
    add_item("Backstage passes to a TAFKAL80ETC concert", 5, 49);
    add_item("Conjured Mana cake",3,6);
}

void list_stock()
{
    int i;
    for(i=0;i<size;i++)
       print_item(items[i]);
}  

void simulate_time(int days)
{
    int day;

    for(day=0;day<days;day++){
       update_quality();
       list_stock();
    }
}

void zero_list_size()
{
    size = 0;
}

int test_add_item(const char* name, int sellIn, int quality)
{
    int result; 

    result = add_item(name, sellIn, quality);
    return result;
}

static int add_item(const char* name, int sellIn, int quality){
    
    if (size >= MAX_ITEMS) return FAILED;
    items[size].name = strdup(name);
    items[size].sellIn = sellIn;
    items[size++].quality = quality; 
    return size;
}


static void print_item(Item item)
{
    printf("Name = %s SellIn = %d  Quality = %d\n",item.name,item.sellIn,item.quality); 
}

static void update_quality()
{
    int i;
    int type; 

    for(i=0;i<size;i++){
       type = identify_item(items[i]);
       switch (type) {
          case NORMAL:    update_normal_item(i);break;
          case BRIE:      update_aged_brie(i);break;
          case LEGENDARY: update_legendary_item(i);break;
          case TICKETS:   update_backstage_pass(i);break;
          case CONJURED:  update_conjured_item(i);break;
          default:        break;
       }
    }
}

static int identify_item(Item item)
{
    if (0 == strcmp(item.name,"+5 Dexterity Vest")){
       return NORMAL;
    }
    if (0 == strcmp(item.name, "Elixir of the Mongoose")){
       return NORMAL;
    }
    if (0 == strcmp(item.name, "Aged Brie")){
       return BRIE; 
    }
    if (0 == strcmp(item.name, "Sulfuras, Hand of Ragnaros")){
       return LEGENDARY;
    }
    if (0 == strcmp(item.name, "Backstage passes to a TAFKAL80ETC concert")){
       return TICKETS;
    }
    if (0 == strcmp(item.name, "Conjured Mana cake")){
       return CONJURED;
    }
    return -1;
}

void test_update_normal_item (int i)
{
    update_normal_item(i);
}

int get_item_sellIn (int i)
{
    return items[i].sellIn;
}

int get_item_quality (int i)
{
    return items[i].quality;
}

static void update_normal_item(int i)
{
    items[i].sellIn--;
    if ((items[i].sellIn >= 0) && (items[i].quality > 0)) items[i].quality--;
    else if ((items[i].sellIn < 0) && (items[i].quality > 0)) items[i].quality -= 2;
    if (items[i].quality < 0) items[i].quality = 0;
}

static void update_aged_brie(int i)
{
    items[i].sellIn--;
    items[i].quality++;
    if (items[i].quality > 50) items[i].quality = 50;
}

static void update_legendary_item(int i)
{
    if (items[i].quality != 80) items[i].quality = 80;
}

static void update_backstage_pass(int i)
{
    items[i].sellIn--;
    if (items[i].sellIn > 10) items[i].quality++;
    else if ((items[i].sellIn <= 10) && (items[i].sellIn > 6)) items[i].quality +=2;
    else if ((items[i].sellIn <=6) && (items[i].sellIn >= 0)) items[i].quality +=3;
    else if (items[i].sellIn < 0) items[i].quality = 0;
    if (items[i].quality > 50) items[i].quality = 50;
}

static void update_conjured_item(int i)
{
    items[i].sellIn--;
    if ((items[i].sellIn >= 0) && (items[i].quality > 0)) items[i].quality -= 2;
    else if ((items[i].sellIn < 0) && (items[i].quality > 0)) items[i].quality -=4;
    if (items[i].quality < 0) items[i].quality = 0;

}

