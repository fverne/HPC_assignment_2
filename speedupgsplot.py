#!/usr/bin/env python # [1]
"""\
This script plots the speedup diagram according to the input data file. 
The input data file should be in the following format:
TODO: add format

Usage: myscript.py file.dat file2.dat file3.dat
"""

from matplotlib import pyplot as plt
import sys
import argparse

def read_data(datafile: str):
    """Read data from datafile and return a list of lists."""
    data = []
    with open(datafile, 'r') as f:        
        for line in f:
            if line[0] == "#":
                continue

            parts = line.strip().split()
            data_point = [float(parts[5]), float(parts[2])]
            data.append(data_point)
    return data


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print(__doc__)
        sys.exit(1)
    parser = argparse.ArgumentParser(
        description="Plot data from multiple files with labels."
    )
    parser.add_argument('files', nargs='+', help="Path to data files")
    parser.add_argument('-l', '--labels', 
        nargs='+', 
        help='Labels for the data files'
    )
    parser.add_argument('-n', '--name', 
        default="speedupplot.png",
        help="The name of the plot file, default is speedupplot.png"
    )
    parser.add_argument('-t', '--title', 
        default="Speedup",
        help="The title of the figure."
    )
    parser.add_argument('-L1', default=32, help="Size of L1 Cache with unut of KB")
    parser.add_argument('-L2', default=256, help="Size of L2 Cache with unut of KB")
    parser.add_argument('-L3', default=25600, help="Size of L3 Cache with unut of KB")
    parser.add_argument('-log', action="store_true", help="Draw the log of the data")
    args = parser.parse_args()
    caches = list(zip(['L1', 'L2', 'L3'], [args.L1, args.L2, args.L3]))

    fig, ax1 = plt.subplots()

    ax2 = ax1.twinx()

    width=0.5
    spacing=0.0
    mem_size=[]
    intermediate_mem_size=[]
    flops=[]
    speedups=[]
    labels=[]
    iterator = 0
    # read the data file and plot
    for file, label in zip(args.files, args.labels):
        data = read_data(file)
        # plot the memory hierarchy diagram 
        mem_size.append([pair[0]+spacing for pair in data])
        flops.append([pair[1] for pair in data])
        intermediate_mem_size = [pair[0]+spacing*0.5 for pair in data]
        
        #amdahl
        speedups.append([flops[0][iterator]/times for times in flops[0]])
        spacing+=0.5
        iterator+=1

    labels.append("Gauss-Seidel (OMP)")
    labels.append("Gauss-Seidel (OMP) Speedup")

    ax1.bar(mem_size[0], flops[0], width=width, color='b', align='center')
    ax2.plot(intermediate_mem_size, speedups[0], marker='o', linestyle='-')

    ax1.set_xlabel('Number of Cores')
    ax1.set_ylabel('Runtime [Secs]')
    ax2.set_ylabel("Speedup")

    # for label, cache in caches:
    #     plt.axvline(x=cache, color='r', linestyle='--', linewidth=1, label=label)
    
    if args.log: 
        plt.xscale('log')
    
    xlim = plt.xlim()
    plt.savefig(args.name) # https://stackoverflow.com/questions/68558593/how-to-get-tick-labels-in-matplotlib-prior-to-calling-plt-show
    # plt.xticks(
    #     ticks= list(plt.gca().get_xticks()) + [cache for _, cache in caches], 
    #     labels= plt.gca().get_xticklabels(minor=False) + [label for label, _ in caches]
    # )
    plt.gca().set_xlim(xlim)

    plt.grid()
    fig.legend(labels, loc='upper center', bbox_to_anchor=(0.5,1.15), ncol=1, bbox_transform=fig.transFigure)
    plt.title(args.title)
    # plt.show()
    plt.savefig(args.name, bbox_inches="tight")