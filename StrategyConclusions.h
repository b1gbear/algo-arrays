//
// Created by Development on 03/05/2020.
//

#ifndef MYALGO_STRATEGYCONCLUSIONS_H
#define MYALGO_STRATEGYCONCLUSIONS_H


#include "Strategy.h"
#include <iostream>

class StrategyConclusions : public Strategy {
public:
    std::string getName() override {
        return "Wnioski";
    }

    StrategyFeedback doAction(FullDataHolder &dataHolder) override {
        std::cout << "Quicksort w momencie otrzymania posortowanego wzoru oraz gdy " << endl
                 << "element partycjonujący jest po lewej lub prawej stronie" << endl
                 << "przepełni stos programu. Więcej informacji w dokumentacji." << endl;

        return StrategyFeedback::success();
    }

};


#endif //MYALGO_STRATEGYCONCLUSIONS_H
