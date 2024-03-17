/***********************************************
Name:	Max V.
Date:	24-Jan-2023
Desc:	An ongoing text game project.

21-Feb-2023:	Phase 2-2 of the project.
				Added headers to each function.
				Added misc comments.
				Started changelog.

06-Mar-2023:	Phase 2-3 of the project.
				Added WipeFile function.
				Added AppendToFile function.
				Integrated log file.
				Updated function headers as
				needed.

13-Mar-2023:	Phase 2-4 of the project.
				Added string.h.
				Added MAX_LENGTH
				Created USER struct.
				Added stdlib.h.
				Created Login() function.
				Created SaveUserToFile() function.
				Created LoadUserFromFile() function.
				Created OverwriteUser() function.
				Changed rooms and interactables
				to incorporate USER.
				Removed room variable (replaced
				with USER.roomID)
				Replaced "stay in room" option
				with "save and quit" in all rooms.
				(hopefully) fixed GetFileName(),
				finally.

16-Mar-2023:	Phase 3-1 of the project.
				Added BATHROOM_KEY item.
				Changed KitchenSink() to give
				bathroom key instead of master
				bedroom key.
				Added Windows.h.
				Added Sleep() throughout program.
				Created SinkPuzzle(), and attached
				it to BathroomSink().
				Added puzzle hints to various items.
				Created MasterPuzzle().
				Added MATCHES item.
				Changed LivingTable() to give
				matches item.
				Updated Outside() to actually have
				proper ending text.
				Messed around with Sleep() instance
				timings.
				Fixed a bug with HasUsedItem() where
				it was counting based on MAX_ITEMS
				instead of MAX_USED

27-Mar-2023:	Phase 3-2 of the project.
				Fixed GetItemName() implementation!
************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>

//******************CONSTANTS******************
//--- OTHER ---
#define MAX_LENGTH		50
#define SLEEP_TIME		2500
#define SHORT_SLEEP		1000
#define SINK_PUZZLE		5617

//--- ROOMS ---
#define GUEST_BEDROOM	0
#define UPPER_HALLWAY	1
#define MASTER_BEDROOM	2
#define LOWER_HALLWAY	3
#define KITCHEN			4
#define BATHROOM		5
#define LIVING_ROOM		6
#define OUTSIDE			7

//--- INVENTORY ---
#define MAX_ITEMS		5	//inventory slots
#define MAX_USED		10	//should be >= no. of items in-game
//--- ITEM IDS ---
#define EMPTY			0
#define GUEST_KEY		1
#define BATHROOM_KEY	2
#define MASTER_KEY		3
#define TWEEZERS		4
#define GLASSES			5
#define MATCHES			6
#define OUTSIDE_KEY		7

//--- BOOL ---
#define TRUE			1
#define FALSE			0
//*********************************************

//*****************STRUCTURES******************
typedef struct inventory {
	int items[MAX_ITEMS];
	int used[MAX_USED];
}INVENTORY;

typedef struct user {
	char username[MAX_LENGTH];
	char password[MAX_LENGTH];
	int roomID;
	INVENTORY inventory;
}USER;

//**********************************************

//*************FUNCTION PROTOTYPES**************
//--- INPUT ---
int ReadInput(int input);
int GetInput(int optionNum, char* filename);
//--------------------

//--- FILES ---
void WipeFile(char* filename);
void AppendToFile(char* filename, int line);
//-------------

//--- USER DATA ---
USER CreateUser(INVENTORY inv);
void Login(USER* user, char* dataFile);
void SaveUserToFile(USER user, char* dataFile);
void LoadUserFromFile(USER* user, char* dataFile);
void OverwriteUser(USER user, char* dataFile);
//-----------------

//--- INVENTORY ---
INVENTORY CreateInventory();
void AddItem(INVENTORY *inv, int itemID, char* file);
int RemoveItem(INVENTORY *inv, char* file);
void DisplayInventory(INVENTORY inv);
const char* GetItemName(int itemID);
int HasItem(INVENTORY inventory, int itemID);
int HasUsedItem(INVENTORY inventory, int itemID);
void UseItem(INVENTORY* inventory, int itemID);
//-----------------

//--- ROOMS ---
void GuestBedroom(USER* user, char* file, char* dataFile);
void UpperHallway(USER* user, char* file, char* dataFile);
void MasterBedroom(USER* user, char* file, char* dataFile);
void LowerHallway(USER* user, char* file, char* dataFile);
void Kitchen(USER* user, char* file, char* dataFile);
void Bathroom(USER* user, char* file, char* dataFile);
void LivingRoom(USER* user, char* file, char* dataFile);
void Outside(USER* user, char* file, char* dataFile);
//--------------

//--- INTERACTABLES ---
void GuestBed(char* file);
void GuestTable(char* file);
void GuestNote();
void GuestDesk(char* file);
void GuestBook();
void GuestJar(USER* user, char* file, char* dataFile);

void Staircase();

void MasterBed(char* file);
void MasterTable(USER* user, char* file, char* dataFile);
int MasterPuzzle(INVENTORY* inv, char* file);
void Glasses(USER* user, char* file, char* dataFile);
void Clock();
void MasterJar();

void PottedPlant();
void TrashCan(char* file);
void ShoeRack();

void Cabinet(char* file);
void KitchenSink(USER* user, char* file, char* dataFile);
void Stove();
void Fridge(char* file);

void Toilet();
void BathroomSink(USER* user, char* file);
int SinkPuzzle(char* file);
void Bathtub();
void Mirror();

void Couch();
void LivingTable(USER* user, char* file);
void LivingBook();
void Loveseat(char* file);
void Fireplace(USER* user, char* file, char* dataFile);
void Caretaker(char* file);
//---------------------

int main(void) {
	char* filename = "dg-outside.txt";
	char* dataFile = "dg-outside.dat";

	INVENTORY inventory = CreateInventory();
	USER user = CreateUser(inventory);

	WipeFile(filename);
	Login(&user, dataFile);

	do {
		switch (user.roomID) {
		case GUEST_BEDROOM:
			printf("\n---------------\n");
			printf("GUEST BEDROOM");
			printf("\n---------------\n");
			GuestBedroom(&user, filename, dataFile);
			break;
		
		case UPPER_HALLWAY:
			printf("\n---------------\n");
			printf("UPPER HALLWAY");
			printf("\n---------------\n");
			UpperHallway(&user, filename, dataFile);
			break;
		
		case MASTER_BEDROOM:
			printf("\n---------------\n");
			printf("MASTER BEDROOM");
			printf("\n---------------\n");
			MasterBedroom(&user, filename, dataFile);
			break;
		
		case LOWER_HALLWAY:
			printf("\n---------------\n");
			printf("LOWER HALLWAY");
			printf("\n---------------\n");
			LowerHallway(&user, filename, dataFile);
			break;
		
		case KITCHEN:
			printf("\n---------------\n");
			printf("KITCHEN");
			printf("\n---------------\n");
			Kitchen(&user, filename, dataFile);
			break;
		
		case BATHROOM:
			printf("\n---------------\n");
			printf("BATHROOM");
			printf("\n---------------\n");
			Bathroom(&user, filename, dataFile);
			break;
		
		case LIVING_ROOM:
			printf("\n---------------\n");
			printf("LIVING ROOM");
			printf("\n---------------\n");
			LivingRoom(&user, filename, dataFile);
			break;
		
		case OUTSIDE:
			printf("\n---------------\n");
			printf("OUTSIDE");
			printf("\n---------------\n");
			Outside(&user, filename, dataFile);
			return 0;
		}
	} while (user.roomID <= OUTSIDE);
	
	printf("There is nothing left for you here. Goodbye.\n");
	return 0;
}

//****************FUNCTIONS*********************
//--- INPUT ---
/************************* ReadInput() ***************************
Purpose:	reads user input and returns result

Input:		input	int			user's input

Output:		input	int			user's input
******************************************************************/
int ReadInput(int input) {
	//still doesn't work for chars because
	//everything I can find about it is beyond
	//what has been covered here yet
	//unless I want to terminate the program
	//every time someone types the wrong thing

	scanf_s("%d", &input);

	return input;
}

/************************** GetInput() ***************************
Purpose:	prompts and processes user's input

Input:		optionNum	int		number of valid options
			filename	char*	name of log file

Output:		input		int		user's input
******************************************************************/
int GetInput(int optionNum, char* filename) {
	int input = 0;
	
	printf("\nPlease input your answer below:\n> ");
	input = ReadInput(input);

	if (input > optionNum || input < 1)
		printf("\nThat is not a valid option, please try again.\n");

	AppendToFile(filename, input);
	return input;
}
//---------------------

