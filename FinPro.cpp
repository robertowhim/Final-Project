//Group Members: Roberto M Martinez and Ethan Chen
//Date: 12/12/19
// Summary: This program runs a game in where the user takes on
// an enemy through a turn based battle. The player will have dice
// with certain actions and the players may choose what actions the
// dice do in order to beat the enemy. After the player defeat the enemy,
// they will continue to fight enemies until they have defeated all of them.

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cassert>
//#include <ncurses.h>
using namespace std;

///////////////////////////////////////////////////////////////////////////////

//Data Structures

struct game_state {
    int PHealth;
    int EHealth;
    int buff;
    int redu;
    int ebuff;
    int eredu;
    int ecount;
};
struct character_dice {
    int dice1;
    int dice2;
    int dice3;
};

///////////////////////////////////////////////////////////////////////////////

//Functions

//function: rolls a number based on the users buffs, debuffs and type of die
// In:takes in the number to do the RNG from and buffs and reductions to reduce
//the output number
//Out: The number randomly generated using the 3 variables
int roll(int type, int buff, int redu);
//Function and IO's same as the top one, just this one has a buff that affects
//the outcome number less, so the buff doesnt grow very fast
int buff_roll(int type, int buff, int redu);

//Function: Displays to the user the available dice to choose from.
void display_dice_options();

//Function: Lets the user input what dice they would like to use and saves
//those options
//In: User input for the type of dice, and a list to record on.
//Out: A saved list of the type of dice the user wanted
character_dice dice_selection(character_dice user_dice);

//Function: (Cat) The first enemy of the game, only attacks until it reaches
//a health threshhold and then it buffs itself and debuffs you
//In: the current state of it's stats and the user's stats
//Out: damage and buffs applied after it's turn is over
game_state first_enemy(game_state battleHP);

//Function: Cannon, buffs itself until it reaches a high
//enough buff number and unleashes a strong attack
//I/O sames as 1st enemy
game_state second_enemy(game_state battleHP);

//Function: Evil Tree, attacks, heals and buffs itself. After a 
//certain HP threshold it, heals itself by alot
//I/O sames as 1st enemy
game_state third_enemy(game_state battleHP);

//Function: Baby Dragon, attacks and buffs itself by alot.
//It's suppose to imitate a glass cannon. (Hard hitting, but frail)
//I/O sames as 1st enemy
game_state fourth_enemy(game_state battleHP);

//Function: Mean Dwarf, it uses tons of reductions on you, and
//weakens you.
//I/O sames as 1st enemy
game_state fifth_enemy(game_state battleHP);

//Function: Demon King, attacks 3 times and reduces you and at the
//same time it slowly gains strength over time (turns).
//I/O sames as 1st enemy
game_state final_boss(game_state battleHP);

//Function: The enemy's attack action, reduces user's health.
//In: The strength of the dice used, and players HP.
//Out: The new player health after taking the damage from enemy.
game_state enemy_atk(int dice, game_state battleHP);

//Function: The enemy's heal action, increases enemy's health.
//In: The strength of the dice used and the health of the enemy.
//Out: The new enemy health after the healing is done.
game_state enemy_heal(int heal, game_state battleHP);

//Function: The user's action to increase their current health.
//In: The numbers to determine how much is healed, and the current user health.
//Out: The health of the user after being healed.
game_state heal(int heal, game_state battleHP);

//Function: The user's action to attack the enemy and deal damage.
//In: The number to determine the strength of the attack and the enemy health.
//Out: The new enemy health after taking damage from your attack.
game_state attack(int damage, game_state battleHP);

//Function: The user's action to reduce the enemy's roll numbers.
//In: The number to determine the strength of the reduction and the enemy's reduction amount.
//Out: The new enemy reduction value.
game_state redu(int redu, game_state battleHP);

//Function: The enemy's action to reduce the player's roll numbers.
//In: The number to determine the strength of the reduction and the player's reduction amount.
//Out: The new player reduction value.
game_state eredu(int eredu, game_state battleHP);

