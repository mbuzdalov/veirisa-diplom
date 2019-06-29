#include "opl.h"

opl::opl(const w_model& new_model, size_t new_lambda, size_t new_n, low_bound l_bound) {
    model = new_model;
    model.set_target(new_n);
    lambda = new_lambda;
    n = new_n;
    p = DEFAULT_NUM_P / n;
}

solution opl::generate_solution(const string& init_s) {
    assert(init_s.size() == n);
    init_params();
    representative cur(init_s, model.init_func(init_s));
    size_t evaluations = 1;
    size_t generations = 0;
    while (cur.f < model.get_target_value()) {
        vector<size_t> best_dif;
        size_t best_f = 0;
        for (size_t i = 0; i < lambda; ++i) {
            vector<size_t> dif = move(generate_dif(cur.s, p));
            size_t f = model.func(cur, dif);
            if (f >= best_f) {
                best_f = f;
                best_dif = move(dif);
            }
        }
        update_params(cur.f, p);
        if (best_f >= cur.f) {
            cur.change(best_dif, best_f);
        }
        evaluations += lambda;
        ++generations;
    }
    update_params(cur.f, p);
    return {evaluations, generations};
}