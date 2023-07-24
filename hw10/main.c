#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the Book structure
typedef struct Book {
    char isbn[20];
    char title[100];
    char author[50];
    int publicationYear;
    int isReserved;
    struct Book *next;
} Book;

// Define the Student structure
typedef struct Student {
    char name[50];
    int id;
    Book *borrowedBooks;
    struct Student *next;
} Student;
// Function to add a new book to the library
void addBook(char* isbn, char* title, char* author, int publicationYear, int method, Book **head) {
    // Create a new book
    Book *newBook = (Book*)malloc(sizeof(Book));
    strcpy(newBook->isbn, isbn);
    strcpy(newBook->title, title);
    strcpy(newBook->author, author);
    newBook->publicationYear = publicationYear;
    newBook->isReserved = 0;
    newBook->next = NULL;

    // Add the book to the linked list
    if (*head == NULL) {
        *head = newBook;
    } else {
        if (method == 0) { // FIFO
            Book *temp = *head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newBook;
        } else if (method == 1) { // LIFO
            newBook->next = *head;
            *head = newBook;
        }
    }
}
// Function to save book information to a text file
void saveBookData(Book *head) {
    FILE *file = fopen("book_data.txt", "w");
    if (file == NULL) {
        printf("Dosya açılamadı.\n");
        return;
    }

    Book *temp = head;
    while (temp != NULL) {
        fprintf(file, "%s;%s;%s;%d;%d\n", temp->isbn, temp->title, temp->author, temp->publicationYear, temp->isReserved);
        temp = temp->next;
    }

    fclose(file);
}
// Function to read book information from a text file
Book* readBookData() {
    FILE *file = fopen("book_data.txt", "r");
    if (file == NULL) {
        printf("Dosya açılamadı.\n");
        return NULL;
    }

    Book *head = NULL;
    char line[100];

    while (fgets(line, sizeof(line), file)) {
        char *token;
        char isbn[20];
        char title[100];
        char author[100];
        int publicationYear;
        int isReserved;

        token = strtok(line, ";");
        strcpy(isbn, token);

        token = strtok(NULL, ";");
        strcpy(title, token);

        token = strtok(NULL, ";");
        strcpy(author, token);

        token = strtok(NULL, ";");
        publicationYear = atoi(token);

        token = strtok(NULL, "\n");
        isReserved = atoi(token);

        // Create a new book
        Book *newBook = (Book*)malloc(sizeof(Book));
        strcpy(newBook->isbn, isbn);
        strcpy(newBook->title, title);
        strcpy(newBook->author, author);
        newBook->publicationYear = publicationYear;
        newBook->isReserved = isReserved;
        newBook->next = NULL;

        // Add the book to the linked list
        if (head == NULL) {
            head = newBook;
        } else {
            Book *temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newBook;
        }
    }

    fclose(file);
    return head;
}
// Function to delete a book from the library
void deleteBook(char* isbn, Book **head) {
    Book *temp = *head;
    Book *prev = NULL;
    int found = 0;

    // Search for the book
    while (temp != NULL) {
        if (strcmp(temp->isbn, isbn) == 0) {
            found = 1;
            break;
        }
        prev = temp;
        temp = temp->next;
    }

    // If the book is found, remove it from the linked list
    if (found) {
        // If the book is the first node
        if (prev == NULL) {
            *head = temp->next;
        } else {
            prev->next = temp->next;
        }
        free(temp);
        printf("Kitap başarıyla silindi.\n");

        // Update the book data in the text file
        saveBookData(*head);
    } else {
        printf("Verilen ISBN numarasına sahip bir kitap bulunamadı.\n");
    }
}
// Function to update the information of a book in the library
void updateBook(char* isbn, char* feature, char* value, Book** head) {
    Book* temp = *head;
    int found = 0;

    // Search for the book
    while (temp != NULL) {
        if (strcmp(temp->isbn, isbn) == 0) {
            found = 1;
            break;
        }
        temp = temp->next;
    }

    // If the book is found, update the specified feature
    if (found) {
        if (strcmp(feature, "title") == 0) {
            strcpy(temp->title, value);
            printf("Kitap başlığı güncellendi.\n");
        } else if (strcmp(feature, "author") == 0) {
            strcpy(temp->author, value);
            printf("Kitap yazarı güncellendi.\n");
        } else if (strcmp(feature, "year") == 0) {
            int newPublicationYear = atoi(value);
            if (newPublicationYear > 0) {
                temp->publicationYear = newPublicationYear;
                printf("Kitap yayın yılı güncellendi.\n");
            } else {
                printf("Geçersiz yayın yılı değeri.\n");
            }
        } else {
            printf("Geçersiz özellik adı.\n");
        }

        // Save the updated book data to the text file
        saveBookData(*head);
    } else {
        printf("Verilen ISBN numarasına sahip bir kitap bulunamadı.\n");
    }
}

