#include "ship.h"

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

void ship::set_Weaken_Status() {
	weaken_Effect = true;
}
void ship::set_Overheat_Status() {
	overheat_Effect = true;
}
void ship::set_Stun_Status() {
	stun_Effect = true;
}
void ship::set_Corrosion_Status() {
	corrosion_Effect = true;
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

bool ship::get_Weaken_Status() {
	return weaken_Effect;
}
bool ship::get_Overheat_Status() {
	return overheat_Effect;
}
bool ship::get_Stun_Status() {
	return stun_Effect;
}
bool ship::get_Corrode_Status() {
	return corrosion_Effect;
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

artillery::artillery( string name, int damage, int accuracy, int attack_Speed, int max_Uses, int energy_Cost, bool can_Corrode, bool can_Stun, bool can_Weaken, bool can_Overheat, int ammo_Quality, string ability_Name) {
	
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
	set_Ammo_Quality(ammo_Quality);
	set_Ability_Name(ability_Name);
}

//getters
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
void artillery::set_Can_Stun(bool can_Stun) {
	this->can_Stun = can_Stun;
}
void artillery::set_Can_Weaken(bool can_Weaken) {
	this->can_Weaken = can_Weaken;
}
void artillery::set_Can_Overheat(bool can_Overheat) {
	this->can_Overload = can_Overload;
}
void artillery::set_Can_Corrode(bool can_Corrode) {
	this->can_Corrode = can_Corrode;
	
}
void artillery::set_Ammo_Quality(int ammo_Quality) {
	if (ammo_Quality >= 0 && ammo_Quality < 4) {
		this->ammo_Quality = ammo_Quality;
	}
}


