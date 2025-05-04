using namespace std;
#include <iostream>
#include <random>
#include <string>
#include <sstream>
#include <cstring>

#include <chrono>
#include <thread>

#include <cctype>
#include <algorithm>
#include "ship.h"










bool player_Corrosion;
bool player_Weakened;
bool player_Stunned;
bool player_Overheated;
bool player_Disrupted;
bool enemy_Corrosion;
bool enemy_Weakened;
bool enemy_Stunned;
bool enemy_Overheated;
bool enemy_Disrupted;


//miscellaneous stuff
std::string print_True_False(bool T_OR_F) {
	if (T_OR_F) {
		return "Yes";
	}
	else {
		return "No";
	}
}
void press_X_To_Continue() {
	
	std::cout << "Press 'x' to continue:" << std::endl;
	char x;
	
	cin >> x;
	cin.ignore();
	//i dont sanitize this input because it doesnt matter. 
	// the purpose is just to feed the information to the player, 
	// and so everything isnt printed at once
	cout << std::endl;
}
void press_X_To_Continue_And_Clear() {
	
	std::cout << "Press 'x' to continue:" << std::endl;
	char x;
	
	cin >> x;
	cin.ignore();
	//i dont sanitize this input because it doesnt matter. 
	// the purpose is just to feed the information to the player, 
	// and so everything isnt printed at once
	system("cls");
	std::cout << std::endl;
}

int random_Number(int min, int max) {
	random_device rd;
	mt19937 gen(rd());
	std::uniform_int_distribution<> distribution(min, max);
	return distribution(gen);
}
bool coin_Flip() {
	int random = random_Number(1, 100);
	if (random % 2 == 0) {
		return true;
	}
	else {
		return false;
	}
}
void win_Screen() {
	system("cls");
	for (int i = 0; i < 50; i++){
		cout << "YOU WIN!" << endl;
	}
	press_X_To_Continue_And_Clear();
}
bool return_Player_Char() {
	char valid_Player_Choice;
	string player_Choice;
	getline(cin, player_Choice);
	stringstream ss(player_Choice);
	ss >> valid_Player_Choice;
	if (ss.fail()) {
		return  false;
	}
	else {
		return true;
	}
}
int return_Player_Choice() {
	int valid_Player_Choice;
	string player_Choice;
	getline(cin, player_Choice);
	stringstream ss(player_Choice);
	ss >> valid_Player_Choice;
	if (ss.fail()) {
		return -5;
	}
	else {
		return valid_Player_Choice;
	}
}


//item drops
void print_Dropped_Items(string text, int items[]) {
	cout << text << endl;
	if (items[0] > 0) {
		cout << "Stellar Debris (" << items[0] << ")" << endl;
	}
	if (items[1] > 0) {
		cout << "Nebula Shards (" << items[1] << ")" << endl;
	}
	if (items[2] > 0) {
		cout << "Quantum Cores (" << items[2] << ")" << endl;
		
	}
	if (items[3] > 0) {
		cout << "Dark Matter Essences (" << items[3] << ")" << endl;
	}
	press_X_To_Continue_And_Clear();
	cout << endl << endl;
}
void drop_Items(int level, int players_Inventory[]) {
	int rarity = random_Number(1, 9 + level);
	int length = random_Number(1, 1 + (level/2));
	int additional_Loot = random_Number(1, level * 3);
	int dropped_Items[4] = {0, 0, 0, 0};
	for (int i = 0; i < length; i++){
		if (rarity <= 8) {
			//drops common item
			dropped_Items[0] += random_Number(5, 5 + additional_Loot);
			
		}
		else if (rarity <= 10) {
			//drops uncommon item
			dropped_Items[1] += random_Number(2, 3 + additional_Loot/1.5);
		}
		else if (rarity <= 14) {
			//drops a rare item
			dropped_Items[2] += random_Number(1, 2 + additional_Loot/2);
		}
		else {
			//drops a very rare item
			dropped_Items[3] += random_Number(1, 1 + additional_Loot/3);
		}
	}
	for (int i = 0; i < 4; i++) {
		players_Inventory[i] += dropped_Items[i];
	}
	print_Dropped_Items("Dropped items:", dropped_Items);
}
void print_Inventory(int players_Inventory[]) {
	cout << endl;
	cout << "Your inventory: " << endl;
	if (players_Inventory[0] > 0) {
		cout << players_Inventory[0] << " Stellar debris" << endl;
	}
	if (players_Inventory[1] > 0) {
		cout  << players_Inventory[1]  << " Nebula shard(s)" << endl;
	}
	if (players_Inventory[2] > 0) {
		cout  << players_Inventory[2]  << " Quantum core(s)" << endl;
	}
	if (players_Inventory[3] > 0) {
		cout  << players_Inventory[3] << " Dark matter essence(s)" << endl;
	}
	if (players_Inventory[0] == 0 && players_Inventory[1] == 0 && players_Inventory[2] == 0 && players_Inventory[3] == 0) {
		cout << "EMPTY" << endl;
	}
	cout << endl;
}
// players inventory and an array of items to give the player
void give_Item(int players_Inventory[], int items[]) {
	for (int i = 0; i < 4; i++){
		players_Inventory[i] += items[i];
	}
	print_Dropped_Items("Items:", items);
}

//combat
void print_Num_Spaces(int num_Spaces) {
	for (int i = 0; i < num_Spaces; i++) {
		cout << " ";
	}
}
//statuses
bool check_Statuses(ship ship, vector<artillery>& artillery) {
	int* status_Effects = ship.get_All_Statuses();
	for (int i = 0; i < 4; i++) {
		if (status_Effects[i] > 0) {
			return true;
		}
	}
	for (int i = 0; i < artillery.size(); i++){
		if (artillery[i].get_Overheat_Status() > 0) {
			return true;
		}
	}
	return false;
}
void reset_Status_Displays() {
	player_Corrosion = false;
	player_Weakened = false;
	player_Stunned = false;
	player_Overheated = false;
	player_Disrupted = false;

	enemy_Corrosion = false;
	enemy_Weakened = false;
	enemy_Stunned = false;
	enemy_Overheated = false;
	enemy_Disrupted = false;
}
bool check_Overheat_Statuses(vector<artillery>& artillery) {
	for (int i = 0; i < artillery.size(); i++){
		if (artillery[i].get_Overheat_Status() > 0) {
			return true;
		}
	}
	return false;
}
void print_Current_Statuses(ship players_Ship, ship enemy_Ship, vector<artillery>& players_Artillery, vector<artillery>& enemys_Artillery, int line) {
	if (line == 1) {
		if (!check_Statuses(players_Ship, players_Artillery)) {
			cout << "NONE";
			print_Num_Spaces(34);
		}
		else if (players_Ship.get_Corrode_Status() > 0) {
			cout << "Corrosion";
			print_Num_Spaces(29);
			player_Corrosion = true;
		}
		else if (players_Ship.get_Weaken_Status() > 0) {
			cout << "Weakened";
			print_Num_Spaces(30);
			player_Weakened = true;
		}
		else if (players_Ship.get_Stun_Status() > 0) {
			cout << "Stunned";
			print_Num_Spaces(31);
			player_Stunned = true;
		}
		else if (check_Overheat_Statuses(players_Artillery)) {
			cout << "Overheated weapon";
			print_Num_Spaces(21);
			player_Overheated = true;
		}
		else if (players_Ship.get_Disrupted_Status() > 0) {
			cout << "Disrupted";
			print_Num_Spaces(29);
			player_Disrupted = true;
		}
		else {
			print_Num_Spaces(38);
		}


		if (!check_Statuses(enemy_Ship, enemys_Artillery)) {
			cout << "NONE" << endl;
		}
		else if (enemy_Ship.get_Corrode_Status() > 0) {
			cout << "Corrosion" << endl;
			enemy_Corrosion = true;
		}
		else if (enemy_Ship.get_Weaken_Status() > 0) {
			cout << "Weakened" << endl;
			enemy_Weakened = true;
		}
		else if (enemy_Ship.get_Stun_Status() > 0) {
			cout << "Stunned" << endl;
			enemy_Stunned = true;
		}
		else if (check_Overheat_Statuses(enemys_Artillery)) {
			cout << "Overheated weapon" << endl;
			enemy_Overheated = true;

		}
		else if (enemy_Ship.get_Disrupted_Status() > 0) {
			cout << "Disrupted" << endl;
			enemy_Disrupted = true;
		}
		
	}
	else if (line == 2) {
		if (players_Ship.get_Weaken_Status() > 0 && !player_Weakened) {
			cout << "Weakened";
			print_Num_Spaces(30);
			player_Weakened = true;
		}
		else if (players_Ship.get_Stun_Status() > 0 && !player_Stunned) {
			cout << "Stunned";
			print_Num_Spaces(31);
			player_Stunned = true;
		}
		else if (check_Overheat_Statuses(players_Artillery) && !player_Overheated) {
			cout << "Overheated weapon";
			print_Num_Spaces(21);
			player_Overheated = true;
		}
		else if (players_Ship.get_Disrupted_Status() > 0 && !player_Disrupted) {
			cout << "Disrupted";
			print_Num_Spaces(29);
			player_Disrupted = true;
		}
		else {
			print_Num_Spaces(38);
		}

		if (enemy_Ship.get_Weaken_Status() > 0 && !enemy_Weakened) {
			cout << "Weakened" << endl;
			enemy_Weakened = true;
		}
		else if (enemy_Ship.get_Stun_Status() > 0 && !enemy_Stunned) {
			cout << "Stunned" << endl;
			enemy_Stunned = true;
		}
		else if (check_Overheat_Statuses(enemys_Artillery) && !enemy_Overheated) {
			cout << "Overheated weapon" << endl;
			enemy_Overheated = true;
		}
		else if (enemy_Ship.get_Disrupted_Status() > 0 && !enemy_Disrupted) {
			cout << "Disrupted" << endl;
			enemy_Disrupted = true;
		}
		else {
			cout << endl;
		}


	}
	else if (line == 3) {
		if (players_Ship.get_Stun_Status() > 0 && !player_Stunned) {
			cout << "Stunned";
			print_Num_Spaces(32);
			player_Stunned = true;
		}
		else if (check_Overheat_Statuses(players_Artillery) && !player_Overheated) {
			cout << "Overheated weapon";
			print_Num_Spaces(21);
			player_Overheated = true;
		}
		else if (players_Ship.get_Disrupted_Status() > 0 && !player_Disrupted) {
			cout << "Disrupted";
			print_Num_Spaces(29);
			player_Disrupted = true;
		}
		else {
			print_Num_Spaces(38);
		}

		if (enemy_Ship.get_Stun_Status() > 0 && !enemy_Stunned) {
			cout << "Stunned" << endl;
			enemy_Stunned = true;
		}
		else if (check_Overheat_Statuses(enemys_Artillery) && !enemy_Overheated) {
			cout << "Overheated weapon" << endl;
			enemy_Overheated = true;
		}
		else if (enemy_Ship.get_Disrupted_Status() > 0 && !enemy_Disrupted) {
			cout << "Disrupted" << endl;
			enemy_Disrupted = true;
		}
		else {
			cout << endl;
		}
		
	}
	else if (line == 4) {
		if (check_Overheat_Statuses(players_Artillery) && !player_Overheated) {
			cout << "Overheated weapon";
			print_Num_Spaces(21);
			player_Overheated = true;
		}
		else if (players_Ship.get_Disrupted_Status() > 0 && !player_Disrupted) {
			cout << "Disrupted";
			print_Num_Spaces(29);
			player_Disrupted = true;
		}
		else {
			print_Num_Spaces(38);
		}
		if (check_Overheat_Statuses(enemys_Artillery) && !enemy_Overheated) {
			cout << "Overheated weapon" << endl;
			enemy_Overheated = true;
		}
		else if (enemy_Ship.get_Disrupted_Status() > 0 && !enemy_Disrupted) {
			cout << "Disrupted" << endl;
			enemy_Disrupted = true;
		}
		else {
			cout << endl;
		}
	}
	else if (line == 5) {
		if (players_Ship.get_Disrupted_Status() > 0 && !player_Disrupted) {
			cout << "Disrupted";
			print_Num_Spaces(29);
			player_Disrupted = true;
		}
		else {
			print_Num_Spaces(38);
		}
		if (enemy_Ship.get_Disrupted_Status() > 0 && !enemy_Disrupted) {
			cout << "Disrupted" << endl;
			enemy_Disrupted = true;
		}
		else {
			cout << endl;
		}
	}
	

}

