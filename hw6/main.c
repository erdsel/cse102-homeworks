#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

/*
Product structure: This structure represents a product, containing fields such as product ID (pID), type, name, brand, price, and additional features.

Stock structure: This structure represents a stock entry, containing fields such as stock ID (sID), product ID (pID), branch name, and the current stock.
*/
typedef struct {
    int pID;
    char Type;
    char Name[9];
    char Brand[6];
    double Price;
    char Additional_features[256]; // Add this line to support additional features
} Product;

typedef struct {
    int sID;
    int pID;
    char Branch[50];
    int Current_stock;
} Stock;

void print_file_operations_submenu() {

/*
print_file_operations_submenu function: This function prints a submenu for file operations, displaying a list of options such as adding, deleting, or updating products and stock entries. 
The user can also add a new feature to products or return to the main menu.
*/
    printf("File Operations:\n");
    printf("1- Add a new product\n");
    printf("2- Delete a product\n");
    printf("3- Update a product\n");
    printf("4- Add feature to products\n");
    printf("5- Add a new stock entry\n");
    printf("6- Delete a stock entry\n");
    printf("7- Update a stock entry\n");
    printf("8- Return to main menu\n");
}
void add_feature_to_products() {

/*
add_feature_to_products function: This function allows the user to add a new feature to all existing products. The user enters the name of the new feature, and the function proceeds to read the existing products from the "products.txt" file. For each product, it assigns a NULL value to the new feature (i.e., "None") and writes the updated product data to a temporary file "temp_products.txt". After all products have been processed, the original "products.txt" file is removed, and the temporary file is renamed to "products.txt". Finally, the function prints a success message.
*/
    char new_feature[50];
    printf("Enter the name of the new feature: ");
    scanf("%s", new_feature);

    FILE *file = fopen("products.txt", "r");
    FILE *temp_file = fopen("temp_products.txt", "w");

    Product product;
    while (fscanf(file, "%d,%c,%[^,],%[^,],%lf", &product.pID, &product.Type, product.Name, product.Brand, &product.Price) != EOF) {
        // Assign NULL value to the new feature for all products
        strcat(product.Additional_features, new_feature);
        fprintf(temp_file, "%d,%c,%s,%s,%.2lf,%s\n", product.pID, product.Type, product.Name, product.Brand, product.Price, product.Additional_features);
    }

    fclose(file);
    fclose(temp_file);
    remove("products.txt");
    rename("temp_products.txt", "products.txt");

    printf("Feature added successfully.\n");
}
// ADD FEATURE THE PORDUCTS
void add_new_product() {
/*
add_new_product: This function adds a new product to the "products.txt" file. It prompts the user to enter the product's type, name, brand, and price. It then reads the last product ID from the file and assigns the new product the next available ID. Finally, it appends the new product to the file and prints a success message.


*/
    Product new_product;

    printf("Enter the Type (D/F/C/O): ");
    scanf(" %c", &new_product.Type);
    getchar(); // Buffer'Ä± temizlemek iÃ§in

    printf("Enter the Name (max 8 characters): ");
    scanf("%s", new_product.Name);

    printf("Enter the Brand (max 5 characters): ");
    scanf("%s", new_product.Brand);

    printf("Enter the Price: ");
    scanf("%lf", &new_product.Price);

    FILE *file = fopen("products.txt", "a+");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    int last_pID = 0;
    Product product;
    while (fscanf(file, "%d,%c,%[^,],%[^,],%lf", &product.pID, &product.Type, product.Name, product.Brand, &product.Price) != EOF) {
        last_pID = product.pID;
    }

    new_product.pID = last_pID + 1;
    fprintf(file, "%d,%c,%s,%s,%.2lf\n", new_product.pID, new_product.Type, new_product.Name, new_product.Brand, new_product.Price);

    fclose(file);
    printf("Product added successfully.\n");
}

// urun EKLEME

