#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <direct.h>
#include <time.h> 
#include <cstdlib> 
#include <cstdio>
#include "GameStart.h"
#include <windows.h> 
using namespace std;

void loot_generate_stats(string existing_character, int level_selected, int left_over_rune_powder, string rarity, string type, bool crafting)//it is also used for crafting
{
	//randomizes the loot stats based on level_selected and type and rarity
	float rune_stat{};
	float* chaos_stats = new float [4] {};
	srand(time(0) + rand());
	if (rarity == "common")
	{
		if (type == "HP")//depeneding on different types of runes, there will be different stats
		{
			rune_stat = 5.0 + level_selected / 3.0 + (float(rand()) / float(RAND_MAX)) * level_selected / 10.0;
		}
		else if (type == "Str" || type == "Agi" || type == "Dex")
		{
			rune_stat = 40.0 + level_selected * 4.0 + (float(rand()) / float(RAND_MAX)) * level_selected / 1.5;
		}
		else if (type == "Chaos")
		{
			chaos_stats[0] = 2.0 + level_selected / 6.0 + (float(rand()) / float(RAND_MAX)) * level_selected / 25.0;//HP
			chaos_stats[1] = 25.0 + level_selected * 2.5 + (float(rand()) / float(RAND_MAX)) * level_selected / 3;//AGI
			chaos_stats[2] = 25.0 + level_selected * 2.5 + (float(rand()) / float(RAND_MAX)) * level_selected / 3;//STR
			chaos_stats[3] = 25.0 + level_selected * 2.5 + (float(rand()) / float(RAND_MAX)) * level_selected / 3;//DEX
		}
	}
	else if (rarity == "magic")
	{
		if (type == "HP")//depeneding on different types of runes, there will be different stats
		{
			rune_stat = 20 + level_selected / 1.0 + (float(rand()) / float(RAND_MAX)) * level_selected / 3.0;
		}
		else if (type == "Str" || type == "Agi" || type == "Dex")
		{
			rune_stat = 190.0 + level_selected * 6.0 + (float(rand()) / float(RAND_MAX)) * level_selected / 0.3;
		}
		else if (type == "Chaos")
		{
			chaos_stats[0] = 10.0 + level_selected / 2.0 + (float(rand()) / float(RAND_MAX)) * level_selected / 8.33;//HP
			chaos_stats[1] = 150.0 + level_selected * 4.8 + (float(rand()) / float(RAND_MAX)) * level_selected;//AGI
			chaos_stats[2] = 150.0 + level_selected * 4.8 + (float(rand()) / float(RAND_MAX)) * level_selected;//STR
			chaos_stats[3] = 150.0 + level_selected * 4.8 + (float(rand()) / float(RAND_MAX)) * level_selected;//DEX
		}
	}
	else if (rarity == "rare")
	{
		if (type == "HP")//depeneding on different types of runes, there will be different stats
		{
			rune_stat = 75.0 + level_selected * 1.20 + (float(rand()) / float(RAND_MAX)) * level_selected * 1.25;
		}
		else if (type == "Str" || type == "Agi" || type == "Dex")
		{
			rune_stat = 680.0 + level_selected * 9.0 + (float(rand()) / float(RAND_MAX)) * level_selected * 1.20;
		}
		else if (type == "Chaos")
		{
			chaos_stats[0] = 58.0 + level_selected / 0.6 + (float(rand()) / float(RAND_MAX)) * level_selected / 2.33;//HP
			chaos_stats[1] = 550.0 + level_selected * 7.78 + (float(rand()) / float(RAND_MAX)) * level_selected * 2.55;//AGI
			chaos_stats[2] = 550.0 + level_selected * 7.78 + (float(rand()) / float(RAND_MAX)) * level_selected * 2.55;//STR
			chaos_stats[3] = 550.0 + level_selected * 7.78 + (float(rand()) / float(RAND_MAX)) * level_selected * 2.55;//DEX
		}
	}
	if(crafting == false)
	{
		ofstream myfile;
		myfile.open("Characters/" + existing_character + "_stash.txt", ios::app);
		if (type == "HP")
		{
			myfile << "Level: " << level_selected << "," << "Rarity: " << rarity << "," << "Type: " << type << "," << "Stats: " << rune_stat << "\n";
		}
		else if (type == "Str" || type == "Agi" || type == "Dex")
		{
			myfile << "Level: " << level_selected << "," << "Rarity: " << rarity << "," << "Type: " << type << "," << "Stats: " << rune_stat << "%" << "\n";
		}
		else if (type == "Chaos")
		{
			myfile << "Level: " << level_selected << "," << "Rarity: " << rarity << "," << "Type: " << type << "," << "HP: " << chaos_stats[0] << "," << "AGI: " << chaos_stats[1] << "%" << "," << "STR: " << chaos_stats[2] << "%" << "," << "DEX: " << chaos_stats[3] << "%" << "\n";
		}
		myfile.close();
		delete[] chaos_stats;
	}
	else
	{
		ofstream myfile;
		string new_stash_file_name = "Characters/" + existing_character + "_new_stash.txt";
		myfile.open(new_stash_file_name, ios::app);//open the new stash file for editing
		myfile << "Rune Powder: " << left_over_rune_powder << "\n";
		ifstream old_stash_file;//open the old stash file for reading
		string old_stash_file_name = "Characters/" + existing_character + "_stash.txt";
		old_stash_file.open(old_stash_file_name);//open the old stash file for writing the previous runes into the new stash file
		int counter = 1;
		string rune;
		while (getline(old_stash_file, rune))//will read every line and store them 
		{
			if (counter != 1)//we do not want the rune powder information from before crafting added into the new file
			{
				counter++;
				myfile << rune << "\n";

			}
			else
			{
				counter++;
			}
		}
		old_stash_file.close();
		if (type == "HP")
		{
			myfile << "Level: " << level_selected << "," << "Rarity: " << rarity << "," << "Type: " << type << "," << "Stats: " << rune_stat << "\n";
		}
		else if (type == "Str" || type == "Agi" || type == "Dex")
		{
			myfile << "Level: " << level_selected << "," << "Rarity: " << rarity << "," << "Type: " << type << "," << "Stats: " << rune_stat << "%" << "\n";
		}
		else if (type == "Chaos")
		{
			myfile << "Level: " << level_selected << "," << "Rarity: " << rarity << "," << "Type: " << type << "," << "HP: " << chaos_stats[0] << "," << "AGI: " << chaos_stats[1] << "%" << "," << "STR: " << chaos_stats[2] << "%" << "," << "DEX: " << chaos_stats[3] << "%" << "\n";
		}
		myfile.close();
		remove(old_stash_file_name.c_str());//removing the old stash file
		rename(new_stash_file_name.c_str(), old_stash_file_name.c_str());//renaming the new stash file
		delete[] chaos_stats;
	}
	return;
	
}

bool drop_or_not(int level_selected)
{
	//this function determines whether or not the loot will drop based on current dungeon level
	float drop_rate;
	bool drop_or_not = false;
	if (level_selected <= 150)//determining the different drop rates in different difficulties
	{
		drop_rate = 0.10 + level_selected / 500.0;
	}
	else if (150 < level_selected <= 450)
	{
		drop_rate = 0.05 + level_selected / 2250;
	}
	else if (450 < level_selected <= 900)
	{
		drop_rate = 0.05 + level_selected / 9000;
	}
	else if (900 < level_selected <= 1800)
	{
		drop_rate = level_selected / 18000;
	}
	Sleep(1000);
	srand(time(0) + rand());
	float holder_for_possibilty = float(rand()) / float(RAND_MAX);
	if (holder_for_possibilty < drop_rate)//check if the randomizer is below current drop rate
	{
		drop_or_not = true;
	}
	return drop_or_not;
}

void drop_loot(string existing_character, int level_selected)
{
	//generate loot depending on level_selected
	//drop_or_not(leve_selected);
	if(drop_or_not(level_selected) == true)
	{
		Sleep(1000);
		srand(time(0) + rand());
		float loot_rarity = float(rand()) / float(RAND_MAX);//a dice roll determining the loot rarity
		loot* received_loot = new loot(loot_rarity, level_selected);
		received_loot->determine_loot_type();
		cout << received_loot->loot_type << "\n";
		cout << received_loot->rarity << "\n";
		if(read_number_of_runes_in_stash(existing_character) + 1 <= 5)
		{
			loot_generate_stats(existing_character, level_selected, 0, received_loot->rarity, received_loot->loot_type, false);//we are not crafting in this case, therefore we can just set left-over rune-powder to whatever
		}
		else
		{
			cout << "Your stash cannot have any more runes, please go salvage at the runemaster!" << "\n";
			loot_generate_stats(existing_character, level_selected, 0, received_loot->rarity, received_loot->loot_type, false);

		}
		delete received_loot;
	}
	return;
	//loot_stats(existing_character, level_selected, received_loot->rarity, received_loot->loot_type);
	//generate loot stats
}

