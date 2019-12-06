// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
//#include <ncurses.h>
using namespace std;
int PHealth = 100;

struct battle_health {
    int PHealth;
    int EHealth;
};
struct character_dice {
    int dice1;
    int dice2;
    int dice3;
};

//function: rolls a number based on the users buffs, debuffs and type of die
//buff: the amount the player is buffed
//redu: the amount the player is debuffed
//type: the type of die the player is using (out of 2/3/6/etc)

int roll(int type, int buff, int redu);

// Boss first attack 
    // PHealth is the players health, subtracts boss rolls and damage
    /// ebuff is amount enemy is buffed
    // eredu is amount the boss is debuffed

battle_health first_enemy(battle_health battleHP, int ebuff, int eredu);
// function: boss attack on player 
// dice: rolls a random number from dice
// PHealth: Players health after boss attacks

battle_health first_enemy_atk(int dice, battle_health battleHP);
//function: Player heals themselves
//heal: takes dice roll and adds that to the players health
// PHealth: players health after heal 

battle_health heal(int heal, battle_health battleHP);
// Players attack on boss
// damage: players damage from their roll 
// EHealth: enemies health after the players damage roll has been subtracted from it
battle_health attack(int damage, battle_health battleHP);


//function: player turn
battle_health Pturn(battle_health battleHP, int buff, int redu);

battle_health Dice1(int pdice, battle_health battleHP);

battle_health battle1(battle_health battleHP, int buff, int redu, int ebuff, int eredu);
/////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    battle_health battleHP;
    battleHP.PHealth = PHealth;
    battleHP.EHealth = 20;
    srand(time(0));
    battle1(battleHP, 0, 0, 0, 0);
    
}

/////////////////////////////////////////////////////////////////////////////////////////

int roll(int type, int buff, int redu)
{
    int roll;
    roll = (rand() % type + 1) + buff - redu;
    if (roll < 0)
    {
        roll = 0;
    }
    return roll;
}


battle_health first_enemy(battle_health battleHP, int ebuff, int eredu)
{
    int dice1 = roll(2, ebuff, eredu);
    int dice2 = roll(3, ebuff, eredu);
    int dice3 = roll(5, ebuff, eredu);

    cout << "The Dragon rolled " << dice1 << " " << dice2 << " " << dice3 << endl;

    battleHP = first_enemy_atk(dice1, battleHP);
    battleHP = first_enemy_atk(dice2, battleHP);
    battleHP = first_enemy_atk(dice3, battleHP);

    return battleHP;
}
//
battle_health first_enemy_atk(int dice, battle_health battleHP)
{
    cout << "The enemy attack deals " << dice << " damage!" << endl;
    battleHP.PHealth = battleHP.PHealth - dice;
    return battleHP;
}

battle_health heal(int heal, battle_health battleHP)
{
    cout << "You healed " << heal << " health!" << endl;
    battleHP.PHealth = battleHP.PHealth + heal;
    return battleHP;
}

battle_health attack(int damage, battle_health battleHP)
{
    cout << "You dealt " << damage << " to the Boss!" << endl;
    battleHP.EHealth = battleHP.EHealth - damage;
    return battleHP;
}

battle_health Dice1(int pdice, battle_health battleHP)
{
    string Response;
    cout << "This dice rolled a " << pdice << "!" << endl
        << "Would you like to Attack or Heal?" << endl;
    cin >> Response;
    if (Response == "Attack" || "attack" || "atk")
    {
        battleHP = attack(pdice, battleHP);
    }
    else if (Response == "Heal" || "heal")
    {
        battleHP = heal(pdice, battleHP);
    }
    return battleHP;
}

battle_health Pturn(battle_health battleHP, int buff, int redu)
{
    cout << "Player turn!" << endl;

    int pdice1 = roll(4, buff, redu);
    int pdice2 = roll(4, buff, redu);
    int pdice3 = roll(4, buff, redu);

    cout << "You rolled the following numbers in this order: "
        << pdice1 << " " << pdice2 << " " << pdice3 << endl;

    battleHP = Dice1(pdice1, battleHP);
    battleHP = Dice1(pdice2, battleHP);
    battleHP = Dice1(pdice3, battleHP);
    return battleHP;
}

battle_health battle1(battle_health battleHP, int buff, int redu, int ebuff, int eredu)
{
    int turn = 1;
    while (battleHP.PHealth && battleHP.EHealth >= 0)
    {
        
        cout << endl << "Turn " << turn << endl << endl
            << "Player Health: " << battleHP.PHealth << " "
            << "Enemy Health: " << battleHP.EHealth << endl;

        battleHP = Pturn(battleHP, buff, redu);

        cout << "Enemy turn!" << endl;

        battleHP = first_enemy(battleHP,ebuff, eredu);

        turn = turn + 1;
        
    }

    if (battleHP.EHealth <= 0)
    {
        cout << endl << "Victory!!!" << endl;
    }
    else if (battleHP.PHealth <= 0)
    {
        cout << endl << "Defeat..." << endl;
    }
    return battleHP;
}
