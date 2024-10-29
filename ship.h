#pragma once
#include <string>
#include < vector>
using namespace std;
class ship {
	

public:
	ship(string name, int max_Health, int max_Energy, int evasiveness, int energy_Regen);
	//void print_Current_Statuses();
	
	

	void set_Name(string name);
	void set_Evasiveness(int evassiveness);
	void set_Current_Energy(int current_Energy);
	void set_Max_Energy(int max_Energy);
	void set_Max_Health(int max_Health);
	void set_Current_Health(int current_Health);
	void set_Energy_Regen(int energy_Regen);

	
	void set_Stun_Status(int num_Turns);
	void set_Weaken_Status(int num_Turns);
	void set_Corrosion_Status();
	void cure_Corrosive();
	void set_Disrupted_Status(int num_Turns);

	void set_Hull_Level(int level);
	void set_Engines_Level(int level);
	void set_Ammo_Reserves_Level(int level);
	void set_Power_Core_Level(int level);
	void set_Nuclear_Reactor_Level(int level);

	string get_Name();
	int get_Max_Health();
	int get_Current_Health();
	int get_Current_Energy();
	int get_Max_Energy();
	int get_Evasiveness();
	int get_Energy_Regen();

	bool get_Evaded();
	void set_Evaded(bool evaded);

	
	int get_Stun_Status();
	int get_Weaken_Status();
	int get_Corrode_Status();
	int get_Disrupted_Status();
	int* get_All_Statuses();

	int get_Hull_Level();
	int get_Engines_Level();
	int get_Ammo_Reserves_Level();
	int get_Power_Core_Level();
	int get_Nuclear_Reactor_Level();
	int* get_All_Levels();

	void evade_Action(int accuracy);

	int upgrade_Options(int player_Inventory[]);
	int heal_Options(int player_Inventory[]);

	void print_Detailed_Stats();
	
	
private:

	//corrosion, stun, weaken, and disrupted
	int status_Effects[4] = {0, 0, 0, 0};
	
	//stats
	string name ;
	int max_Health;
	int current_Health;
	int max_Energy;
	int current_Energy;
	int evasiveness;
	int energy_Regen;
	bool evaded = false;

	//hull, engines, ammo reserves, power core, nuclear reactor
	int upgrade_Levels[5] = {0, 0, 0, 0, 0 };
	
};



class artillery {
public: 


	void print_Combat_Info(int num);
	

	artillery(string name, int damage, int accuracy, int attack_Speed, int max_Uses, int energy_Cost, bool can_Corrode, bool can_Stun, bool can_Weaken, bool can_Overheat, bool can_Disrupt, int percent, int ammo_Quality, string ability_Name);

	string get_Ability_Name();
	string get_Name();
	int get_Damage();
	int get_Accuracy();
	int get_Attack_Speed();
	int get_Max_Uses();
	int get_Current_Uses();
	int get_Energy_Cost();
	int get_Ammo_Quality();
	
	
	bool get_Can_Stun();
	bool get_Can_Weaken();
	bool get_Can_Overheat();
	bool get_Can_Corrode();
	bool get_Can_Disrupt();
	int get_Percent();

	void set_Current_Uses(int max_Uses);
	void set_Max_Uses(int max_Uses);
	void set_Percent(int percent);

	void set_Overheat_Status(int num_Turns);
	int can_Apply_Overheat_Status(int percent);
	int get_Overheat_Status();
	

private:
	string ability_Name;
	string name;
	int damage;
	int accuracy;
	int attack_Speed;
	int max_Uses;
	int current_Uses;
	int energy_Cost;
	bool can_Stun;
	bool can_Weaken;
	bool can_Overheat;
	bool can_Corrode;
	bool can_Disrupt;

	int overheat_Status = 0;

	int ammo_Quality;
	int percent;

	void set_Name(string name);
	void set_Damage(int damage);
	void set_Accuracy(int accuracy);
	void set_Attack_Speed(int attack_Speed);
	
	void set_Ability_Name(string ability);
	void set_Ammo_Quality(int ammo_Quality);
	void set_Energy_Cost(int energy_Cost);


	void set_Can_Stun(bool can_Stun);
	void set_Can_Weaken(bool can_Weaken);
	void set_Can_Overheat(bool can_Overheat);
	void set_Can_Corrode(bool can_Corrode);
	void set_Can_Disrupt(bool can_Disrupt);


	
};