export module spell;
import <vector>;
import <string>;
import <tuple>;
import <iostream>;
import state;
import plard;
import carddata;

using namespace std;

export class Spell: public Card {
    string desc;
  public:
    Spell(string name, vector<tuple<string, int, string>> vec); 

    void banish(Player *played, int indexC, Player *owner, int i);
    void unsummon(Player *played, int indexC, Player *owner, int i);
    void recharge(Player *played, int indexC);
    void disenchant(Player *played, int indexC, Player *owner, int i);
    void raiseDead(Player *played, int indexC);
    void blizzard(Player *played, Player *owner);

    std::string getDesc();
};
