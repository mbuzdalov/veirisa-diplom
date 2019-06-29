#include "w_model.h"

w_model::w_model(problem new_probl, bool new_neutral, bool new_epistasis, size_t new_ruggedness)
    : target_str(), target_value() {
    probl = new_probl;
    neutral = new_neutral;
    epistasis = new_epistasis;
    ruggedness = new_ruggedness;
    is_clear = !new_neutral && !new_epistasis && !new_ruggedness;
};


void w_model::set_target(size_t n) {
    size_t target_str_length = neutral ? n / MU : n;
    target_value = deceptiveness::size_after_ruggedness(ruggedness, target_str_length);
    if (is_clear) {
        target_str = string(target_str_length, '1');
    } else {
        char a[n];
        for (size_t i = 0; i < n; ++i) {
            if (generator() < (generator.max() >> 1)) {
                a[i] = '0';
            } else {
                a[i] = '1';
            }
        }
        target_str = string(a, target_str_length);
    }
}


size_t w_model::init_func(string s) {
    return ruggedness_apply(objective_apply(epistasis_apply(neutral_apply(s))));
}

size_t w_model::func(const representative& parent, const vector<size_t>& dif) {
    assert(!dif.empty());
    if (is_clear) {
        if (probl == ONE_MAX) {
            size_t result = parent.f;
            for (size_t j = 0; j < dif.size(); ++j) {
                if (parent.s[dif[j]] == '1') {
                    --result;
                } else {
                    ++result;
                }
            }
            return result;
        }
        if (probl == LEADING_ONES) {
            if (dif[0] < parent.f) {
                return dif[0];
            }
            size_t result = parent.f;
            for (size_t j = 0; j < dif.size(); ++j) {
                while (result < dif[j]) {
                    if (parent.s[result] == '0') {
                        return result;
                    }
                    ++result;
                }
                if (parent.s[dif[j]] == '0') {
                    ++result;
                } else {
                    return result;
                }
            }
            while (result < target_str.size()) {
                if (parent.s[result] == '0') {
                    return result;
                }
                ++result;
            }
            return result;
        }
        return 0;
    }
    string s = parent.s;
    for (size_t i = 0; i < dif.size(); ++i) {
        if (s[dif[i]] == '1') {
            s[dif[i]] = '0';
        } else {
            s[dif[i]] = '1';
        }
    }
    return init_func(s);
}

string w_model::neutral_apply(const string& s) {
    if (!neutral) {
        return s;
    }
    assert(target_str.size() == s.size() / MU);
    char a[target_str.size()];
    for (size_t i = 0; i < target_str.size(); ++i) {
        size_t ones = 0, zeros = 0;
        for (size_t j = i * MU; j < i * MU + MU; ++j) {
            if (s[j] == '1') {
                ++ones;
            } else {
                ++zeros;
            }
        }
        a[i] = zeros > ones ? '0' : '1';
    }
    return string(a, target_str.size());
}

string w_model::epistasis_apply(const string& s) {
    if (!epistasis) {
        return s;
    }
    assert(s.size() == target_str.size() && target_str.size() % V == 0);
    char a[target_str.size()];
    for (size_t i = 0; i < target_str.size() / V; ++i) {
        size_t from = 0;
        for (size_t j = i * V; j < i * V + V; ++j) {
            from <<= 1;
            from += s[j] == '1' ? 1 : 0;
        }
        size_t to = EV[from];
        size_t ind = i * V + V;
        for (size_t j = i * V; j < i * V + V; ++j) {
            --ind;
            a[ind] = to % 2 ? '1' : '0';
            to >>= 1;
        }
    }
    return string(a, target_str.size());
}

size_t w_model::objective_apply(const string& s) {
    assert(s.size() == target_str.size());
    if (probl == ONE_MAX) {
        size_t result = 0;
        for (size_t i = 0; i < s.size(); ++i) {
            if (s[i] == target_str[i]) {
                ++result;
            }
        }
        return result;
    }
    if (probl == LEADING_ONES) {
        size_t result = 0;
        for (size_t i = 0; i < s.size(); ++i) {
            if (s[i] == target_str[i]) {
                ++result;
            } else {
                return result;
            }
        }
        return result;
    }
    return 0;
}

size_t w_model::ruggedness_apply(size_t f) {
    return deceptiveness::apply_ruggedness(ruggedness, target_str.size(), f);
}


bool operator==(const w_model& a, const w_model& b) {
    return a.probl == b.probl && a.neutral == b.neutral && a.epistasis == b.epistasis && a.ruggedness == b.ruggedness;
}