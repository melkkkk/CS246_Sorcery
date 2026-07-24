module game;

import state;
import plard;

import minion;

import <string>;
import <vector>;
import <fstream>;
import <iostream>;
import <chrono>;   
import <random>;

using namespace std;

// Use minion's special ability, optionally targeting target-card owned by target-player 
//minion only
void Game::use(Player *active, int indexM, Player *other, int i) {
    cout << "called use" << endl;
    Minion *temp = dynamic_cast<Minion*>(active->getCardB(indexM));
    string name = temp->getName();
    // else if (name == "Air Elemental") { airElemental(active, i); }
    // else if (name == "Earth Elemental") { earthElemental(active, i); }
    if (name == "Bone Golem") { temp->boneGolem(); }
    else if (name == "Fire  Elemental") { temp->fireElemental(); }
    else if (name == "Potion Seller") { temp->potionSeller(); }
    else if (name == "Novice Pyromancer") { temp->novicePyromancer(other, i); }
    else if (name == "Apprentice Summoner") { temp->apprenticeSummoner(active); }
    else if (name == "Master Summoner") { temp->masterSummoner(active); }
}

void Game::playCard(Player *active, int indexC, Player *other, int i) {
    cout << "card played" << endl;
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
    //just realized these dont even need this because they can only attack and use
    // we can just move from hand to board ig,,,

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