import scipy.stats

lambda_size = 10
algo = ['opl', 'opl_separating', 'opl_Ab', 'oplQ_Ab']

def wilcoxon_test(problem_name, main_a):
    d = dict()

    for a in algo:
        gens = []
        with open('Wilcoxon/' + problem_name + '/input/' + a + '.txt', 'r') as input:
            input.readline()
            for line in input:
                cur_gens = [float(el) for el in line.split('\t')[3:]]
                gens.append(cur_gens)
        d.setdefault(a, gens)

    with open('Wilcoxon/' + problem_name + '/output/' + main_a + '.txt', 'w') as output:
        for a in algo:
            output.write(a + '\t')
        output.write('\n')
        for i in range(0, lambda_size):
            main_a_cur_gens = d.get(main_a)[i]
            for a in algo:
                a_cur_gens = d.get(a)[i]
                T, p_value = scipy.stats.wilcoxon(x=main_a_cur_gens, y=a_cur_gens)
                output.write('{:.4}'.format(p_value) + '\t')
            output.write('\n')

if __name__ == '__main__':
    wilcoxon_test('PlatoReg', 'opl')
    wilcoxon_test('PlatoReg', 'oplQ_Ab')
    wilcoxon_test('Neutral', 'opl')
    wilcoxon_test('Neutral', 'oplQ_Ab')
    wilcoxon_test('Reg', 'opl')
    wilcoxon_test('Reg', 'oplQ_Ab')
