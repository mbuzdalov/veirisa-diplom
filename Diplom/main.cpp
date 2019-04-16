#include "name_getter.h"

// ------------------------------------- Common -------------------------------------

// --- String generator ---

mt19937 generator(time(0));

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
OPL create_solver(problem probl, size_t lambda, size_t n, low_bound l_bound, none_learning none_learn) {
    return OPL(probl, lambda, n, l_bound);
}

template <typename OPLQ>
OPLQ create_solver(problem probl, size_t lambda, size_t n, low_bound l_bound, learning learn) {
    return OPLQ(probl, lambda, n, l_bound, learn);
}


// ------------------------------------- Tester -------------------------------------

const size_t LAMBDA_SIZE = 2;
const size_t big_lambda[LAMBDA_SIZE] = {/*1, 2, 5, 10, 50, 100, 200, 400, 800, 1600, */ 3200, 6400};

const size_t N_SIZE = 1;
const size_t big_n[N_SIZE] = {1000};

aver_solution aver_solut[LAMBDA_SIZE][N_SIZE];

const size_t TEST_SIZE = 10;
solution test_solut[TEST_SIZE];


void write_evaluations(const string& probl_name, const string& l_bound_name, const string& algorithm_name) {
    ofstream fout_eval("Results/" + probl_name + "/" + l_bound_name + "/Evaluations/eval_" + algorithm_name + ".txt");
    //fout_eval << algorithm_name << " (n - lambda - evaluations - deviation):\n\n";
    for (size_t i = 0; i < LAMBDA_SIZE; ++i) {
        size_t lambda = big_lambda[i];
        for (size_t j = 0; j < N_SIZE; ++j) {
            size_t n = big_n[j];
            fout_eval << lambda << "\t"
                      << n << "\t"
                      << aver_solut[i][j].evaluations << "\t"
                      << aver_solut[i][j].eval_deviation << "\n";
        }
    }
}

void write_generations(const string& probl_name, const string& l_bound_name, const string& algorithm_name) {
    ofstream fout_gen("Results/" + probl_name + "/" + l_bound_name + "/Generations/gen_" + algorithm_name + ".txt");
    //fout_gen << algorithm_name << " (n - lambda - generations - deviation):\n\n";
    for (size_t j = 0; j < N_SIZE; ++j) {
        size_t n = big_n[j];
        for (size_t i = 0; i < LAMBDA_SIZE; ++i) {
            size_t lambda = big_lambda[i];
            fout_gen << n << "\t"
                     << lambda << "\t"
                     << aver_solut[i][j].generations << "\t"
                     << aver_solut[i][j].gen_deviation << "\n";
        }
    }
}

