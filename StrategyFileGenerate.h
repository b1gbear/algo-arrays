//
// Created by Development on 03/05/2020.
//

#ifndef MYALGO_STRATEGYFILEGENERATE_H
#define MYALGO_STRATEGYFILEGENERATE_H

#include <iostream>
#include <limits>
#include <fstream>
#include <random>
#include <iomanip>
#include <cassert>
#include "Strategy.h"

using namespace std;

class StrategyFileGenerate : public Strategy {
    std::string getName() override {
        return "Generuj dane";
    }

    static unsigned int getNumber(int i) {
        std::string numString;
        try {
            std::getline(std::cin, numString);
            if (numString.length() <= 0)
            {
                return i;
            }
            return std::stoi(numString);
        } catch (const std::invalid_argument &ia) {}
        return i;
    }

    static bool getBool(bool b) {
        std::string numString;
        std::getline(std::cin, numString);

        if(numString.empty())
            return b;

        return !(numString.length() > 0 && tolower(numString[0]) == 'n') ;
    }

    StrategyFeedback doAction(FullDataHolder &dataHolder) override {

        const int seed = 1705311660;
        size_t FLOAT_PRECISION = 12;
        std::string defaultName = "dane.csv";
        while (true) {
            std::cout << "Tworzenie pliku " << defaultName << std::endl;
            std::cout << "Wybierz typ danych (int/float) [int]";
            std::string type;
            std::getline(std::cin, type);


            std::cout << "Podaj ilosc danych [10 000]:";
            unsigned int NUM = getNumber(10000);

            std::cout << "Podaj liczbe powtorzen [50]:";
            unsigned int REPEAT = getNumber(50);


            std::cout << "Czy mierzyc czas (tak/nie) [tak]:";
            bool measureTime = getBool(true);

            if (type == "float") {

            	//                // Program
            	//                std::cout << "type\tlowest()\tmin()\t\tmax()\t\tsizeof\n";
            	//                std::cout << "int\t"
            	//                          << std::numeric_limits<int32_t>::lowest() << '\t'
            	//                          << std::numeric_limits<int32_t>::min() << '\t'
            	//                          << std::numeric_limits<int32_t>::max() << '\t'
            	//                          << sizeof(int32_t) << '\n';
            	//                std::cout << "float\t"
            	//                          << std::numeric_limits<float>::lowest() << '\t'
            	//                          << std::numeric_limits<float>::min() << '\t'
            	//                          << std::numeric_limits<float>::max() << '\t'
            	//                          << sizeof(float) << '\n';

            	                // Float must be 4 bytes
            	                assert(sizeof(float) == 4);


                std::default_random_engine generatorFloat(seed);
                std::mt19937 gen(generatorFloat()); //Standard mersenne_twister_engine seeded with rd()
                std::uniform_real_distribution<> dis(-1000000.,1000000);


                fstream fileFloat(defaultName, ios::out);

                if (fileFloat.good()) {
                    header(NUM, REPEAT, measureTime, fileFloat,"float");

                    for (size_t i = 0; i < NUM; i++) {
                        fileFloat << setprecision(FLOAT_PRECISION);
                        fileFloat << dis(gen) << endl;
                    }
                } else {
                    return StrategyFeedback::failed("failed opening file " + defaultName);
                }

            } else /* int */ {

                std::default_random_engine generatorInteger(seed);
                std::uniform_int_distribution<int32_t> distribution(-1000000,1000000) ;


                fstream fileInt(defaultName, ios::out);

                if (fileInt.good()) {
                    header(NUM, REPEAT, measureTime, fileInt,"int");

                    for (size_t i = 0; i < NUM; i++) {
                        fileInt << distribution(generatorInteger) << endl;
                    }

                } else {
                    return StrategyFeedback::failed("failed opening file " + defaultName);
                }
            }
            break;
        }
        return StrategyFeedback::success();
    }

    static void header(unsigned int NUM, unsigned int REPEAT, bool measureTime, fstream &fileStream, const std::string& dataType) {
        fileStream << "[MYALGO] # Sekcja konfiguracji" << endl;
        fileStream << "READ_RECORDS=" << NUM << "# Liczba danych do wczytania" << endl;
        fileStream << "READ_AS=" << dataType << "# Typ danych [int/float]" << endl;
        fileStream << "MEASURE_TIME=" << (measureTime ? "true" : "false") << "# Czy mierzy czas" << endl;
        fileStream << "MEASURE_REPEATS=" << REPEAT << "# Liczba powtorzen" << endl;
        fileStream << "[DATA] # Sekcja danych" << endl;
    }
};


#endif //MYALGO_STRATEGYFILEGENERATE_H
