//
//Name: Ethan Nicholson
//Program Name: Nightmare in Limbo

#include <iostream>
#include <string>
using namespace std;

//used to be able to tell if the game is running
//or to end the game
bool isPlaying = true;

//used to display correct endings
bool goodEnding = false;
bool lost = false;

//used to determine weather or not a room gives a loss or not.
bool mildredDead = false;

//room class
class Room {
	protected:
	        string name;
	        string descr;
	        int numDoors;
			int xCoords;
			int yCoords;
	        
	public:
		//pointers to 4 rooms (one for each possibe connection)
		Room *p[4];
		
		//allows us to initialize the name and description of rooms
		virtual void init(string n, string descript, int x, int y){
			name = n;
			descr = descript;
			xCoords = x;
			yCoords = y;
		}
		
		//used to set array of 4 pointers
		void setDoors(Room *door1, Room *door2, Room *door3, Room *door4);
		
		int getDoors(){
			return numDoors;
		}
		
		void getDoorsCoords(){
			for(int i = 0; i < numDoors; i++){
				int xDiff = xCoords - p[i]->xCoords;
				int yDiff = yCoords - p[i]->yCoords;
				
				if(yDiff < 0){
					cout<< i+1 << ". North\n";
				} else if(xDiff < 0){
					cout<< i+1 << ". East\n";
				} else if(yDiff > 0){
					cout<< i+1 << ". South\n";
				} else if(xDiff > 0){
					cout<< i+1 << ". West\n";
				} 
			}
		}
		
		//displays when entering rooms
		virtual void enterRoom(){
			cout << "\n\nEntered the " << name << "\n\n" << descr;
		}
		
		//displays when opening doors
		virtual void getBasicDescr(){
			cout << "\n\nRoom appears to be a " << name << "\n";
		}
		
		//displays description
		virtual void displayDescr(){
			cout << descr;
		}
		
		//used to desplay extra text when entering the study and mildred is dead
		void concatDescr(){
			string str = "\n  As you appoach the desk, you reconise the face to be Mildred.\n  She appears to be dead due to age.\n\n";
			descr = descr + str;
		}
};

//uses optional parameters to allow us to not use some of our 4 pointers
void Room::setDoors(Room *door1 = NULL, Room *door2 = NULL, Room *door3 = NULL, Room *door4 = NULL){
	int doors = 0;
	if(door1 == NULL){
		doors = 0;
	} else if(door2 == NULL){
		p[0] = door1;
		doors = 1;
	} else if(door3 == NULL){
		p[0] = door1;
		p[1] = door2;
		doors = 2;
	} else if(door4 == NULL){
		p[0] = door1;
		p[1] = door2;
		p[2] = door3;
		doors = 3;
	} else {
		p[0] = door1;
		p[1] = door2;
		p[2] = door3;
		p[3] = door4;
		doors = 4;
	}
	numDoors = doors;
	for(int i = doors; i < 4; i++){
		p[i] = NULL;
	}
}

class Item {

	string out;
	
	public:
		string name;
		void init(string n, string o){
			name = n;
			out = o;
		}
		
		//used when an item is used to display output
		void use(){
			cout << out;
			if(name == "Handheld Mirror"){
				goodEnding = true;
			} else if(name == "Pocket Watch"){
				mildredDead = true;
			}
		}
};

//definitions of all the items
Item mirror;
Item watch;
Item ball;
Item knife;
Item glass;

//an array of all the items the player has
Item *items[5];
//number of items the player has
int ind = 0;

