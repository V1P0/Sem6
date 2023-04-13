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
        int number_of_companies = company_limits.length;
        int number_of_airports = airport_targets.length;
        double[][] costs = {
                {10,7,8},
                {10,11,14},
                {9,12,4},
                {11,13,9}
        };

        Loader.loadNativeLibraries();
        MPSolver solver = MPSolver.createSolver("CBC");
        double infinity = MPSolver.infinity();
        MPVariable[][] x = new MPVariable[number_of_companies][number_of_airports];
        for (int i = 0; i < number_of_companies; i++) {
            for (int j = 0; j < number_of_airports; j++) {
                x[i][j] = solver.makeNumVar(0.0, infinity, "x" + i + j);
            }
        }
        for(int i = 0; i < number_of_companies; i++) {
            MPConstraint constraint = solver.makeConstraint(0.0, company_limits[i], "constraint_company" + i);
            for(int j = 0; j < number_of_airports; j++) {
                constraint.setCoefficient(x[i][j], 1.0);
            }
        }
        for(int j = 0; j < number_of_airports; j++) {
            MPConstraint constraint = solver.makeConstraint(airport_targets[j], infinity, "constraint_airport" + j);
            for(int i = 0; i < number_of_companies; i++) {
                constraint.setCoefficient(x[i][j], 1.0);
            }
        }
        MPObjective objective = solver.objective();
        for(int i = 0; i < number_of_companies; i++) {
            for(int j = 0; j < number_of_airports; j++) {
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
        System.out.print("          |");
        for(int i = 0; i < number_of_companies; i++) {
            System.out.printf(" Company %d |", i);
        }
        System.out.println();
        for(int j = 0; j < number_of_airports; j++) {
            System.out.print("Airport " + (j + 1) + " | ");
            for(int i = 0; i < number_of_companies; i++) {
                System.out.printf("%10.1f| ", x[i][j].solutionValue());
            }
            System.out.println();
        }
        System.out.println("-------------------------------------------------");
        System.out.println("Company   | Total    | Limit");
        for(int i = 0; i < number_of_companies; i++) {
            double total = 0.0;
            for(int j = 0; j < number_of_airports; j++) {
                total += x[i][j].solutionValue();
            }
            System.out.printf("Company %d |%10.1f|%10.1f\n", i, total, company_limits[i]);
        }
        System.out.println("-------------------------------------------------");
        System.out.println("Airport   | Total    | Target");
        for(int j = 0; j < number_of_airports; j++) {
            double total = 0.0;
            for(int i = 0; i < number_of_companies; i++) {
                total += x[i][j].solutionValue();
            }
            System.out.printf("Airport %d |%10.1f|%10.1f\n", j, total, airport_targets[j]);
        }


    }
}
