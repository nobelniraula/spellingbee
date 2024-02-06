#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HISTORY 10 
//Structure to add and find history
typedef struct {
    char correctWord[100];
    char userWord[100];
    int distance;
} TestHistory;

int historyCount = 0;
TestHistory history[MAX_HISTORY];

int min(int x, int y, int z) {
    if (x <= y && x <= z) return x;
    if (y <= x && y <= z) return y;
    return z;
}
//LevenshteinDistance algorithm to find distance between 2 words just like djikstra algorithm unlike in djikstra it finds shortest distance between 2 points just like in google maps
int levenshteinDistance(char *s1, char *s2) {
    int len1 = strlen(s1), len2 = strlen(s2);
    int dp[len1 + 1][len2 + 1];

    for (int i = 0; i <= len1; i++) {
        for (int j = 0; j <= len2; j++) {
            if (i == 0)
                dp[i][j] = j;
            else if (j == 0)
                dp[i][j] = i;
            else if (s1[i - 1] == s2[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = 1 + min(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]);
        }
    }
    return dp[len1][len2];
}

void clearScreen() {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

void spellingTest() {
    if(historyCount >= MAX_HISTORY) {
        printf("History is full, cannot take more tests. Consider reviewing the history.\n");
        return;
    }

    printf("Enter the correct word: ");
    scanf("%99s", history[historyCount].correctWord);
    clearScreen();
    printf("Enter your word: ");
    scanf("%99s", history[historyCount].userWord);

    history[historyCount].distance = levenshteinDistance(history[historyCount].correctWord, history[historyCount].userWord);

    printf("Levenshtein distance is: %d\n", history[historyCount].distance);

    if(history[historyCount].distance == 0) {
        printf("Perfect! You spelled it correctly.\n");
    } else if(history[historyCount].distance <= 2) {
        printf("Close! But there are a few mistakes.\n");
    } else {
        printf("Quite a bit off. Keep practicing!\n");
    }

    historyCount++;
}

void viewHistory() {
    if(historyCount == 0) {
        printf("No history available.\n");
        return;
    }

    printf("Test History:\n");
    for(int i = 0; i < historyCount; i++) {
        printf("%d. Correct Word: %s, Your Word: %s, Distance: %d\n",
               i + 1,
               history[i].correctWord,
               history[i].userWord,
               history[i].distance);
    }
}

int main() {
    int choice;

    do {
        printf("\nSpelling Bee Application\n");
        printf("1. Start Test\n");
        printf("2. View History\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                spellingTest();
                break;
            case 2:
                viewHistory();
                break;
            case 3:
                printf("Exiting the application...\n");
                break;
            default:
                printf("Invalid choice. Please enter 1, 2, or 3.\n");
        }
    } while (choice != 3);

    return 0;
}
