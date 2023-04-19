import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

def plot_data():
    df = pd.read_csv('p15data.csv')
    #sort df by n and when n is the same take average
    df = df.groupby('n').mean()

    #plot the data
    plt.plot(df.index, df['WD'], label='Walking distance')
    plt.plot(df.index, df['MD'], label='Manhattan distance')

    plt.xlabel('n')
    plt.ylabel('Visited nodes')

    plt.legend()
    plt.yscale('log')
    plt.savefig('plots.png')
    plt.show()


if __name__ == '__main__':
    plot_data()
