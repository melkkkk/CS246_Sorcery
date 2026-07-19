export module spell;
import <vector>;
import <string>;
import card;
import player;

using namespace std;

export class Spell: public Card {
    string desc;

  protected:
    //void setState(State newS);
  public:
    Spell(string name, int cost);
    //owner is owner of card selected in input or opponent based on spell
    //void pointer for card i or ritual r
    void playspell(Player played, Player owner, Spell s, void *p);
    void banish(Player played, Player owner, void *p);
    void unsummon(Player played, Player owner, void *p);
    void recharge(Player played);
    void disenchant(Player played, Player owner, void *p);
    void raisedead(Player played);
    void blizzard(Player played, Player owner);
};

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
void Spell::playspell(Player *played, Player *owner, Spell s, void *p) {
    string name = s.getName();
    if (name == "Banish") { banish(played, owner, p); }
    else if (name == "Unsummon") { unsummon(played, owner, p); }
    else if (name == "Recharge") { recharge(played); }
    else if (name == "Disenchant") { this->desc = "Destroy the top enchantment"; }
    else if (name == "Raise Dead") { this->desc = "Resurrect the top minion in your graveyard and set its defence to 1"; }
    else if (name == "Blizzard") { this->desc = "Deal 2 damage to all minions"; }
}

void banish(Player *played, Player *owner, void *p) {
    int i = &p;
    Card *it = owner->board[i];
    owner->board.erase(it);
}
void unsummon(Player *played, Player *owner. void *p) {
    int i = &p;
    owner->hand.emplace_back = owner->board[i]; //add to hand
    Card *it = owner->board[i];
    owner->board.erase(it); //remove from board

}
void recharge(Player *played) {
    int len = played->board.size;
    string t = "";
    for (int i = 0; i < len; i++) {
        t = played->board[i].getType();
        if (t == "ritual") {
            played->board[i].charges += 3;
        }
    }
}
void disenchant(Player *played, Player *owner, void *p) {
    int i = &p;
    int len = owner->board[i].enchantments.size(); //add to hand
    if (len == 0) return;
    else { 
        auto it = owner->board[i].enchantments.begin();
        owner->board[i].enchantments.erase(it);
    }
}
void raisedead(Player *played) {
    int len = owner->graveyard.size(); //add to hand
    if (len == 0) return;
    else { 
        auto it = owner->graveyard.begin();
        owner->graveyard.erase(it);
    }
}
void blizzard(Player *played, Player *owner){
    int len = played->board.size;
    string t = "";
    for (int i = 0; i < len; i++) {
        t = owner->board[i].getType();
        if (t == "minion") {
            owner->board[i].defense -= 2;
        }
    }
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
