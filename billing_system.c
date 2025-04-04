#include <stdio.h>
#include <string.h>

struct list
{
    int id;
    char itemName[30];
    int price;
};

void display(struct list l[], int totalitems, char Name[], char Address[])
{
    int total = 0;
    printf("\n\n\n\n");
    printf("\t Premium Store \n");
    printf("\t-------------- \n");
    printf("\n");
    printf("Name : %s \t Address : %s \n", Name, Address);
    printf("\n");
    for (int i = 0; i < totalitems; i++)
    {
        printf("Id : %d\t", l[i].id);
        printf("Name : %s\t", l[i].itemName);
        printf("Price : %d\n", l[i].price);
        printf("----------------------------------\n");
        total = total + l[i].price;
    }
    printf("\t\tTotal : %d", total);
    printf("\n\n");
    printf("\tThanks for visiting.\n");
    printf("\n\n");
}

int main()
{
    printf("Hello.......\n");
    char Name[30];
    char Address[30];
    int totalItems;
    printf("Enter name \t");
    scanf(" %s", &Name);
    printf("Enter address \t");
    scanf(" %s", &Address);
    printf("Enter total items \t");
    scanf("%d", &totalItems);
    printf("\n");

    struct list l[totalItems];

    for (int i = 0; i < totalItems; i++)
    {
        l[i].id = i + 1;
        printf("Enter %d item name: \t", i + 1);
        scanf(" %s", &l[i].itemName);
        printf("Enter price:\t\t");
        scanf("%d", &l[i].price);
    }

    display(l, totalItems, Name, Address);
}