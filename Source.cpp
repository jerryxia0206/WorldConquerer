#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <direct.h>
#include <time.h> 
#include <cstdlib> 
#include "GameStart.h"
using namespace std;


int selection_menu(string existing_character)//need to IMPLEMENT exiting game in every case
{
	cout << "-----------------------------------------" << endl;
	cout << "0.Dungeon" << endl << "1.Blacksmith" << endl << "2.Runemaster" << endl << "3.Stash" << endl;
	cout << "You can stop playing by typing 4!" << endl;
	//just a modification to see if changes are occurring on github
	cout << "Please type 0,1,2,3 or 4" << endl;
	int option;
	cin >> option;

	switch (option)
	{

		//1 = Yes, 0 = No
		case 0:
		{
			int choice;
			cout << "Are you sure you want to go to dungeon ? 1: Yes 0: No" << endl;//ask player if they wanted to go to dungeon
			cin >> choice;
			if (choice == 0)//if the choice is 0
			{
				selection_menu(existing_character);//call the function again given the options 
			}
			if (choice == 1)
			{
				dungeon_selection(existing_character);


			}


		}
		case 1:
		{
			//NEED TO IMPLEMENT
			//cout << "Are you sure you want to go to Blacksmith ? 1: Yes 0: No";
			//cin >> choice;
			//while (choice == 0)//if the choice is 0
			//{
			//	selection_menu();//call the function again given the options 
			//}
			//if (choice == 1)
			//{
			//	cout << "You are currently in the Blacksmith, what level would you like to go to ? (Alternatively you could go somewhere else by typing esc";
			//	string level;

			//}
		}
		case 2:
		{
			cout << "Are you sure you want to go to Runemaster ? 1: Yes 0: No";
		}
		case 3:
		{
			cout << "Are you sure you want to go to Stash ? 1: Yes 0: No";
		}
		case 4:
		{
			return 0;
		}

	}
	return 0;
}

string* current_stats(string existing_character)//This has been finished implementing
{//extraing stats for character as an array
	ifstream myfile;
	myfile.open(existing_character + ".txt");
	static string stats[5];
	string attack = "ATT";
	string def = "DEF";
	string agi = "AGI";
	string str = "STR";
	string dex = "DEX";
	string line = "";
	bool found[5] = { false, false, false, false, false };
	string current_attack;
	string current_def;
	string current_agi;
	string current_str;
	string current_dex;
	while (std::getline(myfile, line) && ((found[0] == false) || (found[1] == false) || (found[2] == false) || (found[3] == false) || (found[4] == false)))//if the four stats are found, therefore all will be true, and the while loop will stop, if any of the stats aren't found, we should keep running therefore we use ||
	{
		if (line.find(attack) != string::npos) //gotta watchout .find only finds the first element in the textfile that matches attack string
		{
			found[0] = true;
			current_attack = line;//assigning the line with the keyword "current_attack", instead of overwrite attack, because the if statement above 

		}
		else if (line.find(def) != string::npos) //gotta watchout .find only finds the first element in the textfile that matches attack string
		{
			found[1] = true;
			current_def = line;//assigning the line with the keyword "current_attack", instead of overwrite attack, because the if statement above 

		}
		else if (line.find(agi) != string::npos) 
		{
			found[2] = true;
			current_agi = line;
		}
		else if (line.find(str) != string::npos)
		{
			found[3] = true;
			current_str = line;
		}
		else if (line.find(dex) != string::npos)
		{
			found[4] = true;
			current_dex = line;
		}
	}
	current_attack= current_attack.substr(5, current_attack.length() - 1);//extracting current attack power
	current_def = current_def.substr(5, current_def.length() - 1);//extracting current attack power
	current_agi = current_agi.substr(5, current_agi.length() - 1);//extracting current attack power
	current_str = current_str.substr(5, current_str.length() - 1);//extracting current attack power
	current_dex= current_dex.substr(5, current_dex.length() - 1);//extracting current attack power
	stats[0] = current_attack;
	stats[1] = current_def;
	stats[2] = current_agi;
	stats[3] = current_str;
	stats[4] = current_dex;
	

	return stats;

}
int dungeon_selection(string existing_character)
{
	ifstream myfile;
	myfile.open(existing_character + ".txt");
	string line;
	string max_dungeon_level = "MAX dungeon_lvl";
	bool found = false;
	string current_max_dungeon_level;
	cout << "You are currently in the dungeon, what level would you like to go to ? (Alternatively you could go somewhere else by typing esc" << endl;
	while (std::getline(myfile, line) && !found)//implementation for finding character level
	{
		if (line.find(max_dungeon_level) != string::npos) //HERE!
		{
			found = true;

		}
		current_max_dungeon_level = line;//assigning the line with the keyword "level" 
	}
	current_max_dungeon_level = current_max_dungeon_level.substr(max_dungeon_level.length() + 3, current_max_dungeon_level.length() - 1);//taking a substring of the line with keyword max dungeon level and find max 
	//extracting current max dungeon level
	//since current_max_dungeon_level is a string, we can convert using stoi
	int current_Max_Dungeon_level = stoi(current_max_dungeon_level);
	string level_selection;
	cin >> level_selection;//PROBLEM ENCOUNTERED WITH to_string on level selection
	while (level_selection != "esc") {
		if (stoi(level_selection) > current_Max_Dungeon_level)//if selection is higher than the max dungeon level
		{
			cout << "Sorry, your current Max Dungeon Level is " << current_max_dungeon_level << ", please select a level at the same level of the Max Dungeon level or lower" << endl;
			cin >> level_selection;//allow player to select a level

		}
		if (stoi(level_selection) <= current_Max_Dungeon_level)
		{
			cout << "Are you sure you are going to level " << stoi(level_selection) << "? 1: Yes, 0: No " << endl;
			string level_confirmation;
			cin >> level_confirmation;//asking the player to confirm they want to go to this level
			if (level_confirmation == "1")//the player would like to go to this level
			{
				cout << "You are going to level" << level_selection << endl;
				//IMPLEMENT start dungeon();
			}
			else//the player would like to go to another level
			{
				string confirmation;
				cout << "Would you like to go to another level ? 1: Yes 0: No" << endl;
				cin >> confirmation;
				if (confirmation == "1")
				{
					dungeon_selection(existing_character);//redo the dialog of dungeon selection
				}
				else if (confirmation == "0")//Will take the plyaer back to the selection menu since the player does not choose to go to any level
				{
					cout << "----------------------------------------- " << endl;;
					selection_menu(existing_character);
				}

			}
		}
	}
	if (level_selection == "esc")
	{
		selection_menu(existing_character);
	}
	return 0;
}