//rune functions including rune_master, salvage, powder calculation, craft cost
void salvage_rune(string existing_character)//gives the amount of rune powder back to player dependent on the rune salvaging
{
	cout << "Opening Stash..." << "\n";
	if (read_number_of_runes_in_stash(existing_character) != 0)//check if your stash is empty
	{
		Sleep(1000);
		stash(existing_character);//display the current stashed runes to player
		
		cout << "Please select a rune that you would like to salvage (1,2,3,4,5) or esc to go back to main menu" << "\n";
		string rune;//the user would enter a number which represent the rune to be salvaged
		cin >> rune;
		if (rune != "esc")
		{
			if (1 <= stoi(rune) < 6)//if the input rune is within 1 and 5
			{
				int choice_of_rune = stoi(rune);//the rune we want to salvage but it will be a int type
				float* current_character_stats = current_stats(existing_character);
				float current_rune_powder = current_character_stats[10];//extract current rune_powder
				ifstream old_stash_file;//for reading a textfile
				ofstream newfile;//for writing to a textfile
				string original_character_stash_file = "Characters/" + existing_character + "_stash.txt";
				string new_character_stash_file = "Characters/" + existing_character + "_new_stash.txt";

				//find the amount of rune powder by calling the extract rune information, it might be confusing but right now extract rune information return rune powder from salvaging 
				int rune_powder_gained = extract_rune_information(existing_character, choice_of_rune);
				old_stash_file.open(original_character_stash_file);//we would open the original stash file for reading
				newfile.open(new_character_stash_file);// open a new stash file for writing
				string unsalvaged_rune;//this string will store the lines containing the unsalvaged runes 
				int counter = 0;//find the line in th textfile which corresponds to rune we want to salvage
				while (!old_stash_file.eof())//run until we reached the rune which is counted by number
				{
					getline(old_stash_file, unsalvaged_rune);
					if (counter != choice_of_rune && !unsalvaged_rune.empty())//if the current rune isn't the rune we want to salvage, we will add the information of the unsalvaged runes into the new file
					{
						if (counter == 0)//to account for the first line which contains the amount of rune powder
						{
							newfile << "Rune Powder: " << current_rune_powder + rune_powder_gained << "\n";
							counter++;// need to add rune powder calculate with extraction of rune rarity and rune level
						}
						else//not the first line
						{
							newfile << unsalvaged_rune << "\n";//the runes that is not salvaged will be added to new file
							counter++;
						}
					}
					else//if the rune is the one we want to salvage, don't write the line to the new file, and add to counter so we can keep writing the rest of the stash file to the new file
					{
						counter++;
					}
				}
				cout << "You have successfully salvaged your rune, you have gained " << rune_powder_gained << " rune powder" << "\n";
				newfile.close();
				old_stash_file.close();
				remove(original_character_stash_file.c_str());
				rename(new_character_stash_file.c_str(), original_character_stash_file.c_str());
				return selection_menu(existing_character);
			}
			else
			{
				cout << "Please enter a valid input for rune salvage, 1~5" << "\n";
				return salvage_rune(existing_character);
			}
		}
		else
		{
			return selection_menu(existing_character);
		}
		
	}
	else
	{
		cout << "Your stash is empty!" << "\n";
		return selection_menu(existing_character);
	}
	
	//}
}

int extract_rune_information(string existing_character, int rune)//returns the amount of rune powder gained after salvaging
{

	//utilizing the code in the salvage rune, we would extract the line containing the salvage rune
	ifstream myfile; //for reading the textfile
	string original_character_stash_file = "Characters/" + existing_character + "_stash.txt";
	int counter = 0;//for finding the line containing the rune that we want to salvage
	string salvaged_rune;//storing the salvaged rune info
	myfile.open(original_character_stash_file);//open stash file for reading
	while (!myfile.eof() && counter != rune + 1)//we are trying to find the rune we are salvaging
	{
		getline(myfile, salvaged_rune);
		counter++;
	}
	//now we have the salvaged rune information

	//NEED To implement rune information extraction for calculation of rune powder
	myfile.close();
	int first_delimiter = salvaged_rune.find(",");//find the first comma
	int level_found_rune = stoi(salvaged_rune.substr(7, first_delimiter - 7));
	string for_finding_next_delimiter= salvaged_rune.substr(first_delimiter + 1,string::npos);
	int second_delimiter = for_finding_next_delimiter.find(",");//finding the next comma
	string rarity_of_rune = for_finding_next_delimiter.substr(8, second_delimiter - 8);
	return rune_powder_calculate(rarity_of_rune, level_found_rune, false);
	
}

string* extract_rune_stats(string rune)
{
	//because there may be different rarities such as rare and magic, therefore the index at which the occurrence of the string "Type" may be different thus we must get each occurrence of delimiter
	static string rune_stats[4]{};//first stats is type, second type is dex, third stat is agi, fourth stat is str. fifth stat is hp
	int first_occurrence_comma = rune.find(",");
	int second_occurrence_comma = rune.find(",", first_occurrence_comma + 1);
	int third_occurrence_comma = rune.find(",", second_occurrence_comma + 1);
	string type = rune.substr(second_occurrence_comma + 7, third_occurrence_comma - second_occurrence_comma - 7);
	if (type == "Dex")//for each type we make sure that the other stats that aren't related to the rune type are 0, chaos is an exception
	{
		string stats = rune.substr(third_occurrence_comma + 8, rune.length() - third_occurrence_comma - 9);
		rune_stats[0] = "0";
		rune_stats[1] = "0";
		rune_stats[2] = stats;
		rune_stats[3] = "0";
	}
	else if (type == "Agi")
	{
		string stats = rune.substr(third_occurrence_comma + 8, rune.length() - third_occurrence_comma - 9);
		rune_stats[0] = stats;
		rune_stats[1] = "0";
		rune_stats[2] = "0";
		rune_stats[3] = "0";
	}
	else if (type == "Str")
	{
		string stats = rune.substr(third_occurrence_comma + 8, rune.length() - third_occurrence_comma - 9);
		rune_stats[0] = "0";
		rune_stats[1] = stats;
		rune_stats[2] = "0";
		rune_stats[3] = "0";
	}
	else if (type == "HP")
	{
		string stats = rune.substr(third_occurrence_comma + 8, rune.length() - third_occurrence_comma - 8);
		rune_stats[0] = "0";
		rune_stats[1] = "0";
		rune_stats[2] = "0";
		rune_stats[3] = stats;
	}
	else if (type == "Chaos")
	{
		int fourth_occurrence_comma = rune.find(",", third_occurrence_comma + 1);
		string hp = rune.substr(third_occurrence_comma + 5, fourth_occurrence_comma - third_occurrence_comma - 5);
		int fifth_occurrence_comma = rune.find(",", fourth_occurrence_comma + 1);
		string agi = rune.substr(fourth_occurrence_comma + 6, fifth_occurrence_comma - fourth_occurrence_comma - 7);
		int sixth_occurrence_comma = rune.find(",", fifth_occurrence_comma + 1);
		string str = rune.substr(fifth_occurrence_comma + 6, sixth_occurrence_comma - fifth_occurrence_comma - 7);
		int seventh_occurrence_comma = rune.find(",", sixth_occurrence_comma + 1);
		string dex = rune.substr(sixth_occurrence_comma + 6, seventh_occurrence_comma - sixth_occurrence_comma - 7);
		rune_stats[0] = agi;
		rune_stats[1] = str;
		rune_stats[2] = dex;
		rune_stats[3] = hp;
	}
	return rune_stats;
}

