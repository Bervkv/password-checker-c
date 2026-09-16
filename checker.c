#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

#define MAX_WORDS 10000
typedef struct {
    bool length_ok;
    bool has_upper;
    bool has_lower;
    bool has_digit;
    bool has_symbol;
} PasswordCheck;

typedef struct{
    char **words;
    int count;
}WordList;

bool has_repetition(const char* password, int max_repeat){
    int size = strlen(password);
    int streak = 1;
    for (int i = 1; i < size ; i++)
    {
        if (password[i] != password[i-1])
        {
            streak = 1;
        }
        else if (password[i] == password[i-1])
        {
            streak++;
        }
        
       if (streak > max_repeat)
        {   
            return true;
        }

    }
  return false;
    
}

bool has_sequence(const char *password, int min_seq_len) {
    int size = strlen(password);
    if (size < 2) return false;

    int streak = 1;
    int prev_delta = 0;

    for (int i = 1; i < size; i++) {
        int delta = password[i] - password[i - 1];

        if (delta == 1 || delta == -1) {
            if (delta == prev_delta) {
                streak++;
            } else {
                streak = 2;
            }
        } else {
            streak = 1;
        }

        prev_delta = delta;

        if (streak >= min_seq_len) {
            return true;
        }
    }
    return false;
}

void normalize_leetspeak(const char *password, char *output) {
    int size = strlen(password);
    for (int i = 0; i < size; i++) {
        char c = tolower(password[i]);
        switch (c) {
            case '@': output[i] = 'a'; break;
            case '3': output[i] = 'e'; break;
            case '1': output[i] = 'i'; break;
            case '!': output[i] = 'i'; break;
            case '0': output[i] = 'o'; break;
            case '$': output[i] = 's'; break;
            case '5': output[i] = 's'; break;
            default:  output[i] = c;   break;
        }
    }
    output[size] = '\0';
}

bool is_common_password(char* password, WordList list){
    for (int i = 0; i < list.count; i++)
    {
        if (strcmp(password, list.words[i]) == 0)
        {
            return true;
        }
    }
    return false;
}

WordList load_common_passwords(const char* filepath){
    WordList List;
    FILE *file = fopen(filepath, "r");
    if (file == NULL)
    {
        printf("Error: Could Not open %s\n", filepath);
        List.count = 0;
        List.words = NULL;
        return List;
    }
    List.words = malloc(MAX_WORDS * sizeof(char *));
    char line_buffer[256];
    List.count = 0;
    while (fgets(line_buffer, sizeof(line_buffer), file))
    {
        line_buffer[strcspn(line_buffer, "\n")] = '\0';
        char *word_copy = malloc(strlen(line_buffer) + 1);
        strcpy(word_copy, line_buffer);
        List.words[List.count] = word_copy;
        List.count++;
    }
    
    
    return List;
}

PasswordCheck basic_checks(const char *password){
    PasswordCheck results = {false, false, false, false, false};

    int size = strlen(password);

    if (size >= 12)
    {
        results.length_ok = true;
    }

    for (int i = 0; i < size; i++)
    {
        if (isupper(password[i]))
        {
            results.has_upper = true;
        }
        if (islower(password[i]))
        {
            results.has_lower = true;
        }
        if (isdigit(password[i]))
        {
            results.has_digit = true;
        }
        if (ispunct(password[i]))
        {
            results.has_symbol = true;
        }
        
    }
    
    return results;
}

double calculate_entropy(const char* password){
    PasswordCheck checks = basic_checks(password);
    int pool_size = 0;

    if (checks.has_upper == true)    
    {
        pool_size += 26;
    }
    if (checks.has_lower == true)
    {
        pool_size += 26;
    }
    if (checks.has_digit == true)
    {
        pool_size += 10;
    }
    if (checks.has_symbol == true)
    {
        pool_size += 32;
    }
    
    if (pool_size == 0)
    {
        return 0.0;
    }
    
    return strlen(password) * log2(pool_size);
    
}

int main(void){
    PasswordCheck result = basic_checks("Hello123!");
    WordList common = load_common_passwords("common_passwords.txt");
    bool comparator = is_common_password("password", common);
    bool repetition = has_repetition("Hello123!",3);
    bool sequence = has_sequence("Hello123!", 3);
    printf("Comparator: %d\n", comparator);
    printf("First Word : %s\n", common.words[0]);

    printf("Loaded %d words\n", common.count);

    printf("length_ok: %d\n", result.length_ok);
    printf("has_upper: %d\n", result.has_upper);
    printf("has_lower: %d\n", result.has_lower);
    printf("has_digit: %d\n", result.has_digit);
    printf("has_symbol: %d\n", result.has_symbol);
    printf("has repetition: %d\n", repetition);
    printf("has sequence: %d\n", sequence);

    double entropy = calculate_entropy("Hello123!");
    printf("entropy: %f\n", entropy);

    return 0;
}