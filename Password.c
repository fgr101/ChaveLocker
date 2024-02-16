#include <stdio.h>	//*This is the STANDARD LIBRARY for C.
#include <string.h> //*This is the library to work with strings.
#include <unistd.h> //*Include this for access function.
#include <stdlib.h> //*Memory allocation, random numbers, communication 
                    // with the environment, and other basic operations.

FILE *fptr; // Declare the file pointer globally

// Function declaration
void Save();
void Load();
void ClearScreen();

//Constants

const int MAX_STORAGE = 15;

// Global Variables
char MasterKey[30]; 		// STRING Declaration
char UserInput0[50];
char UserInput1[50];
char UserInput2[50];
int Options;
int i;

char WebService[10][40];
char ID[10][40]; //char ID[MAX_STORAGE][MAX_ID_LENGTH];
char passwords[10][40];	//char passwords[MAX_STORAGE][MAX_PASSWORD_LENGTH];

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

// DELETE THE NEXT LATER:
// Initialization using strcpy from string.h library

strcpy(MasterKey, "1234");

if (strcmp(MasterKey, "") == 0)
	
{
	printf("Add a Master password: \n");
	scanf("%39s", &MasterKey);
	
} 

else

{
	printf("What is the MASTER PASSWORD: \n");
	scanf("%49s", &UserInput0);
	
	int comparison = strcmp(MasterKey, UserInput0); //Compares the value of 2 different string variables.
	
	if (comparison == 0)
	
	{	
		printf("THE PASSWORD IS OK! \n");
		goto ProgramStart;
	
	}
	
	else 
	
	{
		printf("WRONG PASSWORD.");
		return 0;
	}
	
}

Load();  // Loads data from the file

ProgramStart:

printf("\n");
printf("1- Show all passwords \n");
printf("2- Add password to remember \n");
printf("3- Advice \n");
printf("4- Exit \n");
printf("\n");

scanf("%d", &Options);

/* AND and OR - Logical operators: 

Using && (AND) operator --> if (age >= 18 && height >= 160) {...
Using || (OR) operator -->  if (age < 16 || height < 140) {... */

switch (Options)

{
	case 1:
		
		printf("\n");
		
		for (i = 0; i < MAX_STORAGE; i++) {
			
			if (strcmp(ID[i], "") != 0 && strcmp(passwords[i], "") != 0) {
						
				printf("%s | ", WebService[i]);
				printf("%s | ", ID[i]);
				printf("%s \n", passwords[i]);
			
			}
		
		}
		
		printf("\n");
		
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
			
			if (strcmp(ID[i], "") == 0 && strcmp(passwords[i], "") == 0) {
			
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
		
		printf("ABOUT ChaveLocker 0.1 | 2024\n");
		printf("============================\n");  
		printf("Created by Fernando G.Ramirez \n");
		printf("\n");
		printf("This app intends to help you with your passwords, so you don't forget them. Password \n"); 
		printf("managers are software programs that securely store and manage user passwords, login \n");
		printf("information, and other sensitive data.\n");
		
		
		printf("\n");
		printf("SUGGESTIONS TO ENHANCE SECURITY \n");
		printf("=============================== \n");
		printf("\n");
		
		printf("Enhance your security by avoiding the use of exact website or service names. Instead, \n"); 
		printf("create suggestive names that only you can understand.\n");
		printf("\n");
		printf("Apply the same principle to your IDs and passwords to prevent storing real information.\n"); 
		printf("For example: WebService? DIGITAL BANK >> ID? My G***** Email >> Password? The difficult one...\n");
		printf("\n");
		printf("Consider adding asterisks (****) in place of certain characters or numbers when inputting\n"); 
		printf("passwords, emails, or IDs. This practice adds an extra layer of security, making it more\n"); 
		printf("challenging for others to decipher your personal data.\n");
		printf("\n");
		printf("Remember to keep track of the coded names or patterns you use for security. Forgetting them may\n"); 
		printf("result in difficulty accessing your stored information.\n");
		printf("\n");
		printf("Ensure the strength of your security by creating unique and robust master passwords. This is a \n"); 
		printf("crucial aspect of safeguarding sensitive data.\n");
		printf("\n");
		
		goto ProgramStart;
		
	case 4:
	
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
    
    fprintf(fptr, "%29s", MasterKey);
    
    for (i = 0; i < MAX_STORAGE; i++) { // FOR..I loop to save passwords and IDs.
        
        fprintf(fptr, "%49s", WebService[i]);
        fprintf(fptr, "%49s", ID[i]);
        fprintf(fptr, "%49s", passwords[i]);
    }


	fclose(fptr);
		
		
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
		
	fscanf(fptr, "%29s", &MasterKey); // adjust buffer size based on your needs

	for (i = 0; i < MAX_STORAGE; i++) { // Corrected loop condition
			
		fscanf(fptr, "%49s", &WebService[i]);	
		fscanf(fptr, "%49s", &ID[i]);
		fscanf(fptr, "%49s", &passwords[i]);
	
	}

	fclose(fptr);
	    
}

void ClearScreen() {

#ifdef _WIN32
    
    // Windows
    system("cls");

#else
    
    // Unix-like systems
    system("clear");

#endif

}