int rune_powder_calculate(string rune_rarity, int rune_level, bool crafting)//if player is crafting runes it will cost a lot more rune powder than receiving rune powder from salvaging
{
	int rune_powder_price{};//subject to change, this is just how many times is the price of crafting comparing to salvaging
	if (crafting == true)//if we are crafting
	{
		rune_powder_price = 5;
	}
	else
	{
		rune_powder_price = 1;
	}

	if (rune_rarity == "common")
	{
		return rune_level * rune_powder_price * 2;
	}
	else if (rune_rarity == "magic")
	{
		return rune_level * rune_powder_price * 5;
	}
	else if (rune_rarity == "rare")
	{
		return rune_level * rune_powder_price * 40;
	}
	else if (rune_rarity == "unique")
	{
		return rune_level * rune_powder_price * 500;
	}
	else if (rune_rarity == "double unique")
	{
		return rune_level * rune_powder_price * 7000;
	}
	else if (rune_rarity == "celestial")
	{
		return rune_level * rune_powder_price * 175000;
	}
	else if (rune_rarity == "double celestial")
	{
		return rune_level * rune_powder_price * 7875000;
	}
}

void rune_master(string exising_character, int maximum_dungeon_level)
{
	float* character_stats = current_stats(exising_character);
	int current_rune_powder = character_stats[10];
	bool craftable[4] = { false };//this array is created to see if you are able to craft each rarity dependent on your maximum_dungeon_level
	int rune_master_option;
	cout << "You have 3 options: 1.Crafting 2.Salvaging 3.Leaving" << "\n";
	cin >> rune_master_option;
	if(rune_master_option == 1)
	{
		if (150 <= maximum_dungeon_level)
		{
			cout << "The best runes you can craft are unique!" << "\n";
			craftable[0] = true;
		}
		else if (450 <= maximum_dungeon_level)
		{
			cout << "The best runes you can craft are double unique!" << "\n";
			craftable[1] = true;
		}
		else if (900 <= maximum_dungeon_level)
		{
			cout << "The best runes you can craft are celestial" << "\n";
			craftable[2] = true;
		}
		else if (1800 <= maximum_dungeon_level)
		{
			cout << "The best runes you can craft are double celestial" << "\n";
			craftable[3] = true;
		}
		else
		{
			cout << "The best runes you can craft are rare" << "\n";
		}
		cout << "Please write what rarity what you like to craft? (rare, unique, double unique, celestial, double celestial) or 0 to exit crafting" << "\n";
		string rarity;
		cin >> rarity;
		int rune_craft_level;
		if (rarity == "rare" || rarity == "magic" || rarity == "common")
		{
			cout << "What level of rune would you like to craft (based on your current maximum dungeon level)? or 0 to exit" << "\n";
			cin >> rune_craft_level;
			while (rune_craft_level > maximum_dungeon_level ||  rune_craft_level < 0)//while the user input is larger than our maximum dungeon level, we shall keep the user to enter an appropriate level between maximum dungeon level and 0
			{
				cout << "Please select a level that is below or equal to your maximum dungeon level (Max Dungeon Level: " << maximum_dungeon_level << " ) or 0 to exit crafting" << "\n";
				cin >> rune_craft_level;

			}
			if(rune_craft_level != 0)//if the user didn't want to exit rune master
			{
				if (rune_powder_calculate(rarity, rune_craft_level, true) <= current_rune_powder)//if we do possess enough rune powder
				{
					cout << "It will cost " << rune_powder_calculate(rarity, rune_craft_level, true) << "rune powder" << "\n";
					
					cout << "Please choose the type of rune you would like to craft: Agi, Str, Dex, HP" << "\n";
					string type_of_rune;
					cin >> type_of_rune;
					while (type_of_rune != "Agi" && type_of_rune != "Str" && type_of_rune != "Dex" && type_of_rune != "HP" && type_of_rune != "0")//as long as the user doesn't put a valid input that is either types or a 0 
					{
						cout << "Please select a valid type of rune or press 0 to exit crafting" << "\n";
						cin >> type_of_rune;

					}
					if (type_of_rune == "0")
					{
						return selection_menu(exising_character);
					}
					else
					{
						int left_over_rune_powder = current_rune_powder - rune_powder_calculate(rarity, rune_craft_level, true);//find the leftover rune powder after crafting
						loot_generate_stats(exising_character, rune_craft_level, left_over_rune_powder, rarity, type_of_rune, true);//adding rune to stash but this time we are adding because crafted
						//need to implement changes to stash file because we have crafted a rune therefore the current rune powder amount must change
						return selection_menu(exising_character);
					}
					
					
				}
				else //if we do not possess enough rune powder
				{

					cout << "You do not have enough rune powder" << "\n";
					cout << "It will cost " << rune_powder_calculate(rarity, rune_craft_level, true) << " rune powder" << "\n";
					return selection_menu(exising_character);
				}
			}
			else
			{
				return selection_menu(exising_character);
			}
			//need to implement crafting cost and if the rune the player is trying to craft is beyond their current rune powder count, we cannot craft
			

		}
		else if (rarity == "unique")
		{
			if (craftable[0] == true)
			{
				cout << "You can craft unique" << "\n";
			}
			else
			{
				cout << "You can't craft unique yet, you haven't reached the dungeon level" << "\n";
			}
		}
		
	}
	else if (rune_master_option == 2)
	{
		return salvage_rune(exising_character);
		
	}
	else if (rune_master_option == 3)
	{
		return selection_menu(exising_character);
	}
}
//character stash 
void stash(string existing_character)//it is completed
{
	cout << "Displaying current stash" << "\n";
	int display_only_runes_not_rune_powder = 0;
	ifstream myfile;
	myfile.open("Characters/" + existing_character + "_stash.txt");
	string line;
	while (!myfile.eof())
	{
		display_only_runes_not_rune_powder++;//line one is not included
		getline(myfile, line);//flushes out the current line
		if (display_only_runes_not_rune_powder >= 2 && !line.empty())
		{
			cout << line << "\n";
		}
	}
	myfile.close();
	cout << "-----------------------------------------" << "\n";
	return;
}
//character equipped functions
void display_currently_equipped(string existing_character)
{
	cout << "Currently Equipped:" << "\n";//display currently equipped runes
	string currently_equipped_runes;
	ifstream read_current_equipped_runes;
	string current_equipped_runes_file = "Characters/" + existing_character + "_currently_equipped_runes.txt";
	read_current_equipped_runes.open(current_equipped_runes_file);
	while (getline(read_current_equipped_runes, currently_equipped_runes))//output every runes currenly the player is equipped by reading everything in the equipped file
	{
		cout << currently_equipped_runes << "\n";
	}
	read_current_equipped_runes.close();
	return;
}

