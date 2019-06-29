#include "oplQ.h"

oplQ::oplQ(const w_model& new_model, size_t new_lambda, size_t new_n, low_bound l_bound, learning new_learn) {
    model = new_model;
    model.set_target(new_n);
    lambda = new_lambda;
    n = new_n;
    init = new_learn.init;
    rew = new_learn.rew;
    def_p = DEFAULT_NUM_P / n;
    max_p = 1.0 / 2;
    min_p = calc_low_bound(l_bound);
    alpha = new_learn.alpha;
    gamma = new_learn.gamma;
    states_count = associate_states(new_learn.state_size, lambda + 1);
}

size_t oplQ::associate_states(size_t state_size, size_t count) {
    associated_state.resize(count);
    size_t cur_state = 0;
    size_t cur_ass_state = 0;
    size_t start = 0;
    size_t length = min(state_size, (size_t)1);
    while (cur_state < count) {
        size_t border = min(start + length, count);
        for (; cur_state < border; ++cur_state) {
            associated_state[cur_state] = cur_ass_state;
        }
        ++cur_ass_state;
        start = cur_state;
    }
    return cur_ass_state;
}

solution oplQ::generate_solution(const string& init_s) {
    assert(init_s.size() == n);
    init_p();
    init_Q();
    init_params();
    representative cur(init_s, model.init_func(init_s));
    size_t evaluations = 1;
    size_t generations = 0;
    size_t suc = UNDEF_STATE;
    operation op = UNDEF;
    while (cur.f < model.get_target_value()) {
        vector<size_t> best_dif;
        size_t best_f = 0;
        size_t new_suc = 0;
        for (size_t i = 0; i < lambda; ++i) {
            vector<size_t> dif = move(generate_dif(cur.s, p));
            size_t f = model.func(cur, dif);
            if (f >= best_f) {
                best_f = f;
                best_dif = move(dif);
            }
            if (f > cur.f) {
                ++new_suc;
            }
        }
        update_params(cur.f, p);
        learn(suc, op, get_reward(best_f, cur.f), new_suc);
        operation new_op = change_p(new_suc);
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

double oplQ::get_visit() {
    size_t visited_states = 0;
    size_t alone_visited_states = 0;
    for (size_t i = 0; i < states_count; ++i) {
        if (visit[i] > 0) {
            if (visit[i] == 1) {
                ++alone_visited_states;
            }
            ++visited_states;
        }
    }
    //return (double)alone_visited_states / (double)visited_states;
    return (double)visited_states / (double)states_count;
}