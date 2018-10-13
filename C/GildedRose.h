typedef struct
{
    char *name;
    int sellIn;
    int quality;
} Item;

typedef struct stock{
    Item  item;
    int	  type;
    struct stock* next;
}STOCK;

#define SUCCESS 0
#define FAILED -1
#define MAX_ITEMS 5
#define MAX_QUALITY 50
#define MIN_QUALITY 0

enum TYPES{NORMAL,BRIE,LEGENDARY,TICKETS,CONJURED};

extern void initialize();
extern void list_stock();
extern int  print_stock();
extern int  free_stock();


extern void simulate_time(int);
extern int add_stock(const char*, int, int, int);
extern int test_add_item(const char*,int, int);
extern void test_update_normal_item (int);
extern int get_item_sellIn (int);
extern int get_item_quality (int);
extern void zero_list_size();
extern void test_update_brie(int);
extern void test_update_legendary (int);
extern void test_update_tickets(int);
extern void test_update_conjured (int);

