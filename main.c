// Bismillahir Rohmanir Rohiym
//Khamidullokhon ibn Khabibulla 
//Library Book Managenment System
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Staff_password "books123"

//First I broke the whole code into chunks to make it eas
void mainMenu();
void staffMenu();
int staffLogin();
void visitorMenu();
void displayBooks();
void addBook();
void searchBook();
void searchByID();
void searchByTitle();
void searchByAuthor();
void updateBook();
void deleteBook();
void borrowBook();
void returnBook();

int main() { 
    mainMenu();
    
return 0;
}

void mainMenu(){
    int choice;
    
    while (1) {
        printf("*******************************\n");
        printf("Library Book Managenment System\n");
        printf("*******************************\n\n");
        printf("          MAIN MENU         \n");
        printf("1. Staff Login\n");
        printf("2. Visitor access\n");
        printf("3. Contact Information\n");
        printf("4. Exit\n");
        printf("Enter your choice:\n");
        scanf("%d", &choice);
    
        switch (choice) {
        case 1:
        if(staffLogin()){
         staffMenu();
        }else { printf("\nIncorrect password!\n");}
        break;
        
        case 2:
        visitorMenu();
        break;
        
        case 3:
        printf("\n===== Contact Information =====\n");
        printf("Library Email: ilmtolibi@gmail.edu\n");
        printf("Phone: +998-99-511-30-36\n");
        printf("Location: Akhsi street, Library\n");
        break;
        
        case 4:
        printf("\nExiting Program...\n");
        exit(0);
        
        default:
        printf("\n<<<Invalid choice! Please try again.>>>");
        }
    }
}    

//Staff login
int staffLogin(){
    char password[50];
    printf("\nPlease, Enter Staff Password: ");
    scanf("%s", password); 
    if(strcmp(password, Staff_password) == 0)
              return 1;
    
return 0;
}

void staffMenu() {
    int choice;
    
    while (1) {
        printf("\n========== STAFF MENU ==========\n");
        printf("1. Add Book\n");
        printf("2. Search Book\n");
        printf("3. Update Book\n");
        printf("4. Delete Book\n");
        printf("5. Display All Books\n");
        printf("6. Log out\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                addBook();
                break;
            
            case 2:
                searchBook();
                break;
                
            case 3:
                updateBook();
                break;
                
            case 4:
                deleteBook();
                break;
            
            case 5:
               displayBooks();
                break;
                
            case 6:
                printf("Logging out...\n");
                return;
                
            default:
            printf("Invalid choice! Try again.\n");
            
        }
    }   
}

