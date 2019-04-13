#include "abstract_oplQ.h"

void abstract_oplQ::init_Q() {
    Q.resize(states_count);
    for (size_t i = 0; i < states_count; ++i) {
        Q[i][MUL] = Q[i][DIV] = 0;
    }
}

double abstract_oplQ::get_reward(double child_f, double parent_f) {
    switch (rew) {
        case ABSOLUTELY:
            return child_f;
        case BINARY:
            return child_f > parent_f ? 1 : 0;
        case SUBTRACTION:
            return child_f - parent_f;
        case DIVISION:
            return child_f / parent_f - 1;
        default:
            return 0;
    }
}

void abstract_oplQ::learn(size_t suc, operation op, double r, size_t new_suc) {
    if (suc != UNDEF_STATE && op != UNDEF) {
        Q[suc][op] = Q[suc][op] + alpha * (r + gamma * max(Q[new_suc][DIV], Q[new_suc][MUL]) - Q[suc][op]);
    }
}

operation abstract_oplQ::change_p(size_t new_suc) {
    /*
    if (choice(1)) {
        if (Q[new_suc][MUL] > Q[new_suc][DIV] || (Q[new_suc][MUL] == Q[new_suc][DIV] && choice(0.5))) {
            p = min(p * 2, max_p);
            return MUL;
        } else {
            p = max(p / 2, min_p);
            return DIV;
        }
    } else {
        if (choice(0.5)) {
            p = min(p * 2, max_p);
            return MUL;
        } else {
            p = max(p / 2, min_p);
            return DIV;
        }
    }
    */
    if (Q[new_suc][MUL] > Q[new_suc][DIV] || (Q[new_suc][MUL] == Q[new_suc][DIV] && new_suc >= max((size_t)1, lambda / 20))) {
        p = min(p * 2, max_p);
        return MUL;
    } else {
        p = max(p / 2, min_p);
        return DIV;
    }
}