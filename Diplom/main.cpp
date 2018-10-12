#include "name_getter.h"

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


// Tester

const size_t SMALL_LAMBDA_SIZE = 3;
const size_t small_lambda[SMALL_LAMBDA_SIZE] = {1, 5, 10};
const size_t BIG_LAMBDA_SIZE = 7;
const size_t big_lambda[BIG_LAMBDA_SIZE] = {50, 100, 200, 400, 800, 1600, 3200};
const size_t LAMBDA_SIZE = SMALL_LAMBDA_SIZE + BIG_LAMBDA_SIZE;

const size_t N_SIZE = 10;
const size_t small_n[N_SIZE] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
const size_t big_n[N_SIZE] = {10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};

aver_solution aver_solut[2][LAMBDA_SIZE][N_SIZE];


const size_t TEST_SIZE = 100;

solution test_solut[TEST_SIZE];


template <typename OPL>
OPL create_solver(problem probl, size_t lambda, size_t n, none_reward rew) {
    return OPL(probl, lambda, n);
}

template <typename OPLQ>
OPLQ create_solver(problem probl, size_t lambda, size_t n, reward rew) {
    return OPLQ(probl, lambda, n, rew);
}

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

    aver_solut[size_ind][lam_ind][n_ind] = aver_solution(evaluations, eval_deviation, generations, gen_deviation);
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
    cout <<  "\n" << algorithm_name << "\n\n";

    for (size_t i = 0; i < SMALL_LAMBDA_SIZE; ++i) {
        size_t lambda = small_lambda[i];
        for (size_t j = 0; j < N_SIZE; ++j) {
            size_t n = small_n[j];
            cout << "lambda: " << lambda << "  n: " << n << "\n";
            OPL solver = create_solver<OPL>(probl, lambda, n, rew);
            testing<OPL>(SMALL, i, j, solver);
        }
    }
    for (size_t i = 0; i < BIG_LAMBDA_SIZE; ++i) {
        size_t lambda = big_lambda[i];
        for (size_t j = 0; j < N_SIZE; ++j) {
            size_t n = big_n[j];
            cout << "lambda: " << lambda << "  n: " << n << "\n";
            OPL solver = create_solver<OPL>(probl, lambda, n, rew);
            testing<OPL>(BIG, i, j, solver);
        }
    }

    write_solution(get_problem_name(probl), algorithm_name);
}


int main() {
    //full_testing<opl, none_reward>(ONE_MAX, NONE);
    //full_testing<opl_separating, none_reward>(ONE_MAX, NONE);
    full_testing<opl_Ab, none_reward>(ONE_MAX, NONE);

    //full_testing<oplQ, reward>(ONE_MAX, ABSOLUTELY);
    //full_testing<oplQ, reward>(ONE_MAX, BINARY);
    full_testing<oplQ, reward>(ONE_MAX, SUBTRACTION);
    //full_testing<oplQ, reward>(ONE_MAX, DIVISION);

    //full_testing<oplQ_separating, reward>(ONE_MAX, ABSOLUTELY);
    //full_testing<oplQ_separating, reward>(ONE_MAX, BINARY);
    full_testing<oplQ_separating, reward>(ONE_MAX, SUBTRACTION);
    //full_testing<oplQ_separating, reward>(ONE_MAX, DIVISION);

    return 0;
}