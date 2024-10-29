using namespace std;
#include "ship.h"

//name , health, energy, evasiveness, energy regen
ship::ship(string name, int max_Health, int max_Energy, int evasiveness, int energy_Regen) {

	set_Name(name);
	set_Max_Health(max_Health);
	set_Current_Health(max_Health);
	set_Evasiveness(evasiveness);
	set_Max_Energy(max_Energy);
	set_Energy_Regen(energy_Regen);
	
}

// setters
void ship::set_Evasiveness(int evasiveness) {
	if (evasiveness >= 0) {
		this->evasiveness = evasiveness;
	}
}
void ship::set_Current_Energy(int current_Energy) {
	if (current_Energy >= 0) {
		this->current_Energy = current_Energy;
	}
}
void ship::set_Max_Energy(int max_Energy) {
	if (max_Energy > 0) {
		this->max_Energy = max_Energy;
		set_Current_Energy(max_Energy);
	}
}
void ship::set_Max_Health(int max_Health) {
	if (max_Health > 0) {
		this->max_Health = max_Health;
		
	}
	
}
void ship::set_Current_Health(int current_Health) {
	this->current_Health = current_Health;
}
void ship::set_Energy_Regen(int energy_Regen) {
	if (energy_Regen >= 10) {
		this->energy_Regen = energy_Regen;
	}
}
void ship::set_Name(string name) {
	if (!name.empty()) {
		this->name = name;
	}
}

void ship::set_Evaded(bool evaded) {
	this->evaded = evaded;
}

void ship::set_Weaken_Status(int num_Turns) {
	this->status_Effects[2] = num_Turns;
}
void ship::set_Stun_Status(int num_Turns) {
	this->status_Effects[1] = num_Turns;
}

void ship::set_Corrosion_Status() {
	if (status_Effects[0] == 0) {
		status_Effects[0] += 1;
	}
	else {
		status_Effects[0] *= 2;
	}
	
}
void ship::cure_Corrosive() {
	status_Effects[0] = 0;
}
void ship::set_Disrupted_Status(int num_Turns) {
	this->status_Effects[3] = num_Turns;
}

void ship::set_Hull_Level(int level) {
	if (level > 0) {
		this->upgrade_Levels[0] = level;
	}
}
void ship::set_Engines_Level(int level) {
	if (level > 0) {
		this->upgrade_Levels[1] = level;
	}
}
void ship::set_Ammo_Reserves_Level(int level) {
	if (level > 0) {
		this->upgrade_Levels[2] = level;
	}

}
void ship::set_Power_Core_Level(int level) {
	if (level > 0) {
		this->upgrade_Levels[3] = level;
	}
}
void ship::set_Nuclear_Reactor_Level(int level) {
	if (level > 0) {
		this->upgrade_Levels[4] = level;
	}
}


//getters
int ship::get_Max_Health() {
	return max_Health;
}
int ship::get_Current_Health() {
	return current_Health;
}
int ship::get_Current_Energy() {
	return current_Energy;
}
int ship::get_Max_Energy() {
	return max_Energy;
}
int ship::get_Evasiveness() {
	return evasiveness;
}
int ship::get_Energy_Regen() {
	return energy_Regen;
}


string ship::get_Name() {
	return name;
}

int ship::get_Weaken_Status() {
	return status_Effects[2];
}

int ship::get_Stun_Status() {
	return status_Effects[1];
}
int ship::get_Corrode_Status() {
	return status_Effects[0];
}
int ship::get_Disrupted_Status() {
	return status_Effects[3];
}
int* ship::get_All_Statuses() {
	return status_Effects;
}


bool ship::get_Evaded() {
	return evaded;
}


int ship::get_Hull_Level() {
	return upgrade_Levels[0];
}
int ship::get_Engines_Level() {
	return upgrade_Levels[1];
}
int ship::get_Ammo_Reserves_Level() {
	return upgrade_Levels[2];
}
int ship::get_Power_Core_Level() {
	return upgrade_Levels[3];
}
int ship::get_Nuclear_Reactor_Level() {
	return upgrade_Levels[4];
}
int* ship::get_All_Levels() {
	return upgrade_Levels;
}





