/***********************************************
Name:	Max V.
Date:	24-Jan-2023
Desc:	Basic beginnings of the text-based game,
		as required by project phase 1-2.
		I chose to not use certain elements
		(namely functions or structs) even if they
		would improve the program, as we haven't
		covered them and I wanted to be fair to
		those that wouldn't know about them yet.
************************************************/

#define TRUE	1
#define FALSE	0

#include <stdio.h>
#include <ctype.h>

int main(void) {
	int currentRoom = 0; //def switch to functions/structs for rooms later
	int userInput; //more detailed inputs made possible later
	int changeRoom = FALSE;

	do{
		switch (currentRoom) {
			case 0: //guest room (start room)
				changeRoom = FALSE;
				
				while (!changeRoom) {
					printf("\n---------------\n");
					printf("GUEST BEDROOM");
					printf("\n---------------\n");
					
					printf("This is the guest bedroom, where you woke up. There is a single person BED here, draped in\nfaded green bedsheets. The walls are a similar hue. ");
					printf("Next to the bed is a small wooden SIDE TABLE.\nA handwritten NOTE sits atop it. ");
					printf("Further in the room, to the left of the side table,\nSunlight streams in through the cracks of a boarded up bay window.\n");
					printf("A DESK lies in front of this window, with some old BOOKS sitting atop it, alongside some odd JARS.\n");
					printf("There is one door in this room. It leads to the UPPER HALLWAY.\n");

					printf("\nFrom this room, your options are:\n");
					printf("\t1) Stay here.\n");
					printf("\t2) Go to UPPER HALLWAY.\n");

					printf("Please input your answer below:\n> ");
					scanf_s("%d", &userInput);
					if (userInput == 1) {
						printf("You have chosen to stay in the room.\n");
					}
					else if (userInput == 2) {
						printf("Opening the door, you step into the hallway...\n");
						changeRoom = TRUE;
						currentRoom = 1;
					}
					else {
						printf("\nThat is not a valid option, please try again.\n");
					}
				}
				break;
			
			case 1: //upper hallway
				changeRoom = FALSE;

				while (!changeRoom) {
					printf("\n---------------\n");
					printf("UPPER HALLWAY");
					printf("\n---------------\n");
					
					printf("This upper hallways serves as a connection to both bedrooms, and the main floor of the house.\n");
					printf("There is one window here, drapes drawn shut over it. The walls are an uninteresting beige,\nadorned only with a few framed artworks.");
					printf("The worn wooden staircase leads to the LOWER HALLWAY.\nThe door to the left of the staircase leads to the MASTER BEDROOM. The one on the right leads\nto the GUEST BEDROOM.\n");

					printf("\nFrom this room, your options are:\n");
					printf("\t1) Stay here.\n");
					printf("\t2) Go to GUEST BEDROOM.\n");
					printf("\t3) Go to MASTER BEDROOM.\n");
					printf("\t4) Go to LOWER HALLWAY.\n");

					printf("Please input your answer below:\n> ");
					scanf_s("%d", &userInput);
					if (userInput == 1) {
						printf("You have chosen to stay in the room.\n");
					}
					else if (userInput == 2) {
						printf("Opening the door, you step into the guest room...\n");
						changeRoom = TRUE;
						currentRoom = 0;
					}
					else if (userInput == 3) {
						printf("Opening the door, you step into the master bedroom...\n");
						changeRoom = TRUE;
						currentRoom = 2;
					}
					else if (userInput == 4) {
						printf("Descending the stairs, you enter the lower hallway...\n");
						changeRoom = TRUE;
						currentRoom = 3;
					}
					else {
						printf("That is not a valid option, please try again.\n");
					}
				}
				break;
			
			case 2: //master bedroom
				changeRoom = FALSE;

				while (!changeRoom) {
					printf("\n---------------\n");
					printf("MASTER BEDROOM");
					printf("\n---------------\n");

					printf("The master bedroom is not particularily fancier than the guest room. Its walls are painted\na deep blue that appears to be chipping in places,");
					printf("and the bedsheets are blue flannel.\nAs with the other rooms, the lone window in this room is boarded up throughouly.\n");
					printf("There is a SIDE TABLE next to the bed. It a pair of GLASSES, a CLOCK, and a lone JAR sit atop it.\n");
					printf("The only door here leads back to the UPPER HALLWAY.\n");

					printf("\nFrom this room, your options are:\n");
					printf("\t1) Stay here.\n");
					printf("\t2) Go to UPPER HALLWAY.\n");

					printf("Please input your answer below:\n> ");
					scanf_s("%d", &userInput);
					if (userInput == 1) {
						printf("You have chosen to stay in the room.\n");
					}
					else if (userInput == 2) {
						printf("Opening the door, you step into the hallway...\n");
						changeRoom = TRUE;
						currentRoom = 1;
					}
					else {
						printf("\nThat is not a valid option, please try again.\n");
					}
				}
				break;
			
			case 3: //lower hallway
				changeRoom = FALSE;

				while (!changeRoom) {
					printf("\n---------------\n");
					printf("LOWER HALLWAY");
					printf("\n---------------\n");

					printf("This lower hallway is significantly larger than the one upstairs. ");
					printf("Directly across from\nthe bottom of the stairs is a KITCHEN, across from the kitchen is the entrance to the LIVING ROOM,\n");
					printf("and a door to the left of the staircase is a BATHROOM. Further down the hall to the right\nlies the FRONT DOOR, which leads OUTSIDE. ");
					printf("Much like the upper hall, this area is sparcely decorated.\nThere is a small TRASH CAN near the kitchen entryway, a POTTED PLANT in ");
					printf("the corner between\nthe bathroom and living room, and a shoe rack across from the front door.\n");

					printf("\nFrom this room, your options are:\n");
					printf("\t1) Stay here.\n");
					printf("\t2) Go to UPPER HALLWAY.\n");
					printf("\t3) Go to KITCHEN.\n");
					printf("\t4) Go to BATHROOM.\n");
					printf("\t5) Go to LIVING ROOM.\n");
					printf("\t6) Go to OUTSIDE.\n");

					printf("Please input your answer below:\n> ");
					scanf_s("%d", &userInput);
					if (userInput == 1) {
						printf("You have chosen to stay in the room.\n");
					}
					else if (userInput == 2) {
						printf("Ascending the stairs, you enter the upper hallway...\n");
						changeRoom = TRUE;
						currentRoom = 1;
					}
					else if (userInput == 3) {
						printf("You step into the kitchen...\n");
						changeRoom = TRUE;
						currentRoom = 4;
					}
					else if (userInput == 4) {
						printf("You step into the bathroom...\n");
						changeRoom = TRUE;
						currentRoom = 5;
					}
					else if (userInput == 5) {
						printf("You step into the living room...\n");
						changeRoom = TRUE;
						currentRoom = 6;
					}
					else if (userInput == 6) {
						printf("You step outside...\n");
						changeRoom = TRUE;
						currentRoom = 7;
					}
					else {
						printf("\nThat is not a valid option, please try again.\n");
					}
				}
				break;
			
			case 4: //kitchen
				changeRoom = FALSE;

				while (!changeRoom) {
					printf("\n---------------\n");
					printf("KITCHEN");
					printf("\n---------------\n");

					printf("The tiled flooring of the kitchen is a notably different surface than the hardwood\ncovering most of the house.");
					printf("There is an l-shaped arrangement of kitchen CABINETS here,\nboth as counter space and higher on the walls. ");
					printf("A metal pot rack hangs from the\nceiling in the middle of this room. ");
					printf("There is also, of course, a STOVE and a FRIDGE here.\n");
					printf("Although some sunlight reaches through the cracks, this window is also boarded up.\n");
					printf("The only location reachable from here is the LOWER HALLWAY.\n");

					printf("\nFrom this room, your options are:\n");
					printf("\t1) Stay here.\n");
					printf("\t2) Go to LOWER HALLWAY.\n");

					printf("Please input your answer below:\n> ");
					scanf_s("%d", &userInput);
					if (userInput == 1) {
						printf("You have chosen to stay in the room.\n");
					}
					else if (userInput == 2) {
						printf("You step into the hallway...\n");
						changeRoom = TRUE;
						currentRoom = 3;
					}
					else {
						printf("\nThat is not a valid option, please try again.\n");
					}
				}
				break;
			
			case 5: //bathroom
				changeRoom = FALSE;

				while (!changeRoom) {
					printf("\n---------------\n");
					printf("BATHROOM");
					printf("\n---------------\n");

					printf("This bathroom has seen better days. It may have a TOILET, SINK, and BATHTUB as one would expect,\n");
					printf("but it doesn't smell the best. This room makes you uneasy. You're almost hesitant to look at the\n");
					printf("cracked MIRROR hanging above the sink. Perhaps you should return to the LOWER HALLWAY.\n");

					printf("\nFrom this room, your options are:\n");
					printf("\t1) Stay here.\n");
					printf("\t2) Go to LOWER HALLWAY.\n");

					printf("Please input your answer below:\n> ");
					scanf_s("%d", &userInput);
					if (userInput == 1) {
						printf("You have chosen to stay in the room.\n");
					}
					else if (userInput == 2) {
						printf("You step into the hallway...\n");
						changeRoom = TRUE;
						currentRoom = 3;
					}
					else {
						printf("\nThat is not a valid option, please try again.\n");
					}
				}
				break;
			
			case 6: //living room
				changeRoom = FALSE;

				while (!changeRoom) {
					printf("\n---------------\n");
					printf("LIVING ROOM");
					printf("\n---------------\n");

					printf("Upon entering this room, the first thing you can see is the BACK DOOR. This also leads OUTSIDE,\n");
					printf("just like the front door. The living room itself is fairly large, probably the largest in the house.\n");
					printf("There is a pale green COUCH to the right of the back door, with a SIDE TABLE next to it, and a\nCOFFEE TABLE across from it. ");
					printf("There are some BOOKS on the coffee table, and a LOVESEAT\nfurther into the room. ");
					printf("The FIREPLACE across from the loveseat is currently cold. All windows are covered,\nas usual. ");
					printf("You get the feeling that someone is supposed to be here...\n");

					printf("\nFrom this room, your options are:\n");
					printf("\t1) Stay here.\n");
					printf("\t2) Go to LOWER HALLWAY.\n");
					printf("\t3) Go to OUTSIDE.\n");

					printf("Please input your answer below:\n> ");
					scanf_s("%d", &userInput);
					if (userInput == 1) {
						printf("You have chosen to stay in the room.\n");
					}
					else if (userInput == 2) {
						printf("You step into the hallway...\n");
						changeRoom = TRUE;
						currentRoom = 3;
					}
					else if (userInput == 3) {
						printf("You step outside...\n");
						changeRoom = TRUE;
						currentRoom = 7;
					}
					else {
						printf("\nThat is not a valid option, please try again.\n");
					}
				}
				break;
			
			case 7: //outside (win room)
				break;
			
			default:
				printf("ERROR - Invalid currentRoom value\n");
		}
	} while (currentRoom != 7);
	
	//win text
	printf("Congrats! You made it outside!\n");
	printf("\n...It's going to be more challenging in the real thing.\n");

	return 0;
}