//VISITOR MENU
void visitorMenu() {
    int choice;

    while(1) {
        printf("========= VISITOR MENU =========\n");
        printf("1. Search Book\n");
        printf("2. Borrow Book\n");
        printf("3. Return Book\n");
        printf("4. Display Books\n");
        printf("5. Exit to Main Menu:\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

    
        switch (choice) {
            case 1:
                searchBook();
                break;
                
            case 2:
                borrowBook();
                break;
                
            case 3:
                returnBook();
                break;
                
            case 4:
                displayBooks();
                break;
                
            case 5:
                printf("Exiting to Main Menu...\n");
                return;
                
            default:
                printf("\nInvalid choice! Try again.\n");
        }
    }
}

//Add Book: File handling and Structure

typedef struct {
    int id;
    char title[50];
    char author[50];
    char category[30];
    int year;
    int isBorrowed; // 0 and 1, if borrowed -> 1
    char borrowedBy[50]; 
    char borrowerPhone[20];
}Book;

void addBook() {
    Book b;
    FILE *fp;
    
    fp = fopen("books.dat", "ab");
    if (fp == NULL){
        printf("There is an error to open file!\n");
        return;
    }
    
    printf("Enter Book ID: ");
    scanf("%d", &b.id);
    
    printf("Enter the Book Title: ");
    getchar();
    fgets(b.title, 50, stdin);
    b.title[strcspn(b.title, "\n")] = 0;
    
    printf("Enter Author Name: ");
    fgets(b.author, 50, stdin);
    b.author[strcspn(b.author, "\n")] = 0;
    
    printf("Enter Book Category: ");
    fgets(b.category, 30, stdin);
    b.category[strcspn(b.category, "\n")] = 0;
    
    printf("Enter Publication year: ");
    scanf("%d", &b.year);
    
    b.isBorrowed = 0;
    strcpy(b.borrowedBy, "");
    strcpy(b.borrowerPhone, "");
    
    fwrite(&b, sizeof(Book), 1, fp); //RAM struct data to the file
    fclose(fp);
    
    printf("\nBook added successfully!\n");
}

void displayBooks() {
    FILE *fp;
    Book b;
    
    fp = fopen("books.dat", "rb"); //read binary
    if (fp == NULL) {
        printf("\nNo books found! File does not exist. \n\n");
        return;
    }
    
    printf("\n========= BOOK LIST =========\n");
    printf("%-5s %-25s %-20s %-15s %-6s %10s\n", "ID", "Title", "Author", "Category", "Year", "Status");
    printf("----------------------------------------------\n");
    
    while (fread(&b, sizeof(Book), 1, fp) == 1) {
        printf("%-5d %-25s %-20s %-15s %-6d %10s\n", b.id, b.title, b.author, b.category, b.year, b.isBorrowed ? "Borrowed" : "Available");
    }
    
    fclose(fp);
}

void searchBook(){
    int choice;
    
    printf("\n=========== SEARCH MENU ===========\n");
    printf("1. Search by Book ID\n");
    printf("2. Search by Title\n");
    printf("3. Search by Author\n");
    printf("4. Return\n ");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    
    switch(choice) {
        case 1:
            searchByID();
            break;
        
        case 2:
            //searchByTitle();
            searchByTitle();
            break;
            
        case 3:
            // searchByAuthor;
            searchByAuthor();
            break;
            
        case 4: 
            return;
        
        default:
            printf("\nInvalid choice! Try again.\n");
    }
}

void searchByID(){
    FILE *fp = fopen("books.dat", "rb");
    if (fp == NULL) {
        printf("\nNo books exist");
        return;
    }
    
    int id;
    Book b;
    int found = 0;
    
    printf("\nEnter Book ID to search: ");
    scanf("%d", &id);

while(fread(&b, sizeof(Book), 1, fp) == 1) {
    if (b.id == id) {
        printf("\nBook found:\n");
        printf("ID: %d\n", b.id);
        printf("Title: %s\n", b.title);
        printf("Category: %s\n", b.category);
        printf("Year: %d", b.year);
        printf("Status: %s\n", b.isBorrowed ? "Borrowed" : "Availabe");
        found = 1;
        break;
    }
}

fclose(fp);

if(!found) {
    printf("\nNo book found with ID %d\n", id);
    }
}

void searchByTitle() {
    FILE *fp = fopen("books.dat", "rb");
    if (fp == NULL) {
        printf("\nNo books found!\n");
        return;
    }

    char title[50];
    Book b;
    int found = 0;

    printf("\nEnter Title to search: ");
    getchar();  
    fgets(title, 50, stdin);
    title[strcspn(title, "\n")] = 0;

    printf("\nSearch Results:\n");

    while (fread(&b, sizeof(Book), 1, fp) == 1) {
        if (strstr(b.title, title) != NULL) {
            printf("\nID: %d\n", b.id);
            printf("Title: %s\n", b.title);
            printf("Author: %s\n", b.author);
            printf("Category: %s\n", b.category);
            printf("Year: %d\n", b.year);
            printf("Status: %s\n", b.isBorrowed ? "Borrowed" : "Available");
            found = 1;
        }
    }

    fclose(fp);

    if (!found) {
        printf("\nNo matching books found.\n");
    }
}

void searchByAuthor() {
    FILE *fp = fopen("books.dat", "rb");
    if (fp == NULL) {
        printf("\nNo books found!\n");
        return;
    }

    char author[50];
    Book b;
    int found = 0;

    printf("\nEnter Author Name to search: ");
    getchar();
    fgets(author, 50, stdin);
    author[strcspn(author, "\n")] = 0;

    printf("\nSearch Results:\n");

    while (fread(&b, sizeof(Book), 1, fp) == 1) {
        if (strstr(b.author, author) != NULL) {
            printf("\nID: %d\n", b.id);
            printf("Title: %s\n", b.title);
            printf("Author: %s\n", b.author);
            printf("Category: %s\n", b.category);
            printf("Year: %d\n", b.year);
            printf("Status: %s\n", b.isBorrowed ? "Borrowed" : "Available");
            found = 1;
        }
    }

    fclose(fp);

    if (!found) {
        printf("\nNo books found for author '%s'.\n", author);
    }
}

void updateBook() {
    FILE *fp, *temp;
    Book b;
    int id, found = 0;

    fp = fopen("books.dat", "rb");
    if (fp == NULL) {
        printf("\nNo books found!\n");
        return;
    }

    temp = fopen("temp.dat", "wb");
    if (temp == NULL) {
        printf("\nError creating temporary file!\n");
        fclose(fp);
        return;
    }

    printf("\nEnter Book ID to update: ");
    scanf("%d", &id);

    while (fread(&b, sizeof(Book), 1, fp) == 1) {
        if (b.id == id) {
            found = 1;

            printf("\nCurrent Book Details:\n");
            printf("Title: %s\n", b.title);
            printf("Author: %s\n", b.author);
            printf("Category: %s\n", b.category);
            printf("Year: %d\n", b.year);

            printf("\nEnter NEW Title: ");
            getchar();
            fgets(b.title, 50, stdin);
            b.title[strcspn(b.title, "\n")] = 0;

            printf("Enter Author name: ");
            fgets(b.author, 50, stdin);
            b.author[strcspn(b.author, "\n")] = 0;

            printf("Enter Category: ");
            fgets(b.category, 30, stdin);
            b.category[strcspn(b.category, "\n")] = 0;

            printf("Enter Published Year: ");
            scanf("%d", &b.year);

            printf("\nBook updated successfully!\n");
        }

        fwrite(&b, sizeof(Book), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    if (!found) {
        printf("\nBook with ID %d not found.\n", id);
        remove("temp.dat");
        return;
    }

    remove("books.dat");          // delete old file
    rename("temp.dat", "books.dat");  // replace with updated file
}

void deleteBook(){
    FILE *fp, *temp;
    Book b;
    int id, found = 0;
    
    fp = fopen("books.dat", "rb");
    if(fp == NULL) {
        printf("\nNo books found!\n");
        return;
    }
    
    temp = fopen("temp.dat", "wb");
    if(temp == NULL){
        printf("Error creating temporary file!\n");
        fclose(fp);
        return;
    }
    printf("\nEnter Book ID to delete: ");
    scanf("%d", &id);
    
    while(fread(&b, sizeof(Book), 1, fp) == 1) {
        if(b.id == id){
            found = 1;
            printf("\nBook with ID %d has been deleted successfully.\n", id);
            continue; //this skips the one intended to delete. so temp write all books except the skipped/deleted one.
        }
        fwrite(&b, sizeof(Book), 1, temp);
    }
    
    fclose(fp);
    fclose(temp);
    
    if(!found){
        printf("\nBook with ID %d not found.\n", id);
        remove("temp.dat");
        return;
    }
    
    remove("books.dat"); //delete old file 
    rename("temp.dat", "books.dat"); 
}
 
void borrowBook(){
    FILE *fp, *temp;
    Book b;
    int id, found = 0;
    
    fp = fopen("books.dat", "rb");
    if ( fp==NULL ) {
        printf("\nNo Books found!\n");
        return;
    }
    
    temp = fopen("temp.dat", "wb");
    if(temp == NULL){
       printf("\nError creating temporary file!\n");
       fclose(fp);
       return;
    }
    
    printf("\nEnter Book ID to borrow: ");
    scanf("%d", &id);
    
    while (fread(&b, sizeof(Book), 1, fp) ==1)
{
    if(b.id == id) {
        found = 1;
        
        if(b.isBorrowed){
            printf("\nSorry, this book is already borrowed by %s.\n", b.borrowedBy);}
            
        else {
                char name[50], phone[20];
                
                printf("Enter Your Name: ");
                getchar();
                fgets(name, 50, stdin);
                name[strcspn(name, "\n")] = 0;
                
                printf("\nEnter your Phone Number: ");
                fgets(phone, 20, stdin);
                phone[strcspn(phone, "\n")] = 0;
                
                b.isBorrowed = 1;
                strcpy(b.borrowedBy, name);
                strcpy(b.borrowerPhone, phone);
                
                printf("\nBook borrowed successfully!\n");
            }
        }
        
        fwrite(&b, sizeof(Book), 1, temp);
    }
    
    fclose(fp);
    fclose(temp);
    
    if(!found){
        printf("\nBook with ID %d is not found!\n", id);
        remove("temp.dat");
        return;
    }
    
    remove("books.dat");
    rename("temp.dat", "books.dat");
} 

void returnBook(){
    FILE *fp, *temp;
    Book b;
    int id, found = 0;
    
    fp = fopen("books.dat", "rb");
    if(fp == NULL) {
        printf("\nNo Books found!\n");
        return;
    }
    
    temp = fopen("temp.dat", "wb");
    if(temp == NULL){
        printf("\nError creating temporary file!\n");
        fclose(fp);
        return;
    }
    
    printf("\nEnter the Book ID to return: ");
    scanf("%d", &id);
    
    while(fread(&b, sizeof(Book), 1, fp) == 1) {
        if(b.id == id){
            found = 1;
            
            if(!b.isBorrowed){
                printf("\nThis book is not currently borrowed.\n");
            } else {
                b.isBorrowed = 0;
                strcpy(b.borrowedBy, "");
                strcpy(b.borrowerPhone, "");
                printf("\nThis book returned successfully!\n");
            }
        }
        fwrite(&b, sizeof(Book), 1, temp);
    }
    fclose(fp);
    fclose(temp);
    
    if(!found){
        printf("\nBook with ID %d not found.\n", id);
    }
    
    remove("books.dat");
    rename("temp.dat", "books.dat");
}
