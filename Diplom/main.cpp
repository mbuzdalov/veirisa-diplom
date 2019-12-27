#include <algorithm>

using std::sort;

#include "name_getter.h"
#include "structures.h"

// ------------------------------------- Common -------------------------------------

// --- String generator ---

mt19937 generator(4);

string random_string(mt19937 generator, size_t n) {
    char a[n];
    for (size_t i = 0; i < n; ++i) {
        if (generator() < (generator.max() >> 1)) {
            a[i] = '0';
        } else {
            a[i] = '1';
        }
    }
    return string(a, n);
}

// --- Solver creater ---

template <typename OPL>
OPL create_solver(const w_model& model, size_t lambda, size_t n, low_bound l_bound, none_learning none_learn) {
    return OPL(model, lambda, n, l_bound);
}

template <typename OPLQ>
OPLQ create_solver(const w_model& model, size_t lambda, size_t n, low_bound l_bound, learning learn) {
    return OPLQ(model, lambda, n, l_bound, learn);
}


// ------------------------------------- Tester -------------------------------------

const size_t LAMBDA_SIZE = 10;
const size_t test_lambda[LAMBDA_SIZE] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};

const size_t N_SIZE = 1;
size_t test_n[N_SIZE] = {1000};

aver_solution aver_solut[LAMBDA_SIZE][N_SIZE];

const size_t TEST_SIZE = 100;
solution test_solut[TEST_SIZE];


bool generated = false;
string test_str[TEST_SIZE];

string random_string(mt19937 generator, size_t n, size_t test) {
    if (!generated) {
        for (size_t i = 0; i < TEST_SIZE; ++i) {
            test_str[i] = random_string(generator, n);
        }
        generated = true;
    }
    return test_str[test];
}


void write_evaluations(const string& probl_name, const string& l_bound_name, const string& algorithm_name) {
    ofstream fout_eval("Results/" + probl_name + "/" + l_bound_name + "/Evaluations/" + algorithm_name + ".txt");
    fout_eval << "lambda - n - evaluations - deviation\n";
    for (size_t i = 0; i < LAMBDA_SIZE; ++i) {
        size_t lambda = test_lambda[i];
        for (size_t j = 0; j < N_SIZE; ++j) {
            size_t n = test_n[j];
            fout_eval << lambda << "\t"
                      << n << "\t"
                      << aver_solut[i][j].evaluations << "\t"
                      << aver_solut[i][j].eval_deviation << "\n";
        }
    }
}

void write_generations(const string& probl_name, const string& l_bound_name, const string& algorithm_name) {
    ofstream fout_gen("Results/" + probl_name + "/" + l_bound_name + "/Generations/" + algorithm_name + ".txt");
    fout_gen << "n - lambda - generations - deviation\n";
    for (size_t j = 0; j < N_SIZE; ++j) {
        size_t n = test_n[j];
        for (size_t i = 0; i < LAMBDA_SIZE; ++i) {
            size_t lambda = test_lambda[i];
            fout_gen << n << "\t"
                     << lambda << "\t"
                     << aver_solut[i][j].generations << "\t"
                     << aver_solut[i][j].gen_deviation << "\n";
        }
    }
}

void write_mediana(const string& probl_name, const string& l_bound_name, const string& algorithm_name) {
    ofstream fout_gen("Results/" + probl_name + "/" + l_bound_name + "/Mediana/" + algorithm_name + ".txt");
    fout_gen << "n - lambda - med generations - generations\n";
    for (size_t j = 0; j < N_SIZE; ++j) {
        size_t n = test_n[j];
        for (size_t i = 0; i < LAMBDA_SIZE; ++i) {
            size_t lambda = test_lambda[i];
            fout_gen << n << "\t"
                     << lambda << "\t"
                     << aver_solut[i][j].gen_med;
            for (size_t k = 0; k < aver_solut[i][j].gen.size(); ++k) {
                fout_gen << "\t" << aver_solut[i][j].gen[k];
            }
            fout_gen << "\n";
        }
    }
}

