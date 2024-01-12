import regex as re
#pip3 install regex

filenames= [
    'grid_j',
    'grid_gs',
    # 'grid_j_omp',
    # 'grid_gs_omp',
    'tolerance_j',
    'tolerance_gs'
    ]

for filename in filenames:
    n = [re.findall(r'(?<=N:(\s)+)(\d+)\w*',line) 
            for line in open(f'src/logs/{filename}.log')]

    tolerance = [re.findall(r'(?<=Tolerance:(\s)+)(\d+\.\d+)\w+',line) 
            for line in open(f'src/logs/{filename}.log')]

    time = [re.findall(r'(?<=Time:(\s)+)(\d+\.\d+)\w+',line) 
            for line in open(f'src/logs/{filename}.log')]
    
    iterseconds = [re.findall(r'(?<=Number of iterations per second:(\s)+)(\d+\.\d+)\w+',line) 
            for line in open(f'src/logs/{filename}.log')]

    threads = [re.findall(r'(?<=Number of threads:(\s)+)(\d+)\w*',line) 
            for line in open(f'src/logs/{filename}.log')]

    n = list(filter(None, n))
    tolerance = list(filter(None, tolerance))
    time = list(filter(None, time))
    threads = list(filter(None, threads))
    iterseconds = list(filter(None, iterseconds))

    file = open(f'src/data/{filename}_thno{threads[0][0][1]}.dat', 'w+')
    file.write("#N\ttolerance\ttime\titerseconds\tthreads\n")
    file.write("\n".join(f"{i[0][1]}\t{j[0][1]}\t{k[0][1]}\t{l[0][1]}\t{m[0][1]}" for i, j, k, l, m in zip(n, tolerance, time, iterseconds, threads)))