//Function: The user's action to buff their own roll numbers.
//In: The number to determine the strength of the buff and the player's buff value.
//Out: The new player buff value.
game_state buff(int buff, game_state battleHP);

//Function: The enemy's action to buff their own roll numbers.
//In: The number to determine the strength of the buff and the enemy's buff value.
//Out: The new enemy buff value.
game_state ebuff(int ebuff, game_state battleHP);

//Function: It setups up the format of how the player takes their turn.
// Going one by one for each dice, and determining which one to use.
//In: The dice chosen by the player to do actions with and the stats of both the player
// and the enemy
//Out: The stats of both the player and the enemy due to the potential buffs/debuffs/
// damage/heals that can happen in the turn.
game_state Pturn(game_state battleHP, character_dice user_dice);

//Function: These dice have a possible of 5 actions and use two of them. They help the player
//Attack,Heal, Buff and Reduce. Their strength of their Dice, is determined by their actions.
//In: They take in the state of battle, like buffs and debuffs, and use their own RNG
//to produce the strength of the dice
//Out: They output the stat changes of the game, from health differences, to buffs.
game_state Dice1(game_state battleHP);
game_state Dice2(game_state battleHP);
game_state Dice3(game_state battleHP);
game_state Dice4(game_state battleHP);
game_state Dice5(game_state battleHP);

//Function: Chooses what dice to be used for an action depending on the 
// user's dice selection.
//Input: Needs the game state and the type of dice to use.
//Output: Uses the corresponding dice dpeneding on the type.
game_state dice_battle_selection(game_state battleHP, int dice_number);

//Function: Switches between the turns of the user and enemy. Keeps tracks of the 
//turns that have passed by and determines when the game is over and what enemy to fight.
//In: The game state, the dice the player chose and the type of enemy to fight.
//Out: The winner of the fight and the health of the players.
game_state battle(game_state battleHP, character_dice user_dice, int type);

//Function: Sets up the stats at the beginning of every fight, depending on the
//type of enemy to fight and to make sure the values of buffs and debuffs are reset.
//In: The current stats and the type of monster to set up the stats for.
//Out: the reset stats with the determined health for the monster
game_state stat_setup(game_state battleHP, int type);

//Function: Displays an intro for each monster when a fight is about to start.
void monster_intro(int type);

//Function: Runs the game
void game(game_state battleHP, character_dice user_dice);

/////////////////////////////////////////////////////////////////////////////////////////

//Tests

bool test_character_dice(character_dice one, character_dice two);
bool test_game_state(game_state one, game_state two);
void test_roll();
void test_dice_selection();
void test_first_enemy();
//void test_second_enemy();
void test_enemy_atk();
void test_attack();
void test_enemy_heal();
void test_heal();
void test_ebuff();
void test_buff();
void test_eredu();
void test_redu();

/////////////////////////////////////////////////////////////////////////////////////////

void test();

void run();

int main() {

    char t;

    cout << "Enter [t] to test, or any other character to run." << endl;

    cin >> t;

    if (t == 't') {

        test();

    }
    else {

        run();

    }

}

//Test Function call

void test() {

    test_roll();
    test_dice_selection();
    test_first_enemy();
    test_enemy_atk();
    //test_second_enemy();
    test_attack();
    test_enemy_heal();
    test_heal();
    test_ebuff();
    test_buff();
    test_eredu();
    test_redu();
    

}

//Run

void run() {
    srand(time(0));
    character_dice user_dice = { user_dice.dice1 = 0, user_dice.dice2 = 0, user_dice.dice3 = 0 };
    game_state battleHP;
    user_dice = dice_selection(user_dice);
    battleHP.PHealth = 100;
    battleHP.EHealth = 30;
    battleHP.ebuff = 0;
    battleHP.eredu = 0;
    battleHP.redu = 0;
    battleHP.buff = 0;
    battleHP.ecount = 0;
    game(battleHP, user_dice);
}

