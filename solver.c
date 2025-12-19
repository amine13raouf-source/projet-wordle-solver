#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define WORDLEN 5
#define MAX_WORDS 10000
#define MAX_ATTEMPTS 6

/* ===================== FEEDBACK (TON CODE) ===================== */
void feedback(const char *target, const char *guess, char *res) {
    int used[WORDLEN] = {0};

    // 1) VERT
    for (int i = 0; i < WORDLEN; i++) {
        if (guess[i] == target[i]) {
            res[i] = 'G';
            used[i] = 1;
        } else {
            res[i] = 'X';
        }
    }

    // 2) JAUNE
    for (int i = 0; i < WORDLEN; i++) {
        if (res[i] == 'G') continue;

        for (int j = 0; j < WORDLEN; j++) {
            if (!used[j] && guess[i] == target[j]) {
                res[i] = 'Y';
                used[j] = 1;
                break;
            }
        }
    }
}

/* ===================== CHARGER DICTIONNAIRE ===================== */
int load_dictionary(char dict[][WORDLEN + 1]) {
    FILE *f = fopen("words.txt", "r");
    if (!f) {
        printf("Erreur ouverture fichier words.txt\n");
        exit(1);
    }

    int n = 0;
    while (fscanf(f, "%5s", dict[n]) != EOF) {
        n++;
    }

    fclose(f);
    return n;
}

/* ===================== MOT SECRET ALEATOIRE ===================== */
void choose_secret(char secret[], char dict[][WORDLEN + 1], int n) {
    srand(time(NULL));
    int index = rand() % n;
    strcpy(secret, dict[index]);
}

/* ===================== COMPATIBILITE ===================== */
int compatible(char word[], char guess[], char fb[]) {
    char test_fb[WORDLEN];
    feedback(word, guess, test_fb);

    for (int i = 0; i < WORDLEN; i++) {
        if (test_fb[i] != fb[i])
            return 0;
    }
    return 1;
}

/* ===================== FILTRER MOTS ===================== */
void filter_words(char dict[][WORDLEN + 1], int possible[],
                  int n, char guess[], char fb[]) {

    for (int i = 0; i < n; i++) {
        if (possible[i] && !compatible(dict[i], guess, fb)) {
            possible[i] = 0;
        }
    }
}

/* ===================== CHOISIR PROCHAIN MOT ===================== */
int choose_next(int possible[], int n) {
    for (int i = 0; i < n; i++) {
        if (possible[i])
            return i;
    }
    return -1;
}



/* ===================== MAIN ===================== */
int main() {
    char dictionary[MAX_WORDS][WORDLEN + 1];
    int dict_size = load_dictionary(dictionary);

    char secret[WORDLEN + 1];
    char guess[WORDLEN + 1];
    char fb[WORDLEN];
    int possible[MAX_WORDS];

    // Choisir mot secret
    choose_secret(secret, dictionary, dict_size);

    // Initialiser les mots possibles
    for (int i = 0; i < dict_size; i++)
        possible[i] = 1;

    printf("=== WORDLE SOLVER ===\n\n");

    for (int attempt = 1; attempt <= MAX_ATTEMPTS; attempt++) {

        int idx = choose_next(possible, dict_size);
        if (idx == -1) {
            printf("Plus aucun mot possible\n");
            return 0;
        }

        strcpy(guess, dictionary[idx]);
        feedback(secret, guess, fb);

        printf("Tentative %d : %s | Feedback : ",
               attempt, guess);
        for (int i = 0; i < WORDLEN; i++)
            printf("%c ", fb[i]);
        printf("\n");

        if (strcmp(guess, secret) == 0) {
            printf("\n SOLVER A GAGNE !\n");
            return 0;
        }

        filter_words(dictionary, possible, dict_size, guess, fb);
    }

    printf("\n SOLVER A ÉCHOUÉ\n");
    printf("Mot secret : %s\n", secret);

    return 0;
}
