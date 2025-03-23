#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 100
#define NAME_LENGTH 50
#define CATEGORY_LENGTH 30
#define INVENTORY_FILE "inventory.dat"

typedef struct
{
    int id;
    char name[NAME_LENGTH];
    char category[CATEGORY_LENGTH];
    float price;
    int stock;
} Product;

Product products[MAX_PRODUCTS];
int productCount = 0;

// Function Prototypes
void loadProducts();
void saveProducts();
void addProduct();
void updateProduct();
void deleteProduct();
void processTransaction();
void generateReport();
int getMaxId();

int main()
{
    int choice;
    loadProducts();

    do
    {
        printf("============================================\n");
        printf("    Inventory Management System \n");
        printf("============================================\n");
        printf("    Please choose an option below:\n");
        printf("--------------------------------------------\n");
        printf("1. Add Product\n");
        printf("2. Update Product\n");
        printf("3. Delete Product\n");
        printf("4. Process Transaction\n");
        printf("5. Display Items & Info.\n");
        printf("6. Exit\n");
        printf("--------------------------------------------\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Exiting.\n");
            break;
        }
        getchar(); // clear newline from input buffer

        switch (choice)
        {
        case 1:
            addProduct();
            break;
        case 2:
            updateProduct();
            break;
        case 3:
            deleteProduct();
            break;
        case 4:
            processTransaction();
            break;
        case 5:
            generateReport();
            break;
        case 6:
            printf("Exiting program.\n");
            break;
        default:
            printf("Invalid choice, try again.\n");
        }
    } while (choice != 6);

    saveProducts();
    return 0;
}

// Load products from the binary file
void loadProducts()
{
    FILE *fp = fopen(INVENTORY_FILE, "rb");
    if (fp == NULL)
    {
        // File doesn't exist. Start with an empty inventory.
        productCount = 0;
        return;
    }
    fread(&productCount, sizeof(int), 1, fp);
    fread(products, sizeof(Product), productCount, fp);
    fclose(fp);
}

// Save products to the binary file
void saveProducts()
{
    FILE *fp = fopen(INVENTORY_FILE, "wb");
    if (fp == NULL)
    {
        printf("Error saving products.\n");
        return;
    }
    fwrite(&productCount, sizeof(int), 1, fp);
    fwrite(products, sizeof(Product), productCount, fp);
    fclose(fp);
}

// Get the maximum product ID in the current list
int getMaxId()
{
    int max = 0;
    for (int i = 0; i < productCount; i++)
    {
        if (products[i].id > max)
            max = products[i].id;
    }
    return max;
}

// Add a new product to the inventory
void addProduct()
{
    if (productCount >= MAX_PRODUCTS)
    {
        printf("Inventory is full. Cannot add more products.\n");
        return;
    }
    Product p;
    p.id = getMaxId() + 1;

    printf("Enter product name: ");
    fgets(p.name, NAME_LENGTH, stdin);
    p.name[strcspn(p.name, "\n")] = '\0'; // Remove newline

    printf("Enter product category: ");
    fgets(p.category, CATEGORY_LENGTH, stdin);
    p.category[strcspn(p.category, "\n")] = '\0';

    printf("Enter product price: ");
    scanf("%f", &p.price);

    printf("Enter product stock quantity: ");
    scanf("%d", &p.stock);
    getchar(); // clear newline

    products[productCount++] = p;
    printf("Product added with ID %d.\n", p.id);
}

// Update an existing product's details
void updateProduct()
{
    int id, found = 0;
    printf("Enter product ID to update: ");
    scanf("%d", &id);
    getchar(); // clear newline

    for (int i = 0; i < productCount; i++)
    {
        if (products[i].id == id)
        {
            found = 1;
            printf("Enter new product name (current: %s): ", products[i].name);
            fgets(products[i].name, NAME_LENGTH, stdin);
            products[i].name[strcspn(products[i].name, "\n")] = '\0';

            printf("Enter new product category (current: %s): ", products[i].category);
            fgets(products[i].category, CATEGORY_LENGTH, stdin);
            products[i].category[strcspn(products[i].category, "\n")] = '\0';

            printf("Enter new product price (current: %.2f): ", products[i].price);
            scanf("%f", &products[i].price);

            printf("Enter new product stock (current: %d): ", products[i].stock);
            scanf("%d", &products[i].stock);
            getchar(); // clear newline

            printf("Product updated.\n");
            break;
        }
    }
    if (!found)
        printf("Product with ID %d not found.\n", id);
}

// Delete a product from the inventory
void deleteProduct()
{
    int id, found = 0;
    printf("Enter product ID to delete: ");
    scanf("%d", &id);
    getchar(); // clear newline

    for (int i = 0; i < productCount; i++)
    {
        if (products[i].id == id)
        {
            found = 1;
            // Shift remaining products to fill the gap
            for (int j = i; j < productCount - 1; j++)
            {
                products[j] = products[j + 1];
            }
            productCount--;
            printf("Product deleted.\n");
            break;
        }
    }
    if (!found)
        printf("Product with ID %d not found.\n", id);
}

// Process a transaction (purchase to add stock or sale to reduce stock)
void processTransaction()
{
    int id, found = 0, qty, type;
    printf("Enter product ID for transaction: ");
    scanf("%d", &id);

    for (int i = 0; i < productCount; i++)
    {
        if (products[i].id == id)
        {
            found = 1;
            printf("Enter transaction type (1 for Purchase, 2 for Sale): ");
            scanf("%d", &type);
            if (type == 1)
            {
                printf("Enter quantity to add: ");
                scanf("%d", &qty);
                products[i].stock += qty;
                printf("Stock updated. New stock: %d\n", products[i].stock);
            }
            else if (type == 2)
            {
                printf("Enter quantity to sell: ");
                scanf("%d", &qty);
                if (qty > products[i].stock)
                {
                    printf("Not enough stock. Current stock: %d\n", products[i].stock);
                }
                else
                {
                    products[i].stock -= qty;
                    printf("Sale processed. New stock: %d\n", products[i].stock);
                }
            }
            else
            {
                printf("Invalid transaction type.\n");
            }
            break;
        }
    }
    if (!found)
        printf("Product with ID %d not found.\n", id);
    getchar(); // clear newline
}

// Generate and display an inventory report
void generateReport()
{
    printf("\n--- Inventory Report ---\n");
    if (productCount == 0)
    {
        printf("No products in inventory.\n");
        return;
    }

    printf("%-5s %-20s %-15s %-10s %-10s\n", "ID", "Name", "Category", "Price", "Stock");
    for (int i = 0; i < productCount; i++)
    {
        printf("%-5d %-20s %-15s %-10.2f %-10d\n", products[i].id, products[i].name,
               products[i].category, products[i].price, products[i].stock);
    }

    // Alert for low stock products (e.g., stock less than 5)
    printf("\nLow stock products (stock < 5):\n");
    int lowStockFound = 0;
    for (int i = 0; i < productCount; i++)
    {
        if (products[i].stock < 5)
        {
            printf("ID %d - %s (Stock: %d)\n", products[i].id, products[i].name, products[i].stock);
            lowStockFound = 1;
        }
    }
    if (!lowStockFound)
        printf("None.\n");
}
