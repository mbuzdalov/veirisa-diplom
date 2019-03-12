#ifndef ABSTRACT_OPLNQ_H
#define ABSTRACT_OPLNQ_H


#include <EA/Default Q-learning/abstract_oplQ.h>

struct abstract_oplNQ : public abstract_oplQ {

    const size_t SPLIT = 1600;
    vector<size_t> normal_state;

    size_t normalize_states(size_t count);
    void learn_normal(size_t suc, operation op, double r, size_t new_suc);
    operation change_p_normal(size_t new_suc);

    inline size_t get_normal_state(size_t st) {
        return st == UNDEF_STATE ? st : normal_state[st];
    }
};


#endif // ABSTRACT_OPLNQ_H
