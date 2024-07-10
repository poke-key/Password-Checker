#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_PASSWORD_LENGTH 100

int check_password_strength(const char* password) {
    int score = 0;
    int length = strlen(password);
    int has_upper = 0, has_lower = 0, has_digit = 0, has_special = 0;

    if (length >= 8) {
        score++;
    }

    for (int i = 0; i < length; i++) {
        if (isupper(password[i])) has_upper = 1;
        else if (islower(password[i])) has_lower = 1;
        else if (isdigit(password[i])) has_digit = 1;
        else has_special = 1;
    }

    score += has_upper + has_lower + has_digit + has_special;

    return score;
}

/*function gives feedback about strength*/
void print_feedback(int score, int length) {
    printf("\nPassword strength: ");
    if (score < 3) printf("Weak\n");
    else if (score < 5) printf("Moderate\n");
    else printf("Strong\n");

    printf("\nSuggestions for improvement:\n");
    if (length < 8) printf("- Password is too short. It should be at least 8 characters.\n");
    if (score < 5) {
        if (!(score & 1)) printf("- Add uppercase letters for stronger password.\n");
        if (!(score & 2)) printf("- Add lowercase letters for stronger password.\n");
        if (!(score & 4)) printf("- Add numbers for stronger password.\n");
        if (!(score & 8)) printf("- Add special characters for stronger password.\n");
    }
    if (score == 5) printf("Great job! Your password is strong.\n");
}

int main() {
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter a password to check: ");
    fgets(password, sizeof(password), stdin);
    
    /*handle any new line characters by removing them*/
    size_t len = strlen(password);
    if (len > 0 && password[len-1] == '\n') {
        password[len-1] = '\0';
    }

    int score = check_password_strength(password);
    print_feedback(score, strlen(password));

    return 0;
}