import os
import sys

import numpy as np
import matplotlib.pyplot as plt


def plot_data(data):
    fig, ax = plt.subplots(figsize=(14, 9))

    # Columns in file:
    # `x`, `y`, `y_FW`, `y_BW`, `y_CE`, `y_AN`
    x, y, y_FW, y_BW, y_CE, y_AN = \
        (data[:, i] for i in range(data.shape[1]))

    lw = 1
    ax.plot(x, y, label='y', color='tab:blue', lw=lw)
    ax.plot(x, y_FW, label='y_FW', color='tab:orange', lw=lw)
    ax.plot(x, y_BW, label='y_BW', color='tab:green', lw=lw)
    ax.plot(x, y_CE, label='y_CE', color='tab:red', lw=lw)
    ax.plot(x, y_AN, label='y_AN', color='tab:purple', lw=lw)

    ax.legend(loc='best')

    fname = "analysis/out/diff.png"
    if not os.path.exists(os.path.dirname(fname)):
        os.makedirs(os.path.dirname(fname))
    plt.savefig(fname, bbox_inches="tight")

    plt.show()


def main():
    data = np.genfromtxt("analysis/data/diff.dat", delimiter='\t')
    plot_data(data)


if __name__ == '__main__':
    main()
