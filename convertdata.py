import regex as re
#pip3 install regex

filenames= [
    'grid_j',
    'grid_gs',
    'threads_jomp',
    'threads_gsomp',
    'tolerance_j',
    'tolerance_gs'
    ]

for filename in filenames:
    n = [re.findall(r'(?<=N:(\s)+)(\d+)\w*',line) 
            for line in open(f'src/logs/{filename}.log')]

    tolerance = [re.findall(r'(?<=Tolerance:(\s)+)((-)*\d+\.\d+)\w+',line) 
            for line in open(f'src/logs/{filename}.log')]

    time = [re.findall(r'(?<=Time:(\s)+)(\d+\.\d+)\w+',line) 
            for line in open(f'src/logs/{filename}.log')]
    
    iterations = [re.findall(r'(?<=Number of iterations:(\s)+)(\d+)\w+',line) 
            for line in open(f'src/logs/{filename}.log')]
    
    iterseconds = [re.findall(r'(?<=Number of iterations per second:(\s)+)(\d+\.\d+)\w+',line) 
            for line in open(f'src/logs/{filename}.log')]

    threads = [re.findall(r'(?<=Number of threads:(\s)+)(\d+)\w*',line) 
            for line in open(f'src/logs/{filename}.log')]

    n = list(filter(None, n))
    tolerance = list(filter(None, tolerance))
    time = list(filter(None, time))
    iterations = list(filter(None, iterations))
    iterseconds = list(filter(None, iterseconds))
    threads = list(filter(None, threads))

    file = open(f'src/data/{filename}.dat', 'w+')
    file.write("#N\ttolerance\ttime\titerations\titerseconds\tthreads\n")
    file.write("\n".join(f"{i[0][1]}\t{j[0][1]}\t{k[0][1]}\t{l[0][1]}\t{m[0][1]}\t{n[0][1]}" for i, j, k, l, m, n in zip(n, tolerance, time, iterations, iterseconds, threads)))