// artillery class info
// name, damage, accuracy, attack speed, max uses, energy cost, corrode, stun, weaken, overheat, disrupt, status chance, ammo quality, ability name
artillery::artillery( string name, int damage, int accuracy, int attack_Speed, int max_Uses, int energy_Cost, bool can_Corrode, bool can_Stun, bool can_Weaken, bool can_Overheat, bool can_Disrupt, int percent, int ammo_Quality, string ability_Name) {
	
	set_Name(name);
	set_Damage(damage);
	set_Accuracy(accuracy);
	set_Attack_Speed(attack_Speed);
	set_Max_Uses(max_Uses);
	set_Current_Uses(max_Uses);
	set_Energy_Cost(energy_Cost);
	set_Can_Overheat(can_Overheat);
	set_Can_Weaken(can_Weaken);
	set_Can_Stun(can_Stun);
	set_Can_Disrupt(can_Disrupt);
	set_Can_Corrode(can_Corrode);
	set_Ammo_Quality(ammo_Quality);
	set_Ability_Name(ability_Name);
	set_Percent(percent);
}

//getters
int artillery::get_Percent() {
	return percent;
}
int artillery::get_Damage() {
	return damage;
}
int artillery::get_Accuracy() {
	return accuracy;
}
int artillery::get_Attack_Speed() {
	return attack_Speed;
}
int artillery::get_Max_Uses() {
	return max_Uses;
}
int artillery::get_Current_Uses() {
	return current_Uses;
}
int artillery::get_Energy_Cost() {
	return energy_Cost;
}
int artillery::get_Ammo_Quality() {
	return ammo_Quality;
}
string artillery::get_Name() {
	return name;
}


string artillery::get_Ability_Name() {
	return ability_Name;
}
bool artillery::get_Can_Corrode() {
	return can_Corrode;
}
bool artillery::get_Can_Disrupt() {
	return can_Disrupt;
}
bool artillery::get_Can_Overheat() {
	return can_Overheat;
}
bool artillery::get_Can_Weaken() {
	return can_Weaken;
}
bool artillery::get_Can_Stun() {
	return can_Stun;
}

int artillery::get_Overheat_Status() {
	return overheat_Status;
}
//setters
void artillery::set_Ability_Name(string ability_Name) {
	if (!ability_Name.empty()) {
		this->ability_Name = ability_Name;
	}
}
void artillery::set_Name(string name) {
	if (!name.empty()) {
		this->name = name;
	}
}
void artillery::set_Damage(int damage) {
	if (damage > 0) {
		this->damage = damage;
	}
}
void artillery::set_Accuracy(int accuracy) {
	if (accuracy >= 0) {
		this->accuracy = accuracy;
	}
}
void artillery::set_Attack_Speed(int attack_Speed) {
	if (attack_Speed > 0) {
		this->attack_Speed = attack_Speed;
	}
}
void artillery::set_Max_Uses(int max_Uses) {
	if (max_Uses > 0) {
		this->max_Uses = max_Uses;
	}
}
void artillery::set_Current_Uses(int current_Uses) {
	if (current_Uses > 0) {
		this->current_Uses = current_Uses;
	}
}
void artillery::set_Energy_Cost(int energy_Cost) {
	if (energy_Cost > 0) {
		this->energy_Cost = energy_Cost;
	}
}
void artillery::set_Percent(int percent) {
	if (percent >= 0) {
		this->percent = percent;
	}
}

void artillery::set_Overheat_Status(int num_Turns) {
	overheat_Status = num_Turns;
}

void artillery::set_Can_Stun(bool can_Stun) {
	this->can_Stun = can_Stun;
}
void artillery::set_Can_Weaken(bool can_Weaken) {
	this->can_Weaken = can_Weaken;
}
void artillery::set_Can_Overheat(bool can_Overheat) {
	this->can_Overheat = can_Overheat;
}
void artillery::set_Can_Corrode(bool can_Corrode) {
	this->can_Corrode = can_Corrode;
	
}
void artillery::set_Can_Disrupt(bool can_Disrupt) {
	this->can_Disrupt = can_Disrupt;
}

void artillery::set_Ammo_Quality(int ammo_Quality) {
	if (ammo_Quality >= 0 && ammo_Quality < 4) {
		this->ammo_Quality = ammo_Quality;
	}
}


