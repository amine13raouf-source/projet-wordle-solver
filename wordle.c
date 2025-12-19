#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define WORDLEN 5
#define MAX_WORDS 20000
#define MAX_LINE 32

 int load_dictionary(const char *path, char words[][WORDLEN+1]) {
    FILE *f = fopen(path, "r");
    if (f == NULL)
            return -1;
    int count = 0;
    char line[MAX_LINE];
    while (fgets(line, sizeof(line), f)) {

       line[strcspn(line, "\r\n ")] = '\0';

        if (strlen(line) != WORDLEN) continue;

        for (int i=0;i<WORDLEN;i++)
                if (line[i]>='A' && line[i]<='Z')
                       line[i] = line[i]-'A'+'a';
        strcpy(words[count++], line);
        if (count >= MAX_WORDS) break;
    }
    fclose(f);
    return count;
}
void pick_random_word(char *out, char words[][WORDLEN+1], int count) {
            int idx = rand() % count;
            strcpy(out, words[idx]);
}
int is_valid_guess(const char *guess, char words[][WORDLEN+1], int count) {
    for (int i=0;i<count;i++)
          if (strcmp(guess, words[i])==0) return 1;
    return 0;
}
void feedback(const char *target, const char *guess, char *res) {
    int used[WORDLEN] = {0};


    for (int i = 0; i < WORDLEN; i++) {
        if (guess[i] == target[i]) {
            res[i] = 'G';
            used[i] = 1;
        } else {
            res[i] = 'X';
        }
    }


    for (int i = 0; i < WORDLEN; i++) {
        if (res[i] == 'G') continue; // Déjà traité

        for (int j = 0; j < WORDLEN; j++) {

            if (!used[j] && guess[i] == target[j]) {
                res[i] = 'Y';
                used[j] = 1; // Marquer la lettre comme utilisée
                break;
            }
        }
    }
}
int main()
{
    char words[MAX_WORDS][WORDLEN+1];
    const char *dict = "words.txt";   // Nom du fichier dictionnaire
    srand((unsigned)time(NULL));

    int n = load_dictionary(dict, words);
    if (n < 1) {
        fprintf(stderr, "Erreur : Impossible de charger le dictionnaire depuis %s\n", dict);
        return 1;
    }

    char target[WORDLEN+1];
    pick_random_word(target, words, n);

    printf("=== Wordle (version ligne de commande) ===\n");

    char guess[WORDLEN+2];
    char res[WORDLEN+1];
    int attempts = 0;

    while (attempts < 6) {
        attempts++;
        printf("Essai %d/6 : Entrez une proposition (5 lettres) : ", attempts);

        if (!fgets(guess, sizeof(guess), stdin)) break;

        guess[strcspn(guess, "\r\n")] = 0;

        for (int i = 0; i < (int)strlen(guess); i++)
            if (guess[i] >= 'A' && guess[i] <= 'Z')
                guess[i] = guess[i] - 'A' + 'a';

        if (strlen(guess) != WORDLEN) {
            printf("La proposition doit contenir 5 lettres.\n");
            attempts--;
            continue;
        }

        if (!is_valid_guess(guess, words, n)) {
            printf("Le mot n'existe pas dans le dictionnaire.\n");
            attempts--;
            continue;
        }

        feedback(target, guess, res);

        for (int i = 0; i < WORDLEN; i++) {
            char c = res[i];
            if (c == 'G') printf("[%c:G] ", guess[i]);
            else if (c == 'Y') printf("[%c:Y] ", guess[i]);
            else printf("[%c:X] ", guess[i]);
        }
        printf("\n");

        if (strcmp(res, "GGGGG") == 0) {
            printf("Bravo ! Vous avez gagne en %d essais.\n", attempts);
            return 0;
        }
    }

    printf("Vous avez perdu. Le mot etait : %s\n", target);
    return 0;
}
