package org.tasks;

import com.google.ortools.Loader;
import com.google.ortools.linearsolver.MPConstraint;
import com.google.ortools.linearsolver.MPObjective;
import com.google.ortools.linearsolver.MPSolver;
import com.google.ortools.linearsolver.MPVariable;

public class Task5 {


    public static void main(String[] args) {
        int[][] time_int_machine = {
                {5, 10, 6},
                {3, 6, 4},
                {4, 5, 3},
                {4, 2, 1}
        };
        int[] max_sold = {400, 100, 150, 500};
        int[] product_cost = {9, 7, 6, 5};
        int[] production_cost_per_machine = {2/60, 2/60, 3/60};
        int[] production_cost_per_product = {4, 1, 1, 1};
        int max_machine_time = 60*60;

        int number_of_products = time_int_machine.length;
        int number_of_machines = time_int_machine[0].length;

        Loader.loadNativeLibraries();

        MPSolver solver = MPSolver.createSolver("CBC");
        MPVariable[] p = new MPVariable[number_of_products];
        MPVariable[] m = new MPVariable[number_of_machines];

        for (int i = 0; i < number_of_products; i++) {
            p[i] = solver.makeIntVar(0, max_sold[i], "p" + i);
        }
        for (int i = 0; i < number_of_machines; i++) {
            m[i] = solver.makeIntVar(0, max_machine_time, "m" + i);
        }
        //connect p and m
        for(int i = 0; i < number_of_machines; i++){
            MPConstraint constraint = solver.makeConstraint(0, 0, "constraint" + i);
            constraint.setCoefficient(m[i], -1);
            for(int j = 0; j < number_of_products; j++){
                constraint.setCoefficient(p[j], time_int_machine[j][i]);
            }
        }
        MPObjective objective = solver.objective();
        for (int i = 0; i < number_of_products; i++) {
            objective.setCoefficient(p[i], product_cost[i]-production_cost_per_product[i]);
        }
        for (int i = 0; i < number_of_machines; i++) {
            objective.setCoefficient(m[i], -production_cost_per_machine[i]);
        }
        objective.setMaximization();
        MPSolver.ResultStatus resultStatus = solver.solve();
        if (resultStatus != MPSolver.ResultStatus.OPTIMAL) {
            System.out.println("The problem does not have an optimal solution!");
            return;
        }
        System.out.println("Total cost = " + objective.value());
        for (int i = 0; i < number_of_products; i++) {
            System.out.println("Product " + i + " = " + p[i].solutionValue());
        }
        for (int i = 0; i < number_of_machines; i++) {
            System.out.println("Machine " + i + " = " + m[i].solutionValue());
        }
    }
}
