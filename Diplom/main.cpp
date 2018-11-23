#include "name_getter.h"

// ------------------------------------- Common -------------------------------------

// String generator

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

// Solver creater

template <typename OPL>
OPL create_solver(problem probl, size_t lambda, size_t n, none_reward rew) {
    return OPL(probl, lambda, n);
}

template <typename OPLQ>
OPLQ create_solver(problem probl, size_t lambda, size_t n, reward rew) {
    return OPLQ(probl, lambda, n, rew);
}


// ------------------------------------- Tester -------------------------------------

/*
const size_t SMALL_LAMBDA_SIZE = 0;
const size_t small_lambda[SMALL_LAMBDA_SIZE] = {};
const size_t BIG_LAMBDA_SIZE = 10;
const size_t big_lambda[BIG_LAMBDA_SIZE] = {1, 5, 10, 50, 100, 200, 400, 800, 1600, 3200};
const size_t LAMBDA_SIZE = SMALL_LAMBDA_SIZE + BIG_LAMBDA_SIZE;

const size_t N_SIZE = 10;
const size_t small_n[N_SIZE] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
const size_t big_n[N_SIZE] = {10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};
*/

const size_t SMALL_LAMBDA_SIZE = 0;
const size_t small_lambda[SMALL_LAMBDA_SIZE] = {};
const size_t BIG_LAMBDA_SIZE = 4;
const size_t big_lambda[BIG_LAMBDA_SIZE] = {200, 400, 800, 1600};
const size_t LAMBDA_SIZE = SMALL_LAMBDA_SIZE + BIG_LAMBDA_SIZE;

const size_t N_SIZE = 1;
const size_t small_n[N_SIZE] = {1000};
const size_t big_n[N_SIZE] = {10000};

aver_solution aver_solut[2][LAMBDA_SIZE][N_SIZE];

//const size_t TEST_SIZE = 100;
const size_t TEST_SIZE = 5;
solution test_solut[TEST_SIZE];


template <typename OPL>
void testing(test_size size_ind, size_t lam_ind, size_t n_ind, OPL solver) {
    size_t n = size_ind == SMALL ? small_n[n_ind] : big_n[n_ind];

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

    aver_solut[size_ind][lam_ind][n_ind] = {evaluations, eval_deviation, generations, gen_deviation};
}

void write_solution(const string& probl_name, const string& algorithm_name) {
    ofstream fout_eval("Results/" + probl_name + "/Evaluations/eval_" + algorithm_name + ".txt");
    fout_eval << algorithm_name << " (n - lambda - evaluations - deviation):\n\n";
    for (size_t i = 0; i < SMALL_LAMBDA_SIZE; ++i) {
        size_t lambda = small_lambda[i];
        for (size_t j = 0; j < N_SIZE; ++j) {
            size_t n = small_n[j];
            fout_eval << lambda << "\t"
                      << n << "\t"
                      << aver_solut[SMALL][i][j].evaluations << "\t"
                      << aver_solut[SMALL][i][j].eval_deviation << "\n";
        }
    }
    for (size_t i = 0; i < BIG_LAMBDA_SIZE; ++i) {
        size_t lambda = big_lambda[i];
        for (size_t j = 0; j < N_SIZE; ++j) {
            size_t n = big_n[j];
            fout_eval << lambda << "\t"
                      << n << "\t"
                      << aver_solut[BIG][i][j].evaluations << "\t"
                      << aver_solut[BIG][i][j].eval_deviation << "\n";
        }
    }

    ofstream fout_gen("Results/" + probl_name + "/Generations/gen_" + algorithm_name + ".txt");
    fout_gen << algorithm_name << " (n - lambda - generations - deviation):\n\n";
    for (size_t j = 0; j < N_SIZE; ++j) {
        size_t n = big_n[j];
        for (size_t i = 0; i < BIG_LAMBDA_SIZE; ++i) {
            size_t lambda = big_lambda[i];
            fout_gen << n << "\t"
                      << lambda << "\t"
                      << aver_solut[BIG][i][j].generations << "\t"
                      << aver_solut[BIG][i][j].gen_deviation << "\n";
        }
    }
}

