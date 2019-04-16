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
    size_t ass_suc = get_associated_state(suc);
    size_t ass_new_suc = get_associated_state(new_suc);
    if (suc != UNDEF_STATE && op != UNDEF) {
        Q[ass_suc][op] = Q[ass_suc][op] + alpha * (r + gamma * max(Q[ass_new_suc][DIV], Q[ass_new_suc][MUL]) - Q[ass_suc][op]);
    }
}

operation abstract_oplQ::change_p(size_t new_suc) {
    size_t ass_new_suc = get_associated_state(new_suc);
    if (Q[ass_new_suc][MUL] > Q[ass_new_suc][DIV] || (Q[ass_new_suc][MUL] == Q[ass_new_suc][DIV]
        && ((init == AB && new_suc >= border) || (init == RANDOM && choice(0.5))))) {
        p = min(p * 2, max_p);
        return MUL;
    } else {
        p = max(p / 2, min_p);
        return DIV;
    }
}