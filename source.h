#ifndef DIPLOM_SOURCE_H
#define DIPLOM_SOURCE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <ctime>
#include <random>
#include <cstdlib>
#include <cassert>
using namespace std;

enum problem {
    ONE_MAX, LEADING_ONES
};

struct solution {
    size_t evaluations;
    size_t generations;

    solution() :
            evaluations(),
            generations()
    {};
    solution(size_t eval, size_t gen) :
            evaluations(eval),
            generations(gen)
    {}
};

struct aver_solution {
    size_t evaluations;
    size_t eval_deviation;
    size_t generations;
    size_t gen_deviation;

    aver_solution() :
            evaluations(),
            eval_deviation(),
            generations(),
            gen_deviation()
    {};
    aver_solution(size_t eval, size_t eval_div, size_t gen, size_t gen_div) :
            evaluations(eval),
            eval_deviation(eval_div),
            generations(gen),
            gen_deviation(gen_div)
    {}
};

enum test_size {
    SMALL, BIG
};

enum operation {
    MUL, DIV, UNDEF
};

enum none_reward {
    NONE
};

enum reward {
    ABSOLUTELY, BINARY, SUBTRACTION, DIVISION
};

#endif //DIPLOM_SOURCE_H