//--- FILES ---
/************************* WipeFile() ***************************
Purpose:	wipes any content already in a file

Input:		filename	char*	name of the file being wiped

Ouput:		none
*****************************************************************/
void WipeFile(char* filename) {
	FILE* fileptr = NULL;
	
	fopen_s(&fileptr, filename, "w");
	if (fileptr == NULL) {
		printf("\nERROR - invalid file name\n");
	}
	else {
		fclose(fileptr);
	}
}

/************************ AppendToFile() ************************
Purpose:	appends input line to the end of a file

Input:		filename	*char	name of the files being added to
			line		int		line being added to the file

Output:		none
*****************************************************************/
void AppendToFile(char* filename, int line) {
	FILE* fileptr = NULL;

	fopen_s(&fileptr, filename, "a");
	if (fileptr == NULL) {
		printf("\nERROR - invalid file name\n");
	}
	else {
		fprintf(fileptr, "%d\n", line);
		fclose(fileptr);
	}
}
//-------------

//--- USER DATA ---
/************************ CreateUser() ************************
Purpose:	creates user to save to the database

Input:		inv		struct		inventory data

Output:		user	struct		the populated user struct
*****************************************************************/
USER CreateUser(INVENTORY inv) {
	USER user;
	printf("Please enter a username below (cannot contain any spaces):\n");
	scanf_s("%s", user.username, MAX_LENGTH);

	printf("Please enter the password below (cannot contain any spaces):\n");
	scanf_s("%s", user.password, MAX_LENGTH);

	user.inventory = inv;
	user.roomID = GUEST_BEDROOM;

	return user;
}

/**************************** Login() ****************************
Purpose:	accesses user database, checks if input exists or not

Input:		user		struct*		storing user info
			dataFile	char*		name of data file

Output:		none
*****************************************************************/
void Login(USER* user, char* dataFile) {
	FILE* filePtr = NULL;
	USER readTo;
	int hasName = FALSE;

	fopen_s(&filePtr, dataFile, "rb");
	if (filePtr == NULL) {
		printf("Data file did not open, or does not exist\n");
		printf("Creating file...\n");
		fopen_s(&filePtr, dataFile, "wb");
		if (filePtr == NULL) {
			printf("ERROR - data file could still not be created/opened.\n");
			exit(EXIT_FAILURE);
		}
		fclose(filePtr);
		//replace recursion later if possible?
		Login(user, dataFile);
	}
	else {
		//check if file is empty
		fseek(filePtr, 0, SEEK_END);
		int size = ftell(filePtr);
		rewind(filePtr);
		if (size == 0) {
			printf("There are no entries in the data yet. Creating new user...\n");
			fclose(filePtr);
			SaveUserToFile(*user, dataFile);
		}
		//read file line by line for the input username
		else {
			while (!feof(filePtr) && hasName != TRUE) {
				fread(&readTo, sizeof(readTo), 1, filePtr);
				if (strcmp(readTo.username, user->username) == 0) {
					hasName = TRUE;
				}
			}

			if (hasName == TRUE) {
				while (strcmp(readTo.password, user->password) != 0) {
					//password input
					printf("Incorrect password. Please enter the correct password below:\n");
					scanf_s("%s", user->password, MAX_LENGTH);
				}
				printf("Correct password, loading data...\n");
				fclose(filePtr);
				LoadUserFromFile(user, dataFile);
			}
			else {
				printf("This user does not yet exist. Creating new user...\n");
				fclose(filePtr);
				SaveUserToFile(*user, dataFile);
			}
		}
	}
}

/*********************** SaveUserToFile() ***********************
Purpose:	saves user struct to the data file

Input:		user		struct		the user data to be saved
			dataFile	char*		name of the data file

Output:		none
*****************************************************************/
void SaveUserToFile(USER user, char* dataFile) {
	FILE* filePtr = NULL;

	fopen_s(&filePtr, dataFile, "ab");
	if (filePtr == NULL) {
		printf("ERROR - data file could not be opened\n");
		exit(EXIT_FAILURE);
	}
	else {
		fwrite(&user, sizeof(USER), 1, filePtr);
		fclose(filePtr);
		printf("User created!\n");
		fclose(filePtr);
	}
}

/********************** LoadUserFromFile() **********************
Purpose:	loads a user from the data file

Input:		user		struct*		struct being loaded to
			dataFile	char*		name of data file

Output:		none
*****************************************************************/
void LoadUserFromFile(USER *user, char* dataFile) {
	FILE* filePtr = NULL;
	USER readTo;

	fopen_s(&filePtr, dataFile, "rb");
	if (filePtr == NULL) {
		printf("ERROR - data file could not be opened\n");
		exit(EXIT_FAILURE);
	}
	else {
		while (!feof(filePtr) && readTo.username != user->username) {
			fread(&readTo, sizeof(readTo), 1, filePtr);
			if (strcmp(readTo.username, user->username) == 0) {
				memmove(user, &readTo, sizeof(readTo));
			}
		}
		printf("User loaded!\n");
		fclose(filePtr);
	}
}

/************************ OverwriteUser() ************************
Purpose:	overwrites user's last saved data with an updated
			version

Input:		user		struct		user data
			dataFile	char*		data file name

Output:		none
******************************************************************/
void OverwriteUser(USER user, char* dataFile) {
	FILE* filePtr = NULL;
	USER readTo;
	int flag = FALSE;

	fopen_s(&filePtr, dataFile, "rb+");
	if (filePtr == NULL) {
		printf("ERROR - data file could not be opened\n");
	}
	else {
		while (!feof(filePtr) && flag != TRUE) {
			fread(&readTo, sizeof(USER), 1, filePtr);
			if (strcmp(readTo.username, user.username) == 0) {
				fseek(filePtr, 0, SEEK_CUR);
				fwrite(&user, sizeof(USER), 1, filePtr);
				flag = TRUE;
			}
		}
		fclose(filePtr);
	}
}
//-----------------

//--- INVENTORY ---
/*********************** CreateInventory() ************************
Purpose:	creates an instance of the inventory struct

Input:		none

Output:		inv		struct		created inventory instance
******************************************************************/
INVENTORY CreateInventory() {
	INVENTORY inv;
	for (int i = 0; i < MAX_ITEMS; i++) {
		inv.items[i] = EMPTY;
	}
	for (int j = 0; j < MAX_USED; j++) {
		inv.used[j] = EMPTY;
	}
	return inv;
}

/*************************** AddItem() ***************************
Purpose:	adds an item to an instance of the inventory
				struct

Input:		inventory	struct*		user's inventory
			itemID		int			ID of item being added

Output:		none
******************************************************************/
void AddItem(INVENTORY *inventory, int itemID, char* file) {
	int added = FALSE;
	const char* itemName = GetItemName(itemID);

	for (int i = 0; i < MAX_ITEMS; i++) {
		if (added == FALSE && inventory->items[i] == EMPTY) {
			inventory->items[i] = itemID;
			added = TRUE;
			printf("You picked up the %s.\n", itemName);
		}
	}
	if (added == FALSE) {
		printf("You have no space for the %s. Would you like to drop something to carry it?\n", itemName);
		printf("\t1) YES\n");
		printf("\t2) NO\n");
		
		int options = 2;
		int choice = GetInput(options, file);

		if (choice == 1) {
			int slot = RemoveItem(inventory, file);
			inventory->items[slot] = itemID;
			printf("You replaced the dropped item with the %s.\n", itemName);
		}
		else if (choice == 2) {
			printf("You decide to leave the %s be.\n", itemName);
		}
	}
}

/************************* RemoveItem() **************************
Purpose:	removes an item from an instance of the inventory
			struct

Input:		inventory	struct*		user's inventory

Output:		choice		int			chosen inventory slot to empty
******************************************************************/
int RemoveItem(INVENTORY *inventory, char* file) {
	printf("Which item would you like to drop?\n");
	DisplayInventory(*inventory);

	int options = MAX_ITEMS;
	int choice = GetInput(options, file);

	inventory->items[choice-1] = EMPTY;
	printf("You dropped the item in slot %d.\n", choice);

	return choice;
}

/********************** DisplayInventory() ***********************
Purpose:	displays the contents of the inventory

Input:		inventory	struct		user's inventory

Output:		none
******************************************************************/
void DisplayInventory(INVENTORY inventory) {
	for (int i = 0; i < MAX_ITEMS; i++) {
		const char* name = GetItemName(inventory.items[i]);
		printf("\t%d) %s\n", i+1, name);
	}
}