template <typename OPL>
void testing(size_t lam_ind, size_t n_ind, OPL solver) {
    size_t n = test_n[n_ind];

    size_t evaluations = 0, generations = 0;
    for (size_t test = 0; test < TEST_SIZE; ++test) {
        test_solut[test] = solver.generate_solution(random_string(generator, n, test));
        evaluations += test_solut[test].evaluations;
        generations += test_solut[test].generations;
    }
    evaluations = (evaluations + TEST_SIZE / 2) / TEST_SIZE;
    generations = (generations + TEST_SIZE / 2) / TEST_SIZE;

    size_t eval_deviation = 0, gen_deviation = 0;
    for (size_t i = 0; i < TEST_SIZE; ++i) {
        eval_deviation += (test_solut[i].evaluations - evaluations) * (test_solut[i].evaluations - evaluations);
        gen_deviation += (test_solut[i].generations - generations) * (test_solut[i].generations - generations);
    }
    eval_deviation = (size_t) sqrt((eval_deviation + TEST_SIZE / 2) / TEST_SIZE);
    gen_deviation = (size_t) sqrt((gen_deviation + TEST_SIZE / 2) / TEST_SIZE);

    vector<size_t> test_gen_sort, test_gen;
    for (size_t test = 0; test < TEST_SIZE; ++test) {
        test_gen.push_back(test_solut[test].generations);
    }
    test_gen_sort = test_gen;
    sort(test_gen_sort.begin(), test_gen_sort.end());

    aver_solut[lam_ind][n_ind] =
            {evaluations, eval_deviation, generations, gen_deviation, test_gen, test_gen_sort[TEST_SIZE / 2]};
}



template <typename OPL, typename LT>
void full_testing(const w_model& model, low_bound l_bound, LT learn) {
    string probl_name = get_model_name(model);
    string l_bound_name = get_low_bound_name(l_bound);
    string algorithm_name = ea<OPL>::get_name() + get_learning_name(learn);
    cout <<  "\n" << "testing (" <<  probl_name << ", " << l_bound_name << "): " << algorithm_name << "\n\n";

    for (size_t i = 0; i < LAMBDA_SIZE; ++i) {
        size_t lambda = test_lambda[i];
        for (size_t j = 0; j < N_SIZE; ++j) {
            size_t n = test_n[j];
            cout << "lambda: " << lambda << "  n: " << n << "\n";
            OPL solver = create_solver<OPL>(model, lambda, n, l_bound, learn);
            testing<OPL>(i, j, solver);
        }
    }

    write_evaluations(probl_name, l_bound_name, algorithm_name);
    write_generations(probl_name, l_bound_name, algorithm_name);
    write_mediana(probl_name, l_bound_name, algorithm_name);
}


// ------------------------------------- Fixed runtime -------------------------------------

const size_t fr_lambda = 32;
const size_t fr_n = 10000;

parameters params;
vector<size_t> count_tests;

void write_parameters(const string& probl_name, const string& l_bound_name, const string& algorithm_name) {
    ofstream fout_func("Results/" + probl_name + "/" + l_bound_name + "/Function/" + to_string(fr_lambda) +
                       "/" + algorithm_name + ".txt");
    fout_func << algorithm_name << " (function):\n";
    fout_func << "~  n = " << fr_n << "  ~  " << "lambda = " << fr_lambda << "  ~\n\n";
    for (size_t i = 0; i < params.f.size(); ++i) {
        fout_func << params.f[i] << "\t";
    }
}