void status_Effect_Actions(ship& ship, vector<artillery>& artillery) {
	string capitalized_Name = ship.get_Name();
	transform(capitalized_Name.begin(), capitalized_Name.end(), capitalized_Name.begin(), ::toupper);
	cout << capitalized_Name << " STATUS EFFECT UPDATES: " << endl << endl;
	if (ship.get_Corrode_Status() > 0) {
		int current_Health = ship.get_Current_Health();
		for (int i = 0; i < ship.get_Corrode_Status() && ship.get_Current_Health() > 0; i++) {
			ship.set_Current_Health(current_Health - 1);
		}
		cout <<  "Took " << ship.get_Corrode_Status() << " corrosion damage" << endl;
		press_X_To_Continue();
		ship.set_Corrosion_Status();
	}
	if (ship.get_Stun_Status() == 1) {
		int chance = random_Number(1, 100);
		if (chance <= 70) {
			ship.set_Stun_Status(0);
			cout <<  "Operating systems have rebooted" << endl;
			press_X_To_Continue();
		}
	}
	else if (ship.get_Stun_Status() > 1) {
		ship.set_Stun_Status(ship.get_Stun_Status() - 1);
	}
	for (int i = 0; i < artillery.size(); i++){
		if (artillery[i].get_Overheat_Status() > 0) {
			artillery[i].set_Overheat_Status(artillery[i].get_Overheat_Status() - 1);
			if (artillery[i].get_Overheat_Status() == 0) {
				cout << "The " << ship.get_Name() << "'s " << artillery[i].get_Name() << " cooled down and is now usable again" << endl;
				press_X_To_Continue();
			}
		}
	}
	if (ship.get_Disrupted_Status() > 0) {
		ship.set_Disrupted_Status(ship.get_Disrupted_Status() - 1);
		if (ship.get_Disrupted_Status() == 0) {
			cout << "Energy generator back online" << endl;
			press_X_To_Continue();
		}
	}
	if (ship.get_Weaken_Status() > 0) {
		ship.set_Weaken_Status(ship.get_Weaken_Status() - 1);
		if (ship.get_Weaken_Status() == 0) {
			cout << "Hull integrity has been restored" << endl;
			press_X_To_Continue();
		}
	}
}
int artillery::can_Apply_Overheat_Status(int percent) {
	int chance = random_Number(1, 100);
	if (chance <= percent) {
		int num_Turns = random_Number(1, 2);
		set_Overheat_Status(num_Turns);
		return num_Turns;
	}
	return false;
}
int can_Apply_Weakened_Status(int percent) {
	int chance = random_Number(1, 100);
	if (chance <= percent) {
		return 1;
	}
	return false;
}
int can_Apply_Stun_Status(int percent) {
	int chance = random_Number(1, 100);
	if (chance <= percent) {
		return 1;
	}
	return false;
}
int can_Apply_Corrosion_Status(int percent) {
	int chance = random_Number(1, 100);
	if (chance <= percent) {
		return 1;
	}
	return false;
}

int can_Apply_Disrupted_Status(int percent) {
	int chance = random_Number(1, 100);
	if (chance <= percent) {
		int num_Turns = random_Number(3, 5);
		return num_Turns;
	}
	return false;
}
void status_Codex() {
	system("cls");
	cout << "STATUS CODEX" << endl;
	cout << "----------------------" << endl;
	cout << "Corrosion: deals damage over time, dealing more each turn, to cure corrosive purchase a repair from a starship depot" << endl;
	cout << "Weaken: decreases the target's defense by 50% for 1 - 2 turns" << endl;
	cout << "Stun: disables the target's ability to act for a turn, 70% chance it goes away the subsequent turn" << endl;
	cout << "Overheat: disables the overheated artillery for 1 - 2 turns" << endl;
	cout << "Disrupted: disables energy regeneration for 3 - 5 turns" << endl;
	cout << "----------------------" << endl;
	cout << "Enter any number to return to combat: " << endl;
	int player_Choice = return_Player_Choice();

}


void ship::print_Detailed_Stats() {
	cout << endl;
	cout << "The " << get_Name() << "'s stats" << endl;
	cout << "Health: " << get_Current_Health() << "/" << get_Max_Health() << endl;
	cout << "Energy: " << get_Current_Energy() << "/" << get_Max_Energy() << endl;
	cout << "Evasiveness: " << get_Evasiveness() << "%" << endl;
	cout << "Energy regeneration: 5% to " << get_Energy_Regen() << "%" << endl << endl;
	
}

void print_Stats(ship players_Ship, ship enemy_Ship, vector<artillery>& players_Artillery, vector<artillery>& enemys_Artillery) {
	reset_Status_Displays();
	int player_Name_Length = 30 - players_Ship.get_Name().length();
	int enemy_Name_Length = 34 - enemy_Ship.get_Name().length();
	//int enemy_Name_Length = 30 - enemy_Ship.get_Name().length();
	cout << "The " << players_Ship.get_Name() << "'s stats";
	print_Num_Spaces(player_Name_Length);
	cout << "STATUS EFFECTS:";
	print_Num_Spaces(23);
	cout << "ENEMY STATUS EFFECTS:" << endl;
	cout << "Health: " << players_Ship.get_Current_Health() << "/" << players_Ship.get_Max_Health();
	print_Num_Spaces(27);
	
	if (players_Ship.get_Current_Health() < 10) {
		print_Num_Spaces(2);
	}
	else if (players_Ship.get_Current_Health() < 100) {
		print_Num_Spaces(1);
	}
	
	if (players_Ship.get_Max_Health() < 10) {
		print_Num_Spaces(2);
	}
	else if (players_Ship.get_Max_Health() < 100) {
		print_Num_Spaces(1);
	}
	
	
	cout << "---------------------";
	print_Num_Spaces(17);
	cout << "---------------------" << endl;
	cout << "Energy: " << players_Ship.get_Current_Energy() << "/" << players_Ship.get_Max_Energy();
	print_Num_Spaces(27);

	if (players_Ship.get_Current_Energy() < 10) {
		print_Num_Spaces(2);
	}
	else if (players_Ship.get_Current_Energy() < 100) {
		print_Num_Spaces(1);
	}

	if (players_Ship.get_Max_Energy() < 10) {
		print_Num_Spaces(2);
	}
	else if (players_Ship.get_Max_Energy() < 100) {
		print_Num_Spaces(1);
	}

	print_Current_Statuses(players_Ship, enemy_Ship, players_Artillery, enemys_Artillery, 1);
	cout << "--------------------";
	print_Num_Spaces(22);
	print_Current_Statuses(players_Ship, enemy_Ship, players_Artillery, enemys_Artillery, 2);
	cout << enemy_Ship.get_Name() << "'s stats";
	print_Num_Spaces(enemy_Name_Length);
	print_Current_Statuses(players_Ship, enemy_Ship, players_Artillery, enemys_Artillery, 3);
	cout << "Health: " << enemy_Ship.get_Current_Health() << "/" << enemy_Ship.get_Max_Health();
	if (enemy_Ship.get_Current_Health() < 100) {
		print_Num_Spaces(1);
	}
	else if (enemy_Ship.get_Current_Health() < 10) {
		print_Num_Spaces(2);
	}
	
	if (enemy_Ship.get_Max_Health() < 100) {
		print_Num_Spaces(1);
	}
	else if (enemy_Ship.get_Max_Health() < 10) {
		print_Num_Spaces(2);
	}
	
	
	print_Current_Statuses(players_Ship, enemy_Ship, players_Artillery, enemys_Artillery, 4);
	cout << "Energy: " << enemy_Ship.get_Current_Energy() << "/" << enemy_Ship.get_Max_Energy();
	print_Num_Spaces(27);
	if (enemy_Ship.get_Current_Energy() < 100) {
		print_Num_Spaces(1);
	}
	else if (enemy_Ship.get_Current_Energy() < 10) {
		print_Num_Spaces(2);
	}

	if (enemy_Ship.get_Max_Energy() < 100) {
		print_Num_Spaces(1);
	}
	else if (enemy_Ship.get_Max_Energy() < 10) {
		print_Num_Spaces(2);
	}
	print_Current_Statuses(players_Ship, enemy_Ship, players_Artillery, enemys_Artillery, 5);
	cout << "--------------------                      ---------------------                 ---------------------" << endl;
	
}

//dodging
bool evade(int percent) {
	int evade = random_Number(1, 100);
	if (evade >= percent) {
		return true;
	}
	else {
		return false;
	}
}
void ship::evade_Action(int accuracy) {
	int max_Energy_Regen = get_Energy_Regen();
	double energy_Regen = random_Number(5, max_Energy_Regen);
	energy_Regen = (energy_Regen / 100);
	int energy = get_Max_Energy() * energy_Regen;
	int total_Energy_Regenerated = get_Current_Energy();
	if (get_Disrupted_Status() > 0) {
		cout << "The " << get_Name() << " preformed evasive maneuvers, but was unable to regain energy" 
		<< endl <<  "because its energy generator is disrupted" << endl;
	}
	else {
		for (int i = 0; i < energy && total_Energy_Regenerated < get_Max_Energy(); i++) {
				total_Energy_Regenerated += 1;
			}
		set_Current_Energy(total_Energy_Regenerated);
		bool evaded = evade(accuracy - get_Evasiveness());
		set_Evaded(evaded);
		cout << "The " << get_Name() <<
		" preformed evasive maneuvers and recovered some energy" << endl;
	}
	
	//
	


}


//input from player and enemy and using that input
void artillery::print_Combat_Info(int num) {
	
	cout << "--------------------" << endl;
	cout << (num + 1) << ") " << get_Name() << endl;

	cout << "Damage: " << get_Damage() << endl;
	cout << "Accuracy: " << get_Accuracy() << "%" << endl;
	cout << "Attack speed: " << get_Attack_Speed() << endl;
	cout << "Energy cost: " << get_Energy_Cost() << endl;
	cout << "Available ammo: " << get_Current_Uses() << "/" << get_Max_Uses() << endl;
}
void print_Player_Options(ship players_Ship, std::vector<artillery> players_Artillery) {
	cout << "Enter a number to fire the corresponding artillery, or press 0 to regain some energy and increase your chances to dodge an attack" << endl;
	cout << "Press " << players_Artillery.size() + 1 << " to bring up the status codex" << endl;
	for (int i = 0; i < players_Artillery.size(); i++){
		cout << "------------------";
		print_Num_Spaces(6);
	}
	cout << endl;
	for (int i = 0; i < players_Artillery.size(); i++) {
		cout << (i + 1) << ") " << players_Artillery[i].get_Name();
		int space = 21 - players_Artillery[i].get_Name().length();
		for (int j = 0; j < space; j++) {
			cout << " ";
		}
	}
	cout << endl;
	for (int i = 0; i < players_Artillery.size(); i++) {
		cout << "Damage: " << players_Artillery[i].get_Damage();
		print_Num_Spaces(14);
	}
	cout << endl;
	for (int i = 0; i < players_Artillery.size(); i++) {
		cout << "Accuracy: " << players_Artillery[i].get_Accuracy() << "%";
		print_Num_Spaces(11);

	}
	cout << endl;
	for (int i = 0; i < players_Artillery.size(); i++) {
		cout << "Energy cost: " << players_Artillery[i].get_Energy_Cost();
		if (players_Artillery[i].get_Energy_Cost() < 10) {
			print_Num_Spaces(10);
		}
		else {
			print_Num_Spaces(9);
		}
	}
	cout << endl;
	for (int i = 0; i < players_Artillery.size(); i++) {
		cout << "Attack speed: " << players_Artillery[i].get_Attack_Speed();
		print_Num_Spaces(8);
	}
	cout << endl;
	for (int i = 0; i < players_Artillery.size(); i++) {
		cout << "Available ammo: " << players_Artillery[i].get_Current_Uses() << "/" << players_Artillery[i].get_Max_Uses();
		print_Num_Spaces(3);
		if (players_Artillery[i].get_Max_Uses() < 10) {
			print_Num_Spaces(1);
		}
		if (players_Artillery[i].get_Current_Uses() < 10) {
			print_Num_Spaces(1);
		}
	}
	cout << endl;
	for (int i = 0; i < players_Artillery.size(); i++) {
		// std::string sub = str.substr(7, 5);
		cout << "Ability:";
		int space = 16 - players_Artillery[i].get_Ability_Name().length();
		cout << players_Artillery[i].get_Ability_Name();
		for (int j = 0; j < space; j++) {
			cout << " ";
		}
	}
	cout << endl;
	

}

