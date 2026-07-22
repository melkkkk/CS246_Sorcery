export module minion;
import <vector>;
import <string>;
import card;
import player;

using namespace std;

export class Minion: public Card {
    int attack;
    int defense;
    string desc;
    int actions;
    // vector of enchantments

  protected:
    //void setState(State newS);
  public:
    Minion(string name, int cost, int attack = 0, int defense = 0, string desc = "", int actions = 0;);
    //owner is owner of card selected in input or opponent based on spell
    //void pointer for card i or ritual r
    void airElemental(Player *played, int *target);
    void earthElemental(Player *played, int *target);
    void boneGolem(Player *played, int *target);
    void fireElemental(Player *played, int *target);
    void potionSeller(Player *played, int *target);
    void novicePyromancer(Player *played, int *target);
    void apprenticeSummoner(Player *played, int *target);
    void masterSummoner(Player *played, int *target);

    //add Attack
    //add Defense
    void addA(int i = 1);
    void addD(int i = 1);
    //multiply Attack
    //multiply Defense
    void multA(int i = 1);
    void multD(int i = 1);

    //observer overrides
    void notify(Card &whoFrom) override;

};

    //add Attack
    //add Defense
    void Minion::addA(int i = 1) { attack += i; }
    void Minion::addD(int i = 1) { defense += i; }
    //multiply Attack
    //multiply Defense
    void Minion::multA(int i = 1) { attack *= i; }
    void Minion::multD(int i = 1) { defense *= i; }


//export enum class StateType { StartOfTurn, EndOfTurn, MinionPlayed, Other };
//export enum class CardType { Ritual, Spell, Enchantment, Minion };

void Minion::notify(State &whoFrom, Player *active) {
  if (whoFrom.sType == StateType::StartOfTurn) {
    //check enchantment haste (+1 each start of turn)
  }
  else if (whoFrom.sType == StateType::EndOfTurn) {
    // would add any cards of end of turn type here
  } else if (whoFrom.sType == StateType::MinionPlayed) {
    if (whoFrom.cType == CardType::Minion) {
      if (whoFrom.rType == RitualType::StandStill) { active->board.pop_back(); }
      else if (whoFrom.rType == RitualType::AuraOfPower) { this.addA(); this.addD(); }
      //any other minion play activated things
    }
  }
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
