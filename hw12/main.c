#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
typedef struct Node {
    void* data;
    struct Node* next;
} Node;

typedef struct {
    char type[20];
    int ivals[1];
    double svals[1];
} Asset1;

typedef struct {
    char type[20];
    double svals[2]; 
    int ivals[2];
} Asset2;

typedef struct {
    char type[20];
    char string1[50];
    char string2[50];
} Asset3;

typedef struct {
    char type[20];
    double value1;
    float value2;
    double value3;
} Asset4;

void fillLinkedList(struct Node** head) {
    srand(time(0));
    int num_nodes = 10 + rand() % 11; //  random number between 10 and 20

    for (int i = 0; i < num_nodes; i++) {
        struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
        int asset_type = 1 + rand() % 4; //  random number between 1 and 4

        switch(asset_type) {
            case 1:
            {
                Asset1* a1 = (Asset1*)malloc(sizeof(Asset1));
                strcpy(a1->type, "Asset1");
                a1->ivals[0] = rand() % 100;
                a1->svals[0] = (double)(rand() % 100);
                new_node->data = a1;
                break;
            }
            case 2:
            {
                Asset2* a2 = (Asset2*)malloc(sizeof(Asset2));
                strcpy(a2->type, "Asset2");
                a2->svals[0] = (double)(rand() % 100);
                a2->svals[1] = (double)(rand() % 100);
                a2->ivals[0] = rand() % 100;
                a2->ivals[1] = rand() % 100;
                new_node->data = a2;
                break;
            }
            case 3:
            {
                Asset3* a3 = (Asset3*)malloc(sizeof(Asset3));
                strcpy(a3->type, "Asset3");
                strcpy(a3->string1, "Random String 1");
                strcpy(a3->string2, "Random String 2");
                new_node->data = a3;
                break;
            }
            case 4:
            {
                Asset4* a4 = (Asset4*)malloc(sizeof(Asset4));
                strcpy(a4->type, "Asset4");
                a4->value1 = (double)(rand() % 100);
                a4->value2 = (float)(rand() % 100);
                a4->value3 = (double)(rand() % 100);
                new_node->data = a4;
                break;
            }
        }
        new_node->next = *head;
        *head = new_node;
    }
}




void printAssetData(Node* head) {
    while (head != NULL) {
        char* type = ((Asset1*)(head->data))->type;

        if (strcmp(type, "Asset1") == 0) {
            Asset1* a = (Asset1*)(head->data);
            printf("Type: %s, First int value: %d, First double value: %.2f\n", type, a->ivals[0], a->svals[0]);
        } else if (strcmp(type, "Asset2") == 0) {
            Asset2* a = (Asset2*)(head->data);
            printf("Type: %s, First double value: %.2f, Second double value: %.2f, First int value: %d, Second int value: %d\n", type, a->svals[0], a->svals[1], a->ivals[0], a->ivals[1]);
        } else if (strcmp(type, "Asset3") == 0) {
            Asset3* a = (Asset3*)(head->data);
            printf("Type: %s, First string: %s, Second string: %s\n", type, a->string1, a->string2);
        } else if (strcmp(type, "Asset4") == 0) {
            Asset4* a = (Asset4*)(head->data);
            printf("Type: %s, First double value: %.2f, Float value: %.2f, Second double value: %.2f\n", type, a->value1, a->value2, a->value3);
        }

        head = head->next;
    }
}
/*
serializeLinkedList işlevi, bağlı listeyi serialize ederek binary bir dosyaya yazıyor. 
Bu sayede, bağlı listedeki verilerin başka bir yerde kullanılabilmesi veya kalıcı olarak saklanabilmesi sağlanıldı. 
deserialize işlemi ise, tam tersine, serileştirilmiş veriyi alarak orijinal bağlı listeyi geri oluşturmayı sağlar.
*/

