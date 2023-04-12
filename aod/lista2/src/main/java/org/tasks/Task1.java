package org.tasks;

import com.google.ortools.Loader;
import com.google.ortools.linearsolver.MPConstraint;
import com.google.ortools.linearsolver.MPObjective;
import com.google.ortools.linearsolver.MPSolver;
import com.google.ortools.linearsolver.MPVariable;

public class Task1 {
    public static void main(String[] args) {
        double[] company_limits = { 275_000.0, 550_000.0, 660_000.0 };
        double[] airport_targets = { 110_000.0, 220_000.0, 330_000.0, 440_000.0 };
        double[][] costs = {
                {10,7,8},
                {10,11,14},
                {9,12,4},
                {11,13,9}
        };

        Loader.loadNativeLibraries();
        MPSolver solver = MPSolver.createSolver("CBC");
        double infinity = MPSolver.infinity();
        MPVariable[][] x = new MPVariable[3][4];
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 4; j++) {
                x[i][j] = solver.makeNumVar(0.0, infinity, "x" + i + j);
            }
        }
        for(int i = 0; i < 3; i++) {
            MPConstraint constraint = solver.makeConstraint(0.0, company_limits[i], "constraint_company" + i);
            for(int j = 0; j < 4; j++) {
                constraint.setCoefficient(x[i][j], 1.0);
            }
        }
        for(int j = 0; j < 4; j++) {
            MPConstraint constraint = solver.makeConstraint(airport_targets[j], infinity, "constraint_airport" + j);
            for(int i = 0; i < 3; i++) {
                constraint.setCoefficient(x[i][j], 1.0);
            }
        }
        MPObjective objective = solver.objective();
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 4; j++) {
                objective.setCoefficient(x[i][j], costs[j][i]);
            }
        }
        objective.setMinimization();
        MPSolver.ResultStatus resultStatus = solver.solve();
        if(resultStatus != MPSolver.ResultStatus.OPTIMAL) {
            System.out.println("The problem does not have an optimal solution!");
            return;
        }
        System.out.println("Total cost = " + objective.value());
        System.out.println("          | Company 1 | Company 2 | Company 3 |");
        for(int j = 0; j < 4; j++) {
            System.out.print("Airport " + (j + 1) + " | ");
            for(int i = 0; i < 3; i++) {
                System.out.printf("%10.1f| ", x[i][j].solutionValue());
            }
            System.out.println();
        }
        System.out.println("-------------------------------------------------");
        System.out.println("Company  | Total    | Limit");
        for(int i = 0; i < 3; i++) {
            double total = 0.0;
            for(int j = 0; j < 4; j++) {
                total += x[i][j].solutionValue();
            }
            System.out.printf("Company%d |%10.1f|%10.1f\n", i, total, company_limits[i]);
        }
        System.out.println("-------------------------------------------------");
        System.out.println("Airport  | Total    | Target");
        for(int j = 0; j < 4; j++) {
            double total = 0.0;
            for(int i = 0; i < 3; i++) {
                total += x[i][j].solutionValue();
            }
            System.out.printf("Airport%d |%10.1f|%10.1f\n", j, total, airport_targets[j]);
        }


    }
}
