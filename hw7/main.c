#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_COUNT 10000000
#define MAX_WORD_SIZE 50
#define VECTOR_SIZE 200
#define MAX_IGNORE_WORDS 100
#define BUFFER_SIZE (MAX_WORD_SIZE * (VECTOR_SIZE + 2))

int read_dict(const char *file_name, char dict[][MAX_WORD_SIZE], float vectors[][VECTOR_SIZE]) {
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    char buffer[BUFFER_SIZE];
    if (fgets(buffer, BUFFER_SIZE, file) == NULL) {
        fclose(file);
        fprintf(stderr, "Error reading the first line of the dictionary file.\n");
        return -1;
    }

    int num_words, vector_size;
    if (sscanf(buffer, "num_word=%d, vector_size=%d", &num_words, &vector_size) != 2) {
        fclose(file);
        fprintf(stderr, "Error parsing the first line of the dictionary file.\n");
        fprintf(stderr, "Expected format: num_word=<integer>, vector_size=<integer>\n");
        fprintf(stderr, "Actual content: %s\n", buffer);
        return -1;
    }

    if (num_words > MAX_WORD_COUNT) {
        fclose(file);
        fprintf(stderr, "The number of words in the dictionary exceeds the maximum limit.\n");
        return -1;
    }

    if (vector_size != VECTOR_SIZE) {
        fclose(file);
        fprintf(stderr, "The vector size in the dictionary file does not match the VECTOR_SIZE constant.\n");
        return -1;
    }

    int i, j;
    for (i = 0; i < num_words; i++) {
        if (fgets(buffer, BUFFER_SIZE, file) == NULL) {
            fclose(file);
            return -1;
        }

        char *token = strtok(buffer, " ");
        if (token == NULL) {
            fclose(file);
            return -1;
        }
        strncpy(dict[i], token, MAX_WORD_SIZE - 1);
        dict[i][MAX_WORD_SIZE - 1] = '\0';

        for (j = 0; j < vector_size; j++) {
            token = strtok(NULL, " ");
            if (token == NULL) {
                fclose(file);
                return -1;
            }
            vectors[i][j] = strtof(token, NULL);
        }
    }

    strcpy(dict[num_words], "-");
    fclose(file);
    return num_words;
}



float doubledissimilarity(char *w1, char *w2, char dict[][MAX_WORD_SIZE], float vectors[][VECTOR_SIZE], float threshold, int num_words) {
    int i, j, k;
    float diff, sum_diffs = 0;

    int index1 = -1, index2 = -1;

    for (i = 0; i < num_words; i++) {
        if (strcmp(dict[i], w1) == 0) {
            index1 = i;
        }
        if (strcmp(dict[i], w2) == 0) {
            index2 = i;
        }
        if (index1 != -1 && index2 != -1) {
            break;
        }
    }

    if (index1 == -1 || index2 == -1) {
        return -1;
    }

    for (k = 0; k < VECTOR_SIZE; k++) {
        diff = vectors[index1][k] - vectors[index2][k];
        sum_diffs += (diff * diff);
    }
    return sum_diffs;
}

int is_punctuation(char c) {
    return (c == '.' || c == ',' || c == ';' || c == ':' || c == '!' || c == '?');
}

int read_ignore_words(const char *ignore_file, char ignore_words[][MAX_WORD_SIZE]) {
    FILE *file = fopen(ignore_file, "r");
    if (file == NULL) {
        return 0;
    }

    int ignore_count = 0;
    while (fscanf(file, "%s", ignore_words[ignore_count]) == 1) {
        ignore_count++;
    }

    strcpy(ignore_words[ignore_count], "-");
    fclose(file);
    return ignore_count;
}