//initalizes all the items
//***************spoilers ahead********************
//skip to line 161
void defineItems(){
	string use;
	use = "  Looking into your reflection in the mirror, and suddenly you feel warm\n"
	      "  Suddenly, your face becomes colorful, you realize you have your body back.\n\n";
	mirror.init("Handheld Mirror", use);
	use = "  Looking into your reflection in the ball, and suddenly you feel cold.\n"
	      "  And colder, and cooooolllder, and cccccccooooooooooollllllllddddddddddddddddddder\n"
	      "  Suddenly, everything fades to black.\n"
	      "  Apon awaking, you hold your head in pain and wish to never look at your reflection again\n"
	      "  as it might kill you for good.\n\n";
	ball.init("Cue Ball", use);
	use = "  Looking into your reflection in the watch. It appears that nothing has happened. Curious.\n\n";
	watch.init("Pocket Watch", use);
	use = "  Looking into your reflection in the knife, and suddenly you feel cold.\n"
	      "  And colder, and cooooolllder, and cccccccooooooooooollllllllddddddddddddddddddder\n"
	      "  Suddenly, everything fades to black.\n"
	      "  Apon awaking, you hold your head in pain and wish to never look at your reflection again\n"
	      "  as it might kill you for good.\n\n";
	knife.init("Shiney Knife", use);
	use = "  Looking into your reflection in the glass, and suddenly you feel cold.\n"
	      "  And colder, and cooooolllder, and cccccccooooooooooollllllllddddddddddddddddddder\n"
	      "  Suddenly, everything fades to black.\n"
	      "  Apon awaking, you hold your head in pain and wish to never look at your reflection again\n"
	      "  as it might kill you for good.\n\n";
	glass.init("Shard of Glass", use);
}
//***************spoilers over*********************


//other types of rooms
class ItemRoom: public Room {

	bool firstTime = true;
	
	public:
		Item *item;
		
		void init(string n, string descript, Item *i, int x, int y){
			name = n;
			descr = descript;
			item = i;
			xCoords = x;
			yCoords = y;
		}
		
		//gives player item
		void giveItem(){
			cout << "\n  After a search of the room, you found a item.";
			items[ind] = item;
			cout << " Item is a " << items[ind]->name;
			ind++;
		}
		
		//displayes text for entering room with item
		void enterRoom(){
			cout << "\n\n  Entered the " << name << "\n\n" << descr;
			if(firstTime){
				giveItem();
				firstTime = false;
			}
		}
};

class NpcRoom: public Room {

	string NpcTalk;
	
	public:
		void init(string n, string descript, string npc, int x, int y){
			name = n;
			descr = descript;
			NpcTalk = npc;
			xCoords = x;
			yCoords = y;
		}
		
		//displays basic descrption for rooms with npc
		void getBasicDescr(){
			cout << "\n\n  Room appears to be a " << name << ". \n";
			if(name != "Staircase") {
				cout << "  There also appears to be a ghostly figure in the room\n";
			}
		}
		
		//displays descrption for rooms with npc
		void displayDescr(){
			cout << descr;
			cout << NpcTalk;
		}
		
		//enter room with npc
		void enterRoom(){
			cout << "\n\n  Entered the " << name << "\n\n" << descr << NpcTalk;
		}
};

//definition of all the Rooms
Room medical_Exam;
NpcRoom medical_Office;
ItemRoom kitchen;
NpcRoom dinning_Room;
ItemRoom billard_Room;
ItemRoom lounge;
NpcRoom staircase;
ItemRoom library;
Room study;
ItemRoom bedroom;
Room hall;
Room outside;

