#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_PLAYERS 100

typedef struct Playes{
	
    int jerseyNo;
    char name[100];
    int runs;
    int wickets;
    int matches;
} Player;

Player players[MAX_PLAYERS] =
{
    {18, "Virat Kohli", 8500, 4, 120},
    {45, "Rohit Sharma", 7500, 8, 110},
    {7, "MS Dhoni", 6000, 1, 100},
    {33, "Hardik Pandya", 2500, 70, 80},
    {93, "Jasprit Bumrah", 500, 150, 75}
};

int playerCount = 5;

void displayMenu(void);
void readLine(char [], int);
int readInt(char []);
int containsIgnoreCase(char [], char []);

int findPlayerByJersey(int);

void displayHeader(void);
void displayPlayer(Player);
void displayAllPlayers(void);

void addPlayer(void);
void removePlayer(void);
void searchPlayerByJersey(void);
void searchPlayerByName(void);
void updatePlayer(void);

void sortCopy(Player [], int, int, int);
void sortPlayers(void);
void showTopThree(void);


int main(void){


    int choice;

    do{
    
        displayMenu();

        choice = readInt("Enter your choice: ");

        switch (choice){
        
            case 1:
                addPlayer();
                break;

            case 2:
                removePlayer();
                break;

            case 3:
                searchPlayerByJersey();
                break;

            case 4:
                searchPlayerByName();
                break;

            case 5:
                updatePlayer();
                break;

            case 6:
                sortPlayers();
                break;

            case 7:
                showTopThree();
                break;

            case 8:
                displayAllPlayers();
                break;

            case 0:
                printf("\nExiting Player Management System.\n");
                break;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    } while (choice != 0);

    return 0;
}

void displayMenu(void){

    printf("\n========= PLAYER MANAGEMENT SYSTEM =========\n");

    printf("1. Add Player\n");
    printf("2. Remove Player\n");
    printf("3. Search Player by Jersey Number\n");
    printf("4. Search Player by Name\n");
    printf("5. Update Player\n");
    printf("6. Display Sorted Players\n");
    printf("7. Display Top 3 Players\n");
    printf("8. Display All Players\n");
    printf("9. Exit\n");

    printf("============================================\n");
}

void readLine(char str[], int size){

    if (fgets(str, size, stdin) != NULL)
        str[strcspn(str, "\n")] = '\0';
    
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

int findPlayerByJersey(int jersey){

    int i;

    for (i = 0; i < playerCount; i++){
    
        if (players[i].jerseyNo == jersey){
        
            return i;
        }
    }

    return -1;
}

void displayHeader(void){

    printf("\n%-10s %-22s %-10s %-10s %-10s\n",
           "Jersey No", "Player Name",
           "Runs", "Wickets", "Matches");

    printf("---------------------------------------------------------------\n");
}

void displayPlayer(Player p){

    printf("%-10d %-22s %-10d %-10d %-10d\n",
           p.jerseyNo, p.name,
           p.runs, p.wickets, p.matches);
}

void displayAllPlayers(void){

    int i;

    if (playerCount == 0){
    
        printf("\nNo players available.\n");
        return;
    }

    displayHeader();

    for (i = 0; i < playerCount; i++){
	
        displayPlayer(players[i]);
    }

    printf("\nTotal Players: %d\n", playerCount);
}

void addPlayer(void){

    Player p;

    if (playerCount >= MAX_PLAYERS){
    
        printf("\nPlayer storage is full!\n");
        return;
    }

    p.jerseyNo = readInt("\nEnter Jersey Number: ");

    if (p.jerseyNo <= 0){
    
        printf("Jersey Number must be positive.\n");
        return;
    }

    if (findPlayerByJersey(p.jerseyNo) != -1){
	
        printf("Jersey Number already exists!\n");
        return;
    }

    printf("Enter Player Name: ");
    readLine(p.name, sizeof(p.name));

    if (p.name[0] == '\0'){

        printf("Player name cannot be empty.\n");
        return;
    }

    p.runs = readInt("Enter Runs: ");

    if (p.runs < 0){

        printf("Runs cannot be negative.\n");
        return;
    }

    p.wickets = readInt("Enter Wickets: ");

    if (p.wickets < 0){
	
        printf("Wickets cannot be negative.\n");
        return;
    }

    p.matches = readInt("Enter Matches Played: ");

    if (p.matches < 0){
	
        printf("Matches cannot be negative.\n");
        return;
    }

    players[playerCount] = p;
    playerCount++;

    printf("\nPlayer added successfully!\n");
}

void removePlayer(void){

    int jersey, index, i;

    jersey = readInt("Enter Jersey Number to remove: ");

    index = findPlayerByJersey(jersey);

    if (index == -1){
	
        printf("Player not found!\n");
        return;
    }

    printf("\nRemoved Player: %s\n", players[index].name);

    for (i = index; i < playerCount - 1; i++){
	
        players[i] = players[i + 1];
    }

    playerCount--;

    printf("Player removed successfully!\n");
}

void searchPlayerByJersey(void){


    int jersey, index;

    jersey = readInt("Enter Jersey Number: ");

    index = findPlayerByJersey(jersey);

    if (index == -1){
	
        printf("Player not found!\n");
        return;
    }

    displayHeader();

    displayPlayer(players[index]);
}

void searchPlayerByName(void){

    char name[100];
    int i, found = 0;

    printf("Enter Player Name: ");

    readLine(name, sizeof(name));

    displayHeader();

    for (i = 0; i < playerCount; i++){
	
        if (containsIgnoreCase(players[i].name, name)){
        
            displayPlayer(players[i]);
            
            found = 1;
        }
    }

    if (!found){

        printf("No matching players found.\n");
    }
}

void updatePlayer(void){

    int jersey, index;
    int runs, wickets, matches;

    jersey = readInt("Enter Jersey Number to update: ");

    index = findPlayerByJersey(jersey);

    if (index == -1){
	
        printf("Player not found!\n");
        return;
    }

    printf("\nCurrent Player Details:\n");

    displayHeader();

    displayPlayer(players[index]);

    runs = readInt("\nEnter New Runs: ");

    if (runs < 0){
	
        printf("Runs cannot be negative.\n");
        return;
    }

    wickets = readInt("Enter New Wickets: ");

    if (wickets < 0){
	
        printf("Wickets cannot be negative.\n");
        return;
    }

    matches = readInt("Enter New Matches: ");

    if (matches < 0){
	
        printf("Matches cannot be negative.\n");
        return;
    }

    players[index].runs = runs;
    players[index].wickets = wickets;
    players[index].matches = matches;

    printf("\nPlayer updated successfully!\n");
}

void sortCopy(Player arr[], int count, int field, int descending){


    int i, j;
    Player temp;
    int a, b;

    for (i = 0; i < count - 1; i++){
	
        for (j = 0; j < count - 1 - i; j++){
		
            if (field == 1){
            
                a = arr[j].runs;
                b = arr[j + 1].runs;
            }
            else{
            
                a = arr[j].wickets;
                b = arr[j + 1].wickets;
            }

            if ((!descending && a > b) ||
                (descending && a < b)){
				
            
                temp = arr[j];

                arr[j] = arr[j + 1];

                arr[j + 1] = temp;
            }
        }
    }
}

void sortPlayers(void){

    Player copy[MAX_PLAYERS];

    int field, order, i;

    if (playerCount == 0){
	
        printf("No players available.\n");
        return;
    }

    printf("\nSort Players By:\n");

    printf("1. Runs\n");
    printf("2. Wickets\n");

    field = readInt("Enter choice: ");

    if (field != 1 && field != 2){
	
        printf("Invalid sorting field!\n");
        return;
    }

    printf("\nSorting Order:\n");

    printf("1. Maximum to Minimum\n");
    printf("2. Minimum to Maximum\n");

    order = readInt("Enter choice: ");

    if (order != 1 && order != 2){
	
        printf("Invalid sorting order!\n");
        return;
    }

    for (i = 0; i < playerCount; i++){
	
        copy[i] = players[i];
    }

    sortCopy(copy, playerCount, field, order == 1);

    printf("\nSorted by %s (%s):\n",
           field == 1 ? "Runs" : "Wickets",
           order == 1 ? "Descending" : "Ascending");

    displayHeader();

    for (i = 0; i < playerCount; i++){
	
        displayPlayer(copy[i]);
    }
}

void showTopThree(void){

    Player copy[MAX_PLAYERS];

    int field, i, limit;

    if (playerCount == 0){
    
        printf("No players available.\n");
        return;
    }

    printf("\nDisplay Top 3 Players By:\n");

    printf("1. Runs\n");
    printf("2. Wickets\n");

    field = readInt("Enter choice: ");

    if (field != 1 && field != 2){
    
        printf("Invalid choice!\n");
        return;
    }

    for (i = 0; i < playerCount; i++){
    
        copy[i] = players[i];
    }

    sortCopy(copy, playerCount, field, 1);

    limit = playerCount < 3 ? playerCount : 3;

    printf("\nTop %d Players by %s:\n",
           limit, field == 1 ? "Runs" : "Wickets");

    displayHeader();

    for (i = 0; i < limit; i++){
	
        displayPlayer(copy[i]);
    }
}