/*
update_product: This function updates an existing product in the "products.txt" file. It prompts the user to enter the product ID (pID) and the feature to update (type, name, brand, or price). It reads the products from the file, and when it finds the product to update, it prompts the user for the new value of the specified feature. It writes the updated product information to a temporary file, then replaces the original file with the temporary file. It prints a success message if the product is found and updated.

delete_product: This function deletes an existing product from the "products.txt" file. It prompts the user to enter the product ID (pID) of the product to delete. It reads the products from the file, and if the product to delete is found, it skips writing it to the temporary file. It also adjusts the product IDs of the remaining products after the deleted one. Finally, it replaces the original file with the temporary file and prints a success message if the product is found and deleted.
*/

void update_product() {
    int pID_to_update;
    printf("Enter the pID of the product to update: ");
    scanf("%d", &pID_to_update);

    char feature[20];
    printf("Enter the feature to update (Type/Name/Brand/Price): ");
    scanf("%s", feature);

    FILE *file = fopen("products.txt", "r");
    FILE *temp_file = fopen("temp_products.txt", "w");

    Product product;
    bool found = false;
    while (fscanf(file, "%d,%c,%[^,],%[^,],%lf", &product.pID, &product.Type, product.Name, product.Brand, &product.Price) != EOF) {
        if (product.pID == pID_to_update) {
            found = true;

            if (strcmp(feature, "Type") == 0) {
                printf("Enter the new Type (D/F/C/O): ");
                scanf(" %c", &product.Type);
            } else if (strcmp(feature, "Name") == 0) {
                printf("Enter the new Name (max 8 characters): ");
                scanf("%s", product.Name);
            } else if (strcmp(feature, "Brand") == 0) {
                printf("Enter the new Brand (max 5 characters): ");
                scanf("%s", product.Brand);
            } else if (strcmp(feature, "Price") == 0) {
                printf("Enter the new Price: ");
                scanf("%lf", &product.Price);
            } else {
                printf("Invalid feature.\n");
                fclose(file);
                fclose(temp_file);
                remove("temp_products.txt");
                return;
            }
        }

        fprintf(temp_file, "%d,%c,%s,%s,%.2lf\n", product.pID, product.Type, product.Name, product.Brand, product.Price);
    }

    fclose(file);
    fclose(temp_file);
    remove("products.txt");
    rename("temp_products.txt", "products.txt");

    if (found) {
        printf("Product updated successfully.\n");
    } else {
        printf("Product not found.\n");
    }
}
// URUN GÃœNCELLEME

/*
delete_stock_entry: This function deletes an existing stock entry from the "stocks.txt" file. It prompts the user to enter the stock ID (sID) of the entry to delete. It reads the stock entries from the file, and if the entry to delete is found, it skips writing it to the temporary file. It also adjusts the stock IDs of the remaining entries after the deleted one. Finally, it replaces the original file with the temporary file and prints a success message if the stock entry is found and deleted.

update_stock_entry: This function updates an existing stock entry in the "stocks.txt" file. It prompts the user to enter the stock ID (sID) and the feature to update (pID, branch, or current_stock). It reads the stock entries from the file, and when it finds the entry to update, it prompts the user for the new value of the specified feature. It writes the updated stock entry information to a temporary file, then replaces the original file with the temporary file. It prints a success message if the stock entry is found and updated.
*/
void delete_product() {
    int pID_to_delete;
    printf("Enter the pID of the product to delete: ");
    scanf("%d", &pID_to_delete);

    FILE *file = fopen("products.txt", "r");
    FILE *temp_file = fopen("temp_products.txt", "w");

    Product product;
    bool found = false;
    while (fscanf(file, "%d,%c,%[^,],%[^,],%lf", &product.pID, &product.Type, product.Name, product.Brand, &product.Price) != EOF) {
        if (product.pID != pID_to_delete) {
            if (found) {
                product.pID--;
            }
            fprintf(temp_file, "%d,%c,%s,%s,%.2lf\n", product.pID, product.Type, product.Name, product.Brand, product.Price);
        } else {
            found = true;
        }
    }

    fclose(file);
    fclose(temp_file);
    remove("products.txt");
    rename("temp_products.txt", "products.txt");

    if (found) {
        printf("Product deleted successfully.\n");
    } else {
        printf("Product not found.\n");
    }
}
// URUN SILME

