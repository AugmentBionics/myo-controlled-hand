import numpy as np
from matplotlib import pyplot as plt


def parse_file(filename):
    """myo raw data file parser returns numpy array"""
    points = np.array([0, 0, 0], ndmin=2)
    with open(filename) as f:
        for line in f:
            parts = line.split(',')
            # skips the lines that have some error
            if len(parts) == 3:
                time = parts[0].split(':')[1]
                sample = parts[1].split(':')[1]
                mapped = parts[2].split(':')[1][:-1]
                # print(time, sample, mapped)
                points = np.vstack((points, np.array([int(time), int(sample), int(mapped)])))
    result = points
    return result


def plot_result(data, name):
    """input results from parse file"""
    plt.title(name)
    plt.plot(list(data[:, 0]), list(data[:, 1]))
    plt.plot(list(data[:, 0]), list(data[:, 2]))
    plt.show()


def main():
    points = np.array([0, 0, 0], ndmin=2)

    with open('data.txt') as f:
        for line in f:
            # line = f.readline()
            parts = line.split(',')
            if len(parts) == 3:
                time = parts[0].split(':')[1]
                sample = parts[1].split(':')[1]
                mapped = parts[2].split(':')[1][:-1]
                # print(time, sample, mapped)
                points = np.vstack((points, np.array([int(time), int(sample), int(mapped)])))

    length = -1
    # print(points[:length])

    # print(points[:, 0][:length])
    # print(points[:, 1][:length])
    plt.plot(list(points[:, 0][:length]), list(points[:, 1][:length]))
    plt.plot(list(points[:, 0][:length]), list(points[:, 2][:length]))
    plt.show()


if __name__ == '__main__':
    main()
