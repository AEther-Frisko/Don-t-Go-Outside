/***********************************************
Name:	Max V.
Date:	24-Jan-2023
Desc:	Phase 1-3 of the text game project, code
		is made to be far more modular and uses
		functions. Input validation is also
		better now.
************************************************/

#include <stdio.h>

//*************FUNCTION PROTOTYPES**************
//--- USEFUL STUFF ---
int ReadInput(int input);
int GetInput();

//--- ROOMS ---
int GuestBedroom(int room);
int UpperHallway(int room);
int MasterBedroom(int room);
int LowerHallway(int room);
int Kitchen(int room);
int Bathroom(int room);
int LivingRoom(int room);
int Outside(int room);
//**********************************************

int main(void) {
	int room = 0;

	do {
		switch (room) {
		case 0:
			printf("\n---------------\n");
			printf("GUEST BEDROOM");
			printf("\n---------------\n");
			room = GuestBedroom(room);
			break;
		
		case 1:
			printf("\n---------------\n");
			printf("UPPER HALLWAY");
			printf("\n---------------\n");
			room = UpperHallway(room);
			break;
		
		case 2:
			printf("\n---------------\n");
			printf("MASTER BEDROOM");
			printf("\n---------------\n");
			room = MasterBedroom(room);
			break;
		
		case 3:
			printf("\n---------------\n");
			printf("LOWER HALLWAY");
			printf("\n---------------\n");
			room = LowerHallway(room);
			break;
		
		case 4:
			printf("\n---------------\n");
			printf("KITCHEN");
			printf("\n---------------\n");
			room = Kitchen(room);
			break;
		
		case 5:
			printf("\n---------------\n");
			printf("BATHROOM");
			printf("\n---------------\n");
			room = Bathroom(room);
			break;
		
		case 6:
			printf("\n---------------\n");
			printf("LIVING ROOM");
			printf("\n---------------\n");
			room = LivingRoom(room);
			break;
		
		case 7:
			printf("\n---------------\n");
			printf("OUTSIDE");
			printf("\n---------------\n");
			room = Outside(room);
			break;
		}
	} while (room <= 7);
	
	return 0;
}

//****************FUNCTIONS*********************
int ReadInput(int input) {
	//still doesn't work for chars because
	//everything I can find about it is beyond
	//what has been covered here yet
	//unless I want to terminate the program
	//every time someone types the wrong thing

	scanf_s("%d", &input);

	return input;
}

int GetInput() {
	int input = 0;
	
	printf("\nPlease input your answer below:\n> ");
	input = ReadInput(input);

	if (input == 1){
		printf("You have chosen to stay in the room.\n");
	}

	return input;
}

int GuestBedroom(int room) {
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

	int choice = GetInput();

	if (choice == 2) {
		printf("Opening the door, you step into the hallway...\n");
		room = 1;
	}
	else if (choice != 1){
		printf("\nThat is not a valid option, please try again.\n");
	}
	return room;
}

int UpperHallway(int room) {
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

	int choice = GetInput();

	if (choice == 2) {
		printf("Opening the door, you step into the guest room...\n");
		room = 0;
	}
	else if (choice == 3) {
		printf("Opening the door, you step into the master bedroom...\n");
		room = 2;
	}
	else if (choice == 4) {
		printf("Descending the stairs, you enter the lower hallway...\n");
		room = 3;
	}
	else if (choice != 1){
		printf("That is not a valid option, please try again.\n");
	}

	return room;
}