template <typename OPL>
void testing(size_t lam_ind, size_t n_ind, OPL solver) {
    size_t n = big_n[n_ind];

    size_t evaluations = 0, generations = 0;
    for (size_t test = 0; test < TEST_SIZE; ++test) {
        test_solut[test] = solver.generate_solution(random_string(generator, n));
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

    aver_solut[lam_ind][n_ind] = {evaluations, eval_deviation, generations, gen_deviation};
}


template <typename OPL, typename LT>
void full_testing(problem probl, low_bound l_bound, LT learn) {
    string algorithm_name = ea<OPL>::get_name() + get_learning_name(learn);
    cout <<  "\n" << "testing: " << algorithm_name << "\n\n";

    for (size_t i = 0; i < LAMBDA_SIZE; ++i) {
        size_t lambda = big_lambda[i];
        for (size_t j = 0; j < N_SIZE; ++j) {
            size_t n = big_n[j];
            cout << "lambda: " << lambda << "  n: " << n;// << "\n";
            clock_t t = clock();
            OPL solver = create_solver<OPL>(probl, lambda, n, l_bound, learn);
            testing<OPL>(i, j, solver);
            cout << "  generations: " << aver_solut[i][j].generations
                 << "  deviation: " << aver_solut[i][j].gen_deviation << "\n";
        }
    }

    //write_evaluations(get_problem_name(probl), get_low_bound_name(l_bound), algorithm_name);
    //write_generations(get_problem_name(probl), get_low_bound_name(l_bound), algorithm_name);
}


// ------------------------------------- Fixed runtime -------------------------------------

const size_t fr_lambda = 1600;
const size_t fr_n = 10000;
const string fr_test_string = random_string(generator, fr_n);

parameters params;


void write_parameters(const string& probl_name, const string& l_bound_name, const string& algorithm_name) {
    ofstream fout_func("Results/" + probl_name + "/" + l_bound_name + "/Function/" + to_string(fr_lambda) +
                        "/func_" + algorithm_name + ".txt");
    //fout_func << algorithm_name << " (function):\n";
    //fout_func << "~  n = " << fr_n << "  ~  " << "lambda = " << fr_lambda << "  ~\n\n";
    for (size_t i = 0; i < params.f.size(); ++i) {
        fout_func << params.f[i] << "\t";
    }

    cout << "Params size: " << params.f.size() << "\n\n";

    ofstream fout_prob("Results/" + probl_name + "/" + l_bound_name + "/Probability/" + to_string(fr_lambda) +
                        "/prob_" + algorithm_name + ".txt");
    //fout_prob << algorithm_name << " (probability):\n";
    //fout_prob << "~  n = " << fr_n << "  ~  " << "lambda = " << fr_lambda << "  ~\n\n";
    for (size_t i = 0; i < params.p.size(); ++i) {
        if (!isnan(params.p[i])) {
            fout_prob << fixed << setprecision(8) << params.p[i];
        }
        fout_prob << "\t";
    }
}

template <typename OPL, typename LT>
void fixed_runtime(problem probl, low_bound l_bound, LT learn) {
    string algorithm_name = ea<OPL>::get_name() + get_learning_name(learn);
    cout <<  "\n" << "fixed runtime: " << algorithm_name << "\n\n";

    OPL solver = create_solver<OPL>(probl, fr_lambda, fr_n, l_bound, learn);
    solver.generate_solution(fr_test_string);
    params = solver.get_params();

    write_parameters(get_problem_name(probl), get_low_bound_name(l_bound), algorithm_name);
}


// ------------------------------------- Main -------------------------------------

int main() {

    size_t lambda_s = 3200;
    size_t lambda_b = 6400;
    size_t n = 10000;

    for (int i = 0; i < 10; ++i) {
        string rs = random_string(generator, n);

        oplQ solverQ(ONE_MAX, lambda_s, n, LINEAR, DEFAULT_LEARN);
        cout << "gen_Q (" << lambda_s << "): " << solverQ.generate_solution(rs).generations << "\n";

        oplQ solverQNorm(ONE_MAX, lambda_s, n, LINEAR, DEFAULT_NORM_LEARN);
        cout << "gen_NQ (" << lambda_s << "): " << solverQNorm.generate_solution(rs).generations << "\n";

        cout << "\n";

        oplQ solverQB(ONE_MAX, lambda_b, n, LINEAR, DEFAULT_LEARN);
        cout << "gen_Q (" << lambda_b << "): " << solverQB.generate_solution(rs).generations << "\n";

        oplQ solverQNormB(ONE_MAX, lambda_b, n, LINEAR, DEFAULT_NORM_LEARN);
        cout << "gen_NQ (" << lambda_b << "): " << solverQNormB.generate_solution(rs).generations << "\n";

        cout << "\n\n";
    }

    //full_testing<opl, none_learning>(ONE_MAX, LINEAR, NONE_LEARN);
    //full_testing<opl_separating, none_learning>(ONE_MAX, LINEAR, NONE_LEARN);

    //full_testing<opl_Ab, none_learning>(ONE_MAX, LINEAR, NONE_LEARN);

    //full_testing<oplQ, learning>(ONE_MAX, LINEAR, DEFAULT_LEARN);
    //full_testing<oplQ, learning>(ONE_MAX, LINEAR, DEFAULT_LEARN_AB);
    //full_testing<oplQ, learning>(ONE_MAX, LINEAR, DEFAULT_NORM_LEARN);
    for (int i = 0; i < 10; ++i) {
        full_testing<oplQ, learning>(ONE_MAX, QUADRATIC, DEFAULT_LEARN);
        full_testing<oplQ, learning>(ONE_MAX, QUADRATIC, DEFAULT_NORM_LEARN);
    }

    return 0;
}