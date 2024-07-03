#include <stdio.h>  //*This is the STANDARD LIBRARY for C.
#include <ctype.h>  // to use _getch()
#include <string.h> //*This is the library to work with strings.
#include <unistd.h> //*Include this for access function. Required for sleep() on Unix-like systems
#include <stdlib.h> //*Memory allocation, random numbers, communication 
                    // with the environment, and other basic operations.
                    
#ifdef _WIN32
#include <windows.h> // Required for Sleep() on Windows 
#endif

FILE *fptr; // Declare the file pointer globally

// Function declaration

void Save();
void Load();
void ClearScreen();
void ShowPasswords();
void AskForPassword();
void EditPassword();
void WaitKey();
void WaitSleep();
void ChangeMasterKey();

void MenuSettings();

//Constants

const int MAX_STORAGE = 15;

// Global Variables
char MasterKey[30]; 		// STRING Declaration
char input;
char UserInput0[50];
char UserInput1[50];
char UserInput2[50];
int Options;
int SlotToEdit;
int i;

char WebService[15][40];
char ID[15][40]; //char ID[MAX_STORAGE][MAX_ID_LENGTH];
char passwords[15][40];	//char passwords[MAX_STORAGE][MAX_PASSWORD_LENGTH];

int main () {

//======================================================================
// CREATES DATA FILE (IF IT DOESN'T EXIST)

const char * filename = "data.dat";

// Check if the file exists

if (access(filename, F_OK) != -1) {
	
	//fptr = fopen(filename, "r+"); 
    Load();
    
} else {
        
		// File doesn't exist, create a new file
        
        fptr = fopen(filename, "w+");
        printf("File does not exist. New file created. \n");
        fclose(fptr);
    
	}

// Check if the file was opened successfully
if (fptr == NULL) 

{
	
	printf("Error opening the file.\n");
	return 1; // indicate an error to the operating system

}

// Close the file
//fclose(fptr);

//======================================================================

MasterKeyINI:

if (strcmp(MasterKey, "") == 0)
	
{
	printf("Add a Master password: \n");
	scanf("%39s", &MasterKey);
	
} 

else

{
	
	AskForPassword();
	
}

Load();  // Loads data from the file
ClearScreen();

ProgramStart:

printf("\n");
printf("########################## \n");
printf("| ChaveLocker 0.3 | 2024 | \n");
printf("########################## \n");
printf("\n");

WaitSleep();

printf("1- Show Passwords \n");
WaitSleep();
printf("2- Add Password to Remember \n");
WaitSleep();
printf("3- Advice \n");
WaitSleep();
printf("4- Delete an speciffic password \n");
WaitSleep();
printf("14- Setting \n");
WaitSleep();
printf("5- Delete all passwords \n");
WaitSleep();
printf ("6- Edit Password \n");
WaitSleep();
printf("7- Exit \n");
printf("\n");
WaitSleep();


scanf("%d", &Options);

/* AND and OR - Logical operators: 

Using && (AND) operator --> if (age >= 18 && height >= 160) {...
Using || (OR) operator -->  if (age < 16 || height < 140) {... */

switch (Options) {
	
	case 1:
		
		AskForPassword();
		ShowPasswords();
		goto ProgramStart;
		
	case 2:
	
		printf("\n");
		printf("Service or Website:\n");
		scanf("%49s", UserInput0);
		
		printf("\n");
		printf("The service or website to be stored is %s.", UserInput0);
		
		printf("\n");
		printf("ID to Remember:\n");
		scanf("%49s", UserInput1);
		
		printf("\n");
		printf("The ID to be stored is %s. \n", UserInput1);
	
		printf("\n");
		printf("Password to Remember:\n");
		scanf("%49s", UserInput2);
		
		printf("\n");
		printf("The password to be stored is %s. \n", UserInput2);
		printf("\n");
		
		for (i = 0; i < MAX_STORAGE; i++) {
			
			if (strcmp(WebService[i], "") == 0 && strcmp(ID[i], "") == 0 && strcmp(passwords[i], "") == 0) {
			
				strcpy(WebService[i], UserInput0);
				strcpy(ID[i], UserInput1);
				strcpy(passwords[i], UserInput2);
				break;
			
			}
		
		}
		
		Save();		
		goto ProgramStart;
		
	case 3:
		
		ClearScreen();
		
		printf("ABOUT ChaveLocker 0.2 | 2024\n");
		printf("============================\n");  
		printf("Created by Fernando G.Ramirez \n\n");
		
		WaitSleep();
		
		printf("This app intends to help you with your passwords, so you don't forget them. Password \n"); 
		printf("managers are software programs that securely store and manage user passwords, login \n");
		printf("information, and other sensitive data.\n\n");
		
		WaitSleep();
		
		printf("SUGGESTIONS TO ENHANCE SECURITY \n");
		printf("=============================== \n");
		printf("\n");
		
		WaitSleep();
		
		printf("Enhance your security by avoiding the use of exact website or service names. Instead, \n"); 
		printf("create suggestive names that only you can understand.\n\n");
				
		WaitSleep();
		
		printf("Apply the same principle to your IDs and passwords to prevent storing real information.\n"); 
		printf("For example: WebService? DIGITAL BANK >> ID? My G***** Email >> Password? The difficult\n");
		printf("one... \n\n");
				
		WaitSleep();
		
		printf("Consider adding asterisks (****) in place of certain characters or numbers when inputting\n"); 
		printf("passwords, emails, or IDs. This practice adds an extra layer of security, making it more\n"); 
		printf("challenging for others to decipher your personal data. \n\n");
		
		WaitSleep();
		
		printf("Remember to keep track of the coded names or patterns you use for security. Forgetting them may\n"); 
		printf("result in difficulty accessing your stored information.\n\n");
		
		WaitSleep();
				
		printf("Ensure the strength of your security by creating unique and robust master passwords. This is \n"); 
		printf("a crucial aspect of safeguarding sensitive data.\n\n");
		
		WaitSleep();
		
		printf("Enhance the security of this program by keeping it hidden in a randomly chosen location on \n");
		printf("your hard drive. Place it in a folder with a unique and unrelated name that only you know. \n");
		printf("Additionally, rename the program to something obscure and unrelated to passwords, such as a \n");
		printf("random sequence. Avoid using terms like 'PasswordManager' or 'Key' to make it less conspicuous. \n");
		printf("Choose a name that is memorable to you but doesn't reveal the program's purpose. \n");

		goto ProgramStart;
	
	case 14:
	
		MenuSettings();
		goto ProgramStart;
	
	case 4:
		
		ClearScreen();
		AskForPassword();
		ShowPasswords();
		
		printf("What slot would you like to delete? \n");
		scanf("%d", &Options);
		
		printf("\n");
		printf ("Are you sure you want to delete the information stored in that slot? \n");
		printf("Write YES to confirm the action: ");
		scanf("%4s", &UserInput0);
				
		if (strcasecmp(UserInput0, "YES") == 0) {
		
			strcpy(WebService[Options], "");
			strcpy(ID[Options], "");
			strcpy(passwords[Options], "");

			printf("\n");
			printf("The speciffic ID and Password has been deleted. \n");
			printf("\n");
		
		} else {
			
			printf("\n"); 
			printf("The action ha been canceled... \n");
			
			}
		
		goto ProgramStart;
				
	case 5: // DELETE ALL IDs & PASSWORDS.
	
		AskForPassword();
	
		printf("\n");
		printf ("Are you sure you want to delete all the information stored? \n");
		printf("Write YES to confirm the action: ");
		scanf("%4s", &UserInput0);
				
		if (strcasecmp(UserInput0, "YES") == 0) {
		
			for (i = 0; i < MAX_STORAGE; i++) {
			
				strcpy(WebService[i], "");
				strcpy(ID[i], "");
				strcpy(passwords[i], "");
					
			}
		
			printf("\n");
			printf("All IDs and Passwords have been deleted. \n");
			printf("\n");
		
		} else {
			
			printf("\n"); 
			printf("The action ha been canceled... \n");
			
			}
		
		goto ProgramStart;
	
	
	case 6:
	
		EditPassword();
		goto ProgramStart;
		
	case 7:
	
		Save();
		return 0;

}

return 0;

}

