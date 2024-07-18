#pragma once
#include <iostream>
#include <string>
#include <time.h> 
#include <cstdlib> 
using namespace std;
class goblin
{
public:
	float health;
	float strength;
	float agi;
	float attack;
	float defense;
	float dex;
	float attack_power;
	double enemy_level;
	float exp;
	goblin(int current_dungeon_level, int character_level, float character_defense)//don't forget to add parameter character_defense
	{
		//need to implement difficulty scaling
		enemy_level = round(current_dungeon_level + (current_dungeon_level * current_dungeon_level) / 2000);
		health = 70 + enemy_level * enemy_level / 3;
		srand(time(0) + rand());//creating a random seed dependent on rand
		strength = float(current_dungeon_level) * 0.3 + float(rand()) / float(RAND_MAX) * current_dungeon_level * 0.3;
		srand(time(0) + rand());
		agi = float(current_dungeon_level) * 0.3+ (float(rand()) / float(RAND_MAX) * current_dungeon_level) * 0.3;
		srand(time(0) + rand());
		attack = float(current_dungeon_level) * 0.5 + (float(rand()) / float(RAND_MAX) * current_dungeon_level) * 0.5;
		srand(time(0) + rand());
		defense = float(current_dungeon_level) * 0.5 + float(rand()) / float(RAND_MAX) * current_dungeon_level * 0.5;
		srand(time(0) + rand());
		dex = float(current_dungeon_level) * 0.3 + float(rand()) / float(RAND_MAX) * current_dungeon_level * 0.3;
		exp = round((enemy_level * enemy_level) / 3) + 3;
		if (character_defense >= attack)
		{
			attack_power = 1;
		}
		else
		{
			attack_power = (attack - character_defense) * (1 + strength / 30) * (1 + dex / 30);
		}
		
		
	}
	~goblin()
	{

	}

};
class type_of_loot
{
public:
	string loot_type;
	void determine_loot_type()
	{
		float determiner = float(rand()) / float(RAND_MAX);
		if (determiner <= 0.2375)
		{
			loot_type = "Str";
		}
		else if (0.2375 < determiner <= 0.4750)
		{
			loot_type = "Agi";
		}
		else if (0.4750 < determiner <= 0.7125)
		{
			loot_type = "Dex";
		}
		else if (0.7125 < determiner <= 0.9500)
		{
			loot_type = "HP";
		}
		else
		{
			loot_type = "Chaos";
		}

	}

};
class loot : public type_of_loot
{
public:
	string rarity;
	loot(float rand_for_determining_drop, int level_selected)
	{
		if (level_selected <= 150)
		{
			float common_drop_chance = 0.85 - level_selected / 300;
			float magic_drop_chance = 0.10 + 5* (level_selected / 2400);
			float rare_drop_chance = 0.05 + level_selected / 800;
			if (rand_for_determining_drop <= common_drop_chance)//if the dice roll less than the chance for a common
			{
				rarity = "common";
			}
			else if (rand_for_determining_drop <= (1 - rare_drop_chance) && rand_for_determining_drop > common_drop_chance)
			{
				rarity = "magic";
			}
			else
			{
				rarity = "rare";
			}
		}
		else if (150 <level_selected <= 450)
		{
			float magic_drop_chance = 0.90 - level_selected / 1000;
			float rare_drop_chance = 0.08 + 2* level_selected / 3000;
			float unique_drop_chance = 0.02 + level_selected / 3000;
			if (rand_for_determining_drop <= magic_drop_chance)//if the dice roll less than the chance for a common
			{
				rarity = "magic";
			}
			else if (rand_for_determining_drop <= (1 - unique_drop_chance) && rand_for_determining_drop > magic_drop_chance)
			{
				rarity = "rare";
			}
			else 
			{
				rarity = "unique";
			}
		}
		else if (450 < level_selected <= 900)
		{
			float rare_drop_chance = 0.90 - level_selected / 4000;
			float unqiue_drop_chance = 0.095 + 2 * level_selected / 12000;
			float double_unique_drop_chance = 0.005 + level_selected / 12000;
			if (rand_for_determining_drop <= rare_drop_chance)//if the dice roll less than the chance for a common
			{
				rarity = "rare";
			}
			else if (rand_for_determining_drop <= (1 - double_unique_drop_chance) && rand_for_determining_drop > rare_drop_chance)
			{
				rarity = "unique";
			}
			else 
			{
				rarity = "double unique";
			}
		}
		else if (900 < level_selected <= 1800)
		{
			float unique_drop_chance= 0.98 - level_selected / 12000;
			float double_unqiue_drop_chance = 0.0195 + 2 * level_selected / 36000;
			float celestial_drop_chance = 0.0005 + level_selected / 36000;
			if (rand_for_determining_drop <= unique_drop_chance)//if the dice roll less than the chance for a common
			{
				rarity = "unique";
			}
			else if (rand_for_determining_drop <= (1 - celestial_drop_chance) && rand_for_determining_drop > unique_drop_chance)
			{
				rarity = "double unique";
			}
			else
			{
				rarity = "celestial";
			}
		}
		else 
		{
			float double_unique_drop_chance = 0.9995 - level_selected / 36000;
			float celestial_unqiue_drop_chance = 0.00045 + 2 * level_selected / 108000;
			float double_celestial_drop_chance = 0.00005 + level_selected / 108000;
			if (rand_for_determining_drop <= double_unique_drop_chance)//if the dice roll less than the chance for a common
			{
				rarity = "double unique";
			}
			else if (rand_for_determining_drop <= (1 - double_celestial_drop_chance) && rand_for_determining_drop > double_unique_drop_chance)
			{
				rarity = "celestial";
			}
			else 
			{
				rarity = "double celestial";
			}
		}

	}
	~loot()
	{

	}
};
void loot_generate_stats(string existing_character, int level_selected,int left_over_rune_powder, string rarity, string type, bool crafting);
bool drop_or_not(int level_selected);
void drop_loot(string existing_character, int level_selected);
//rune functions including rune_master, salvage, powder calculation, craft cost
void salvage_rune(string existing_character);
int extract_rune_information(string existing_character, int rune);
string* extract_rune_stats(string existing_character);
int rune_powder_calculate(string rune_rarity, int rune_level, bool crafting);
void rune_master(string exising_character, int maximum_dungeon_level);
//character stash 
void stash(string existing_character);
//character equipped functions
void display_currently_equipped(string existing_character);
void equipping_runes(string existing_character);
int read_number_of_runes_equipped(string existing_character);
int read_number_of_runes_in_stash(string existing_character);
//character growth including functions such as new_stats, growth_rate...etc
void new_stats(string existing_character);
float* growth_rate(string existing_character);
float current_exp_requirement(float level);
void gain_exp(float exp_gain, string exist_character);

//generate comabt
void start_dungeon(int level_selected, string exist_character);
void update_number_of_enemies_killed(string existing_character, int level_selected);
float combat(goblin* enemy, string existing_character, float current_hp);

//Game interface
void selection_menu(string existing_character);
float* current_stats(string existing_character);
void dungeon_selection(string existing_character);
void view_stats(string existing_character);
void generating(string character_name);//generating your character
bool find_charactername(string character_name);
void delete_character_save(string existing_character);
void delete_character(string character_name);
void begin_game();
bool check_input_if_letter();
