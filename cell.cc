export module cell;
import <cstddef>;
import state;
import subj_obs;
import info;

export class Cell : public Subject, public Observer {
    const size_t r, c;
    Colour colour = Colour::Nothing;

    // *** Add other private members if necessary
    bool needflip;
    Direction dir(Info from, Info to);

  public:
    Cell(size_t r, size_t c);

    // Place a piece of given colour here.
    void setPiece(Colour colour); 

    // Toggles my colour.
    void toggle(); 

    // My neighbours will call this when they've changed state.
    virtual void notify(Subject &whoFrom) override;

    Info getInfo() const override;
};
