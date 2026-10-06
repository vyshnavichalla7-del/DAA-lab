#include <stdio.h>

#define MAX 100

int people[MAX];
int count = 0;

/* Person enters */
void personEntered()
{
    if (count < MAX)
    {
        people[count] = count + 1;
        count++;

        printf("\nPerson entered.");
        printf("\nCurrent number of people: %d\n", count);
    }
    else
    {
        printf("\nMaximum capacity reached!\n");
    }
}

/* Person exits */
void personExited()
{
    if (count > 0)
    {
        count--;

        printf("\nPerson exited.");
        printf("\nCurrent number of people: %d\n", count);
    }
    else
    {
        printf("\nNo people inside!\n");
    }
}

/* Display count */
void displayCount()
{
    printf("\n============================\n");
    printf(" PEOPLE COUNT: %d\n", count);
    printf("============================\n");
}

/* Main */
int main()
{
    int choice;

    while (1)
    {
        printf("\n\n========== PEOPLE COUNTER ==========\n");
        printf("1. Person Entered\n");
        printf("2. Person Exited\n");
        printf("3. Display Count\n");
        printf("4. Exit\n");

        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                personEntered();
                break;

            case 2:
                personExited();
                break;

            case 3:
                displayCount();
                break;

            case 4:
                printf("\nProgram ended.\n");
                return 0;

            default:
                printf("\nInvalid choice!\n");
        }
    }

    return 0;
}