//initiallizes all the rooms 
//*****************spoilers ahead******************
//skip to line 329
void defineRooms(){
	string descript;
	string npc;

	descript = "\n  You awaken to a bright light. As your vision comes back you appear to be in a medical examination room.\n"
		     "  You notice that the table you are on is covered in old blood stains. With a heavy head, you slowly get off the table.\n"
		     "  You realise that the room has one door on the front side of the table. On the other two sides,\n"
		     "  there appears to be a bunch of powertools. Nothing you would expect to see in a medical setting.\n\n";
	medical_Exam.init("Medical Examination Room", descript, 1, 0);
	medical_Exam.setDoors(&medical_Office);
	
	descript = "\n  There are two doors in this room. The room is full of desks, filing cabnets and things alike. The ghost in\n"
		   "  the center of the room is standing there giggling. As you enter the room, you step in some paper that makes\n"
		   "  a crinkling sound that alerts the ghost.\n\n";
		   
	npc = "\n  \"AHHH! You scared me there. Hehehe You must be Mildred's new experiment. I was the first one she got.\n"
		"  Been stuck here ever since... AHHH! Sorry, this place gives me a case of the creepy jeepys. Hehehe You know,\n" 
		"  I can't remember how long it's been. Oh, right!  How rude of me. The name is Giggles, and welcome to limbo!\n"
		"  Hehehe Ta-da! You're dead now; well, at least almost dead. AHHH! Did you hear that? See, the creepy jeepys!\n"
		"  Hehehe Anyway, the good news is there is a way to come back. You need to find the magic......  thingy ma jigger;\n"
		"  which, is here somewhere. Hehehe It's reflective, but that can be alot of thingy ma jiggers. That gets your body\n"
		"  back, but you also need to the exit to this place before the night is over. AHHH! Mildred is still around here\n"
		"  somewhere, and be warned, if she catches you, you will be dead, like dead dead. Hehehe I think she is trying to\n"
		"  figure out a way to cure death. AHHH! Zombies, skellies, and ghosties. AHHH! I'm a ghostie! Hehehe\"\n\n";
	medical_Office.init("Medical Office", descript, npc, 1, 1);
	medical_Office.setDoors(&kitchen, &medical_Exam);
	
	descript = "\n  There are four doors in this room. The kitchen looks like one you might find in a resturant.\n\n";
	kitchen.init("Kitchen", descript, &knife, 1, 2);
	kitchen.setDoors(&lounge, &billard_Room, &medical_Office, &dinning_Room);
	
	descript = "\n  There is one door in this room. The room gives huge man cave vibes. It even has a pool table; however, it feels unused.\n\n";
	billard_Room.init("Billard Room", descript, &ball, 2, 2);
	billard_Room.setDoors(&kitchen);
	
	descript = "\n  There are two doors in this room. The center has a massive and extremely fancy dinning table. You hear some erie\n"
		   "  music in the background. The ghost in the corner of the room is crying heavly. As you enter the room, a wooden\n"
		   "  floor board creeks alerting the ghost.\n\n";
		   
	npc = "\n  \"Waaa! Waah! HEeeey, you're new around here. Please excuse me, I didn't mean to bother anyone. You can call me\n"
	      "  Weepers. I've just been so sad after my maiden left me. I'm so maidenless, man. WAAA! Waaah! You wouldn't\n"
	      "  understand the pain. All I did was lose to her in the game CLUE, and now look at me. It's a rough life man. I don't\n"
	      "  get it. Why do maidens care if I'm \"good\" or not? WAAA! I got so good at this game man, so good in fact that I found\n"
		  "  out where Mildred is. She is always studying texts to figure out how to raise the dead. It just isn't good enough I\n"
		  "  guess. Now leave me to die in my sorrows.\"\n\n";
	dinning_Room.init("Dinning Room", descript, npc, 0, 2);
	dinning_Room.setDoors(&hall, &kitchen);
	
	descript = "\n  There are four doors in this room. This room is basically a expensive living room."
		   "  You hear some erie music in the background.\n\n";
	lounge.init("Lounge", descript, &mirror, 1, 3);
	lounge.setDoors(&library, &staircase, &kitchen, &hall);
	
	descript = "\n  As you head up the staircase you see some writing in craved wood that says \"TURN AROUND NOW! IT NEVER ENDS\"\n"
		   "  You keep walking up. At this point, it's been a full minute. \"STOP!\" You hear from behind. It's another ghost.\n\n";
		   
	npc = "\n  \"Didn't you read the message? If you go any further, you become lost for the rest of time. I lost the only friend\n"
	      "  I had in here to these stairs. Sometimes I still hear his footsteps. It's been enchanted by Mildred to keep us ghosts here.\n"
	      "  It used to lead to the outside world, but she cut the exit off. Anyway, I'm Larry. I assume you're trying to leave this place?\n"
	      "  Well, it isn't worth it. Leaving this place without your body is basically the worst thing you can do. You'll be so alone.\n"
	      "  The further you go from your body, the more you'll experience losing your soul. It's the worst way to go. Don't leave this\n"
		  "  place without your body. You need to look at your reflection through Mildred's enchanted reflection device.\n"
	      "  The only hint we have is \"I'm the bridge between planes of existance; however most of the time people just glance and stare with\n"
	      "  funny faces.\n I hope you're able to figure it out.\"\n\n";
	staircase.init("Staircase", descript, npc, 2, 3);
	staircase.setDoors(&lounge);
	
	descript = "\n  There are 4 doors in this room. At this point the erie music is very loud. This room looks like a boss fight arena, or the enterance\n"
		   "  to a very nice mansion. In fact it looks really familiar, however that memory is foggy.\n\n";
	hall.init("Hall", descript, 0, 3);
	hall.setDoors(&study, &lounge, &dinning_Room, &outside);
	
	descript = "\n  You've made outside. Congrats!\n\n";
	outside.init("Freedom (or Outside)", descript, -1, 3);
	outside.setDoors(&hall);
	
	descript = "\n  There are three doors in this room. At this point the erie music is very loud. On one side there is a window that seems to be cracked,\n"
		   "  but other than that there are a lot of books.\n\n";
	library.init("Library", descript, &glass, 1, 4);
	library.setDoors(&bedroom, &lounge, &study);
	
	descript = "\n  There are two doors in this room. You see a figure at the desk.\n\n";
	study.init("Study", descript, 0, 4);
	study.setDoors(&library, &hall);
	
	descript = "\n  There is one door in this room. The music gets a bit quieter. This must be Mildred's Room.";
	bedroom.init("Bedroom", descript, &watch, 2, 4);
	bedroom.setDoors(&library);
}
//*****************spoilers over*******************


