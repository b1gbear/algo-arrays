//
// Created by Development on 03/05/2020.
//

#ifndef MYALGO_STRATEGYFILELOAD_H
#define MYALGO_STRATEGYFILELOAD_H

#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include "tools.h"

#include "Strategy.h"
#include "FullDataHolder.h"

using namespace std;

class StrategyFileLoad : public Strategy {
public:
    std::string getName() override {
        return "Zaladuj plik";
    }

    StrategyFeedback doAction(FullDataHolder &dataHolder) override {
        string line;
        string fName;
        std::cout << "Podaj nazwe pliku badz nacisnij ENTER [domyslnie: dane.csv]:";
        std::getline(std::cin, line);
        if (line.length() > 0) {
            fName = line;
        } else {
            fName = "dane.csv";
        }

        return loadFileNameToFullDataHolder(fName, dataHolder);
    }

    static StrategyFeedback loadFileNameToFullDataHolder(const std::string &fName, FullDataHolder &dataHolder) {
        fstream file;

        map<string, string> properties;
        file.open(fName, std::ios::in);
        string line;

        if (file.good()) {
            cout << "Wczytywanie" << endl;

            util::trim(line);

            while (file.peek() != EOF && std::getline(file, line)) {
                if ( util::trim(line) == "[MYALGO]") {
                    break;
                }
            }
            if (file.peek() == EOF) {
                return StrategyFeedback::failed("EOF reached before [MYALGO header]");
            }


            while (true) {
                if (!getline(file, line)) break;
                line =  util::trim(line);
                if (std::string("[DATA]") == line) break;
                auto found = line.find_first_of('=');
                if (found == std::string::npos) {
                    return StrategyFeedback::failed("Properties line is not KEY=VALUE pair");
                } else {
                    string key =  util::algo_lower(line.substr(0, found));
                    string value =  util::algo_lower(line.substr(found + 1));
                    properties.insert(std::pair<string, string>(key, value));
                }
            }

            if (properties.find("read_records") == properties.end()) {
                return StrategyFeedback::failed("Field READ_RECORDS was not provided");
            }

            size_t recordsNum = std::stoul(properties.at("read_records"));


            int measureRepeats;
            bool measureTime;

            if (properties.find("measure_repeats") == properties.end()) {

                return StrategyFeedback::failed("Field measure_repeats  was not provided");
            } else {
                try {
//                    std::cout << properties.at("measure_repeats");
                    int NUM = std::stoi(properties.at("measure_repeats"));
                    measureRepeats = NUM;
                } catch (const std::invalid_argument &ia) {
                    return StrategyFeedback::failed("Field measure_repeats  was not  good");
                }
            }

            if (properties.find("measure_time") == properties.end()) {
                return StrategyFeedback::failed("Field measure_time  was not provided");
            } else {
                string measureTimeString = properties.at("measure_time");
                if (measureTimeString == "true") {
                    measureTime = true;
                } else if (measureTimeString == "false") {
                    measureTime = false;
                } else {
                    return StrategyFeedback::failed("Field measure_time unexpected value " + measureTimeString);
                }
            }

            if (properties.find("read_as") == properties.end()) {
                return StrategyFeedback::failed("Field READ_AS  was not provided");
            }

            string readAs = properties.at("read_as");

            if (readAs == std::string("float")) {
                dataHolder.loadedDataType = DataType::FLOAT;
                dataHolder.dataHolderFloat.measureRepeats = measureRepeats;
                dataHolder.dataHolderFloat.measureTime = measureTime;
                while (getline(file, line)) {
                    float num = std::stof( util::trim(line));
                    dataHolder.dataHolderFloat.data.push_back(num);

                }
            } else if (readAs == std::string("int")) {
                dataHolder.loadedDataType = DataType::INT;
                dataHolder.dataHolderInt.measureRepeats = measureRepeats;
                dataHolder.dataHolderInt.measureTime = measureTime;
                while (getline(file, line)) {
                    int integer = std::stoi( util::trim(line));
                    dataHolder.dataHolderInt.data.push_back(integer);
                }
            }
            dataHolder.measureTime = measureTime;

//            cout << "measure_time " << dataHolder.measureTime << endl;
//            cout << "measure_repeats " << dataHolder.measureRepeats << endl;


        } else {
            return StrategyFeedback::failed("Plik w folderze powinien nazywac sie " + fName);
        }
        return StrategyFeedback::success();
    }

};


#endif //MYALGO_STRATEGYFILELOAD_H
