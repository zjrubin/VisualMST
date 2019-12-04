import numpy as np
import matplotlib.pyplot as plt
from collections import defaultdict
from mpl_toolkits.mplot3d import Axes3D


def main():
    input_file = './sample1/sample1_out.txt'

    with open(input_file, 'r') as infile:
        num_verticies = int(infile.readline())

        # Read in verticies
        x, y, z = list(), list(), list()
        for i in range(num_verticies):
            x_, y_, z_ = infile.readline().split()
            x.append(float(x_))
            y.append(float(y_))
            z.append(float(z_))

        infile.readline()  # read in extra \n

        # Read in total edge weight
        total_edge_weight = float(infile.readline())
        print('total edge weight: ', total_edge_weight)

        # Read in edges
        edges = defaultdict(list)
        for line in infile.readlines():
            v1, v2 = line.split()
            v1, v2 = int(v1), int(v2)
            edges[v1].append(v2)

    # Create the graph
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
    