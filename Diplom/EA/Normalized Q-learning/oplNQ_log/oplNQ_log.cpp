#include "oplNQ_log.h"


oplNQ_log::oplNQ_log(problem new_probl, size_t new_lambda, size_t new_n, low_bound l_bound, reward new_rew) {
    probl = new_probl;
    lambda = new_lambda;
    n = new_n;
    rew = new_rew;
    def_p = NUMERATOR_P / n;
    max_p = 1.0 / 2;
    min_p = calc_low_bound(l_bound);
    alpha = DEFAULT_ALPHA;
    gamma = DEFAULT_GAMMA;
    states_count = normalize_states(lambda + 1);
}

size_t oplNQ_log::normalize_states(size_t count) {
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
            }
            ++cur_normal_state;
            start = cur_state;
        }
        length *= 2;
    }
    return cur_normal_state;
}

solution oplNQ_log::generate_solution(const string& init_s) {
    assert(init_s.size() == n);
    init_p();
    init_Q();
    init_params();
    representative cur(init_s, init_func(init_s));
    size_t evaluations = 1;
    size_t generations = 0;
    size_t suc = UNDEF_STATE;
    operation op = UNDEF;
    while (cur.f < n) {
        vector<size_t> best_dif;
        size_t best_f = 0;
        size_t new_suc = 0;
        for (size_t i = 0; i < lambda; ++i) {
            vector<size_t> dif = move(generate_dif(cur.s, p));
            size_t f = func(cur, dif);
            if (f >= best_f) {
                best_f = f;
                best_dif = move(dif);
            }
            if (f > cur.f) {
                ++new_suc;
            }
        }
        update_params(cur.f, p);
        learn_normal(suc, op, get_reward(best_f, cur.f), new_suc);
        operation new_op = change_p_normal(new_suc);
        if (best_f >= cur.f) {
            cur.change(best_dif, best_f);
        }
        evaluations += lambda;
        ++generations;
        suc = new_suc;
        op = new_op;
    }
    update_params(cur.f, p);
    return {evaluations, generations};
}