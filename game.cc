export module game;

import state;
import plard;
import minion;

// CAN COMMMENT OUT IF NOT READY
import ritual;
import enchantment;
import spell;

//import board;

import <string>;
import <vector>;
import <fstream>;
import <iostream>;
import <chrono>;   
import <random>;
import <algorithm>;


export class Game;

export class Game{
    Player *active;
    Player *inactive;

    //will add these on later
    //Board &b;
    // vector<Card> board;
    // Board B;

    // MAY CHANGE LOCATION LATER
    inline static std::vector<std::string> spellCards = {"Banish", "Unsummon", "Recharge", "Disenchant", "Raise Dead", "Blizzard"};
    inline static std::vector<std::string> ritualCards = {"Dark Ritual", "Aura of Power", "Standstill"};
    inline static std::vector<std::string> minionCards = {"Air Elemental", "Earth Elemental", "Bone Golem", "Potion Seller", 
                                                            "Novice Pyromancer", "Apprentice Summoner", "Fire Elemental", "Master Summoner"};
    inline static std::vector<std::string> enchantmentCards = {"Giant Strength", "Enrage", "Haste", "Magic Fatigue", "Silence"};

  public:
    Game(Player *active, Player *inactive); //add board to this eventually
    void attackM(Player *active, int indexM, Player *other = nullptr, int i = -1);
    void use(Player *active, int indexM, Player *inactive = nullptr, int i = -1);
    void playCard(Player *active, int indexC, Player *inactive = nullptr, int i = -1);
    ~Game();

    // draws top card from the deck, probably needs to raise error later on?
    void drawCard(Player *active);
};

// Use minion's special ability, optionally targeting target-card owned by target-player 
//minion only
// void use(Player *active, int indexM, Player *other = nullptr, int i = -1) {
//     cout << "called use" << endl;
//     string name = active->board[indexM]->getName();
//     // else if (name == "Air Elemental") { airElemental(active, i); }
//     // else if (name == "Earth Elemental") { earthElemental(active, i); }
//     if (name == "Bone Golem") { boneGolem(active, i); }
//     else if (name == "Fire  Elemental") { fireElemental(active, i); }
//     else if (name == "Potion Seller") { potionSeller(active, i); }
//     else if (name == "Novice Pyromancer") { novicePyromancer(active, i); }
//     else if (name == "Apprentice Summoner") { apprenticeSummoner(active, i); }
//     else if (name == "Master Summoner") { masterSummoner(active, i); }
// }

// void playCard(Player &active, int indexC, Player &other = nullptr, int i = -1) {
//     cout << "card played" << endl;
    // card played 
    // string name = active->hand[i].getname();
    // //spell
    // if (name == "Banish") { banish(active, other, i); }
    // else if (name == "Unsummon") { unsummon(active, other, i); }
    // else if (name == "Recharge") { recharge(active); }
    // else if (name == "Disenchant") { disenchant(active, other, i); }
    // else if (name == "Raise Dead") { raiseDead(active); }
    // else if (name == "Blizzard") { blizzard(active, other); }
    // // ritual
    // else if (name == "Dark Ritual") { darkRitual(active); }
    // else if (name == "Aura of Power") { auraOfPower(active); }
    // else if (name == "Standstill") { standstill(active); }
    // //enchantment
    // else if (name == "Giant Strength") { giantStrength(active, other, i); }
    // else if (name == "Enrage") { enrage(active, other, i); }
    // else if (name == "Haste") { haste(active, other, i); }
    // else if (name == "Magic Fatigue") { magicFatigue(active, other, i); }
    // else if (name == "Silence") { silence(active, other, i); }
    // minion 
    // just realized these dont even need this because they can only attack and use
    // we can just move from hand to board ig,,,

    // else if (name == "Air Elemental") { airElemental(active, i); }
    // else if (name == "Earth Elemental") { earthElemental(active, i); }
    // else if (name == "Bone Golem") { boneGolem(active, i); }
    // else if (name == "Fire  Elemental") { fireElemental(active, i); }
    // else if (name == "Potion Seller") { potionSeller(active, i); }
    // else if (name == "Novice Pyromancer") { novicePyromancer(active, i); }
    // else if (name == "Apprentice Summoner") { apprenticeSummoner(active, i); }
    // else if (name == "Master Summoner") { masterSummoner(active, i); }

    

// }