void equipping_runes(string existing_character)//this function gives the options to equip, unequip, change runes
{
	cout << "What would you like to do today? 1.Equip runes 2.Unequip runes 3.Change runes 4.Exit" << "\n";
	int options;
	cin >> options;
	switch (options)
	{
	case 1://equipping rune
	{
		
		if (read_number_of_runes_equipped(existing_character) < 5)
		{
			if (read_number_of_runes_in_stash(existing_character) > 0)
			{
				display_currently_equipped(existing_character);
				cout << "-----------------------------------------" << "\n";
				stash(existing_character);//display the current stash
				int rune_option;
				cout << "Which rune would you like to equip ? (Choose 1,2,3,4,5 or 0 to exit)" << "\n";
				cin >> rune_option;
				while (rune_option > 5 || rune_option < 0)
				{
					cout << "This is not a valid option, please enter 1,2,3,4,5 or 0 to exit" << "\n";
					cin >> rune_option;
				}
				if (rune_option != 0)
				{
					int counter = 0;
					float* current_character_stats = current_stats(existing_character);
					float current_rune_powder = current_character_stats[10];//extract current rune_powder

					ifstream read_current_stash;
					ofstream write_to_current_equipped;
					ofstream the_not_equipped_runes;
					string old_stash_file = "Characters/" + existing_character + "_stash.txt";
					string new_stash_file = "Characters/" + existing_character + "_new_stash.txt";
					string current_equipped_runes_file = "Characters/" + existing_character + "_currently_equipped_runes.txt";
					read_current_stash.open(old_stash_file);//we have to add the rune we want to equip to the current_equipped file
					string rune_to_equip;
					write_to_current_equipped.open(current_equipped_runes_file, ios::app); //we want to add the rune we are equipping to the currently equipped
					the_not_equipped_runes.open(new_stash_file);
					while (getline(read_current_stash, rune_to_equip))//reading the stash file to find the rune we want to equip
					{
						if (counter == rune_option)//for the rune we are equipping
						{
							write_to_current_equipped << rune_to_equip << "\n";//if the line containing the string of the rune we want to equip we write it to the currently equipped
							counter++;
						}
						else if (counter == 0)
						{
							the_not_equipped_runes << "Rune Powder: " << current_rune_powder << "\n";
							counter++;
						}
						else
						{
							the_not_equipped_runes << rune_to_equip << "\n";
							counter++;
						}
					}
					read_current_stash.close();
					write_to_current_equipped.close();
					//now we have added the non-equipped runes into the new stash file
					the_not_equipped_runes.close();
					remove(old_stash_file.c_str());
					rename(new_stash_file.c_str(), old_stash_file.c_str());
					//now we have finished equipping and removing the rune from the stash
					return selection_menu(existing_character);

				}
				else
				{
					return selection_menu(existing_character);
				}
			}
			else
			{
				cout << "Your stash is currently empty!" << "\n";
				return selection_menu(existing_character);
			}
		}
		else
		{
			cout << "You currently cannot equip any more runes!" << "\n";
			return selection_menu(existing_character);
		}
		
	}
	case 2://for unequipping runes
	{
		//if the character is not equipping any runes, we can not unequip runes
		if (read_number_of_runes_equipped(existing_character) > 0)
		{
			if (read_number_of_runes_in_stash(existing_character) < 5)// if the number of runes in the stash is less than 5
			{
				display_currently_equipped(existing_character);
				cout << "-----------------------------------------" << "\n";
				stash(existing_character);
				cout << "Which rune would you like to unequip? 1,2,3,4,5 or press 0 to exit" << "\n";
				//read_old_currently_equipped.open()
				int rune_to_unequip;
				cin >> rune_to_unequip;
				while (rune_to_unequip > read_number_of_runes_equipped(existing_character) || rune_to_unequip < 0)//if the player enters an option that is more than the number of runes they are currently wearing
				{
					cout << "This is not a valid option, please enter 1,2,3,4,5 or 0 to exit" << "\n";
					cin >> rune_to_unequip;
				}
				if (rune_to_unequip != 0)
				{
					string new_currently_equipped = "Characters/" + existing_character + "_new_currently_equipped_runes.txt";
					string old_currently_equipped = "Characters/" + existing_character + "_currently_equipped_runes.txt";
					string current_stash = "Characters/" + existing_character + "_stash.txt";
					ofstream write_current_stash;//for writing to the current stash
					ifstream read_old_currently_equipped;//for reading from the currently equipped
					ofstream write_new_currently_equipped;//for writing to the new currently equipped
					write_current_stash.open(current_stash,ios::app);//append the rune unequipped to the stash
					read_old_currently_equipped.open(old_currently_equipped);
					write_new_currently_equipped.open(new_currently_equipped, ios::app);//append the runes that are not unequipped to the new equip file
					int counter = 1;//for counter in reading the currently equipped runes
					string rune_equipped;
					//read the currently equipped runes and add the runes that are not being unequipped into the new equipped file
					while(getline(read_old_currently_equipped, rune_equipped))// write the unequipped rune information into the stash file and write the still equipped runes into the new equipped file
					{
						if (counter != rune_to_unequip)
						{
							write_new_currently_equipped << rune_equipped << "\n";
							counter++;
						}
						else
						{
							write_current_stash << rune_equipped << "\n";
							counter++;
						}
					}
					write_current_stash.close();
					read_old_currently_equipped.close();
					write_new_currently_equipped.close();
					remove(old_currently_equipped.c_str());
					rename(new_currently_equipped.c_str(), old_currently_equipped.c_str());
				}
				
				return selection_menu(existing_character);
			}
			else
			{
				cout << "Your stash is full! Please salvage some runes!" << "\n";
				return selection_menu(existing_character);
			}
		}
		else
		{
			cout << "You are currently not equipping any runes therefore you cannot unequip!" << "\n";
			return selection_menu(existing_character);
		}
	}
	case 3:
	{

	}
	case 4:
	{
		return selection_menu(existing_character);
	}
	}


}

int read_number_of_runes_equipped(string existing_character)
{
	int current_equipped_runes = 0;//we will read 6 in total, and 6 is the maximum
	string line;
	ifstream read_file;
	read_file.open("Characters/" + existing_character + "_currently_equipped_runes.txt");
	while (getline(read_file, line))
	{
		if (line.find("Rarity") != string::npos)
		{
			current_equipped_runes++; //basically count how many runes are currently in the stash
		}
	}
	read_file.close();

	return current_equipped_runes;
}

int read_number_of_runes_in_stash(string existing_character)//it is completed
{
	int current_stashed_runes = 0;//we will read 6 in total, and 6 is the maximum
	string line;
	ifstream read_file;
	read_file.open("Characters/" + existing_character + "_stash.txt");
	while (getline(read_file, line))
	{
		if (line.find("Rarity") != string::npos)
		{
			current_stashed_runes++; //basically count how many runes are currently in the stash
		}
	}
	read_file.close();

	return current_stashed_runes;
}

//character growth including functions such as new_stats, growth_rate...etc

void new_stats(string existing_character)//after levelling we have new stats//it is completed
{
	float* current_growth_rate = growth_rate(existing_character);
	float* current_stats_character = current_stats(existing_character);
	string new_stats_file = "Characters/" + existing_character + "_new.txt";
	ofstream myfile;
	myfile.open(new_stats_file);
	myfile << "Barbarian" << "\n";//defining the stats of a barbarian
	myfile << "-----------------------------------------" << "\n";
	myfile << "HP: " << current_stats_character[6] + current_growth_rate[0] << "\n";
	myfile << "ATT: " << current_stats_character[0] + current_growth_rate[1] / 100<< "\n";
	myfile << "DEF: " << current_stats_character[2] << "\n"; //+ current_growth_rate
	myfile << "AGI: " << current_stats_character[1] + current_growth_rate[2] / 100 << "\n";
	myfile << "STR: " << current_stats_character[4] + current_growth_rate[3] / 100 << "\n";
	myfile << "DEX: " << current_stats_character[3] + current_growth_rate[4] / 100 << "\n";
	myfile.close();//do not forget to close your textfile, I have made a mistake of not closing the file in continue_game therefore leading to not able to delete the original_character_stats_file
	string original_character_stats_file = "Characters/" + existing_character + ".txt";
	remove(original_character_stats_file.c_str());
	rename(new_stats_file.c_str(), original_character_stats_file.c_str());
	return;

}

float* growth_rate(string existing_character)//it is completed
{
	ifstream read_from_equipment_file;
	string equipment_file = "Characters/" + existing_character + "_currently_equipped_runes.txt";
	read_from_equipment_file.open(equipment_file);//we will read the equipment data and update the stats
	string rune_information;//for storing the info of rune currently equipped 
	float total_equipment_stats[4]{};
	while (getline(read_from_equipment_file, rune_information))
	{
		if(!rune_information.empty())
		{
			string* individual_rune_stats = extract_rune_stats(rune_information);//extract the stats of the rune from current line
			total_equipment_stats[0] += stof(individual_rune_stats[0]);//agility growth
			total_equipment_stats[1] += stof(individual_rune_stats[1]);//strength growth
			total_equipment_stats[2] += stof(individual_rune_stats[2]);//dexiterity growth
			total_equipment_stats[3] += stof(individual_rune_stats[3]);//hp growth
		}
		
	}
	string agi_growth = "AGI Growth";
	string str_growth = "STR Growth";
	string dex_growth= "DEX Growth";
	string hp_growth = "HP Growth";
	string attack_growth = "ATT Growth";
	string current_agi_growth;
	string current_str_growth;
	string current_dex_growth;
	string current_hp_growth;
	string current_attack_growth;
	static float growth_rate_character[5];
	bool found[5] = { false, false, false, false, false};
	string character_growth_file = "Characters/" + existing_character + "_growth.txt";
	string line = "";
	ifstream myfile;
	myfile.open(character_growth_file);
	while (std::getline(myfile, line) && ((found[0] == false) || (found[1] == false) || (found[2] == false) || (found[3] == false)))
	{
		if (line.find(agi_growth) != string::npos) //gotta watchout .find only finds the first element in the textfile that matches attack string
		{
			found[0] = true;
			current_agi_growth = line;//assigning the line with the keyword "current_attack", instead of overwrite attack, because the if statement above 

		}
		else if (line.find(str_growth) != string::npos) //gotta watchout .find only finds the first element in the textfile that matches attack string
		{
			found[1] = true;
			current_str_growth = line;//assigning the line with the keyword "current_def", instead of overwrite attack, because the if statement above 

		}
		else if (line.find(dex_growth) != string::npos)
		{
			found[2] = true;
			current_dex_growth = line;
		}
		else if (line.find(hp_growth) != string::npos)
		{
			found[3] = true;
			current_hp_growth = line;
		}
		else if (line.find(attack_growth) != string::npos)
		{
			found[4] = true;
			current_attack_growth= line;
		}
	}
	myfile.close();
	current_agi_growth = current_agi_growth.substr(12, current_agi_growth.length() - 2);
	current_dex_growth = current_dex_growth.substr(12, current_dex_growth.length() - 2);
	current_str_growth = current_str_growth.substr(12, current_str_growth.length() - 2);
	current_hp_growth = current_hp_growth.substr(11, current_hp_growth.length() - 2);
	current_attack_growth = current_attack_growth.substr(12, current_attack_growth.length() - 2);
	growth_rate_character[0] = stof(current_hp_growth) + total_equipment_stats[3];
	growth_rate_character[1] = stof(current_attack_growth);
	growth_rate_character[2] = stof(current_agi_growth)+ total_equipment_stats[0];
	growth_rate_character[3] = stof(current_str_growth) +total_equipment_stats[1];
	growth_rate_character[4] = stof(current_dex_growth) + total_equipment_stats[2];
	
	return growth_rate_character;



}

