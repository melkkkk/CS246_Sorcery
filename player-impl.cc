// module player;

// import card;
// import <string>;
// import <vector>;
// import <fstream>;
// import <iostream>;
// import <chrono>;   
// import <random>;


// using namespace std;

// Player::Player(string name, int life, int magic): name{name}, life{life}, magic{magic} {}

// // name getter and setters
// string Player::getName() {return name;}
// void Player::setName(string name) {this->name = name;}

// // gets the strings from the fstream and adds it to the vector
// void Player::setDeck(ifstream& infile){
//     string card_name;
//     while (getline(infile, card_name)){
//         deck.push_back(card_name);
//     }
// }

// // shuffles deck vector
// void Player::shuffleDeck(default_random_engine &rng){
//     shuffle(deck.begin(), deck.end(), rng);
//     // for (const auto& card : deck) {
//     //     cout << card << endl;
//     // }
//     // cout << endl;
// }

// // draws top card from the deck, probably needs to raise error later on?
// void Player::drawCard() {
//     if (deck.empty()){
//         cout << "Deck is empty" << endl;
//     }

//     string s = deck.at(0);
//     deck.erase(deck.begin());
//     hand.emplace_back(s);

//     // cout << "CARD REMOVED " << s << endl;
//     // for (const auto& card : deck) {
//     //     cout << card << endl;
//     // }
//     // cout << endl;
//     // for (auto& card : hand) {
//     //     cout << card.getName() << endl;
//     // }
//     // cout << endl;
// }
