#include <iostream>
#include <clocale>
#include "game_cir.h"

int main() {
    setlocale(LC_ALL, "Russian");
    Field field(true);

    while (!field.isOver()) {
        field.print();
        std::cout << "Ходит "
            << (field.isRedTurnNow() ? "красный" : "желтый")
            << " игрок, введите ход (1-" << FIELD_WIDTH << "): ";

        int column;
        std::cin >> column;

        if (std::cin.fail()) {
            std::cin.clear();                    
            std::cin.ignore(1000, '\n');          
            std::cout << "Ошибка: нужно ввести целое число от 1 до " << FIELD_WIDTH << "!\n";
            continue;
        }

        if (!field.makeTurn(column)) {
            std::cout << "Неверный ход! Колонка либо заполнена, либо вне диапазона 1.."
                << FIELD_WIDTH << ". Попробуйте ещё раз.\n";
        }
    }
    field.printResult();
    return 0;
}