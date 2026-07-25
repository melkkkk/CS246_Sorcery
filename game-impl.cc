module game;

import state;
import plard;

import minion;

// CAN COMMMENT OUT IF NOT READY
import ritual;
import enchantment;
import spell;

import <string>;
import <vector>;
import <fstream>;
import <iostream>;
import <chrono>;   
import <random>;

using namespace std;

Game::~Game() {}

Game::Game(Player *active, Player *inactive): active{active}, inactive{inactive} {
    p1 = std::make_unique<Player>();
    p2 = std::make_unique<Player>();
}

//if int i is negative then attacks player instead
//deoesnt remove if one of them dies,,,

//default args aready declared for last 2
void Game::attackM(Player *active, int indexM, Player *other, int i) {
    cout << "called attack" << endl;
    //Minion *temp = dynamic_cast<Minion*>(active->getCardB(indexM));
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

// Use minion's special ability, optionally targeting target-card owned by target-player 
//minion only
void Game::use(Player *active, int indexM, Player *other, int i) {
    cout << "called use" << endl;
    // Minion *temp = dynamic_cast<Minion*>(active->getCardB(indexM));
    // string name = temp->getName();
    // // else if (name == "Air Elemental") { airElemental(active, i); }
    // // else if (name == "Earth Elemental") { earthElemental(active, i); }
    // if (name == "Bone Golem") { temp->boneGolem(); }
    // else if (name == "Fire  Elemental") { temp->fireElemental(); }
    // else if (name == "Potion Seller") { temp->potionSeller(); }
    // else if (name == "Novice Pyromancer") { temp->novicePyromancer(other, i); }
    // else if (name == "Apprentice Summoner") { temp->apprenticeSummoner(active); }
    // else if (name == "Master Summoner") { temp->masterSummoner(active); }
}

void Game::playCard(int indexC, Player *other, int i) {
    cout << "card played" << endl;
    // card played 
    Card *c = active->getCardH(indexC);
    string name = c->getname();
    if (std::find(spellCards.begin(), spellCards.end(), name) != spellCards.end()) {
        Spell *temp = dynamic_cast<Spell*>(c);
        if (name == "Banish") { c->banish(active, other, i); }
        else if (name == "Unsummon") { c->unsummon(active, other, i); }
        else if (name == "Recharge") { c->recharge(active); }
        else if (name == "Disenchant") { c->disenchant(active, other, i); }
        else if (name == "Raise Dead") { c->raiseDead(active); }
        else if (name == "Blizzard") { c->blizzard(active, other); }
    } else if (std::find(spellCards.begin(), spellCards.end(), s) != spellCards.end()) {
        Spell *temp = dynamic_cast<Spell*>(c);
        
    } else if (std::find(ritualCards.begin(), ritualCards.end(), s) != ritualCards.end()) {
        active->addToHand(make_unique<Ritual>(s, 0));
    } else if (std::find(enchantmentCards.begin(), enchantmentCards.end(), s) != enchantmentCards.end()) {
        active->addToHand(make_unique<Enchantment>(s, 0));
    }
    //spell
    
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
    // just realized these dont even need this because they can only attack and use
    // we can just move from hand to board ig,,,
    
    //Minion *temp = dynamic_cast<Minion*>(c);

    else if (name == "Air Elemental") { airElemental(active, i); }
    else if (name == "Earth Elemental") { earthElemental(active, i); }
    else if (name == "Bone Golem") { boneGolem(active, i); }
    else if (name == "Fire  Elemental") { fireElemental(active, i); }
    else if (name == "Potion Seller") { potionSeller(active, i); }
    else if (name == "Novice Pyromancer") { novicePyromancer(active, i); }
    else if (name == "Apprentice Summoner") { apprenticeSummoner(active, i); }
    else if (name == "Master Summoner") { masterSummoner(active, i); }

    

}

// draws top card from the deck, probably needs to raise error later on?
void Game::drawCard(Player *active) {
    // checking if the deck is empty
    if (active->getDeck().empty()){
        cout << "Deck is empty" << endl;
        return;
    }

    // get the top card of the deck
    string s = active->getDeck().at(0);
    active->getDeck().erase(active->getDeck().begin());
    // active->addToHand(make_unique<Minion>(s, 0));
    
    // cout << s << endl;

    // Based on what the name is, the correct card is created
    if (std::find(minionCards.begin(), minionCards.end(), s) != minionCards.end()) {
        active->addToHand(make_unique<Minion>(s, 0));
    } else if (std::find(spellCards.begin(), spellCards.end(), s) != spellCards.end()) {
        active->addToHand(make_unique<Spell>(s, 0));
    } else if (std::find(ritualCards.begin(), ritualCards.end(), s) != ritualCards.end()) {
        active->addToHand(make_unique<Ritual>(s, 0));
    } else if (std::find(enchantmentCards.begin(), enchantmentCards.end(), s) != enchantmentCards.end()) {
        active->addToHand(make_unique<Enchantment>(s, 0));
    } else {
        cout << "Card found in deck does not match up: " << s << endl;
    }
}
