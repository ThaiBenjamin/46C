#include "KnightTourGame.hpp"

#include <iostream>
#include <limits>

namespace {
void clearInputStream() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int readMenuChoice() {
    int choice = 0;
    while (true) {
        if (std::cin >> choice && choice >= 1 && choice <= 3) {
            clearInputStream();
            return choice;
        }
        std::cout << "Enter a number between 1 and 3: ";
        clearInputStream();
    }
}
} // namespace

void showMainMenu() {
    std::cout << "\n==========================================\n";
    std::cout << "            KNIGHT'S TOUR                \n";
    std::cout << "==========================================\n";
    std::cout << "1. Play Interactive Knight's Tour (Human)\n";
    std::cout << "2. Compare BST vs LLRB Performance\n";
    std::cout << "3. Exit\n";
    std::cout << "Choice: ";
}

int main() {
    KnightTourGame game;
    bool running = true;

    while (running) {
        showMainMenu();
        const int choice = readMenuChoice();
        switch (choice) {
            case 1:
                game.playHumanMode();
                break;
            case 2:
                game.compareBSTPerformanceAcrossSizes();
                break;
            case 3:
                running = false;
                break;
        }
    }

    std::cout << "Goodbye!\n";
    return 0;
}