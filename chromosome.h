#pragma once
#include "ml_digger.h"
#include <vector>
class Chromosome{
    public:
        Chromosome();
        Chromosome make_cross(Chromosome parent1, Chromosome parent2);
        Chromosome mutate(Chromosome chromosome);
        
    private:
        std::vector<std::pair<Digger::Commands,int>> path;
        int score;
};