void serializeLinkedList(struct Node* head) {
    FILE* outfile;

    // Open file for writing
    outfile = fopen("linkedlist.bin", "wb");
    if (outfile == NULL) {
        fprintf(stderr, "\nError opening file\n");
        return;
    }

    // Serialize linked list and write to file
    struct Node* cursor = head;
    while (cursor != NULL) {
        char* type = ((Asset1*)(cursor->data))->type;
        
        if (strcmp(type, "Asset1") == 0) {
            Asset1* a = (Asset1*)(cursor->data);
            fwrite(type, sizeof(char), 20, outfile); // Write the type
            fwrite(a->ivals, sizeof(int), 1, outfile);
            fwrite(a->svals, sizeof(double), 1, outfile);
        } else if (strcmp(type, "Asset2") == 0) {
            Asset2* a = (Asset2*)(cursor->data);
            fwrite(type, sizeof(char), 20, outfile); // Write the type
            fwrite(a->svals, sizeof(double), 2, outfile);
            fwrite(a->ivals, sizeof(int), 2, outfile);
        } else if (strcmp(type, "Asset3") == 0) {
            Asset3* a = (Asset3*)(cursor->data);
            fwrite(type, sizeof(char), 20, outfile); // Write the type
            fwrite(a->string1, sizeof(char), 50, outfile);
            fwrite(a->string2, sizeof(char), 50, outfile);
        } else if (strcmp(type, "Asset4") == 0) {
            Asset4* a = (Asset4*)(cursor->data);
            fwrite(type, sizeof(char), 20, outfile); // Write the type
            fwrite(&(a->value1), sizeof(double), 1, outfile);
            fwrite(&(a->value2), sizeof(float), 1, outfile);
            fwrite(&(a->value3), sizeof(double), 1, outfile);
        }
        
        cursor = cursor->next;
    }

    // Close file
    fclose(outfile);
}

void deserializeLinkedList(struct Node** head) {
    FILE* infile;

    // Open file 
    infile = fopen("linkedlist.bin", "rb");
    if (infile == NULL) {
        fprintf(stderr, "\nError opening file\n");
        return;
    }

    // Read from file and reconstruct linked list
    struct Node* prevNode = NULL; // Önceki düğümü izlemek için bir işaretçi 
    while (!feof(infile)) {
        char type[20];
        fread(type, sizeof(char), 20, infile); // Read the type 

        if (feof(infile)) {
            break;
        }

        struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

        if (strcmp(type, "Asset1") == 0) {
            Asset1* a = (Asset1*)malloc(sizeof(Asset1));
            strcpy(a->type, type);
            fread(a->ivals, sizeof(int), 1, infile);
            fread(a->svals, sizeof(double), 1, infile);
            new_node->data = a;
        } else if (strcmp(type, "Asset2") == 0) {
            Asset2* a = (Asset2*)malloc(sizeof(Asset2));
            strcpy(a->type, type);
            fread(a->svals, sizeof(double), 2, infile);
            fread(a->ivals, sizeof(int), 2, infile);
            new_node->data = a;
        } else if (strcmp(type, "Asset3") == 0) {
            Asset3* a = (Asset3*)malloc(sizeof(Asset3));
            strcpy(a->type, type);
            fread(a->string1, sizeof(char), 50, infile);
            fread(a->string2, sizeof(char), 50, infile);
            new_node->data = a;
        } else if (strcmp(type, "Asset4") == 0) {
            Asset4* a = (Asset4*)malloc(sizeof(Asset4));
            strcpy(a->type, type);
            fread(&(a->value1), sizeof(double), 1, infile);
            fread(&(a->value2), sizeof(float), 1, infile);
            fread(&(a->value3), sizeof(double), 1, infile);
            new_node->data = a;
        }

        new_node->next = NULL; // Yeni düğümün next değeri başlangıçta NULL olacak

        if (*head == NULL) {
            *head = new_node; // Eğer başlangıç düğümü boşsa, yeni düğümü başlangıç düğümü olarak ayarla
        } else {
            prevNode->next = new_node; // Önceki düğümün next değerini yeni düğüm olarak ayarla
        }

        prevNode = new_node; // prevNode'u yeni düğüm olarak güncelle
    }

    // Close file
    fclose(infile);
}



int main() {
    struct Node* node = NULL;

    fillLinkedList(&node);

    printf("\nBEFORE DESERIALIZATION:\n\n");
    printAssetData(node);

    serializeLinkedList(node);

    // Clear the linked list
    while (node != NULL) {
        struct Node* temp = node;
        node = node->next;
        free(temp);
    }
    node = NULL;

    // Now deserialize
    deserializeLinkedList(&node);

    printf("\nAFTER DESERIALIZATION:\n\n");
    printAssetData(node);
    
    
   
    
    
    

    return 0;
}
