module minion;
import <vector>;
import <string>;
import <iostream>;
import plard;

using namespace std;

int Minion::getAttack() { return attack; }
int Minion::getDefense() { return defense; }
//add Attack
//add Defense
void Minion::addA(int i = 1) { attack += i; }
void Minion::addD(int i = 1) { defense += i; }
void Minion::addAction(int i = 1) { attack += i; }

//multiply Attack
//multiply Defense
void Minion::multA(int i = 1) { attack *= i; }
void Minion::multD(int i = 1) { defense *= i; }

Minion::Minion(string name, int cost, int attack = 0, int defense = 0, string desc = "", int actions = 0):
  Card{name, cost}, attack{attack}, defense{defense} {
    //set defense and actions if applicable

    cout << "minion ctor" << endl;
}

//void Minion::airElemental(Player *played, int *target) {}
//void Minion::earthElemental(Player *played, int *target) {}
void Minion::boneGolem(Player *played, int *target) {
  cout << "bone golem called" << endl;}
void Minion::fireElemental(Player *played, int *target) {
  cout << "fire elemental called" << endl;}
void Minion::potionSeller(Player *played, int *target) {
  cout << "potion seller called" << endl;}
void Minion::novicePyromancer(Player *played, int *target) {
  cout << "novice pyromancer called" << endl;}
void Minion::apprenticeSummoner(Player *played, int *target) {
  cout << "apprentice summoner called" << endl;}
void Minion::masterSummoner(Player *played, int *target) {{
  cout << "master summoner called" << endl;}

//if int i is negative then attacks player instead
//deoesnt remove if one of them dies,,,
void attack(Player *active, int indexM, Player *other = nullptr, int i = -1) {
  if (i < 0) {
  cout << "attacked player" << endl;
    //int damage = active->board[indexM]->getAttack() * -1;
    //other.addL(damage);
  } else {
  cout << "attacked minion: " << i << endl;
    //int damageTo = active->board[indexM]->getAttack() * -1;
    //int damageFrom = other->board[i]->getAttack() * -1;
    //other->board[i]->addD(damageTo);
    //active->board[i]->addD(damageFrom);
  }
}

//export enum class StateType { StartOfTurn, EndOfTurn, MinionPlayed, Other };
//export enum class CardType { Ritual, Spell, Enchantment, Minion };

void Minion::notify(State &whoFrom, Player *active) {
  // if (whoFrom.sType == StateType::StartOfTurn) {
  //   //check enchantment haste (+1 each start of turn)
  // }
  // else if (whoFrom.sType == StateType::EndOfTurn) {
  //   // would add any cards of end of turn type here
  // } else if (whoFrom.sType == StateType::MinionPlayed) {
  //   if (whoFrom.cType == CardType::Minion) {
      
  //   }
  // }
}



// |-------------------------------||-------------------------------||-------------------------------||-------------------------------|
// | Air Elemental           |   0 || Earth Elemental         |   3 || Bone Golem              |   2 || Fire Elemental          |   2 |
// |-------------------------------||-------------------------------||-------------------------------||-------------------------------|
// |                        Minion ||                        Minion ||                        Minion ||                        Minion |
// |-------------------------------||-------------------------------||-------------------------------||-------------------------------|
// |                               ||                               || Gain +1/+1 whenever a minion  || Whenever an opponent's minion |
// |                               ||                               || leaves play.                  || enters play, deal 1 damage to |
// |                               ||                               ||                               || it.                           |
// |------                   ------||------                   ------||------                   ------||------                   ------|
// | 1   |                   |   1 || 4   |                   |   4 || 1   |                   |   3 || 2   |                   |   2 |
// |-------------------------------||-------------------------------||-------------------------------||-------------------------------|
// |-------------------------------||-------------------------------||-------------------------------||-------------------------------|
// | Potion Seller           |   2 || Novice Pyromancer       |   1 || Apprentice Summoner     |   1 || Master Summoner         |   3 |
// |-------------------------------||-------------------------------||-------------------------------||-------------------------------|
// |                        Minion ||                        Minion ||                        Minion ||                        Minion |
// |-------------------------------||-------------------------------||-------------------------------||-------------------------------|
// | At the end of your turn, all  || 1   | Deal 1 damage to target || 1   | Summon a 1/1 air        || 2   | Summon up to three 1/1  |
// | your minions gain +0/+1.      ||------  minion                 ||------ elemental               ||------ air elementals          |
// |                               ||                               ||                               ||                               |
// |------                   ------||------                   ------||------                   ------||------                   ------|
// | 1   |                   |   3 || 0   |                   |   1 || 1   |                   |   1 || 2   |                   |   3 |
// |-------------------------------||-------------------------------||-------------------------------||-------------------------------|