int should_ignore(const char *word, char ignore_words[][MAX_WORD_SIZE], int ignore_count) {
    for (int i = 0; i < ignore_count; i++) {
        if (strcmp(word, ignore_words[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int read_text(const char *text_file, char ignore_words[][MAX_WORD_SIZE], int ignore_count, char words[][MAX_WORD_SIZE]) {
    FILE *file = fopen(text_file, "r");
    if (file == NULL) {
        return -1;
    }

    int word_count = 0;
    char buffer[4096];
    size_t bytes_read = 0;
    char *line;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        line = buffer;
        while ((line = strchr(line, '\n')) != NULL) {
            line++; // Skip over the newline character
            int i = 0;
            char word[MAX_WORD_SIZE];
            while (*line != '\0' && i < MAX_WORD_SIZE - 1) {
                if (is_punctuation(*line)) {
                    line++;
                    continue;
                }
                int j = 0;
                while (!is_punctuation(*line) && *line != '\0' && j < MAX_WORD_SIZE - 1) {
                    word[j++] = tolower((unsigned char)*line++);
                }
                word[j] = '\0';

                if (!should_ignore(word, ignore_words, ignore_count)) {
                    strncpy(words[word_count++], word, MAX_WORD_SIZE - 1);
                    words[word_count - 1][MAX_WORD_SIZE - 1] = '\0';
                }
            }
        }
    }

    strcpy(words[word_count], "-");
    fclose(file);
    return word_count;
}


/*
int histogram(const char words[][MAX_WORD_SIZE], const int occurrences[], char hist[][MAX_WORD_SIZE + 5 + 20]) {
    int max_occurrences = 0;
    int index = 0;
    while (strcmp(words[index], "-") != 0) {
        if (occurrences[index] > max_occurrences) {
            max_occurrences = occurrences[index];
        }
        index++;
    }

    int scale = max_occurrences > 20 ? max_occurrences / 20 : 1;
int j;
    index = 0;
    while (strcmp(words[index], "-") != 0) {
        int num_chars = occurrences[index] / scale;
        sprintf(hist[index], "%s: ", words[index]);
        for ( j = 0; j < num_chars; j++) {
            strcat(hist[index], "*");
        }
        index++;
    }

    strcpy(hist[index], "-");
    return scale;
}

int find_word_index(char *word, char dict[][MAX_WORD_SIZE], int dict_size) {
	int i;
    for ( i = 0; i < dict_size; i++) {
        if (strcmp(word, dict[i]) == 0) {
            return i;
        }
    }
    return -1;
    }
int find_word(const char words[][MAX_WORD_SIZE], const char *word) {
    int i = 0;
    while (strcmp(words[i], "-") != 0) {
        if (strcmp(words[i], word) == 0) {
            return i;
        }
        i++;
    }
    return -1;
}
int find_closest_word(const char words[][MAX_WORD_SIZE], const char *word, float threshold) {
    int closest_index = -1;
    double min_dissimilarity = 1000000.0; // buyuk bir baslangıc degeri
    int i = 0;

    int dict_size = 0;
    while (strcmp(words[dict_size], "-") != 0) {
        dict_size++;
    }

    float vectors[MAX_NUM_WORDS][MAX_VECTOR_SIZE]; // Veektorleri temsil eden float dizisi
    
    memset(vectors, 0, sizeof(float) * MAX_NUM_WORDS * MAX_VECTOR_SIZE);

    while (strcmp(words[i], "-") != 0) {
        double dissim = dissimilarity((char )words[i], (char *)word, vectors, (char ()[MAX_WORD_SIZE])words, dict_size);
        if (dissim < min_dissimilarity) {
            min_dissimilarity = dissim;
            closest_index = i;
        }
        i++;
    }

    if (min_dissimilarity <= threshold) {
        return closest_index;
    } else {
        return -1;
    }
    }
*/


int main() {
    // Read ignore words
    char ignore_words[MAX_IGNORE_WORDS][MAX_WORD_SIZE];
    int ignore_count = read_ignore_words("ignore.txt", ignore_words);

    char words[MAX_WORD_COUNT][MAX_WORD_SIZE];
    int num_words = read_text("input.txt", ignore_words, ignore_count, words);

    if (num_words == -1) {
        printf("Error reading text.\n");
        exit(EXIT_FAILURE);
    }

    printf("Text contains %d words:\n", num_words);

    char dictionary[MAX_WORD_COUNT][MAX_WORD_SIZE];
    float vectors[MAX_WORD_COUNT][VECTOR_SIZE];
    int num_words2 = read_dict("dictionary.txt", dictionary, vectors);

    if (num_words2 == -1) {
        printf("Error reading dictionary.\n");
        exit(EXIT_FAILURE);
    }

    printf("Dictionary contains %d words:\n", num_words2);

    float similarity = doubledissimilarity("car", "bus", dictionary, vectors, 0.5, num_words2);
    printf("Similarity between car and bus: %f\n", similarity);

    return 0;
}


