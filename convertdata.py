import regex as re
#pip3 install regex

filenames= [
    'grid_j',
    'grid_gs',
    # 'grid_j_omp',
    # 'grid_gs_omp',
    ]

for filename in filenames:
    n = [re.findall(r'(?<=N:(\s)+)(\d+)\w+',line) 
            for line in open(f'src/logs/{filename}.log')]

    time = [re.findall(r'(?<=Time:(\s)+)(\d+\.\d+)\w+',line) 
            for line in open(f'src/logs/{filename}.log')]

    n = list(filter(None, n))
    time = list(filter(None, time))


    file = open(f'src/data/{filename}.dat', 'w+')
    file.write("\n".join(f"{i[0][1]}\t{j[0][1]}" for i, j in zip(n, time)))
