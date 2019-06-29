#ifndef DIPLOM_W_MODEL_H
#define DIPLOM_W_MODEL_H

#include "source.h"
#include "EA/representative.h"
#include "deceptiveness/deceptiveness.h"

struct w_model {

    w_model() = default;
    w_model(problem new_probl, bool new_neutral, bool new_epistasis, size_t new_ruggedness);

    void set_target(size_t n);

    size_t init_func(string s);
    size_t func(const representative& parent, const vector<size_t>& dif);
    inline size_t get_target_value() { return target_value; };

    friend bool operator==(const w_model& a, const w_model& b);

private:

    mt19937 generator = mt19937(2);

    problem probl;
    bool neutral;
    bool epistasis;
    size_t ruggedness;
    bool is_clear;
    string target_str;
    size_t target_value;

    string neutral_apply(const string& s);
    string epistasis_apply(const string& s);
    size_t objective_apply(const string& s);
    size_t ruggedness_apply(size_t f);

};

bool operator==(const w_model& a, const w_model& b);

#endif //DIPLOM_W_MODEL_H
