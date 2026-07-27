module ritual;
import <vector>;
import <string>;
import <iostream>;
import <tuple>;
import state;
import plard;
import minion;
import carddata;

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
// Ritual::Ritual(string name, int cost, int owner): Card{name, cost}, owner{owner} {
//     cout << "ritual ctor" << endl;
//     if (name == "Dark Ritual") { 
//       desc = "At the start of your turn, gain 1 magic"; 
//       charges = 5;
//       activation = 1;
//     }
//     else if (name == "Aura of Power") { 
//       desc = "Whenever a minion enters play under your control it gains +1/+1"; 
//       charges = 4;
//       activation = 1;
//     }
//     else if (name == "Standstill") { 
//       desc = "Whenever a minion enters play, destroy it"; 
//       charges = 4;
//       activation = 2;
//     }
// }


Ritual::Ritual(string name, int owner, vector<tuple<string, int, int, string, int, int>> vec) : Card{name} {
  cout << "Ritual ctor" << endl;
  int i = 0;
  if (name == "Dark Ritual") { i = 0; }
  else if (name == "Aura of Power") { i = 1; }
  else if (name == "Standstill") { i = 2; }

  tuple<string, int, int, string, int, int> temp = (vec[i]);
  this->setName(get<0>(temp));
  this->setCost(get<1>(temp));
  this->owner = owner;
  this->desc = (get<3>(temp));
  this->charges = (get<4>(temp));
  this->activation = (get<5>(temp));
}

// export std::tuple<std::string, int, int, std::string, int, int> darkritualR{"Dark Ritual", 0, 0, "At the start of your turn, gain 1 magic", 5, 1};
// export std::tuple<std::string, int, int, std::string, int, int> auraofpowerR{"Aura of Power", 1, 0, "Whenever a minion enters play under your control it gains +1/+1", 4, 1};
// export std::tuple<std::string, int, int, std::string, int, int> standstillR{"Standstill", 3, 0, "Whenever a minion enters play, destroy it", 4, 2};

// export std::vector<std::tuple<std::string, int, int, std::string, int, int>> ritualData = {darkritualR, auraofpowerR, standstillR};

//selects which spell to use
// void Ritual::playRitual(Player *played, Player *owner, int *p) {
//     string name = s.getName();
//     if (name == "Dark Ritual") { darkRitual(played); }
//     else if (name == "Aura of Power") { auraOfPower(played); }
//     else if (name == "Standstill") { standstill(played); }
// }

void Ritual::darkRitual(Player &active) {
  cout << "darkRitual called" << endl;
  //change condition to activated at start of turn, gains value
  if (charges - activation >= 0){
    active.addMagic(1);
    charges -= activation;
  }
}
void Ritual::auraOfPower(Player &active, int index) {
  cout << "auraOfPower called" << endl;
  //change condition to activated for minion in play under activated players control, add to value
  if (owner == active.getId() && charges - activation >= 0){
    Minion *temp = dynamic_cast<Minion*>(active.getHand()[index].get());
    temp->addA(1);
    temp->addD(1);
    charges -= activation;
  }
}

void Ritual::standstill(Player &active, int index, bool bothStandstill) {
  cout << "standstill called" << endl;
  //change condition to activated for minion in play, destory it
  // Minion *temp = dynamic_cast<Minion*>(active.getBoard()[active.getSizeB() - 1].get());
  if (((bothStandstill && active.getId() == owner) || !bothStandstill) && charges - activation >= 0){
    active.removeFrom(active.getHand(), index);
    charges -= activation;
    cout << "charges = " << charges << endl;
  }
}

void Ritual::notify(EventType event, Player &active, int index, bool bothStandstill) {
  cout << "notified ritual " << owner << endl;
  if (event == EventType::StartOfTurn){
    if (this->getName() == "Dark Ritual" && active.getId() == owner){
      darkRitual(active);
    }
  } else if (event == EventType::MinionPlayed) {
    if (this->getName() == "Aura of Power" && active.getId() == owner){
      auraOfPower(active, index);
    } else if (this->getName() == "Standstill"){
      standstill(active, index, bothStandstill);
    }
  }
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
