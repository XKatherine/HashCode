#include "ortools/linear_solver/linear_solver.h"
#include "ortools/linear_solver/linear_solver.pb.h"

namespace operations_research {
  void practice( MPSolver::OptimizationProblemType optimization_problem_type) {
    MPSolver solver("LinearOP", optimization_problem_type);
    const double infinity = solver.infinity();
    MPVariable* const x = solver.MakeNumVar(-infinity, infinity, "x");
    MPVariable* const y = solver.MakeNumVar(-infinity, infinity, "y");
    MPObjective* const ob = solver.MutableObjective();
    ob->SetCoefficient(x, 3);
    ob->SetCoefficient(y, 4);
    ob->SetMaximization();

    MPConstraint* const c1 = solver.MakeRowConstraint(-infinity, 14.0);
    c1->SetCoefficient(x, 1);
    c1->SetCoefficient(y, 2);

    MPConstraint* const c2 = solver.MakeRowConstraint(0, infinity);
    c2->SetCoefficient(x, 3);
    c2->SetCoefficient(y, -1);
    
    MPConstraint* const c3 = solver.MakeRowConstraint(-infinity, 2);
    c3->SetCoefficient(x, 1);
    c3->SetCoefficient(y, -1);

    solver.Solve();
    printf("\nSolution:");
    printf("\nx = %.1f", x->solution_value());
    printf("\ny = %.1f", y->solution_value());
    printf("\nobjective = %.1f", ob->Value());
  }

  void RunPractice() {
    practice(MPSolver::GLOP_LINEAR_PROGRAMMING);
  }
}

int main(){
  operations_research::RunPractice();
  return 0;
}
