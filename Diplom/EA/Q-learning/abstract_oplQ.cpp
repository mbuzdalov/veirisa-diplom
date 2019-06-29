#include "abstract_oplQ.h"

void abstract_oplQ::init_Q() {
    Q.resize(states_count);
    for (size_t i = 0; i < states_count; ++i) {
        Q[i][MUL] = Q[i][DIV] = 0;
    }
    visit.resize(states_count);
    for (size_t i = 0; i < states_count; ++i) {
        visit[i] = 0;
    }
}

double abstract_oplQ::get_reward(double child_f, double parent_f) {
    switch (rew) {
        case ABSOLUTELY:
            return child_f;
        case BINARY:
            return child_f == parent_f ? 0 : (child_f > parent_f ? 1 : -1);
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
    ++visit[ass_new_suc];
    operation res_op;
    if (Q[ass_new_suc][MUL] > Q[ass_new_suc][DIV] || (Q[ass_new_suc][MUL] == Q[ass_new_suc][DIV]
        && ((init == AB && new_suc > 0) || (init == RANDOM && choice(0.5))))) {
        p *= 2;
        res_op = MUL;
    } else {
        p *= 0.5;
        res_op = DIV;
    }
    p = max(min_p, min(p, max_p));
    return res_op;
}