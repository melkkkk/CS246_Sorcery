export module state;

/* State types are:
    NewPiece -- I am a new piece.  I was just placed on the board.  I'm letting
                you know that I exist, in case you need to change colour.

    Relay -- I have a neighbour (or a neighbour's neighbour, etc.) who is a 
             new piece, not of my colour, and is a straight line away from me.
             I'm letting you know that that neighbour exists, and in which
             direction it is, in case you need to change colour.

    Reply -- I have a neighbour (or a neighbour's neighbour, etc.) who is a
             new piece, of my colour, and is a straight line away from me.  OR
             I am an in between piece, and am changing my colour now.
*/

//other is for any card played that either doesnt trigger anything
export enum class EventType { StartOfTurn, EndOfTurn, MinionPlayed, MinionDied, Other };
// export enum class CardType { Ritual, Spell, Enchantment, Minion };
// export enum class RitualType { Nothing, Standstill, AuraOfPower };
//export enum class Direction { NW, N, NE, W, E, SW, S, SE };

export struct State {
    EventType eType;  // See above
    // CardType cType;   // What colour was the new piece? (NOT what is my colour)
    // //Direction direction;  // In which direction from me is the new piece?
    // RitualType rType;
};