// SAVE Function

void Save() {
	
	printf("Saving...");
	
	// Save the variable to a file
	fptr = fopen("data.dat", "w+");
	
	if (fptr == NULL) {
		
		printf("Error opening file!\n");
		return;
	}

    // Write variables to the file
    
    fprintf(fptr, "%29s\n", MasterKey);
    
    for (i = 0; i < MAX_STORAGE; i++) { // FOR..I loop to save passwords and IDs.
        
        fprintf(fptr, "%49s", WebService[i]);
        fprintf(fptr, "%49s", ID[i]);
        fprintf(fptr, "%49s\n", passwords[i]);
    }


	fclose(fptr);
	
	ClearScreen();
		
		
}

// LOAD Function
void Load() {
	
	printf("Loading...");
	
	 fptr = fopen("data.dat", "r");
	
    // Load the variable from the file
	
	if (fptr == NULL) {
		
		printf("Error opening file!\n");
    	return;

	}

	// Read variables from the file
		
	fscanf(fptr, "%29s\n", &MasterKey); // adjust buffer size based on your needs

	for (i = 0; i < MAX_STORAGE; i++) { // Corrected loop condition
			
		fscanf(fptr, "%49s", &WebService[i]);	
		fscanf(fptr, "%49s", &ID[i]);
		fscanf(fptr, "%49s\n", &passwords[i]);
	
	}

	fclose(fptr);
	
	ClearScreen();
	    
}