int read_User_Input(ship& players_Ship, vector<artillery>& players_Artillery) {
	bool valid = false;
	int player_Choice = return_Player_Choice();
	if (players_Ship.get_Stun_Status() <= 0) {
		while (!valid) {
			if (player_Choice == 0 || player_Choice == players_Artillery.size() + 1) {
				valid = true;
				return (player_Choice - 1);
			}
			else if (player_Choice > 0 && player_Choice <= players_Artillery.size()) {
				if (players_Ship.get_Current_Energy() >= players_Artillery[player_Choice - 1].get_Energy_Cost()) {
					if (players_Artillery[player_Choice - 1].get_Current_Uses() > 0) {
						if (!players_Artillery[player_Choice - 1].get_Overheat_Status()) {
							valid = true;
							int uses_Remaining = players_Artillery[player_Choice - 1].get_Current_Uses() - 1;
							players_Artillery[player_Choice - 1].set_Current_Uses(uses_Remaining);
							int energy_Remaining = players_Ship.get_Current_Energy() - players_Artillery[player_Choice - 1].get_Energy_Cost();
							players_Ship.set_Current_Energy(energy_Remaining);
							return (player_Choice - 1);
						}
						else {
							cout << "This weapon has been overheated, and is not operable" << endl;
							player_Choice = return_Player_Choice();
						}

					}
					else {
						cout << "You do not have enough ammo" << endl;
						player_Choice = return_Player_Choice();
					}
				}
				else {
					cout << "You do not have enough energy to fire this weapon" << endl;
					player_Choice = return_Player_Choice();
				}
			}
			else {
				cout << "Invalid, please try again" << endl;
				player_Choice = return_Player_Choice();
			}
		}
	}
	else {
		cout << "Your ship's operating system has been stunned" << endl;
		valid = true;
		press_X_To_Continue();
		return -2;
		
	}

}
void user_Action(int player_Choice, ship& players_Ship, vector<artillery>& players_Artillery, ship& enemy_Ship) {
	int num_Turns;
	int percent = players_Artillery[player_Choice].get_Percent();
	if (player_Choice >= 0) {
		if (enemy_Ship.get_Evaded() == false && evade(players_Artillery[player_Choice].get_Accuracy() == false)) {
			int damage_Dealt = players_Artillery[player_Choice].get_Damage();
			if (enemy_Ship.get_Weaken_Status() > 0) {
				damage_Dealt *= 1.5;
			}
			int remaining_Health = enemy_Ship.get_Current_Health() - damage_Dealt;
			enemy_Ship.set_Current_Health(remaining_Health);

			cout << "You fired your " << players_Artillery[player_Choice].get_Name() << " and dealt " << damage_Dealt << " damage" << endl;

			if (players_Artillery[player_Choice].get_Can_Corrode()) {
				if (can_Apply_Corrosion_Status(percent) > 0) {
					enemy_Ship.set_Corrosion_Status();
					cout << "and you also inflicted corrosion on the " << enemy_Ship.get_Name() << endl;
				}

			}
			else if (players_Artillery[player_Choice].get_Can_Weaken()) {
				if (can_Apply_Weakened_Status(percent) > 0) {
					num_Turns = random_Number(2, 3);
					enemy_Ship.set_Weaken_Status(num_Turns);
					cout << "and you also weakened the " << enemy_Ship.get_Name() << "'s hull" << endl;
				}
			}
			else if (players_Artillery[player_Choice].get_Can_Stun()) {
				if (can_Apply_Stun_Status(percent) > 0) {
					enemy_Ship.set_Stun_Status(2);
					cout << "and you also stunned the " << enemy_Ship.get_Name() << "'s operating systems" << endl;
				}
			}
			else if (players_Artillery[player_Choice].get_Can_Disrupt()) {
				if (can_Apply_Disrupted_Status(percent) > 0) {
					num_Turns = random_Number(5, 6);
					enemy_Ship.set_Disrupted_Status(num_Turns);
					cout << "and you also disrupted the " << enemy_Ship.get_Name() << "'s energy generator" << endl;
				}
			}
		}
		else {
			cout << "You fired your " << players_Artillery[player_Choice].get_Name() << ", however the " << enemy_Ship.get_Name() << " was able to dodge it" << endl;
			enemy_Ship.set_Evaded(false);
		}
		if (players_Artillery[player_Choice].get_Can_Overheat()) {
			if (players_Artillery[player_Choice].can_Apply_Overheat_Status(percent) > 0) {
				num_Turns = random_Number(2, 3);
				players_Artillery[player_Choice].set_Overheat_Status(num_Turns);
				cout << "however, this weapon has overheated and will not be operable for the next " << num_Turns - 1 << " turns" << endl;
			}

		}
	}
}
int read_Enemy_Input(ship& enemy_Ship, vector<artillery>& enemys_Artillery, ship& players_Ship) {
	bool valid = false;
	int enemy_Choice;

	while (!valid) {
		int max = 0;
		int max_I;
		if (players_Ship.get_Weaken_Status() > 0 || players_Ship.get_Stun_Status() > 0) {
			for (int i = 0; i < enemys_Artillery.size(); i++){
				
				if (enemys_Artillery[i].get_Damage() > max) {
					max_I = i;
					max = enemys_Artillery[i].get_Damage();
				}
			}
			enemy_Choice = max_I;
		}
		else {
			enemy_Choice = random_Number(0, (enemys_Artillery.size() - 1));
		}
		
		
		
		if (enemys_Artillery[enemy_Choice].get_Energy_Cost() <= enemy_Ship.get_Current_Energy() && enemys_Artillery[enemy_Choice].get_Current_Uses() > 0 && enemys_Artillery[enemy_Choice].get_Overheat_Status() <= 0) {
			
			int uses_Remaining = enemys_Artillery[enemy_Choice].get_Current_Uses() - 1;
			enemys_Artillery[enemy_Choice].set_Current_Uses(uses_Remaining);

			//cout << enemy_Ship.get_Current_Energy() << " " << enemys_Artillery[enemy_Choice].get_Energy_Cost() << " ";
			int energy_Remaining = enemy_Ship.get_Current_Energy() - enemys_Artillery[enemy_Choice].get_Energy_Cost();
			enemy_Ship.set_Current_Energy(energy_Remaining);
			//cout << enemy_Ship.get_Current_Energy();

			valid = true;
		}
		else {
			valid = false;
			for (int i = 0; i < enemys_Artillery.size()-1; i++) {
				if (enemys_Artillery[i].get_Energy_Cost() <= enemy_Ship.get_Current_Energy() && enemys_Artillery[i].get_Current_Uses() > 0 && enemys_Artillery[i].get_Overheat_Status() <= 0) {

					enemy_Choice = i; 
					int uses_Remaining = enemys_Artillery[enemy_Choice].get_Current_Uses() - 1;
					enemys_Artillery[enemy_Choice].set_Current_Uses(uses_Remaining);

					int energy_Remaining = enemy_Ship.get_Current_Energy() - enemys_Artillery[enemy_Choice].get_Energy_Cost();
					enemy_Ship.set_Current_Energy(energy_Remaining);
					valid = true;
					break;
				}
			}
			
			if (!valid) {
				enemy_Choice = -1;
				valid = true; // Exit the loop
			}
		}
	}

	return enemy_Choice;
}
void enemy_Action(int enemy_Choice, ship& players_Ship, ship& enemy_Ship, vector<artillery>& enemys_Artillery) {
	int percent = enemys_Artillery[enemy_Choice].get_Percent();
	int num_Turns;
	if ((players_Ship.get_Evaded() == false) && (evade(enemys_Artillery[enemy_Choice].get_Accuracy() == false))) {
		int damage_Dealt = enemys_Artillery[enemy_Choice].get_Damage();
		if (players_Ship.get_Weaken_Status() > 0) {
			damage_Dealt *= 1.5;
		}
		int remaining_Health = players_Ship.get_Current_Health() - damage_Dealt;
		players_Ship.set_Current_Health(remaining_Health);
		cout << "The " << enemy_Ship.get_Name() << " fired their " << enemys_Artillery[enemy_Choice].get_Name()
		<< " and dealt " << damage_Dealt << " damage " << endl;
		if (enemys_Artillery[enemy_Choice].get_Can_Corrode()) {
			if (can_Apply_Corrosion_Status(percent) > 0) {
				players_Ship.set_Corrosion_Status();
				cout << "they also have inflicted corrosion upon the " << players_Ship.get_Name() << endl;
			}

		}
		else if (enemys_Artillery[enemy_Choice].get_Can_Weaken()) {
			if (can_Apply_Weakened_Status(percent) > 0) {
				num_Turns = random_Number(1, 2);
				players_Ship.set_Weaken_Status(num_Turns);
				cout << "the " << enemy_Ship.get_Name() << " has also weakened your hull" << endl;
			}
		}
		else if (enemys_Artillery[enemy_Choice].get_Can_Stun()) {
			if (can_Apply_Stun_Status(percent) > 0) {
				players_Ship.set_Stun_Status(2);
				cout << "the " << enemy_Ship.get_Name() << " stunned your ship's operating system" << endl;
			}
		}
		
		else if (enemys_Artillery[enemy_Choice].get_Can_Disrupt()) {
			if (can_Apply_Disrupted_Status(percent) > 0) {
				num_Turns = random_Number(3, 5);
				players_Ship.set_Disrupted_Status(num_Turns);
				cout << "the " << enemy_Ship.get_Name() << " disrupted your energy generator" << endl;
			}
		}
	}
	else {
		cout << "The " << enemy_Ship.get_Name() << " fired their " << enemys_Artillery[enemy_Choice].get_Name()
		<< ", but your ship managed to evade it " << endl;
		players_Ship.set_Evaded(false);
	}
	if (enemys_Artillery[enemy_Choice].get_Can_Overheat()) {
		if (enemys_Artillery[enemy_Choice].can_Apply_Overheat_Status(percent) > 0) {
			num_Turns = random_Number(2, 3);
			enemys_Artillery[enemy_Choice].set_Overheat_Status(num_Turns);
			cout << "however, the " << enemy_Ship.get_Name() << "'s " << enemys_Artillery[enemy_Choice].get_Name() << " overheated" << endl;
		}
	}
}





