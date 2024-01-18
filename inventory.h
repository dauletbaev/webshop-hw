#include "product.h"

typedef struct {
    Product *products;
    int size;
    int capacity;
} Inventory;

void initInventory(Inventory *inventory, int initialCapacity);
void freeInventory(Inventory *inventory);
int findProduct(Inventory *inventory, const char *name);
void resizeInventory(Inventory *inventory, int newCapacity);
void insertProduct(Inventory *inventory, const char *name, float price, int quantity);
void removeProduct(Inventory *inventory, const char *name, int quantity);
