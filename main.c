#include <stdio.h>

#include "inventory.h"

void printMenu() {
    printf("1. Load webshop store from a file\n");
    printf("2. Write the content of the store to a file\n");
    printf("3. Insert an item to cart\n");
    printf("4. Get the price of cart\n");
    printf("5. Buy the products\n");
    printf("6. Exit the program\n");
}

void loadStore(Inventory *store) {
    char filename[50];
    printf("Enter filename: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Failed to open file\n");
        return;
    }

    char name[50];
    float price;
    int quantity;
    while (fscanf(file, "%s %f %d", name, &price, &quantity) == 3) {
        insertProduct(store, name, price, quantity);
    }

    fclose(file);
}

void saveStore(Inventory *store) {
    char filename[50];
    printf("Enter filename: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Failed to open file\n");
        return;
    }

    for (int i = 0; i < store->size; i++) {
        fprintf(file, "%s %f %d\n", store->products[i].name, store->products[i].price, store->products[i].quantity);
    }

    fclose(file);
}

void insertToCart(Inventory *store, Inventory *cart) {
    char name[50];
    int quantity;
    printf("Enter product name: ");
    scanf("%s", name);
    printf("Enter quantity: ");
    scanf("%d", &quantity);

    int index = findProduct(store, name);
    if (index == -1) {
        printf("Product not found\n");
        return;
    }

    insertProduct(cart, name, store->products[index].price, quantity);
}

void getPriceOfCart(Inventory *cart) {
    float total = 0;
    for (int i = 0; i < cart->size; i++) {
        total += cart->products[i].price * cart->products[i].quantity;
    }
    printf("Total price: %.2f\n", total);
}

void buyProducts(Inventory *store, Inventory *cart) {
    for (int i = 0; i < cart->size; i++) {
        int index = findProduct(store, cart->products[i].name);
        if (index == -1 || store->products[index].quantity < cart->products[i].quantity) {
            printf("%d %s are missing\n", cart->products[i].quantity - store->products[index].quantity, cart->products[i].name);
        }
        removeProduct(store, cart->products[i].name, cart->products[i].quantity);
    }
    freeInventory(cart);
    initInventory(cart, 10);
}

int main() {
    Inventory store;
    initInventory(&store, 10);
    Inventory cart;
    initInventory(&cart, 10);

    int choice;
    do {
        printMenu();
        printf("--------------------\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            loadStore(&store);
            break;
        case 2:
            saveStore(&store);
            break;
        case 3:
            insertToCart(&store, &cart);
            break;
        case 4:
            getPriceOfCart(&cart);
            break;
        case 5:
            buyProducts(&store, &cart);
            break;
        case 6:
            break;
        default:
            printf("Invalid choice\n");
            break;
        }
    } while (choice != 6);

    freeInventory(&store);
    freeInventory(&cart);

    return 0;
}