float current_exp_requirement(float level)//exp requirement is not part of the array from return of current_stats //it is completed
{
	float required_exp = 20;
	for (int i = 0; i < level; i++)//calculate the exp requirement for CURRENT level
	{
		required_exp += i * 10;
	}
	return required_exp;
}

void gain_exp(float exp_gain, string existing_character)//completed
{
	float* character_stats = current_stats(existing_character);//retrieve the current stats of the character
	if (character_stats[8] + exp_gain >= current_exp_requirement(character_stats[7]))//determine if the exp gained is enough to level up
	{
		cout << "Congratulations! You levelled up! You are now level "<< character_stats[7] + 1 << "\n";//if we levelled up we must change the statss
		new_stats(existing_character);
		ofstream myfile;
		string new_character_exp_file = "Characters/" + existing_character + "_new_current_exp_requirement.txt";//creating a new textfile for recalculation of current exp
		myfile.open(new_character_exp_file);
		myfile << "level: " << character_stats[7] + 1 << "\n"; //if level up is true, we add one to current level and output to file
		myfile << "Current exp: " << character_stats[8] + exp_gain - current_exp_requirement(character_stats[7]); // we would require the current_exp plus the exp gain - current_exp requirement
		myfile.close();
		string delete_current_exp_file = "Characters/" + existing_character + "_current_exp_requirement.txt";//there seems to be a problem with deleting character and still leaving a space behind in the save file
		remove(delete_current_exp_file.c_str());
		rename(new_character_exp_file.c_str(), delete_current_exp_file.c_str()); // because we are renaming the new file to the old file name
		return;

	}
	else
	{
		ofstream myfile;
		string new_character_exp_file ="Characters/" + existing_character + "_new_current_exp_requirement.txt";//creating a new textfile for recalculation of current exp
		myfile.open(new_character_exp_file);
		myfile <<"level: "<< character_stats[7] << "\n"; //if level_up is false, we 
		myfile << "Current exp: " << character_stats[8] + exp_gain;
		myfile.close();
		string delete_current_exp_file = "Characters/" + existing_character + "_current_exp_requirement.txt";//there seems to be a problem with deleting character and still leaving a space behind in the save file
		remove(delete_current_exp_file.c_str());
		rename(new_character_exp_file.c_str(), delete_current_exp_file.c_str()); // because we are renaming the new file to the old file name
		return;


	}
}
//generate comabt
void start_dungeon(int level_selected, string existing_character)//completed
{
	cout << "-----------------------------------------" << "\n";
	cout << "Currently generating dungeon ...." << "\n";
	cout << "Dungeon generated" << "\n" << "-----------------------------------------" << "\n";
	//determining what level the player has selected
	int number_of_enemies;
	float* your_character_stats = current_stats(existing_character);
	float current_hp = your_character_stats[6];//for tracking the hp in the dungeon
	int current_level = your_character_stats[7]; //extracting current stats
	if (level_selected < 5)
	{
		number_of_enemies = 2;
	}
	else
	{
		number_of_enemies = 3;
	}
	int current_number_enemies = 0;//the counter for the enemies
	while (current_number_enemies < number_of_enemies && current_hp > 0)//stops if you have defeated the number of enemies generated, or if you die
	{
		Sleep(2500);//make a lag to simulate fighting
		goblin* enemies_goblins = new goblin(level_selected, current_level, your_character_stats[2]);
		current_number_enemies++;
		cout << enemies_goblins->attack_power << "\n";
		cout << enemies_goblins->health << "\n";
		/*cout << enemies_goblins->attack_power << "\n";
		cout << enemies_goblins->health << "\n";*/
		current_hp = combat(enemies_goblins, existing_character, current_hp);
		cout << current_hp << "\n";
		if (current_hp > 0)//after combat, only if our current hp is above zero would give us exp, loot
		{
			cout << "You win this battle! You gained " << enemies_goblins->exp << " exp" << "\n";
			update_number_of_enemies_killed(existing_character, level_selected);
			gain_exp(enemies_goblins->exp, existing_character);//if your current hp is greater than 0, you gain exp, if you are dead, you don't get exp
			drop_loot(existing_character, level_selected);
		}
		else {
			cout << "You are now dead! You can do better next time!" << "\n";
		}
		delete enemies_goblins;
	}
	if (current_hp > 0 && (level_selected >= your_character_stats[9]))//if after combat, you have successfully survived, you will unlock the next 3 dungeon levels
	{
		ofstream myfile;
		string new_dungeon_level_file = "Characters/" + existing_character + "_new_current_max_dungeon.txt";
		myfile.open(new_dungeon_level_file);
		myfile << "MAX dungeon_lvl = " << your_character_stats[9] + 3;
		myfile.close();
		string original_dungeon_level_file = "Characters/" + existing_character + "_current_max_dungeon.txt";
		remove(original_dungeon_level_file.c_str());
		rename(new_dungeon_level_file.c_str(), original_dungeon_level_file.c_str());
		cout << "You may move up to the " << your_character_stats[9] + 3 << " level" << "\n";
		cout << "----------------------------------------- " << "\n";
		
	}
	return dungeon_selection(existing_character);
	
}

void update_number_of_enemies_killed(string existing_character, int level_selected)
{
	ifstream myfile;
	string current_number_enemies_kill_count_file = "Characters/" + existing_character + "_number_of_kills_in_each_difficulty.txt";
	myfile.open(current_number_enemies_kill_count_file);
	string array_number_of_kills[5];
	string line;
	while (getline(myfile, line))
	{
		if (line.find("normal") != string::npos)
		{
			array_number_of_kills[0] = line;
		}
		else if (line.find("veteran") != string::npos)
		{
			array_number_of_kills[1] = line;
		}
		else if (line.find("elite") != string::npos)
		{
			array_number_of_kills[2] = line;
		}
		else if (line.find("torture") != string::npos)
		{
			array_number_of_kills[3] = line;
		}
		else if (line.find("divine") != string::npos)
		{
			array_number_of_kills[4] = line;
		}		
	}
	myfile.close();
	int number_of_kills_per_difficulty[5];//extract the number of kills per difficulty
	array_number_of_kills[0] = array_number_of_kills[0].substr(47, array_number_of_kills[0].length() - 1);
	array_number_of_kills[1] = array_number_of_kills[1].substr(48, array_number_of_kills[1].length() - 1);
	array_number_of_kills[2] = array_number_of_kills[2].substr(46, array_number_of_kills[2].length() - 1);
	array_number_of_kills[3] = array_number_of_kills[3].substr(48, array_number_of_kills[3].length() - 1);
	array_number_of_kills[4] = array_number_of_kills[4].substr(47, array_number_of_kills[4].length() - 1);
	number_of_kills_per_difficulty[0] = stoi(array_number_of_kills[0]);
	number_of_kills_per_difficulty[1] = stoi(array_number_of_kills[1]);
	number_of_kills_per_difficulty[2] = stoi(array_number_of_kills[2]);
	number_of_kills_per_difficulty[3] = stoi(array_number_of_kills[3]);
	number_of_kills_per_difficulty[4] = stoi(array_number_of_kills[4]);
	if (level_selected <= 150)
	{
		number_of_kills_per_difficulty[0] += 1;
	}
	else if (150 < level_selected <= 450)
	{
		number_of_kills_per_difficulty[1] += 1;
	}
	else if (450 < level_selected <= 900)
	{
		number_of_kills_per_difficulty[2] += 1;
	}
	else if (900 < level_selected <= 1800)
	{
		number_of_kills_per_difficulty[3] += 1;
	}
	else
	{
		number_of_kills_per_difficulty[4] += 1;
	}
	string new_enemies_kill_count_file ="Characters/" + existing_character + "_new_number_of_kills_in_each_difficulty.txt";
	ofstream newfile;
	newfile.open(new_enemies_kill_count_file);
	newfile << "Number of enemies killed in normal difficulty: " << number_of_kills_per_difficulty[0] << "\n";
	newfile << "Number of enemies killed in elite difficulty: " << number_of_kills_per_difficulty[1] << "\n";
	newfile << "Number of enemies killed in veteran difficulty: " << number_of_kills_per_difficulty[2] << "\n";
	newfile << "Number of enemies killed in torture difficulty: " << number_of_kills_per_difficulty[3] << "\n";
	newfile << "Number of enemies killed in divine difficulty: " << number_of_kills_per_difficulty[4];
	newfile.close();
	remove(current_number_enemies_kill_count_file.c_str());
	rename(new_enemies_kill_count_file.c_str(), current_number_enemies_kill_count_file.c_str());

}

