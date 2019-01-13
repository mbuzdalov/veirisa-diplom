#ifndef DIPLOM_SOURCE_H
#define DIPLOM_SOURCE_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <ctime>
#include <random>
#include <cstdlib>
#include <cassert>
using namespace std;


enum operation {
    MUL, DIV, UNDEF
};

struct solution {
    size_t evaluations;
    size_t generations;
};

struct parameters {
    vector<size_t> f;
    vector<double> p;
};



enum problem {
    ONE_MAX, LEADING_ONES
};

enum low_bound {
    ZERO, LINEAR, QUADRATIC
};

enum none_reward {
    NONE
};

enum reward {
    ABSOLUTELY, BINARY, SUBTRACTION, DIVISION
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

#endif //DIPLOM_SOURCE_H