// players ship, players artillery, players inventory, enemy level, enemy ship, enemy's artillery
int combat(ship& players_Ship, vector<artillery>& players_Artillery, int players_Inventory[], int enemy_Level, ship& enemy_Ship, vector<artillery>& enemys_Artillery) {
	players_Ship.set_Current_Energy(players_Ship.get_Max_Energy());

	while (enemy_Ship.get_Current_Health() > 0) {
		if (players_Ship.get_Current_Health() > 0) {
			bool player_Choice_Loop = false;
			int player_Choice;
			
			while (!player_Choice_Loop) {
				print_Stats(players_Ship, enemy_Ship, players_Artillery, enemys_Artillery);
				print_Player_Options(players_Ship, players_Artillery);
				player_Choice = read_User_Input(players_Ship, players_Artillery);

				if (player_Choice == players_Artillery.size()) {
					system("cls");
					status_Codex();
					system("cls");
				}
				else {
					player_Choice_Loop = true;
				}
			}
			int enemy_Choice = read_Enemy_Input(enemy_Ship, enemys_Artillery, players_Ship);
			int players_Artillery_Accuracy = 0;
			int enemys_Artillery_Accuracy  = 0;
			if (player_Choice > -1) {
				players_Artillery_Accuracy = players_Artillery[player_Choice].get_Accuracy();
			}
			if (enemy_Choice > -1) {
				enemys_Artillery_Accuracy = enemys_Artillery[enemy_Choice].get_Accuracy();
			}
			if (player_Choice == -2 ^ enemy_Choice == -2) {
				if (enemy_Ship.get_Current_Health() > 0) {
					if (enemy_Choice > -1) {
						enemy_Action(enemy_Choice, players_Ship, enemy_Ship, enemys_Artillery);
						press_X_To_Continue_And_Clear();
					}
					else if (enemy_Choice == -1) {
						enemy_Ship.evade_Action(players_Artillery_Accuracy);
						press_X_To_Continue_And_Clear();
					}
					if (player_Choice > -1) {
						user_Action(player_Choice, players_Ship, players_Artillery, enemy_Ship);
						press_X_To_Continue_And_Clear();
					}
					else if (player_Choice == -1) {
						players_Ship.evade_Action(enemys_Artillery_Accuracy);
						press_X_To_Continue_And_Clear();
					}
					
				}
			}
			else if (player_Choice == -2 && enemy_Choice == -2){
				cout << "Both you and the " << enemy_Ship.get_Name() << " have been stunned, and neither of you could take any actions" << endl;
				press_X_To_Continue_And_Clear();
			}
			else if (enemy_Choice == -1 || player_Choice == -1) {
				bool first_Evade = false;
				if (player_Choice == -1) {
					players_Ship.evade_Action(0);
					press_X_To_Continue();
					first_Evade = true;
				}
				if (enemy_Choice == -1) {
					enemy_Ship.evade_Action(0);
					if (first_Evade) {
						press_X_To_Continue_And_Clear();
					}
					else {
						press_X_To_Continue();

					}
				}
				if (player_Choice > -1) {
					user_Action(player_Choice, players_Ship, players_Artillery, enemy_Ship);
					press_X_To_Continue_And_Clear();
				}
				if (enemy_Choice > -1) {
					enemy_Action(enemy_Choice, players_Ship, enemy_Ship, enemys_Artillery);
					press_X_To_Continue_And_Clear();
				}
			}
			
			else if (enemys_Artillery[enemy_Choice].get_Attack_Speed() > players_Artillery[player_Choice].get_Attack_Speed()){
				cout << "The enemy's weapon speed was faster than yours, so they attacked you first" << endl;
				press_X_To_Continue();
				enemy_Action(enemy_Choice, players_Ship, enemy_Ship, enemys_Artillery);
				press_X_To_Continue();
				if (players_Ship.get_Current_Health() > 0) {
					if (players_Ship.get_Stun_Status() <= 0) {
						user_Action(player_Choice, players_Ship, players_Artillery, enemy_Ship);
						press_X_To_Continue_And_Clear();
					}
					else {
						cout << "The enemy stunned you before you could attack, so you were unable to fire any of your artillery" << endl;
						press_X_To_Continue_And_Clear();
					}
				}
			}
			else {
				user_Action(player_Choice, players_Ship, players_Artillery, enemy_Ship);
				press_X_To_Continue();
				if (enemy_Ship.get_Current_Health() > 0) {
					if (enemy_Ship.get_Stun_Status() <= 0) {
						enemy_Action(enemy_Choice, players_Ship, enemy_Ship, enemys_Artillery);
						press_X_To_Continue_And_Clear();
					}
					else {
						cout << "You stunned the enemy before they were able to attack" << endl;
						press_X_To_Continue_And_Clear();
					}
					
				}
			}
			status_Effect_Actions(enemy_Ship, enemys_Artillery);
			system("cls");
			status_Effect_Actions(players_Ship, players_Artillery);
			system("cls");
		}
		else {
			cout << "GAME OVER, YOU DIED" << endl;
			exit(0);
		}
	}
	win_Screen();
	drop_Items(enemy_Level, players_Inventory);
	return 0;
  }

//depot
void add_Artillery1(vector<artillery>& artillery_Vector) {
	artillery_Vector.push_back(artillery("Stasis Cannon", 25, 85, 95, 15, 10, false, true, false, false, false, 40, 0, "40% to stun"));
}
void add_Artillery2(vector<artillery>& artillery_Vector) {
	
	artillery_Vector.push_back(artillery("Graviton Corroder", 40, 75, 30, 15, 20, true, false, false, false, false, 30, 1, "30% to corrosion"));
}
void add_Artillery3(vector<artillery>& artillery_Vector) {
	artillery_Vector.push_back(artillery("Void Piercer", 20, 115, 95, 10, 15, false, false, true, false, false, 65, 2, "65% to weaken"));
}
void add_Artillery4(vector<artillery>& artillery_Vector) {
	artillery_Vector.push_back(artillery("Energy Ripper", 65, 75, 15, 5, 35, false, false, false, false, true , 35, 3, "35% to disrupt"));
}



void display_Price(int price[]) {
	cout << " \tPRICE: ";
	bool first = false;
	for (int j = 0; j < 4; j++) {
		if (price[j] > 0) {
			if (first) {
				cout << "\t       ";
			}
			cout << price[j];
			if (j == 0) {
				first = true;
				//cout << price[j];
				cout << " Stellar debris" << endl;
			}
			if (j == 1) {
				first = true;
				cout << " Nebula shard(s)" << endl;
			}
			if (j == 2) {
				first = true;
				//cout << price[j];
				cout << " Quantum core(s)" << endl;
			}
			if (j == 3) {
				first = true;
				//cout << price[j];
				cout << " Dark matter essence(s)" << endl;
			}
		}
	}
}
void wipe_Price(int price[]) {
	for (int i = 0; i < 4; i++) {
		price[i] = 0;
	}
}

int generate_Price(int num, int multiplier, int minus) {
	num = minus - num;
	int old_Num = num / 2;
	num *= multiplier;
	num += old_Num;



	return num;
}
int* generate_Upgade_Price(int num, int price[]) {
	//num = 4 - num;
	for (int i = 0; i < 4 && i < num + 1; i++) {
		price[i] = (3 - i) * 2 + 1;
	}
	if (num == 4) {
		wipe_Price(price);
		price[3] = 2;
	}
	return price;
}
void purchase(int price[], int player_Inventory[]) {
	for (int i = 0; i < 4; i++) {
		if (price[i] > 0) {
			player_Inventory[i] -= price[i];
		}
	}
}
bool validate_Purchase(int price[], int player_Inventory[]) {
	for (int i = 0; i < 4; i++){
		if (price[i] > player_Inventory[i]) {
			
			return false;
		}
	}
	return true;
}

int depot_Options() {
	bool valid = false;
	system("cls");
	cout << "STARSHIP DEPOT" << endl;
	cout << "----------------------------------------------------" << endl;
	cout << "Welcome to the Starship Depot,where your ship's journey" << endl
	<< "begins again! Let's get you powered up and ready for the" << endl 
	<< "stars" << endl;
	cout << "----------------------------------------------------" << endl;
	cout << "What do you want to do? If you wish to leave enter 0" << endl;
	cout << "0. LEAVE" << endl;
	cout << "1.Upgrade ship " << endl;
	cout << "2.Purchase new artillery" << endl;
	cout << "3.Repair ship" << endl;
	cout << "4.Restock ammo" << endl;
	
	int player_Choice;
	while (!valid) {
		player_Choice = return_Player_Choice();
		if (player_Choice >= 0 && player_Choice < 5) {
			return player_Choice;
		}
		else {
			cout << "Invalid, please try again" << endl;
		}
	}
	return player_Choice;
}

