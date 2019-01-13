#include "oplQ_separating.h"

oplQ_separating::oplQ_separating(problem new_probl, size_t new_lambda, size_t new_n, low_bound l_bound, reward new_rew) {
    probl = new_probl;
    lambda = new_lambda;
    n = new_n;
    rew = new_rew;
    def_p = NUMERATOR_P / n;
    max_p = 1.0 / 4;
    min_p = 2.0 * calc_low_bound(l_bound);
    alpha = DEFAULT_ALPHA;
    gamma = DEFAULT_GAMMA;
    Q.resize((lambda + 1) / 2 + 1);
}

solution oplQ_separating::generate_solution(const string& init_s) {
    assert(init_s.size() == n);
    init_p();
    init_Q();
    init_params();
    representative cur(init_s, init_func(init_s));
    size_t evaluations = 1;
    size_t generations = 0;
    size_t suc = UNDEF_STATE;
    while (cur.f < n) {
        vector<size_t> best_dif;
        size_t best_f = 0;
        size_t best_f_mul = 0;
        size_t best_f_div = 0;
        operation best_op = UNDEF;
        size_t new_suc_mul = 0;
        size_t new_suc_div = 0;
        for (size_t i = 0; i < lambda; ++i) {
            bool is_mul = i < (lambda >> 1);
            vector<size_t> dif = move(generate_dif(cur.s, is_mul ? p * 2 : p / 2));
            size_t f = func(cur, dif);
            if (is_mul && f >= best_f_mul) {
                best_f_mul = f;
            }
            if (!is_mul && f >= best_f_div) {
                best_f_div = f;
            }
            if (f >= best_f) {
                best_f = f;
                best_dif = move(dif);
                best_op = is_mul ? MUL : DIV;
            }
            if (f > cur.f) {
                if (is_mul) {
                    ++new_suc_mul;
                } else {
                    ++new_suc_div;
                }
            }
        }
        update_params(cur.f, best_op == MUL ? p * 2 : p / 2);
        learn(suc, MUL, get_reward(best_f_mul, cur.f), new_suc_mul);
        learn(suc, DIV, get_reward(best_f_div, cur.f), new_suc_div);
        size_t best_suc = best_op == MUL ? new_suc_mul : new_suc_div;
        operation choosed_op = change_p(best_suc);
        if (best_f >= cur.f) {
            cur.change(best_dif, best_f);
        }
        evaluations += lambda;
        ++generations;
        suc = choosed_op == MUL ? new_suc_mul : new_suc_div;
    }
    update_params(cur.f, p);
    return {evaluations, generations};
}