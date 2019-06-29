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
#include <thread>
using namespace std;


// ------------------------------------- Common -------------------------------------

struct solution {
    size_t evaluations;
    size_t generations;
};

struct parameters {
    vector<size_t> f;
    vector<double> p;
};


enum operation {
    MUL, DIV, UNDEF
};


enum problem {
    ONE_MAX, LEADING_ONES
};


enum low_bound {
    ZERO, LINEAR, QUADRATIC
};


enum random_jump {
    NONE_JUMP, QUARTER4_JUMP, HALF2_JUMP
};


struct none_learning {};


// ------------------------------------- Learning -------------------------------------

enum reward {
    ABSOLUTELY, BINARY, SUBTRACTION, DIVISION
};

enum initial {
    RANDOM, AB
};


struct learning {
    double alpha;
    double gamma;
    reward rew;
    initial init;
    size_t state_size;
};


// ------------------------------------- Testing -------------------------------------

struct aver_solution {
    size_t evaluations;
    size_t eval_deviation;
    size_t generations;
    size_t gen_deviation;
    vector<size_t> gen;
    size_t gen_med;
};


// ------------------------------------- Constants -------------------------------------

// --- Common ---

const double DEFAULT_NUM_P = 1.0;

// --- WModel ---

const size_t MU = 3;
const size_t V = 4;
const vector<size_t> EV = {0, 13, 11, 6, 7, 10, 12, 1, 15, 2, 4, 9, 8, 5, 3, 14};

// --- Q-learning ---

const double DEFAULT_ALPHA = 0.8;
const double DEFAULT_GAMMA = 0.2;
const reward DEFAULT_REWARD = DIVISION;
const size_t DEFAUlT_STATE_SIZE = 5;
const size_t MIN_STATE_SIZE = numeric_limits<size_t>::max();

const size_t UNDEF_STATE = numeric_limits<size_t>::max();


#endif //DIPLOM_SOURCE_H
