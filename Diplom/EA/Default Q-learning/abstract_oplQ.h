#ifndef DIPLOM_ABSTRACT_OPLQ_H
#define DIPLOM_ABSTRACT_OPLQ_H


#include <EA/Basic/abstract_opl.h>

struct abstract_oplQ : public abstract_opl {

    const size_t UNDEF_STATE = numeric_limits<size_t>::max();
    const double DEFAULT_ALPHA = 0.8;
    const double DEFAULT_GAMMA = 0.2;
    double alpha, gamma;
    reward rew;
    size_t states_count;
    vector<array<double, 2>> Q;

    void init_Q();
    double get_reward(double child_f, double parent_f);
    void learn(size_t suc, operation op, double r, size_t new_suc);
    operation change_p(size_t new_suc);
};


#endif //DIPLOM_ABSTRACT_OPLQ_H
