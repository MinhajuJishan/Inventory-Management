#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node structure to represent each inventory item
struct Node {
    char name[50];
    int quantity;
    struct Node* next;
};

// LinkedList structure to manage items
struct Inventory {
    struct Node* head;
};

// Function to create a new node
struct Node* createNode(const char* itemName, int itemQuantity) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode != NULL) {
        strcpy(newNode->name, itemName);
        newNode->quantity = itemQuantity;
        newNode->next = NULL;
    }
    return newNode;
}

// Function to add a new item to the inventory
void addItem(struct Inventory* inventory, const char* itemName, int quantity) {
    struct Node* newNode = createNode(itemName, quantity);
    if (newNode != NULL) {
        newNode->next = inventory->head;
        inventory->head = newNode;
    }
}

// Function to remove an item from the inventory
void removeItem(struct Inventory* inventory, const char* itemName) {
    struct Node* current = inventory->head;
    struct Node* prev = NULL;

    while (current != NULL && strcmp(current->name, itemName) != 0) {
        prev = current;
        current = current->next;
    }

    if (current != NULL) {
        if (prev != NULL) {
            prev->next = current->next;
        } else {
            inventory->head = current->next;
        }

        free(current);
    }
}

// Function to search for an item in the inventory
struct Node* searchItem(const struct Inventory* inventory, const char* itemName) {
    struct Node* current = inventory->head;

    while (current != NULL) {
        if (strcmp(current->name, itemName) == 0) {
            return current;
        }
        current = current->next;
    }

    return NULL; // Item not found
}

// Function to display all items in the inventory
void displayInventory(const struct Inventory* inventory) {
    struct Node* current = inventory->head;
    printf("Inventory:\n");
    while (current != NULL) {
        printf("Name: %s, Quantity: %d\n", current->name, current->quantity);
        current = current->next;
    }
}

// Function to free memory allocated for the linked list
void freeInventory(struct Inventory* inventory) {
    struct Node* current = inventory->head;
    struct Node* nextNode;

    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    inventory->head = NULL;
}

int main() {
    struct Inventory inventory;
    inventory.head = NULL;

    // Interactive menu
    int choice;
    char itemName[50];
    int itemQuantity;

    do {
        printf("\n1. Add Item\n");
        printf("2. Remove Item\n");
        printf("3. Search Item\n");
        printf("4. Display Inventory\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter item name: ");
                scanf("%s", itemName);
                printf("Enter quantity: ");
                scanf("%d", &itemQuantity);
                addItem(&inventory, itemName, itemQuantity);
                break;

            case 2:
                printf("Enter item name to remove: ");
                scanf("%s", itemName);
                removeItem(&inventory, itemName);
                break;

            case 3:
                printf("Enter item name to search: ");
                scanf("%s", itemName);
                {
                    struct Node* result = searchItem(&inventory, itemName);
                    if (result != NULL) {
                        printf("Item found - Name: %s, Quantity: %d\n", result->name, result->quantity);
                    } else {
                        printf("Item not found.\n");
                    }
                }
                break;

            case 4:
                displayInventory(&inventory);
                break;

            case 5:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 5);

    // Free allocated memory before exiting
    freeInventory(&inventory);

    return 0;
}