//used for player navigation thru the game 
Room *curr;
Room *currDoor;


//useful functions for game control
void waitForPlayer();
void clearConsole();

//controls what action player performs
void getCommand();

//actions that getCommand() runs
void openDoor();
void closeDoor();
int enterDoor();
void describe();
void itemSelect();
void leave();
void quit();

//story functions
void playStartingCutScene();
void playEndingCutScene();

//main function
int main(){
	defineRooms();
	defineItems();
	curr = &medical_Exam;	//sets current room to starting postion
	playStartingCutScene();
	
	while(isPlaying){	
		getCommand(); //yes, this is the game
	}
	
	return 0;
}

//waits for player input before continuing
//used when reading is involed
void waitForPlayer(){
	char ch;
	cout << "\nPress any key and then enter to continue:";
	cin >> ch;
}

//clears the console to make things look prettier
void clearConsole(){
	#if defined _WIN32
		system("cls");
		//clrscr(); // including header file : conio.h
	#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
		system("clear");
		//std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
	#elif defined (__APPLE__)
		system("clear");
	#endif
}

//asks for an input that corresponds to an action that affects the state of the game
void getCommand(){
	int input;
	clearConsole();
	cout << "\nActions (enter number)\n1. open door (asks you to open a door and lets you get a peek inside)\n2. enter current open door\n3. re-display room description"
			"\n4. use/display item(s)\n5. quit\n\nAction: ";
	cin >> input;
	switch(input){
		case 1: openDoor(); break;
		case 2: enterDoor(); break;
		case 3: describe(); break;
		case 4: itemSelect(); break;
		case 5: quit(); break;
		default: 
			cout << "\nNot a valid input\n";
			waitForPlayer();
	}
}

//asks the player for a number that corresponds to a door that is then opened
void openDoor(){
	int input;
	clearConsole();
	cout << "There are doors to the:\n";
	curr->getDoorsCoords();
	cout << "Enter the number to the door you wish to open:";
	cin >> input;
	if(input >= 1 && input <= curr->getDoors()){
		curr->p[input-1]->getBasicDescr();
		waitForPlayer();
		currDoor = curr->p[input-1];
	} else {
		cout << "\n\nNot a valid number";
		waitForPlayer();
		openDoor();
	}
}