float combat(goblin* enemies, string existing_character, float current_hp)
{
	float* your_character_stats = current_stats(existing_character);//we aren't editing the character file, so these stats are just extracted using current stats and the stats are used to compare enemies and you
	bool enemy_moves_first = your_character_stats[1] < enemies->agi;
	if (!enemy_moves_first)
	{
		enemies->health = enemies->health - (your_character_stats[5] - enemies->defense);
		if (enemies->health > 0)
		{
			current_hp = current_hp - enemies->attack_power;//your character would be making the first move because you have higher agility
		}
		else
		{
			cout << "You win this battle" << "\n";
			return current_hp;
		}

	}
	else
	{
		current_hp = current_hp - enemies->attack_power;//the enemies would attack you first becuase they have higher agi
	}
	
	
	while (enemies->health > 0 && current_hp > 0)//check whether your hp or the enemy hp is higher than 0
	{
		enemies->health = enemies->health - (your_character_stats[5] - enemies->defense);
		if (enemies->health > 0)
		{
			current_hp = current_hp- enemies->attack_power;
		}
	}
	
		//implement exp_gain() which contains level_up
	return current_hp;
		
}
//Game interface
void selection_menu(string existing_character)//need to IMPLEMENT exiting game in every case
{
	cout << "-----------------------------------------" << "\n";
	cout << "0.Dungeon" << "\n" << "1.Runemaster" << "\n" << "2.Stash" << "\n" << "3.View your current stats" << "\n" << "4.Change runes" << "\n" << "5.Exit game" << "\n";
	cout << "You can stop playing by typing 5!" << "\n";
	cout << "Please type 0,1,2,3,4 or 5" << "\n";
	int option;
	cin >> option;

	

	//1 = Yes, 0 = No
	if (check_input_if_letter())
	{
		cout << "Please enter a valid input! 1~5" << "\n";
		return selection_menu(existing_character);
	}
	else
	{
		if (option == 0)
		{
			if (read_number_of_runes_in_stash(existing_character) < 5)
			{
				int choice;
				cout << "Are you sure you want to go to dungeon ? 1: Yes 0: No" << "\n";//ask player if they wanted to go to dungeon
				cin >> choice;
				if (choice == 0)//if the choice is 0
				{
					return selection_menu(existing_character);//call the function again given the options 
				}
				else if (choice == 1)
				{
					return dungeon_selection(existing_character);

				}
			}
			else
			{
				cout << "Please salvage your runes in runemaster!" << "\n";
				return selection_menu(existing_character);
			}


		}
		else if (option == 1)
		{
			float* character_stats = current_stats(existing_character);
			return rune_master(existing_character, character_stats[9]);
			//NEED TO IMPLEMENT rune master


			//}
		}
		else if (option == 2)
		{
			//need to implement stash
			stash(existing_character);
			return selection_menu(existing_character);



		}
		else if (option == 3)
		{
			//view current stats
			return view_stats(existing_character);
		}
		else if (option == 4)
		{
			//implement change runes
			return equipping_runes(existing_character);
		}
		else if (option == 5)
		{
			cout << "Ending the game...." << "\n";
			return;
		}
		else if (option < 0 || option > 5)
		{
			cout << "Please enter a valid option! 1~5" << "\n";
			return selection_menu(existing_character);
		}
	}
	
	
}

float* current_stats(string existing_character)
{//extraing stats for character as an array
	ifstream myfile;
	myfile.open("Characters/" + existing_character + ".txt");
	static float stats[11];
	string HP = "HP";
	string attack = "ATT";
	string def = "DEF";
	string agi = "AGI";
	string str = "STR";
	string dex = "DEX";
	string level = "level";
	string line = "";
	bool found[6] = { false, false, false, false, false, false};
	string current_hp;
	string current_attack;
	string current_def;
	string current_agi;
	string current_str;
	string current_dex;
	string current_level;
	string current_max_dungeon_level;
	while (std::getline(myfile, line) && ((found[0] == false) || (found[1] == false) || (found[2] == false) || (found[3] == false) || (found[4] == false) || (found[5] == false)))//if the four stats are found, therefore all will be true, and the while loop will stop, if any of the stats aren't found, we should keep running therefore we use ||
	{
		if (line.find(attack) != string::npos) //gotta watchout .find only finds the first element in the textfile that matches attack string
		{
			found[0] = true;
			current_attack = line;//assigning the line with the keyword "current_attack", instead of overwrite attack, because the if statement above 

		}
		else if (line.find(agi) != string::npos) //gotta watchout .find only finds the first element in the textfile that matches attack string
		{
			found[1] = true;
			current_agi = line;//assigning the line with the keyword "current_def", instead of overwrite attack, because the if statement above 

		}
		else if (line.find(def) != string::npos) 
		{
			found[2] = true;
			current_def = line;
		}
		else if (line.find(dex) != string::npos)
		{
			found[3] = true;
			current_dex = line;
		}
		else if (line.find(str) != string::npos)
		{
			found[4] = true;
			current_str = line;
		}
		else if (line.find(HP) != string::npos) 
		{
			found[5] = true;
			current_hp = line;

		}
	}
	myfile.close();
	myfile.open("Characters/" + existing_character + "_current_max_dungeon.txt");
	while (std::getline(myfile, line))
	{
		current_max_dungeon_level = line;
	}
	current_max_dungeon_level = current_max_dungeon_level.substr(18, current_max_dungeon_level.length() - 1);
	myfile.close();
	current_attack= current_attack.substr(5, current_attack.length() - 1);//extracting attack power
	current_def = current_def.substr(5, current_def.length() - 1);//extracting current defense
	current_agi = current_agi.substr(5, current_agi.length() - 1);//extracting current agility
	current_str = current_str.substr(5, current_str.length() - 1);//extracting current strength
	current_dex= current_dex.substr(5, current_dex.length() - 1);//extracting current dexterity
	current_hp = current_hp.substr(4, current_hp.length() - 1);//extracting current hp
	stats[0] = stof(current_attack);
	stats[1] = stof(current_agi);
	stats[2] = stof(current_def); 
	stats[3] = stof(current_dex);
	stats[4] = stof(current_str);
	//if you are a barb we have to take into account str for damage as well, but for rogue we take into account agi as damage
	float total_damage = (1 + stof(current_str) / 40) * stof(current_attack);
	string current_total_damage = to_string(total_damage);
	stats[5] = stof(current_total_damage);
	stats[6] = stof(current_hp);

	myfile.open("Characters/" + existing_character + "_current_exp_requirement.txt");
	string current_exp = "Current exp"; //find current exp
	while (std::getline(myfile, line))
	{
		if (line.find(current_exp) != string::npos)
		{
			current_exp = line;
		}
		if (line.find(level) != string::npos)
		{
			current_level = line;
		}


	}
	myfile.close();
	current_exp = current_exp.substr(13, current_exp.length() - 1);
	current_level = current_level.substr(7, current_level.length() - 1);
	stats[7] = stof(current_level);
	stats[8] = stof(current_exp);
	stats[9] = stof(current_max_dungeon_level);
	myfile.open("Characters/" + existing_character + "_stash.txt");
	string current_rune_powder = "Rune Powder:";
	while (std::getline(myfile, line))
	{
		if (line.find(current_rune_powder) != string::npos)
		{
			current_rune_powder = line;
		}
	}
	current_rune_powder = current_rune_powder.substr(13, current_rune_powder.length() - 1);
	stats[10] = stof(current_rune_powder);
	myfile.close();
	return stats;

}

