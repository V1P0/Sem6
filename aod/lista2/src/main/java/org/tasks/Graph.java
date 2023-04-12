package org.tasks;

import java.util.ArrayList;
import java.util.List;

public class Graph {
    int size;
    List<List<Integer>> outgoings;
    List<List<Integer>> incomings;

    double[][] times;
    double[][] costs;

    public Graph(int size) {
        this.size = size;
        outgoings = new ArrayList<>(size);
        incomings = new ArrayList<>(size);
        times = new double[size][size];
        costs = new double[size][size];
        for(int i = 0; i < size; i++) {
            for(int j = 0; j < size; j++) {
                times[i][j] = -1;
                costs[i][j] = -1;
            }
        }
        for(int i = 0; i < size; i++) {
            outgoings.add(new ArrayList<>());
            incomings.add(new ArrayList<>());
        }
    }

    public void addEdge(int from, int to, double time, double cost) {
        outgoings.get(from).add(to);
        incomings.get(to).add(from);
        times[from][to] = time;
        costs[from][to] = cost;
    }

    public List<Integer> getOutgoings(int vertex) {
        return outgoings.get(vertex);
    }

    public List<Integer> getIncomings(int vertex) {
        return incomings.get(vertex);
    }

    public static Graph getRandomGraph(int size) {
        Graph graph = new Graph(size);
        for(int i = 0; i < size; i++) {
            for(int j = 0; j < size; j++) {
                if(Math.random() < 0.2) {
                    graph.addEdge(i, j, Math.random() * 10, Math.random() * 10);
                }
            }
        }
        return graph;
    }

    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < size; i++) {
            sb.append(i).append(": ");
            for (int j : outgoings.get(i)) {
                sb.append(j).append(" (").append(times[i][j]).append(", ").append(costs[i][j]).append(") ");
            }
            sb.append("\n");
        }
        return sb.toString();
    }

    public int getVerticesCount() {
        return size;
    }

}