/************************ GetItemName() **************************
Purpose:	converts a given item ID into its corresponding name

Input:		itemID		int		number ID of item

Output:		char*	name of the item via ID
******************************************************************/
const char* GetItemName(int itemID) {
	const char* itemName;

	if (itemID == GUEST_KEY)	//add as many of these as there are items
		itemName = "GUEST KEY";
	else if (itemID == BATHROOM_KEY)
		itemName = "BATHROOM KEY";
	else if (itemID == MASTER_KEY)
		itemName = "MASTER KEY";
	else if (itemID == TWEEZERS)
		itemName = "TWEEZERS";
	else if (itemID == GLASSES)
		itemName = "GLASSES";
	else if (itemID == OUTSIDE_KEY)
		itemName = "FRONT DOOR KEY";
	else if (itemID == MATCHES)
		itemName = "MATCHES";
	else
		itemName = "EMPTY";
	
	return itemName;
}

/************************** HasItem() ****************************
Purpose:	checks if an item is in the user's inventory

Input:		inventory	struct		user's inventory
			itemID		int			item to be checked

Output:		TRUE/FALSE	int			true/false determination
******************************************************************/
int HasItem(INVENTORY inventory, int itemID) {
	for (int i = 0; i < MAX_ITEMS; i++) {
		if (inventory.items[i] == itemID)
			return TRUE;
	}
	return FALSE;
}

/************************ HasUsedItem() **************************
Purpose:	checks if an item has been used by the user

Input:		inventory	struct		user's inventory
			itemID		int			item to be checked

Output:		TRUE/FALSE	int			true/false determination
******************************************************************/
int HasUsedItem(INVENTORY inventory, int itemID) {
	for (int i = 0; i < MAX_USED; i++) {
		if (inventory.used[i] == itemID)
			return TRUE;
	}
	return FALSE;
}

/************************** UseItem() ****************************
Purpose:	uses an item, transfering it from the user's inventory
			to their used items

Input:		inventory	struct		user's inventory
			itemID		int			item being used

Output:		none
******************************************************************/
void UseItem(INVENTORY *inventory, int itemID) {
	int used = FALSE;
	int added = FALSE;

	for (int i = 0; i < MAX_ITEMS; i++) {
		if (inventory->items[i] == itemID && used == FALSE) {
			inventory->items[i] = EMPTY;
			used = TRUE;
		}
	}

	for (int j = 0; j < MAX_USED; j++) {
		if (inventory->used[j] == EMPTY && added == FALSE) {
			inventory->used[j] = itemID;
			added = TRUE;
		}
	}
	const char* itemName = GetItemName(itemID);
	printf("The %s was used.\n", itemName);
}
//-----------------

//--- ROOMS ---
/*********************** GuestBedroom() **************************
Purpose:	handles all guest bedroom interactions

Input:		user	struct*		user's data
			file	char*		name of log file
			dataFile	char*	name of data file

Output:		none
******************************************************************/
void GuestBedroom(USER *user, char* file, char* dataFile) {
	printf("This room is probably some kind of guest bedroom, judging by the single BED you\nwoke up on. ");
	printf("Its sheets are green, only marginally darker than the paint on the\nwalls. ");
	printf("There's a mildly musty smell to the air, like no one often visits this\nplace. ");
	printf("The small wooden SIDE TABLE next to the bed is scuffed up and a little\ndusty, adding to that impression. ");
	printf("Notably, however, the NOTE sitting atop the\nside table appears like a recent addition.\n");
	printf("\nThe only light in this room streams in through a bay window on the left of the\nside table, further into the room. ");
	printf("There isn't much to see outside, however, as\nsomeone has thoughroughly boarded up the glass with an excess of wooden boards.\n");
	printf("As a result, sunlight pours through whatever cracks it can find, unevenly\nlighting the area. ");
	printf("A DESK lies in front of the window, some old BOOKS stacked\non its surface in various colours. ");
	printf("There are also a few opaque JARS resting\nopposite to the books, covered in a particularily thick layering of dust.\n");
	printf("\nThere is one door in this room. It leads to the UPPER HALLWAY.\n");

	printf("\nFrom this room, your options are:\n");
	printf("\t1) Save and quit.\n");
	printf("\t2) Go to UPPER HALLWAY.\n");
	printf("\t3) Look at BED.\n");
	printf("\t4) Look at SIDE TABLE.\n");
	printf("\t5) Look at NOTE.\n");
	printf("\t6) Look at DESK.\n");
	printf("\t7) Look at BOOKS.\n");
	printf("\t8) Look at JARS.\n");
	printf("\t9) Check INVENTORY.\n");

	int options = 9;
	int choice = GetInput(options, file);

	if (choice == 1) {
		printf("Saving your progress...\n");
		OverwriteUser(*user, dataFile);
		printf("Progress saved! Game will now exit.\n");
		exit(EXIT_SUCCESS);
	}
	else if (choice == 2) {
		if (HasUsedItem(user->inventory, GUEST_KEY) == TRUE) {
			printf("Opening the door, you step into the hallway...\n");
			user->roomID = UPPER_HALLWAY;
			OverwriteUser(*user, dataFile);
		}
		else if(HasItem(user->inventory, GUEST_KEY == TRUE)){
			printf("You unlock the door.\n");
			UseItem(&user->inventory, GUEST_KEY);
			OverwriteUser(*user, dataFile);
		}
		else {
			printf("The door is locked. You're stuck here until you find a key.\n");
		}
	}
	else if (choice == 3) {
		printf("You take a closer look at the bed...\n");
		GuestBed(file);
		Sleep(SLEEP_TIME);
	}
	else if (choice == 4) {
		printf("You take a closer look at the side table...\n");
		GuestTable(file);
		Sleep(SLEEP_TIME);
	}
	else if (choice == 5) {
		printf("You take a closer look at the note on the table...\n");
		GuestNote();
		Sleep(SLEEP_TIME);
	}
	else if (choice == 6) {
		printf("You take a closer look at the desk...\n");
		GuestDesk(file);
		Sleep(SLEEP_TIME);
	}
	else if (choice == 7) {
		printf("You take a closer look at the books on the desk...\n");
		GuestBook();
		Sleep(SLEEP_TIME);
	}
	else if (choice == 8) {
		printf("You take a closer look at the jars on the desk...\n");
		GuestJar(user, file, dataFile);
		Sleep(SLEEP_TIME);
	}
	else if (choice == 9) {
		printf("Your inventory contains:\n");
		DisplayInventory(user->inventory);
	}
	Sleep(SHORT_SLEEP);
}

/*********************** UpperHallway() **************************
Purpose:	handles all upper hallway interactions

Input:		user	struct*		user's data
			file	char*		name of log file
			dataFile	char*	name of data file

Output:		none
******************************************************************/
void UpperHallway(USER* user, char* file, char* dataFile) {
	printf("With beige walls and grey wooden siding, this hallway does not give a very\ninteresting impression. ");
	printf("Its singular window is boarded up as you have come to\nexpect. ");
	printf("There is a STAIRCASE leading to a LOWER HALLWAY, with a door on either\nside of this upper hall. ");
	printf("The right door leads into the GUEST BEDROOM, and the\nleft door leads to the MASTER BEDROOM. ");
	printf("A few framed photos and paintings hang\non the wall above the stairs. Nothing of note about these.\n");

	printf("\nFrom this room, your options are:\n");
	printf("\t1) Save and quit.\n");
	printf("\t2) Go to GUEST BEDROOM.\n");
	printf("\t3) Go to MASTER BEDROOM.\n");
	printf("\t4) Go to LOWER HALLWAY.\n");
	printf("\t5) Look at STAIRCASE.\n");
	printf("\t6) Check INVENTORY.\n");

	int options = 5;
	int choice = GetInput(options, file);

	if (choice == 1) {
		printf("Saving your progress...\n");
		OverwriteUser(*user, dataFile);
		printf("Progress saved! Game will now exit.\n");
		exit(EXIT_SUCCESS);
	}
	else if (choice == 2) {
		printf("Opening the door, you step into the guest room...\n");
		user->roomID = GUEST_BEDROOM;
		OverwriteUser(*user, dataFile);
	}
	else if (choice == 3) {
		if (HasUsedItem(user->inventory, MASTER_KEY) == TRUE) {
			printf("Opening the door, you step into the master bedroom...\n");
			user->roomID = MASTER_BEDROOM;
			OverwriteUser(*user, dataFile);
		}
		else if (HasItem(user->inventory, MASTER_KEY) == TRUE) {
			printf("You unlock the door.\n");
			UseItem(&user->inventory, MASTER_KEY);
			OverwriteUser(*user, dataFile);
		}
		else {
			printf("The door is locked.\n");
		}
	}
	else if (choice == 4) {
		printf("Descending the stairs, you enter the lower hallway...\n");
		user->roomID = LOWER_HALLWAY;
		OverwriteUser(*user, dataFile);
	}
	else if (choice == 5) {
		printf("You take a closer look at the staircase...\n");
		Staircase();
		Sleep(SLEEP_TIME);
	}
	else if (choice == 6) {
		printf("Your inventory contains:\n");
		DisplayInventory(user->inventory);
	}
	Sleep(SHORT_SLEEP);
}

