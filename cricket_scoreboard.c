
#include <stdio.h>
#include <stdlib.h>
void first_inning(char y[5]);
int second_inning(char y[5], char x[5]);

char Team1[5];
char Team2[5];
int toss, target, overs, score, wickets, inning = 1;
float runrate;
int balls, p_balls;
float c_overs;
int bat_first;

int main()
{

    printf("*-------------------------------------------*");
    printf("\n \t\tBeast Cricket Scorer\t\t");
    printf("*\n-------------------------------------------*");
    printf("\nPress any key to Continue");
    getchar();
    system("cls");

    printf("Enter Name of Team1:");
    scanf("%s", Team1);
    printf("Enter Name of Team2:");
    scanf("%s", Team2);
    printf("Enter the number of overs:");
    scanf("%d", &overs);
    balls = overs * 6;
re:
    printf("Which Team is batting first?\n");
    printf("\n[1] %s\n[2] %s\n", Team1, Team2);
    scanf("%d", &toss);
    switch (toss)
    {
    case 1:
        printf("Team 1 is batting first");
        first_inning(Team1);
        bat_first = 1;
        break;
    case 2:
        printf("Team 2 is batting first");
        first_inning(Team2);
        bat_first = 2;

        break;
    default:
        printf("Enter a valid choice!");
        goto re;
    }
    if (target > 0)
    {
        if (bat_first == 1)
        {
            second_inning(Team2, Team1);
        }
        else
        {
            second_inning(Team1, Team2);
        }
    }

    return 0;
}

void first_inning(char y[5])
{
    p_balls = 0;
    score = 0, wickets = 0;
    int j;
    int scorer, r;
    printf(":--------------First Innings----------------\n");
    for (j = 0; j != balls; j++)
    {
    label:
        printf("Last ball...");
        printf("\n[1]Normal delivery\n[2]No ball/wide\n");
        scanf("%d", &scorer);
        printf("\nRuns on last ball\n");
        printf("[0]Dot ball\n[1]1 run\n[2]2 runs\n[3]3 runs\n[4]4 \n[5]6\n[6]Wicket!\n");
        scanf("%d", &r);
        switch (scorer)
        {
        case 1:
            p_balls += 1;
            if (p_balls % 6 == 0)
            {
                c_overs += 0.5;
            }
            else
            {
                c_overs += 0.1;
            }
            break;
        case 2:
            score += 1;
        default:
            goto label;
            break;
        }
        switch (r)
        {
        case 0:
            break;
        case 1:
            score += 1;
            break;
        case 2:
            score += 2;
            break;
        case 3:
            score += 3;
            break;
        case 4:
            score += 4;
            break;
        case 5:
            score += 6;
            break;
        case 6:
            wickets += 1;
            break;

        default:
            printf("Enter a valid choice!");
            goto label;
            break;
        }
        runrate = score / overs;
        printf(":--------------First Innings----------------\n");
        printf("Inning 1|");
        printf("\nSCORE---%s|%d-%d|\t\t |overs:- %.1f|", y, score, wickets, c_overs);
        printf("\nRR:-%.2f", runrate);

        getchar();
        system("cls");
        if (wickets == 10 || p_balls == balls)
        {
            inning = 2;
            if (inning == 2)
            {
                target = score + 1;
                printf("\nTarget is %d", target);
            }
            break;
        }
    }
}
int second_inning(char y[5], char x[5])
{
    p_balls = 0;
    c_overs = 0;
    score = 0, wickets = 0;
    int j;
    int scorer, r;
    printf("\n");
    printf("\n:--------------SECOND Innings----------------\n");
    for (j = 0; j != balls; j++)
    {
    label:
        printf("Last ball...\n");
        printf("\n[1]Normal delivery\n[2]No ball/wide\n");
        scanf("%d", &scorer);
        printf("\nRuns on last ball\n");
        printf("[0]Dot ball\n[1]1 run\n[2]2 runs\n[3]3 runs\n[4]4 \n[5]6\n[6]Wicket!\n");
        scanf("%d", &r);
        switch (scorer)
        {
        case 1:
            p_balls += 1;
            if (p_balls % 6 == 0)
            {
                c_overs += 0.5;
            }
            else
            {
                c_overs += 0.1;
            }
            break;
        case 2:
            score += 1;
        default:
            break;
        }
        switch (r)
        {
        case 0:
            break;
        case 1:
            score += 1;
            break;
        case 2:
            score += 2;
            break;
        case 3:
            score += 3;
            break;
        case 4:
            score += 4;
            break;
        case 5:
            score += 6;
            break;
        case 6:
            wickets += 1;
            break;

        default:
            printf("Enter a valid choice!");
            goto label;
            break;
        }

        runrate = score / overs;
        printf("\n:--------------SECOND innings----------------\n");

        printf("Inning 2|");
        printf("\nSCORE---%s|%d-%d|\t\t |overs:- %.1f| Target - %d|", y, score, wickets, c_overs, target);
        printf("\n RR:-%.2f", runrate);
        printf("|Need %d of %d to win| ", target - score, balls - p_balls);

        getchar();
        system("cls");
        if (wickets == 10 || p_balls == balls || score >= target)
        {
            if (score >= target)
            {
                printf("%s Won the Match!", y);
                return 0;
            }
            else
            {
                printf("%s Won the Match!", x);
                return 0;
            }
        }
    }
}
