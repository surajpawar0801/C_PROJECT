#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_BOOKS 100

typedef struct Book{

    int bookId;
    char bookName[100];
    char authorName[100];
    char category[50];
    float price;
    float rating;
} Book;

Book books[MAX_BOOKS] = {
  {100,"Suraj Autobiography","Suraj Pawar","Autobiography",599,5.0},
  {101, "Java Programming", "James Gosling", "Programming", 650, 4.8},
  {102, "Effective Java", "Joshua Bloch", "Programming", 850, 4.9},
  {103, "Wings of Fire", "APJ Abdul Kalam", "Biography", 350, 4.7},
  {104, "The Alchemist", "Paulo Coelho", "Fiction", 299, 4.5},
  {105, "Clean Code", "Robert C Martin", "Programming", 750, 4.6},
  {106, "C Programming", "Dennis Ritchie", "Programming", 500, 4.6},
  {107, "The C Programming Language", "Brian Kernighan", "Programming", 600, 4.8},
  {108, "Rich Dad Poor Dad", "Robert Kiyosaki", "Finance", 400, 4.5},
  {109, "Atomic Habits", "James Clear", "Self Help", 550, 4.7},
  {110, "Think and Grow Rich", "Napoleon Hill", "Self Help", 450, 4.4},
  {111, "Harry Potter", "J.K. Rowling", "Fantasy", 700, 4.9},
  {112, "The Psychology of Money", "Morgan Housel", "Finance", 399, 4.8},
  {113, "Ikigai", "Hector Garcia", "Self Help", 350, 4.3},
  {114, "1984", "George Orwell", "Fiction", 299, 4.6},
  {115, "The Hobbit", "J.R.R. Tolkien", "Fantasy", 500, 4.7},
  {116, "Introduction to Algorithms", "Thomas H. Cormen", "Programming", 1200, 4.9},
  {117, "Deep Work", "Cal Newport", "Productivity", 450, 4.6},
  {118, "The Power of Habit", "Charles Duhigg", "Self Help", 480, 4.5},
  {119, "Sapiens", "Yuval Noah Harari", "History", 650, 4.7},
  {120, "The 5 AM Club", "Robin Sharma", "Self Help", 399, 4.4}
};

int bookCount = 5;

void displayMenu(void);
void readLine(char [], int);
int readInt(char []);
float readFloat(char []);
int findBookById(int);
void displayHeader(void);
void displayBook(Book);
void displayAllBooks(void);
void addBook(void);
void removeBook(void);
void searchBookById(void);
void searchBookByName(void);
void showBooksByAuthor(void);
void showBooksByCategory(void);
void updateBook(void);
void sortBooks(void);
void showTopThree(void);
int containsIgnoreCase(char [], char []);
void sortCopy(Book [], int, int, int);