/*********************** MasterBedroom() *************************
Purpose:	handles all master bedroom interactions

Input:		user	struct*		user's data
			file	char*		name of log file
			dataFile	char*	name of data file

Output:		none
******************************************************************/
void MasterBedroom(USER* user, char* file, char* dataFile) {
	printf("Although it's larger than the guest room, this bedroom is not much more\ndecorated. ");
	printf("The walls are a plain deep blue, chipped in places, especially\naround the boarded up window. ");
	printf("At the very least, it doesn't smell as musty as\nthe guest room. ");
	printf("The double BED has some soft-looking flannel sheets which match\nthe colour of the walls pretty well. ");
	printf("As in the other bedroom, there is a SIDE\nTABLE next to the bed. ");
	if (HasItem(user->inventory, GLASSES) == FALSE && HasUsedItem(user->inventory, GLASSES) == FALSE)
		printf("A pair of GLASSES, a small CLOCK, and a lone opaque JAR\ntake up its surface. ");
	else
		printf("A small CLOCK and a lone opaque JAR take up its surface.\n");
	printf("The clock ticks quietly, the only obvious sound in this\nroom.\n");
	printf("\nThere is one door in this room, which leads to the UPPER HALLWAY.\n");

	printf("\nFrom this room, your options are:\n");
	printf("\t1) Save and quit.\n");
	printf("\t2) Go to UPPER HALLWAY.\n");
	printf("\t3) Look at BED.\n");
	printf("\t4) Look at SIDE TABLE.\n");
	if (HasItem(user->inventory, GLASSES) == FALSE && HasUsedItem(user->inventory, GLASSES) == FALSE)
		printf("\t5) Look at GLASSES.\n");
	printf("\t6) Look at CLOCK.\n");
	printf("\t7) Look at JAR.\n");
	printf("\t8) Check INVENTORY.\n");

	int options = 8;
	int choice = GetInput(options, file);

	if (choice == 1) {
		printf("Saving your progress...\n");
		OverwriteUser(*user, dataFile);
		printf("Progress saved! Game will now exit.\n");
		exit(EXIT_SUCCESS);
	}
	else if (choice == 2) {
		printf("Opening the door, you step into the hallway...\n");
		user->roomID = UPPER_HALLWAY;
		OverwriteUser(*user, dataFile);
	}
	else if (choice == 3) {
		printf("You take a closer look at the bed...\n");
		MasterBed(file);
		Sleep(SLEEP_TIME);
	}
	else if (choice == 4) {
		printf("You take a closer look at the side table...\n");
		MasterTable(user, file, dataFile);
		Sleep(SLEEP_TIME);
	}
	else if (choice == 5) {
		if (HasItem(user->inventory, GLASSES) == FALSE && HasUsedItem(user->inventory, GLASSES) == FALSE) {
			printf("You take a closer look at the glasses on the side table...\n");
			Glasses(user, file, dataFile);
			Sleep(SLEEP_TIME);
		}
		else {
			printf("That is not a valid option, please try again.\n");
		}
	}
	else if (choice == 6) {
		printf("You take a closer look at the clock on the side table...\n");
		Clock();
		Sleep(SLEEP_TIME);
	}
	else if (choice == 7) {
		printf("You take a closer look at the jar on the side table...\n");
		MasterJar();
		Sleep(SLEEP_TIME);
	}
	else if (choice == 8) {
		printf("Your inventory contains:\n");
		DisplayInventory(user->inventory);
	}
	Sleep(SHORT_SLEEP);
}

/*********************** LowerHallway() **************************
Purpose:	handles all lower hallway interactions

Input:		user	struct*		user's data
			file	char*		name of log file
			dataFile	char*	name of data file

Output:		none
******************************************************************/
void LowerHallway(USER* user, char* file, char* dataFile) {
	printf("This lower hall is quite large, technically also being a front room of sorts.\n");
	printf("There is a staircase leading back to the UPPER HALLWAY, with a KITCHEN across\nfrom the stairs, and a BATHROOM door on the wall to the left of it. ");
	printf("The entry\nto the LIVING ROOM is the same wall that the staircase ascends above, next to\nthe stairs. ");
	printf("Farther down the hall, to the right of the stairs, is the FRONT\nDOOR.\n");
	printf("\nAs is common with this house, there is minimal decor in this room. ");
	printf("Aside from a\nPOTTED PLANT in the corner between the bathroom and living room, and a SHOE\nRACK across from the front door. ");
	printf("Unless you want to count the TRASH CAN next to\nthe kitchen, but that feels like a stretch. ");
	printf("The plant isn't exactly thriving in\nthis environment, either. ");
	printf("It's an overall lackluster display, really. ");
	printf("Not that\nthe beige walls wanted you to believe otherwise.\n");

	printf("\nFrom this room, your options are:\n");
	printf("\t1) Save and quit.\n");
	printf("\t2) Go to UPPER HALLWAY.\n");
	printf("\t3) Go to KITCHEN.\n");
	printf("\t4) Go to BATHROOM.\n");
	printf("\t5) Go to LIVING ROOM.\n");
	printf("\t6) Go to OUTSIDE.\n");
	printf("\t7) Look at POTTED PLANT.\n");
	printf("\t8) Look at TRASH CAN.\n");
	printf("\t9) Look at SHOE RACK.\n");
	printf("\t10) Check INVENTORY.\n");

	int options = 10;
	int choice = GetInput(options, file);

	if (choice == 1) {
		printf("Saving your progress...\n");
		OverwriteUser(*user, dataFile);
		printf("Progress saved! Game will now exit.\n");
		exit(EXIT_SUCCESS);
	}
	else if (choice == 2) {
		printf("Ascending the stairs, you enter the upper hallway...\n");
		user->roomID = UPPER_HALLWAY;
		OverwriteUser(*user, dataFile);
	}
	else if (choice == 3) {
		printf("You step into the kitchen...\n");
		user->roomID = KITCHEN;
		OverwriteUser(*user, dataFile);
	}
	else if (choice == 4) {
		if (HasUsedItem(user->inventory, BATHROOM_KEY) == TRUE) {
			printf("Opening the door, you step into the bathroom...\n");
			user->roomID = BATHROOM;
			OverwriteUser(*user, dataFile);
		}
		else if (HasItem(user->inventory, BATHROOM_KEY) == TRUE) {
			printf("You unlock the door.\n");
			UseItem(&user->inventory, BATHROOM_KEY);
			OverwriteUser(*user, dataFile);
		}
		else {
			printf("The door is locked.\n");
		}
	}
	else if (choice == 5) {
		printf("You step into the living room...\n");
		user->roomID = LIVING_ROOM;
		OverwriteUser(*user, dataFile);
	}
	else if (choice == 6) {
		if (HasUsedItem(user->inventory, OUTSIDE_KEY) == TRUE) {
			printf("You step outside...\n");
			user->roomID = OUTSIDE;
			OverwriteUser(*user, dataFile);
		}
		else if (HasItem(user->inventory, OUTSIDE_KEY) == TRUE) {
			printf("You unlock the door.\n");
			UseItem(&user->inventory, OUTSIDE_KEY);
			OverwriteUser(*user, dataFile);
		}
		else {
			printf("The door is locked.\n");
		}
	}
	else if (choice == 7) {
		printf("You take a closer look at the potted plant...\n");
		PottedPlant();
		Sleep(SLEEP_TIME);
	}
	else if (choice == 8) {
		printf("You take a closer look at the trash can by the kitchen...\n");
		TrashCan(file);
		Sleep(SLEEP_TIME);
	}
	else if (choice == 9) {
		printf("You take a closer look at the shoe rack by the front door...\n");
		ShoeRack();
		Sleep(SLEEP_TIME);
	}
	else if (choice == 10) {
		printf("Your inventory contains:\n");
		DisplayInventory(user->inventory);
	}
	Sleep(SHORT_SLEEP);
}