int continue_game(string existing_character)
{
	ifstream myfile;
	myfile.open(existing_character + ".txt");
	cout << "What would you like to do today, " << existing_character << "? " << endl;
	string level = "level";//finding where the row with keyword" level 
	string line;
	string current_level;
	bool found = false;
	while (std::getline(myfile, line) && !found)//implementation for finding character level
	{
		if (line.find(level) != string::npos) //HERE!
		{
			found = true;
			current_level = line;//assigning the line with the keyword "level" 
			 
		}
	}
	myfile.close();
	current_level = current_level.substr(6, current_level.length() - 1);//taking a substring of the line with keyword level and find level number
	cout << "You are currently level " << current_level << endl;
	string* stats_character;//holds the address to the array with stats
	cout << "-----------------------------------------" << endl;
	cout << "You have the following options:" << endl;
	selection_menu(existing_character);
	

	return 0;

}
int generating(string character_name)//generating your character
{
	
	string character_save = character_name + ".txt";//creating individual character saves
	ofstream myfile;
	myfile.open(character_save, ios::app);
	cout << "Welcome to World of Madness! Here you will fight and improve yourself endlessly! " << endl;
	cout << "Choose your brave hero! " << endl;
	cout << "Here are your options:" << endl;
	string barbarian_description = "Barbarian: Brave Conqueror of the lands, they are able to wield swords, spears, axes, and maces (They have passive bonus of +50% HP/ +50% STR \n" ;
	string rogue_description = "Rogue: Brave conqueror of the undergrounds, they are able to wield bows, daggers (They have passive bonus of +50% AGI/ + 50% DEX \n" ;
	cout << barbarian_description << endl;
	cout << rogue_description << endl ;
	cout << "-----------------------------------------" << endl;

	int hero_choose;
	bool yes_no = 0;//are you sure you are choosing the hero
	//creating a function that allows input to be given if the player wanted to choose a different hero, 
	while (yes_no == 0)
	{
		cout << "Which hero are you going with? 1:Barbarian 2:Rogue" << endl;
		cin >> hero_choose;
		if (hero_choose == 1)
		{
			cout << "Are you sure you are going with Barbarian? 1:Yes 0:No";
			cin >> yes_no;
			if (yes_no == 1)
			{
				myfile << "Barbarian" << endl;
				myfile << "level 0" << endl;//defining the stats of a barbarian
				myfile << "MAX dungeon_lvl = 0" << endl;//starting character will have a MAX dungeon_level of 0
				myfile << "-----------------------------------------" << endl;
				myfile << "Currently Equipped:" << endl;
				myfile << "Weapon: None" << endl;
				myfile << "Helmet: None" << endl;
				myfile << "Armor: None" << endl;
				myfile << "Pants: None" << endl;
				myfile << "Jewelry: None" << endl;
				myfile << "Gloves: None" << endl;
				myfile << "-----------------------------------------" << endl;
				myfile << "ATT: 0" << endl;
				myfile << "DEF: 1" << endl;
				myfile << "AGI: 1" << endl;
				myfile << "STR: 3" << endl;
				myfile << "DEX: 1" << endl;
				myfile << "-----------------------------------------" << endl;
				myfile << "AGI Growth: " << to_string(40 + rand() % 15) << "%" << endl;
				myfile << "STR Growth: " << to_string(90 + rand() % 15) << "%" << endl;
				myfile << "DEX Growth: " << to_string(40 + rand() % 15) << "%" << endl;
				myfile << "-----------------------------------------" << endl;
				myfile.close();
				string character_inventory = character_name + "_inventory.txt";
				myfile.open(character_inventory,ios::app);
				srand(time(0));//generating a random seed for rand, probably should create a data base for a lot of variety of weapons and armors....
				myfile << "wooden sword" << " ATT: " << to_string(3 + rand() % 3) << " | " << " STR: " << to_string(2 + rand() % 3) << endl;//generating random stats for equipment
				myfile << "wooden helmet" << " HP: " << to_string(20 + rand() % 3) << endl;
				myfile << "wooden pants" << " DEF: " << to_string( 3 + rand() % 3) << endl;
				myfile << "wooden armor" << " HP: " << to_string(20 + rand() % 3) << "|" << " DEF: " << to_string( 6 + rand() % 3) << endl;
				myfile << "wooden gloves" << " HP: " << to_string(20 + rand() % 3) << "|" << " AGI: " << to_string(1+ rand() % 3 ) << " | " << " STR: " << to_string(3 + rand() %3) << endl;
				myfile.close();
				string character_town = character_name + "_town.txt";
				myfile.open(character_town, ios::app);
				myfile << "0.Dungeon" << endl;
				myfile << "1.Blacksmith" << endl;
				myfile << "2.Runemaster" << endl;
				myfile << "3.Stash" << endl;
				myfile.close();
				//gamegenerating();
				continue_game(character_name);

			}
		}
		else if (hero_choose == 2)
		{
			cout << "Are you sure you are going with Rogue? 1: Yes 0: No " << endl;
			cin >> yes_no;
			if (yes_no == 1)
			{
				myfile << "Rogue" << endl;
				myfile << "level 0" << endl;
				//gamegenerating();


			}
		}
		else
		{
			cout << "Please put a valid input!" << endl;//any other option other than 1 or 2
			yes_no = 0;
		}

	}
	return 0;
}
bool find_charactername(string character_name)
{
		ifstream  myfile("Save.txt");
		string line;

		bool found = false;
		while (std::getline(myfile, line) && !found)
		{
			if (line.find(character_name) != string::npos) //HERE!
			{
				found = true;
			}
		}
		return found;
}


