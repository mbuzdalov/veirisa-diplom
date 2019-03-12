#ifndef DIPLOM_NAME_GETTER_H
#define DIPLOM_NAME_GETTER_H


#include "source.h"
#include <EA/Basic/opl/opl.h>
#include <EA/Basic/opl_Ab/opl_Ab.h>
#include <EA/Basic/opl_separating/opl_separating.h>
#include <EA/Default Q-learning/oplQ/oplQ.h>
#include <EA/Default Q-learning/oplQ_separating/oplQ_separating.h>
#include <EA/Normalized Q-learning/oplNQ/oplNQ.h>

string get_problem_name(problem probl) {
    switch (probl) {
        case ONE_MAX:
            return "OneMax";
        case LEADING_ONES:
            return "LeadingOnes";
        default:
            return "";
    }
}


string get_low_bound_name(low_bound l_bound) {
    switch (l_bound) {
        case LINEAR:
            return "_(line)";
        case QUADRATIC:
            return "_(quad)";
        default:
            return "";
    }
}


string get_reward_name(none_reward rew) {
    return "";
}

string get_reward_name(reward rew) {
    switch (rew) {
        case ABSOLUTELY:
            return "_ABS";
        case BINARY:
            return "_BIN";
        case DIVISION:
            return "_DIV";
        case SUBTRACTION:
            return "_SUB";
        default:
            return "";
    }
}


template <typename EA>
struct ea {};

template <>
struct ea<opl> { static string get_name() { return "opl"; } };

template <>
struct ea<opl_separating> { static string get_name() { return "opl_separating"; } };

template <>
struct ea<opl_Ab> { static string get_name() { return "opl_Ab"; } };

template <>
struct ea<oplQ> { static string get_name() { return "oplQ"; } };

template <>
struct ea<oplQ_separating> { static string get_name() { return "oplQ_separating"; } };

template <>
struct ea<oplNQ> { static string get_name() { return "oplNQ"; } };

#endif //DIPLOM_NAME_GETTER_H