/************************* Kitchen() *****************************
Purpose:	handles all kitchen interactions

Input:		user	struct*		user's data
			file	char*		name of log file
			dataFile	char*	name of data file

Output:		none
******************************************************************/
void Kitchen(USER* user, char* file, char* dataFile) {
	printf("Unlike the rest of this house, the kitchen floor is a cold tile in alternating\ncolours. ");
	printf("Most of the walls are covered in 2 l-shaped arranagements of kitchen\nCABINETS. ");
	printf("One acting as counterspace, and the other as further storage above\nthe first. ");
	printf("There is a SINK in the cabinets, as well as one counter on the end\nbeing replaced by a STOVE. ");
	printf("The corner on the other end holds the FRIDGE. ");
	printf("There\nis a metal pot rack hanging from the ceiling in the middle of it all.\n");
	printf("\nUnless you're going to get through that boarded up window, the only place to go\nfrom here is back to the LOWER HALLWAY.\n");

	printf("\nFrom this room, your options are:\n");
	printf("\t1) Save and quit.\n");
	printf("\t2) Go to LOWER HALLWAY.\n");
	printf("\t3) Look at CABINETS.\n");
	printf("\t4) Look at SINK.\n");
	printf("\t5) Look at STOVE.\n");
	printf("\t6) Look at FRIDGE.\n");
	printf("\t7) Check INVENTORY.\n");

	int options = 7;
	int choice = GetInput(options, file);

	if (choice == 1) {
		printf("Saving your progress...\n");
		OverwriteUser(*user, dataFile);
		printf("Progress saved! Game will now exit.\n");
		exit(EXIT_SUCCESS);
	}
	else if (choice == 2) {
		printf("You step into the hallway...\n");
		user->roomID = LOWER_HALLWAY;
		OverwriteUser(*user, dataFile);
	}
	else if (choice == 3) {
		printf("You take a closer look at the cabinets...\n");
		Cabinet(file);
		Sleep(SLEEP_TIME);
	}
	else if (choice == 4) {
		printf("You take a closer look at the sink...\n");
		KitchenSink(user, file, dataFile);
		Sleep(SLEEP_TIME);
	}
	else if (choice == 5) {
		printf("You take a closer look at the stove...\n");
		Stove();
		Sleep(SLEEP_TIME);
	}
	else if (choice == 6) {
		printf("You take a closer look at the fridge...\n");
		Fridge(file);
		Sleep(SLEEP_TIME);
	}
	else if (choice == 7) {
		printf("Your inventory contains:\n");
		DisplayInventory(user->inventory);
	}
	Sleep(SHORT_SLEEP);
}

/************************* Bathroom() ****************************
Purpose:	handles all bathroom interactions

Input:		user	struct*		user's data
			file	char*		name of log file
			dataFile	char*	name of data file

Output:		none
******************************************************************/
void Bathroom(USER* user, char* file, char* dataFile) {
	printf("This bathroom has seen better days. ");
	printf("The air here feels thick, somehow different\nand worse than the musty air of the guest bedroom. ");
	printf("There is a TOILET, SINK and\nBATHTUB as one would expect from the sole bathroom of the house, but you aren't\nparticularily keen on using any of them. ");
	printf("Something about this room makes you\nuneasy. ");
	printf("Your eyes are hesitant to even wander to the cracked MIRROR hanging\nabove the sink. ");
	printf("The less time you can spend in here, the better.\n");

	printf("\nFrom this room, your options are:\n");
	printf("\t1) Save and quit.\n");
	printf("\t2) Go to LOWER HALLWAY.\n");
	printf("\t3) Look at TOILET.\n");
	printf("\t4) Look at SINK.\n");
	printf("\t5) Look at BATHTUB.\n");
	printf("\t6) Look at MIRROR.\n");
	printf("\t7) Check INVENTORY.\n");

	int options = 7;
	int choice = GetInput(options, file);

	if (choice == 1) {
		printf("Saving your progress...\n");
		OverwriteUser(*user, dataFile);
		printf("Progress saved! Game will now exit.\n");
		exit(EXIT_SUCCESS);
	}
	else if (choice == 2) {
		printf("You step into the hallway...\n");
		user->roomID = LOWER_HALLWAY;
		OverwriteUser(*user, dataFile);
	}
	else if (choice == 3) {
		printf("You take a closer look at the toilet...\n");
		Toilet();
		Sleep(SLEEP_TIME);
	}
	else if (choice == 4) {
		printf("You take a closer look at the sink...\n");
		BathroomSink(user, dataFile);
		Sleep(SLEEP_TIME);
	}
	else if (choice == 5) {
		printf("You take a closer look at the bathtub...\n");
		Bathtub();
		Sleep(SLEEP_TIME);
	}
	else if (choice == 6) {
		printf("You take a closer look at the mirror...\n");
		Mirror();
		Sleep(SLEEP_TIME);
	}
	else if (choice == 7) {
		printf("Your inventory contains:\n");
		DisplayInventory(user->inventory);
	}
	Sleep(SHORT_SLEEP);
}

/************************ LivingRoom() ***************************
Purpose:	handles all guest bedroom interactions

Input:		user	struct*		user's data
			file	char*		name of log file
			dataFile	char*	name of data file

Output:		room	int			current room ID
******************************************************************/
void LivingRoom(USER* user, char* file, char* dataFile) {
	printf("This room is sort of l-shaped, with a BACK DOOR right across from the entrance\ninto the room. ");
	printf("Further along the same wall as the back door, there is an alcove\nof sorts containing a pale green COUCH and a small SIDE TABLE. ");
	printf("The coffee table\nacross from that holds a few BOOKS, and further into the room there is a\nLOVESEAT. ");
	printf("It's the same colour as the couch. ");
	printf("The FIREPLACE to the right of the\nloveseat is cold, not even any embers at the bottom.\n");
	printf("\nThe CARETAKER sits on the couch. ");
	printf("They are unremarkable in this strange sort of\nway where you can't really put your finger on what their features are. ");
	printf("They\nhave yet to pay you any mind, reading something in silence.\n");

	printf("\nFrom this room, your options are:\n");
	printf("\t1) Save and quit.\n");
	printf("\t2) Go to LOWER HALLWAY.\n");
	printf("\t3) Go to OUTSIDE.\n");
	printf("\t4) Look at COUCH.\n");
	printf("\t5) Look at SIDE TABLE.\n");
	printf("\t6) Look at BOOKS.\n");
	printf("\t7) Look at LOVESEAT.\n");
	printf("\t8) Look at FIREPLACE.\n");
	printf("\t9) Speak to CARETAKER.\n");
	printf("\t10) Check INVENTORY.\n");

	int options = 10;
	int choice = GetInput(options, file);

	if (choice == 1) {
		printf("Saving your progress...\n");
		OverwriteUser(*user, dataFile);
		printf("Progress saved! Game will now exit.\n");
		exit(EXIT_SUCCESS);
	}
	else if (choice == 2) {
		printf("You step into the hallway...\n");
		user->roomID = LOWER_HALLWAY;
		OverwriteUser(*user, dataFile);
	}
	else if (choice == 3) {
		if (HasUsedItem(user->inventory, OUTSIDE_KEY) == TRUE) {
			printf("You step outside...\n");
			user->roomID = OUTSIDE;
			OverwriteUser(*user, dataFile);
		}
		else if (HasItem(user->inventory, OUTSIDE_KEY) == TRUE) {
			printf("You unlock the door.\n");
			UseItem(user->roomID, OUTSIDE_KEY);
			OverwriteUser(*user, dataFile);
		}
		else {
			printf("The door is locked.\n");
		}
	}
	else if (choice == 4) {
		printf("You take a closer look at the couch...\n");
		Couch();
		Sleep(SLEEP_TIME);
	}
	else if (choice == 5) {
		printf("You take a closer look at the side table...\n");
		LivingTable(user, file);
		Sleep(SLEEP_TIME);
	}
	else if (choice == 6) {
		printf("You take a closer look at the books...\n");
		LivingBook();
		Sleep(SLEEP_TIME);
	}
	else if (choice == 7) {
		printf("You take a closer look at the loveseat...\n");
		Loveseat(file);
		Sleep(SLEEP_TIME);
	}
	else if (choice == 8) {
		printf("You take a closer look at the fireplace...\n");
		Fireplace(user, file, dataFile);
		Sleep(SLEEP_TIME);
	}
	else if (choice == 9) {
		printf("You approach the Caretaker...\n");
		Caretaker(file);
		Sleep(SLEEP_TIME);
	}
	else if (choice == 10) {
		printf("Your inventory contains:\n");
		DisplayInventory(user->inventory);
	}
	Sleep(SHORT_SLEEP);
}