// Function to create a new book
Book* createBook(char* isbn, char* title, char* author, int publicationYear) {
    Book* newBook = (Book*)malloc(sizeof(Book));
    strcpy(newBook->isbn, isbn);
    strcpy(newBook->title, title);
    strcpy(newBook->author, author);
    newBook->publicationYear = publicationYear;
    newBook->next = NULL;
    return newBook;
}
// Function to swap two books
void swapBooks(Book* book1, Book* book2) {
    Book temp = *book1;
    *book1 = *book2;
    *book2 = temp;
}
// Function to add a book to the list
void addBookToList(Book** head, char* isbn, char* title, char* author, int publicationYear) {
    Book* newBook = createBook(isbn, title, author, publicationYear);
    if (*head == NULL) {
        *head = newBook;
    } else {
        Book* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newBook;
    }
}

// Function to sort the books by title
void sortBooksByTitle(Book** head) {
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }
    int swapped;
    Book* current;
    Book* last = NULL;

    do {
        swapped = 0;
        current = *head;

        while (current->next != last) {
            if (strcmp(current->title, current->next->title) > 0) {
                swapBooks(current, current->next);
                swapped = 1;
            }
            current = current->next;
        }
        last = current;
    } while (swapped);
}

// Function to sort the books by author
void sortBooksByAuthor(Book** head) {
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }
    int swapped;
    Book* current;
    Book* last = NULL;

    do {
        swapped = 0;
        current = *head;

        while (current->next != last) {
            if (strcmp(current->author, current->next->author) > 0) {
                swapBooks(current, current->next);
                swapped = 1;
            }
            current = current->next;
        }
        last = current;
    } while (swapped);
}

// Function to sort the books by publication year
void sortBooksByPublicationYear(Book** head) {
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }
    int swapped;
    Book* current;
    Book* last = NULL;

    do {
        swapped = 0;
        current = *head;

        while (current->next != last) {
            if (current->publicationYear > current->next->publicationYear) {
                swapBooks(current, current->next);
                swapped = 1;
            }
            current = current->next;
        }
        last = current;
    } while (swapped);
}

// Function to print the library books
void printLibrary(Book* head) {
    Book* temp = head;
    while (temp != NULL) {
        printf("ISBN: %s, Başlık: %s, Yazar: %s, Yayın Yılı: %d\n", temp->isbn, temp->title, temp->author, temp->publicationYear);
        temp = temp->next;
    }
}

// Function to free the memory allocated for the library
void freeLibrary(Book* head) {
    Book* temp = head;
    while (temp != NULL) {
        Book* current = temp;
        temp = temp->next;
        free(current);
    }
}





// Function to filter and sort books in the library
void filterAndSortBooks(int filterChoice, char* filter, int sortChoice, Book** head) {
    Book* filteredBooks = NULL;
    Book* temp = *head;

    while (temp != NULL) {
        if (filterChoice == 0 && strcmp(temp->author, filter) == 0) { // Filter by author
            addBookToList(&filteredBooks, temp->isbn, temp->title, temp->author, temp->publicationYear);
        } else if (filterChoice == 1 && temp->publicationYear == atoi(filter)) { // Filter by publication year
            addBookToList(&filteredBooks, temp->isbn, temp->title, temp->author, temp->publicationYear);
        }
        temp = temp->next;
    }

    switch (sortChoice) {
        case 0: // Sort by title
            sortBooksByTitle(&filteredBooks);
            break;
        case 1: // Sort by author
            sortBooksByAuthor(&filteredBooks);
            break;
        case 2: // Sort by publication year
            sortBooksByPublicationYear(&filteredBooks);
            break;
        default:
            printf("Geçersiz sıralama seçeneği.\n");
            return;
    }

    printf("Filtrelenmiş ve sıralanmış kitaplar:\n");
    printLibrary(filteredBooks);

    freeLibrary(filteredBooks);
}

// Function to reverse the order of books in the linked list
void reverseBookList(Book** head) {
    Book* prev = NULL;
    Book* current = *head;
    Book* next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    *head = prev;
}

// Function to search for books based on the given criteria
void searchBooks(int searchChoice, char* searchValue, Book* head) {
    int found = 0;
    Book* temp = head;

    while (temp != NULL) {
        if (searchChoice == 0 && strcmp(temp->isbn, searchValue) == 0) { // Search by ISBN number
            printf("ISBN: %s, Başlık: %s, Yazar: %s, Yayın Yılı: %d\n", temp->isbn, temp->title, temp->author, temp->publicationYear);
            found = 1;
        } else if (searchChoice == 1 && strcmp(temp->author, searchValue) == 0) { // Search by author
            printf("ISBN: %s, Başlık: %s, Yazar: %s, Yayın Yılı: %d\n", temp->isbn, temp->title, temp->author, temp->publicationYear);
            found = 1;
        } else if (searchChoice == 2 && strcmp(temp->title, searchValue) == 0) { // Search by title
            printf("ISBN: %s, Başlık: %s, Yazar: %s, Yayın Yılı: %d\n", temp->isbn, temp->title, temp->author, temp->publicationYear);
            found = 1;
        }
        temp = temp->next;
    }

    if (!found) {
        printf("Kitap bulunamadı.\n");
    }
}

