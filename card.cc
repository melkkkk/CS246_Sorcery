export module card;
import <vector>;
import <string>;
//import player;


export class Card;

export class Card {
    std::string name;
    int cost;
    //std::vector<Observer*> observers;
    //State state;
  protected:
    //void setState(State newS);
    std::string getName();
    int getCost();
  public:
    Card(std::string name, int cost = 0);

    // player that played card i from their deck
    // owner is the selected players card
    // void pointer is for card i, or ritual r
    //void playcard(Player played, int i, Player owner, void *p);

    //void attach(Observer *o);  
    //void notifyObservers();
    //virtual Info getInfo() const = 0;
    //State getState() const;
};

// export class Observer {
//   public:
//     // Pass the Subject that called the notify method.
//     virtual void notify(Subject &whoFrom) = 0; 
//     virtual ~Observer() = default;
// };

//