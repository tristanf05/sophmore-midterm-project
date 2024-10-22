#include <iostream>
#include <random>
//#include <cmath>
#include <string>
#include <sstream>
#include <cstring>
#include "ship.h"
using namespace std;
std::random_device rd;
std::mt19937 gen(rd());

using namespace std;
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
void print_Dropped_Items(int items[]) {
	cout << "Dropped items: " << endl;
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
	int additional_Loot = random_Number(1, level * 1.5);
	int dropped_Items[4] = {0, 0, 0, 0};
	for (int i = 0; i < length; i++){
		if (rarity <= 8) {
			//drops common item
			dropped_Items[0] += random_Number(3, 5 + additional_Loot);
			
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
	print_Dropped_Items(dropped_Items);
}

void print_Inventory(int player_Inventory[]) {
	cout << endl;
	cout << "Your inventory: " << endl;
	if (player_Inventory[0] > 0) {
		cout << player_Inventory[0] << " Stellar debris" << endl;
	}
	if (player_Inventory[1] > 0) {
		cout  << player_Inventory[1]  << " Nebula shard(s)" << endl;
	}
	if (player_Inventory[2] > 0) {
		cout  << player_Inventory[2]  << " Quantum core(s)" << endl;
	}
	if (player_Inventory[3] > 0) {
		cout  << player_Inventory[3] << " Dark matter essence(s)" << endl;
	}
	if (player_Inventory[0] == 0 && player_Inventory[1] == 0 && player_Inventory[2] == 0 && player_Inventory[3] == 0) {
		cout << "EMPTY" << endl;
	}
	cout << endl;
}

//combat
void ship::print_Detailed_Stats() {
	cout << endl;
	cout << "The " << get_Name() << "'s stats" << endl;
	cout << "Health: " << get_Current_Health() << "/" << get_Max_Health() << endl;
	cout << "Energy: " << get_Current_Energy() << "/" << get_Max_Energy() << endl;
	cout << "Evasiveness: " << get_Evasiveness() << "%" << endl;
	cout << "Energy regeneration: 5% to " << get_Energy_Regen() << "%" << endl << endl;
	
}
void ship::print_Stats() {
	cout << "Health: " << get_Current_Health() << "/" << get_Max_Health() << endl;
	cout << "Energy: " << get_Current_Energy() << "/" << get_Max_Energy() << endl;
	cout << "--------------------" << endl;
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
	for (int i = 0; i < energy && total_Energy_Regenerated < get_Max_Energy(); i++) {
		total_Energy_Regenerated += 1;
	}
	set_Current_Energy(total_Energy_Regenerated);
	//
	bool evaded = evade(accuracy - get_Evasiveness());
	set_Evaded(evaded);
	cout << "The " << get_Name() <<
		" preformed evasive maneuvers and recovered some energy" << endl;


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
	for (int i = 0; i < players_Artillery.size(); i++){
		cout << "--------------------   ";
	}
	cout << endl;
	for (int i = 0; i < players_Artillery.size(); i++) {
		cout << (i + 1) << ") " << players_Artillery[i].get_Name();
		int space = 20 - players_Artillery[i].get_Name().length();
		for (int j = 0; j < space; j++) {
			cout << " ";
		}
	}
	cout << endl;
	for (int i = 0; i < players_Artillery.size(); i++) {
		cout << "Damage: " << players_Artillery[i].get_Damage() << "             ";
	}
	cout << endl;
	for (int i = 0; i < players_Artillery.size(); i++) {
		cout << "Accuracy: " << players_Artillery[i].get_Accuracy() << "%" << "          ";
	}
	cout << endl;
	for (int i = 0; i < players_Artillery.size(); i++) {
		cout << "Energy cost: " << players_Artillery[i].get_Energy_Cost() << "        ";
		if (players_Artillery[i].get_Energy_Cost() < 10) {
			cout << " ";
		}
	}
	cout << endl;
	for (int i = 0; i < players_Artillery.size(); i++) {
		cout << "Attack speed: " << players_Artillery[i].get_Attack_Speed() << "       ";
	}
	cout << endl;
	for (int i = 0; i < players_Artillery.size(); i++) {
		cout << "Available ammo: " << players_Artillery[i].get_Current_Uses() << "/" << players_Artillery[i].get_Max_Uses() << "  ";
		if (players_Artillery[i].get_Max_Uses() < 10) {
			cout << " ";
		}
		if (players_Artillery[i].get_Current_Uses() < 10) {
			cout << " ";
		}
	}
	cout << endl;
	for (int i = 0; i < players_Artillery.size(); i++) {
		// std::string sub = str.substr(7, 5);
		cout << "Ability:";
		int space = 15 - players_Artillery[i].get_Ability_Name().length();
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
	
	while (!valid) {
		if (player_Choice == 0) {
			valid = true;
			return player_Choice - 1;
		}
		if (player_Choice > 0 && player_Choice <= players_Artillery.size()) {
			if (players_Ship.get_Current_Energy() >= players_Artillery[player_Choice-1].get_Energy_Cost()) {
				if (players_Artillery[player_Choice-1].get_Current_Uses() > 0) {
					valid = true;
					int uses_Remaining = players_Artillery [player_Choice- 1] .get_Current_Uses() - 1;
					players_Artillery[player_Choice -1].set_Current_Uses(uses_Remaining);

					int energy_Remaining = players_Ship.get_Current_Energy() - players_Artillery[player_Choice -1].get_Energy_Cost();
					players_Ship.set_Current_Energy(energy_Remaining);

					return player_Choice - 1;


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
void user_Action(int player_Choice, ship& players_Ship, vector<artillery>& players_Artillery, ship& enemy_Ship) {
	if (enemy_Ship.get_Evaded() == false && evade(players_Artillery[player_Choice].get_Accuracy() == false)) {
		int remaining_Health = enemy_Ship.get_Current_Health() - players_Artillery[player_Choice].get_Damage();
		enemy_Ship.set_Current_Health(remaining_Health);
		cout << "You fired your " << players_Artillery[player_Choice].get_Name() << " and dealt " << players_Artillery[player_Choice].get_Damage() << " damage" << endl;
	}
	else {
		cout << "You fired your " << players_Artillery[player_Choice].get_Name() << ", however the " << enemy_Ship.get_Name() << " was able to dodge it" << endl;
		enemy_Ship.set_Evaded(false);
	}
}
int read_Enemy_Input(ship& enemy_Ship, vector<artillery>& enemys_Artillery) {
	bool valid = false;
	int enemy_Choice;

	while (!valid) {
		
		enemy_Choice = random_Number(0, (enemys_Artillery.size() - 1));

		
		if (enemys_Artillery[enemy_Choice].get_Energy_Cost() <= enemy_Ship.get_Current_Energy() && enemys_Artillery[enemy_Choice].get_Current_Uses() > 0) {
			
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
				if (enemys_Artillery[i].get_Energy_Cost() <= enemy_Ship.get_Current_Energy() && enemys_Artillery[i].get_Current_Uses() > 0) {
					enemy_Choice = i; 
					int uses_Remaining = enemys_Artillery[enemy_Choice].get_Current_Uses() - 1;
					enemys_Artillery[enemy_Choice].set_Current_Uses(uses_Remaining);

					//cout << enemy_Ship.get_Current_Energy() << " " << enemys_Artillery[enemy_Choice].get_Energy_Cost() << " ";
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
	if ((players_Ship.get_Evaded() == false) && (evade(enemys_Artillery[enemy_Choice].get_Accuracy() == false))) {
		int remaining_Health = players_Ship.get_Current_Health() - enemys_Artillery[enemy_Choice].get_Damage();
		players_Ship.set_Current_Health(remaining_Health);
		cout << "The " << enemy_Ship.get_Name() << " fired their " << enemys_Artillery[enemy_Choice].get_Name()
			<< " and dealt " << enemys_Artillery[enemy_Choice].get_Damage() << " damage " << endl;
	}
	else {
		cout << "The " << enemy_Ship.get_Name() << " fired their " << enemys_Artillery[enemy_Choice].get_Name()
		<< ", however your ship managed to evade it " << endl;
		players_Ship.set_Evaded(false);
	}
}

//status effects
void ship::status_Effects() {


}
void ship::apply_Overheat_Status(int percent) {
	int chance = random_Number(1, 100);
	if (chance <= percent/2) {
		set_Overheat_Status();
	}
}
void ship::apply_Defense_Down_Status(int percent) {
	int chance = random_Number(1, 100);
	if (chance <= percent) {
		set_Weaken_Status();
	}
}
void ship::apply_Stun_Status( int percent) {
	int chance = random_Number(1, 100);
	if (chance <= percent) {
		set_Stun_Status();
	}
}
void ship::apply_Corrosion_Status(int percent) {
	int chance = random_Number(1, 100);
	if (chance <= percent) {
		set_Corrosion_Status();
	}
}

int combat(ship& players_Ship, vector<artillery>& players_Artillery, int players_Inventory[], int enemy_Level, ship& enemy_Ship, vector<artillery>& enemys_Artillery) {
	int max_Energy = players_Ship.get_Max_Energy();
	players_Ship.set_Current_Energy(max_Energy);
	while (enemy_Ship.get_Current_Health() > 0) {
		if (players_Ship.get_Current_Health() > 0) {
			cout << "The " << players_Ship.get_Name() << "'s stats" << endl;
			players_Ship.print_Stats();
			cout << enemy_Ship.get_Name() << "'s stats" << endl;
			enemy_Ship.print_Stats();
			print_Player_Options(players_Ship, players_Artillery);
			int player_Choice = read_User_Input(players_Ship, players_Artillery);
			int enemy_Choice = read_Enemy_Input(enemy_Ship, enemys_Artillery);
			int players_Artillery_Accuracy = 0;
			int enemys_Artillery_Accuracy  = 0;
			if (player_Choice > -1) {
				players_Artillery_Accuracy = players_Artillery[player_Choice].get_Accuracy();
			}
			if (enemy_Choice > -1) {
				enemys_Artillery_Accuracy = enemys_Artillery[enemy_Choice].get_Accuracy();
			}
			if (enemy_Choice == -1 || player_Choice == -1) {
				bool first_Evade = false;
				if (player_Choice == -1) {
					//user evade function
					players_Ship.evade_Action(enemys_Artillery_Accuracy);
					press_X_To_Continue();
					first_Evade;
				}
				if (enemy_Choice == -1) {
					enemy_Ship.evade_Action(players_Artillery_Accuracy);
					if (first_Evade) {
						press_X_To_Continue_And_Clear();
					}
					else {
						press_X_To_Continue();
					}
				}
				if (player_Choice != -1) {
					user_Action(player_Choice, players_Ship, players_Artillery, enemy_Ship);
					press_X_To_Continue_And_Clear();
				}
				if (enemy_Choice != -1) {
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
					user_Action(player_Choice, players_Ship, players_Artillery, enemy_Ship);
					press_X_To_Continue_And_Clear();
				}
			}
			else {
				user_Action(player_Choice, players_Ship, players_Artillery, enemy_Ship);
				press_X_To_Continue();
				if (enemy_Ship.get_Current_Health() > 0) {
					enemy_Action(enemy_Choice, players_Ship, enemy_Ship, enemys_Artillery);
					press_X_To_Continue_And_Clear();
				}
			}
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
void add_Artillery1(vector<artillery>& artillery_For_Purchase) {
	artillery_For_Purchase.push_back(artillery("stasis cannon", 25, 85, 95, 15, 10, false, true, false, false, 1, "40% to stun"));
}
void add_Artillery2(vector<artillery>& artillery_For_Purchase) {
	artillery_For_Purchase.push_back(artillery("voidpeircer", 15, 85, 95, 12, 10, false, false, true, false, 2, "50% to weaken"));
}

void add_Artillery3(vector<artillery>& artillery_For_Purchase) {
	artillery_For_Purchase.push_back(artillery("star breaker", 65, 75, 15, 7, 35, false, false, false, true, 3, "25% to overheat"));
}

int generate_Price(int num, int multiplier, int minus) {
	num = minus - num;
	int old_Num = num / 2;
	num *= multiplier;
	num += old_Num;

	

	return num;
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
		cout << " Improves the ship's health by 15"  << endl;
		price = generate_Upgade_Price(get_Hull_Level(), price);
		display_Price(price);
		wipe_Price(price);
	}
	else {
		cout << " MAX LEVEL" << endl;
	}
	cout << "2. Engines:";
	if (get_Engines_Level() < 5) {
		cout << " Increases the ship's evasiveness by 5%" << endl;
		price = generate_Upgade_Price(get_Engines_Level(), price);
		display_Price(price);
		wipe_Price(price);
	}
	else {
		cout << " MAX LEVEL" << endl;
	}
	cout << "3. Ammo reserves:";
	if (get_Ammo_Reserves_Level() < 5) {
		cout << " Improves the ammo capacity of all your artillery by 10%" << endl;
		price = generate_Upgade_Price(get_Ammo_Reserves_Level(), price);
		display_Price(price);
		wipe_Price(price);
	}
	else {
		cout << " MAX LEVEL" << endl;
	}
	cout << "4. Power core:";
	if (get_Power_Core_Level() < 5) {
		cout << " Increases the ship's energy capacity by 10" << endl;
		
		price = generate_Upgade_Price(get_Power_Core_Level(), price);
		display_Price(price);
		wipe_Price(price);
	}
	else {
		cout << " MAX LEVEL" << endl;
	}
	cout << "5. Nuclear reactor:";
	if (get_Nuclear_Reactor_Level() < 5) {
		cout << " Improves the ship's energy regeneration by 5%" << endl;
		
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
		if (player_Choice <= 5 && player_Choice >= 0) {
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
	if (missing_Health > repair_Teirs[0]) {
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
		cout << "THE SHIP IS IN GREAT CONDITION, NO REEPAIRS NEEDED" << endl;
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
		accurate_Price = missing_Ammo / (2 + players_Artillery[i].get_Ammo_Quality());
		if (accurate_Price < 0 && accurate_Price < 1) {
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

int starship_Depot(ship players_Ship, vector<artillery>& players_Artillery, vector<artillery>& artillery_For_Purchase, int player_Inventory[]) {
	bool done = false;
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
					players_Ship.set_Max_Health(players_Ship.get_Max_Health() + 15);
					for (int i = 0; i < 15 && players_Ship.get_Current_Health() < players_Ship.get_Max_Health(); i++) {
						players_Ship.set_Current_Health(players_Ship.get_Current_Health() + 1);
					}
					cout << "Your health was increased by 15!" << endl;
					press_X_To_Continue_And_Clear();
					
				}
				else if (upgrade_Option == 2) {
					players_Ship.set_Engines_Level(players_Ship.get_Engines_Level() + 1);
					players_Ship.set_Evasiveness(players_Ship.get_Evasiveness() + 5);
					cout << "Your evasiveness was increased by +5%" << endl;
					press_X_To_Continue_And_Clear();
				}
				else if (upgrade_Option == 3) {
					players_Ship.set_Ammo_Reserves_Level(players_Ship.get_Ammo_Reserves_Level() + 1);
					for (int i = 0; i < players_Artillery.size(); i++) {
						double increase = players_Artillery[i].get_Max_Uses() * .1;
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
					players_Ship.set_Max_Energy(players_Ship.get_Max_Energy() + 10);
					cout << "Your energy capacity was increased by 10!" << endl;
					if (!filled) {
						cout << "We also topped off your energy for you! You're good to go" << endl;
					}
					press_X_To_Continue_And_Clear();
				}
				else if (upgrade_Option == 5) {
					players_Ship.set_Nuclear_Reactor_Level(players_Ship.get_Nuclear_Reactor_Level() + 1);
					players_Ship.set_Energy_Regen(players_Ship.get_Energy_Regen() + 5);
					cout << "Your energy regeneration was increased by +5%" << endl;
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

int main() {
	int players_Inventory[4] = { 32, 32, 32, 10 };
	
	vector<artillery> artillery_For_Purchase = {
	artillery("graviton corroder", 30, 60, 35, 10, 20, true, false, false, false, 0, "None") };
	/*
	Stellar Debris (Common), Nebula Shards (Uncommon), Quantum Cores (Rare), Dark Matter Essence (very rare)
	// name, damage, accuracy, attack_Speed, max_Uses, energy_Cost, is_EMP, is_Pulse_Disruptor, is_Plasma_Overload);
	*/
	
	cout << "You are the captain of your very own spaceship, you are going to"
	<< " have to navigate outer space while defending yourself against hostile" 
	<< " space pirates.You start out with basic artillery, but as you progress" 
	<< " you will be able to acquire new types of guns. You will also be able to"
	<< " upgrade your ship with the materials you gain while fighting the enemies "
	<< "you find in space. " << endl << endl;
	string user_Name;
	cout << "What do you want to name your vessel: " << endl;
	getline(cin, user_Name);
	system("cls");

	ship players_Ship(user_Name, 50, 50, 10, 10);
	//name , health, energy, evasiveness, energy regen
	vector<artillery> players_Artillery = {
	artillery( "basic artillery", 15, 95, 50, 30, 5, false, false, false, false, 0, "None") };
	// name, damage, accuracy, attack_Speed, max_Uses, energy_Cost, is_EMP, is_Pulse_Disruptor, is_Plasma_Overload);

		//fight 1, level 1 
	ship enemy_Ship1("Space pirate ship", 35, 20, 15, 25);
	vector<artillery> enemys_Artillery = {
	artillery("Ion Pulse Blaster", 10, 80, 70, 40, 5, false, false, false, false, 0, " "),
	artillery("Basic Rail Gun", 20, 60, 30, 1, 20, false, false, false, false, 0, " ") };
	//combat(players_Ship, players_Artillery, players_Inventory, 1, enemy_Ship1, enemys_Artillery);
	starship_Depot(players_Ship, players_Artillery, artillery_For_Purchase, players_Inventory);
	enemys_Artillery.clear();
	

	//fight2, level 1
	ship enemy_Ship2("Astro bandit", 35, 20, 15, 25);
	enemys_Artillery = {
	artillery("Ion Pulse Blaster", 10, 80, 70, 40, 5, false, false, false, false, 0, " "),
	artillery("Basic Rail Gun", 20, 60, 30, 1, 20, false, false, false, false, 0, " ")};
	combat(players_Ship, players_Artillery, players_Inventory, 1, enemy_Ship2, enemys_Artillery);
	enemys_Artillery.clear();

	//fight 3, level 1
	ship enemy_Ship3("Scavenger", 35, 20, 15, 25);
	 enemys_Artillery = {
	artillery("Ion Pulse Blaster", 10, 80, 70, 40, 5, false, false, false, false, 0, " "),
	artillery("Basic Rail Gun", 20, 60, 30, 1, 20, false, false, false, false, 0, " ") };
	combat(players_Ship, players_Artillery, players_Inventory, 1, enemy_Ship3, enemys_Artillery);
	starship_Depot(players_Ship, players_Artillery, artillery_For_Purchase, players_Inventory);
	enemys_Artillery.clear();


	//2
	//fight 1 level2
	add_Artillery1(artillery_For_Purchase);
	ship enemy_Ship4("Enforcer", 35, 20, 15, 25);
	 enemys_Artillery = {
	artillery("Ion Pulse Blaster", 10, 80, 70, 40, 5, false, false, false, false, 0, " "),
	artillery("Basic Rail Gun", 20, 60, 30, 1, 20, false, false, false, false, 0, " ") };
	combat(players_Ship, players_Artillery, players_Inventory, 2, enemy_Ship4, enemys_Artillery);
	enemys_Artillery.clear();

	//fight 2, level 2
	ship enemy_Ship5("Starbane Raider", 35, 20, 15, 25);
	 enemys_Artillery = {
	artillery("Ion Pulse Blaster", 10, 80, 70, 40, 5, false, false, false, false, 0, " "),
	artillery("Basic Rail Gun", 20, 60, 30, 1, 20, false, false, false, false, 0, " ") };
	combat(players_Ship, players_Artillery, players_Inventory, 2, enemy_Ship5, enemys_Artillery);
	starship_Depot(players_Ship, players_Artillery, artillery_For_Purchase, players_Inventory);
	enemys_Artillery.clear();

	//fight 2, level 2
	ship enemy_Ship6("Scourge", 35, 20, 15, 25);
	 enemys_Artillery = {
	artillery("Ion Pulse Blaster", 10, 80, 70, 40, 5, false, false, false, false, 0, " "),
	artillery("Basic Rail Gun", 20, 60, 30, 1, 20, false, false, false, false, 0, " ") };
	combat(players_Ship, players_Artillery, players_Inventory, 2, enemy_Ship6, enemys_Artillery);
	enemys_Artillery.clear();

	//3
	//fight 1, level 3
	add_Artillery2(artillery_For_Purchase);
	ship enemy_Ship7("Eclipse Marauder", 35, 20, 15, 25);
	 enemys_Artillery = {
	artillery("Ion Pulse Blaster", 10, 80, 70, 40, 5, false, false, false, false, 0, " "),
	artillery("Basic Rail Gun", 20, 60, 30, 1, 20, false, false, false, false, 0, " ") };
	combat(players_Ship, players_Artillery, players_Inventory, 2, enemy_Ship7, enemys_Artillery);
	starship_Depot(players_Ship, players_Artillery, artillery_For_Purchase, players_Inventory);
	enemys_Artillery.clear();

	//fight 2, level 3
	ship enemy_Ship8("Tempest", 35, 20, 15, 25);
	 enemys_Artillery = {
	artillery("Ion Pulse Blaster", 10, 80, 70, 40, 5, false, false, false, false, 0, " "),
	artillery("Basic Rail Gun", 20, 60, 30, 1, 20, false, false, false, false, 0, " ") };
	combat(players_Ship, players_Artillery, players_Inventory, 3, enemy_Ship8, enemys_Artillery);
	enemys_Artillery.clear();

	//fight 3, level 3
	ship enemy_Ship9("Space Vultures", 35, 20, 15, 25);
	 enemys_Artillery = {
	artillery("Ion Pulse Blaster", 10, 80, 70, 40, 5, false, false, false, false, 0, " "),
	artillery("Basic Rail Gun", 20, 60, 30, 1, 20, false, false, false, false, 0, " ") };
	combat(players_Ship, players_Artillery, players_Inventory, 3, enemy_Ship9, enemys_Artillery);
	enemys_Artillery.clear();

	//4
	//fight 1, level 4
	ship enemy_Ship10("Nightmare", 35, 20, 15, 25);
	 enemys_Artillery = {
	artillery("Ion Pulse Blaster", 10, 80, 70, 40, 5, false, false, false, false, 0, " "),
	artillery("Basic Rail Gun", 20, 60, 30, 1, 20, false, false, false, false, 0, " ") };
	combat(players_Ship, players_Artillery, players_Inventory, 4, enemy_Ship10, enemys_Artillery);
	starship_Depot(players_Ship, players_Artillery, artillery_For_Purchase, players_Inventory);
	enemys_Artillery.clear();

	//fight 2, level 4
	ship enemy_Ship11("Star Hunters", 35, 20, 15, 25);
	 enemys_Artillery = {
	artillery("Ion Pulse Blaster", 10, 80, 70, 40, 5, false, false, false, false, 0, " "),
	artillery("Basic Rail Gun", 20, 60, 30, 1, 20, false, false, false, false, 0, " ") };
	combat(players_Ship, players_Artillery, players_Inventory, 4, enemy_Ship11, enemys_Artillery);
	starship_Depot(players_Ship, players_Artillery, artillery_For_Purchase, players_Inventory);
	enemys_Artillery.clear();

	//fight 3, level 4
	ship enemy_Ship12("Shadow Dread", 35, 20, 15, 25);
	 enemys_Artillery = {
	artillery("Ion Pulse Blaster", 10, 80, 70, 40, 5, false, false, false, false, 0, " "),
	artillery("Basic Rail Gun", 20, 60, 30, 1, 20, false, false, false, false, 0, " ") };
	combat(players_Ship, players_Artillery, players_Inventory, 4, enemy_Ship12, enemys_Artillery);
	enemys_Artillery.clear();
	
	//5
	//fight 1, level 5
	add_Artillery3(artillery_For_Purchase);
	ship enemy_Ship13("Raptor", 35, 20, 15, 25);
	 enemys_Artillery = {
	artillery("Ion Pulse Blaster", 10, 80, 70, 40, 5, false, false, false, false, 0, " "),
	artillery("Basic Rail Gun", 20, 60, 30, 1, 20, false, false, false, false, 0, " ") };
	combat(players_Ship, players_Artillery, players_Inventory, 5, enemy_Ship13, enemys_Artillery);
	enemys_Artillery.clear();

	//fight 2, level 5
	ship enemy_Ship14("Galactic Prowler", 35, 20, 15, 25);
	 enemys_Artillery = {
	artillery("Ion Pulse Blaster", 10, 80, 70, 40, 5, false, false, false, false, 0, " "),
	artillery("Basic Rail Gun", 20, 60, 30, 1, 20, false, false, false, false, 0, " ") };
	combat(players_Ship, players_Artillery, players_Inventory, 5, enemy_Ship14, enemys_Artillery);
	starship_Depot(players_Ship, players_Artillery, artillery_For_Purchase, players_Inventory);
	enemys_Artillery.clear();

	//fight 3, level 5
	ship enemy_Ship15("Starborn menace", 35, 20, 15, 25);
	 enemys_Artillery = {
	artillery("Ion Pulse Blaster", 10, 80, 70, 40, 5, false, false, false, false, 0, " "),
	artillery("Basic Rail Gun", 20, 60, 30, 1, 20, false, false, false, false, 0, " ") };
	combat(players_Ship, players_Artillery, players_Inventory, 5, enemy_Ship15, enemys_Artillery);
	enemys_Artillery.clear();

	//6
	//fight 1, level 6
	ship enemy_Ship16("Celestial predator", 35, 20, 15, 25);
	 enemys_Artillery = {
	artillery("Ion Pulse Blaster", 10, 80, 70, 40, 5, false, false, false, false, 0, " "),
	artillery("Basic Rail Gun", 20, 60, 30, 1, 20, false, false, false, false, 0, " ") };
	combat(players_Ship, players_Artillery, players_Inventory, 6, enemy_Ship16, enemys_Artillery);
	starship_Depot(players_Ship, players_Artillery, artillery_For_Purchase, players_Inventory);
	enemys_Artillery.clear();

	//fight 2 level 6
	ship enemy_Ship17("Dreadnought", 35, 20, 15, 25);
	 enemys_Artillery = {
	artillery("Ion Pulse Blaster", 10, 80, 70, 40, 5, false, false, false, false, 0, " "),
	artillery("Basic Rail Gun", 20, 60, 30, 1, 20, false, false, false, false, 0, " ") };
	combat(players_Ship, players_Artillery, players_Inventory, 6, enemy_Ship17, enemys_Artillery);
	enemys_Artillery.clear();

	//fight 3, level 6
	ship enemy_Ship18("Void Stalker", 35, 20, 15, 25);
	 enemys_Artillery = {
	artillery("Ion Pulse Blaster", 10, 80, 70, 40, 5, false, false, false, false, 0, " "),
	artillery("Basic Rail Gun", 20, 60, 30, 1, 20, false, false, false, false, 0, " ") };
	combat(players_Ship, players_Artillery, players_Inventory, 6, enemy_Ship18, enemys_Artillery);
	starship_Depot(players_Ship, players_Artillery, artillery_For_Purchase, players_Inventory);
	enemys_Artillery.clear();
	
	//artillery(ship & players_Ship, string name, int damage, int accuracy, int attack_Speed, int max_Uses, int energy_Cost, bool is_EMP, bool is_Pulse_Disruptor, bool is_Plasma_Overload);
	//combat(players_Ship, players_Artillery, players_Inventory, 1, enemy_Ship1, enemys_Artillery);
	
	
	
	//starship_Depot(players_Ship, players_Artillery, artillery_For_Purchase, players_Inventory);

	return 0;
}