//enters current open door
int enterDoor(){
	clearConsole();
	curr = currDoor;
	
	if(curr == &outside){
		curr->enterRoom();
		isPlaying = false;
		playEndingCutScene();
		return 0;
	} else if(curr == &study) {
		if(!mildredDead){
			curr->enterRoom();
			lost = true;
			isPlaying = false;
			playEndingCutScene();
			return 0;
		} else {
			study.concatDescr();
			
		}
	}
	curr->enterRoom();
	waitForPlayer();
	return 0;
}

//displays Room description
void describe(){
	clearConsole();
	curr->displayDescr();
	waitForPlayer();
}

//asks the play to select an item that is then used NOT FINISHED
void itemSelect(){
	int input;
	cout << "Enter the item number you wish to use or 0 to cancel\n\n";
	for(int i = 0; i < ind; i++){
		cout << i+1 << ". " << items[i]->name << "\n";
	}
	cin >> input;
	if((input <= ind) && (input >= 0)){
		if(input != 0){
			items[input-1]->use();
			waitForPlayer();
			clearConsole();
		}
	} else {
		cout << "\n\nNot a valid number";
		waitForPlayer();
		clearConsole();
		itemSelect();
	}
}

//player quits the game and program ends
void quit(){
	isPlaying = false;
}

//*********************Spoilers from this point foward***************************
//plays dialong at the beginng of the game
void playStartingCutScene(){
	cout << "  Pitter-Patter. Pitter-Patter.\n"
		"  You've been stranded in the woods on this dark rainy night.\n"
		"  Thankfully you come across some shelter that appears to be a large manison.\n"
		"  Knock-Knock\n"
		"  ....\n"
		"  Door opens to a older looking lady. Maybe late 60s.\n";
	waitForPlayer();
	clearConsole();
	cout << "  Oh, hello there! Sorry, I would have been at the door sooner;\n"
		"  however, I wasn't expecting any guests. Anyway look at you.\n"
		"  Such a poor thing out in that rain.\n";
	waitForPlayer();
	clearConsole();
	cout << "  She takes your coat and offers you hot chocolate and a seat;\n"
		"  which, you kindly accept.\n";
	waitForPlayer();
	cout << "  There thats better isn't it.\n";
	waitForPlayer();
	cout << "  You nod.\n";
	waitForPlayer();
	cout << "  Anyways, You can call me Mildred, but I'm sorry in advance for\n"
		"  any pain you may endure during this smooth tra...\n";
	waitForPlayer();
	cout << "  Everything fades to black.\n";
	waitForPlayer();
	clearConsole();
	curr->displayDescr();
	waitForPlayer();
}

//plays endings
void playEndingCutScene(){
	if(lost){
		cout << "  You lost\n";
		waitForPlayer();
		cout << "  You walked into the room Mildred is in and was killed.\n\n"
			"  If you missed the erie music geting louder on the way to this door I can't blame you as there isn't any real music.\n"
			"  It just, \"the music is getting louder.\" which is easy to forget about.\n\n"
			"  A good tip for next time is to open all the doors before you enter a room. Side note: all the rooms next to the kitchen\n"
			"  are safe spots :)\n";
	} else if(goodEnding){
		cout << "  Good Ending\n";
		waitForPlayer();
		cout << "  You escaped the house with your body and were able to get far away from the manison.\n"
			"  Congrats!"; 
	} else{
		cout << "  Bad Ending\n";
		waitForPlayer();
		cout << "  You escaped the house without your body and died a painful death as your soul escaped your ghostly form.\n"
			"  The way you get your body back is by is using the correct item. There is a riddle on the staircase to help you.\n"
			"  Be careful tho using the wrong ones can hurt you.";
	}
}