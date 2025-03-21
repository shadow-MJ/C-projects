#include <stdio.h>
#include <stdlib.h>

void addItem();
void displayItems();
void searchItem();
void editItem();
void deleteItem();
void exitProgram();

int main()
{
    int choice;
    while (1)
    {
        printf("============================================\n");
        printf("  WELCOME TO INVENTORY MANAGEMENT SYSTEM\n");
        printf("============================================\n\n");
        printf("  Please choose an option below:\n");
        printf("  --------------------------------------------\n");
        printf("  1. Add New Item\n");
        printf("  2. Display Items\n");
        printf("  3. Search Item\n");
        printf("  4. Edit Item\n");
        printf("  5. Delete Item\n");
        printf("  6. Exit\n");
        printf("  --------------------------------------------\n");
        printf("  Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addItem();
            break;
        case 2:
            displayItems();
            break;
        case 3:
            searchItem();
            break;
        case 4:
            editItem();
            break;
        case 5:
            deleteItem();
            break;
        case 6:
            exitProgram();
            break;
        default:
            printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

struct Item
{
    int id;
    char name[30];
    int quantity;
    float price;
};

void addItem()
{
    struct Item item;
    FILE *fp;

    fp = fopen("inventory.dat", "ab");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Item ID: ");
    scanf("%d", &item.id);
    printf("Enter Item Name: ");
    scanf("%s", item.name);
    printf("Enter Quantity: ");
    scanf("%d", &item.quantity);
    printf("Enter Price: ");
    scanf("%f", &item.price);

    fwrite(&item, sizeof(struct Item), 1, fp);
    fclose(fp);

    printf("Item added successfully!\n");
}

void displayItems()
{
    struct Item item;
    FILE *fp;

    fp = fopen("inventory.dat", "rb");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    printf("\nID\tName\tQuantity\tPrice\n");
    printf("-----------------------------------\n");

    while (fread(&item, sizeof(struct Item), 1, fp))
    {
        printf("%d\t%s\t%d\t\t%.2f\n", item.id, item.name, item.quantity, item.price);
    }

    fclose(fp);
}

void searchItem()
{
    struct Item item;
    int id, found = 0;
    FILE *fp;

    fp = fopen("inventory.dat", "rb");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Item ID to search: ");
    scanf("%d", &id);

    while (fread(&item, sizeof(struct Item), 1, fp))
    {
        if (item.id == id)
        {
            printf("\nID: %d\nName: %s\nQuantity: %d\nPrice: %.2f\n", item.id, item.name, item.quantity, item.price);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Item not found!\n");
    }

    fclose(fp);
}

void editItem()
{
    struct Item item;
    int id, found = 0;
    FILE *fp;

    fp = fopen("inventory.dat", "rb+");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Item ID to edit: ");
    scanf("%d", &id);

    while (fread(&item, sizeof(struct Item), 1, fp))
    {
        if (item.id == id)
        {
            printf("Enter new name: ");
            scanf("%s", item.name);
            printf("Enter new quantity: ");
            scanf("%d", &item.quantity);
            printf("Enter new price: ");
            scanf("%f", &item.price);

            fseek(fp, -sizeof(struct Item), SEEK_CUR);
            fwrite(&item, sizeof(struct Item), 1, fp);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Item not found!\n");
    }
    else
    {
        printf("Item updated successfully!\n");
    }

    fclose(fp);
}

void deleteItem()
{
    struct Item item;
    int id, found = 0;
    FILE *fp, *temp;

    fp = fopen("inventory.dat", "rb");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    temp = fopen("temp.dat", "wb");
    if (temp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Item ID to delete: ");
    scanf("%d", &id);

    while (fread(&item, sizeof(struct Item), 1, fp))
    {
        if (item.id != id)
        {
            fwrite(&item, sizeof(struct Item), 1, temp);
        }
        else
        {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("inventory.dat");
    rename("temp.dat", "inventory.dat");

    if (found)
    {
        printf("Item deleted successfully!\n");
    }
    else
    {
        printf("Item not found!\n");
    }
}

void exitProgram()
{
    printf("Exiting program...\n");
    exit(0);
}
