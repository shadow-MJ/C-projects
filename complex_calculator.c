#include <stdio.h>
int cal(int a, char b, int c)
{
    switch (b)
    {
    case '+':
        return a + c;
        break;
    case '-':
        return a - c;
        break;
    case '*':
        return a * c;
        break;
    case '/':
        return a / c;
        break;
    default:
        printf("ERROR operator!\n");
        return 0;
        break;
    }
}

int main(void)
{
    printf("\tΠΠΠ CALCULATOR ΠΠΠ\n\n\n");
    int a, c, result = 0;
    char b;
    printf("Enter first number-\n");
    scanf("%d", &a);
    printf("Enter operator-\n");
    scanf(" %c", &b);
    printf("Enter last number-\n");
    scanf("%d", &c);

    result = cal(a, b, c);
    printf("%d\n", result);

    while (1)
    {
        scanf(" %c", &b);
        scanf("%d", &c);
        result = cal(result, b, c);
        printf("%d\n", result);
    }

    return 0;
}