#ifndef GAME_CIR_H
#define GAME_CIR_H

#include <iostream>

const int FIELD_WIDTH = 7;
const int FIELD_HEIGHT = 6;
const int WIN_LENGTH = 4;
const int DIR_NUMBER = 4;
extern const int di[];
extern const int dj[];


enum Cell {
    EMPTY,
    RED,
    YELLOW
};

class Field {
public:
    Field(bool isRedFirst);
    void clear(bool isRedFirst);
    bool makeTurn(int column);
    bool isWon(bool red) const;
    bool isOver() const;
    Cell getCell(int i, int j) const;
    bool isRedTurnNow() const;
    void print() const;
    void printResult() const;

private:
    Cell cells[FIELD_WIDTH][FIELD_HEIGHT];
    bool isRedTurn;
    Cell winner;

    void checkWinner();
};

#endif