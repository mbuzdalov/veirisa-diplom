#ifndef DIPLOM_ABSTRACT_OPLQ_H
#define DIPLOM_ABSTRACT_OPLQ_H


#include <EA/Basic/abstract_opl.h>

struct abstract_oplQ : public abstract_opl {

    double alpha, gamma;
    initial init;
    size_t border;
    reward rew;
    size_t states_count;
    vector<size_t> associated_state;
    vector<array<double, 2>> Q;

    inline size_t get_associated_state(size_t st) {
        return st == UNDEF_STATE ? st : associated_state[st];
    }

    void init_Q();
    double get_reward(double child_f, double parent_f);
    void learn(size_t suc, operation op, double r, size_t new_suc);
    operation change_p(size_t new_suc);
};


#endif //DIPLOM_ABSTRACT_OPLQ_H
