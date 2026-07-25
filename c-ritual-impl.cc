module ritual;
import <vector>;
import <string>;
import <iostream>;
import state;
import plard;
import minion;

using namespace std;

//add charge
//multiply charge
void Ritual::addC(int i) { charges += i; }
void Ritual::multC(int i) { charges *= i; }

//removes the activation from charge
void Ritual::played() {
  //this.addC(-(activation));
}

int Ritual::getCharges(){return charges;}
int Ritual::getActivation(){ return activation;}
std::string Ritual::getDesc(){ return desc;}

//CTOR
Ritual::Ritual(string name, int cost): Card{name, cost} {
    cout << "ritual ctor" << endl;
    if (name == "Dark Ritual") { 
      desc = "At the start of your turn, gain 1 magic"; 
      charges = 5;
      activation = 1;
    }
    else if (name == "Aura of Power") { 
      desc = "Whenever a minion enters play under your control it gains +1/+1"; 
      charges = 4;
      activation = 1;
    }
    else if (name == "Standstill") { 
      desc = "Whenever a minion enters play, destroy it"; 
      charges = 4;
      activation = 2;
    }
}

//selects which spell to use
// void Ritual::playRitual(Player *played, Player *owner, int *p) {
//     string name = s.getName();
//     if (name == "Dark Ritual") { darkRitual(played); }
//     else if (name == "Aura of Power") { auraOfPower(played); }
//     else if (name == "Standstill") { standstill(played); }
// }

void Ritual::darkRitual(Player *played) {
  cout << "darkRitual called" << endl;
  //change condition to activated at start of turn, gains value
}
void Ritual::auraOfPower(Player *played) {
  cout << "auraOfPower called" << endl;
  //change condition to activated for minion in play under activated players control, add to value
}
void Ritual::standstill(Player *played) {
  cout << "standstill called" << endl;
  //change condition to activated for minion in play, destory it
}

 void Ritual::notify(State &whoFrom, Player *active) {
  cout << "notified ritual" << endl;
//   if (whoFrom.sType == StateType::StartOfTurn) {
//     //check if dark ritual then add 1 to magic
//     if (this.getname() == "Dark Ritual") {
//       if (charges > activation) { active->addM(1); this.played(); }
//     }
//   }
//   else if (whoFrom.sType == StateType::EndOfTurn) {
//     // would add any cards of end of turn type here
//   } else if (whoFrom.sType == StateType::MinionPlayed) {
//     if (whoFrom.cType == CardType::Minion) {
//       if (this->getname() == "Standstill") { active->board.pop_back(); }
//       else if (this->getname() == "Aura of Power") { this.addA(); this.addD(); }
//       //any other minion play activated things
//     }
//   }
}

// |-------------------------------||-------------------------------||-------------------------------|
// | Dark Ritual             |   0 || Aura of Power           |   1 || Standstill              |   3 |
// |-------------------------------||-------------------------------||-------------------------------|
// |                        Ritual ||                        Ritual ||                        Ritual |
// |-------------------------------||-------------------------------||-------------------------------|
// | 1   | At the start of your    || 1   | Whenever a minion enters|| 2   | Whenever a minion       |
// |------ turn, gain 1 magic      ||------ play under your control,||------ enters play, destroy it |
// |                               ||       it gains +1/+1          ||                               |
// |                         ------||                         ------||                         ------|
// |                         |   5 ||                         |   4 ||                         |   4 |
// |-------------------------------||-------------------------------||-------------------------------|
