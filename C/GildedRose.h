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
#define MAX_QUALITY 50
#define MIN_QUALITY 0

enum TYPES{NORMAL,BRIE,LEGENDARY,TICKETS,CONJURED};

extern int  initialize();
extern int  print_stock();
extern int  free_stock();
extern void simulate_time(int);
extern int  add_stock(const char*, int, int, int);
extern int get_item_sellIn (int);
extern int get_item_quality (int);
extern const char* get_item_name (int);
extern STOCK* test_business_rule(const char*, int, int, int);



