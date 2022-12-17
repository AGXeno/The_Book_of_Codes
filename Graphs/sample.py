class Graph:
    def __init__(self):
        # initialize an empty dictionary to store the graph's vertices and edges
        self.vertices = {}

    def addVertex(self, vertex):
        # if the vertex doesn't exist in the graph, add it and set its value to an empty set
        if vertex not in self.vertices:
            self.vertices[vertex] = set()

    def addEdge(self, v1, v2):
        # if both vertices exist in the graph, add the edge between them
        if v1 in self.vertices and v2 in self.vertices:
            self.vertices[v1].add(v2)
            self.vertices[v2].add(v1)

    def removeVertex(self, vertex):
        # if the vertex exists in the graph, remove it and all edges connected to it
        if vertex in self.vertices:
            # loop through all vertices in the graph
            for v in self.vertices:
                # if the vertex is connected to the one we're removing, remove the edge
                if vertex in self.vertices[v]:
                    self.vertices[v].remove(vertex)
            # finally, remove the vertex itself
            del self.vertices[vertex]

    def removeEdge(self, v1, v2):
        # if both vertices exist in the graph, remove the edge between them
        if v1 in self.vertices and v2 in self.vertices:
            self.vertices[v1].remove(v2)
            self.vertices[v2].remove(v1)

    def getVertices(self):
        # return a list of all vertices in the graph
        return list(self.vertices.keys())

    def getEdges(self):
        # return a list of all edges in the graph
        edges = []
        # loop through all vertices in the graph
        for v in self.vertices:
            # loop through all edges connected to each vertex
            for neighbor in self.vertices[v]:
                # if the edge hasn't been added to the list yet, add it
                if (v, neighbor) not in edges and (neighbor, v) not in edges:
                    edges.append((v, neighbor))
        return edges

    def getNeighbors(self, vertex):
        # return a list of all vertices connected to the given vertex by an edge
        if vertex in self.vertices:
            return list(self.vertices[vertex])
        return None

    def containsVertex(self, vertex):
        # return true if the given vertex is in the graph, and false otherwise
        return vertex in self.vertices

    def containsEdge(self, v1, v2):
        # return true if the given edge is in the graph, and false otherwise
        # an edge exists if both vertices exist in the graph and are connected by an edge
        return v1 in self.vertices and v2 in self.vertices and v2 in self.vertices[v1]

    def isEmpty(self):
     pass