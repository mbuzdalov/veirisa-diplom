#include "abstract_opl.h"

double abstract_opl::calc_low_bound(low_bound l_bound) {
    switch (l_bound) {
        case LINEAR:
            return 1.0 / n;
        case QUADRATIC:
            return 1.0 / (n * n);
        default:
            return 0;
    }
}

void abstract_opl::init_params() {
    param_f.clear();
    param_p_sum = vector<double>(n + 1, 0);
    param_p_size = vector<size_t>(n + 1, 0);
}

void abstract_opl::update_params(size_t cur_f, double cur_p) {
    param_f.push_back(cur_f);
    param_p_sum[cur_f] += cur_p;
    ++param_p_size[cur_f];
}

parameters abstract_opl::convert_params() {
    vector<double> param_p;
    for (size_t i = 0; i < n; ++i) {
        param_p.push_back(param_p_sum[i] / param_p_size[i]);
    }
    return {param_f, param_p};
}

vector<size_t> abstract_opl::generate_dif(const string& s, double prob) {
    vector<size_t> dif;
    size_t ind = next_inv_ind(0, prob);
    while (ind < n) {
        dif.push_back(ind);
        ind = next_inv_ind(ind + 1, prob);
    }
    return dif;
}

void abstract_opl::change_p(operation op) {
    if (jump == HALF2_JUMP && !choice(0.5)) {
        p = choice(0.5) ? p * 2 : p * 0.5;
    } else {
        p = op == MUL ? p * 2 : p * 0.5;
    }
    p = max(min_p, min(p, max_p));
}