void add_new_stock_entry() {
    Stock new_stock;

    printf("Enter the pID: ");
    scanf("%d", &new_stock.pID);

    printf("Enter the Branch: ");
    scanf("%s", new_stock.Branch);

    printf("Enter the Current_stock: ");
    scanf("%d", &new_stock.Current_stock);

    FILE *file = fopen("stocks.txt", "a+");

    int last_sID = 0;
    Stock stock;
    while (fscanf(file, "%d,%d,%[^,],%d", &stock.sID, &stock.pID, stock.Branch, &stock.Current_stock) != EOF) {
        if (stock.sID > last_sID) {
            last_sID = stock.sID;
        }
    }

    new_stock.sID = last_sID + 1;
    fprintf(file, "%d,%d,%s,%d\n", new_stock.sID, new_stock.pID, new_stock.Branch, new_stock.Current_stock);

    fclose(file);
    printf("Stock entry added successfully.\n");
}// ADD NEW STOCK


void delete_stock_entry() {
    int sID_to_delete;
    printf("Enter the sID of the stock entry to be deleted: ");
    scanf("%d", &sID_to_delete);

    FILE *file = fopen("stocks.txt", "r");
    FILE *temp_file = fopen("temp_stocks.txt", "w");

    Stock stock;
    bool found = false;
    while (fscanf(file, "%d,%d,%[^,],%d", &stock.sID, &stock.pID, stock.Branch, &stock.Current_stock) != EOF) {
        if (stock.sID == sID_to_delete) {
            found = true;
        } else {
            if (found) {
                stock.sID -= 1;
            }
            fprintf(temp_file, "%d,%d,%s,%d\n", stock.sID, stock.pID, stock.Branch, stock.Current_stock);
        }
    }

    fclose(file);
    fclose(temp_file);
    remove("stocks.txt");
    rename("temp_stocks.txt", "stocks.txt");

    if (found) {
        printf("Stock entry deleted successfully.\n");
    } else {
        printf("Stock entry with the given sID not found.\n");
    }
}
// DELETE STOCK ENTRY



void update_stock_entry() {
    int sID_to_update;
    printf("Enter the sID of the stock entry to be updated: ");
    scanf("%d", &sID_to_update);

    char feature[20];
    printf("Enter the name of the feature to be updated (pID, Branch, Current_stock): ");
    scanf("%s", feature);

    FILE *file = fopen("stocks.txt", "r");
    FILE *temp_file = fopen("temp_stocks.txt", "w");

    Stock stock;
    bool found = false;
    while (fscanf(file, "%d,%d,%[^,],%d", &stock.sID, &stock.pID, stock.Branch, &stock.Current_stock) != EOF) {
        if (stock.sID == sID_to_update) {
            found = true;
            if (strcmp(feature, "pID") == 0) {
                printf("Enter the new pID: ");
                scanf("%d", &stock.pID);
            } else if (strcmp(feature, "Branch") == 0) {
                printf("Enter the new Branch: ");
                scanf("%s", stock.Branch);
            } else if (strcmp(feature, "Current_stock") == 0) {
                printf("Enter the new Current_stock: ");
                scanf("%d", &stock.Current_stock);
            } else {
                printf("Invalid feature name. Update canceled.\n");
                break;
            }
        }
        fprintf(temp_file, "%d,%d,%s,%d\n", stock.sID, stock.pID, stock.Branch, stock.Current_stock);
    }

    fclose(file);
    fclose(temp_file);
    remove("stocks.txt");
    rename("temp_stocks.txt", "stocks.txt");

    if (found) {
        printf("Stock entry updated successfully.\n");
    } else {
        printf("Stock entry with the given sID not found.\n");
    }
}
// UPDATE STOCK ENTRY


