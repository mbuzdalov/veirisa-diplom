#include "abstract_oplNQ.h"

/*
size_t abstract_oplNQ::normalize_states(size_t count) {
    normal_state.resize(count);
    size_t cur_state = 0;
    size_t start = 0;
    size_t length = 1;
    size_t cur_normal_state = 0;
    while (cur_state < count) {
        for (; cur_state < min(start + length, count); ++cur_state) {
            normal_state[cur_state] = cur_normal_state;
        }
        start = cur_state;
        length *= 2;
        ++cur_normal_state;
    }
    return cur_normal_state;
}
*/

/* BEST
size_t abstract_oplNQ::normalize_states(size_t count) {
    normal_state.resize(count);
    size_t cur_state = 0;
    size_t cur_normal_state = 0;
    size_t start = 0;
    size_t length = 1;
    while (cur_state < count) {
        size_t border = min(start + length, count);
        size_t split_length = (length + SPLIT - 1) / SPLIT;
        for (size_t i = 0; i < SPLIT && cur_state < min(start + split_length, border); ++i) {
            for (; cur_state < min(start + split_length, border); ++cur_state) {
                normal_state[cur_state] = cur_normal_state;
                // cout << cur_state << ": " << cur_normal_state << "\n";
            }
            ++cur_normal_state;
            start = cur_state;
        }
        length *= 2;
    }
    return cur_normal_state;
}
*/

/*
size_t abstract_oplNQ::normalize_states(size_t count) {
    normal_state.resize(count);
    size_t cur_state_inv = 0;
    size_t cur_normal_state = 0;
    size_t start = 0;
    size_t length = (count + 1) / 2;
    while (cur_state_inv < count) {
        size_t border = min(start + length, count);
        size_t split_length = (length + SPLIT - 1) / SPLIT;
        for (size_t i = 0; i < SPLIT && cur_state_inv < min(start + split_length, border); ++i) {
            for (; cur_state_inv < min(start + split_length, border); ++cur_state_inv) {
                normal_state[count - 1 - cur_state_inv] = cur_normal_state;
                cout << count - 1 - cur_state_inv << ": " << cur_normal_state << "\n";
            }
            ++cur_normal_state;
            start = cur_state_inv;
        }
        length = (length + 1) / 2;
    }
    return cur_normal_state;
}
*/

void abstract_oplNQ::learn_normal(size_t suc, operation op, double r, size_t new_suc) {
    learn(get_normal_state(suc), op, r, get_normal_state(new_suc));
}

operation abstract_oplNQ::change_p_normal(size_t new_suc) {
    return change_p(get_normal_state(new_suc));
}