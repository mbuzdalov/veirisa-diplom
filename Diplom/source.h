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
    size_t split_limit;
};


// ------------------------------------- Testing -------------------------------------

struct aver_solution {
    size_t evaluations;
    size_t eval_deviation;
    size_t generations;
    size_t gen_deviation;
};

enum test_size {
    SMALL, BIG
};


// ------------------------------------- Constants -------------------------------------


// --- Values ---

// const double DEFAULT_NUM_P = 1.0;

const double DEFAULT_BORDER_COEF = 1.0 / 20;

// const double DEFAULT_EPS = 0.0;
const double DEFAULT_ALPHA = 0.8;
const double DEFAULT_GAMMA = 0.2;
const reward DEFAULT_REWARD = DIVISION;
const size_t DEFAUlT_SPLIT_LIMIT = 801;
const size_t MAX_SPLIT_LIMIT = numeric_limits<size_t>::max();

const size_t UNDEF_STATE = numeric_limits<size_t>::max();


// --- Structures ---

const none_learning NONE_LEARN = {};

const learning DEFAULT_LEARN = {DEFAULT_ALPHA, DEFAULT_GAMMA, DEFAULT_REWARD, RANDOM, MAX_SPLIT_LIMIT};
const learning DEFAULT_LEARN_AB = {DEFAULT_ALPHA, DEFAULT_GAMMA, DEFAULT_REWARD, AB, MAX_SPLIT_LIMIT};
const learning DEFAULT_NORM_LEARN = {DEFAULT_ALPHA, DEFAULT_GAMMA, DEFAULT_REWARD, RANDOM, DEFAUlT_SPLIT_LIMIT};
const learning DEFAULT_NORM_LEARN_AB = {DEFAULT_ALPHA, DEFAULT_GAMMA, DEFAULT_REWARD, AB, DEFAUlT_SPLIT_LIMIT};


#endif //DIPLOM_SOURCE_H