/**
Pseudocode:
#Have a Game running.
##Have the player custimize their character
##Have a battle between the player and enemy
### Have the player take a turn.
#### Determine actions based off player's dice.
##### Have the players actions affect the enemy or player.
#### Have the player choose the actions of their moves.
#### Display information of the current state of the game.
### Have the enemy take a turn.
#### Determine what type of attacks the enemy has.
#### Have the enemy do actions.
##### Have the enemy's actions affect the enemy or player.
### Determine if the player or enemy has won.

**/
///////////////////////////////////////////////////////////////////////////////

//Function Definitions

bool test_character_dice(character_dice one, character_dice two)
{   
    bool test = one.dice1 == two.dice1 
        && one.dice2 == two.dice2 
        && one.dice3 == two.dice3;
    return test;
}

bool test_game_state(game_state one, game_state two)
{
    bool test = one.PHealth == two.PHealth
        && one.EHealth == two.EHealth
        && one.buff == two.buff
        && one.ebuff == two.ebuff
        && one.redu == two.redu
        && one.eredu == two.eredu
        && one.ecount == two.ecount;
    return test;
}

void test_roll()
{
    assert(roll(0,5,10) == 0);
    assert(roll(10,10,30) == 0);
    assert(buff_roll(3,20,5) == 0);
}

void test_dice_selection()
{
    character_dice one;
    one.dice1 = 0;
    one.dice2 = 0;
    one.dice3 = 0;
    character_dice two;
    two.dice1 = 1;
    two.dice2 = 1;
    two.dice3 = 1;
    assert(test_character_dice(dice_selection(one),two));
}

void test_first_enemy()
{
    game_state one;
    one.EHealth = 1;
    one.PHealth = 1;
    one.ebuff = 0;
    one.eredu = 10;
    one.buff = 0;
    one.redu = 0;
    one.ecount = 0;
    game_state two;
    two.EHealth = 1;
    two.PHealth = 1;
    two.ebuff = 5;
    two.eredu = 10;
    two.buff = 0;
    two.redu = 5;
    two.ecount = 1;
    assert(test_game_state(first_enemy(one), two));
}
/**
void test_second_enemy()
{
    game_state one;
    one.EHealth = 1;
    one.PHealth = 1;
    one.ebuff = 0;
    one.eredu = 13;
    one.buff = 0;
    one.redu = 0;
    one.ecount = 0;
    game_state two;
    two.EHealth = 1;
    two.PHealth = 1;
    two.ebuff = 3;
    two.eredu = 13;
    two.buff = 0;
    two.redu = 0;
    two.ecount = 0;
    assert(test_game_state(second_enemy(one), two));
}
**/

void test_enemy_atk()
{   
    game_state one;
    one.EHealth = 10;
    one.PHealth = 10;
    one.ebuff = 0;
    one.eredu = 0;
    one.buff = 0;
    one.redu = 0;
    one.ecount = 0;
    game_state two;
    two.EHealth = 10;
    two.PHealth = 9;
    two.ebuff = 0;
    two.eredu = 0;
    two.buff = 0;
    two.redu = 0;
    two.ecount = 0;
    assert(test_game_state(enemy_atk(1,one), two));   
}

void test_attack()
{
    game_state one;
    one.EHealth = 10;
    one.PHealth = 10;
    one.ebuff = 0;
    one.eredu = 0;
    one.buff = 0;
    one.redu = 0;
    one.ecount = 0;
    game_state two;
    two.EHealth = 9;
    two.PHealth = 10;
    two.ebuff = 0;
    two.eredu = 0;
    two.buff = 0;
    two.redu = 0;
    two.ecount = 0;
    assert(test_game_state(attack(1, one), two));
}

void test_heal()
{
    game_state one;
    one.EHealth = 10;
    one.PHealth = 10;
    one.ebuff = 0;
    one.eredu = 0;
    one.buff = 0;
    one.redu = 0;
    one.ecount = 0;
    game_state two;
    two.EHealth = 10;
    two.PHealth = 11;
    two.ebuff = 0;
    two.eredu = 0;
    two.buff = 0;
    two.redu = 0;
    two.ecount = 0;
    assert(test_game_state(heal(1, one), two));
}