int MasterBedroom(int room) {
	printf("Although it's larger than the guest room, this bedroom is not much more\ndecorated. ");
	printf("The walls are a plain deep blue, chipped in places, especially\naround the boarded up window. ");
	printf("At the very least, it doesn't smell as musty as\nthe guest room. ");
	printf("The double BED has some soft-looking flannel sheets which match\nthe colour of the walls pretty well. ");
	printf("As in the other bedroom, there is a SIDE\nTABLE next to the bed. ");
	printf("A pair of GLASSES, a small CLOCK, and a lone opaque JAR\ntake up its surface. ");
	printf("The clock ticks quietly, the only obvious sound in this\nroom.\n");
	printf("\nThere is one door in this room, which leads to the UPPER HALLWAY.\n");

	printf("\nFrom this room, your options are:\n");
	printf("\t1) Stay here.\n");
	printf("\t2) Go to UPPER HALLWAY.\n");

	int choice = GetInput();

	if (choice == 2) {
		printf("Opening the door, you step into the hallway...\n");
		room = 1;
	}
	else if(choice != 1) {
		printf("\nThat is not a valid option, please try again.\n");
	}

	return room;
}

int LowerHallway(int room) {
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

	int choice = GetInput();

	if (choice == 2) {
		printf("Ascending the stairs, you enter the upper hallway...\n");
		room = 1;
	}
	else if (choice == 3) {
		printf("You step into the kitchen...\n");
		room = 4;
	}
	else if (choice == 4) {
		printf("You step into the bathroom...\n");
		room = 5;
	}
	else if (choice == 5) {
		printf("You step into the living room...\n");
		room = 6;
	}
	else if (choice == 6) {
		printf("You step outside...\n");
		room = 7;
	}
	else if (choice != 1){
		printf("\nThat is not a valid option, please try again.\n");
	}

	return room;
}

int Kitchen(int room) {
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

	int choice = GetInput();

	if (choice == 2) {
		printf("You step into the hallway...\n");
		room = 3;
	}
	else if (choice != 1){
		printf("\nThat is not a valid option, please try again.\n");
	}

	return room;
}

int Bathroom(int room) {
	printf("This bathroom has seen better days. ");
	printf("The air here feels thick, somehow different\nand worse than the musty air of the guest bedroom. ");
	printf("There is a TOILET, SINK and\nBATHTUB as one would expect from the sole bathroom of the house, but you aren't\nparticularily keen on using any of them. ");
	printf("Something about this room makes you\nuneasy. ");
	printf("Your eyes are hesitant to even wander to the cracked MIRROR hanging\nabove the sink. ");
	printf("The less time you can spend in here, the better.\n");

	printf("\nFrom this room, your options are:\n");
	printf("\t1) Stay here.\n");
	printf("\t2) Go to LOWER HALLWAY.\n");

	int choice = GetInput();

	if (choice == 2) {
		printf("You step into the hallway...\n");
		room = 3;
	}
	else if (choice != 1){
		printf("\nThat is not a valid option, please try again.\n");
	}

	return room;
}

int LivingRoom(int room) {
	printf("This room is sort of l-shaped, with a BACK DOOR right across from the entrance\ninto the room. ");
	printf("Further along the same wall as the back door, there is an alcove\nof sorts containing a pale green COUCH and a small SIDE TABLE. ");
	printf("The COFFEE TABLE\nacross from that holds a few BOOKS, and further into the room there is a\nLOVESEAT. ");
	printf("It's the same colour as the couch. ");
	printf("The FIREPLACE to the right of the\nloveseat is cold, not even any embers at the bottom.\n");
	printf("\nThe CARETAKER sits on the couch. ");
	printf("They are unremarkable in this strange sort of\nway where you can't really put your finger on what their features are. ");
	printf("They\nhave yet to pay you any mind, reading something in silence.\n");

	printf("\nFrom this room, your options are:\n");
	printf("\t1) Stay here.\n");
	printf("\t2) Go to LOWER HALLWAY.\n");
	printf("\t3) Go to OUTSIDE.\n");

	int choice = GetInput();

	if (choice == 2) {
		printf("You step into the hallway...\n");
		room = 3;
	}
	else if (choice == 3) {
		printf("You step outside...\n");
		room = 7;
	}
	else if (choice != 1){
		printf("\nThat is not a valid option, please try again.\n");
	}

	return room;
}

int Outside(int room) {
	printf("Congrats! You made it outside!\n");
	printf("\n...It's going to be more challenging in the real thing.\n");
	room = 8;
	return room;
}