#include <stdio.h>
#include <string.h>

struct user
{
    char username[50];
    char password[50];
};

void signup(struct user u[], int count)
{
    if (count < 10)
    {
        printf("Enter user name:");
        scanf("%s", u[count].username);
        printf("Enter password:");
        scanf("%s", u[count].password);
        printf("Registration Successful\n");
    }
    else
    {
        printf("Max limit reached.\n");
    }
}

int signin(struct user u[], int count)
{
    char username[50];
    char password[50];
    printf("Username:");
    scanf("%s", username);
    printf("Password:");
    scanf("%s", password);

    for (int i = 0; i < count; i++)
    {
        if (strcmp(username, u[i].username) == 0 && strcmp(password, u[i].password) == 0)
        {
            printf("Login successful\n");
            return 1; // Return 1 to indicate successful login
        }
    }
    printf("Invalid username & password.\n");
    return 0; // Return 0 to indicate unsuccessful login
}

void displayMenu()
{
    printf("1.SignUp.\n");
    printf("2.SignIn\n");
    printf("3.EXIT\n");
    printf("Enter your choice ");
}

int main(void)
{
    struct user u[10];
    int count = 0;
    int choice;

    do
    {
        displayMenu();
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            signup(u, count);
            count++;
            break;
        case 2:
            if (signin(u, count))
            {
                return 0;
            }
            break;
        case 3:
            printf("EXIT\n");
            break;
        default:
            printf("Invalid option. Try again!\n");
        }
    } while (choice != 3);

    return 0;
}