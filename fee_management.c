#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "fees.dat"

struct Student
{
    int rollNo;
    char name[50];
    char branch[30];
    float totalFee;
    float paidFee;
    float pendingFee;
};

/* Add Student */
void addStudent()
{
    struct Student s;
    FILE *fp;

    fp = fopen(FILE_NAME, "ab");

    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    printf("\nEnter Roll Number: ");
    scanf("%d", &s.rollNo);

    printf("Enter Student Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter Branch: ");
    scanf(" %[^\n]", s.branch);

    printf("Enter Total Fee: ");
    scanf("%f", &s.totalFee);

    printf("Enter Paid Fee: ");
    scanf("%f", &s.paidFee);

    s.pendingFee = s.totalFee - s.paidFee;

    fwrite(&s, sizeof(s), 1, fp);

    fclose(fp);

    printf("\nStudent added successfully!\n");
}

/* Display All Students */
void displayStudents()
{
    struct Student s;
    FILE *fp;

    fp = fopen(FILE_NAME, "rb");

    if (fp == NULL)
    {
        printf("\nNo student records found!\n");
        return;
    }

    printf("\n================ STUDENT FEE DETAILS ================\n");

    printf("%-8s %-20s %-15s %-12s %-12s %-12s\n",
           "Roll", "Name", "Branch",
           "Total", "Paid", "Pending");

    printf("--------------------------------------------------------------------------\n");

    while (fread(&s, sizeof(s), 1, fp))
    {
        printf("%-8d %-20s %-15s %-12.2f %-12.2f %-12.2f\n",
               s.rollNo,
               s.name,
               s.branch,
               s.totalFee,
               s.paidFee,
               s.pendingFee);
    }

    fclose(fp);
}

/* Search Student */
void searchStudent()
{
    struct Student s;
    FILE *fp;
    int roll, found = 0;

    fp = fopen(FILE_NAME, "rb");

    if (fp == NULL)
    {
        printf("\nNo records found!\n");
        return;
    }

    printf("\nEnter Roll Number to search: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp))
    {
        if (s.rollNo == roll)
        {
            printf("\nStudent Found!\n");
            printf("Roll Number : %d\n", s.rollNo);
            printf("Name        : %s\n", s.name);
            printf("Branch      : %s\n", s.branch);
            printf("Total Fee   : %.2f\n", s.totalFee);
            printf("Paid Fee    : %.2f\n", s.paidFee);
            printf("Pending Fee : %.2f\n", s.pendingFee);

            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nStudent not found!\n");

    fclose(fp);
}

/* Pay Fee */
void payFee()
{
    struct Student s;
    FILE *fp, *temp;
    int roll, found = 0;
    float amount;

    fp = fopen(FILE_NAME, "rb");
    temp = fopen("temp.dat", "wb");

    if (fp == NULL)
    {
        printf("\nNo records found!\n");
        return;
    }

    printf("\nEnter Roll Number: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp))
    {
        if (s.rollNo == roll)
        {
            found = 1;

            printf("Student Name: %s\n", s.name);
            printf("Pending Fee: %.2f\n", s.pendingFee);

            printf("Enter amount to pay: ");
            scanf("%f", &amount);

            if (amount <= 0)
            {
                printf("Invalid amount!\n");
            }
            else if (amount > s.pendingFee)
            {
                printf("Amount exceeds pending fee!\n");
            }
            else
            {
                s.paidFee += amount;
                s.pendingFee = s.totalFee - s.paidFee;

                printf("\nPayment successful!\n");
                printf("Paid Fee: %.2f\n", s.paidFee);
                printf("Remaining Fee: %.2f\n", s.pendingFee);
            }
        }

        fwrite(&s, sizeof(s), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    if (!found)
        printf("\nStudent not found!\n");
}

/* Display Pending Fees */
void pendingFees()
{
    struct Student s;
    FILE *fp;
    int found = 0;

    fp = fopen(FILE_NAME, "rb");

    if (fp == NULL)
    {
        printf("\nNo records found!\n");
        return;
    }

    printf("\n============== PENDING FEES ==============\n");

    while (fread(&s, sizeof(s), 1, fp))
    {
        if (s.pendingFee > 0)
        {
            printf("\nRoll Number : %d", s.rollNo);
            printf("\nName        : %s", s.name);
            printf("\nPending Fee : %.2f\n", s.pendingFee);

            found = 1;
        }
    }

    if (!found)
        printf("\nNo pending fees!\n");

    fclose(fp);
}

/* Main Function */
int main()
{
    int choice;

    while (1)
    {
        printf("\n\n========================================\n");
        printf("         FEE MANAGEMENT SYSTEM\n");
        printf("========================================\n");

        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student\n");
        printf("4. Pay Fee\n");
        printf("5. Display Pending Fees\n");
        printf("6. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                payFee();
                break;

            case 5:
                pendingFees();
                break;

            case 6:
                printf("\nThank you!\n");
                exit(0);

            default:
                printf("\nInvalid choice!\n");
        }
    }

    return 0;
}