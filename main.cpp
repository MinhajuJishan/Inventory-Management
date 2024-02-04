#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
        strncpy(newNode->name, itemName, sizeof(newNode->name) - 1);
        newNode->name[sizeof(newNode->name) - 1] = '\0'; // Ensure null-termination
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
        printf("\nTask Completed Successfully.\n");
    } else {
        printf("\nFailed to add item. Memory allocation error.\n");
    }
}

// Function to remove an item from the inventory
void removeItem(struct Inventory* inventory, const char* itemName, int removeQuantity) {
    struct Node* current = inventory->head;
    struct Node* prev = NULL;

    while (current != NULL && strcmp(current->name, itemName) != 0) {
        prev = current;
        current = current->next;
    }

    if (current != NULL) {
        if (removeQuantity >= current->quantity) {
            // Remove the entire node
            if (prev != NULL) {
                prev->next = current->next;
            } else {
                inventory->head = current->next;
            }

            free(current);
            printf("\nTask Completed Successfully.\n");
        } else {
            // Remove a specific quantity
            current->quantity -= removeQuantity;
            printf("\nTask Completed Successfully.\n");
        }
    } else {
        printf("\nItem not found. Task failed.\n");
    }
}

// Function to update the quantity of an existing item
void updateItem(struct Inventory* inventory, const char* itemName) {
    struct Node* current = inventory->head;

    while (current != NULL && strcmp(current->name, itemName) != 0) {
        current = current->next;
    }

    if (current != NULL) {
        int updateQuantity;
        char operation[10];

        printf("Current quantity: %d\n", current->quantity);

        do {
            printf("Do you want to (A)dd or (S)ubtract quantity? ");
            if (scanf(" %9s", operation) != 1) {
                printf("Invalid input. Please enter 'A' or 'S'.\n");
                while (getchar() != '\n'); // Clear input buffer
            }
        } while (strcmp(operation, "A") != 0 && strcmp(operation, "a") != 0 &&
                 strcmp(operation, "S") != 0 && strcmp(operation, "s") != 0);

        do {
            printf("Enter quantity to update: ");
            if (scanf("%d", &updateQuantity) != 1) {
                printf("Invalid input. Please enter a valid number.\n");
                while (getchar() != '\n'); // Clear input buffer
            }
        } while (updateQuantity < 0);

        if (strcmp(operation, "A") == 0 || strcmp(operation, "a") == 0) {
            current->quantity += updateQuantity;
            printf("\nTask Completed Successfully.\n");
        } else if (strcmp(operation, "S") == 0 || strcmp(operation, "s") == 0) {
            if (updateQuantity <= current->quantity) {
                current->quantity -= updateQuantity;
                printf("\nTask Completed Successfully.\n");
            } else {
                printf("Invalid input. Cannot subtract more than the current quantity.\n");
            }
        } else {
            printf("Invalid operation. Task failed.\n");
        }
    } else {
        printf("\nItem not found. Task failed.\n");
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
    printf("\nInventory:\n");
    while (current != NULL) {
        printf("Name: %s, Quantity: %d\n", current->name, current->quantity);
        current = current->next;
    }
    printf("\nTask Completed Successfully.\n");
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
    int removeQuantity;

    do {
        printf("\n1. Add Item\n");
        printf("2. Remove Item\n");
        printf("3. Update Item Quantity\n");
        printf("4. Search Item\n");
        printf("5. Display Inventory\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");

        while (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a valid number.\n");
            while (getchar() != '\n'); // Clear input buffer
        }

        switch (choice) {
            case 1:
                printf("Enter item name: ");
                if (scanf("%49s", itemName) != 1) {
                    printf("Invalid input. Please enter a valid name.\n");
                    while (getchar() != '\n'); // Clear input buffer
                    break;
                }

                do {
                    printf("Enter quantity: ");
                    if (scanf("%d", &itemQuantity) != 1) {
                        printf("Invalid input. Please enter a valid number.\n");
                        while (getchar() != '\n'); // Clear input buffer
                    }
                } while (itemQuantity < 0);

                addItem(&inventory, itemName, itemQuantity);
                break;

            case 2:
                printf("Enter item name to remove: ");
                if (scanf("%49s", itemName) != 1) {
                    printf("Invalid input. Please enter a valid name.\n");
                    while (getchar() != '\n'); // Clear input buffer
                    break;
                }

                do {
                    printf("Enter quantity to remove: ");
                    if (scanf("%d", &removeQuantity) != 1) {
                        printf("Invalid input. Please enter a valid number.\n");
                        while (getchar() != '\n'); // Clear input buffer
                    }
                } while (removeQuantity < 0);

                removeItem(&inventory, itemName, removeQuantity);
                break;

            case 3:
                printf("Enter item name to update: ");
                if (scanf("%49s", itemName) != 1) {
                    printf("Invalid input. Please enter a valid name.\n");
                    while (getchar() != '\n'); // Clear input buffer
                    break;
                }
                updateItem(&inventory, itemName);
                break;

            case 4:
                printf("Enter item name to search: ");
                if (scanf("%49s", itemName) != 1) {
                    printf("Invalid input. Please enter a valid name.\n");
                    while (getchar() != '\n'); // Clear input buffer
                    break;
                }

                {
                    struct Node* result = searchItem(&inventory, itemName);
                    if (result != NULL) {
                        printf("Item found - Name: %s, Quantity: %d\n", result->name, result->quantity);
                    } else {
                        printf("Invalid input. Item not found.\n");
                    }
                }
                break;

            case 5:
                displayInventory(&inventory);
                break;

            case 6:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 6);

    // Free allocated memory before exiting
    freeInventory(&inventory);

    return 0;
}
