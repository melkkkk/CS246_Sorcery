module cell;

import <cstddef>;
import state;
import subj_obs;
import info;

Direction Cell::dir(Info from, Info to) {
    if (from.row == to.row) {
        if (from.col - to.col == 1) {return Direction::W;}
        if (to.col - from.col == 1) {return Direction::E;}
    }
    if (from.col == to.col) {
        if (from.row - to.row == 1) {return Direction::N;}
        if (to.row - from.row == 1) {return Direction::S;}
    }
    if (from.col - to.col == 1) {
        if (from.row - to.row == 1) {return Direction::NW;}
        if (to.row - from.row == 1) {return Direction::SW;}
    }
    else {
        if (from.row - to.row == 1) {return Direction::NE;}
        else {return Direction::SE;}
    }
}

Cell::Cell(size_t r, size_t c) : r{r}, c{c} {
    State newS = State{ StateType::NewPiece, Colour::Nothing, Direction::N };
    this->setState(newS);
    needflip = false;
}
    // Place a piece of given colour here.
void Cell::setPiece(Colour colour) {
    this->colour = colour; 
    State s = getState();
    s.type = StateType::NewPiece;
    s.colour = colour;
    setState(s);
    notifyObservers();
}
    // Toggles my colour.
void Cell::toggle() {
    if (colour == Colour::Black) colour = Colour::White;
    else if (colour == Colour::White) colour = Colour::Black;
}

    // My neighbours will call this when they've changed state.
void Cell::notify(Subject &whoFrom) {
    if (this->colour == Colour::Nothing) return;
    State s = whoFrom.getState();
    Info i = whoFrom.getInfo();

    if (s.type == StateType::NewPiece) {
        if (this->colour == s.colour) return;
        else {
            s.type = StateType::Relay;
            s.direction = dir(i, this->getInfo());
            this->setState(s);
            notifyObservers();
        } //notify next in line
    } else if ((s.type == StateType::Relay) && (s.direction == dir(i, this->getInfo()))) {
        if (this->colour == s.colour) {
            s.type = StateType::Reply; 
            s.direction = dir(this->getInfo(), i);
            this->setState(s);
            notifyObservers();
        } //flip prev
        else {
            this->setState(s);
            notifyObservers();
        }
    } else if (s.type == StateType::Reply) {
        if (this->colour == s.colour) return;
        if (s.direction == dir(this->getInfo(), i)) {
            this->toggle();
            
            this->needflip = true;

            this->setState(s);
            notifyObservers(); //need to indicate to grid and textdisplay
        }
    }
}

Info Cell::getInfo() const {
    return Info{r, c, colour};
}
