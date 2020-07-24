//
// Created by Development on 03/05/2020.
//

#ifndef MYALGO_STRATEGYEXIT_H
#define MYALGO_STRATEGYEXIT_H
#include <string>
#include "Strategy.h"

class StrategyExit : public Strategy {
    std::string getName() override {
        return "Wyjscie";
    }

    StrategyFeedback doAction(FullDataHolder &dataHolder) override {
        return StrategyFeedback::exit("Everything went ok");
    }

};
#endif //MYALGO_STRATEGYEXIT_H