int ship::upgrade_Options(int player_Inventory[]) {
	
	system("cls");
	bool valid = false;
	//int price[4] = { 0, 0, 0, 0 };
	int* price = new int[4];
	cout << "Here are the upgrade options for your ship, or enter 0 to go back" << endl;
	cout << "0. BACK" << endl;
	cout << "1. Hull:";
	if (get_Hull_Level() < 5) {
		cout << " Improves the ship's health by 25"  << endl;
		price = generate_Upgade_Price(get_Hull_Level(), price);
		display_Price(price);
		wipe_Price(price);
	}
	else {
		cout << " MAX LEVEL" << endl;
	}
	cout << "2. Engines:";
	if (get_Engines_Level() < 5) {
		cout << " Increases the ship's evasiveness by 10%" << endl;
		price = generate_Upgade_Price(get_Engines_Level(), price);
		display_Price(price);
		wipe_Price(price);
	}
	else {
		cout << " MAX LEVEL" << endl;
	}
	cout << "3. Ammo reserves:";
	if (get_Ammo_Reserves_Level() < 5) {
		cout << " Improves the ammo capacity of all your artillery by 20%" << endl;
		price = generate_Upgade_Price(get_Ammo_Reserves_Level(), price);
		display_Price(price);
		wipe_Price(price);
	}
	else {
		cout << " MAX LEVEL" << endl;
	}
	cout << "4. Power core:";
	if (get_Power_Core_Level() < 5) {
		cout << " Increases the ship's energy capacity by 20" << endl;
		
		price = generate_Upgade_Price(get_Power_Core_Level(), price);
		display_Price(price);
		wipe_Price(price);
	}
	else {
		cout << " MAX LEVEL" << endl;
	}
	cout << "5. Nuclear reactor:";
	if (get_Nuclear_Reactor_Level() < 5) {
		cout << " Improves the ship's energy regeneration by 10%" << endl;
		
		price = generate_Upgade_Price(get_Nuclear_Reactor_Level(), price);
		display_Price(price);
		wipe_Price(price);
	}
	else {
		cout << " MAX LEVEL" << endl;
	}
	print_Detailed_Stats();
	print_Inventory(player_Inventory);
	int player_Choice = 0;
	while (!valid) {
		player_Choice = return_Player_Choice();
		int* all_Upgrade_Levels = get_All_Levels();
		price = generate_Upgade_Price(all_Upgrade_Levels[player_Choice - 1], price);
		if (player_Choice <= 5 && player_Choice > 0) {
			if (all_Upgrade_Levels[player_Choice - 1] < 5) {

				if (validate_Purchase(price, player_Inventory)) {
					purchase(price, player_Inventory);
					valid = true;
					return player_Choice;
				}
				else {
					cout << "You do not have enough recourses to purchase this" << endl;
				}
				
			}
			else {
				cout << "This upgrade is max level" << endl;
			}
			
		}
		else if (player_Choice == 0) {
			valid = true;
			return player_Choice;
		}
		else {
			cout << "Invalid input, please try again" << endl;
		}
	}

}
int artillery_Options( vector<artillery>& players_Artillery, vector<artillery>& artillery_For_Purchase, int player_Inventory[]) {
	system("cls");
	cout << "Here are the artillery to purchase, or enter 0 to go back" << endl;
	cout << "0. BACK" << endl;
	int price[4] = {0, 0, 0, 0};
	if (artillery_For_Purchase.size() > 0) {
		for (int i = 0; i < artillery_For_Purchase.size(); i += 1) {
			cout << i + 1 << ". ";
			int quality = artillery_For_Purchase[i].get_Ammo_Quality();
			price[quality] = generate_Price(quality, 2, 4);
			cout << artillery_For_Purchase[i].get_Name() << "\n" << "Damage:" << artillery_For_Purchase[i].get_Damage()
				<< "\nAccuracy:" << artillery_For_Purchase[i].get_Accuracy() << "\nAttack speed:" << artillery_For_Purchase[i].get_Attack_Speed() << "\nAmmo capacity:" << artillery_For_Purchase[i].get_Max_Uses() << "\nEnergy cost:" << artillery_For_Purchase[i].get_Energy_Cost()
				<< "\nAbility:" << artillery_For_Purchase[i].get_Ability_Name() << "\n----------------------" << endl;
			cout << "PRICE: " << endl;
			display_Price(price);
			cout << "----------------------" << endl;
			wipe_Price(price);
		}
	}
	else {
		cout << "NO ARTILLERY FOR SALE" << endl;
	}
	bool valid = false;
	print_Inventory(player_Inventory);
	int player_Choice = 0;
	while (!valid) {
		player_Choice = return_Player_Choice();
		if ((player_Choice <= artillery_For_Purchase.size() && player_Choice > 0)) {
			wipe_Price(price);
			int quality = artillery_For_Purchase[player_Choice - 1].get_Ammo_Quality();
			price[quality] = generate_Price(quality, 2, 4);
			if (validate_Purchase(price, player_Inventory)) {
				purchase(price, player_Inventory);
				valid = true;
				return player_Choice;
			}
			else {
				cout << "You do not have enough recourses to purchase this" << endl;
			}
		}
		else if (player_Choice == 0) {
			valid = true;
			return player_Choice;
		}
		else {
			cout << "Invalid input, please try again" << endl;
		}
		
	}
	
	return player_Choice;
}
int ship::heal_Options(int player_Inventory[]) {
	system("cls");
	int price[4];
	int max_Repair_Teir = 0;
	int repair_Teirs[6] = { 10, 25, 40, 60, 85, 100 };
	cout << "Your ship's condition:" << endl;
	cout << "Health: " << get_Current_Health() << "/" << get_Max_Health() << endl;
	int missing_Health = get_Max_Health() - get_Current_Health();
	cout << "0. BACK" << endl;
	if (missing_Health >= repair_Teirs[0]) {
		for (int i = 0; i < 6 && missing_Health >= repair_Teirs[i]; i++) {
			max_Repair_Teir = i + 1;
			if (i < 3) {
				price[i / 3] = ((i + 1) * 2);
			}
			else {
				price[i / 3] = (((i+1) - 3) * 2) + 1;
			}
			cout << 1 + i << ".";
			if (i == 0) {
				cout << "Hull patch (10 Health)";
			}
			else if (i == 1) {
				cout << "System tune-up (25 Health)";
			}
			else if (i == 2) {
				cout << "Structural restoration (40 Health)";
			}
			else if (i == 3) {
				cout << "Critical system rebuild (60 Health)";
			}
			else if (i == 4) {
				cout << "Full hull rebuild (85 Health)";
				
			}
			else if (i == 5) {
				cout << "Complete overhaul (100 Health)";
			}
			cout << endl;
			
			display_Price(price);
			cout << "----------------------" << endl;
			wipe_Price(price);
		}
	
	}
	else {
		cout << "THE SHIP IS IN GREAT CONDITION, NO REPAIRS NEEDED" << endl;
	}


	print_Inventory(player_Inventory);
	bool valid = false;
	
	int player_Choice;
	while (!valid) {
		player_Choice = return_Player_Choice();
		if ((player_Choice <= max_Repair_Teir && player_Choice > 0)) {
			wipe_Price(price);
			if (player_Choice <= 3) {
				price[((player_Choice - 1) / 3)] = ((player_Choice)  * 2);
			}
			else {
				price[((player_Choice - 1) / 3)] = ((player_Choice - 3) * 2) + 1;
			}
			
			if (validate_Purchase(price, player_Inventory)) {
				purchase(price, player_Inventory);
				valid = true;
				return repair_Teirs[player_Choice - 1];
			}
			else {
				cout << "You do not have enough recourses to purchase this" << endl;
			}
		}
		else if (player_Choice == 0) {
			valid = true;
			return player_Choice;
		}
		else {
			cout << "Invalid input, please try again" << endl;
		}

	}

	return player_Choice;
}
int ammo_Options(vector<artillery>& players_Artillery, int player_Inventory[]) {
	system("cls");
	int player_Choice;
	bool valid = false;
	int price[4];
	int missing_Ammo = 0;
	double accurate_Price;
	cout << "Which artillery would you like to purchase ammo for, or press 0 to go back" << endl;
	cout << "0. BACK" << endl;
	for (int i = 0; i < players_Artillery.size(); i++){
		cout << i + 1 << ". " << players_Artillery[i].get_Name() << " ammunition " << endl;
		missing_Ammo = players_Artillery[i].get_Max_Uses() - players_Artillery[i].get_Current_Uses();
		accurate_Price = missing_Ammo / (2.00 + players_Artillery[i].get_Ammo_Quality());
		if (accurate_Price > 0 && accurate_Price < 1) {
			accurate_Price = 1;
		}
		price[players_Artillery[i].get_Ammo_Quality()] = accurate_Price;
		display_Price(price);
		wipe_Price(price);
		if (players_Artillery[i].get_Current_Uses() == players_Artillery[i].get_Max_Uses()) {
			cout << "FULL" << endl;
		}
		cout << "----------------------" << endl;
	}
	print_Inventory(player_Inventory);
	while (!valid) {
		player_Choice = return_Player_Choice();
		if (player_Choice > 0 && player_Choice <= players_Artillery.size()) {
			missing_Ammo = players_Artillery[player_Choice-1].get_Max_Uses() - players_Artillery[player_Choice-1].get_Current_Uses();
			if (players_Artillery[player_Choice - 1].get_Ammo_Quality() == 0) {
				price[players_Artillery[player_Choice-1].get_Ammo_Quality()] = missing_Ammo / 2;
			}
			else if (players_Artillery[player_Choice - 1].get_Ammo_Quality() == 1) {
				price[players_Artillery[player_Choice-1].get_Ammo_Quality()] = missing_Ammo / 3;
			}
			else if (players_Artillery[player_Choice - 1].get_Ammo_Quality() == 2) {
				price[players_Artillery[player_Choice-1].get_Ammo_Quality()] = missing_Ammo / 4;
			}
			else if (players_Artillery[player_Choice - 1].get_Ammo_Quality() == 3) {
				price[players_Artillery[player_Choice-1].get_Ammo_Quality()] = missing_Ammo / 5;
			}
			if (price[players_Artillery[player_Choice - 1].get_Ammo_Quality()] == 0) {
				price[players_Artillery[player_Choice - 1].get_Ammo_Quality()] = 1;
			}
			if (validate_Purchase(price, player_Inventory)) {
				purchase(price, player_Inventory);
				valid = true;
				return player_Choice;
			}
			else {
				cout << "You do not have enough recourses to purchase this" << endl;
			}
			
		}
		else if (player_Choice == 0) {
			return player_Choice;
		}
		else {
			cout << "Invalid input, try again" << endl;
		}
	}


	return player_Choice;
}

//star ship depot
int starship_Depot(ship& players_Ship, vector<artillery>& players_Artillery, vector<artillery>& artillery_For_Purchase, int player_Inventory[]) {
	bool done = false;
	cout << "Guided in by automated systems, your ship settled onto the docking bay with a heavy clang. " 
	<< endl << "Mechanics and repair arms spring into action, a crew member giving you a quick nod before assessing the damage." << endl;
	press_X_To_Continue();
	/*
	The last sparks of the pirate ship faded behind you, and your battered vessel rattled, systems flashing warnings of low fuel and hull breaches. After what felt like hours, a flicker of light appeared in the distance—a starship depot. Relief washed over you.
*/
	cout << "You've docked at a Starship Depot!" << endl 
	<<  "Time to give your ship some love. Repair, upgrade, and stock up on new" << endl 
	<< "artillery to keep your journey smooth and your enemies at bay " << endl;
	press_X_To_Continue();
	while (!done) {
		//hull, engines, ammo reserves, power core, nuclear reactor
		int player_Choice = depot_Options();
		if (player_Choice == 0) {
			done = true;
		}
		if (player_Choice == 1) {
			int upgrade_Option = players_Ship.upgrade_Options(player_Inventory);
			while (upgrade_Option > 0) {
				if (upgrade_Option == 1) {
					players_Ship.set_Hull_Level(players_Ship.get_Hull_Level() + 1);
					players_Ship.set_Max_Health(players_Ship.get_Max_Health() + 25);
					for (int i = 0; i < 15 && players_Ship.get_Current_Health() < players_Ship.get_Max_Health(); i++) {
						players_Ship.set_Current_Health(players_Ship.get_Current_Health() + 1);
					}
					cout << "Your health was increased by 25!" << endl;
					press_X_To_Continue_And_Clear();
					
				}
				else if (upgrade_Option == 2) {
					players_Ship.set_Engines_Level(players_Ship.get_Engines_Level() + 1);
					players_Ship.set_Evasiveness(players_Ship.get_Evasiveness() + 10);
					cout << "Your evasiveness was increased by +10%" << endl;
					press_X_To_Continue_And_Clear();
				}
				else if (upgrade_Option == 3) {
					players_Ship.set_Ammo_Reserves_Level(players_Ship.get_Ammo_Reserves_Level() + 1);
					for (int i = 0; i < players_Artillery.size(); i++) {
						double increase = players_Artillery[i].get_Max_Uses() * .2;
						if (increase < 1) {
							increase = 1;
						}
						int new_Max = increase;
						players_Artillery[i].set_Max_Uses(players_Artillery[i].get_Max_Uses() + new_Max);
						for (int j = 0; j < new_Max && players_Artillery[i].get_Current_Uses() < players_Artillery[i].get_Max_Uses(); j++) {
							players_Artillery[i].set_Current_Uses(players_Artillery[i].get_Current_Uses() + 1);
						}
					}
					cout << "All your ammo reserves were increased by 10%!" << endl;
					press_X_To_Continue_And_Clear();
				}
				else if (upgrade_Option == 4) {
					bool filled = true;
					if (players_Ship.get_Current_Energy() < players_Ship.get_Max_Energy()) {
						filled = false;
					}
					players_Ship.set_Power_Core_Level(players_Ship.get_Power_Core_Level() + 1);
					players_Ship.set_Max_Energy(players_Ship.get_Max_Energy() + 20);
					cout << "Your energy capacity was increased by 20!" << endl;
					if (!filled) {
						cout << "We also topped off your energy for you! You're good to go" << endl;
					}
					press_X_To_Continue_And_Clear();
				}
				else if (upgrade_Option == 5) {
					players_Ship.set_Nuclear_Reactor_Level(players_Ship.get_Nuclear_Reactor_Level() + 1);
					players_Ship.set_Energy_Regen(players_Ship.get_Energy_Regen() + 10);
					cout << "Your energy regeneration was increased by +10%" << endl;
					press_X_To_Continue_And_Clear();
				}
				upgrade_Option = players_Ship.upgrade_Options(player_Inventory);
			}
		}
		if (player_Choice == 2) {
			int artillery_Option = artillery_Options(players_Artillery, artillery_For_Purchase, player_Inventory);
			while (artillery_Option > 0) {
					cout << "You purchased the " << artillery_For_Purchase[artillery_Option - 1].get_Name() << "!" << endl;
					press_X_To_Continue_And_Clear();
					players_Artillery.push_back(artillery_For_Purchase[artillery_Option - 1]);
					artillery_For_Purchase.erase(artillery_For_Purchase.begin() + (artillery_Option - 1));
					artillery_Option = artillery_Options(players_Artillery, artillery_For_Purchase, player_Inventory);
			}
		}
		if (player_Choice == 3) {
			int heal_Option = players_Ship.heal_Options(player_Inventory);
			while (heal_Option > 0) {
				for (int i = 0; i < heal_Option && players_Ship.get_Current_Health() < players_Ship.get_Max_Health(); i++) {
					players_Ship.set_Current_Health(players_Ship.get_Current_Health() + 1);
				}
				cout << "You repaired your ship for " << heal_Option << " health!" << endl;
				players_Ship.cure_Corrosive();
				press_X_To_Continue_And_Clear();
				heal_Option = players_Ship.heal_Options(player_Inventory);
			}
			
		}
		if (player_Choice == 4) {
			int ammo_Option = ammo_Options(players_Artillery, player_Inventory);
			while (ammo_Option > 0){
				for (int i = 0;  players_Artillery[ammo_Option - 1].get_Current_Uses() < players_Artillery[ammo_Option - 1].get_Max_Uses(); i++){
					int ammo = players_Artillery[ammo_Option - 1].get_Current_Uses() + 1;
					players_Artillery[ammo_Option - 1].set_Current_Uses(ammo);
				}
				cout << "The ammo for your " << players_Artillery[ammo_Option - 1].get_Name() << " was refilled" << endl;
				press_X_To_Continue_And_Clear();
				ammo_Option = ammo_Options(players_Artillery, player_Inventory);
			}
		}
	}
	cout << "May your thrusters stay strong and your shields hold steady." << endl
	<< "Come back if you need a tune - up!" << endl;
	press_X_To_Continue_And_Clear();
	system("cls");
	return 0;
}