int main(void){

    int choice;
    do {
    
        displayMenu();
        choice = readInt("Enter your choice: ");
        
        switch (choice){
		
            case 1:
                addBook();
                break;

            case 2:
                removeBook();
                break;

            case 3:
                searchBookById();
                break;

            case 4:
                searchBookByName();
                break;

            case 5:
                showBooksByAuthor();
                break;

            case 6:
                showBooksByCategory();
                break;

            case 7:
                updateBook();
                break;

            case 8:
                sortBooks();
                break;

            case 9:
                showTopThree();
                break;

            case 10:
                displayAllBooks();
                break;

            case 0:
                printf("\nExiting Book Management System.\n");
                break;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    } while (choice != 0);

    return 0;
}


void displayMenu(void){

    printf("\n========= BOOK MANAGEMENT SYSTEM =========\n");
    printf("1.  Add Book\n");
    printf("2.  Remove Book\n");
    printf("3.  Search Book by ID\n");
    printf("4.  Search Book by Name\n");
    printf("5.  Show Books by Author\n");
    printf("6.  Show Books by Category\n");
    printf("7.  Update Book Price and Rating\n");
    printf("8.  Display Sorted Books\n");
    printf("9.  Display Top 3 Books\n");
    printf("10. Display All Books\n");
    printf("11. Exit\n");
    printf("=========================================\n");
}


void readLine(char str[], int size){

    if (fgets(str, size, stdin) != NULL){
    	
        str[strcspn(str, "\n")] = '\0';
    }
    else
        str[0] = '\0';
    
}


int readInt(char message[]){

    char input[100];
    int value;
    char extra;

    while (1){
    
        printf("%s", message);
        readLine(input, sizeof(input));

        if (sscanf(input, " %d %c", &value, &extra) == 1){
		
            return value;
        }

        printf("Invalid integer! Please try again.\n");
    }
}


float readFloat(char message[]){

    char input[100];
    float value;
    char extra;

    while (1){
    
        printf("%s", message);
        readLine(input, sizeof(input));

        if (sscanf(input, " %f %c", &value, &extra) == 1){
        
            return value;
        }

        printf("Invalid number! Please try again.\n");
    }
}


int containsIgnoreCase(char text[], char search[]){

    int i, j;

    if (search[0] == '\0')
        return 1;

    for (i = 0; text[i] != '\0'; i++){
	
        for (j = 0; search[j] != '\0'; j++){
		
            if (text[i + j] == '\0')
                break;

            if (tolower((unsigned char)text[i + j]) !=
                tolower((unsigned char)search[j])){
				
                break;
            }
        }

        if (search[j] == '\0')
            return 1;
    }

    return 0;
}


int findBookById(int id){

    int i;

    for (i = 0; i < bookCount; i++){
	
        if (books[i].bookId == id){
		
            return i;
        }
    }

    return -1;
}


void displayHeader(void){

    printf("\n%-8s %-25s %-22s %-15s %-10s %-8s\n",
           "Book ID", "Book Name", "Author Name",
           "Category", "Price", "Rating");

    printf("-----------------------------------------------------------\n");
}


void displayBook(Book b){

    printf("%-8d %-25s %-22s %-15s %-10.2f %-8.1f\n",
           b.bookId, b.bookName, b.authorName,
           b.category, b.price, b.rating);
}


void displayAllBooks(void){
	
    int i;

    if (bookCount == 0){
	
        printf("\nNo books available.\n");
        return;
    }

    displayHeader();

    for (i = 0; i < bookCount; i++){
	
        displayBook(books[i]);
    }

    printf("\nTotal books: %d\n", bookCount);
}


void addBook(void){
	
    Book b;

    if (bookCount >= MAX_BOOKS){
	
        printf("\nBook storage is full!\n");
        return;
    }

    printf("\nEnter Book ID: ");
    b.bookId = readInt("");

    if (b.bookId <= 0){
	
        printf("Book ID must be positive.\n");
        return;
    }

    if (findBookById(b.bookId) != -1){
	
        printf("Book ID already exists!\n");
        return;
    }

    printf("Enter Book Name: ");
    readLine(b.bookName, sizeof(b.bookName));

    printf("Enter Author Name: ");
    readLine(b.authorName, sizeof(b.authorName));

    printf("Enter Category: ");
    readLine(b.category, sizeof(b.category));

    b.price = readFloat("Enter Price: ");

    if (b.price < 0){
	
        printf("Price cannot be negative.\n");
        return;
    }

    b.rating = readFloat("Enter Rating (0 to 5): ");

    if (b.rating < 0 || b.rating > 5){
	
        printf("Rating must be between 0 and 5.\n");
        return;
    }

    if (b.bookName[0] == '\0' || b.authorName[0] == '\0' || b.category[0] == '\0'){
	
        printf("Book name, author and category cannot be empty.\n");
        return;
    }

    books[bookCount] = b;
    bookCount++;

    printf("\nBook added successfully!\n");
}


void removeBook(void){

    int id, index, i;
    id = readInt("Enter Book ID to remove: ");
    index = findBookById(id);
    if (index == -1){
	
        printf("Book not found!\n");
        return;
    }

    printf("\nRemoved book: %s\n", books[index].bookName);
    /* Shift remaining books to fill the gap */
    for (i = index; i < bookCount - 1; i++){
	
        books[i] = books[i + 1];
    }

    bookCount--;

    printf("Book removed successfully!\n");
}


void searchBookById(void){

    int id, index;
    id = readInt("Enter Book ID: ");
    index = findBookById(id);
    if (index == -1){
	
        printf("Book not found!\n");
        return;
    }

    displayHeader();
    displayBook(books[index]);
}

void searchBookByName(void){

    char name[100];
    int i, found = 0;

    printf("Enter Book Name or part of its name: ");
    readLine(name, sizeof(name));

    displayHeader();

    for (i = 0; i < bookCount; i++){
	
        if (containsIgnoreCase(books[i].bookName, name)){
		
            displayBook(books[i]);
            found = 1;
        }
    }

    if (!found){
	
        printf("No matching books found.\n");
    }
}


void showBooksByAuthor(void){

    char author[100];
    int i, found = 0;

    printf("Enter Author Name: ");
    readLine(author, sizeof(author));

    displayHeader();

    for (i = 0; i < bookCount; i++){
	
        if (containsIgnoreCase(books[i].authorName, author)){
		
            displayBook(books[i]);
            found = 1;
        }
    }

    if (!found){
	
        printf("No books found for this author.\n");
    }
}


void showBooksByCategory(void){

    char category[50];
    int i, found = 0;

    printf("Enter Category: ");
    readLine(category, sizeof(category));

    displayHeader();

    for (i = 0; i < bookCount; i++){
	
        if (containsIgnoreCase(books[i].category, category)){
        
            displayBook(books[i]);
            found = 1;
        }
    }

    if (!found){
	
        printf("No books found in this category.\n");
    }
}


void updateBook(void){

    int id, index;
    float price, rating;

    id = readInt("Enter Book ID to update: ");

    index = findBookById(id);

    if (index == -1){
	
        printf("Book not found!\n");
        return;
    }

    printf("\nCurrent book details:\n");
    displayHeader();
    displayBook(books[index]);

    price = readFloat("\nEnter new Price: ");

    if (price < 0){
	
        printf("Price cannot be negative.\n");
        return;
    }

    rating = readFloat("Enter new Rating (0 to 5): ");

    if (rating < 0 || rating > 5){
	
        printf("Rating must be between 0 and 5.\n");
        return;
    }

    books[index].price = price;
    books[index].rating = rating;

    printf("\nBook updated successfully!\n");
}


void sortCopy(Book arr[], int count, int field, int descending){

    int i, j;
    Book temp;
    float a, b;

    for (i = 0; i < count - 1; i++){
	
        for (j = 0; j < count - 1 - i; j++){
		
            if (field == 1){
            
                a = arr[j].price;
                b = arr[j + 1].price;
            }
            else{
			
                a = arr[j].rating;
                b = arr[j + 1].rating;
            }

            if ((!descending && a > b) || (descending && a < b)){
				
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


void sortBooks(void){

    Book copy[MAX_BOOKS];
    int field, order, i;

    if (bookCount == 0){
	
        printf("No books available.\n");
        return;
    }

    printf("\nSort by:\n");
    printf("1. Price\n");
    printf("2. Rating\n");

    field = readInt("Enter choice: ");

    if (field != 1 && field != 2){
	
        printf("Invalid sorting field!\n");
        return;
    }

    printf("\nOrder:\n");
    printf("1. Highest to Lowest\n");
    printf("2. Lowest to Highest\n");

    order = readInt("Enter choice: ");

    if (order != 1 && order != 2){
	
        printf("Invalid sorting order!\n");
        return;
    }

    for (i = 0; i < bookCount; i++){
	
        copy[i] = books[i];
    }

    sortCopy(copy, bookCount, field, order == 1);

    printf("\nSorted by %s (%s):\n",
           field == 1 ? "Price" : "Rating",
           order == 1 ? "Descending" : "Ascending");

    displayHeader();

    for (i = 0; i < bookCount; i++){
	
        displayBook(copy[i]);
    }
}


void showTopThree(void){

    Book copy[MAX_BOOKS];
    int field, i, limit;

    if (bookCount == 0){
	
        printf("No books available.\n");
        return;
    }

    printf("\nDisplay top 3 books by:\n");
    printf("1. Price\n");
    printf("2. Rating\n");

    field = readInt("Enter choice: ");

    if (field != 1 && field != 2){
	
        printf("Invalid choice!\n");
        return;
    }

    for (i = 0; i < bookCount; i++){
	
        copy[i] = books[i];
    }

    sortCopy(copy, bookCount, field, 1);

    limit = bookCount < 3 ? bookCount : 3;

    printf("\nTop %d books by %s:\n",
           limit, field == 1 ? "Price" : "Rating");

    displayHeader();

    for (i = 0; i < limit; i++){
	
        displayBook(copy[i]);
    }
}