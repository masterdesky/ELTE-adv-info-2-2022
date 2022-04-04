#!/bin/env/python
import os

import numpy as np
import matplotlib.pyplot as plt


def plot_data(data):
    fig, ax = plt.subplots(figsize=(14, 9))

    # Columns in file:
    # `x`, `y`, `y_FW`, `y_BW`, `y_CE`, `y_AN`
    x, y, y_FW, y_BW, y_CE, y_AN = \
        (data[:, i] for i in range(data.shape[1]))

    lw = 3
    alpha = 0.6
    ax.plot(x, y, label='y', color='tab:blue', lw=lw)
    ax.plot(x, y_FW, label='y_FW', color='tab:orange', lw=lw, alpha=alpha)
    ax.plot(x, y_BW, label='y_BW', color='tab:green', lw=lw, alpha=alpha)
    ax.plot(x, y_CE, label='y_CE', color='tab:red', lw=lw, alpha=alpha)
    ax.plot(x, y_AN, label='y_AN', color='tab:purple', lw=lw, alpha=alpha)

    ax.set_xlim(min(x), max(x))

    ax.tick_params(axis='both', which='major', labelsize=20)

    ax.legend(loc='best', fontsize=16)

    fname = "analysis/out/diff.png"
    if not os.path.exists(os.path.dirname(fname)):
        os.makedirs(os.path.dirname(fname))
    plt.savefig(fname, bbox_inches="tight")

    plt.show()


def main():
    data = np.genfromtxt("data/diff.dat", delimiter='\t')
    plot_data(data)


if __name__ == '__main__':
    main()
