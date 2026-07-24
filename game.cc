export module game;

import plard;

import minion;
import ritual;
import enchantment;
import spell;

import board;

import <string>;
import <vector>;
import <fstream>;
import <chrono>;   
import <random>;

using namespace std;

export class Game;

export class Game{
    Player &active;
    Player &inactive;
    Board &b;
    // vector<Card> board;
    // Board B;

  public:
    Game();
    void use(Player *active, int i, Player *inactive = nullptr, int i = -1);
    void playCard(Player *active, int indexC, Player *inactive = nullptr, int i = -1);
    ~Game();
};

// Use minion's special ability, optionally targeting target-card owned by target-player 
//minion only
void use(Player *active, int indexM, Player *other = nullptr, int i = -1) {
  if (i < 0) {
    int damage = active->board[indexM]->getAttack() * -1;
    other.addL(damage);
  } else {
    int damageTo = active->board[indexM]->getAttack() * -1;
    int damageFrom = other->board[i]->getAttack() * -1;
    other->board[i]->addD(damageTo);
    active->board[i]->addD(damageFrom);
  }
}

void playCard(Player &active, int indexC, Player &other = nullptr, int i = -1) {
    // card played 
    string name = active->hand[i].getname();
    //spell
    if (name == "Banish") { banish(active, other, i); }
    else if (name == "Unsummon") { unsummon(active, other, i); }
    else if (name == "Recharge") { recharge(active); }
    else if (name == "Disenchant") { disenchant(active, other, i); }
    else if (name == "Raise Dead") { raiseDead(active); }
    else if (name == "Blizzard") { blizzard(active, other); }
    // ritual
    else if (name == "Dark Ritual") { darkRitual(active); }
    else if (name == "Aura of Power") { auraOfPower(active); }
    else if (name == "Standstill") { standstill(active); }
    //enchantment
    else if (name == "Giant Strength") { giantStrength(active, other, i); }
    else if (name == "Enrage") { enrage(active, other, i); }
    else if (name == "Haste") { haste(active, other, i); }
    else if (name == "Magic Fatigue") { magicFatigue(active, other, i); }
    else if (name == "Silence") { silence(active, other, i); }
    // minion 
    //just realized these dont even need this because they can only attack and use
    // else if (name == "Air Elemental") { airElemental(active, i); }
    // else if (name == "Earth Elemental") { earthElemental(active, i); }
    // else if (name == "Bone Golem") { boneGolem(active, i); }
    // else if (name == "Fire  Elemental") { fireElemental(active, i); }
    // else if (name == "Potion Seller") { potionSeller(active, i); }
    // else if (name == "Novice Pyromancer") { novicePyromancer(active, i); }
    // else if (name == "Apprentice Summoner") { apprenticeSummoner(active, i); }
    // else if (name == "Master Summoner") { masterSummoner(active, i); }

    //

}