//CLS Function
void ClearScreen() {

#ifdef _WIN32
    
    // Windows
    system("cls");

#else
    
    // Unix-like systems
    system("clear");

#endif

}

void ShowPasswords() {
	
		printf("\n");
		
		for (i = 0; i < MAX_STORAGE; i++) {
			
			if (strcmp(ID[i], "") != 0 && strcmp(passwords[i], "") != 0) {
						
				printf("[%d] %s | %s | %s \n", i, WebService[i], ID[i], passwords[i]);
				WaitSleep();
				
			}
		
		}
		
		printf("\n");

}

void AskForPassword() {
	
	ClearScreen();
	
	for (i = 0; i < 3; i++) {
	
		printf("\n");
		printf("What is the MASTER PASSWORD: \n");
		scanf("%49s", &UserInput0);
		printf("\n");
					
		int comparison = strcmp(MasterKey, UserInput0); //Compares the value of 2 different string variables.
		
		if (comparison == 0)
		
		{	
			ClearScreen();
			printf(">> CORRECT PASSWORD. ACCESS CONFIRMED <<\n");
			printf("\n");
			return;
		
		}
		
		else {
			
			if (i == 2) {
				
				printf(">> WRONG PASSWORD. ACCESS DENIED. PROGRAM ENDED <<\n");
				printf("\n");
				exit(0); //Exits the program.
			}
				
			printf("Wrong password. Try again...");
			
		}	
	
	}
	
}

