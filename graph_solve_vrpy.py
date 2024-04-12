from networkx import DiGraph, set_node_attributes
from vrpy import VehicleRoutingProblem

def read_graph_file(file_path):
    with open(file_path, 'r') as file:
        N = int(file.readline().strip()) - 1
        demands = {}
        for _ in range(N):
            line = file.readline().strip().split()
            node_id, demand = int(line[0]), int(line[1])
            demands[node_id] = demand
        K = int(file.readline().strip())
        edges = []
        for _ in range(K):
            line = file.readline().strip().split()
            source, destination, weight = int(line[0]), int(line[1]), int(line[2])
            edges.append((source, destination, weight))
    return demands, edges

file_path = 'graph.txt'
demands, edges = read_graph_file(file_path)

G = DiGraph()
for start, end, cost in edges:
    if start == 0:
        start = "Source"
    if end == 0:
        end = "Sink"
    G.add_edge(start, end, cost=cost)

set_node_attributes(G, values=demands, name="demand")

prob = VehicleRoutingProblem(G, load_capacity=int(input("Enter the vehicle capacity: ")))
prob.num_stops = int(input("Enter the maximum number of stops: "))
prob.solve()

print()
print("Best routes: " + str(prob.best_routes))
print("Best value: " + str(prob.best_value))
print("Load: " + str(prob.best_routes_load))
print("Cost: " + str(prob.best_routes_cost))