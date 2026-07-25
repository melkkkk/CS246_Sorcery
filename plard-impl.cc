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
std::string Card::getName() {return name;}
int Card::getCost() {return cost; }
//void Subject::attach(Observer *o) { observers.emplace_back(o); }
//void Subject::notifyObservers() { for (auto &ob : observers) ob->notify(*this); }
//void Subject::setState(State newS) { state = newS; }
//State Subject::getState() const { return state; }


Player::Player(string name, int life, int magic): name{name}, life{life}, magic{magic} {}

//adding
void Player::addL(int i) { life += i; }
void Player::addM(int i) { magic += i; }

Card *Player::getCardH(int i) { return hand[i].get(); }
Card *Player::getCardB(int i) { return board[i].get(); }

unique_ptr<Card>& Player::getUniqueH(int i) { return hand[i]; }
unique_ptr<Card>& Player::getUniqueB(int i) { return board[i]; }

int Player::getSizeH() { return hand.size(); }
int Player::getSizeB() { return board.size(); }

vector<string>& Player::getDeck() { return deck; }

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

// adds a card to hand
void Player::addToHand(unique_ptr<Card> card){
    hand.push_back(move(card));

    int i = hand.size() - 1;
    std::cout << hand[i]->getName() << " has been added to hand!" << endl;
}

void Player::moveToBoard(unique_ptr<Card> card, int i){
    if (i != 0) {
        board.push_back(move(card));
        int j = board.size() - 1;
        std::cout << board[j]->getName() << " has been added to board!" << endl;
    } else {
        //set ritual pointer to given ritual
        board[i] = move(card);
        std::cout << board[i]->getName() << " has been added to board!" << endl;
    }
}
