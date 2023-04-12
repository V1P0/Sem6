package org.tasks;

import com.google.ortools.Loader;
import com.google.ortools.linearsolver.MPConstraint;
import com.google.ortools.linearsolver.MPObjective;
import com.google.ortools.linearsolver.MPSolver;
import com.google.ortools.linearsolver.MPVariable;

public class Task3 {
    public static void main(String[] args) {
        int[][] minimum = {
                {2, 4, 3},
                {3, 6, 5},
                {5, 7, 6}
        };
        int[][] maximum = {
                {3, 7, 5},
                {5, 7, 10},
                {8, 12, 10}
        };
        int[] minimum_per_shift = {10, 20, 18};
        int[] minimum_per_district = {10, 14, 13};

        Loader.loadNativeLibraries();
        MPSolver solver = MPSolver.createSolver("CBC");
        MPVariable[][] x = new MPVariable[minimum.length][minimum[0].length];
        for (int i = 0; i < minimum.length; i++) {
            for (int j = 0; j < minimum[0].length; j++) {
                x[i][j] = solver.makeIntVar(minimum[i][j], maximum[i][j], "x" + i + j);
            }
        }

        MPConstraint[] shift_constraints = new MPConstraint[minimum_per_shift.length];
        for (int i = 0; i < minimum_per_shift.length; i++) {
            shift_constraints[i] = solver.makeConstraint(minimum_per_shift[i], MPSolver.infinity(), "shift_constraint" + i);
            for (int j = 0; j < minimum[0].length; j++) {
                shift_constraints[i].setCoefficient(x[i][j], 1.0);
            }
        }

        MPConstraint[] district_constraints = new MPConstraint[minimum_per_district.length];
        for (int i = 0; i < minimum_per_district.length; i++) {
            district_constraints[i] = solver.makeConstraint(minimum_per_district[i], MPSolver.infinity(), "district_constraint" + i);
            for (int j = 0; j < minimum.length; j++) {
                district_constraints[i].setCoefficient(x[j][i], 1.0);
            }
        }

        MPObjective objective = solver.objective();
        for (int i = 0; i < minimum.length; i++) {
            for (int j = 0; j < minimum[0].length; j++) {
                objective.setCoefficient(x[i][j], 1.0);
            }
        }
        objective.setMinimization();

        MPSolver.ResultStatus resultStatus = solver.solve();
        if (resultStatus != MPSolver.ResultStatus.OPTIMAL) {
            System.out.println("The problem does not have an optimal solution!");
            return;
        }
        System.out.println("Total cost = " + objective.value());
        System.out.println("           | Shift 1 | Shift 2 | Shift 3 |");
        for(int i = 0; i < minimum.length; i++) {
            System.out.print("District " + (i + 1) + " |");
            for(int j = 0; j < minimum[0].length; j++) {
                System.out.print("    " + (int) x[i][j].solutionValue() + "    |");
            }
            System.out.println();
        }
    }
}
