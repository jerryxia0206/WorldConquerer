#pragma once
#include <iostream>
#include <string>
#include <time.h> 
#include <cstdlib> 
using namespace std;
int dungeon_selection(string existing_character);
string* current_stats(string existing_character);
bool find_charactername(string character_name);
int delete_character(string character_name);
int begin_game();
void delete_character_save(string existing_character);
class goblin
{
public:
	int strength;
	
};