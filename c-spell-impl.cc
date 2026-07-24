module spell;
import <vector>;
import <string>;
import <iostream>;
import state;
import plard;
import minion;
import ritual;

using namespace std;

//CTOR
Spell::Spell(string name, int cost): Card{name, cost} {
    if (name == "Banish") { this->desc = "Destroy target minion or ritual"; }
    else if (name == "Unsummon") { this->desc = "Return target minion to its owner's hand"; }
    else if (name == "Recharge") { this->desc = "Your ritual gains 3 charges"; }
    else if (name == "Disenchant") { this->desc = "Destroy the top enchantment"; }
    else if (name == "Raise Dead") { this->desc = "Resurrect the top minion in your graveyard and set its defence to 1"; }
    else if (name == "Blizzard") { this->desc = "Deal 2 damage to all minions"; }
}

//selects which spell to use
// void Spell::playspell(Player *played, Player *owner, Spell s, int *p) {
//     string name = s.getName();
//     if (name == "Banish") { banish(played, owner, p); }
//     else if (name == "Unsummon") { unsummon(played, owner, p); }
//     else if (name == "Recharge") { recharge(played); }
//     else if (name == "Disenchant") { disenchant(played, owner, p); }
//     else if (name == "Raise Dead") { raiseDead(played); }
//     else if (name == "Blizzard") { blizzard(played, owner); }
// }

void banish(Player *played, int indexC, Player *owner, int i) {
  cout << "banish called" << endl;
    // Card *it = owner->board[i];
    // owner->board.erase(it);
}
void unsummon(Player *played, int indexC, Player *owner, int i) {
  cout << "unsummon called" << endl;
    // owner->hand.emplace_back = owner->board[i]; //add to hand
    // Card *it = owner->board[i];
    // owner->board.erase(it); //remove from board

}
void recharge(Player *played, int indexC) {
  cout << "recharge called" << endl;
    // int len = played->board.size;
    // string t = "";
    // for (int i = 0; i < len; i++) {
    //     t = played->board[i].getType();
    //     if (t == "ritual") {
    //         played->board[i].addC(3);
    //     }
    // }
}
void disenchant(Player *played, int indexC, Player *owner, int i) {
  cout << "disenchant called" << endl;
    // int len = owner->board[i].enchantments.size(); //add to hand
    // if (len == 0) return;
    // else { 
    //     auto it = owner->board[i].enchantments.begin();
    //     owner->board[i].enchantments.erase(it);
    // }
}
void raiseDead(Player *played, int indexC) {
  cout << "raide dead called" << endl;
    // int len = owner->graveyard.size(); //check non empty graveyard
    // if (len == 0) return;
    // else { 
    //     owner->hand.emplace_back(owner->graveyard.begin()); //add to hand
    //     auto it = owner->graveyard.begin();
    //     owner->graveyard.erase(it); //remove from graveyard
    // }
}
void blizzard(Player *played, int indexC, Player *owner){
  cout << "blizzard called" << endl;
    // int len = played->board.size;
    // string t = "";
    // for (int i = 0; i < len; i++) {
    //     t = owner->board[i].getType();
    //     if (t == "minion") {
    //         owner->board[i].addD(-2);
    //     }
    // }
}

// |-------------------------------||-------------------------------||-------------------------------|
// | Banish                  |   2 || Unsummon                |   1 || Recharge                |   1 |
// |-------------------------------||-------------------------------||-------------------------------|
// |                         Spell ||                         Spell ||                         Spell |
// |-------------------------------||-------------------------------||-------------------------------|
// | Destroy target minion or      || Return target minion to its   || Your ritual gains 3 charges   |
// | ritual                        || owner's hand                  ||                               |
// |                               ||                               ||                               |
// |                               ||                               ||                               |
// |                               ||                               ||                               |
// |-------------------------------||-------------------------------||-------------------------------|
// |-------------------------------||-------------------------------||-------------------------------|
// | Disenchant              |   1 || Raise Dead              |   1 || Blizzard                |   3 |
// |-------------------------------||-------------------------------||-------------------------------|
// |                         Spell ||                         Spell ||                         Spell |
// |-------------------------------||-------------------------------||-------------------------------|
// | Destroy the top enchantment   || Resurrect the top minion in   || Deal 2 damage to all minions  |
// | on target minion              || your graveyard and set its.   ||                               |
// |                               || defence to 1                  ||                               |
// |                               ||                               ||                               |
// |                               ||                               ||                               |
// |-------------------------------||-------------------------------||-------------------------------|
