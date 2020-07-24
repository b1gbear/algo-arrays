//
// Created by Development on 03/05/2020.
//

#ifndef MYALGO_DATAHOLDER_H
#define MYALGO_DATAHOLDER_H
#include <vector>

template<typename T>
class DataHolder {
public:
    // Labels
    std::vector<T> data;
    std::vector<T> dataSorted;
    T min, max, sum;
    bool measureTime = false;
    unsigned long measureRepeats = 0;
    std::vector<std::chrono::nanoseconds> timeMeasurements;
};



#endif //MYALGO_DATAHOLDER_H