string pick_Name() {
	string user_Name;
	cout << "What do you want to name your vessel: " << endl;
	getline(cin, user_Name);
	system("cls");
	return user_Name;
}

void story_Part1() {
	//  (OpenAI, 2024)
	cout << "The dim lights of your cockpit flicker, a harsh reminder of your ship's fragility." << endl;
	press_X_To_Continue();
	cout << "Once, you might have scoffed at flying in such a patched-up vessel, but after the raid," << endl;
	press_X_To_Continue();
	cout << "it's all you have." << endl;
	press_X_To_Continue();
	cout << "Outside the viewport, the debris from what was once New Castra Station, your home, " << endl << "a bustling hub on the edge of Union space drifts silently," <<
	endl << "a grim reminder of the pirate attack that destroyed everything you knew." << endl;
	press_X_To_Continue();
}
void story_Part2() {
	//  (OpenAI, 2024)
	cout << "New Castra wasn't just a colony." << endl;
	press_X_To_Continue();
	cout << "It was a thriving, independent settlement, one that wanted no part of the Unified Celestial Alliance (UCA)." << endl;
	press_X_To_Continue();
	cout << "But in recent years, pirate factions have become unusually bold and well armed," << endl
		<< "attacking vital colonies like New Castra with ruthless precision." << endl;
	press_X_To_Continue_And_Clear();

	cout << "The UCA's patrols rarely came this far out, but during the attack, they were nowhere to be seen." << endl;
	press_X_To_Continue();
	cout << "What happened to New Castra just doesn't sit right, the raiders have never been this powerful." << endl;
	press_X_To_Continue();
	cout << "And it cost you everything." << endl;
	press_X_To_Continue_And_Clear();

	cout << "As you push the engines to their limits, you feel the weight of the insignia that still clings to your jacket, the faded mark of the UCA Fleet. " << endl;
	press_X_To_Continue();
	cout << "Once, it was a symbol of pride." << endl;
	press_X_To_Continue();
	cout << "Now, it's a scar, a constant reminder of your failure to protect your home." << endl;
	press_X_To_Continue();
	cout << "You'd left the military for a quieter life, trading your uniform for a life on New Castra, " << endl;
	press_X_To_Continue();
	cout << "but the pirates took that life from you" << endl;
	press_X_To_Continue();
	cout << "in a single," << endl;
	press_X_To_Continue();
	cout << "merciless" << endl;
	press_X_To_Continue();
	cout << "attack." << endl;
	press_X_To_Continue_And_Clear();

	cout << "Revenge simmers in your veins, fueled by the echoing screams and blazing wreckage that still haunt you." << endl;
	press_X_To_Continue();
	cout << "These pirates aren't just bandits. They're organized, bold, and almost too well armed for mere raiders." << endl;
	press_X_To_Continue();
	cout << "Something bigger is at work here." << endl;
	press_X_To_Continue();
	cout << "Your fingers tighten around the controls as you activate the ship's weapons system." << endl;
	press_X_To_Continue();
	cout << "You've lost everything to the pirates. But now they're about to face everything you have left" << endl;
	press_X_To_Continue_And_Clear();

	cout << "Your ship strained as it pulled free from New Castra's drifting remains, the cockpit eerily silent." << endl;
	press_X_To_Continue();
	cout << "The ruins of your home, torn apart by pirate fire, still burned in your mind." << endl;
	press_X_To_Continue();
	cout << "You barely registered the blip on your radar, but when you saw the ship's silhouette, your pulse spiked." << endl;
	press_X_To_Continue_And_Clear();
	cout << "It was them. One of the pirate raiders that had destroyed New Castra." << endl;
	press_X_To_Continue();
	cout << "The battered, jagged vessel drifted through the debris, like a predator circling a fresh kill." << endl;
	press_X_To_Continue();
	cout << "Your fingers tightened on the controls. This ship was part of the very strike that left you alone in the galaxy." << endl;
	press_X_To_Continue();
	cout << "A crackling comm signal came through. 'Well, well, a little lost lamb left behind, hmm? " 
	<< endl << "Didn't anyone tell you this sector's ours now?' The voice dripped with mockery." << endl;
	press_X_To_Continue();
	cout << "'You think everyone was just going to roll over and die?' you replied, fighting to keep your voice steady." << endl;
	press_X_To_Continue();
	cout << "A low chuckle answered. 'I remember your planet's 'fleet', nice ships. Too bad they popped like fireworks.'" << endl;
	press_X_To_Continue();
	cout << "Your shields were low, weapons basic, but revenge burned hotter than fear. 'Let's see who pops now.'" << endl;
	press_X_To_Continue_And_Clear();

}

void loading_Screen(string text) {
	int length = random_Number(2, 6);
	for (int i = 0; i < length; i++){
		cout << "\r" << text << "      ";
		this_thread::sleep_for(chrono::seconds(1));
		cout << "\r" << text << " .    ";
		this_thread::sleep_for(chrono::seconds(1));
		cout << "\r" << text << " . .  ";
		this_thread::sleep_for(chrono::seconds(1));
		cout << "\r" << text << " . . .";
		this_thread::sleep_for(chrono::seconds(1));
	}
	system("cls");
}

void intermittent_Text() {
	int num = random_Number(1, 3);
	if (num == 1) {
		cout << "Drifting through space, your radar suddenly pings, a hostile ship, dead ahead." << endl;
	}
	else if (num == 2) {
		cout << "Drifting through the quiet of space, your sensors suddenly pick up a blip, an enemy ship." << endl;
	}
	else if (num == 3) {
		cout << "As you glide through the quiet void, your radar flashes, a hostile ship in your path." << endl;
	}
	press_X_To_Continue_And_Clear();
}
void story_Part3(int players_Inventory[]) {
	//  (OpenAI, 2024)
	cout << "The last sparks of the pirate ship faded behind you, and your battered vessel rattled, " 
	<< endl << "systems flashing warnings of low fuel and hull breaches. " << endl;
	press_X_To_Continue();
	cout << "After what felt like hours, a flicker of light appeared in the distance, a starship depot. " << endl << "Relief washes over you." << endl;
	press_X_To_Continue_And_Clear();
	cout << "You search your ship for any forgotten materials that could be used for trading, and you find some debris in a secluded corner of the ship" << endl;
	int items[4] = { 10, 0, 0, 0 };
	give_Item(players_Inventory, items);
}
void story_Part4() {
	//  (OpenAI, 2024)
	cout << "You leave Starship depot, the emptiness of space stretching ahead." << endl;
	press_X_To_Continue();
	cout << "Hours pass along a trade route, sensors quiet, until a blip appears on your radar." << endl;
	press_X_To_Continue();
	cout << "A pirate vessel looms into view, larger and more heavily armed than the last." << endl;
	press_X_To_Continue();
	cout << "A crackling voice sneers over the comm: 'Thought you could slip through our turf? Bad luck. Prepare to be boarded.' " << endl;
	press_X_To_Continue();
	cout << "You grip the controls, weapons hot. Out here, it's just you, them, and open space" << endl;
	press_X_To_Continue_And_Clear();

}
void story_Part5() {
	//  (OpenAI, 2024)
	cout << "The pirate ship bursts into flames, spiraling out of control as it crashes onto a barren planet below. " << 
		endl << "A plume of smoke marking its impact site on the surface. " << endl;
	press_X_To_Continue();
	cout << "Driven by curiosity and suspicion, you lower your ship down, following the wreckage to investigate." << endl;
	press_X_To_Continue();
	cout << "The planet's surface is harsh and dusty, winds kicking up small clouds as you land near the crash site." << endl;
	press_X_To_Continue();
	cout << "The pirate vessel lies scattered, debris scattered across a wide radius. " << 
		endl << "You walk through the wreckage carefully stepping over shredded metal and destroyed consoles." << endl;
	press_X_To_Continue();
	cout << "Among the wreckage, your eyes catch something peculiar, the gear the pirates left behind is marked with a familiar emblem, " << 
		endl << "a symbol of the UCA. Weapons, armor, even the insignia on certain pieces, all unmistakably standard issue UCA." << endl;
	press_X_To_Continue_And_Clear();
	cout << "A chill runs down your spine. Pirates like these shouldn't have access to UCA grade gear." << 
		endl <<	"A thought begins to form." << endl;
	press_X_To_Continue();
	cout << "Had these pirates managed to steal from the UCA? " << endl;
	press_X_To_Continue();
	cout << "The idea seems far-fetched, security on UCA outposts was notoriously tight," << 
		endl << "and this much gear would require inside knowledge or resources that the average pirate couldn't access. " << endl;
	press_X_To_Continue();
	cout << "But if they somehow had..." << endl;
	press_X_To_Continue();
	cout << "It would explain the pirates' recent surge in strength, their well coordinated attacks, " << 
		endl << "and the heavy weaponry they now wielded. " << endl;
	press_X_To_Continue();
	cout << "You leave the wreckage with a sinking feeling." << endl;
	press_X_To_Continue_And_Clear();
}
void story_Part6() {
	//  (OpenAI, 2024)
	cout << "You bring your ship down on a dusty, isolated colony planet, weary from the recent battles. " << endl;
	press_X_To_Continue();
	cout << "As you dock in a makeshift landing bay, the hum of life and chatter fills the air, a relief after the empty void of space." << endl;
	press_X_To_Continue();
	cout << "You disembark and make your way to a dimly lit inn on the edge of the port, hoping for a night's rest." << endl;
	press_X_To_Continue();
	cout << "Inside, locals fill the small, worn out bar area, their faces weathered by long days and hard lives. " << 
		endl << "As you settle down, fragments of their conversation catch your attention." << endl;
	press_X_To_Continue();
	cout << "'The UCA's supposed to protect us,' a voice says bitterly, 'but look around. Pirate attacks are worse than ever.'" << endl;
	press_X_To_Continue();
	cout << "A man scoffs in response. 'Protection's for those who can afford it. It costs a fortune to get a colony into the UCA's ranks now. " << 
		endl <<  "They raised the fare again, double what it was last year.'" << endl;
	press_X_To_Continue();
	cout << "'Guess they don't mind letting the rest of us fend for ourselves,' the first voice mutters." << endl;
	press_X_To_Continue();
	cout << "A younger voice pipes up. 'Do you think it's because the pirates are more powerful now? Feels like they have better gear every time they hit us.'" << endl;
	press_X_To_Continue();
	cout << "The conversation falls silent as they exchange uneasy looks, a question left unspoken in the air." << endl;
	press_X_To_Continue();
	cout << "You take it all in, a knot forming in your stomach. " << endl;
	press_X_To_Continue();
	cout << "But you brush it aside, weariness catching up with you. You find a small room, the worn cot a welcome sight." << endl;
	press_X_To_Continue();
	cout << "As you sink into bed, the conversations echo in your mind. " << endl;
	press_X_To_Continue_And_Clear();

	cout << "When you wake the next morning, the voices from last night linger in your mind. " << endl;
	press_X_To_Continue();
	cout << "You sit in the inn's small dining area, picking at a basic meal." << endl;
	press_X_To_Continue();
	cout << "The fragments of conversation, pirates growing stronger, the UCA's raised fees, defenseless colonies, churn in your thoughts, but so does something else, a nagging question of purpose." <<
		endl << "The anger you felt yesterday has cooled, replaced by a quiet exhaustion. You've taken down pirates, one by one, ship by ship, but for what? " << endl;
	press_X_To_Continue();
	cout << "The problem feels bigger than any one person could solve. Part of you wonders if any of this will make a difference, " << 
		endl << "if taking on these battles alone is worth it." << endl;
	press_X_To_Continue();
	cout << "But then you remember New Castra, once a place full of life, now left in ashes." << endl;
	press_X_To_Continue();
	cout << "With a deep breath, you finish your meal, your resolve hardening." << endl;
	press_X_To_Continue();
	cout << "No matter how powerful these pirates have become, you can't stand by while innocent colonies are left at their mercy. " << 
		endl << "You head back to your ship, determined to press on, one battle at a time." << endl;
	press_X_To_Continue();
}
void story_Part7() {
	//  (OpenAI, 2024)
	cout << "After defeating the last pirate ship in the sector, your comms light up with a scrambled message. " << 
		endl << "You piece together what you can from the encrypted signal, and a series of phrases become clear: " << endl;
	press_X_To_Continue();
	cout << "a larger faction congratulating their underlings, and a directive to 'await the next delivery.'" << endl;
	press_X_To_Continue();
	cout << "The message details a specific exchange point in a remote system and uses a coded phrase, one you've seen before in UCA protocols. " << endl;
	press_X_To_Continue();
	cout << "Suspicion knots in your stomach, and curiosity pulls you to set course for the meeting." << endl;
	press_X_To_Continue();
	cout << "You arrive at the exchange location, hiding your ship behind an asteroid field as a convoy of large UCA vessels approaches. " << endl;
	press_X_To_Continue();
	cout << "Holding your breath, you watch as the ships lower their cargo bays, and a small fleet of pirate ships drifts in from the other side." << endl;
	press_X_To_Continue();
	cout << "The pirates dock seamlessly, as if this exchange were nothing out of the ordinary." << endl;
	press_X_To_Continue();
	cout << "From your vantage point, you see UCA officers, dressed in standard uniforms, unloading crates." << 
		endl << "Marked with the UCA insignia, the crates contain advanced weaponry, fuel cells, and high grade armor. " << endl;
	press_X_To_Continue();
	cout << "The officers work in silence, handing the supplies over to the pirates, who accept them with practiced ease, as if they'd done this countless times before." << endl;
	press_X_To_Continue();
	cout << "A cold realization settles over you. This isn't negligence or a few rogue elements, this is a deliberate supply chain. " << endl;
	press_X_To_Continue();
	cout << "The UCA isn't struggling to fight the pirates, they're supplying them. " << endl;
	press_X_To_Continue();
	cout << "They're orchestrating this entire threat, pushing colonies to their limits, all to tighten their grip under the guise of 'protection.'" << endl;
	press_X_To_Continue();
	cout << "A surge of anger rushes through you. " << endl;
	press_X_To_Continue();
	cout << "The organization that's supposed to protect these worlds has betrayed them," << 
		endl << " creating the very danger they claim to defend against." << endl;
	press_X_To_Continue();

	cout << "Watching the last of the crates exchange hands, you power up and surge forward.The pirate ship darts away into the shadows, but the UCA vessel stays, its turrets locking onto you." << endl;
	press_X_To_Continue();
	cout << "'Traitors, ' you grit, tightening your grip on the controls. The UCA ship charges its weapons." << endl;
	press_X_To_Continue_And_Clear();
	


	

		
 }