/************************* Outside() *****************************
Purpose:	win location description

Input:		user	struct*		user's data
			file	char*		log file name
			dataFile	char*	data file name

Output:		none
******************************************************************/
void Outside(USER *user, char* file, char* dataFile) {
	printf("\"Stop!\"");
	printf("Before you can really step outside, a rough hand on your arm tugs you back,\n");
	printf("spinning you around to face the Caretaker. It doesn't take a genius to see that\n");
	printf("they aren't all that pleased with you.");
	Sleep(SHORT_SLEEP);
	printf("\"You cannot go out there, it is not safe.I allowed you to get this far, and\n");
	printf("that alone was a mistake.\"\n");
	printf("Their grip tightens around your arm.\n");
	printf("\"There is something out there,\n");
	Sleep(SHORT_SLEEP);
	printf("something waiting. Waiting for you to open that door.\"\n");
	Sleep(SHORT_SLEEP);
	printf("\"You just have to trust me.\"\n");
	Sleep(SHORT_SLEEP);
	printf("Will you GO OUTSIDE?\n");
	printf("\t1) YES\n");
	printf("\t2) NO\n");

	int options = 2;
	int choice = GetInput(options, file);

	if (choice == 1) {
		printf("Despite the Caretaker's warning, you yank your arm from their grip and push\n");
		printf("your way through the door. They reach out to stop you, but it's too late for\n");
		printf("that. The fresh outdoor breeze flows past, drowning out the stagnant air that\n");
		printf("permeated the interior of that house. You are free. The Caretaker cries out in\n");
		printf("anguish-- or warning, you aren't sure. That doesn't matter now.\n");
		Sleep(SHORT_SLEEP);
		printf("...How long has that second sun been there?\n");
	}
	else if (choice == 2) {
		printf("Despite all that you went through to ignore their warnings, something about\n");
		printf("their words made you falter. You step away from the door, and they loosen their\n");
		printf("grip on your arm.\n");
		printf("\"I know this is not easy to do.Thank you for trusting me.\"");
		printf("You give the door a last longing look before returning the key to the Caretaker\n");
		printf("Whatever is out there, you'll just have to trust them on it.\n");
		Sleep(SHORT_SLEEP);
		printf("...Still, is this really how you want to live for the forseeable future?\n");
	}

	user->roomID = 8;
	OverwriteUser(*user, dataFile);
}
//---------------

//--- INTERACTABLES ---
//I REALLY want to make these simpler if possible just because
//so many functions just for items feels ridiculous
//But I'm not sure how I'll do it yet
/************************* GuestBed() ****************************
Purpose:	guest bed information/interaction

Input:		file	char*		name of log file

Output:		none
******************************************************************/
void GuestBed(char* file) {
	printf("The bed is certainly nothing new, but it's not terrible either. ");
	printf("It at least is\nnot dusty. ");
	printf("If you really wanted, you could probably sleep on it.\n");
	printf("\nRest in the bed?\n");
	printf("\t1) YES\n");
	printf("\t2) NO\n");
	
	int options = 2;
	int choice = GetInput(options, file);

	if (choice == 1) {
		printf("No harm in a quick rest, it's not like the world is ending. ");
		printf("You lie down on the\nbed, which seems to fit you fairly well. ");
		printf("Laying there, you find yourself\ngreeted by the ceiling. ");
		printf("You aren't really sure how long you stay there, it's\nalmost like time stagnates.\n");
		printf("\nEventually, you exit the bed and stand back up. ");
		printf("Not really sure why you did\nthat.\n");
	}
	else if (choice == 2) {
		printf("Now is not the time for a break.\n");
	}
}

/************************ GuestTable() ***************************
Purpose:	guest table information/interaction

Input:		file	char*		name of log file

Output:		none
******************************************************************/
void GuestTable(char* file) {
	printf("Now that you are looking more closely at it... ");
	printf("The side table is still dusty.\n");
	printf("The top surface is covered in a thin layer of dust, but the small drawer on the\nfront of it still looks functional.\n");
	printf("\nDo you want to look inside?\n");
	printf("\t1) YES\n");
	printf("\t2) NO\n");

	int options = 2;
	int choice = GetInput(options, file);

	if (choice == 1) {
		printf("The drawer opens with minor resistance, catching for a few seconds before it\ncontinues to be opened with an audible squeaking. ");
		printf("Inside, you find...\n");
		printf("\nNot much. ");
		printf("There's a few half-empty pens, one broken with the dark liquid slowly\npooling on the interior of the drawer. ");
		printf("No real reason to take any of this with\nyou.\n");
	}
	else if (choice == 2) {
		printf("You leave it alone for now.\n");
	}
}

/************************ GuestNote() ****************************
Purpose:	guest note information/interaction

Input:		none

Output:		none
******************************************************************/
void GuestNote() {
	printf("Now that you are a bit closer, you can see the note clearly. ");
	printf("It reads:\n");
	printf("\n\"Greetings, I imagine you must be confused. ");
	printf("I have written this to help ease\nthat confusion. ");
	printf("You are currently in my home, in a room I hope you will enjoy.\n");
	printf("While I would prefer you stay in here, I will not stop you if you choose to\nwander. ");
	printf("However. I have one important request. ");
	printf("Regardless of what you may think\nyou want out there, no matter the circumstances, you must not go outside. ");
	printf("It's\nnot safe. ");
	printf("You must trust me on this, it is difficult to explain. ");
	printf("I hope you\nwill make yourself at home regardless.\"\n");
	printf("\nThe note ends there.\n");
}

/************************ GuestDesk() ****************************
Purpose:	guest desk information/interaction

Input:		file	char*		name of log file

Output:		none
******************************************************************/
void GuestDesk(char* file) {
	printf("Much like the rest of this room, the desk has a thin covering of dust atop it.\n");
	printf("It isn't that bad of a desk, really. ");
	printf("A little cleaning up and it could be\nsomething nice. ");
	printf("It has a couple of drawers you could check.\n");
	printf("Will you search the drawers?\n");
	printf("\t1) YES\n");
	printf("\t2) NO\n");

	int options = 2;
	int choice = GetInput(options, file);

	if (choice == 1) {
		printf("There are two drawers on each side of the desk. ");
		printf("The top left one refuses to\nbudge no matter how much effort you put into it. ");
		printf("The bottom left is completely\nempty... ");
		printf("The top right drawer has some loose papers, but they're all blank.\n");
		printf("The bottom right drawer is empty as well. This desk must not get much use.\n");
	}
	else if (choice == 2) {
		printf("No point in doing that right now.\n");
	}
}

/************************ GuestBook() ****************************
Purpose:	guest book information/interaction

Input:		none

Output:		none
******************************************************************/
void GuestBook() {
	printf("There is a paper stuck in one of the books, that doesn't seem to belong. ");
	printf("This\nis what it says...");
	printf("\"First, they will come in fives, bearing down upon the earth with reckless\nabandon.\"");
}

/************************ GuestJar() *****************************
Purpose:	guest jar information/interaction

Input:		user	struct*		user's data
			file	char*		name of log file
			dataFile	char*	name of data file

Output:		none
******************************************************************/
void GuestJar(USER *user, char* file, char* dataFile) {
	if (HasItem(user->inventory, GUEST_KEY) == FALSE && HasUsedItem(user->inventory, GUEST_KEY) == FALSE) {
		printf("The three odd jars sit on the desk and feel a bit out of place. ");
		printf("Being closer to\nthem like this, you notice a dark shape inside of one of the jars. ");
		printf("Something\nsmall, and oddly shaped.\n");
		printf("\nBreak open the jar?\n");
		printf("\t1) YES\n");
		printf("\t2) NO\n");

		int options = 2;
		int choice = GetInput(options, file);

		if (choice == 1) {
			printf("You picked up the small jar with ease, the item inside rattling with a metallic\nclanging against the glass walls. ");
			printf("You smash it into the desk, stray bits of\nopaque glass flying every which way. ");
			printf("From the remains of the smashed jar, you\nfind a key.\n");
			AddItem(&user->inventory, GUEST_KEY, file);
			OverwriteUser(*user, dataFile);
		}
		else if (choice == 2) {
			printf("Best not to go around breaking things.\n");
		}
	}
	else {
		printf("Only two strange jars remain. Nothing else of note about them.\n");
	}
}

/************************ Staircase() ****************************
Purpose:	staircase information/interaction

Input:		none

Output:		none
******************************************************************/
void Staircase() {
	printf("You admire the craftsmanship of these wooden stairs. ");
	printf("Despite their presumed age,\nthey still hold strong. ");
	printf("Nothing useful about them, though.\n");
}