void file_operations() {
    int option;

    while (1) {
        print_file_operations_submenu();
        scanf("%d", &option);

        switch (option) {
            case 1:
                add_new_product();
                break;
            case 2:
                delete_product();
                break;
            case 3:
                update_product();
                break;
            case 4:
                add_feature_to_products();
                break;
            case 5:
                add_new_stock_entry();
                break;
            case 6:
                delete_stock_entry();
                break;
            case 7:
                update_stock_entry();
                break;
            case 8:
                return;  // Back to main menu
            default:
                printf("Invalid option. Please try again.\n");
        }
    }
}

void print_menu() {
    printf("Welcome operator, please select an option to continue:\n");
    printf("1- File Operations\n");
    printf("2- Query products\n");
    printf("3- Check stock status\n");
    printf("4- Stock control by brand\n");
    printf("5- Export report\n");
}



void print_search_product_menu() {
    printf("Please select an option to continue:\n");
    printf("1- List all products\n");
    printf("2- Filter products by brand, type, price, or a user-defined feature\n");
    printf("3- Back to main menu\n");
}
/*

list_all_products: This function reads and displays all products from the "products.txt" file. It opens the file, prints the table header (pID, Type, Name, Brand, and Price), and then reads each product from the file. For each product, it prints its pID, type, name, brand, and price. After processing all products, it closes the file.

is_filter_match: This function checks if a product matches the given filter criteria. It takes a product and a filter string as input. The filter string is in the format "key,value" (e.g., "brand,Samsung"). The function extracts the key and value from the filter string and then checks if the product's corresponding attribute matches the value. If the product's attribute matches the value, the function returns true; otherwise, it returns false.

filter_products: This function reads products from the "products.txt" file and displays only those that match the given filter criteria. It prompts the user to enter a filter string and then opens the file. It prints the table header (pID, Type, Name, Brand, and Price) and reads each product from the file. For each product, it calls the is_filter_match function with the given filter. If the product matches the filter, it prints the product's pID, type, name, brand, and price. After processing all products, it closes the file.

search_product: This function provides an interface for users to search for products by displaying a menu with options to list all products, filter products, or return to the main menu. It continuously prompts the user to choose an option and performs the corresponding action based on the user's choice. If the user chooses option 1, it calls the list_all_products function; if the user chooses option 2, it calls the filter_products function; if the user chooses option 3, it returns to the main menu. If the user chooses an invalid option, it displays an error message and prompts the user to try again.

*/
void list_all_products() {
    FILE *file = fopen("products.txt", "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    printf("pID\tType\tName\tBrand\tPrice\n");
    Product product;
    while (fscanf(file, "%d,%c,%[^,],%[^,],%lf", &product.pID, &product.Type, product.Name, product.Brand, &product.Price) != EOF) {
        printf("%d\t%c\t%s\t%s\t%.2lf\n", product.pID, product.Type, product.Name, product.Brand, product.Price);
    }
    fclose(file);
}

bool is_filter_match(Product product, const char *filter) {
    char key[20], value[20];
    sscanf(filter, "%[^,],%s", key, value);

    if (strcmp(key, "brand") == 0 && strcmp(product.Brand, value) == 0) {
        return true;
    } else if (strcmp(key, "type") == 0 && product.Type == value[0]) {
        return true;
    } else if (strcmp(key, "price") == 0 && product.Price == atof(value)) {
        return true;
    }
    return false;
}

void filter_products() {
    char filter[100];
    printf("Enter your filter (e.g. 'brand,Samsung,type,O'): ");
    scanf(" %99[^\n]", filter);

    FILE *file = fopen("products.txt", "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    printf("Filtered products:\n");
    printf("pID\tType\tName\tBrand\tPrice\n");
    Product product;
    while (fscanf(file, "%d,%c,%[^,],%[^,],%lf", &product.pID, &product.Type, product.Name, product.Brand, &product.Price) != EOF) {
        if (is_filter_match(product, filter)) {
            printf("%d\t%c\t%s\t%s\t%.2lf\n", product.pID, product.Type, product.Name, product.Brand, product.Price);
        }
    }
    fclose(file);
}

void search_product() {
    int option;

    while (1) {
        print_search_product_menu();
        scanf("%d", &option);

        switch (option) {
            case 1:
                list_all_products();
                break;
            case 2:
                filter_products();
                break;
            case 3:
                return;  // Back to main menu
            default:
                printf("Invalid option. Please try again.\n");
        }
    }
}



void loadStocksFromFile(Stock **stocks, int *stockCount);
void queryStockByProductAndBranch(Stock *stocks, int stockCount);
void listStocksInBranch(Stock *stocks, int stockCount);
void listOutOfStockProductsInBranch(Stock *stocks, int stockCount);

void brand_stock_control() {
    FILE *product_file = fopen("products.txt", "r");
    FILE *stock_file = fopen("stocks.txt", "r");
    char brand[6];
    int product_count = 0;
    int stock_count = 0;
    Product products[100];
    Stock stocks[100];
    
    if (product_file == NULL || stock_file == NULL) {
        printf("Error opening files.\n");
        return;
    }
    
    // Read products from the file and store them in the Product struct array
    while (fscanf(product_file, "%d,%c,%[^,],%[^,],%lf,%[^\n]", &products[product_count].pID, &products[product_count].Type, products[product_count].Name, products[product_count].Brand, &products[product_count].Price, products[product_count].Additional_features) != EOF) {
        product_count++;
    }
    
    // Read stocks from the file and store them in the Stock struct array
    while (fscanf(stock_file, "%d,%d,%[^,],%d", &stocks[stock_count].sID, &stocks[stock_count].pID, stocks[stock_count].Branch, &stocks[stock_count].Current_stock) != EOF) {
        stock_count++;
    }
    
    // Get the brand from the user
    printf("Enter the brand name: ");
    scanf("%s", brand);
    
    int brand_products_count = 0;
    double brand_products[100][3]; // 2D array to store pID, price, and current stock values of products
    int i,j;
    // Iterate through Stock struct and match the pID with the Product struct to get the brand of the product
    for ( i = 0; i < stock_count; i++) {
        for ( j = 0; j < product_count; j++) {
            if (stocks[i].pID == products[j].pID) {
                if (strcmp(products[j].Brand, brand) == 0) { // If the brand matches with the given brand
                    // Store the pID, price, and current stock values of that product in the 2D array
                    brand_products[brand_products_count][0] = stocks[i].pID;
                    brand_products[brand_products_count][1] = products[j].Price;
                    brand_products[brand_products_count][2] = stocks[i].Current_stock;
                    brand_products_count++;
                }
                break;
            }
        }
    }
    
    // Print the 2D array
    printf("Products of %s brand with their current stock:\n", brand);
    printf("pID\tPrice\tCurrent Stock\n");
    
    for (i = 0; i < brand_products_count; i++) {
        printf("%d\t%.2f\t%d\n", (int)brand_products[i][0], brand_products[i][1], (int)brand_products[i][2]);
    }
    
    fclose(product_file);
    fclose(stock_file);
}

void stock_report() {
    FILE *product_file = fopen("products.txt", "r");
    FILE *stock_file = fopen("stocks.txt", "r");
    char brand[6];
    int product_count = 0;
    int stock_count = 0;
    Product products[100];
    Stock stocks[100];
    
    if (product_file == NULL || stock_file == NULL) {
        printf("Error opening files.\n");
        return;
    }
    
    // Read products from the file and store them in the Product struct array
    while (fscanf(product_file, "%d,%c,%[^,],%[^,],%lf,%[^\n]", &products[product_count].pID, &products[product_count].Type, products[product_count].Name, products[product_count].Brand, &products[product_count].Price, products[product_count].Additional_features) != EOF) {
        product_count++;
    }
    
    // Read stocks from the file and store them in the Stock struct array
    while (fscanf(stock_file, "%d,%d,%[^,],%d", &stocks[stock_count].sID, &stocks[stock_count].pID, stocks[stock_count].Branch, &stocks[stock_count].Current_stock) != EOF) {
        stock_count++;
    }
    
    // Get the brand from the user
    printf("Enter the brand name: ");
    scanf("%s", brand);
    
    int brand_products_count = 0;
    double brand_products[100][3]; // 2D array to store pID, price, and current stock values of products
    int i,j;
    // Iterate through Stock struct and match the pID with the Product struct to get the brand of the product
    for ( i = 0; i < stock_count; i++) {
        for ( j = 0; j < product_count; j++) {
            if (stocks[i].pID == products[j].pID) {
                if (strcmp(products[j].Brand, brand) == 0) { // If the brand matches with the given brand
                    // Store the pID, price, and current stock values of that product in the 2D array
                    brand_products[brand_products_count][0] = stocks[i].pID;
                    brand_products[brand_products_count][1] = products[j].Price;
                    brand_products[brand_products_count][2] = stocks[i].Current_stock;
                    brand_products_count++;
                }
                break;
            }
        }
    }
    
    // Print the 2D array
    printf("Products of %s brand with their current stock:\n", brand);
    printf("pID\tPrice\tCurrent Stock\n");
    
    for (i = 0; i < brand_products_count; i++) {
        printf("%d\t%.2f\t%d\n", (int)brand_products[i][0], brand_products[i][1], (int)brand_products[i][2]);
    }
    
    // Calculate minimum, maximum, and median stock values for each product
    int stock_values[brand_products_count][4]; // 2D array to store required stock values
    for (i = 0; i < brand_products_count; i++) {
        stock_values[i][0] = (int)brand_products[i][0]; // pID
        stock_values[i][1] = (int)brand_products[i][2]; // current stock value
        stock_values    [i][2] = (int)brand_products[i][2]; // current stock value (set initial value for maximum)
    stock_values[i][3] = (int)brand_products[i][2]; // current stock value (initialize total stock value to calculate median)
}

for (i = 0; i < brand_products_count; i++) {
    for (j = i + 1; j < brand_products_count; j++) {
        if (stock_values[i][0] == stock_values[j][0]) { // If the pID of two products match
            if (stock_values[j][1] < stock_values[i][1]) {
                stock_values[i][1] = stock_values[j][1]; // Update minimum stock value
            }
            if (stock_values[j][2] > stock_values[i][2]) {
                stock_values[i][2] = stock_values[j][2]; // Update maximum stock value
            }
            stock_values[i][3] += stock_values[j][2]; // Add current stock value to calculate median
            stock_values[j][0] = -1; // Mark the product as processed
        }
    }
}

// Write stock report to file
FILE *report_file = fopen("stock_report.txt", "w");
if (report_file == NULL) {
    printf("Error opening file.\n");
    return;
}
for (i = 0; i < brand_products_count; i++) {
    if (stock_values[i][0] == -1) {
        continue; // Skip already processed products
    }
    int median = stock_values[i][3] / 3; // assuming there are three branches
    fprintf(report_file, "%d,%d,%d,%d\n", stock_values[i][0], stock_values[i][1],
            stock_values[i][2], median);
}
fclose(report_file);

fclose(product_file);
fclose(stock_file);
}


int main() {
    bool is_running = true;
    int option;
    int stock_count;
    Stock *stocks = NULL;
    int stockCount = 0;




    while (is_running) {
        print_menu();
        scanf("%d", &option);

        switch (option) {
            case 1:
                file_operations();
                break;
            case 2:
                search_product();
                break;
            case 3:
            	
            	
    loadStocksFromFile(&stocks, &stockCount);

    int choice = 0;
    while (choice != 4) {
        printf("\n1. Query stock of a product in a branch\n");
        printf("2. List stock of all products in a branch\n");
        printf("3. List out-of-stock products in a branch\n");
        printf("4. Return to main menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                queryStockByProductAndBranch(stocks, stockCount);
                break;
            case 2:
                listStocksInBranch(stocks, stockCount);
                break;
            case 3:
                listOutOfStockProductsInBranch(stocks, stockCount);
                break;
            case 4:
                printf("Returning to main menu.\n");
                break;
            default:
                printf("Invalid choice, please try again.\n");
        }
    }

    free(stocks);

            	
                break;
            case 4:
                 
                
                    // Call brand_stock_control function with the given brand
                    brand_stock_control();
                break;
            case 5:
                stock_report();
                is_running = false;
                break;
            default:
                printf("Invalid option. Please try again.\n");
        }
    }

    return 0;
}

void loadStocksFromFile(Stock **stocks, int *stockCount) {
    FILE *file = fopen("stocks.txt", "r");
    if (!file) {
        printf("Unable to open stocks.txt\n");
        exit(1);
    }

    int sID, pID, stock;
    char branch[50];
  //  fscanf(file, "%*[^\n]\n"); // Ignore header line

    while (fscanf(file, "%d,%d,%[^,],%d", &sID, &pID, branch, &stock) == 4) {
        *stocks = realloc(*stocks, (*stockCount + 1) * sizeof(Stock));
        (*stocks)[*stockCount].sID = sID;
        (*stocks)[*stockCount].pID = pID;
        strcpy((*stocks)[*stockCount].Branch, branch);
        (*stocks)[*stockCount].Current_stock = stock;
        (*stockCount)++;
    }

    fclose(file);
}


void queryStockByProductAndBranch(Stock *stocks, int stockCount) {
    int pID,i;
    char branch[50];
    printf("Enter product ID: ");
    scanf("%d", &pID);
    printf("Enter branch name: ");
    scanf("%49s", branch);

    for ( i = 0; i < stockCount; i++) {
        if (stocks[i].pID == pID && strcmp(stocks[i].Branch, branch) == 0) {
        	printf("Product %d has %d units in stock at %s branch.\n", pID, stocks[i].Current_stock, branch);
            return;
        }
    }

    printf("No stock information found for product %d at %s branch.\n", pID, branch);
}


void listStocksInBranch(Stock *stocks, int stockCount) {
    char branch[50];
    int i;
    printf("Enter branch name: ");
    scanf("%49s", branch);

    printf("Stocks in %s branch:\n", branch);
    for ( i = 0; i < stockCount; i++) {
        if (strcmp(stocks[i].Branch, branch) == 0) {
            printf("Product %d: %d units\n", stocks[i].pID, stocks[i].Current_stock);
        }
    }
}


void listOutOfStockProductsInBranch(Stock *stocks, int stockCount) {
    char branch[50];
    int i;
    printf("Enter branch name: ");
    scanf("%49s", branch);

    printf("Out-of-stock products in %s branch:\n", branch);
    int found = 0;
    for (i = 0; i < stockCount; i++) {
        if (strcmp(stocks[i].Branch, branch) == 0 && stocks[i].Current_stock == 0) {
            printf("Product %d\n", stocks[i].pID);
            found = 1;
        }
    }

    if (!found) {
        printf("No out-of-stock products in %s branch.\n", branch);
    }
}

void read_products(Product products[], int *num_products) {
    FILE *file = fopen("products.txt", "r");
    if (!file) {
        printf("Error: Unable to open products.txt\n");
        return;
    }

    *num_products = 0;

    // Read products from the file
    // Assuming each line is formatted as: pID,Type,Name,Brand,Price,Additional_features
    while (fscanf(file, "%d,%c,%[^,],%[^,],%lf,%[^\n]", &products[*num_products].pID, &products[*num_products].Type,
                  products[*num_products].Name, products[*num_products].Brand, &products[*num_products].Price,
                  products[*num_products].Additional_features) != EOF) {
        (*num_products)++;
    }

    fclose(file);
}

void read_stocks(Stock stocks[], int *num_stocks) {
    FILE *file = fopen("stocks.txt", "r");
    if (!file) {
        printf("Error: Unable to open stocks.txt\n");
        return;
    }

    *num_stocks = 0;

    // Read stocks from the file
    // Assuming each line is formatted as: sID,pID,branch,current_stock
    while (fscanf(file, "%d,%d,%[^,],%d", &stocks[*num_stocks].sID, &stocks[*num_stocks].pID,
                  stocks[*num_stocks].Branch, &stocks[*num_stocks].Current_stock) != EOF) {
        (*num_stocks)++;
    }

    fclose(file);
}