template <typename OPL, typename R>
void full_testing(problem probl, R rew) {
    string algorithm_name = ea<OPL>::get_name() + get_reward_name(rew);
    cout <<  "\n" << "testing: " << algorithm_name << "\n\n";

    for (size_t i = 0; i < SMALL_LAMBDA_SIZE; ++i) {
        size_t lambda = small_lambda[i];
        for (size_t j = 0; j < N_SIZE; ++j) {
            size_t n = small_n[j];
            cout << "lambda: " << lambda << "  n: " << n;// << "\n";
            OPL solver = create_solver<OPL>(probl, lambda, n, rew);
            testing<OPL>(SMALL, i, j, solver);
            cout << "  evaluations: " << aver_solut[SMALL][i][j].evaluations
                 << "  deviation: " << aver_solut[SMALL][i][j].eval_deviation << "\n";
        }
    }
    for (size_t i = 0; i < BIG_LAMBDA_SIZE; ++i) {
        size_t lambda = big_lambda[i];
        for (size_t j = 0; j < N_SIZE; ++j) {
            size_t n = big_n[j];
            cout << "lambda: " << lambda << "  n: " << n;// << "\n";
            OPL solver = create_solver<OPL>(probl, lambda, n, rew);
            testing<OPL>(BIG, i, j, solver);
            cout << "  evaluations: " << aver_solut[BIG][i][j].evaluations
                 << "  deviation: " << aver_solut[BIG][i][j].eval_deviation << "\n";
        }
    }

    //write_solution(get_problem_name(probl), algorithm_name);
}


// ------------------------------------- Fixed runtime -------------------------------------

const size_t fr_lambda = 400;
const size_t fr_n = 10000;
const string fr_test_string = random_string(generator, fr_n);

vector<parameters> params;


void write_parameters(const string& probl_name, const string& algorithm_name) {
    ofstream fout_param("Results/" + probl_name + "/Parameters/param_" + algorithm_name + ".txt");
    fout_param << algorithm_name << " (function - probability):\n";
    fout_param << "~  n = " << fr_n << "  ~  " << "lambda = " << fr_lambda << "  ~\n\n";
    cout << "!" << params.size() << "\n";
    for (size_t i = 0; i < params.size(); ++i) {
        fout_param << params[i].f << "\t" << params[i].p << "\n";
    }
}

template <typename OPL, typename R>
void fixed_runtime(problem probl, R rew) {
    string algorithm_name = ea<OPL>::get_name() + get_reward_name(rew);
    cout <<  "\n" << "fixed runtime: " << algorithm_name << "\n\n";

    OPL solver = create_solver<OPL>(probl, fr_lambda, fr_n, rew);
    solver.generate_solution(fr_test_string);
    params = solver.get_params();

    write_parameters(get_problem_name(probl), algorithm_name);
}


// ------------------------------------- Main -------------------------------------

int main() {
    //full_testing<opl, none_reward>(ONE_MAX, NONE);
    full_testing<opl_separating, none_reward>(ONE_MAX, NONE);
    //full_testing<opl_Ab, none_reward>(ONE_MAX, NONE);

    //full_testing<oplQ, reward>(ONE_MAX, SUBTRACTION);
    //full_testing<oplQ, reward>(ONE_MAX, DIVISION);

    //full_testing<oplQ_separating, reward>(ONE_MAX, SUBTRACTION);
    //full_testing<oplQ_separating, reward>(ONE_MAX, DIVISION);

    //fixed_runtime<opl, none_reward>(ONE_MAX, NONE);
    //fixed_runtime<opl_separating, none_reward>(ONE_MAX, NONE);
    //fixed_runtime<opl_Ab, none_reward>(ONE_MAX, NONE);

    //fixed_runtime<oplQ, reward>(ONE_MAX, SUBTRACTION);
    //fixed_runtime<oplQ, reward>(ONE_MAX, DIVISION);

    //fixed_runtime<oplQ_separating, reward>(ONE_MAX, SUBTRACTION);
    //fixed_runtime<oplQ_separating, reward>(ONE_MAX, DIVISION);

    return 0;
}