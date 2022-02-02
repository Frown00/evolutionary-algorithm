# Vehicle Routing Problem
Program created as a university project to become familiar with the procedure for testing, tuning and comparing the results of different metaheuristics.\
Each metaheuristic has a set of parameters that must be selected individually by an empirical method. Due to the element of non-determinism, metaheuristics must be run a minimum of 10 times and the results averaged. The research procedure, involves comparing the results of metaheuristics for files different difficulty scales.

## Problem ([wiki])
<img src="https://www.researchgate.net/profile/Savvas-Pericleous/publication/319754352/figure/fig1/AS:631655517659162@1527609819407/The-Capacitated-Vehicle-Routing-Problem-CVRP.png" width="350">

The capacitated vehicle routing problem (CVRP) is a VRP in which vehicles with limited carrying capacity need to pick up or deliver items at various locations. The items have a quantity, such as weight or volume, and the vehicles have a maximum capacity that they can carry. The problem is to pick up or deliver the items for the least cost, while never exceeding the capacity of the vehicles.

[wiki]: https://en.wikipedia.org/wiki/Vehicle_routing_problem

## Soultions
### Genetic Algorithm
The genetic algorithm is a method for solving both constrained and unconstrained optimization problems that is based on natural selection, the process that drives biological evolution. The genetic algorithm repeatedly modifies a population of individual solutions.

### Tabu Search
The implementation of tabu search uses memory structures that describe the visited solutions or user-provided sets of rules.[2] If a potential solution has been previously visited within a certain short-term period or if it has violated a rule, it is marked as "tabu" (forbidden) so that the algorithm does not consider that possibility repeatedly.

### Simulated Annealing
Simulated annealing is a process where the temperature is reduced slowly, starting from a random search at high temperature eventually becoming pure greedy descent as it approaches zero temperature. The randomness should tend to jump out of local minima and find regions that have a low heuristic value; greedy descent will lead to local minima. At high temperatures, worsening steps are more likely than at lower temperatures.

## Comparison
### Example (60 locations)
Best result through each generation

![alt text][chart]

### Final Results
![alt text][results]

[chart]: https://github.com/Frown00/evolutionary-algorithm/blob/main/assets/chart.PNG?raw=true "Most difficult task - 60 locations"
[results]: https://github.com/Frown00/evolutionary-algorithm/blob/main/assets/stats.PNG?raw=true "Results"