// Function to borrow a book
void borrowBook(char* isbn, Book* head) {
    Book* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->isbn, isbn) == 0) {
            if (temp->isReserved == 0) {
                temp->isReserved = 1;
                printf("Kitap başarıyla ödünç alındı.\n");
                return;
            } else {
                printf("Kitap zaten ödünç alınmış.\n");
                return;
            }
        }
        temp = temp->next;
    }
    printf("Kitap bulunamadı.\n");
}

// Function to return a book
void returnBook(char* isbn, Book* head) {
    Book* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->isbn, isbn) == 0) {
            if (temp->isReserved == 1) {
                temp->isReserved = 0;
                printf("Kitap başarıyla iade edildi.\n");
                return;
            } else {
                printf("Kitap zaten mevcut durumda.\n");
                return;
            }
        }
        temp = temp->next;
    }
    printf("Kitap bulunamadı.\n");
}

int main() {
    Book *library = NULL;
    char isbn[20];
    char title[100];
    char author[100];
    int publicationYear;
    char updateIsbn[20];
    char feature[20];
    char value[100];
    int filterChoice;
    char filter[100];
    int sortChoice;
    int searchChoice;
    char searchValue[100];
    char borrowIsbn[20];
    char returnIsbn[20];
    int choice = 0;

    // Read book data from the text file at startup
    library = readBookData();

    do {
        printf("\nKütüphane Menüsü:\n");
        printf("1. Kitap Ekle\n");
        printf("2. Kitapları Listele\n");
        printf("3. Kitap Güncelle\n");
        printf("4. Kitapları Filtrele ve Sırala\n");
        printf("5. Kitap Listesini Ters Çevir\n");
        printf("6. Kitap Ara\n");
        printf("7. Kitap Ödünç Al\n");
        printf("8. Kitap İade Et\n");
        printf("9. Çıkış\n");

        printf("Seçiminizi girin: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Add a new book to the library
                printf("Kitap bilgilerini girin:\n");
                printf("ISBN: ");
                scanf("%s", isbn);
                printf("Başlık: ");
                scanf(" %[^\n]s", title);
                printf("Yazar: ");
                scanf(" %[^\n]s", author);
                printf("Yayın Yılı: ");
                scanf("%d", &publicationYear);

                // Add the book to the library using FIFO method
                addBookToList(&library, isbn, title, author, publicationYear);

                // Save the updated book data to the text file
                saveBookData(library);

                break;
            case 2:
                // Print the library books
                printf("Kütüphanedeki kitaplar:\n");
                printLibrary(library);

                break;
            case 3:
                // Update a book
                printf("Güncellemek istediğiniz kitabın ISBN numarasını girin: ");
                scanf("%s", updateIsbn);
                printf("Güncellenecek özelliği girin (title, author, year): ");
                scanf("%s", feature);
                printf("Yeni değeri girin: ");
                scanf(" %[^\n]s", value);

                updateBook(updateIsbn, feature, value, &library);

                // Save the updated book data to the text file
                saveBookData(library);

                break;
            case 4:
                // Filter and sort books
                printf("Filtreleme seçeneğini girin (0: Yazar, 1: Yayın Yılı): ");
                scanf("%d", &filterChoice);
                printf("Filtreleme kriterini girin: ");
                scanf(" %[^\n]s", filter);
                printf("Sıralama seçeneğini girin (0: Başlık, 1: Yazar, 2: Yayın Yılı): ");
                scanf("%d", &sortChoice);

                filterAndSortBooks(filterChoice, filter, sortChoice, &library);

                // Save the updated book data to the text file
                saveBookData(library);

                break;
            case 5:
                // Reverse the book list
                reverseBookList(&library);

                // Print the reversed library books
                printf("Ters çevrilmiş kütüphanedeki kitaplar:\n");
                printLibrary(library);

                break;
            case 6:
                // Search for books
                printf("Arama seçeneğini girin (0: ISBN, 1: Yazar, 2: Başlık): ");
                scanf("%d", &searchChoice);
                printf("Arama değerini girin: ");
                scanf(" %[^\n]s", searchValue);

                searchBooks(searchChoice, searchValue, library);

                break;
            case 7:
                // Borrow a book
                printf("Ödünç almak istediğiniz kitabın ISBN numarasını girin: ");
                scanf("%s", borrowIsbn);

                borrowBook(borrowIsbn, library);

                // Save the updated book data to the text file
                saveBookData(library);

                break;
            case 8:
                // Return a book
                printf("İade etmek istediğiniz kitabın ISBN numarasını girin: ");
                scanf("%s", returnIsbn);

                returnBook(returnIsbn, library);

                // Save the updated book data to the text file
                saveBookData(library);

                break;
            case 9:
                // Free the memory allocated for the library
                freeLibrary(library);

                break;
            default:
                printf("Geçersiz seçim!\n");
                break;
        }

    } while (choice != 9);

    return 0;
}

