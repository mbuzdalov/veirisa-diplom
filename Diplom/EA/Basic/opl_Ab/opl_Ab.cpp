#include "opl_Ab.h"

opl_Ab::opl_Ab(const w_model& new_model, size_t new_lambda, size_t new_n, low_bound l_bound) {
    model = new_model;
    model.set_target(new_n);
    lambda = new_lambda;
    n = new_n;
    def_p = DEFAULT_NUM_P / n;
    max_p = 1.0 / 2;
    min_p = calc_low_bound(l_bound);
    jump = NONE_JUMP;
}

solution opl_Ab::generate_solution(const string& init_s) {
    assert(init_s.size() == n);
    init_p();
    init_params();
    representative cur(init_s, model.init_func(init_s));
    size_t evaluations = 1;
    size_t generations = 0;
    while (cur.f < model.get_target_value()) {
        vector<size_t> best_dif;
        size_t best_f = 0;
        size_t better_children = 0;
        for (size_t i = 0; i < lambda; ++i) {
            vector<size_t> dif = move(generate_dif(cur.s, p));
            size_t f = model.func(cur, dif);
            if (f >= best_f) {
                best_f = f;
                best_dif = move(dif);
            }
            if (f >= cur.f) {
                ++better_children;
            }
        }
        update_params(cur.f, p);
        if (best_f >= cur.f) {
            cur.change(best_dif, best_f);
        }
        change_p(better_children > 0 ? MUL : DIV);
        evaluations += lambda;
        ++generations;
    }
    update_params(cur.f, p);
    return {evaluations, generations};
}