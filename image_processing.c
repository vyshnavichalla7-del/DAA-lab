#include <stdio.h>
#include <stdlib.h>

#define MAX 500

int image[MAX][MAX];
int rows, cols;

/* Read PGM Image */
void readImage()
{
    FILE *fp;
    char format[3];
    int maxValue;

    fp = fopen("input.pgm", "r");

    if (fp == NULL)
    {
        printf("Error: Cannot open input.pgm\n");
        exit(1);
    }

    fscanf(fp, "%s", format);
    fscanf(fp, "%d %d", &cols, &rows);
    fscanf(fp, "%d", &maxValue);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            fscanf(fp, "%d", &image[i][j]);
        }
    }

    fclose(fp);

    printf("\nImage loaded successfully!\n");
    printf("Width  : %d\n", cols);
    printf("Height : %d\n", rows);
}

/* Negative Image */
void negative()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            image[i][j] = 255 - image[i][j];
        }
    }

    printf("\nNegative image applied!\n");
}

/* Thresholding */
void threshold()
{
    int t;

    printf("Enter threshold value (0-255): ");
    scanf("%d", &t);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (image[i][j] >= t)
                image[i][j] = 255;
            else
                image[i][j] = 0;
        }
    }

    printf("\nThresholding applied!\n");
}

/* Brightness */
void brightness()
{
    int value;

    printf("Enter brightness value (-255 to 255): ");
    scanf("%d", &value);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            image[i][j] += value;

            if (image[i][j] > 255)
                image[i][j] = 255;

            if (image[i][j] < 0)
                image[i][j] = 0;
        }
    }

    printf("\nBrightness adjusted!\n");
}

/* Save Image */
void saveImage()
{
    FILE *fp;

    fp = fopen("output.pgm", "w");

    if (fp == NULL)
    {
        printf("Error creating output file!\n");
        return;
    }

    fprintf(fp, "P2\n");
    fprintf(fp, "%d %d\n", cols, rows);
    fprintf(fp, "255\n");

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            fprintf(fp, "%d ", image[i][j]);
        }

        fprintf(fp, "\n");
    }

    fclose(fp);

    printf("\nImage saved as output.pgm\n");
}

/* Main */
int main()
{
    int choice;

    readImage();

    while (1)
    {
        printf("\n================================\n");
        printf("      IMAGE PROCESSING\n");
        printf("================================\n");

        printf("1. Negative Image\n");
        printf("2. Thresholding\n");
        printf("3. Brightness Adjustment\n");
        printf("4. Save Image\n");
        printf("5. Exit\n");

        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                negative();
                break;

            case 2:
                threshold();
                break;

            case 3:
                brightness();
                break;

            case 4:
                saveImage();
                break;

            case 5:
                printf("\nProgram ended.\n");
                exit(0);

            default:
                printf("\nInvalid choice!\n");
        }
    }

    return 0;
}