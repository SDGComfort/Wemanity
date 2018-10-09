typedef struct
{
    char *name;
    int sellIn;
    int quality;
} Item;

#define SUCCESS 0
#define FAILED -1
#define MAX_ITEMS 20
#define MAX_QUALITY 50
#define MIN_QUALITY 0

enum TYPES{NORMAL,BRIE,LEGENDARY,TICKETS,CONJURED};

extern void initialize();
extern void list_stock();
extern void simulate_time();
