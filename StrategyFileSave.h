//
// Created by Development on 03/05/2020.
//

#ifndef MYALGO_STRATEGYFILESAVE_H
#define MYALGO_STRATEGYFILESAVE_H

#include "Strategy.h"

class StrategyFileSave : public Strategy {
    std::string getName() override {
        return "Zapisz";
    }


    template<typename T>
    bool checkSorted(std::vector<T> &v) {
        if (v.empty())
            return false;
        for(size_t i = 0;i < v.size() -1; i++)
        {
            if (v[i] > v[i+1]){
            	std::cout << i << std::endl;
                std::cout << v[i] << std::endl;
                std::cout << v[i+1] << std::endl;
                std::cout << 111;
                return false;

            }
        }
        return true;
    }


    StrategyFeedback doAction(FullDataHolder &dataHolder) override {
        fstream file;
        string line;

        if (dataHolder.loadedDataType == DataType::INT)
        {

            if (!checkSorted(dataHolder.dataHolderInt.dataSorted)){
                return StrategyFeedback::failed( "Nie mozna zapisac danych przed posortowaniem");
            }
        }else if (dataHolder.loadedDataType == DataType::FLOAT)
        {
            if (!checkSorted(dataHolder.dataHolderFloat.dataSorted)){
                return StrategyFeedback::failed( "Nie mozna zapisac danych przed posortowaniem");
            }
        }else if (dataHolder.loadedDataType == DataType::NONE)
        {
            return StrategyFeedback::failed( "Brak danych do zapisania");
        }


        file.open("wyjscie.csv", std::ios::out);


        if (file.good()) {
            if (dataHolder.loadedDataType == DataType::FLOAT) {
                doExecute(dataHolder.dataHolderFloat, file);
            } else if (dataHolder.loadedDataType == DataType::INT) {
                doExecute(dataHolder.dataHolderInt, file);
            }
        } else {
            cout << "Plik w folderze powinien nazywac sie dane.csv" << endl;
        }

        return StrategyFeedback::success("Everything went ok");
    }

    template <typename T>
    void doExecute(const DataHolder<T> &dataHolder, fstream &file) const {
        file << string("[MYALGO]") << endl;
        file << "AVG=" << dataHolder.sum /( dataHolder.dataSorted.empty()  ? 1 : dataHolder.dataSorted.size() ) << endl;
        file << "SUM=" << dataHolder.sum << endl;
        file << "MIN=" << dataHolder.min << endl;
        file << "MAX=" << dataHolder.max << endl;
        file << string("[TIME_MEASURMENTS]") << endl;
        for (auto & timeMeasurement : dataHolder.timeMeasurements) {
            file << timeMeasurement.count() << endl;
        }
        file << "READ_RECORDS=int" << endl;
        file << string("[DATA]") << endl;
        for (int i : dataHolder.dataSorted) {
            file << i << endl;
        }
    }

};


#endif //MYALGO_STRATEGYFILESAVE_H
