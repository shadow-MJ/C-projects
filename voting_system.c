#include <stdio.h>

struct vote
{
    float BNP;
    float Awami;
    float Students;
    float Shibir;
};

void result(int totalvotes, int array[])
{
    struct vote v;
    float percent = 100 / totalvotes;
    v.BNP = v.Awami = v.Students = v.Shibir = 0;
    for (int i = 0; i < totalvotes; i++)
    {
        switch (array[i])
        {
        case 1:
            (v.BNP)++;
            break;
        case 2:
            (v.Awami)++;
            break;
        case 3:
            (v.Students)++;
            break;
        case 4:
            (v.Shibir)++;
            break;
        }
    }

    printf("\n\n");
    printf("\tResult-\n");
    printf("BNP-   %.1f%%  Total votes- %.1f\n", (v.BNP) * percent, (v.BNP));
    printf("Awami League-   %.1f%%  Total votes- %.1f\n", (v.Awami) * percent, (v.Awami));
    printf("Students-  %.1f%%  Total votes- %.1f\n", (v.Students) * percent, (v.Students));
    printf("Shibir-   %.1f%%  Total votes- %.1f\n", (v.Shibir) * percent, (v.Shibir));
}

int main(void)
{
    printf("\t...Voting System...\n");
    int totalvotes;
    printf("Enter total voters:");
    scanf("%d", &totalvotes);
    int array[totalvotes];
    for (int i = 0; i < totalvotes; i++)
    {
        printf("\n");
        printf("Select your option-\n");
        printf("1.BNP.\n");
        printf("2.Awami League.\n");
        printf("3.Students.\n");
        printf("4.Shibir.\n");
        scanf("%d", &array[i]);
    }

    result(totalvotes, array);

    return 0;
}