void dungeon_selection(string existing_character)
{
	float* character_stats = current_stats(existing_character);
	float current_max_dungeon_level = character_stats[9];
	cout << "You are currently in the dungeon, input a level or esc to leave dungeon" << "\n";
	string level_selection;
	cin >> level_selection;//PROBLEM ENCOUNTERED WITH to_string on level selection
	while (level_selection != "esc") {
		if (stof(level_selection) > current_max_dungeon_level)//if selection is higher than the max dungeon level
		{
			cout << "Sorry, your current Max Dungeon Level is " << current_max_dungeon_level << ", please select a level at the same level of the Max Dungeon level or lower" << "\n";
			cin >> level_selection;//allow player to select a level

		}
		if (stof(level_selection) <= current_max_dungeon_level)
		{
			cout << "Are you sure you are going to level " << stof(level_selection) << " ? 1: Yes, 0: No " << "\n";
			string level_confirmation;
			cin >> level_confirmation;//asking the player to confirm they want to go to this level
			if (level_confirmation == "1")//the player would like to go to this level
			{
				cout << "You are going to level" << level_selection << "\n";
				
				//IMPLEMENT start dungeon();
				return start_dungeon(stoi(level_selection),existing_character);
			}
			else//the player would like to go to another level
			{
				string confirmation;
				cout << "Would you like to go to another level ? 1: Yes 0: No" << "\n";
				cin >> confirmation;
				if (confirmation == "1")
				{
					return dungeon_selection(existing_character);//redo the dialog of dungeon selection
				}
				else if (confirmation == "0")//Will take the plyaer back to the selection menu since the player does not choose to go to any level
				{
					cout << "----------------------------------------- " << "\n";
					return selection_menu(existing_character);
				}

			}
		}
	}
	if (level_selection == "esc")
	{
		return selection_menu(existing_character);
	}
}

void view_stats(string existing_character)
{
	cout << "What would you like to do today, " << existing_character << "? " << "\n";
	float* stats_array = current_stats(existing_character);//retrieving current stats
	float* growth_array = growth_rate(existing_character);
	cout << "You current stats are: " << "\n";
	cout << "LEVEL: " << stats_array[7] << "\n";
	cout << "HP: " << stats_array[6] << "\n";
	cout << "ATT: " << stats_array[0] << "\n";
	cout << "AGI: " << stats_array[1] << "\n";
	cout << "DEF: " << stats_array[2] << "\n";
	cout << "DEX: " << stats_array[3] << "\n";
	cout << "STR: " << stats_array[4] << "\n";
	cout << "TOTAL ATTCK POWER: " << stats_array[5] << "\n";
	cout << "MAX dungeon level: " << stats_array[9] << "\n";
	cout << "HP Growth: " << growth_array[0] << "\n";
	cout << "ATT Growth: " << growth_array[1] << "\n";
	cout << "AGI Growth: " << growth_array[2] << "\n";
	cout << "STR Growth: " << growth_array[3] << "\n";
	cout << "DEX Growth: " << growth_array[4] << "\n";
	cout << "Current Rune Powder: " << stats_array[10] << "\n";
	cout << "-----------------------------------------" << "\n";
	return selection_menu(existing_character);


}

void generating(string character_name)//generating your character, NOT implementing the inventory system yet, just going with runes
{
	
	string character_save = "Characters/" + character_name + ".txt";//creating individual character saves
	ofstream myfile;
	myfile.open(character_save, ios::app);
	cout << "Welcome to World of Madness! Here you will fight and improve yourself endlessly! " << "\n";
	cout << "Choose your brave hero! " << "\n";
	cout << "Here are your options:" << "\n";
	string barbarian_description = "Barbarian: Brave Conqueror of the lands, they are able to wield swords, spears, axes, and maces (They have passive bonus of +50% HP/ +50% STR \n" ;
	string rogue_description = "Rogue: Brave conqueror of the undergrounds, they are able to wield bows, daggers (They have passive bonus of +50% AGI/ + 50% DEX \n" ;
	cout << barbarian_description << "\n";
	cout << rogue_description << "\n" ;
	cout << "-----------------------------------------" << "\n";

	int hero_choose;
	bool yes_no = 0;//are you sure you are choosing the hero
	//creating a function that allows input to be given if the player wanted to choose a different hero, 
	while (yes_no == 0)
	{
		cout << "Which hero are you going with? 1:Barbarian 2:Rogue" << "\n";
		cin >> hero_choose;
		if (hero_choose == 1)
		{
			cout << "Are you sure you are going with Barbarian? 1: Yes 0: No" << "\n";
			cin >> yes_no;
			if (yes_no == 1)
			{
				srand(time(0) + rand());
				myfile << "Barbarian" << "\n";//defining the stats of a barbarian
				/*myfile << "-----------------------------------------" << "\n";
				myfile << "Currently Equipped:" << "\n";
				myfile << "Weapon: None" << "\n";
				myfile << "Helmet: None" << "\n";
				myfile << "Armor: None" << "\n";
				myfile << "Pants: None" << "\n";
				myfile << "Jewelry: None" << "\n";
				myfile << "Gloves: None" << "\n";*/
				myfile << "-----------------------------------------" << "\n";
				myfile << "HP: 100.00" << "\n";
				myfile << "ATT: 25.00" << "\n";
				myfile << "DEF: 3.00" << "\n";
				myfile << "AGI: 1.00" << "\n";
				myfile << "STR: 3.00" << "\n";
				myfile << "DEX: 1.00" << "\n";
				myfile.close();
				string character_growth = "Characters/" + character_name + "_growth.txt";
				myfile.open(character_growth, ios::app);				
				myfile << "HP Growth: " << to_string(40 + rand() % 30) << "\n";
				myfile << "ATT Growth: " << to_string(70 + rand() % 20) << "%" << "\n";
				myfile << "AGI Growth: " << to_string(40 + rand() % 15) << "%" << "\n";
				myfile << "STR Growth: " << to_string(230 + rand() % 50) << "%" << "\n";
				myfile << "DEX Growth: " << to_string(40 + rand() % 15) << "%" << "\n";
				myfile.close();
				//string character_inventory = character_name + "_inventory.txt";
				//myfile.open(character_inventory,ios::app);
				//srand(time(0) + 1);//generating a different seed for the stats
				////generating a random seed for rand, probably should create a data base for a lot of variety of weapons and armors....
				//myfile << "wooden sword" << " ATT: " << to_string(3 + rand() % 3) << " | " << " STR: " << to_string(2 + rand() % 3) << "\n";//generating random stats for equipment
				//myfile << "wooden helmet" << " HP: " << to_string(20 + rand() % 3) << "\n";
				//myfile << "wooden pants" << " DEF: " << to_string( 3 + rand() % 3) << "\n";
				//myfile << "wooden armor" << " HP: " << to_string(20 + rand() % 3) << "|" << " DEF: " << to_string( 6 + rand() % 3) << "\n";
				//myfile << "wooden gloves" << " HP: " << to_string(20 + rand() % 3) << "|" << " AGI: " << to_string(1+ rand() % 3 ) << " | " << " STR: " << to_string(3 + rand() %3) << "\n";
				//myfile.close();
				string current_exp_requirement = "Characters/" + character_name + "_current_exp_requirement.txt";
				myfile.open(current_exp_requirement, ios::app);
				myfile << "level: 1" << "\n";
				myfile << "Current exp: 0";
				myfile.close();
				string max_dungeon = "Characters/" + character_name + "_current_max_dungeon.txt";
				myfile.open(max_dungeon, ios::app);
				myfile << "MAX dungeon_lvl = 1" ;//starting character will have a MAX dungeon_level of 0;
				myfile.close();
				string character_stash= "Characters/" + character_name + "_stash.txt";
				myfile.open(character_stash, ios::app);//creating a stahs file for character
				myfile << "Rune Powder: 0 " << "\n";
				myfile.close();
				string currently_equipped = "Characters/" + character_name + "_currently_equipped_runes.txt";
				myfile.open(currently_equipped);
				myfile.close();
				string number_of_kills = "Characters/" + character_name + "_number_of_kills_in_each_difficulty.txt";
				myfile.open(number_of_kills, ios::app);
				myfile << "Number of enemies killed in normal difficulty: 0" << "\n";
				myfile << "Number of enemies killed in veteran difficulty: 0" << "\n";
				myfile << "Number of enemies killed in elite difficulty: 0" << "\n";
				myfile << "Number of enemies killed in torture difficulty: 0" << "\n";
				myfile << "Number of enemies killed in divine difficulty: 0";
				myfile.close();
				//gamegenerating();
				return selection_menu(character_name);

			}
		}
		else if (hero_choose == 2)
		{
			cout << "Are you sure you are going with Rogue? 1: Yes 0: No " << "\n";
			cin >> yes_no;
			if (yes_no == 1)
			{
				myfile << "Rogue" << "\n";
				myfile << "level 0" << "\n";
				//gamegenerating();


			}
		}
		else
		{
			cout << "Please put a valid input!" << "\n";//any other option other than 1 or 2
			yes_no = 0;
		}

	}
	return;
}

