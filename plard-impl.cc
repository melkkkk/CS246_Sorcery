module plard;
import <string>;
import <vector>;
import <fstream>;
import <iostream>;
import <chrono>;   
import <random>;
import state;

using namespace std;

//destructor
Card::~Card() {}

Card::Card(string name, int cost): name{name}, cost{cost} {}
std::string Card::getName() {return name; }
int Card::getCost() {return cost; }
//void Subject::attach(Observer *o) { observers.emplace_back(o); }
//void Subject::notifyObservers() { for (auto &ob : observers) ob->notify(*this); }
//void Subject::setState(State newS) { state = newS; }
//State Subject::getState() const { return state; }



Player::Player(string name, int life, int magic): name{name}, life{life}, magic{magic} {}

//adding
void Player::addL(int i) { life += i; }
void Player::addM(int i) { magic += i; }

// Card *Player::getCardH(int i) { return hand[i]; }
Card *Player::getCardB(int i) { return board[i]; }

// name getter and setters
string Player::getName() {return name;}
void Player::setName(string name) {this->name = name;}

// gets the strings from the fstream and adds it to the vector
void Player::setDeck(ifstream& infile){
    string card_name;
    while (getline(infile, card_name)){
        deck.push_back(card_name);
    }
}

// shuffles deck vector
void Player::shuffleDeck(default_random_engine &rng){
    shuffle(deck.begin(), deck.end(), rng);
    // for (const auto& card : deck) {
    //     cout << card << endl;
    // }
    // cout << endl;
}

// draws top card from the deck, probably needs to raise error later on?
void Player::drawCard() {
    if (deck.empty()){
        cout << "Deck is empty" << endl;
    }

    string s = deck.at(0);
    deck.erase(deck.begin());
    
    // hand.push_back(new Card(s));

    // cout << "CARD REMOVED " << s << endl;
    // for (const auto& card : deck) {
    //     cout << card << endl;
    // }
    // cout << endl;
    // for (auto& card : hand) {
    //     cout << card.getName() << endl;
    // }
    // cout << endl;
}
