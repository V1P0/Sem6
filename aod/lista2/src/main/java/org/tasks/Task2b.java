package org.tasks;

import com.google.ortools.Loader;
import com.google.ortools.linearsolver.*;

import java.util.Arrays;

public class Task2b {
    public static void main(String[] args) {
        Graph graph = Graph.getRandomGraph(20);
        final int maxTime = 10;
        int start = 0;
        int end = 9;

        Loader.loadNativeLibraries();
        MPSolver solver = MPSolver.createSolver("CBC");
        MPVariable[][] x = new MPVariable[graph.getVerticesCount()][graph.getVerticesCount()];
        for(int i = 0; i < graph.getVerticesCount(); i++) {
            for(Integer j :graph.getOutgoings(i)) {
                x[i][j] = solver.makeNumVar(0, 1, "x" + i + "_" + j);
            }
        }
        MPObjective objective = solver.objective();
        for(int i = 0; i < graph.getVerticesCount(); i++) {
            for(Integer j :graph.getOutgoings(i)) {
                objective.setCoefficient(x[i][j], graph.costs[i][j]);
            }
        }
        objective.setMinimization();
        /*MPConstraint timeConstraint = solver.makeConstraint(0, maxTime, "time_constraint");
        for(int i = 0; i < graph.getVerticesCount(); i++) {
            for(Integer j :graph.getOutgoings(i)) {
                timeConstraint.setCoefficient(x[i][j], graph.times[i][j]);
            }
        }*/
        for(int i = 0; i < graph.getVerticesCount(); i++) {
            MPConstraint constraint;
            if(i == start) {
                constraint = solver.makeConstraint(1, 1, "constraint" + i);

            }else if(i == end) {
                constraint = solver.makeConstraint(-1, -1, "constraint" + i);
            }else{
                constraint = solver.makeConstraint(0, 0, "constraint" + i);
            }
            for(Integer j :graph.getOutgoings(i)) {
                constraint.setCoefficient(x[i][j], 1);
            }
            for(Integer j :graph.getIncomings(i)) {
                constraint.setCoefficient(x[j][i], -1);
            }
        }
        MPSolver.ResultStatus resultStatus = solver.solve();
        if(resultStatus != MPSolver.ResultStatus.OPTIMAL) {
            System.out.println("The problem does not have an optimal solution!");
            return;
        }
        System.out.println("Total cost = " + objective.value());
        for(int i = 0; i < graph.getVerticesCount(); i++) {
            for(Integer j :graph.getOutgoings(i)) {
                System.out.println("x" + i + "_" + j + " = " + x[i][j].solutionValue());
            }
        }




    }
}
