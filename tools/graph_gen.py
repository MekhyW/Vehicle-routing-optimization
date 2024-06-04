import random

def generate_demand_dictionary(N):
    return {i: random.randint(1, 10) for i in range(1, N)}

def generate_graph_entries(num_nodes, max_weight=100, probability=0.25):
    graph = {}
    for i in range(1, num_nodes):
        graph[(0, i)] = random.randint(1, max_weight)
        graph[(i, 0)] = graph[(0, i)]  # Assume the distance back to the depot is the same
    for i in range(1, num_nodes):
        for j in range(i+1, num_nodes):
            if random.random() > (1 - probability):
                weight = random.randint(1, max_weight)
                graph[(i, j)] = weight

    return graph

num_nodes = int(input("Enter the number of nodes: "))
demands = generate_demand_dictionary(num_nodes)
graph = generate_graph_entries(num_nodes)

with open('graph.txt', 'w') as file:
    file.write(str(num_nodes) + "\n")
    for location, demand in demands.items():
        line = f"{location} {demand}\n"
        file.write(line)
    file.write(str(len(graph)) + "\n")
    for edge, weight in graph.items():
        line = f"{edge[0]} {edge[1]} {weight}\n"  # SOURCE DESTINATION COST
        file.write(line)
print("Graph generated successfully!")