void story_Part9() {
	//  (OpenAI, 2024)
	cout << "Shaken by what you just witnessed, you set a course to the nearest planet, desperate to put distance between yourself and the UCA's dark dealings." << 
		endl <<" Your mind spins with questions, but exhaustion weighs on you, and you land in a small, quiet colony on the planet's surface." << endl;
	press_X_To_Continue();
	cout << "As you disembark, you notice the people here look worn and gaunt, their clothing faded, eyes downcast as they work on rough machinery, " << 
		endl << "lifting heavy loads or shoveling soil into drying fields. You approach a nearby worker, an older man with hollow cheeks and calloused hands." << endl;
	press_X_To_Continue();
	cout << "He looks at you cautiously, but there's a flicker of curiosity in his eyes. 'You're new here, aren't you?' he asks quietly." << endl;
	press_X_To_Continue();
	cout << "You nod, and he glances around to make sure no one is listening before speaking. " << endl;
	press_X_To_Continue();
	cout << "'We used to be happy here. Independent, thriving in our own way. But th... the pirate attacks started." << 
		endl << " More raids than we'd ever seen. The UCA offered protection, but the fee was high, higher than we could afford.' " << endl;
	press_X_To_Continue();
	cout << "We joined because we had no choice, but now...' He gestures to the weary people around you." << endl;
	press_X_To_Continue();
	cout << "'We work like this, day and night, just to pay off the debt.'" << endl;
	press_X_To_Continue();
	cout << "Another worker overhears and steps over, a young woman with a sunken face. 'The UCA demands a heavy price for its protection, " << 
		endl << "and what little we earn goes to pay off the admission cost. It's as if they own us now.'" << endl;
	press_X_To_Continue();
	cout << "The older man nods grimly, then offers a sad smile. 'Still, we're not without kindness. You look like you need rest. Come, there's a place for you to sleep tonight, though it isn't much.'" << endl;
	press_X_To_Continue();
	cout << "Grateful, you follow them to a small, bare room, the floor covered with a simple mat. " << 
		endl << "As you lie down, their words echo in your mind. The UCA wasn't just protecting this colony," << 
		endl << " they were exploiting it, tightening their grip on every world they 'saved.' You close your eyes," << 
		endl << " but sleep doesn't come easily. " << endl;
	press_X_To_Continue_And_Clear();

}
void story_Part8() {
	//  (OpenAI, 2024)
	cout << "You gun the engines, pushing your ship to its limits as you pursue the fleeing pirate vessels." << endl;
	press_X_To_Continue();
	cout << "It darts through asteroid fields and around shattered moon fragments, but you stay on its tail, your targeting systems locking in." << endl;
	press_X_To_Continue_And_Clear();
	
}
void story_Part10() {
	//  (OpenAI, 2024)
	cout << "Fueled by everything you've witnessed, you set a course straight for UCA territory, intent on making them answer for their treachery." <<
			endl << " You navigate through their patrols undetected, inching closer to the UCA capital with every lightyear." << endl;
	press_X_To_Continue();
	cout << "Finally, the capital looms ahead, a fortress of influence and power. " << endl;
	press_X_To_Continue();
	cout << "But before you can get any closer, an imposing UCA vessel appears, bristling with advanced weaponry. Its turrets lock onto you, engines humming with lethal energy." << endl;
	press_X_To_Continue();
	cout << "You take a steadying breath and grip the controls." << endl;
	press_X_To_Continue();
	cout << "There's no going back now. With resolve hardening, you prepare for a fight against the heart of the UCA's defenses." << endl;
	press_X_To_Continue_And_Clear();
}
void story_Part11() {
	//  (OpenAI, 2024)
	cout << "Determined to inflict as much  destruction as you can to the heart of the UCA, you engage full thrusters and dive toward the nearest patrols." << endl;
	press_X_To_Continue();
	cout << "Your weapons hum to life as you open fire on nearby ships" << endl;
	press_X_To_Continue_And_Clear();
	

}
void story_Part12() {
	//  (OpenAI, 2024)
	cout << "After tearing through the last of the UCA ships, you dock near the heart of their headquarters, determined to get answers." << endl;
	press_X_To_Continue();
	cout << "Moving stealthily, you slip past guards and security checkpoints until you reach an imposing door." << endl;
	press_X_To_Continue();
	cout << "Inside, voices echo, someone is discussing the chaos you've caused, how your actions have shaken the UCA." << endl;
	press_X_To_Continue();
	cout << "Without hesitation, you burst into the room, finding yourself face to face with the UCA's Grand Director." << endl;
	press_X_To_Continue();
	cout << "He turns, surprised yet strangely amused, showing no fear." << endl;
	press_X_To_Continue();
	cout << "You demand an explanation, why has he fueled such suffering, empowered pirates, and brought colonies to their knees?" << endl;
	press_X_To_Continue();
	cout << "With a smug smile, he leans back, almost bored by your anger." << endl;
	press_X_To_Continue();
	cout << "'Ah, well,' he says, 'it's simply a matter... luxury.'" << endl;
	press_X_To_Continue();
	cout << "'There's something I've had my eye on. Very exclusive. Quite costly, really.'" << endl;
	press_X_To_Continue();
	cout << "Your fists clench, incredulously. " << endl;
	press_X_To_Continue();
	cout << "'What could possibly be so valuable that you'd justify all this destruction?'" << endl;
	press_X_To_Continue();
	cout << "He smirks." << endl;
	press_X_To_Continue();
	cout << "'A toilet,' he replies calmly." << endl;
	press_X_To_Continue_And_Clear();

}

void the_End() {
	cout << "Congratulations, you won. Thanks for playing my game." << endl;
	cout << "Written and produced by Tristan Alvarez" << endl;
	press_X_To_Continue_And_Clear();
}

void demo() {
	int players_Inventory[4] = { 30, 30, 30, 10 };
	vector<artillery> artillery_For_Purchase;
	/*
	Stellar Debris (Common), Nebula Shards (Uncommon), Quantum Cores (Rare), Dark Matter Essence (very rare)
	// name, damage, accuracy, attack_Speed, max_Uses, energy_Cost, is_EMP, is_Pulse_Disruptor, is_Plasma_Overload);
	*/

	
	string user_Name = pick_Name();
	

	ship players_Ship(user_Name, 50, 50, 10, 10);
	//name , health, energy, evasiveness, energy regen
	vector<artillery> players_Artillery = {
	artillery("Basic Artillery", 15, 95, 60, 30, 5, false, false, false, true, false, 10, 0, "10% to overheat") };
	// artillery(string name, int damage, int accuracy, int attack_Speed, int max_Uses, int energy_Cost, bool can_Corrode, bool can_Stun, bool can_Weaken, bool can_Overheat, bool can_Disrupt, int percent, int ammo_Quality, string ability_Name);

	add_Artillery1(players_Artillery);
	add_Artillery2(players_Artillery);
	add_Artillery3(players_Artillery);
	add_Artillery4(players_Artillery);



	//fight 1, level 1 
	ship enemy_Ship1("Space pirate ship", 35, 20, 15, 25);
	vector<artillery> enemys_Artillery = {
	artillery("Ion Pulse Blaster", 10, 80, 70, 40, 5, false, false, false, false, false, 0, 0, " "),
	artillery("Basic Rail Gun", 20, 60, 30, 1, 20, false, false, false, true, false, 0, 0, " ") };

	combat(players_Ship, players_Artillery, players_Inventory, 1, enemy_Ship1, enemys_Artillery);
	
	starship_Depot(players_Ship, players_Artillery, artillery_For_Purchase, players_Inventory);
	enemys_Artillery.clear();

	ship enemy_Ship12("Nightmare", 155, 55, 40, 15);
	enemys_Artillery = {
   artillery("Veil Cannon", 10, 100, 20, 10, 1, false, false, false, true, false, 50, 0, " "),
   artillery("Night's Wrath", 30, 90, 60, 2, 20, false, false, true, false, true, 50, 0, " "),
   artillery("Talon", 20, 60, 60, 10, 10, false, true, false, false, false, 30, 0, " ") };
	loading_Screen("Flying through space");
	intermittent_Text();
	combat(players_Ship, players_Artillery, players_Inventory, 4, enemy_Ship12, enemys_Artillery);
	enemys_Artillery.clear();
	
}