void test_enemy_heal()
{
    game_state one;
    one.EHealth = 10;
    one.PHealth = 10;
    one.ebuff = 0;
    one.eredu = 0;
    one.buff = 0;
    one.redu = 0;
    one.ecount = 0;
    game_state two;
    two.EHealth = 11;
    two.PHealth = 10;
    two.ebuff = 0;
    two.eredu = 0;
    two.buff = 0;
    two.redu = 0;
    two.ecount = 0;
    assert(test_game_state(enemy_heal(1, one), two));
}

void test_ebuff()
{
    game_state one;
    one.EHealth = 10;
    one.PHealth = 10;
    one.ebuff = 0;
    one.eredu = 0;
    one.buff = 0;
    one.redu = 0;
    one.ecount = 0;
    game_state two;
    two.EHealth = 10;
    two.PHealth = 10;
    two.ebuff = 1;
    two.eredu = 0;
    two.buff = 0;
    two.redu = 0;
    two.ecount = 0;
    assert(test_game_state(ebuff(1, one), two));
}

void test_buff()
{
    game_state one;
    one.EHealth = 10;
    one.PHealth = 10;
    one.ebuff = 0;
    one.eredu = 0;
    one.buff = 0;
    one.redu = 0;
    one.ecount = 0;
    game_state two;
    two.EHealth = 10;
    two.PHealth = 10;
    two.ebuff = 0;
    two.eredu = 0;
    two.buff = 1;
    two.redu = 0;
    two.ecount = 0;
    assert(test_game_state(buff(1, one), two));
}

void test_eredu()
{
    game_state one;
    one.EHealth = 10;
    one.PHealth = 10;
    one.ebuff = 0;
    one.eredu = 0;
    one.buff = 0;
    one.redu = 0;
    one.ecount = 0;
    game_state two;
    two.EHealth = 10;
    two.PHealth = 10;
    two.ebuff = 0;
    two.eredu = 0;
    two.buff = 0;
    two.redu = 1;
    two.ecount = 0;
    assert(test_game_state(eredu(1, one), two));
}

void test_redu()
{
    game_state one;
    one.EHealth = 10;
    one.PHealth = 10;
    one.ebuff = 0;
    one.eredu = 0;
    one.buff = 0;
    one.redu = 0;
    one.ecount = 0;
    game_state two;
    two.EHealth = 10;
    two.PHealth = 10;
    two.ebuff = 0;
    two.eredu = 1;
    two.buff = 0;
    two.redu = 0;
    two.ecount = 0;
    assert(test_game_state(redu(1, one), two));
}

int roll(int type, int buff, int redu)
{
    int roll;
    roll = (rand() % (type + 1)) + (2 * buff) - redu;
    if (roll < 0)
    {
        roll = 0;
    }
    return roll;
}

