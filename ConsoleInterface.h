//
// Created by Development on 03/05/2020.
//

#ifndef UNTITLED_CONSOLEINTERFACE_H
#define UNTITLED_CONSOLEINTERFACE_H

#include <iostream>
#include <vector>
#include <memory>

#ifdef __linux__

#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#else

#include <windows.h>
#include <conio.h>
#include <fstream>
#include <map>

#endif

#include <bits/stdc++.h>

#include <algorithm>
#include <cctype>
#include <locale>
#include <cassert>

#include  "Strategy.h"
#include "tools.h"
#include "IoManager.h"

using namespace std;


/**
 * Console Interface class
 */
class ConsoleInterface : public IoManager {
protected:
    FullDataHolder &dataHolder;
    std::vector<Strategy *> strategies;
public:

    /**
     * Constructor
     * @param labels strategies
     */
    explicit ConsoleInterface(vector<Strategy *> &strategies, FullDataHolder &dataHolder) : strategies(strategies),
                                                                                        dataHolder(dataHolder) {
    }

    /**
     * Print interface
     * @param select current option
     */
    void printInterface(size_t select) {
        size_t real_len; // real length to center
        {
            size_t max_length = 0;
            for (Strategy *s : strategies) {
                if (s->getName().length() > max_length)
                    max_length = s->getName().length();
            }

            if (max_length < 4) {
                cout << "Nadluzsza z opcji musi miec przynajmniej 4 znaki" << endl;
                return;
            }
            real_len = max_length + 2;
        }

        clearScreen();

        cout << LG << printTimes(horizontal, real_len) << PG << endl;
        cout << vertical << printCentered("Menu", real_len, ' ') << vertical << endl;
        cout << LK << printTimes(horizontal, real_len) << PK << endl;

        // Print strategies
        for (size_t i = 0; i < strategies.size(); i++) {
            string s = strategies.at(i)->getName();
            cout << vertical << printTimes(' ', (real_len - s.length()) / 2);
            if (i == select) // change color for selected option
                setFont(Color::RED);
            cout << s;
            setFont(Color::WHITE); // set color back to white
            cout << printTimes(' ', (real_len - s.length() + 1) / 2) << vertical << endl;
        }


        authorship(real_len);

        cout << LD << printTimes(horizontal, real_len) << PD << std::endl;
    }

    virtual void authorship(size_t real_len) const {

    }

    void visitingCard(){

        std::vector<std::string> lines;
        lines.emplace_back("Proste algorytmy");
        lines.emplace_back("hardcoded.info");

        size_t real_len = 30;

        cout << LG << printTimes(horizontal, real_len) << PG << endl;

        for (const auto& s : lines) {
            cout << vertical << printTimes(' ', (real_len - s.length()) / 2);
            cout << s;
            setFont(Color::WHITE); // set color back to white
            cout << printTimes(' ', (real_len - s.length() + 1) / 2) << vertical << endl;
        }

        cout << LD << printTimes(horizontal, real_len) << PD << std::endl;
    }

    /**
     * Run interface
     */
    void run() {
        unsigned int selected = 0;
        while (true) {
            printInterface(selected);
            int pick;

            pick = multiPlatformGetch();


            /* Multi-platform, Windows and Linux options */
            if (pick == 'w' || pick == 72 || pick == 65) {
                if (selected > 0)
                    selected--;
                else
                    selected = strategies.size() - 1;
            }
                /* Multi-platform, Windows and Linux options */
            else if (pick == 's' || pick == 80 || pick == 66) {
                if (selected < strategies.size() - 1)
                    selected++;
                else
                    selected = 0;
            }
                /* Windows and Linux options */
            else if (pick == 13 || pick == '\n') {
                clearScreen();


                cout << "Wybrano opcje: " << selected + 1 << endl;
                assert(selected >= 0);
                assert(selected < strategies.size());
                Strategy *selectedStrategy = strategies.at(selected);

                StrategyFeedback fb = selectedStrategy->doAction(dataHolder);

                if (fb.getCode() == StrategyCode::EXIT) {
                    break;
                } else if (fb.getCode() == StrategyCode::SUCCESS) {
                    if (fb.isTimed()) {

                        cout << "Elapsed time in nanoseconds : " << castLong(fb.getTime().count()) << " ns" << endl;
                    }
                    if (fb.isWait()) {
                        cout << "Prosze nacisnac dowolny przycisk: ";
                        pressAnyKey();
                    }
                } else {
                    std::cerr << fb.getMessage();
                    pressAnyKey();
                }
            }
        }
    }


};

#endif //UNTITLED_CONSOLEINTERFACE_H
