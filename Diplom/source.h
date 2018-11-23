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
};

struct parameters {
    size_t f;
    double p;
};

struct aver_solution {
    size_t evaluations;
    size_t eval_deviation;
    size_t generations;
    size_t gen_deviation;
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
