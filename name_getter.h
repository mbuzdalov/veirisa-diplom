#ifndef DIPLOM_NAME_GETTER_H
#define DIPLOM_NAME_GETTER_H


#include "source.h"
#include <EA/Basic/opl/opl.h>
#include <EA/Basic/opl_Ab/opl_Ab.h>
#include <EA/Basic/opl_separating/opl_separating.h>
#include <EA/Q-learning/oplQ/oplQ.h>
#include <EA/Q-learning/oplQ_separating/oplQ_separating.h>

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


#endif //DIPLOM_NAME_GETTER_H
