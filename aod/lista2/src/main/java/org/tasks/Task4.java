package org.tasks;

import com.google.ortools.Loader;
import com.google.ortools.linearsolver.MPConstraint;
import com.google.ortools.linearsolver.MPObjective;
import com.google.ortools.linearsolver.MPSolver;
import com.google.ortools.linearsolver.MPVariable;

public class Task4 {
    public static void main(String[] args) {
        int[][] containers = {
                {1, 0, 0, 0, 0, 0, 1},
                {0, 1, 0, 0, 0, 1, 0},
                {0, 0, 1, 0, 1, 0, 0},
                {0, 0, 0, 1, 0, 0, 0},
                {0, 0, 1, 0, 1, 0, 0},
                {0, 1, 0, 0, 0, 1, 0},
                {1, 0, 0, 0, 0, 0, 1}
        };
        int k = 3;

        int n = containers.length;
        int m = containers[0].length;

        Loader.loadNativeLibraries();
        MPSolver solver = MPSolver.createSolver("CBC");
        MPVariable[][] camera = new MPVariable[n][m];
        MPVariable[][] seen = new MPVariable[n][m];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                camera[i][j] = solver.makeBoolVar("x" + i + j);
                seen[i][j] = solver.makeIntVar(0, MPSolver.infinity(), "y" + i + j);
            }
        }
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                MPConstraint constraint = solver.makeConstraint(0, 0, "constraint" + i +"_" + j);
                constraint.setCoefficient(seen[i][j], -1);
                for(int x = -k; x <= k; x++) {
                    if(i + x < n && i + x >= 0) {
                        constraint.setCoefficient(camera[i + x][j], 1);
                    }
                    if(j + x < m && j + x >= 0) {
                        constraint.setCoefficient(camera[i][j + x], 1);
                    }
                }
                if(containers[i][j] == 1) {
                    constraint = solver.makeConstraint(1, MPSolver.infinity(), "constraint_" + i +"_" + j);
                    constraint.setCoefficient(seen[i][j], 1);
                    constraint = solver.makeConstraint(0, 0, "constraint__" + i +"_" + j);
                    constraint.setCoefficient(camera[i][j], 1);
                }
            }
        }
        MPObjective objective = solver.objective();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                objective.setCoefficient(camera[i][j], 1.0);
            }
        }
        objective.setMinimization();

        MPSolver.ResultStatus resultStatus = solver.solve();
        if (resultStatus != MPSolver.ResultStatus.OPTIMAL) {
            System.out.println("The problem does not have an optimal solution!");
            return;
        }
        System.out.println("Total cost = " + objective.value());
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                System.out.print((int)camera[i][j].solutionValue() + " ");
            }
            System.out.println();
        }

    }
}
