#ifndef DIPLOM_NAME_GETTER_H
#define DIPLOM_NAME_GETTER_H


#include "source.h"
#include <EA/Basic/opl/opl.h>
#include <EA/Basic/opl_Ab/opl_Ab.h>
#include <EA/Basic/opl_separating/opl_separating.h>
#include <EA/Q-learning/oplQ/oplQ.h>

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
            return "Linear";
        case QUADRATIC:
            return "Quadratic";
        default:
            return "";
    }
}


string get_learning_name(none_learning none_learn) {
    return "";
}

string get_learning_name(learning learn) {
    if (learn.split_limit < MAX_SPLIT_LIMIT) {
        if (learn.init == AB) {
            return "_normal+Ab";
        } else {
            return "_normal";
        }
    } else {
        if (learn.init == AB) {
            return "_Ab";
        } else {
            return "";
        }
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


#endif //DIPLOM_NAME_GETTER_H