/************************ MasterBed() ****************************
Purpose:	master bed information/interaction

Input:		file	char*		name of log file

Output:		none
******************************************************************/
void MasterBed(char* file) {
	printf("This bed looks a little better kept than the one in the guest room. ");
	printf("It probably\nis actively used by whoever lives here. ");
	printf("You don't really think its a good idea\nto sleep in someone's else bed. ");
	printf("But, you could still snoop around and see if\nanything is hidden under it.\n");
	printf("\nSearch the bed?\n");
	printf("\t1) YES\n");
	printf("\t2) NO\n");

	int options = 2;
	int choice = GetInput(options, file);

	if (choice == 1) {
		printf("It doesn't take long to check under the bed. ");
		printf("As far as you can tell, nothing is\ndown there. ");
		printf("Unless you're looking for dust. ");
		printf("Which you're probably not.\n");
	}
	else if (choice == 2) {
		printf("No need to do that.\n");
	}
}

/*********************** MasterTable() ***************************
Purpose:	master table information/interaction

Input:		user	struct*		user's data
			file	char*		name of log file
			dataFile	char*	name of data file

Output:		none
******************************************************************/
void MasterTable(USER *user, char* file, char* dataFile) {
	printf("This side table appears to be a matching piece to the one in the guest room.\n");
	printf("However, this one is not as dusty. ");
	printf("You could check the drawer if you wanted.\n");
	printf("\nSearch the side table?\n");
	printf("\t1) YES\n");
	printf("\t2) NO\n");

	int options = 2;
	int choice = GetInput(options, file);

	if (choice == 1) {
		if (HasUsedItem(user->inventory, MATCHES)) {
			printf("There is nothing else of use here.\n");
		}

		else {
			printf("This drawer is locked. Unlike the previous padlock, this one is hollow. ");
			printf("Despite\nthat, the lock remains in place. ");
			printf("There is a note stuffed in the hole, though.\nIt reads...");
			printf("\"Take me out and scratch my head, what once was red is now black instead.\"\n");
			printf("Maybe you can put something else here.\n");
			int isSolved = MasterPuzzle(&user->inventory, file);

			if (isSolved == TRUE) {
				printf("You easily slide open the drawer. Inside, there is a key.\n");
				AddItem(&user->inventory, OUTSIDE_KEY, file);
				OverwriteUser(*user, dataFile);
			}
		}
	}
	else if (choice == 2) {
		printf("You decide to leave it be.\n");
	}
}

/*********************** MasterPuzzle() ***************************
Purpose:	master table information/interaction

Input:		inv		struct*		user's inventory
			file	char*		name of log file

Output:		none
*******************************************************************/
int MasterPuzzle(INVENTORY *inv, char* file) {
	printf("Please select which item you want to use:\n");
	DisplayInventory(*inv);

	int options = MAX_ITEMS;
	int choice = GetInput(options, file);
	AppendToFile(file, choice);

	if (inv->items[choice - 1] == MATCHES) {
		printf("You put some matches inside the hollow of the padlock...\n");
		printf("Somehow, it clicks open!\n");
		UseItem(inv, MATCHES);
		return TRUE;
	}
	else {
		printf("That doesn't seem to work...\n");
		return FALSE;
	}
}

/************************* Glasses() *****************************
Purpose:	glasses information/interaction

Input:		user	struct*		user's data
			file	char*		name of log file
			dataFile	char*	name of data file

Output:		none
******************************************************************/
void Glasses(USER *user, char* file, char* dataFile) {
	printf("It seems a little strange for someone to leave these here if they aren't\nsleeping. ");
	printf("You could take them... if you really wanted.\n");
	printf("\nTake the glasses?\n");
	printf("\t1) YES\n");
	printf("\t2) NO\n");

	int options = 2;
	int choice = GetInput(options, file);

	if (choice == 1) {
		printf("You're not really sure why, but you take them.\n");
		AddItem(&user->inventory, GLASSES, file);
		OverwriteUser(*user, dataFile);
	}
	else {
		printf("No need to be taking people's glasses.\n");
	}
}

/************************** Clock() ******************************
Purpose:	clock information/interaction

Input:		none

Output:		none
******************************************************************/
void Clock() {
	printf("The clock is a small analogue one, ticking away the seconds at an even pace.\n");
	printf("It's made of mostly wood and metal, it looks quite nice actually. ");
	printf("You don't\nhave anything to use it for, though.\n");
}

/************************ MasterJar() ****************************
Purpose:	master jar information/interaction

Input:		none

Output:		none
******************************************************************/
void MasterJar() {
	printf("This jar looks a lot like the ones in the guest room. ");
	printf("Nothing to do with it\nright now.\n");
}


/*********************** PottedPlant() ***************************
Purpose:	potted plant information/interaction

Input:		none

Output:		none
******************************************************************/
void PottedPlant() {
	printf("You had already somewhat noted this from afar, but the plant looks sickly in\nits housing. ");
	printf("It isn't getting everything it needs, but it's still around anyway.\n");
	printf("Nothing you can do with it now.\n");
}

/************************ TrachCan() *****************************
Purpose:	trash can information/interaction

Input:		file	char*		name of log file

Output:		none
******************************************************************/
void TrashCan(char* file) {
	printf("The trash can is nearly full, you can spot many crumpled wrappers, pieces of\npaper, and other random odds and ends. ");
	printf("You could try digging through the trash\nif you really wanted to...\n");
	printf("\nSearch the trash can?\n");
	printf("\t1) YES\n");
	printf("\t2) NO\n");

	int options = 2;
	int choice = GetInput(options, file);

	if (choice == 1) {
		printf("Digging through the trash can, you find......\n");
		printf("More trash. Guess this person isn't one to hide things in a trash can. Figures.\n");
	}
	else if (choice == 2) {
		printf("You'll pass on digging through someone's garbage.\n");
	}
}

/************************ ShoeRack() *****************************
Purpose:	shoe rack information/interaction

Input:		none

Output:		none
******************************************************************/
void ShoeRack() {
	printf("A few pairs of shoes are neatly sitting on this rack. ");
	printf("All look to be about the\nsame size, just meant for different weather. ");
	printf("A single pair of boots has some\nmud on it, the rest appear to have not been used in quite some time.\n");
	printf("There is a neatly folded paper on the ground next to the rack, that you didn't\nnotice before. Something is written on it...\n");
	printf("\"The second one lies six feet under, in peaceful bliss.\"");
}

/************************* Cabinet() *****************************
Purpose:	cabinets information/interaction

Input:		file	char*		name of log file

Output:		none
******************************************************************/
void Cabinet(char* file) {
	printf("The kitchen has lots of available cabinets, but nothing particularily notable\nabout any of them. ");
	printf("Still, they could be worth searching in case of something\nuseful.");
	printf("\nSearch the cabinets?\n");
	printf("\t1) YES\n");
	printf("\t2) NO\n");

	int options = 2;
	int choice = GetInput(options, file);

	if (choice == 1) {
		printf("You spend a short time checking each cabinet, rifling through drawers for any\nsign of something worth holding onto. ");
		printf("There's plenty of utensils, plates, and\nother such things one would expect to find in a kitchen. ");
		printf("But, nothing useful.\n");
	}
	else if (choice == 2) {
		printf("You decide to leave them be.\n");
	}
}

/*********************** KitchenSink() ***************************
Purpose:	kitchen sink information/interaction

Input:		inv		struct*		user's inventory
			file	char*		name of log file

Output:		none
******************************************************************/
void KitchenSink(USER* user, char* file, char* dataFile) {
	if (HasItem(user->inventory, MASTER_KEY) == FALSE && HasUsedItem(user->inventory, MASTER_KEY) == FALSE) {
		printf("The sink looks fine enough...  ");
		printf("But now that you're closer you notice something\ninteresting. ");
		printf("There appears to be a metal glint of something wedged in the drain.\n");
		printf("Try to get it out?\n");
		printf("\t1) YES\n");
		printf("\t2) NO\n");

		int options = 2;
		int choice = GetInput(options, file);

		if (choice == 1) {
			if (HasItem(user->inventory, TWEEZERS) == TRUE) {
				UseItem(&user->inventory, TWEEZERS);
				printf("Using the tweezers, you're able to rescue the item. It's...\nA key.\n");
				AddItem(&user->inventory, BATHROOM_KEY, file);
			}
			else {
				printf("Try as you might, you can't seem to get a good grip. ");
				printf("If your fingers were a\nlittle smaller, maybe you could.\n");
			}
		}
		else if (choice == 2) {
			printf("You decide to leave it be.\n");
		}
	}
	else {
		printf("The sink looks fine enough, nothing notable. ");
		printf("It's no longer useful to you.\n");
	}
}