void EditPassword() {
	
	ClearScreen();
	AskForPassword();
	ShowPasswords();
	
	printf("What slot would you like to edit?");
	scanf("%d", &SlotToEdit);
	printf("\n");
	
	
	ShowEditScreen:
	ClearScreen();
	
	printf("[%d] %s | %s | %s \n", SlotToEdit, WebService[SlotToEdit], ID[SlotToEdit], passwords[SlotToEdit]);
	
	EditAskAgain:
	
	printf("\n");
	printf("[1] Edit Web and Service [2] Edit ID [3] Edit Password [7] EXIT \n");
	scanf("%d", &Options);
	
	switch(Options) {
	
		case 1:
		
			printf("\n");
			printf("Service or Website:\n");
			scanf("%49s", UserInput0);
			
			strcpy(WebService[SlotToEdit], UserInput0);
			break;
			
		case 2:
		
			printf("\n");
			printf("ID to Remember:\n");
			scanf("%49s", UserInput1);
			
			strcpy(ID[SlotToEdit], UserInput1);
			break;
			
		case 3:
				
			printf("\n");
			printf("Password to Remember:\n");
			scanf("%49s", UserInput2);
				
			strcpy(passwords[SlotToEdit], UserInput2);
			break;
			
		case 7:
			
			Save();
			return;

		default:
		
			printf("\n");
			printf("Choose one of the options above: 1, 2 or 3. \n");
			goto EditAskAgain;
	}					
	
	goto ShowEditScreen;
		
}
	
void WaitKey() {
	
	// Loop until a key is pressed
			
	do {
			
		input = getchar();
		
	} while (input == '\n'); // Ignore newline characters

	printf("\n Key '%c' pressed. Program continues...\n", input);

	return;

}

void WaitSleep() {
	
    // Pause the program for 1 second
    
    #ifdef _WIN32
    Sleep(200); // Sleep for 1000 milliseconds (1 second) on Windows
    
    #else
    sleep(0.2); // Sleep for 1 second on Unix-like systems
    
    #endif

    return;

}

void ChangeMasterKey() {
	
	ChangeMasterKey:
	
	printf("Input NEW MASTER KEY: ");
	scanf("%49s", &UserInput0);
	printf("Repeat NEW MASTER KEY: ");
	scanf("%49s", &UserInput1);
		
	int comparison = strcmp(UserInput0, UserInput1); //Compares the value of 2 different string variables.
		
		if (comparison == 0) {	
			
			strcpy(MasterKey, UserInput0);
			printf(">> SUCCESS! MASTER KEY CHANGED! <<\n");
			printf("New Master Key is: %s\n\n", MasterKey);
			Save();
			WaitSleep();
			return;
		
		}
		
		else {
			
			
			ClearScreen();				
			printf(">> CHARACTERS DON'T MATCH. TRY AGAIN << \n\n");
			WaitSleep();
			goto ChangeMasterKey;
			
		}	
	
}
	

void MenuSettings() {
		
	ClearScreen();
	
	printf("\n");
	printf("########################## \n");
	printf("| ChaveLocker 0.3 | 2024 | \n");
	printf("########################## \n");
	printf("\n");

	WaitSleep();
	
	printf("1- Change Master Key \n");
	printf("7- Exit \n");
	printf("\n");

	scanf("%d", &Options);
	
	switch(Options){
		
		case 1:
		
			AskForPassword();
			ChangeMasterKey();
			return;
		
		case 7:
		
			ClearScreen();
			return;
		
	}
		
}


//======================================================================

//NOTES:

// TO DO
// =====

// Deleting PASSWORDS and IDs [NOT FINISHED] [45%] --> Delete INDIVIDUAL
// and SPECIFFIC passwords.

// ASK PASSWORD, verify password --> Sub Function - Create and implement 
// its use along the whole program.

// DELETE an speciffic WebService, ID, and Password.
// EDIT an speciffic WebService, ID, and Password.

// FINISHED
// ========

// Version 0.3

// - 'Change MasterKey' --> Ask for MasterKey twice and verify if both 
//   inputs match.
// - 'Change MasterKey' option [100%] 
// - MENU section --> SETTINGS [OK]

// Version 0.2

// - Delete ALL passwords - FINISHED [75%]
// - Verify Password when accessing important areas. [100%]
// EDIT PASSWORDS [100%]


//======================================================================
