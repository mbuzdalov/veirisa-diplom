#include "opl_separating.h"

opl_separating::opl_separating(const w_model& new_model, size_t new_lambda, size_t new_n, low_bound l_bound) {
    model = new_model;
    model.set_target(new_n);
    lambda = new_lambda;
    n = new_n;
    def_p = 2 * DEFAULT_NUM_P / n;
    max_p = 1.0 / 4;
    min_p = 2.0 * calc_low_bound(l_bound);
    jump = HALF2_JUMP;
}

solution opl_separating::generate_solution(const string& init_s) {
    assert(init_s.size() == n);
    init_p();
    init_params();
    representative cur(init_s, model.init_func(init_s));
    size_t evaluations = 1;
    size_t generations = 0;
    size_t half_lambda = lambda >> 1;
    while (cur.f < model.get_target_value()) {
        vector<size_t> best_dif;
        size_t best_f = 0;
        operation best_op = UNDEF;
        for (size_t i = 0; i < lambda; ++i) {
            bool is_mul = i < half_lambda;
            if (i == half_lambda && lambda % 2 != 0 && choice(0.5)) {
                is_mul = !is_mul;
            }
            vector<size_t> dif = move(generate_dif(cur.s, is_mul ? p * 2 : p / 2));
            size_t f = model.func(cur, dif);
            if (f >= best_f) {
                best_f = f;
                best_dif = move(dif);
                best_op = is_mul ? MUL : DIV;
            }
        }
        update_params(cur.f, best_op == MUL ? p * 2 : p / 2);
        if (best_f >= cur.f) {
            cur.change(best_dif, best_f);
        }
        change_p(best_op);
        evaluations += lambda;
        ++generations;
    }
    update_params(cur.f, p);
    return {evaluations, generations};
}