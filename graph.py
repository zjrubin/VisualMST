import argparse
import numpy as np
import matplotlib.pyplot as plt
from collections import defaultdict
from mpl_toolkits.mplot3d import Axes3D
from typing import List, TextIO, Tuple


def main():
    parser = argparse.ArgumentParser(description='Script for graphing an MST in 3D cartesian space')
    parser.add_argument('--infile', '-i', type=str, required=True,
                        help='The name of the input file containing the verticies and edges')
    args = parser.parse_args()

    run(args.infile)


def run(input_filename: str) -> None:
    with open(input_filename, 'r') as infile:
        # Read in verticies
        x, y, z = read_verticies(infile)

        infile.readline()  # read in extra \n

        # Read in total edge weight
        total_edge_weight = float(infile.readline())
        print('total edge weight: ', total_edge_weight)

        # Read in edges
        edges = read_edges(infile)

    create_graph(x, y, z, edges)


def read_verticies(infile: TextIO) -> Tuple[List, List, List]:
    num_verticies = int(infile.readline())
    x, y, z = list(), list(), list()
    for _ in range(num_verticies):
        x_, y_, z_ = infile.readline().split()
        x.append(float(x_))
        y.append(float(y_))
        z.append(float(z_))
    return (x, y, z)


def read_edges(infile: TextIO) -> defaultdict(list):
    edges = defaultdict(list)
    for line in infile.readlines():
        v1, v2 = line.split()
        v1, v2 = int(v1), int(v2)
        edges[v1].append(v2)
    return edges


def create_graph(x: list, y: list, z: list, edges: defaultdict) -> None:
    # Create the figure
    plt.figure(figsize=(20,10))
    ax = plt.axes(projection='3d')
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')

    # Plot the verticies
    ax.scatter(x, y, z, color='red')

    # Plot the edges
    for v1, v2s in edges.items():
        for v2 in v2s:
            ax.plot([x[v1], x[v2]], [y[v1], y[v2]], [z[v1], z[v2]], color='blue')

    plt.show()


if __name__ == '__main__':
    main()