bool find_charactername(string character_name)
{
		ifstream  myfile("Save.txt");
		string line;

		bool found = false;
		while (!myfile.eof() && found == false)//if both are fullfilled -> not end of the file and not found character name, we sop if end of file is reached or if character is found
		{
			getline(myfile, line);
			if(line == character_name)
			{
				found = true;
			}
		}
		return found;
}

void delete_character_save(string existing_character)
{
	//create a temporary file to save the characters that aren't getting deleted
	ifstream myfile("Save.txt");
	string line;
	ofstream temp("Save_New.txt");
	while (!myfile.eof())//reach the end of the file
	{
		getline(myfile, line);
		if (line != existing_character && !line.empty())
		{
			temp << line << endl; //adding the characters to the temporary file (that doesn't contain the existing character)
		}
		
	}

	temp.close();
	myfile.close();
	string delete_save =  "Save.txt";//there seems to be a problem with deleting character and still leaving a space behind in the save file
	remove(delete_save.c_str());
	rename("Save_New.txt", "Save.txt");
	string delete_max_dungeon_file ="Characters/" + existing_character + "_current_max_dungeon.txt";
	remove(delete_max_dungeon_file.c_str());
	string character_file = "Characters/" + existing_character + ".txt";
	remove(character_file.c_str());//using c_str to return a pointer to the array of chars made up of the "character_file_path" string
	/*string inventory_file = existing_character + "_inventory.txt";
	remove(inventory_file.c_str());*/
	string character_stash_file ="Characters/" + existing_character + "_stash.txt";
	remove(character_stash_file.c_str());//removing the stashfile
	string character_exp_requirement_file = "Characters/" + existing_character + "_current_exp_requirement.txt";
	remove(character_exp_requirement_file.c_str());//removing the exp_requirement file
	string character_growth_file = "Characters/" + existing_character + "_growth.txt";
	remove(character_growth_file.c_str());//removing the character growth file
	string current_enemies_kill_file = "Characters/" + existing_character + "_number_of_kills_in_each_difficulty.txt";
	remove(current_enemies_kill_file.c_str());
	string current_equipped_file = "Characters/" + existing_character + "_currently_equipped_runes.txt";
	remove(current_equipped_file.c_str());
	return;
}

void delete_character(string existing_character)//implementing deletion of character when the game first boot
{
	
	bool delete_char;
	cout << "-----------------------------------------" << "\n";
	if (find_charactername(existing_character) == true)//look for the name of the character you are trying to delete, if found we proceed
	{
		cout << "This character has been found, would you like to delete character? 1: Yes 0: No" << "\n";
		cin >> delete_char;
		if (delete_char == true)
		{
			string character_name;
			cout << "If you would like delete your character, please reenter the name of the character you are deleting (WARNING! your character would be deleted if you enter the correct name" << "\n";//as an insurance, the player would be asked to reenter their character name
			cin >> character_name;
			if (character_name == existing_character)//if the character names match, we are proceeding to delete
			{
				//DELETE all character files
				delete_character_save(existing_character);
				return begin_game();
				
			}
			else 
			{
				cout << "Your entry doesn't match the name of the character you are deleting" << "\n";
				cout << "Would you like to try again" << "\n";
				cin >> delete_char;//the input would determine whether the player would like to try to delete their character again ;
				if (delete_char == true)
				{
					cout << "Enter the name of the character you would like to delete: " << "\n";
					string character_name;
					cin >> character_name;
					return delete_character(character_name);//the function would run again

				}
				else 
				{
					return begin_game();//go back to the beginning of the game becuase the player has been determined to not want to delete their character
				}
			}

		}
		else 
		{
			return begin_game();
		}

	}
	else
	{
		cout << "Character name is not found" << "\n"; //warns the player that the character they are trying to delete is not found
		return begin_game();
	}
	return;
}

void begin_game()//need to implement if a character with the same name as been found, we need to choose a different name
{
	cout << "-----------------------------------------" << "\n"; // for asethetic reasons
	cout << "Welcome to Dungeon Conqueror!" << "\n";
	bool creating_new_character = 0;//determine whether player wanted to create new character
	cout << "Would you like to play from a previous save? 2:Delete character 1: Yes 0: No " << "\n";//if the player have played before or havent played before we provide options
	int play ;
	cin >> play;
	switch (play)
	{
		case 0:
		{
			cout << "Would you like to make a new character? 1: Yes 0: No" << "\n";//ask if the player would like to make a new character
			cin >> creating_new_character;


			if (creating_new_character == 1)//we would like to create a new character
			{
				ofstream myfile;
				myfile.open("Save.txt", ios::app);
				string charactername;
				cout << "Enter your character name! " << "\n";//enter your character name
				cin >> charactername;
				if (charactername.length() > 0) //we check if the name is not null
				{
					if (find_charactername(charactername) == false)
					{
						cout << "You character name is " << charactername << "\n";
						bool Yes_No;
						cout << "Are you sure this is your name? 1: Yes 0: No" << "\n";
						cin >> Yes_No;
						while (Yes_No == 0)
						{
							cout << "Reenter your character name!" << "\n";
							cin >> charactername; //taking your input as character name, ignore get rid of the current input
							cout << "You character name is " << charactername << "\n";//output your character name
							cout << "Are you sure this is your name? 1: Yes 0: No" << "\n";//are you sure you are going with your name
							cin >> Yes_No;//take your input and if no reenter your name

						}
						myfile << charactername << "\n";//only add character name if it is not in the save file
						myfile.close();
						return generating(charactername);
						
					}
					else {
						cout << "A character with similar name has been found" << "\n";
						//Would you like to use a different name? IMPLEMENTATION
					}
				}
				else
				{
					cout << "Character name must not be empty!" << "\n";
					//MUST IMPLEMENT reenter character name or create a separate function for creating character
				}
			}
		}
		case 1 :
		 {//if the player wants to play from a previous save
			cout << "What character would you like to play? " << "\n";//loading save
			ifstream  myfile("Save.txt");
			string line;
			string existing_character;//states which existing character should be played
			while (!myfile.eof())//basically runs until endoffile thus eof, outputs on console which characters are available
			{
				getline(myfile, line);
				cout << line << "\n";
			}
			cin >> existing_character;
			bool found = find_charactername(existing_character);//try to find the existing character name

			while (found == false)//if the character hasn't been found ask user to reenter the name
			{
				cout << "No characters with such a name has been found" << "\n";//restart game if character hasn't been found 
				return begin_game();
			}
			if (found == true)//if the character has been found, continue game
			{
				cout << "A character has been found with the entered name" << "\n";
				cout << "Generating dungeons for " << existing_character << "\n";//continue playing the saved character
				cout << "-----------------------------------------" << "\n";
				return selection_menu(existing_character);
				
			}
		}

		
		case 2 :
		{
			cout << "-----------------------------------------" << "\n";
			cout << "What is the name of the character you would like to delete?: " << "\n";
			string delete_character_name;
			cin >> delete_character_name;
			return delete_character(delete_character_name);

		}
	}
	return;
}

bool check_input_if_letter()
{
	if (!cin.good())
	{
		cin.clear();//clears state of cin
		cin.ignore(INT_MAX, '\n'); // this clears console
		return true;
	}
	else
	{
		return false;
	}
}

int main() 
{
	/*cout << read_number_of_runes_equipped("Jerry") << "\n";
	cout << read_number_of_runes_in_stash("Jerry") << "\n";*/
	if (!_mkdir("Characters"))
	{
		_mkdir("Characters");
	}
	begin_game();

}
