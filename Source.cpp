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
void loot_generate_stats(string existing_character, int level_selected, string rarity, string type)
{
	//randomizes the loot stats based on level_selected and type and rarity
	float rune_stat{};
	float* chaos_stats = new float [5] {};
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
	ofstream myfile;
	myfile.open("Characters/" + existing_character + "_stash.txt", ios::app);
	if(type == "HP")
	{
		myfile << "Rarity: " << rarity << "," << "Type: " << type << "," << "Stats: " << rune_stat << "\n";
	}
	else if (type == "Str" || type == "Agi" || type == "Dex")
	{
		myfile << "Rarity: " << rarity << "," << "Type: " << type << "," << "Stats: " << rune_stat << "%"  <<  "\n";
	}
	else if (type == "Chaos")
	{
		myfile << "Rarity: " << rarity << "," << "Type: " << type << "," << "HP: " << chaos_stats[0] << "%" << "," << "AGI: " << chaos_stats[1] << "%" << "," << "STR: " << chaos_stats[2] << "%" << "," << "DEX: " << chaos_stats[3] << "%" << "\n";
	}
	myfile.close();
	delete[] chaos_stats;
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
		if((read_number_of_runes(existing_character) + 1) <= 5) // if the current number of runes in the stash plus the rune you got is exceeding the limit
		{
			loot_generate_stats(existing_character, level_selected, received_loot->rarity, received_loot->loot_type);
		}
		else//the number of runes you currently hold in your inventory would exceed the total allowed if the loot is stashed
		{
			cout << "You have reached the maximum number of runes" << "\n";
			cout << "Would you like to salvage some of your runes in your stash? 1:Yes 0:No " << "\n";
			bool salvage;
			cin >> salvage;
			if (salvage == true)
			{
				//implementing salvage, need to implement rune powder
			}
		}
		delete received_loot;
	}
	return;
	//loot_stats(existing_character, level_selected, received_loot->rarity, received_loot->loot_type);
	//generate loot stats
}
void stash(string existing_character)
{
	cout << "Displaying current stash" << "\n";
	ifstream myfile;
	myfile.open("Characters/" + existing_character + "_stash.txt");
	string line;
	while (!myfile.eof())
	{
		getline(myfile, line);
		cout << line << "\n";
	}
	myfile.close();
	cout << "-----------------------------------------" << "\n";
	
}
int read_number_of_runes(string existing_character)
{
	int current_stashed_runes = 0;
	string line;
	ifstream read_file;
	read_file.open("Characters/" + existing_character + "_stash.txt");
	while (getline(read_file, line))
	{
		current_stashed_runes++; //basically count how many runes are currently in the stash
	}
	read_file.close();

	return current_stashed_runes;
}
void new_stats(string existing_character)//after levelling we have new stats
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

float* growth_rate(string existing_character)
{
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
	growth_rate_character[0] = stof(current_hp_growth);
	growth_rate_character[1] = stof(current_attack_growth);
	growth_rate_character[2] = stof(current_agi_growth);
	growth_rate_character[3] = stof(current_str_growth);
	growth_rate_character[4] = stof(current_dex_growth);
	
	return growth_rate_character;



}
float current_exp_requirement(float level)//exp requirement is not part of the array from return of current_stats 
{
	float required_exp = 20;
	for (int i = 0; i < level; i++)//calculate the exp requirement for CURRENT level
	{
		required_exp += i * 10;
	}
	return required_exp;
}
void gain_exp(float exp_gain, string existing_character)
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
void start_dungeon(int level_selected, string existing_character)
{
	cout << "-----------------------------------------" << "\n";
	cout << "Currently generating dungeon ...." << "\n";
	cout << "Dungeon generated" << "\n" << "-----------------------------------------" << "\n";
	//determining what level the player has selected
	int number_of_enemies;
	float* your_character_stats = current_stats(existing_character);
	float current_hp = your_character_stats[6];//for tracking the hp in the dungeon
	int current_level = your_character_stats[7]; //extracting current stats
	//float current_defense = stof(your_character_stats[2]);//extracting current defense
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
		current_hp = combat(enemies_goblins, existing_character, current_hp);
		if (current_hp > 0)//after combat, only if our current hp is above zero would give us exp, loot
		{
			cout << "You win this battle! You gained " << enemies_goblins->exp << "\n";
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

void selection_menu(string existing_character)//need to IMPLEMENT exiting game in every case
{
	cout << "-----------------------------------------" << "\n";
	cout << "0.Dungeon" << "\n" << "1.Runemaster" << "\n" << "2.Stash" << "\n" << "3.View your current stats" << "\n" << "4.Change runes" << "\n" << "5.Exit game" << "\n";
	cout << "You can stop playing by typing 4!" << "\n";
	cout << "Please type 0,1,2,3,4 or 5" << "\n";
	int option;
	cin >> option;

	switch (option)
	{

		//1 = Yes, 0 = No
		case 0:
		{
			int choice;
			cout << "Are you sure you want to go to dungeon ? 1: Yes 0: No" << "\n";//ask player if they wanted to go to dungeon
			cin >> choice;
			if (choice == 0)//if the choice is 0
			{
				return selection_menu(existing_character);//call the function again given the options 
			}
			if (choice == 1)
			{
				return dungeon_selection(existing_character);
				


			}


		}
		case 1:
		{
			return;
			//NEED TO IMPLEMENT rune master
			

			//}
		}
		case 2:
		{
			//need to implement stash
			stash(existing_character);
			return selection_menu(existing_character);
			
			

		}
		case 3:
		{
			//view current stats
			return view_stats(existing_character);
		}
		case 4:
		{
			//implement change runes
		}
		case 5:
		{
			cout << "Ending the game...." << "\n";
			return;
		}

	}
	return;
}

float* current_stats(string existing_character)
{//extraing stats for character as an array
	ifstream myfile;
	myfile.open("Characters/" + existing_character + ".txt");
	static float stats[10];
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
	float total_damage = (1 + stof(current_str) / 100) * stof(current_attack);
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
			cout << "Are you sure you are going to level " << stof(level_selection) << "? 1: Yes, 0: No " << "\n";
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
				srand(time(0));
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
				myfile << "HP Growth: " << to_string(15 + rand() % 10) << "\n";
				myfile << "ATT Growth: " << to_string(70 + rand() % 20) << "%" << "\n";
				myfile << "AGI Growth: " << to_string(40 + rand() % 15) << "%" << "\n";
				myfile << "STR Growth: " << to_string(130 + rand() % 30) << "%" << "\n";
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

int main() 
{

	if (!_mkdir("Characters"))
	{
		_mkdir("Characters");
	}
	begin_game();

}
