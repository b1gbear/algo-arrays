//
// Created by Development on 03/05/2020.
//

#ifndef MYALGO_FULLDATAHOLDER_H
#define MYALGO_FULLDATAHOLDER_H
#include <vector>
#include <chrono>
#include "DataHolder.h"

enum class DataType { NONE, INT, FLOAT};


class FullDataHolder {
public:

    DataHolder<int> dataHolderInt;
    DataHolder<float> dataHolderFloat;
    std::vector<std::chrono::nanoseconds> timeMeasurements;
    DataType loadedDataType = DataType::NONE;
    bool measureTime = false;

};


#endif //MYALGO_DATAHOLDER_H
