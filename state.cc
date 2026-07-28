export module state;

//other is for any card played that either doesnt trigger anything
export enum class EventType { StartOfTurn, EndOfTurn, MinionPlayed, MinionDied, MinionSummoned, Other };

export struct State {
    EventType eType;  // See above
};
