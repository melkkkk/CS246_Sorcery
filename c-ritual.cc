export module ritual;
import <vector>;
import <string>;
import <tuple>;
import state;
import plard;
import minion;
import carddata;


export class Ritual: public Card, public Observer {
    int owner;
    std::string desc;
    int charges;
    int activation;
  public:
    Ritual(std::string name, int owner, std::vector<std::tuple<std::string, int, int, std::string, int, int>>);
    
    void darkRitual(Player &active);
    void auraOfPower(Player &active, int index, int extra = -1);
    void standstill(Player &active, int index, int ss, int extra = -1);

    //add charge
    //multiply charge
    void addC(int i = 1);
    void multC(int i = 1);

    int getCharges();
    int getActivation();
    std::string getDesc();

    //observer
    void notify(EventType event, Player &active, int index, int extra) override;
};