int buff_roll(int type, int buff, int redu)
{
    int roll;
    roll = (rand() % (type + 1)) + (buff / 10) - redu;
    if (roll < 0)
    {
        roll = 0;
    }
    return roll;
}
void display_dice_options()
{
    cout << "Dice 1: Max Roll = 12 Commands: Attack/Heal" << endl
        << "Dice 2: Max Roll = 3 Commands: Buff/Heal" << endl
        << "Dice 3: Max Roll = 3 Commands: Buff/Attack" << endl
        << "Dice 4: Max Roll = 6 Commands: Reduce/Attack" << endl
        << "Dice 5: Max Roll = 6 Commands: Reduce/Heal" << endl;
}
character_dice dice_selection(character_dice user_dice)
{
    cout << "What dice would you like for your 1st dice?" << endl
        << "Input the number corresponding to the dice" << endl;
    display_dice_options();
    cin >> user_dice.dice1;
    cout << "What dice would you like for your 2nd dice?" << endl
        << "Input the number corresponding to the dice" << endl;
    display_dice_options();
    cin >> user_dice.dice2;
    cout << "What dice would you like for your 3rd dice?" << endl
        << "Input the number corresponding to the dice" << endl;
    display_dice_options();
    cin >> user_dice.dice3;
    return user_dice;
}
game_state enemy_fight(game_state battleHP, int type)
{
    if (type == 1)
    {
        battleHP = first_enemy(battleHP);
    }
    else if (type == 2)
    {
        battleHP = second_enemy(battleHP);
    }
    else if (type == 3)
    {
        battleHP = third_enemy(battleHP);
    }
    else if (type == 4)
    {
        battleHP = fourth_enemy(battleHP);
    }
    else if (type == 5)
    {
        battleHP = fifth_enemy(battleHP);
    }
    else if (type == 6)
    {
        battleHP = final_boss(battleHP);
    }
    return battleHP;
}
//Cat Health 30
game_state first_enemy(game_state battleHP)
{
    int dice1 = roll(10, battleHP.ebuff, battleHP.eredu);
    int dice2 = roll(7, battleHP.ebuff, battleHP.eredu);
    int dice3 = roll(5, battleHP.ebuff, battleHP.eredu);
    cout << "The Cat rolled " << dice1 << " " << dice2 << " " << dice3 << endl;
    battleHP = enemy_atk(dice1, battleHP);
    battleHP = enemy_atk(dice2, battleHP);
    battleHP = enemy_atk(dice3, battleHP);
    if (battleHP.EHealth < 10 && battleHP.ecount < 1)
    {
        cout << "The Cat put on a hat! Your rolls are reduced by 5!!!" << endl
            << "The Cat's rolls are increased by 5!!!" << endl;
        battleHP.ebuff = 5;
        battleHP.redu = 5;
        battleHP.ecount = 1;
    }

    return battleHP;
}

game_state enemy_atk(int dice, game_state battleHP)
{
    cout << "The enemy attack deals " << dice << " damage!" << endl;
    battleHP.PHealth = battleHP.PHealth - dice;
    return battleHP;
}
//Cannon Health 100
game_state second_enemy(game_state battleHP)
{
    int dice1 = buff_roll(10, battleHP.ebuff, battleHP.eredu);
    int dice2 = buff_roll(10, battleHP.ebuff, battleHP.eredu);
    int dice3 = buff_roll(10, battleHP.ebuff, battleHP.eredu);
    cout << "The Cannon is charging for 3 " << dice1 << " " << dice2 << " " << dice3 << endl;
    battleHP.ebuff = battleHP.ebuff + 3;
    battleHP = ebuff(dice1, battleHP);
    battleHP = ebuff(dice2, battleHP);
    battleHP = ebuff(dice3, battleHP);
    if (battleHP.ebuff >= 70 && battleHP.ecount < 1)
    {
        cout << "The Cannon is almost finished charging!" << endl;
        battleHP.ecount = 1;
    }
    if (battleHP.ebuff >= 100)
    {
        int damage = roll(1, battleHP.ebuff, battleHP.eredu);
        cout << "The Cannon attacked! Dealt " << damage << " damage!" << endl;
        battleHP.PHealth = battleHP.PHealth - damage;
    }

    return battleHP;
}
//Tree Health 60
game_state third_enemy(game_state battleHP)
{
    int dice1 = buff_roll(3, battleHP.ebuff, battleHP.eredu);
    int dice2 = roll(7, battleHP.ebuff, battleHP.eredu);
    int dice3 = roll(7, battleHP.ebuff, battleHP.eredu);
    cout << "The evil Tree rolled " << dice1 << " " << dice2 << " " << dice3 << endl;
    cout << "It healed itself for 4!" << endl;
    battleHP.EHealth = battleHP.EHealth + 4;
    battleHP = ebuff(dice1, battleHP);
    battleHP = enemy_atk(dice2, battleHP);
    battleHP = enemy_heal(dice3, battleHP);
    if (battleHP.EHealth <= 30 and battleHP.ecount < 1)
    {
        cout << "Emergency heal! The evil Tree healed 20 damage!" << endl;
        battleHP.EHealth = battleHP.EHealth + 20;
        battleHP.ecount = 1;
    }
    return battleHP;
}

