export module card;
import <vector>;
import <string>;

/* A note on Info and State:

   We have separated the collection of fields into two parts: its Info
   and its State.

   Info is for the parts of the subject inherent to what it is: its position
   and its colour.

   State is for the parts of the subject that, when changed, trigger
   notifications.  This is the information that the Observer "gets" when it
   calls getState on the subject.  It comprises the type of state, a direction,
   and a colour.  For more details, see state.h.
*/

using namespace std;
export class Card;

// export class Observer {
//   public:
//     // Pass the Subject that called the notify method.
//     virtual void notify(Subject &whoFrom) = 0; 
//     virtual ~Observer() = default;
// };

export class Card {
    std::string name;
    int cost;
    //std::vector<Observer*> observers;
    //State state;
  protected:
    //void setState(State newS);
    Card(string name, int cost = 0);
  public:
    //void attach(Observer *o);  
    //void notifyObservers();
    //virtual Info getInfo() const = 0;
    //State getState() const;
};
