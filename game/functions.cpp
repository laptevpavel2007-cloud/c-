#include "game_cir.h"

const int di[] = { 1, 0, 1, 1 };
const int dj[] = { 0, 1, -1, 1 };


Field::Field(bool isRedFirst) {
    clear(isRedFirst);
}

void Field::clear(bool isRedFirst) {
    isRedTurn = isRedFirst;
    winner = EMPTY;
    for (int i = 0; i < FIELD_WIDTH; ++i)
        for (int j = 0; j < FIELD_HEIGHT; ++j)
            cells[i][j] = EMPTY;
}

bool Field::makeTurn(int column) {
    if (winner != EMPTY || column < 1 || column > FIELD_WIDTH)
        return false;

    int i = column - 1;
    for (int j = 0; j < FIELD_HEIGHT; ++j) {
        if (cells[i][j] == EMPTY) {
            cells[i][j] = isRedTurn ? RED : YELLOW;
            checkWinner();
            isRedTurn = !isRedTurn;
            return true;
        }
    }
    return false;
}

void Field::checkWinner() {
    for (int i = 0; i < FIELD_WIDTH; ++i) {
        for (int j = 0; j < FIELD_HEIGHT; ++j) {
            Cell start = cells[i][j];
            if (start == EMPTY) continue;

            for (int dir = 0; dir < DIR_NUMBER; ++dir) {
                int length = 1;
                int ni = i + di[dir];
                int nj = j + dj[dir];

                while (length < WIN_LENGTH) {
                    if (ni < 0 || ni >= FIELD_WIDTH || nj < 0 || nj >= FIELD_HEIGHT)
                        break;
                    if (cells[ni][nj] != start)
                        break;
                    ++length;
                    ni += di[dir];
                    nj += dj[dir];
                }

                if (length == WIN_LENGTH) {
                    winner = start;
                    return;
                }
            }
        }
    }
    winner = EMPTY;
}

bool Field::isOver() const {
    if (winner != EMPTY) return true;
    for (int i = 0; i < FIELD_WIDTH; ++i)
        for (int j = 0; j < FIELD_HEIGHT; ++j)
            if (cells[i][j] == EMPTY)
                return false;
    return true;
}

bool Field::isWon(bool red) const {
    return (red && winner == RED) || (!red && winner == YELLOW);
}

Cell Field::getCell(int i, int j) const {
    return cells[i][j];
}

bool Field::isRedTurnNow() const {
    return isRedTurn;
}

void Field::print() const {
    std::cout << "   ";
    for (int col = 1; col <= FIELD_WIDTH; ++col)
        std::cout << col << "   ";
    std::cout << "\n";

    for (int j = FIELD_HEIGHT - 1; j >= 0; --j) {
        std::cout << " | ";
        for (int i = 0; i < FIELD_WIDTH; ++i) {
            switch (cells[i][j]) {
            case EMPTY:  std::cout << ". "; break;
            case RED:    std::cout << "R "; break;
            case YELLOW: std::cout << "Y "; break;
            }
            std::cout << "| ";
        }
        std::cout << "\n";
    }

    std::cout << "  ";
    for (int i = 0; i < FIELD_WIDTH; ++i)
        std::cout << "----";
    std::cout << "\n";
}

void Field::printResult() const {
    if (winner == RED)
        std::cout << "Победил красный игрок!\n";
    else if (winner == YELLOW)
        std::cout << "Победил желтый игрок!\n";
    else
        std::cout << "Ничья!\n";
}