game_state fourth_enemy(game_state battleHP)
{
    cout << "Baby Dragon is growing by 3..." << endl;
    battleHP.ebuff = battleHP.ebuff + 3;
    int dice1 = roll(10, battleHP.ebuff, battleHP.eredu);
    int dice2 = roll(7, battleHP.ebuff, battleHP.eredu);
    int dice3 = roll(8, battleHP.ebuff, battleHP.eredu);
    cout << "The Baby Dragon rolled " << dice1 << " " << dice2 << " " << dice3 << endl;
    battleHP = ebuff(dice1, battleHP);
    battleHP = enemy_atk(dice2, battleHP);
    battleHP = enemy_atk(dice3, battleHP);
    return battleHP;
}

game_state fifth_enemy(game_state battleHP)
{
    int dice1 = roll(6, battleHP.ebuff, battleHP.eredu);
    int dice2 = roll(8, battleHP.ebuff, battleHP.eredu);
    int dice3 = roll(2, battleHP.ebuff, battleHP.eredu);
    cout << "The mean Dwarf rolled " << dice1 << " " << dice2 << " " << dice3 << endl
        << "Mean Dwarf insulted you with &^%*$#@, you were reduced by 2" << endl;
    battleHP.redu = battleHP.redu + 2;
    battleHP = enemy_atk(dice1, battleHP);
    battleHP = eredu(dice2, battleHP);
    battleHP = ebuff(dice3, battleHP);
    if (battleHP.EHealth < 40 && battleHP.ecount < 1)
    {
        cout << "The mean Dwarf intensifies..." << endl << "It buffed itself by 7!";
        battleHP.ebuff = battleHP.ebuff + 7;
        battleHP.ecount = 1;
    }
    return battleHP;
}
game_state final_boss(game_state battleHP)
{
    int dice1 = roll(10, battleHP.ebuff, battleHP.eredu);
    int dice2 = roll(10, battleHP.ebuff, battleHP.eredu);
    int dice3 = roll(10, battleHP.ebuff, battleHP.eredu);
    int dice4 = roll(3, battleHP.ebuff, battleHP.eredu);
    cout << "The Demon King rolled " << dice1 << " " << dice2 << " " << dice3
        << " " << dice4 << " " << 1 << endl;
    battleHP = enemy_atk(dice1, battleHP);
    battleHP = enemy_atk(dice2, battleHP);
    battleHP = enemy_atk(dice3, battleHP);
    battleHP = eredu(dice4, battleHP);
    battleHP.ebuff = battleHP.ebuff + 1;
    cout << "The Demon King's power rose by 1!" << endl;
    return battleHP;
}

