#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TABLE_SIZE 10
#define MAX 200

// Node for Hash Table
struct FAQ {
    char keyword[50];
    char answer[MAX];
    struct FAQ *next;
};

struct FAQ *hashTable[TABLE_SIZE];

/* Hash Function */
int hashFunction(char keyword[]) {
    int hash = 0;
    int i;

    for (i = 0; keyword[i] != '\0'; i++) {
        hash = (hash + keyword[i]) % TABLE_SIZE;
    }

    return hash;
}

/* Convert string to lowercase */
void toLowerCase(char str[]) {
    int i;

    for (i = 0; str[i] != '\0'; i++) {
        str[i] = tolower(str[i]);
    }
}

/* Insert FAQ into Hash Table */
void insertFAQ(char keyword[], char answer[]) {
    int index;
    struct FAQ *newNode;
    struct FAQ *temp;

    toLowerCase(keyword);

    index = hashFunction(keyword);

    newNode = (struct FAQ *)malloc(sizeof(struct FAQ));

    strcpy(newNode->keyword, keyword);
    strcpy(newNode->answer, answer);
    newNode->next = NULL;

    // Collision handling using chaining
    if (hashTable[index] == NULL) {
        hashTable[index] = newNode;
    } else {
        temp = hashTable[index];

        while (temp->next != NULL) {
            temp = temp->next;
        }

        temp->next = newNode;
    }
}

/* Search FAQ */
char *searchFAQ(char keyword[]) {
    int index;
    struct FAQ *temp;

    toLowerCase(keyword);

    index = hashFunction(keyword);

    temp = hashTable[index];

    while (temp != NULL) {
        if (strcmp(temp->keyword, keyword) == 0) {
            return temp->answer;
        }

        temp = temp->next;
    }

    return NULL;
}

/* Save FAQ to File */
void saveFAQToFile(char keyword[], char answer[]) {
    FILE *fp;

    fp = fopen("faq.txt", "a");

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(fp, "%s|%s\n", keyword, answer);

    fclose(fp);
}

/* Load FAQs from File */
void loadFAQs() {
    FILE *fp;
    char line[MAX];
    char keyword[50];
    char answer[MAX];

    fp = fopen("faq.txt", "r");

    if (fp == NULL) {
        return;
    }

    while (fgets(line, sizeof(line), fp)) {

        line[strcspn(line, "\n")] = '\0';

        if (sscanf(line, "%[^|]|%[^\n]", keyword, answer) == 2) {
            insertFAQ(keyword, answer);
        }
    }

    fclose(fp);
}

/* Save Chat History */
void saveChat(char question[], char answer[]) {
    FILE *fp;

    fp = fopen("chat_history.txt", "a");

    if (fp == NULL) {
        printf("Error opening chat history file!\n");
        return;
    }

    fprintf(fp, "Student: %s\n", question);
    fprintf(fp, "Bot: %s\n\n", answer);

    fclose(fp);
}

/* Display all FAQs */
void displayFAQs() {
    int i;
    struct FAQ *temp;

    printf("\n========== ALL FAQs ==========\n");

    for (i = 0; i < TABLE_SIZE; i++) {

        temp = hashTable[i];

        if (temp != NULL) {
            printf("\nIndex %d:\n", i);

            while (temp != NULL) {
                printf("Keyword : %s\n", temp->keyword);
                printf("Answer  : %s\n", temp->answer);

                temp = temp->next;
            }
        }
    }
}

/* Add new FAQ */
void addFAQ() {
    char keyword[50];
    char answer[MAX];

    printf("\nEnter keyword: ");
    scanf(" %[^\n]", keyword);

    printf("Enter answer: ");
    scanf(" %[^\n]", answer);

    insertFAQ(keyword, answer);
    saveFAQToFile(keyword, answer);

    printf("\nFAQ added successfully!\n");
}

/* Ask Chatbot */
void askChatbot() {
    char question[MAX];
    char keyword[50];
    char *answer;

    printf("\nYou: ");
    scanf(" %[^\n]", question);

    /*
       For simplicity, user enters the main keyword.
       Example: library, hostel, fees
    */

    printf("Enter important keyword from your question: ");
    scanf("%s", keyword);

    answer = searchFAQ(keyword);

    if (answer != NULL) {
        printf("Bot: %s\n", answer);
        saveChat(question, answer);
    } else {
        printf("Bot: Sorry! I don't have information about this.\n");

        saveChat(question,
                 "Sorry! I don't have information about this.");
    }
}

/* View Chat History */
void viewHistory() {
    FILE *fp;
    char ch;

    fp = fopen("chat_history.txt", "r");

    if (fp == NULL) {
        printf("\nNo chat history available.\n");
        return;
    }

    printf("\n========== CHAT HISTORY ==========\n");

    while ((ch = fgetc(fp)) != EOF) {
        putchar(ch);
    }

    fclose(fp);
}

/* Main Function */
int main() {

    int choice;

    // Initialize hash table
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }

    // Load existing FAQs
    loadFAQs();

    // Insert default FAQs if file is empty
    if (searchFAQ("library") == NULL) {

        insertFAQ("library",
                  "Library is located in Block A, Ground Floor.");

        insertFAQ("hostel",
                  "Hostel is located near Block C.");

        insertFAQ("canteen",
                  "Canteen is located beside Block B.");

        insertFAQ("fees",
                  "For fee details, contact the Accounts Office.");

        insertFAQ("exam",
                  "Exam Cell is located in Block A.");

        insertFAQ("transport",
                  "Transport Office is near the main gate.");

        insertFAQ("office",
                  "Administrative Office is located in Block A.");

        insertFAQ("wifi",
                  "Campus Wi-Fi support is available at the IT Helpdesk.");
    }

    while (1) {

        printf("\n\n====================================\n");
        printf("       CAMPUS HELPDESK CHATBOT\n");
        printf("====================================\n");

        printf("1. Ask Chatbot\n");
        printf("2. Add FAQ\n");
        printf("3. Search FAQ\n");
        printf("4. Display All FAQs\n");
        printf("5. View Chat History\n");
        printf("6. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                askChatbot();
                break;

            case 2:
                addFAQ();
                break;

            case 3: {
                char keyword[50];
                char *answer;

                printf("\nEnter keyword to search: ");
                scanf("%s", keyword);

                answer = searchFAQ(keyword);

                if (answer != NULL)
                    printf("Answer: %s\n", answer);
                else
                    printf("FAQ not found!\n");

                break;
            }

            case 4:
                displayFAQs();
                break;

            case 5:
                viewHistory();
                break;

            case 6:
                printf("\nThank you for using Campus Helpdesk!\n");
                exit(0);

            default:
                printf("\nInvalid choice!\n");
        }
    }

    return 0;
}