int main() {

	// citations:
	// OpenAI. (2024). ChatGPT (nov 2nd version) [Large language model]. https://chat.openai.com/share/dccb3610-1db9-4eed-88b1-cdb06f67982a




	int players_Inventory[4] = {0, 0, 0, 0};
	vector<artillery> artillery_For_Purchase;
	/*
	Stellar Debris (Common), Nebula Shards (Uncommon), Quantum Cores (Rare), Dark Matter Essence (very rare)
	// name, damage, accuracy, attack_Speed, max_Uses, energy_Cost, is_EMP, is_Pulse_Disruptor, is_Plasma_Overload);
	*/
	//demo();
	story_Part1();
	string user_Name = pick_Name();
	story_Part2();

	ship players_Ship(user_Name, 100, 50, 10, 10);
	
	//name , health, energy, evasiveness, energy regen
	vector<artillery> players_Artillery = {
	artillery( "Basic Artillery", 15, 95, 60, 40, 5, false, false, false, true, false, 10, 0, "10% to overheat") };
	// artillery(string name, int damage, int accuracy, int attack_Speed, int max_Uses, int energy_Cost, bool can_Corrode, bool can_Stun, bool can_Weaken, bool can_Overheat, bool can_Disrupt, int percent, int ammo_Quality, string ability_Name);
	
	
	//fight 1, level 1 
	ship enemy_Ship1("Space pirate ship", 35, 20, 15, 25);
	vector<artillery> enemys_Artillery = {
	artillery("Ion Pulse Blaster", 10, 80, 70, 40, 5, false, false, false, false, false, 0, 0, " "),
	artillery("Basic Rail Gun", 20, 60, 30, 1, 20, false, false, false, true, false, 0, 0, " ") };

	combat(players_Ship, players_Artillery, players_Inventory, 1, enemy_Ship1, enemys_Artillery);
	story_Part3(players_Inventory);

	add_Artillery1(artillery_For_Purchase);
	starship_Depot(players_Ship, players_Artillery, artillery_For_Purchase, players_Inventory);
	enemys_Artillery.clear();
	
	//fight2, level 1
	ship enemy_Ship2("Astro drifter", 50, 40, 15, 20);
	enemys_Artillery = {
	artillery("Solar lance", 20, 20, 60, 6, 15, false, false, false, false, false, 0, 0, " ")};
	story_Part4();
	combat(players_Ship, players_Artillery, players_Inventory, 1, enemy_Ship2, enemys_Artillery);
	enemys_Artillery.clear();

	//fight 3, level 1
	ship enemy_Ship3("Scavenger", 80, 30, 0, 65);
	enemys_Artillery = {
	artillery("Phase disruptor", 15, 90, 70, 10, 10, false, false, false, false, true, 50, 0, " ") };
	loading_Screen("Flying through space");
	intermittent_Text();
	combat(players_Ship, players_Artillery, players_Inventory, 1, enemy_Ship3, enemys_Artillery);
	starship_Depot(players_Ship, players_Artillery, artillery_For_Purchase, players_Inventory);
	enemys_Artillery.clear();


	//2
	//fight 1 level 2
	add_Artillery2(artillery_For_Purchase);
	ship enemy_Ship4("Enforcer", 70, 40, 5, 50);
	 enemys_Artillery = {
	artillery("Ion Pulse Blaster", 30, 10, 70, 5, 20, false, false, false, true, false, 20, 0, " ")};
	story_Part5();
	loading_Screen("Flying through space");
	intermittent_Text();
	combat(players_Ship, players_Artillery, players_Inventory, 2, enemy_Ship4, enemys_Artillery);
	starship_Depot(players_Ship, players_Artillery, artillery_For_Purchase, players_Inventory);
	enemys_Artillery.clear();



	//fight 2, level 2
	ship enemy_Ship5("Starbane Raider", 55, 25, 55, 100);
	 enemys_Artillery = {
	artillery("Void Ripper", 10, 80, 70, 40, 5, false, false, true, false, false, 50, 0, " "),
	artillery("Howitzer", 30, 70, 20, 2, 20, false, false, false, false, false, 0, 0, " ") };
	 loading_Screen("Flying through space");
	 intermittent_Text();
	combat(players_Ship, players_Artillery, players_Inventory, 2, enemy_Ship5, enemys_Artillery);
	starship_Depot(players_Ship, players_Artillery, artillery_For_Purchase, players_Inventory);
	enemys_Artillery.clear();

	//fight 2, level 2
	ship enemy_Ship6("Scourge", 45, 35, 35, 15);
	 enemys_Artillery = {
	artillery("Rift cannon", 10, 100, 100, 40, 5, false, false, false, false, false, 0, 0, " "),
	artillery("Corrosion Harpoon", 5, 85, 50, 1, 1, true, false, false, false, false, 80, 0, " ")};
	loading_Screen("Flying through space");
	intermittent_Text();
	combat(players_Ship, players_Artillery, players_Inventory, 2, enemy_Ship6, enemys_Artillery);
	enemys_Artillery.clear();
	starship_Depot(players_Ship, players_Artillery, artillery_For_Purchase, players_Inventory);
	loading_Screen("Looking for a place to sleep");
	story_Part6();
	//3
	//fight 1, level 3
	add_Artillery3(artillery_For_Purchase);
	ship enemy_Ship7("Eclipse Marauder", 95, 65, 5, 5);
	 enemys_Artillery = {
	artillery("Pulsewave breacher", 20, 75, 90, 10, 10, false, false, false, false, true, 20, 0, " "),
	artillery("Hellfire cannon", 30, 60, 30, 5, 30, false, false, false, true, false, 40, 0, " ") };
	loading_Screen("Flying through space");
	intermittent_Text();
	combat(players_Ship, players_Artillery, players_Inventory, 2, enemy_Ship7, enemys_Artillery);
	starship_Depot(players_Ship, players_Artillery, artillery_For_Purchase, players_Inventory);
	enemys_Artillery.clear();

	//fight 2, level 3
	ship enemy_Ship8("Tempest", 40, 40, 45, 35);
	 enemys_Artillery = {
	artillery("Ion Beam Cannon", 50, 35, 100, 7, 20, false, false, false, true, false, 50, 0, " "),
	artillery("EMP Burst", 5, 100, 90, 1, 20, false, true, false, false, false, 50, 0, " ") };
	loading_Screen("Flying through space");
	intermittent_Text();
	combat(players_Ship, players_Artillery, players_Inventory, 3, enemy_Ship8, enemys_Artillery);
	enemys_Artillery.clear();

	//fight 3, level 3
	ship enemy_Ship9("Space Vulture", 70, 70, 25, 25);
	 enemys_Artillery = {
	artillery("Ion Pulse Blaster", 10, 80, 70, 40, 5, false, false, false, false, false, 0, 0, " "),
	artillery("Basic Rail Gun", 20, 60, 30, 1, 20, false, false, false, false, false,0, 0, " ") };
	loading_Screen("Flying through space");
	intermittent_Text();
	combat(players_Ship, players_Artillery, players_Inventory, 3, enemy_Ship9, enemys_Artillery);
	enemys_Artillery.clear();
	
	//4
	//fight 1, level 4
	ship enemy_Ship10("Starborn Menace", 110, 55, 25, 30);
	 enemys_Artillery = {
	artillery("Zeus Howitzer", 25, 115, 70, 10, 20, false, false, false, true, false, 20, 0, " "),
	artillery("Vortex Cannon", 15, 70, 70, 5, 5, false, true, false, false, false, 35, 0, " ") };
	loading_Screen("Flying through space");
	intermittent_Text();
	combat(players_Ship, players_Artillery, players_Inventory, 4, enemy_Ship10, enemys_Artillery);
	starship_Depot(players_Ship, players_Artillery, artillery_For_Purchase, players_Inventory);
	enemys_Artillery.clear();
	
	
	//fight 2, level 4
	ship enemy_Ship11("Star Hunter", 70, 90, 70, 50);
	 enemys_Artillery = {
	artillery("Ion Pulse Blaster", 10, 80, 70, 40, 5, false, false, false, false, false, 0, 0, " "),
	artillery("Rust Reaper", 20, 30, 30, 3, 10, true, false, false, false, false, 80, 0, " "),
	artillery("Star Breaker", 65, 55, 40, 10, 35, false, false, false, true, false, 75, 0, " ") };
	loading_Screen("Flying through space");
	intermittent_Text();
	combat(players_Ship, players_Artillery, players_Inventory, 4, enemy_Ship11, enemys_Artillery);
	starship_Depot(players_Ship, players_Artillery, artillery_For_Purchase, players_Inventory);
	enemys_Artillery.clear();

	//fight 3, level 4
	ship enemy_Ship12("Nightmare", 155, 55, 40, 15);
	 enemys_Artillery = {
	artillery("Veil Cannon", 10, 100, 20, 10, 1, false, false, false, true, false, 50, 0, " "),
	artillery("Night's Wrath", 30, 90, 60, 2, 20, false, false, true, false, true, 50, 0, " "),
	artillery("Talon", 20, 60, 60, 10, 10, false, true, false, false, false, 30, 0, " ") };
	loading_Screen("Flying through space");
	intermittent_Text();
	combat(players_Ship, players_Artillery, players_Inventory, 4, enemy_Ship12, enemys_Artillery);
	enemys_Artillery.clear();
	story_Part7();
	//5
	
	//fight 1, level 5
	ship enemy_Ship14("UCA Prowler", 90, 30, 95, 115);
	enemys_Artillery = {
   artillery("Phantom railgun", 45, 80, 30, 5, 20, false, false, false, true, false, 20, 0, " "),
   artillery("Talon", 20, 60, 60, 10, 10, false, true, true, false, false, 30, 0, " ") };
	loading_Screen("Flying through space");
	intermittent_Text();
	combat(players_Ship, players_Artillery, players_Inventory, 5, enemy_Ship14, enemys_Artillery);
	starship_Depot(players_Ship, players_Artillery, artillery_For_Purchase, players_Inventory);
	enemys_Artillery.clear();
	story_Part8();

	//fight 2, level 5
	add_Artillery4(artillery_For_Purchase);
	ship enemy_Ship13("Void stalker", 140, 100, 50, 5);
	 enemys_Artillery = {
	artillery("Void Piercer", 20, 85, 95, 5, 15, false, false, true, false, false, 65, 0, ""),
	artillery("Void Cleaver", 60, 60, 30, 5, 30, false, false, false, true, false, 35, 0, "") };
	loading_Screen("Flying through space");
	intermittent_Text();
	combat(players_Ship, players_Artillery, players_Inventory, 5, enemy_Ship13, enemys_Artillery);
	enemys_Artillery.clear();

	//fight 3, level 5
	ship enemy_Ship15("Shadow Dread", 170, 60, 75, 50);
	enemys_Artillery = {
   artillery("Reaper Cannon", 10, 80, 70, 5, 10, false, false, true, false, false, 70, 0, " "),
   artillery("Nightfall Howitzer", 50, 120, 50, 3, 20, false, false, false, true, false, 100, 0, " "),
   artillery("Wrathfire", 20, 60, 70, 5, 10, true, false, false, false, false, 50, 0, " ") };
	loading_Screen("Flying through space");
	intermittent_Text();
	combat(players_Ship, players_Artillery, players_Inventory, 5, enemy_Ship15, enemys_Artillery);
	enemys_Artillery.clear();
	story_Part9();
	

	

	//6
	//fight 1, level 6
	ship enemy_Ship16("UCA Predator", 180, 140, 35, 15);
	 enemys_Artillery = {
	artillery("Mauler", 20, 60, 30, 1, 20, false, false, false, false, false, 0, 0, " "), 
	 artillery("Talon MK2", 25, 75, 60, 10, 10, false, true, true, false, false, 45, 0, " "),
	artillery("Beast Maw", 20, 60, 30, 1, 20, false, false, false, false, false, 0, 0, " ") };
	loading_Screen("Flying through space");
	intermittent_Text();
	combat(players_Ship, players_Artillery, players_Inventory, 6, enemy_Ship16, enemys_Artillery);
	starship_Depot(players_Ship, players_Artillery, artillery_For_Purchase, players_Inventory);
	enemys_Artillery.clear();

	//fight 2 level 6
	ship enemy_Ship17("UCA Dreadnought", 300, 100, 10, 30);
	 enemys_Artillery = {
	artillery("Dread Breaker", 15, 100, 70, 3, 5, false, false, false, false, true, 70, 0, " "),
	artillery("Titan Cannon", 30, 50, 100, 25, 15, false, false, false, false, false, 0, 0, " ") };
	loading_Screen("Flying through space");
	intermittent_Text();
	combat(players_Ship, players_Artillery, players_Inventory, 6, enemy_Ship17, enemys_Artillery);
	enemys_Artillery.clear();
	starship_Depot(players_Ship, players_Artillery, artillery_For_Purchase, players_Inventory);
		
	//fight 3, level 6
	ship enemy_Ship18("UCA Raptor", 100, 60, 120, 140);
	 enemys_Artillery = {
	artillery("Claw Howitzer", 15, 80, 70, 3, 10, false, false, false, false, true, 40, 0, " "),
	artillery("Hawkeye Rail Gun", 50, 100, 100, 3, 10, false, false, false, true, false, 50, 0, " "),
	artillery("Talon MK3", 30, 85, 90, 3, 10, false, true, true, true, false, 50, 0, " "),
	artillery("Venom spitter", 10, 80, 40, 3, 5, true, false, false, false, false, 30, 0, " ") };
	loading_Screen("Flying through space");
	intermittent_Text();
	combat(players_Ship, players_Artillery, players_Inventory, 6, enemy_Ship18, enemys_Artillery);
	enemys_Artillery.clear();
	story_Part12();
	system("cls");
	the_End();


	return 0;
}
