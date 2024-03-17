/***********************************************
Name:	Max V.
Date:	24-Jan-2023
Desc:	An ongoing text game project.

21-Feb-2023:	Phase 2-2 of the project.
				Added headers to each function.
				Added misc comments.
				Started changelog.
************************************************/

#include <stdio.h>

//******************CONSTANTS******************
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
#define MASTER_KEY		2
#define TWEEZERS		3
#define GLASSES			4
#define OUTSIDE_KEY		5

//--- BOOL ---
#define TRUE			1
#define FALSE			0
//*********************************************

//*****************STRUCTURES******************
typedef struct inventory {
	int items[MAX_ITEMS];
	int used[MAX_USED];
}INVENTORY;

//once we add files and such I want to make a room struct
//and maybe an item one
//so all these really similar functions can be condensed

//**********************************************

//*************FUNCTION PROTOTYPES**************
//--- USEFUL STUFF ---
int ReadInput(int input);
int GetInput(int optionNum);
//--------------------

//--- INVENTORY ---
INVENTORY CreateInventory();
void AddItem(INVENTORY *inv, int itemID);
int RemoveItem(INVENTORY *inv);
void DisplayInventory(INVENTORY inv);
const char* GetItemName(int itemID);
int HasItem(INVENTORY inventory, int itemID);
int HasUsedItem(INVENTORY inventory, int itemID);
void UseItem(INVENTORY* inventory, int itemID);
//-----------------

//--- ROOMS ---
int GuestBedroom(int room, INVENTORY *inv);
int UpperHallway(int room, INVENTORY *inv);
int MasterBedroom(int room, INVENTORY *inv);
int LowerHallway(int room, INVENTORY *inv);
int Kitchen(int room, INVENTORY *inv);
int Bathroom(int room, INVENTORY *inv);
int LivingRoom(int room, INVENTORY *inv);
int Outside(int room);
//--------------

//--- INTERACTABLES ---
void GuestBed();
void GuestTable();
void GuestNote();
void GuestDesk();
void GuestBook();
void GuestJar(INVENTORY *inv);

void Staircase();

void MasterBed();
void MasterTable(INVENTORY *inv);
void Glasses(INVENTORY *inv);
void Clock();
void MasterJar();

void PottedPlant();
void TrashCan();
void ShoeRack();

void Cabinet();
void KitchenSink(INVENTORY *inv);
void Stove();
void Fridge();

void Toilet();
void BathroomSink();
void Bathtub();
void Mirror();

void Couch();
void LivingTable();
void LivingBook();
void Loveseat();
void Fireplace(INVENTORY *inv);
void Caretaker();
//---------------------

int main(void) {
	int room = GUEST_BEDROOM;

	INVENTORY inventory = CreateInventory();

	do {
		switch (room) {
		case GUEST_BEDROOM:
			printf("\n---------------\n");
			printf("GUEST BEDROOM");
			printf("\n---------------\n");
			room = GuestBedroom(room, &inventory);
			break;
		
		case UPPER_HALLWAY:
			printf("\n---------------\n");
			printf("UPPER HALLWAY");
			printf("\n---------------\n");
			room = UpperHallway(room, &inventory);
			break;
		
		case MASTER_BEDROOM:
			printf("\n---------------\n");
			printf("MASTER BEDROOM");
			printf("\n---------------\n");
			room = MasterBedroom(room, &inventory);
			break;
		
		case LOWER_HALLWAY:
			printf("\n---------------\n");
			printf("LOWER HALLWAY");
			printf("\n---------------\n");
			room = LowerHallway(room, &inventory);
			break;
		
		case KITCHEN:
			printf("\n---------------\n");
			printf("KITCHEN");
			printf("\n---------------\n");
			room = Kitchen(room, &inventory);
			break;
		
		case BATHROOM:
			printf("\n---------------\n");
			printf("BATHROOM");
			printf("\n---------------\n");
			room = Bathroom(room, &inventory);
			break;
		
		case LIVING_ROOM:
			printf("\n---------------\n");
			printf("LIVING ROOM");
			printf("\n---------------\n");
			room = LivingRoom(room, &inventory);
			break;
		
		case OUTSIDE:
			printf("\n---------------\n");
			printf("OUTSIDE");
			printf("\n---------------\n");
			room = Outside(room);
			break;
		}
	} while (room <= OUTSIDE);
	
	return 0;
}

