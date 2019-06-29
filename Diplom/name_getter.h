#ifndef DIPLOM_NAME_GETTER_H
#define DIPLOM_NAME_GETTER_H


#include "source.h"
#include "structures.h"
#include <EA/Basic/opl/opl.h>
#include <EA/Basic/opl_Ab/opl_Ab.h>
#include <EA/Basic/opl_separating/opl_separating.h>
#include <EA/Q-learning/oplQ/oplQ.h>


string get_model_name(const w_model& model) {

    if (model == CLEAR_ONE_MAX) {
        return "OneMax";
    } else if (model == NEUTRAL_ONE_MAX) {
        return "OneMax_neutral";
    } else if (model == EPISTASIS_ONE_MAX) {
        return "OneMax_epistasis";
    } else if (model == PLATO_REGGEDNESS_ONE_MAX) {
        return "OneMax_plato-reggedness";
    } else if (model == REGGEDNESS_ONE_MAX) {
        return "OneMax_reggedness";
    }

    if (model == CLEAR_LEADING_ONES) {
        return "LeadingOnes";
    } else if (model == NEUTRAL_LEADING_ONES) {
        return "LeadingOnes_neutral";
    } else if (model == EPISTASIS_LEADING_ONES) {
        return "LeadingOnes_epistasis";
    } else if (model == PLATO_REGGEDNESS_LEADING_ONES) {
        return "LeadingOnes_plato-reggedness";
    } else if (model == REGGEDNESS_LEADING_ONES) {
        return "OneMax_reggedness";
    }

    return "WModel";
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
    if (learn.state_size > MIN_STATE_SIZE) {
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
