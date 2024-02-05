#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Node {
    char name[50];
    int quantity;
    struct Node* next;
};

struct Inventory {
    struct Node* head;
};

struct Node* createNode(const char* itemName, int itemQuantity) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode != NULL) {
        strncpy(newNode->name, itemName, sizeof(newNode->name) - 1);
        newNode->name[sizeof(newNode->name) - 1] = '\0';
        newNode->quantity = itemQuantity;
        newNode->next = NULL;
    }
    return newNode;
}


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

void removeItem(struct Inventory* inventory, const char* itemName, int removeQuantity) {
    struct Node* current = inventory->head;
    struct Node* prev = NULL;

    while (current != NULL && strcmp(current->name, itemName) != 0) {
        prev = current;
        current = current->next;
    }

    if (current != NULL) {
        if (removeQuantity >= current->quantity) {
            if (prev != NULL) {
                prev->next = current->next;
            } else {
                inventory->head = current->next;
            }

            free(current);
            printf("\nTask Completed Successfully.\n");
        } else {

            current->quantity -= removeQuantity;
            printf("\nTask Completed Successfully.\n");
        }
    } else {
        printf("\nItem not found. Task failed.\n");
    }
}

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
                while (getchar() != '\n');
            }
        } while (strcmp(operation, "A") != 0 && strcmp(operation, "a") != 0 &&
                 strcmp(operation, "S") != 0 && strcmp(operation, "s") != 0);

        do {
            printf("Enter quantity to update: ");
            if (scanf("%d", &updateQuantity) != 1) {
                printf("Invalid input. Please enter a valid number.\n");
                while (getchar() != '\n');
            } else if (updateQuantity < 0) {
                printf("Invalid input. Quantity should be a non-negative number.\n");
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

struct Node* searchItem(const struct Inventory* inventory, const char* itemName) {
    struct Node* current = inventory->head;

    while (current != NULL) {
        if (strcmp(current->name, itemName) == 0) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

void displayInventory(const struct Inventory* inventory) {
    struct Node* current = inventory->head;
    printf("\nInventory:\n");
    while (current != NULL) {
        printf("Name: %s, Quantity: %d\n", current->name, current->quantity);
        current = current->next;
    }
    printf("\nTask Completed Successfully.\n");
}

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

    int choice;
    char itemName[50];
    int itemQuantity;
    int removeQuantity;

    printf("Welcome! Please enter the password to log in.\n");

    char adminUsername[] = "inventory";
    char adminPassword[] = "123456";
    char enteredUsername[50];
    char enteredPassword[7];

    printf("Username: %s\n", adminUsername);
    printf("Password (6 digits): ");

    while (scanf("%6s", enteredPassword) != 1 || strcmp(adminPassword, enteredPassword) != 0) {
        printf("Invalid password. Please try again.\nPassword (6 digits): ");
        while (getchar() != '\n');
    }

    printf("\nAdmin login successful.\n");

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
            while (getchar() != '\n');
        }

        switch (choice) {
            case 1:
                printf("Enter item name: ");
                if (scanf("%49s", itemName) != 1) {
                    printf("Invalid input. Please enter a valid name.\n");
                    while (getchar() != '\n');
                    break;
                }

                do {
                    printf("Enter quantity: ");
                    if (scanf("%d", &itemQuantity) != 1) {
                        printf("Invalid input. Please enter a valid number.\n");
                        while (getchar() != '\n');
                    }
                } while (itemQuantity < 0);

                addItem(&inventory, itemName, itemQuantity);
                break;

            case 2:
                printf("Enter item name to remove: ");
                if (scanf("%49s", itemName) != 1) {
                    printf("Invalid input. Please enter a valid name.\n");
                    while (getchar() != '\n');
                    break;
                }

                do {
                    printf("Enter quantity to remove: ");
                    if (scanf("%d", &removeQuantity) != 1) {
                        printf("Invalid input. Please enter a valid number.\n");
                        while (getchar() != '\n');
                    }
                } while (removeQuantity < 0);

                removeItem(&inventory, itemName, removeQuantity);
                break;

            case 3:
                printf("Enter item name to update: ");
                if (scanf("%49s", itemName) != 1) {
                    printf("Invalid input. Please enter a valid name.\n");
                    while (getchar() != '\n');
                    break;
                }
                updateItem(&inventory, itemName);
                break;

            case 4:
                printf("Enter item name to search: ");
                if (scanf("%49s", itemName) != 1) {
                    printf("Invalid input. Please enter a valid name.\n");
                    while (getchar() != '\n');
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


    freeInventory(&inventory);

    return 0;
}