game_state heal(int heal, game_state battleHP)
{
    cout << "You healed " << heal << " health!" << endl;
    battleHP.PHealth = battleHP.PHealth + heal;
    return battleHP;
}
game_state enemy_heal(int heal, game_state battleHP)
{
    cout << "The enemy healed " << heal << " health!" << endl;
    battleHP.EHealth = battleHP.EHealth + heal;
    return battleHP;
}
game_state attack(int damage, game_state battleHP)
{
    cout << "You dealt " << damage << " to the Enemy!" << endl;
    battleHP.EHealth = battleHP.EHealth - damage;
    return battleHP;
}
game_state buff(int buff, game_state battleHP)
{
    cout << "You buffed " << buff << " to yourself!" << endl;
    battleHP.buff = battleHP.buff + buff;
    return battleHP;
}
game_state ebuff(int ebuff, game_state battleHP)
{
    cout << "The enemy buffed " << ebuff << " to itself!" << endl;
    battleHP.ebuff = battleHP.ebuff + ebuff;
    return battleHP;
}
game_state redu(int redu, game_state battleHP)
{
    cout << "You weakend the Enemy by " << redu << "!" << endl;
    battleHP.eredu = battleHP.eredu + redu;
    return battleHP;
}
game_state eredu(int eredu, game_state battleHP)
{
    cout << "The enemy weakened you by " << eredu << "!" << endl;
    battleHP.redu = battleHP.redu + eredu;
    return battleHP;
}
game_state Dice1(game_state battleHP)
{
    int pdice = roll(12, battleHP.buff, battleHP.redu);
    string Response;
    cout << endl << "This dice rolled a " << pdice << "!" << endl;
    while (Response != "Attack" && Response != "atk" && Response != "Heal" && pdice != 0)
    {
        cout << "Would you like to Attack or Heal?" << endl;
        cin >> Response;
        if (Response != "Attack" && Response != "atk" && Response != "Heal")
        {
            cout << "That's an invalid input, retry!" << endl;
        }
    }
    if (Response == "Attack" || Response == "atk")
    {
        battleHP = attack(pdice, battleHP);
    }
    else if (Response == "Heal")
    {
        battleHP = heal(pdice, battleHP);
    }
    return battleHP;
}
game_state Dice2(game_state battleHP)
{
    int pdice = buff_roll(3, battleHP.buff, battleHP.redu);
    string Response;
    cout << endl << "This dice rolled a " << pdice << "!" << endl;
    while (Response != "Buff" && Response != "Heal" && pdice != 0)
    {
        cout << "Would you like to Buff or Heal?" << endl;
        cin >> Response;
        if (Response != "Buff" && Response != "Heal")
        {
            cout << "That's an invalid input, retry!" << endl;
        }
    }
    if (Response == "Buff")
    {
        battleHP = buff(pdice, battleHP);
    }
    else if (Response == "Heal")
    {
        battleHP = heal(pdice, battleHP);
    }
    return battleHP;
}
game_state Dice3(game_state battleHP)
{
    int pdice = buff_roll(3, battleHP.buff, battleHP.redu);
    string Response;
    cout << endl << "This dice rolled a " << pdice << "!" << endl;
    while (Response != "Buff" && Response != "Attack" && Response != "atk" && pdice != 0)
    {
        cout << "Would you like to Buff or Attack?" << endl;
        cin >> Response;
        if (Response != "Buff" && Response != "Attack" && Response != "atk")
        {
            cout << "That's an invalid input, retry!" << endl;
        }
    }
    if (Response == "Buff")
    {
        battleHP = buff(pdice, battleHP);
    }
    else if (Response == "Attack" || Response == "atk")
    {
        battleHP = attack(pdice, battleHP);
    }
    return battleHP;
}
game_state Dice4(game_state battleHP)
{
    int pdice = buff_roll(6, battleHP.buff, battleHP.redu);
    string Response;
    cout << endl << "This dice rolled a " << pdice << "!" << endl;
    while (Response != "Reduce" && Response != "Attack" && Response != "atk" && pdice != 0)
    {
        cout << "Would you like to Reduce or Attack?" << endl;
        cin >> Response;
        if (Response != "Reduce" && Response != "Attack" && Response != "atk")
        {
            cout << "That's an invalid input, retry!" << endl;
        }
    }
    if (Response == "Reduce")
    {
        battleHP = redu(pdice, battleHP);
    }
    else if (Response == "Attack" || Response == "atk")
    {
        battleHP = attack(pdice, battleHP);
    }
    return battleHP;
}
game_state Dice5(game_state battleHP)
{
    int pdice = buff_roll(6, battleHP.buff, battleHP.redu);
    string Response;
    cout << endl << "This dice rolled a " << pdice << "!" << endl;
    while (Response != "Reduce" && Response != "Heal" && pdice != 0)
    {
        cout << "Would you like to Reduce or Heal?" << endl;
        cin >> Response;
        if (Response != "Reduce" && Response != "Heal")
        {
            cout << "That's an invalid input, retry!" << endl;
        }
    }
    if (Response == "Reduce")
    {
        battleHP = redu(pdice, battleHP);
    }
    else if (Response == "Heal")
    {
        battleHP = heal(pdice, battleHP);
    }
    return battleHP;
}
game_state dice_battle_selection(game_state battleHP, int dice_number)
{
    if (dice_number == 1)
    {
        battleHP = Dice1(battleHP);
    }
    else if (dice_number == 2)
    {
        battleHP = Dice2(battleHP);
    }
    else if (dice_number == 3)
    {
        battleHP = Dice3(battleHP);
    }
    else if (dice_number == 4)
    {
        battleHP = Dice4(battleHP);
    }
    else if (dice_number == 5)
    {
        battleHP = Dice5(battleHP);
    }
    return battleHP;
}
game_state Pturn(game_state battleHP, character_dice user_dice)
{
    cout << endl << "Player turn!" << endl;
    battleHP = dice_battle_selection(battleHP, user_dice.dice1);
    battleHP = dice_battle_selection(battleHP, user_dice.dice2);
    battleHP = dice_battle_selection(battleHP, user_dice.dice3);
    if (battleHP.PHealth > 100)
    {
        battleHP.PHealth = 100;
    }
    return battleHP;
}
game_state battle(game_state battleHP, character_dice user_dice, int type)
{
    int turn = 1;
    while (battleHP.PHealth > 0 && battleHP.EHealth > 0)
    {
        cout << endl << "Turn " << turn << endl << endl
            << "Player Health: " << battleHP.PHealth << " "
            << "Enemy Health: " << battleHP.EHealth << endl;
        battleHP = Pturn(battleHP, user_dice);
        if (battleHP.EHealth > 0)
        {
            cout << endl << "Enemy turn!" << endl;
            battleHP = enemy_fight(battleHP, type);
        }
        turn = turn + 1;
    }
    if (battleHP.EHealth <= 0 && battleHP.PHealth > 0)
    {
        cout << endl << "Victory!!!" << endl;
    }
    else if (battleHP.PHealth <= 0)
    {
        cout << endl << "Defeat..." << endl;
    }
    return battleHP;
}

