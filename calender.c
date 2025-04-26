#include <stdio.h>

int isLeapYear(int year)
{
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        return 1;
    return 0;
}

int getFirstDayOfYear(int year)
{
    int day = (year + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400) % 7;
    return day; 
}

void printCalendar(int year)
{
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    char *months[] = {"January", "February", "March", "April", "May", "June",
                      "July", "August", "September", "October", "November", "December"};

    if (isLeapYear(year))
        daysInMonth[1] = 29; 

    int firstDay = getFirstDayOfYear(year);

    for (int month = 0; month < 12; month++)
    {
        printf("\n  ------------ %s %d ------------\n", months[month], year);
        printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

        for (int i = 0; i < firstDay; i++)
            printf("     ");

        for (int day = 1; day <= daysInMonth[month]; day++)
        {
            printf("%5d", day);

            if (++firstDay > 6)
            { 
                firstDay = 0;
                printf("\n");
            }
        }
        printf("\n");
    }
}

int main()
{
    int year;
    printf("Enter the year: ");
    scanf("%d", &year);

    printCalendar(year);

    return 0;
}