int begin_game()//need to implement if a character with the same name as been found, we need to choose a different name
{
	cout << "Welcome to Dungeon Conqueror!" << endl;
	bool creating_new_character = 0;//determine whether player wanted to create new character
	cout << "Would you like to play from a previous save? 1: Yes 0: No " << endl;//if the player have played before or havent played before we provide options
	bool play = 0;
	cin >> play;
	if (play == 1) {
		cout << "What character would you like to play? " << endl;//loading save
		ifstream  myfile("Save.txt");
		string line;
		string existing_character;//states which existing character should be played
		while (!myfile.eof())//basically runs until endoffile thus eof, outputs on console which characters are available
		{
			getline(myfile, line);
			cout << "" << line << endl;
		}
		cin >> existing_character;
		cout << "Generating dungeons for " << existing_character << endl;//continue playing the saved character
		cout << "-----------------------------------------" << endl;
		continue_game(existing_character);
	}

	if (play == 0)
	{
		cout << "Would you like to make a new character? 1: Yes 0: No" << endl;//ask if the player would like to make a new character
		cin >> creating_new_character;

	}
	if (creating_new_character == 1)
	{
		ofstream myfile;
		myfile.open("Save.txt", ios::app);
		string charactername;
		cout << "Enter your character name! " << endl;//enter your character name
		getline(cin.ignore(100, '\n'), charactername);
		if (find_charactername(charactername) == false)
		{
			cout << "You character name is " << charactername << endl;
			bool Yes_No;
			cout << "Are you sure this is your name? 1: Yes 0: No" << endl;
			cin >> Yes_No;
			while (Yes_No == 0)
			{
				int length_charactername = int(charactername.length()) - 1;//find length of the charactername
				cout << "Reenter your character name!" << endl;
				getline(cin.ignore(length_charactername, '\n'), charactername);//taking your input as character name, ignore get rid of the current input
				cout << "You character name is " << charactername << endl;//output your character name
				cout << "Are you sure this is your name? 1: Yes 0: No" << endl;//are you sure you are going with your name
				cin >> Yes_No;//take your input and if no reenter your name

			}
			myfile << charactername << std::endl;//only add character name if it is not in the save file
			myfile.close();
			generating(charactername);
		}
		else {
			cout << "A character with similar name has been found";
			//Would you like to use a different name? IMPLEMENTATION
		}
	}
	return 0;
}


int main() {

	begin_game();

}