game_state stat_setup(game_state battleHP, int type)
{
    battleHP.ebuff = 0;
    battleHP.eredu = 0;
    battleHP.redu = 0;
    battleHP.buff = 0;
    battleHP.ecount = 0;
    if (type == 1)
    {
        battleHP.EHealth = 30;
    }
    else if (type == 2)
    {
        battleHP.EHealth = 100;
    }
    else if (type == 3)
    {
        battleHP.EHealth = 60;
    }
    else if (type == 4)
    {
        battleHP.EHealth = 50;
    }
    else if (type == 5)
    {
        battleHP.EHealth = 100;
    }
    else if (type == 6)
    {
        battleHP.EHealth = 200;
    }
    return battleHP;
}
void monster_intro(int type)
{
    if (type == 1)
    {
        cout << endl << "You start your journey to defeat all the enemies in this castle."
            << endl << "And like with all castles, it has a 'C-A-T'. A cat approaches you" << endl;
    }
    else if (type == 2)
    {
        cout << endl << "You continue forward, only to find yourself looking down" <<
            " the barrel of a cannon." << endl;
    }
    else if (type == 3)
    {
        cout << endl << "You walk into a room, a tree is seen." << endl
            << "It offers a high-five, only to say 'too slow' ..." << endl;
    }
    else if (type == 4)
    {
        cout << endl << "You gain deeper into the castle. You see an egg." << endl
            << "A dragon hatches out of it, it throws up on your white Air Force 1's" << endl;
    }
    else if (type == 5)
    {
        cout << endl << "You hear some very strong words coming from around the corner." << endl
            << "It's a mean Dwarf..." << endl;
    }
    else if (type == 6)
    {
        cout << endl << "HOLY &%*^, IT'S AN ACTUAL ENEMY!" << endl
            << "The Demon King stands there menacingly..." << endl
            << "He's kinda big...." << endl;
    }
}

void game(game_state battleHP, character_dice user_dice)
{
    int count = 1;
    while (battleHP.PHealth > 0 && count <= 6)
    {
        battleHP = stat_setup(battleHP, count);
        monster_intro(count);
        battleHP = battle(battleHP, user_dice, count);
        count = count + 1;
    }
    if (battleHP.PHealth > 0)
    {
        cout << "Congratulations! You defeated all the enemies!" << endl;
    }
}