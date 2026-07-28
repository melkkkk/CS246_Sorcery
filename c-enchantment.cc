export module enchantment;
import <vector>;
import <string>;
import <tuple>;
import plard;
import minion;
import carddata;

using namespace std;

export class Enchantment: public Card {
  std::string desc = "";
  std::string attack = "";
  std::string defense = "";

  public:
    Enchantment(string name, vector<tuple<string, int, string, string, string>> vec); 

    void giantStrength(Player *played, Player *owner, int p);
    void enrage(Player *played, Player *owner, int p);
    void haste(Player *played, Player *owner, int p);
    void magicFatigue(Player *played, Player *owner, int p);
    void silence(Player *played, Player *owner, int p);

    void giantStrength(Minion *temp);
    void enrage(Minion *temp);
    void haste(Minion *temp);
    void magicFatigue(Minion *temp);
    void silence(Minion *temp);

    std::string getAttack();
    std::string getDefense();
    std::string getDesc();

};
