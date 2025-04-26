#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

void enableNonBlockingMode()
{
    struct termios newt;
    tcgetattr(STDIN_FILENO, &newt);
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

int kbhit()
{
    struct timeval tv = {0, 0};
    fd_set rdfs;
    FD_ZERO(&rdfs);
    FD_SET(STDIN_FILENO, &rdfs);
    return select(STDIN_FILENO + 1, &rdfs, NULL, NULL, &tv);
}

char getch()
{
    char ch;
    read(STDIN_FILENO, &ch, 1);
    return ch;
}

void displayTime(int hours, int minutes, int seconds)
{
    system("clear"); // Clear screen for Linux/Mac
    printf("\nStopwatch: %02d:%02d:%02d\n", hours, minutes, seconds);
    printf("\nPress 's' to start/stop, 'r' to reset, 'q' to quit.\n");
}

int main()
{
    int hours = 0, minutes = 0, seconds = 0;
    int running = 0; // 1 = running, 0 = stopped

    enableNonBlockingMode();
    displayTime(hours, minutes, seconds);

    while (1)
    {
        if (kbhit())
        {
            char ch = getch();
            if (ch == 's')
            {
                running = !running;
            }
            else if (ch == 'r')
            {
                hours = minutes = seconds = 0;
                running = 0;
                displayTime(hours, minutes, seconds);
            }
            else if (ch == 'q')
            {
                break;
            }
        }

        if (running)
        {
            seconds++;
            if (seconds == 60)
            {
                seconds = 0;
                minutes++;
                if (minutes == 60)
                {
                    minutes = 0;
                    hours++;
                }
            }
            displayTime(hours, minutes, seconds);
        }
        sleep(1);
    }

    return 0;
}