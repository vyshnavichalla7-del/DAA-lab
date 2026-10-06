#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX 10
#define FEATURES 5

struct Person
{
    char name[50];
    int features[FEATURES];
};

/* Calculate difference between two faces */
int calculateDifference(int face1[], int face2[])
{
    int i;
    int difference = 0;

    for (i = 0; i < FEATURES; i++)
    {
        difference += abs(face1[i] - face2[i]);
    }

    return difference;
}

/* Add person */
void addPerson()
{
    struct Person p;
    FILE *fp;
    int i;

    fp = fopen("faces.dat", "ab");

    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    printf("\nEnter person's name: ");
    scanf(" %[^\n]", p.name);

    printf("\nEnter 5 facial feature values:\n");

    for (i = 0; i < FEATURES; i++)
    {
        printf("Feature %d: ", i + 1);
        scanf("%d", &p.features[i]);
    }

    fwrite(&p, sizeof(p), 1, fp);

    fclose(fp);

    printf("\nFace data stored successfully!\n");
}

/* Recognize face */
void recognizeFace()
{
    struct Person p;
    FILE *fp;

    int inputFace[FEATURES];
    int i;

    int minDifference = 9999;
    char recognizedName[50] = "Unknown";

    fp = fopen("faces.dat", "rb");

    if (fp == NULL)
    {
        printf("\nNo face data available!\n");
        return;
    }

    printf("\nEnter facial feature values:\n");

    for (i = 0; i < FEATURES; i++)
    {
        printf("Feature %d: ", i + 1);
        scanf("%d", &inputFace[i]);
    }

    while (fread(&p, sizeof(p), 1, fp))
    {
        int difference;

        difference =
            calculateDifference(inputFace, p.features);

        printf("\nComparing with %s...", p.name);
        printf("\nDifference = %d\n", difference);

        if (difference < minDifference)
        {
            minDifference = difference;
            strcpy(recognizedName, p.name);
        }
    }

    fclose(fp);

    /*
       Smaller difference means
       greater similarity.
    */

    if (minDifference <= 20)
    {
        printf("\n============================\n");
        printf("FACE RECOGNIZED!\n");
        printf("Person: %s\n", recognizedName);
        printf("Difference: %d\n", minDifference);
        printf("============================\n");
    }
    else
    {
        printf("\nFace not recognized!\n");
    }
}

/* Display stored people */
void displayPeople()
{
    struct Person p;
    FILE *fp;

    fp = fopen("faces.dat", "rb");

    if (fp == NULL)
    {
        printf("\nNo face records found!\n");
        return;
    }

    printf("\n====== REGISTERED PEOPLE ======\n");

    while (fread(&p, sizeof(p), 1, fp))
    {
        printf("\nName: %s", p.name);

        printf("\nFeatures: ");

        for (int i = 0; i < FEATURES; i++)
        {
            printf("%d ", p.features[i]);
        }

        printf("\n");
    }

    fclose(fp);
}

/* Main */
int main()
{
    int choice;

    while (1)
    {
        printf("\n\n================================\n");
        printf("       FACE RECOGNITION\n");
        printf("================================\n");

        printf("1. Register Face\n");
        printf("2. Recognize Face\n");
        printf("3. Display Registered People\n");
        printf("4. Exit\n");

        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addPerson();
                break;

            case 2:
                recognizeFace();
                break;

            case 3:
                displayPeople();
                break;

            case 4:
                printf("\nThank you!\n");
                return 0;

            default:
                printf("\nInvalid choice!\n");
        }
    }
}