template <typename OPL, typename LT>
void fixed_runtime(const w_model& model, low_bound l_bound, LT learn) {
    string algorithm_name = ea<OPL>::get_name() + get_learning_name(learn);
    cout <<  "\n" << "fixed runtime: " << algorithm_name << "\n\n";

    params = {{}, {}};
    count_tests = {};
    OPL solver = create_solver<OPL>(model, fr_lambda, fr_n, l_bound, learn);
    for (size_t t = 0; t < TEST_SIZE; ++t) {
        cout << "test: " << t << "\n";
        solver.generate_solution(random_string(generator, fr_n, t));
        parameters cur_params = solver.get_params();
        for (size_t i = 0; i < cur_params.f.size(); ++i) {
            if (params.f.size() <= i) {
                params.f.push_back(0);
                count_tests.push_back(0);
            }
            params.f[i] += cur_params.f[i];
            ++count_tests[i];
        }
    }
    for (size_t i = 0; i < params.f.size(); ++i) {
        for (size_t c = count_tests[i]; c < TEST_SIZE; ++c) {
            params.f[i] += fr_n;
        }
        params.f[i] = (params.f[i] + TEST_SIZE / 2) / TEST_SIZE;
        if (params.f[i] == fr_n) {
            params.f.resize(i + 1);
            break;
        }
    }

    write_parameters(get_model_name(model), get_low_bound_name(l_bound), algorithm_name);
}


// ------------------------------------- Test -------------------------------------

// ONE MAX - LINEAR
void test_onemax_line() {
    full_testing<opl, none_learning>(CLEAR_ONE_MAX, LINEAR, NONE_LEARN);
    full_testing<opl_separating, none_learning>(CLEAR_ONE_MAX, LINEAR, NONE_LEARN);
    full_testing<opl_Ab, none_learning>(CLEAR_ONE_MAX, LINEAR, NONE_LEARN);
    full_testing<oplQ, learning>(CLEAR_ONE_MAX, LINEAR, DEFAULT_LEARN);
    full_testing<oplQ, learning>(CLEAR_ONE_MAX, LINEAR, DEFAULT_LEARN_AB);

}

// ONE MAX - QUADRATIC
void test_onemax_quad() {
    full_testing<opl, none_learning>(CLEAR_ONE_MAX, QUADRATIC, NONE_LEARN);
    full_testing<opl_separating, none_learning>(CLEAR_ONE_MAX, QUADRATIC, NONE_LEARN);
    full_testing<opl_Ab, none_learning>(CLEAR_ONE_MAX, QUADRATIC, NONE_LEARN);
    full_testing<oplQ, learning>(CLEAR_ONE_MAX, QUADRATIC, DEFAULT_LEARN);
    full_testing<oplQ, learning>(CLEAR_ONE_MAX, QUADRATIC, DEFAULT_LEARN_AB);
}

// LEADING ONES - LINEAR
void test_leading_ones_line() {
    full_testing<opl, none_learning>(CLEAR_LEADING_ONES, LINEAR, NONE_LEARN);
    full_testing<opl_separating, none_learning>(CLEAR_LEADING_ONES, LINEAR, NONE_LEARN);
    full_testing<opl_Ab, none_learning>(CLEAR_LEADING_ONES, LINEAR, NONE_LEARN);
    full_testing<oplQ, learning>(CLEAR_LEADING_ONES, LINEAR, DEFAULT_LEARN);
    full_testing<oplQ, learning>(CLEAR_LEADING_ONES, LINEAR, DEFAULT_LEARN_AB);
}

// LEADING ONES - QUADRATIC
void test_leading_ones_quad() {
    full_testing<opl, none_learning>(CLEAR_LEADING_ONES, QUADRATIC, NONE_LEARN);
    full_testing<opl_separating, none_learning>(CLEAR_LEADING_ONES, QUADRATIC, NONE_LEARN);
    full_testing<opl_Ab, none_learning>(CLEAR_LEADING_ONES, QUADRATIC, NONE_LEARN);
    full_testing<oplQ, learning>(CLEAR_LEADING_ONES, QUADRATIC, DEFAULT_LEARN);
    full_testing<oplQ, learning>(CLEAR_LEADING_ONES, QUADRATIC, DEFAULT_LEARN_AB);
}


// ------------------------------------- Main -------------------------------------

int main() {
    test_onemax_line();
    test_onemax_quad();
    test_leading_ones_line();
    test_leading_ones_quad();
    return 0;
}
