//
// Created by us on 20.06.2020.
//

#ifndef MYALGO_IOMANAGER_H
#define MYALGO_IOMANAGER_H

#include <iostream>
#include <vector>
#include <memory>
#include <stdio.h>


#ifdef __linux__

#include <termios.h>
#include <unistd.h>

#else

#include <conio.h>

#endif

#include <string>
#include <algorithm>

using namespace std;

class IoManager {
protected:
    // Variables for neat table design
    char LG;
    char PG;
    char LD;
    char PD;
    char LK;
    char PK;
    char horizontal;
    char vertical;
public:

    IoManager() {
        // Initialize table characters for windows or for linux
#ifdef __linux__
        LG = '+';
        PG = '+';
        LD = '+';
        PD = '+';
        LK = '+';
        PK = '+';
        horizontal = '-';
        vertical = '|';
#else
        LG = '\xC9';
        PG = '\xBB';
        LD = '\xC8';
        PD = '\xBC';
        LK = '\xCC';
        PK = '\xB9';
        horizontal = '\xCD';
        vertical = '\xBA';
#endif
    }

    /**
     * Split number using space every 3 digits
     * @param count
     * @return
     */
    static std::string castLong(long long int count) {
        std::string str;

        unsigned int i = 1;
        do {
            str += count % 10 + '0';

            count /= 10;

            if ((i % 3) == 0)
                str += " ";
            i++;
        } while (count > 0);

        reverse(str.begin(), str.end());

        return str;;
    }
    /**
     * Clear screen
     */
    static void pressAnyKey() {
#ifdef __linux__
        std::cout << "Press [Enter] to continue . . .";
        std::cin.get();
#else
        _getch();
#endif
    }

    /**
     * Clear screen
     */
    static void clearScreen() {
#ifdef __linux__
        system("clear");
#else
        system("cls");
#endif
    }

    // Enums for font color change
    enum class Color {
        RED, WHITE
    };

#pragma clang diagnostic push
#pragma ide diagnostic ignored "hicpp-signed-bitwise"

    /**
     * Set foreground font
     * @param color new color of foreground
     */
    static void setFont(Color color) {
#ifdef __linux__
        if (color == Color::WHITE)
            cout << "\033[0m";
        else
            cout << "\033[1;31m";
#else
        static HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (color == Color::WHITE)
            SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN |
                                          FOREGROUND_BLUE); // NOLINT(hicpp-signed-bitwise)
        else
            SetConsoleTextAttribute(hOut, FOREGROUND_RED);
#endif
    }

#pragma clang diagnostic pop

    static int multiPlatformGetch() {
#ifdef __linux__
        char buf = 0;
        struct termios old = {0};
        fflush(stdout);
        if (tcgetattr(0, &old) < 0)
            perror("tcsetattr()");
        old.c_lflag &= ~ICANON;   // local modes = Non Canonical mode
        old.c_lflag &= ~ECHO;     // local modes = Disable echo.
        old.c_cc[VMIN] = 1;         // control chars (MIN value) = 1
        old.c_cc[VTIME] = 0;         // control chars (TIME value) = 0 (No time)
        if (tcsetattr(0, TCSANOW, &old) < 0)
            perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
            perror("read()");
        old.c_lflag |= ICANON;    // local modes = Canonical mode
        old.c_lflag |= ECHO;      // local modes = Enable echo.
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
            perror("tcsetattr ~ICANON");
        return buf;
#else
        return _getch();
#endif
    }

    /**
     * Print string centered
     * @param str string to center
     * @param width total width
     * @param fillCharacter character to fill (width - string size space)
     * @return centered string with gaps filled with fillCharacter
     */
    static string printCentered(const string &str, int width, char fillCharacter) {
        return std::string((width - str.length()) / 2, fillCharacter) +
               str +
               std::string((width - str.length() + 1) / 2, fillCharacter);
    }

    /**
     * Print ch N times
     * @param ch character to print
     * @param times how many occurrences
     * @return string of N characters ch
     */
    static string printTimes(char ch, size_t N) {
        return string(N, ch);
    }
};


#endif //MYALGO_IOMANAGER_H
