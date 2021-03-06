#ifndef COMMANDS
#define COMMANDS


enum COMMAND {
    SET_NICKNAME,
    LETTER_VOTE,
    PASSWORD_GUESS,
    END_OF_ROUND,
    NOTHING,
    NEW_PASSWORD,
    SEND_MASK,
    GET_PASSWORD,
    NEXT_TOUR,
    SEND_ALPHABET,
    SEND_LETTER,
    SEND_PIECES,
    PASSWORD_GUESS_SUCCESS,
    PASSWORD_GUESS_FAILURE,
    SERVER_OVERLOAD,
    LIST_OF_PLAYERS,
    ROUND_LOST,
    WINNER,
};


#endif // COMMANDS

