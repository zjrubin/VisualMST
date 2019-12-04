import argparse
import random


def main():
    parser = argparse.ArgumentParser(description='Script for generating verticies in a 3D cartesian space')
    parser.add_argument('--number', '-n', type=int, default=25,
                        help='The number of vertices')
    parser.add_argument('--outfile', '-o', type=str, default='verticies.txt',
                        help='The name of the output file for the generated vertices')
    parser.add_argument('--min', type=float, default=-50,
                        help='The minimum value of any given coordinate')
    parser.add_argument('--max', type=float, default=50,
                        help='The maximum value of any given coordinate')

    args = parser.parse_args()
    generate_verticies(num_vertices=args.number, min_coord=args.min, max_coord=args.max, outfile_name=args.outfile)


def generate_verticies(num_vertices: int, min_coord: float, max_coord: float, outfile_name: str) -> None:
    with open(outfile_name, 'w') as outfile:
        for _ in range(num_vertices):
            x = random.uniform(min_coord, max_coord)
            y = random.uniform(min_coord, max_coord)
            z = random.uniform(min_coord, max_coord)
            print(x, ' ', y, ' ', z, file=outfile)


if __name__ == '__main__':
    main()
