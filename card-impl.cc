module card;

using namespace std;
Card::Card(string name, int cost): name{name}, cost{cost} {}
string::Card getname() {return this->name; }
string::Card getcost() {return this->cost; }
//void Subject::attach(Observer *o) { observers.emplace_back(o); }
//void Subject::notifyObservers() { for (auto &ob : observers) ob->notify(*this); }
//void Subject::setState(State newS) { state = newS; }
//State Subject::getState() const { return state; }