/************************** Stove() ******************************
Purpose:	stove information/interaction

Input:		none

Output:		none
******************************************************************/
void Stove() {
	printf("Well, it's definitely a stove. ");
	printf("No real use for it right now.\n");
}

/************************* Fridge() ******************************
Purpose:	fridge information/interaction

Input:		file	char*		name of log file

Output:		none
******************************************************************/
void Fridge(char* file) {
	printf("The fridge lays unadorned by any magnets or pictures. ");
	printf("Maybe there's something\ninside?\n");
	printf("\nSearch the fridge?\n");
	printf("\t1) YES\n");
	printf("\t2) NO\n");

	int options = 2;
	int choice = GetInput(options, file);

	if (choice == 1) {
		printf("You open the fridge door. ");
		printf("It has... Food in it. ");
		printf("The only thing of note is a\npiece of paper stuck to one of the inside walls. ");
		printf("There's something written on\nit...\n");
		printf("\"He is the third, the sole remainder in a faceless crowd.\"");
	}
	else if (choice == 2) {
		printf("You leave the fridge alone.\n");
	}
}


/************************* Toilet() ******************************
Purpose:	toilet information/interaction

Input:		none

Output:		none
******************************************************************/
void Toilet() {
	printf("You don't really want to touch this. Best to leave it alone.\n");
}

/*********************** BathroomSink() **************************
Purpose:	bathroom sink information/interaction

Input:		user	struct*		user information
			file	char*		log file name

Output:		none
******************************************************************/
void BathroomSink(USER* user, char* file) {
	printf("There is nothing too notable about this sink on the outside. ");
	printf("But the storage\nsection underneath could be a little more interesting...\n");
	printf("Search under the sink?\n");
	printf("\t1) YES\n");
	printf("\t2) NO\n");

	int options = 2;
	int choice = GetInput(options, file);

	if (choice == 1) {
		printf("You open it up. Reeks of cleaning supplies. ");
		printf("There are some assorted cleaning\nsupplies inside, but something else catches your attention. ");
		printf("A small box, with\na four - digit padlock. ");
		printf("Each number dial goes from 0 to 9, pretty standard.\n");
		printf("If you have the right code, you could probably unlock it...\n");
		printf("\t1) Input a code\n");
		printf("\t2) Leave\n");

		int choice2 = GetInput(options, file);

		if (choice2 == 1) {
			int isSolved = SinkPuzzle(file);
			if (isSolved == TRUE) {
				printf("The box now opens with no issue. Inside, you find another key.\n");
				AddItem(&user->inventory, MASTER_KEY, file);
				OverwriteUser(*user, file);
			}
		}
		else if (choice2 == 2) {
			printf("You leave it alone for now.\n");
		}
	}
	else if (choice == 2) {
		printf("Best not to.\nYou might not like what you find down there.\n");
	}
}

/************************ SinkPuzzle() ***************************
Purpose:	sink puzzle code input

Input:		file	char*	log file name

Output:		TRUE/FALSE	int		true/false flag
******************************************************************/
int SinkPuzzle(char* file) {
	int code = 0;

	while (code != -1 && code != SINK_PUZZLE) {
		printf("Please enter a four-digit code below (-1 to quit):\n>");
		scanf_s("%d", &code);
		AppendToFile(file, code);

		if (code == -1) {
			return FALSE;
		}
		else if (code != SINK_PUZZLE) {
			printf("Incorrect code.\n");
		}
	}
	printf("Click!\n");
	printf("The box is unlocked.\n");
	return TRUE;
}

/************************* Bathtub() *****************************
Purpose:	bathtub information/interaction

Input:		none

Output:		none
******************************************************************/
void Bathtub() {
	printf("You can't see anything useful to do with this. Better leave it be.\n");
}

/************************* Mirror() ******************************
Purpose:	mirror information/interaction

Input:		none

Output:		none
******************************************************************/
void Mirror() {
	printf("The mirror is grimy and cracked, you can barely see your own face through its\nfragmented glass. ");
	printf("Staring into it makes you uneasy. ");
	printf("It feels like time to\nleave.\n");
}


/************************** Couch() ******************************
Purpose:	couch information/interaction

Input:		none

Output:		none
******************************************************************/
void Couch() {
	printf("The couch is partially occupied by the Caretaker, but aside from that there\nisn't anything notable about it.\n");
}

/*********************** LivingTable() ***************************
Purpose:	living room table information/interaction

Input:		none

Output:		none
******************************************************************/
void LivingTable(USER *user, char* file) {
	printf("This wodden table is of about the quality you've come to expect of this house.\n");
	printf("Nice enough, but certainly not new. ");
	printf("There are books sitting on it that you\nalready saw upon entering the room.\n");
	if (!HasUsedItem(user->inventory, MATCHES) || !HasItem(user->inventory, MATCHES)) {
		printf("There is also a box of matches. That could be useful, maybe.\n");
		printf("Take the matches?\n");
		printf("\t1) YES\n");
		printf("\t2) NO\n");

		int options = 2;
		int choice = GetInput(options, file);

		if (choice == 1) {
			printf("Not like anyone is using them, anyway.\n");
			AddItem(&user->inventory, MATCHES, file);
			OverwriteUser(*user, file);
		}
		else if (choice == 2) {
			printf("Best leave it alone for now.\n");
		}
	}
}

/************************ LivingBook() ***************************
Purpose:	living room book information/interaction

Input:		none

Output:		none
******************************************************************/
void LivingBook() {
	printf("This small stack of books doesn't have any names that jump out at you. ");
	printf("Maybe\nthey could be useful for something, but you don't know what.\n");
	printf("There is, however, a note stuck to one of them. it reads...\n");
	printf("\"Finally, seven have been united under the shrinking remnants of our fading\nworld.\"");
}

/************************ Loveseat() *****************************
Purpose:	loveseat information/interaction

Input:		file	char*		name of log file

Output:		none
******************************************************************/
void Loveseat(char* file){
	printf("Much like the couch, there isn't much to note about this loveseat. ");
	printf("It's\nbasically just a smaller version with no one sitting on it. ");
	printf("You could search\nthe cushions if you were really so inclined.\n");
	printf("\nSearch the loveseat?\n");
	printf("\t1) YES\n");
	printf("\t2) NO\n");

	int options = 2;
	int choice = GetInput(options, file);

	if (choice == 1) {
		printf("Unfortunately, nothing was hidden in the cushions.\n");
	}
	else if (choice == 2) {
		printf("No need to do that.\n");
	}
}

/************************ Fireplace() ****************************
Purpose:	fireplace information/interaction

Input:		user	struct*		user's data
			file	char*		name of log file
			dataFile	char*	name of data file

Output:		none
******************************************************************/
void Fireplace(USER* user, char* file, char* dataFile) {
	printf("The fireplace is cold. ");
	if (HasItem(user->inventory, TWEEZERS) == TRUE && HasUsedItem(user->inventory, TWEEZERS) == TRUE) {
		printf("There are old ashes at the bottom, but nothing of note.\n");
		printf("Unless you want ashes for some reason.\n");
	}
	else {
		printf("Amongst the old ashes, something small and metal catches your eye. ");
		printf("Perhaps a\nkey? ");
		printf("Investigating closer, you find... Tweezers. ");
		printf("What a weird place for these\nto be.\n");
		AddItem(&user->inventory, TWEEZERS, file);
		OverwriteUser(*user, dataFile);
	}
}

/************************ Caretaker() ****************************
Purpose:	caretaker information/interaction

Input:		file	char*		name of log file

Output:		none
******************************************************************/
void Caretaker(char* file) {
	printf("The Caretaker doesn't seem to notice you at first, only looking up from their\nbook a short time after you approach. ");
	printf("They give you a curious look.\n");
	printf("\n\"Would you like something?\"\n");
	printf("\t1) When can I leave\n");
	printf("\t2) Nothing\n");

	int options = 2;
	int choice = GetInput(options, file);

	if (choice == 1) {
		printf("\"Did you... even read my note? You CANNOT leave. ");
		printf("You have to stay here. There is\nnothing good out there anymore.\"\n");
		printf("\nTheir face grows stern, something akin to a frustrated parent. ");
		printf("You get the\nimpression that they aren't likely to budge on this idea. ");
		printf("Perhaps you should\njust leave for now.\n");
	}
	else if (choice == 2) {
		printf("\"I see. Let me know if you need anything.\"\n");
	}
}
//----------------------