//****************FUNCTIONS*********************
//--- USEFUL STUFF ---
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

Output:		input		int		user's input
******************************************************************/
int GetInput(int optionNum) {
	int input = 0;
	
	printf("\nPlease input your answer below:\n> ");
	input = ReadInput(input);

	if (input > optionNum || input < 1)
		printf("\nThat is not a valid option, please try again.\n");

	return input;
}
//---------------------

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
void AddItem(INVENTORY *inventory, int itemID) {
	int added = FALSE;
	char* itemName = GetItemName(itemID);

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
		int choice = GetInput(options);

		if (choice == 1) {
			int slot = RemoveItem(inventory);
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
int RemoveItem(INVENTORY *inventory) {
	printf("Which item would you like to drop?\n");
	DisplayInventory(*inventory);

	int options = MAX_ITEMS;
	int choice = GetInput(options);

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
		char* name = GetItemName(inventory.items[i]);
		printf("\t%d) %s\n", i+1, name);
	}
}

/************************ GetItemName() **************************
Purpose:	converts a given item ID into its corresponding name

Input:		itemID		int		number ID of item

Output:		char*	name of the item via ID
******************************************************************/
const char* GetItemName(int itemID) {
	if (itemID == GUEST_KEY)	//add as many of these as there are items
		return "GUEST KEY";
	else if (itemID == MASTER_KEY)
		return "MASTER KEY";
	else if (itemID == TWEEZERS)
		return "TWEEZERS";
	else if (itemID == GLASSES)
		return "GLASSES";
	else if (itemID == OUTSIDE_KEY)
		return "FRONT DOOR KEY";
	else
		return "EMPTY";
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
	for (int i = 0; i < MAX_ITEMS; i++) {
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
	char* itemName = GetItemName(itemID);
	printf("The %s was used.\n", itemName);
}
//-----------------

//--- ROOMS ---
/*********************** GuestBedroom() **************************
Purpose:	handles all guest bedroom interactions

Input:		room	int			current room ID
			inv		struct*		user's inventory

Output:		room	int			current room ID
******************************************************************/
int GuestBedroom(int room, INVENTORY *inv) {
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
	printf("\t1) Stay here.\n");
	printf("\t2) Go to UPPER HALLWAY.\n");
	printf("\t3) Look at BED.\n");
	printf("\t4) Look at SIDE TABLE.\n");
	printf("\t5) Look at NOTE.\n");
	printf("\t6) Look at DESK.\n");
	printf("\t7) Look at BOOKS.\n");
	printf("\t8) Look at JARS.\n");
	printf("\t9) Check INVENTORY.\n");

	int options = 9;
	int choice = GetInput(options);

	if (choice == 1) {
		printf("You have chosen to stay in the room.\n");
	}
	else if (choice == 2) {
		if (HasUsedItem(*inv, GUEST_KEY) == TRUE) {
			printf("Opening the door, you step into the hallway...\n");
			room = UPPER_HALLWAY;
		}
		else if(HasItem(*inv, GUEST_KEY == TRUE)){
			printf("You unlock the door.\n");
			UseItem(inv, GUEST_KEY);
		}
		else {
			printf("The door is locked. You're stuck here until you find a key.\n");
		}
	}
	else if (choice == 3) {
		printf("You take a closer look at the bed...\n");
		GuestBed();
	}
	else if (choice == 4) {
		printf("You take a closer look at the side table...\n");
		GuestTable();
	}
	else if (choice == 5) {
		printf("You take a closer look at the note on the table...\n");
		GuestNote();
	}
	else if (choice == 6) {
		printf("You take a closer look at the desk...\n");
		GuestDesk();
	}
	else if (choice == 7) {
		printf("You take a closer look at the books on the desk...\n");
		GuestBook();
	}
	else if (choice == 8) {
		printf("You take a closer look at the jars on the desk...\n");
		GuestJar(inv);
	}
	else if (choice == 9) {
		printf("Your inventory contains:\n");
		DisplayInventory(*inv);
	}
	return room;
}

/*********************** UpperHallway() **************************
Purpose:	handles all upper hallway interactions

Input:		room	int			current room ID
			inv		struct*		user's inventory

Output:		room	int			current room ID
******************************************************************/
int UpperHallway(int room, INVENTORY *inv) {
	printf("With beige walls and grey wooden siding, this hallway does not give a very\ninteresting impression. ");
	printf("Its singular window is boarded up as you have come to\nexpect. ");
	printf("There is a STAIRCASE leading to a LOWER HALLWAY, with a door on either\nside of this upper hall. ");
	printf("The right door leads into the GUEST BEDROOM, and the\nleft door leads to the MASTER BEDROOM. ");
	printf("A few framed photos and paintings hang\non the wall above the stairs. Nothing of note about these.\n");

	printf("\nFrom this room, your options are:\n");
	printf("\t1) Stay here.\n");
	printf("\t2) Go to GUEST BEDROOM.\n");
	printf("\t3) Go to MASTER BEDROOM.\n");
	printf("\t4) Go to LOWER HALLWAY.\n");
	printf("\t5) Look at STAIRCASE.\n");
	printf("\t6) Check INVENTORY.\n");

	int options = 5;
	int choice = GetInput(options);

	if (choice == 1) {
		printf("You have chosen to stay in the room.\n");
	}
	else if (choice == 2) {
		printf("Opening the door, you step into the guest room...\n");
		room = GUEST_BEDROOM;
	}
	else if (choice == 3) {
		if (HasUsedItem(*inv, MASTER_KEY) == TRUE) {
			printf("Opening the door, you step into the master bedroom...\n");
			room = MASTER_BEDROOM;
		}
		else if (HasItem(*inv, MASTER_KEY) == TRUE) {
			printf("You unlock the door.\n");
			UseItem(inv, MASTER_KEY);
		}
		else {
			printf("The door is locked.\n");
		}
	}
	else if (choice == 4) {
		printf("Descending the stairs, you enter the lower hallway...\n");
		room = LOWER_HALLWAY;
	}
	else if (choice == 5) {
		printf("You take a closer look at the staircase...\n");
		Staircase();
	}
	else if (choice == 6) {
		printf("Your inventory contains:\n");
		DisplayInventory(*inv);
	}

	return room;
}

/*********************** MasterBedroom() *************************
Purpose:	handles all master bedroom interactions

Input:		room	int			current room ID
			inv		struct*		user's inventory

Output:		room	int			current room ID
******************************************************************/
int MasterBedroom(int room, INVENTORY *inv) {
	printf("Although it's larger than the guest room, this bedroom is not much more\ndecorated. ");
	printf("The walls are a plain deep blue, chipped in places, especially\naround the boarded up window. ");
	printf("At the very least, it doesn't smell as musty as\nthe guest room. ");
	printf("The double BED has some soft-looking flannel sheets which match\nthe colour of the walls pretty well. ");
	printf("As in the other bedroom, there is a SIDE\nTABLE next to the bed. ");
	if (HasItem(*inv, GLASSES) == FALSE && HasUsedItem(*inv, GLASSES) == FALSE)
		printf("A pair of GLASSES, a small CLOCK, and a lone opaque JAR\ntake up its surface. ");
	else
		printf("A small CLOCK and a lone opaque JAR take up its surface.\n");
	printf("The clock ticks quietly, the only obvious sound in this\nroom.\n");
	printf("\nThere is one door in this room, which leads to the UPPER HALLWAY.\n");

	printf("\nFrom this room, your options are:\n");
	printf("\t1) Stay here.\n");
	printf("\t2) Go to UPPER HALLWAY.\n");
	printf("\t3) Look at BED.\n");
	printf("\t4) Look at SIDE TABLE.\n");
	if (HasItem(*inv, GLASSES) == FALSE && HasUsedItem(*inv, GLASSES) == FALSE)
		printf("\t5) Look at GLASSES.\n");
	printf("\t6) Look at CLOCK.\n");
	printf("\t7) Look at JAR.\n");
	printf("\t8) Check INVENTORY.\n");

	int options = 8;
	int choice = GetInput(options);

	if (choice == 1) {
		printf("You have chosen to stay in the room.\n");
	}
	else if (choice == 2) {
		printf("Opening the door, you step into the hallway...\n");
		room = UPPER_HALLWAY;
	}
	else if (choice == 3) {
		printf("You take a closer look at the bed...\n");
		MasterBed();
	}
	else if (choice == 4) {
		printf("You take a closer look at the side table...\n");
		MasterTable(inv);
	}
	else if (choice == 5) {
		if (HasItem(*inv, GLASSES) == FALSE && HasUsedItem(*inv, GLASSES) == FALSE) {
			printf("You take a closer look at the glasses on the side table...\n");
			Glasses(inv);
		}
		else {
			printf("That is not a valid option, please try again.\n");
		}
	}
	else if (choice == 6) {
		printf("You take a closer look at the clock on the side table...\n");
		Clock();
	}
	else if (choice == 7) {
		printf("You take a closer look at the jar on the side table...\n");
		MasterJar();
	}
	else if (choice == 8) {
		printf("Your inventory contains:\n");
		DisplayInventory(*inv);
	}

	return room;
}

/*********************** LowerHallway() **************************
Purpose:	handles all lower hallway interactions

Input:		room	int			current room ID
			inv		struct*		user's inventory

Output:		room	int			current room ID
******************************************************************/
int LowerHallway(int room, INVENTORY *inv) {
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
	printf("\t1) Stay here.\n");
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
	int choice = GetInput(options);

	if (choice == 1) {
		printf("You have chosen to stay in the room.\n");
	}
	else if (choice == 2) {
		printf("Ascending the stairs, you enter the upper hallway...\n");
		room = UPPER_HALLWAY;
	}
	else if (choice == 3) {
		printf("You step into the kitchen...\n");
		room = KITCHEN;
	}
	else if (choice == 4) {
		printf("Opening the door, you step into the bathroom...\n");
		room = BATHROOM;
	}
	else if (choice == 5) {
		printf("You step into the living room...\n");
		room = LIVING_ROOM;
	}
	else if (choice == 6) {
		if (HasUsedItem(*inv, OUTSIDE_KEY) == TRUE) {
			printf("You step outside...\n");
			room = OUTSIDE;
		}
		else if (HasItem(*inv, OUTSIDE_KEY) == TRUE) {
			printf("You unlock the door.\n");
			UseItem(inv, OUTSIDE_KEY);
		}
		else {
			printf("The door is locked.\n");
		}
	}
	else if (choice == 7) {
		printf("You take a closer look at the potted plant...\n");
		PottedPlant();
	}
	else if (choice == 8) {
		printf("You take a closer look at the trash can by the kitchen...\n");
		TrashCan();
	}
	else if (choice == 9) {
		printf("You take a closer look at the shoe rack by the front door...\n");
		ShoeRack();
	}
	else if (choice == 10) {
		printf("Your inventory contains:\n");
		DisplayInventory(*inv);
	}

	return room;
}

/************************* Kitchen() *****************************
Purpose:	handles all kitchen interactions

Input:		room	int			current room ID
			inv		struct*		user's inventory

Output:		room	int			current room ID
******************************************************************/
int Kitchen(int room, INVENTORY *inv) {
	printf("Unlike the rest of this house, the kitchen floor is a cold tile in alternating\ncolours. ");
	printf("Most of the walls are covered in 2 l-shaped arranagements of kitchen\nCABINETS. ");
	printf("One acting as counterspace, and the other as further storage above\nthe first. ");
	printf("There is a SINK in the cabinets, as well as one counter on the end\nbeing replaced by a STOVE. ");
	printf("The corner on the other end holds the FRIDGE. ");
	printf("There\nis a metal pot rack hanging from the ceiling in the middle of it all.\n");
	printf("\nUnless you're going to get through that boarded up window, the only place to go\nfrom here is back to the LOWER HALLWAY.\n");

	printf("\nFrom this room, your options are:\n");
	printf("\t1) Stay here.\n");
	printf("\t2) Go to LOWER HALLWAY.\n");
	printf("\t3) Look at CABINETS.\n");
	printf("\t4) Look at SINK.\n");
	printf("\t5) Look at STOVE.\n");
	printf("\t6) Look at FRIDGE.\n");
	printf("\t7) Check INVENTORY.\n");

	int options = 7;
	int choice = GetInput(options);

	if (choice == 1) {
		printf("You have chosen to stay in the room.\n");
	}
	else if (choice == 2) {
		printf("You step into the hallway...\n");
		room = LOWER_HALLWAY;
	}
	else if (choice == 3) {
		printf("You take a closer look at the cabinets...\n");
		Cabinet();
	}
	else if (choice == 4) {
		printf("You take a closer look at the sink...\n");
		KitchenSink(inv);
	}
	else if (choice == 5) {
		printf("You take a closer look at the stove...\n");
		Stove();
	}
	else if (choice == 6) {
		printf("You take a closer look at the fridge...\n");
		Fridge();
	}
	else if (choice == 7) {
		printf("Your inventory contains:\n");
		DisplayInventory(*inv);
	}

	return room;
}

/************************* Bathroom() ****************************
Purpose:	handles all bathroom interactions

Input:		room	int			current room ID
			inv		struct*		user's inventory

Output:		room	int			current room ID
******************************************************************/
int Bathroom(int room, INVENTORY *inv) {
	printf("This bathroom has seen better days. ");
	printf("The air here feels thick, somehow different\nand worse than the musty air of the guest bedroom. ");
	printf("There is a TOILET, SINK and\nBATHTUB as one would expect from the sole bathroom of the house, but you aren't\nparticularily keen on using any of them. ");
	printf("Something about this room makes you\nuneasy. ");
	printf("Your eyes are hesitant to even wander to the cracked MIRROR hanging\nabove the sink. ");
	printf("The less time you can spend in here, the better.\n");

	printf("\nFrom this room, your options are:\n");
	printf("\t1) Stay here.\n");
	printf("\t2) Go to LOWER HALLWAY.\n");
	printf("\t3) Look at TOILET.\n");
	printf("\t4) Look at SINK.\n");
	printf("\t5) Look at BATHTUB.\n");
	printf("\t6) Look at MIRROR.\n");
	printf("\t7) Check INVENTORY.\n");

	int options = 7;
	int choice = GetInput(options);

	if (choice == 1) {
		printf("You have chosen to stay in the room.\n");
	}
	else if (choice == 2) {
		printf("You step into the hallway...\n");
		room = LOWER_HALLWAY;
	}
	else if (choice == 3) {
		printf("You take a closer look at the toilet...\n");
		Toilet();
	}
	else if (choice == 4) {
		printf("You take a closer look at the sink...\n");
		BathroomSink();
	}
	else if (choice == 5) {
		printf("You take a closer look at the bathtub...\n");
		Bathtub();
	}
	else if (choice == 6) {
		printf("You take a closer look at the mirror...\n");
		Mirror();
	}
	else if (choice == 7) {
		printf("Your inventory contains:\n");
		DisplayInventory(*inv);
	}

	return room;
}

/************************ LivingRoom() ***************************
Purpose:	handles all guest bedroom interactions

Input:		room	int			current room ID
			inv		struct*		user's inventory

Output:		room	int			current room ID
******************************************************************/
int LivingRoom(int room, INVENTORY *inv) {
	printf("This room is sort of l-shaped, with a BACK DOOR right across from the entrance\ninto the room. ");
	printf("Further along the same wall as the back door, there is an alcove\nof sorts containing a pale green COUCH and a small SIDE TABLE. ");
	printf("The coffee table\nacross from that holds a few BOOKS, and further into the room there is a\nLOVESEAT. ");
	printf("It's the same colour as the couch. ");
	printf("The FIREPLACE to the right of the\nloveseat is cold, not even any embers at the bottom.\n");
	printf("\nThe CARETAKER sits on the couch. ");
	printf("They are unremarkable in this strange sort of\nway where you can't really put your finger on what their features are. ");
	printf("They\nhave yet to pay you any mind, reading something in silence.\n");

	printf("\nFrom this room, your options are:\n");
	printf("\t1) Stay here.\n");
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
	int choice = GetInput(options);

	if (choice == 1) {
		printf("You have chosen to stay in the room.\n");
	}
	else if (choice == 2) {
		printf("You step into the hallway...\n");
		room = LOWER_HALLWAY;
	}
	else if (choice == 3) {
		if (HasUsedItem(*inv, OUTSIDE_KEY) == TRUE) {
			printf("You step outside...\n");
			room = OUTSIDE;
		}
		else if (HasItem(*inv, OUTSIDE_KEY) == TRUE) {
			printf("You unlock the door.\n");
			UseItem(inv, OUTSIDE_KEY);
		}
		else {
			printf("The door is locked.\n");
		}
	}
	else if (choice == 4) {
		printf("You take a closer look at the couch...\n");
		Couch();
	}
	else if (choice == 5) {
		printf("You take a closer look at the side table...\n");
		LivingTable();
	}
	else if (choice == 6) {
		printf("You take a closer look at the books...\n");
		LivingBook();
	}
	else if (choice == 7) {
		printf("You take a closer look at the loveseat...\n");
		Loveseat();
	}
	else if (choice == 8) {
		printf("You take a closer look at the fireplace...\n");
		Fireplace(inv);
	}
	else if (choice == 9) {
		printf("You approach the Caretaker...\n");
		Caretaker();
	}
	else if (choice == 10) {
		printf("Your inventory contains:\n");
		DisplayInventory(*inv);
	}

	return room;
}

/************************* Outside() *****************************
Purpose:	win location description

Input:		room	int			current room ID

Output:		room	int			current room ID
******************************************************************/
int Outside(int room) {
	printf("Congrats! You made it outside!\n");
	printf("\n...It's going to be more challenging in the real thing.\n");
	room = 8;
	return room;
}
//---------------

//--- INTERACTABLES ---
//I REALLY want to make these simpler if possible just because
//so many functions just for items feels ridiculous
//But I'm not sure how I'll do it yet
/************************* GuestBed() ****************************
Purpose:	guest bed information/interaction

Input:		none

Output:		none
******************************************************************/
void GuestBed() {
	printf("The bed is certainly nothing new, but it's not terrible either. ");
	printf("It at least is\nnot dusty. ");
	printf("If you really wanted, you could probably sleep on it.\n");
	printf("\nRest in the bed?\n");
	printf("\t1) YES\n");
	printf("\t2) NO\n");
	
	int options = 2;
	int choice = GetInput(options);

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

Input:		none

Output:		none
******************************************************************/
void GuestTable() {
	printf("Now that you are looking more closely at it... ");
	printf("The side table is still dusty.\n");
	printf("The top surface is covered in a thin layer of dust, but the small drawer on the\nfront of it still looks functional.\n");
	printf("\nDo you want to look inside?\n");
	printf("\t1) YES\n");
	printf("\t2) NO\n");

	int options = 2;
	int choice = GetInput(options);

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

Input:		none

Output:		none
******************************************************************/
void GuestDesk() {
	printf("Much like the rest of this room, the desk has a thin covering of dust atop it.\n");
	printf("It isn't that bad of a desk, really. ");
	printf("A little cleaning up and it could be\nsomething nice. ");
	printf("It has a couple of drawers you could check.\n");
	printf("Will you search the drawers?\n");
	printf("\t1) YES\n");
	printf("\t2) NO\n");

	int options = 2;
	int choice = GetInput(options);

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
	printf("There are a couple different books here. ");
	printf("Various works of fiction from what you\ncan tell. ");
	printf("One has a primarily red cover, another is mostly dark blue, the third\nis green, and the last is purple. ");
	printf("They don't seem particularily useful to you\nright now.\n");
}

/************************ GuestJar() *****************************
Purpose:	guest jar information/interaction

Input:		inv		struct*		user's inventory

Output:		none
******************************************************************/
void GuestJar(INVENTORY *inv) {
	if (HasItem(*inv, GUEST_KEY) == FALSE && HasUsedItem(*inv, GUEST_KEY) == FALSE) {
		printf("The three odd jars sit on the desk and feel a bit out of place. ");
		printf("Being closer to\nthem like this, you notice a dark shape inside of one of the jars. ");
		printf("Something\nsmall, and oddly shaped.\n");
		printf("\nBreak open the jar?\n");
		printf("\t1) YES\n");
		printf("\t2) NO\n");

		int options = 2;
		int choice = GetInput(options);

		if (choice == 1) {
			printf("You picked up the small jar with ease, the item inside rattling with a metallic\nclanging against the glass walls. ");
			printf("You smash it into the desk, stray bits of\nopaque glass flying every which way. ");
			printf("From the remains of the smashed jar, you\nfind a key.\n");
			AddItem(inv, GUEST_KEY);
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

Input:		none

Output:		none
******************************************************************/
void MasterBed() {
	printf("This bed looks a little better kept than the one in the guest room. ");
	printf("It probably\nis actively used by whoever lives here. ");
	printf("You don't really think its a good idea\nto sleep in someone's else bed. ");
	printf("But, you could still snoop around and see if\nanything is hidden under it.\n");
	printf("\nSearch the bed?\n");
	printf("\t1) YES\n");
	printf("\t2) NO\n");

	int options = 2;
	int choice = GetInput(options);

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

Input:		inv		struct*		user's inventory

Output:		none
******************************************************************/
void MasterTable(INVENTORY *inv) {
	printf("This side table appears to be a matching piece to the one in the guest room.\n");
	printf("However, this one is not as dusty. ");
	printf("You could check the drawer if you wanted.\n");
	printf("\nSearch the side table?\n");
	printf("\t1) YES\n");
	printf("\t2) NO\n");

	int options = 2;
	int choice = GetInput(options);

	if (choice == 1) {
		printf("You easily slide open the drawer. Inside, there is a key.\n");
		AddItem(inv, OUTSIDE_KEY);
	}
	else if (choice == 2) {
		printf("You decide to leave it be.\n");
	}
}

/************************* Glasses() *****************************
Purpose:	glasses information/interaction

Input:		inv		struct*		user's inventory

Output:		none
******************************************************************/
void Glasses(INVENTORY *inv) {
	printf("It seems a little strange for someone to leave these here if they aren't\nsleeping. ");
	printf("You could take them... if you really wanted.\n");
	printf("\nTake the glasses?\n");
	printf("\t1) YES\n");
	printf("\t2) NO\n");

	int options = 2;
	int choice = GetInput(options);

	if (choice = 1) {
		printf("You're not really sure why, but you take them.\n");
		AddItem(inv, GLASSES);
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

Input:		none

Output:		none
******************************************************************/
void TrashCan() {
	printf("The trash can is nearly full, you can spot many crumpled wrappers, pieces of\npaper, and other random odds and ends. ");
	printf("You could try digging through the trash\nif you really wanted to...\n");
	printf("\nSearch the trash can?\n");
	printf("\t1) YES\n");
	printf("\t2) NO\n");

	int options = 2;
	int choice = GetInput(options);

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
}

/************************* Cabinet() *****************************
Purpose:	cabinets information/interaction

Input:		none

Output:		none
******************************************************************/
void Cabinet() {
	printf("The kitchen has lots of available cabinets, but nothing particularily notable\nabout any of them. ");
	printf("Still, they could be worth searching in case of something\nuseful.");
	printf("\nSearch the cabinets?\n");
	printf("\t1) YES\n");
	printf("\t2) NO\n");

	int options = 2;
	int choice = GetInput(options);

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

Output:		none
******************************************************************/
void KitchenSink(INVENTORY *inv) {
	if (HasItem(*inv, MASTER_KEY) == FALSE && HasUsedItem(*inv, MASTER_KEY) == FALSE) {
		printf("The sink looks fine enough...  ");
		printf("But now that you're closer you notice something\ninteresting. ");
		printf("There appears to be a metal glint of something wedged in the drain.\n");
		printf("Try to get it out?\n");
		printf("\t1) YES\n");
		printf("\t2) NO\n");

		int options = 2;
		int choice = GetInput(options);

		if (choice == 1) {
			if (HasItem(*inv, TWEEZERS) == TRUE) {
				UseItem(inv, TWEEZERS);
				printf("Using the tweezers, you're able to rescue the item. It's...\nA key.\n");
				AddItem(inv, MASTER_KEY);
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

Input:		none

Output:		none
******************************************************************/
void Fridge() {
	printf("The fridge lays unadorned by any magnets or pictures. ");
	printf("Maybe there's something\ninside?\n");
	printf("\nSearch the fridge?\n");
	printf("\t1) YES\n");
	printf("\t2) NO\n");

	int options = 2;
	int choice = GetInput(options);

	if (choice == 1) {
		printf("You open the fridge door. ");
		printf("It has... Food in it. ");
		printf("But nothing useful.\n");
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

Input:		none

Output:		none
******************************************************************/
void BathroomSink() {
	printf("You could get water from this if you had something to collect it with...\n");
	printf("But you don't need to do that right now.\n");
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
void LivingTable() {
	printf("This wodden table is of about the quality you've come to expect of this house.\n");
	printf("Nice enough, but certainly not new. ");
	printf("There are books sitting on it that you\nalready saw upon entering the room, but nothing else of note.\n");
}

/************************ LivingBook() ***************************
Purpose:	living room book information/interaction

Input:		none

Output:		none
******************************************************************/
void LivingBook() {
	printf("This small stack of books doesn't have any names that jump out at you. ");
	printf("Maybe\nthey could be useful for something, but you don't know what.\n");
}

/************************ Loveseat() *****************************
Purpose:	loveseat information/interaction

Input:		none

Output:		none
******************************************************************/
void Loveseat(){
	printf("Much like the couch, there isn't much to note about this loveseat. ");
	printf("It's\nbasically just a smaller version with no one sitting on it. ");
	printf("You could search\nthe cushions if you were really so inclined.\n");
	printf("\nSearch the loveseat?\n");
	printf("\t1) YES\n");
	printf("\t2) NO\n");

	int options = 2;
	int choice = GetInput(options);

	if (choice == 1) {
		printf("Unfortunately, nothing was hidden in the cushions.\n");
	}
	else if (choice == 2) {
		printf("No need to do that.\n");
	}
}

/************************ Fireplace() ****************************
Purpose:	fireplace information/interaction

Input:		inv		struct*		user's inventory

Output:		none
******************************************************************/
void Fireplace(INVENTORY *inv) {
	printf("The fireplace is cold. ");
	if (HasItem(*inv, TWEEZERS) == TRUE && HasUsedItem(*inv, TWEEZERS) == TRUE) {
		printf("There are old ashes at the bottom, but nothing of note.\n");
		printf("Unless you want ashes for some reason.\n");
	}
	else {
		printf("Amongst the old ashes, something small and metal catches your eye. ");
		printf("Perhaps a\nkey? ");
		printf("Investigating closer, you find... Tweezers. ");
		printf("What a weird place for these\nto be.\n");
		AddItem(inv, TWEEZERS);
	}
}

/************************ Caretaker() ****************************
Purpose:	caretaker information/interaction

Input:		none

Output:		none
******************************************************************/
void Caretaker() {
	printf("The Caretaker doesn't seem to notice you at first, only looking up from their\nbook a short time after you approach. ");
	printf("They give you a curious look, smiling\nwarmly.\n");
	printf("\n\"Would you like something?\"\n");
	printf("\t1) When can I leave\n");
	printf("\t2) Nothing\n");

	int options = 2;
	int choice = GetInput(options);

	if (choice == 1) {
		printf("\"Did you... Not read my note? You CANNOT leave. ");
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