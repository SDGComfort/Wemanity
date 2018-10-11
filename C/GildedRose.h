typedef struct
{
    char *name;
    int sellIn;
    int quality;
} Item;

#define SUCCESS 0
#define FAILED -1
#define MAX_ITEMS 5
#define MAX_QUALITY 50
#define MIN_QUALITY 0

enum TYPES{NORMAL,BRIE,LEGENDARY,TICKETS,CONJURED};

extern void initialize();
extern void list_stock();
extern void simulate_time(int);
extern int test_add_item(const char*,int, int);
extern void test_update_normal_item (int);
extern int get_item_sellIn (int);
extern int get_item_quality (int);
extern void zero_list_size();
extern void test_update_brie(int);
extern void test_update_legendary (int);


