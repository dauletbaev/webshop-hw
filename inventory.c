#include <stdlib.h>
#include <string.h>

#include "inventory.h"

void initInventory(Inventory *inventory, int initialCapacity) {
    inventory->products = malloc(initialCapacity * sizeof(Product));
    inventory->size = 0;
    inventory->capacity = initialCapacity;
}

void freeInventory(Inventory *inventory) {
    free(inventory->products);
    inventory->products = NULL;
    inventory->size = 0;
    inventory->capacity = 0;
}

int findProduct(Inventory *inventory, const char *name) {
    for (int i = 0; i < inventory->size; i++) {
        if (strcmp(inventory->products[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

void resizeInventory(Inventory *inventory, int newCapacity) {
    Product *newProducts = malloc(newCapacity * sizeof(Product));
    memcpy(newProducts, inventory->products, inventory->size * sizeof(Product));
    free(inventory->products);
    inventory->products = newProducts;
    inventory->capacity = newCapacity;
}

void insertProduct(Inventory *inventory, const char *name, float price, int quantity) {
    int index = findProduct(inventory, name);
    if (index != -1) {
        inventory->products[index].quantity += quantity;
    } else {
        if (inventory->size == inventory->capacity) {
            resizeInventory(inventory, inventory->capacity * 2);
        }
        strcpy(inventory->products[inventory->size].name, name);
        inventory->products[inventory->size].price = price;
        inventory->products[inventory->size].quantity = quantity;
        inventory->size++;
    }
}

void removeProduct(Inventory *inventory, const char *name, int quantity) {
    int index = findProduct(inventory, name);
    if (index != -1) {
        inventory->products[index].quantity -= quantity;
        if (inventory->products[index].quantity < 0) {
            inventory->products[index].quantity = 0;
        }
    }
}
