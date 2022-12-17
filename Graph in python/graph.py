import math


class Graph:
    """
    Class graph keeps track of vertex and their relationship with other adjacent vertexes
    """
    def __init__(self):
        self.vertices_dict = {}
        self.edges_dict = {}
        self.graph = {}
        self.num_vertices = 0

    def add_vertex(self, label):
        """
        add a vertex with the specified label. Returns itself. label must be a
        string or raise ValueError
        :param label:
        :return: graph
        """
        if not isinstance(label, str):  # check if label is a string
            raise ValueError
        self.vertices_dict[label] = None  # add new vertex to dict
        self.add_edge(label, label, 0.0)
        self.num_vertices += 1

        return self

    def add_edge(self, source, dest, weight):
        """
        edge is a tuple
        add an edge from vertex src to vertex dest with weight w. Return
        the graph. validate src, dest, and w: raise ValueError if not valid.
        :param source: vertex1
        :param dest: vertex 2
        :param weight: default to 1 if no weight is provided
        :return: graph
        """
        check_source = False
        check_dest = False
        # print(source, dest, weight) # debug

        if not isinstance(source, str) or not isinstance(dest, str):
            raise ValueError

        if isinstance(weight, int) or isinstance(weight, float):
            pass

        else:
            raise ValueError

        for vertex in self.vertices_dict.keys():
            if source == vertex:
                check_source = True
                break

        for vertex in self.vertices_dict.keys():
            if dest == vertex:
                check_dest = True
                break

        if check_source and check_dest:
            self.edges_dict[(source, dest)] = weight

        else:
            # print("this is rejected")
            raise ValueError
        return self

    def get_weight(self, source, dest):
        """
        Return the weight on edge src-dest (math.inf if no path exists,
        raise ValueError if src or dest not added to graph).
        :param source:
        :param dest:
        :return:
        """
        if not isinstance(source, str) or not isinstance(dest, str):
            raise ValueError

        if source not in self.vertices_dict or dest not in self.vertices_dict:
            raise ValueError

        checker = (source, dest)
        found_edge = False
        for edge in self.edges_dict.keys():
            # print(checker, edge)
            if checker == edge:
                found_edge = True
                break

        if found_edge:
            return self.edges_dict[checker]

        # return math.infinity if edge doesn't exist
        if source == dest:
            self.add_edge(source, dest, 0.0)
            return self.edges_dict[checker]

        return math.inf

    def dfs(self, starting_vertex):
        """
        Return a generator for traversing the graph in depth-first order
        starting from the specified vertex. Raise a ValueError if the vertex does not exist.
        :param starting_vertex:
        :return:
        """
        if starting_vertex not in self.vertices_dict:
            raise ValueError

        stack = []
        visited = []
        stack.append(starting_vertex)

        while stack:
            popped = stack.pop(0)
            yield popped

            if popped not in visited:  # if main vertex is not in visited...
                visited.append(popped)  # append main vertex to visited
                # check for adj vertex related to main vertex
                for adj in self.vertex_and_their_friends(popped):
                    if adj not in visited:  # if adj vertex is not in
                        stack.append(adj)

    def vertex_and_their_friends(self, popped):
        adj_list = []
        # search in edges dictionary related to popped
        for tuple in self.edges_dict.keys():
            if popped == tuple[0]:
                adj_list.append(tuple[1])

        # return a list of adj vertexes
        return adj_list

    def bfs(self, starting_vertex):
        """
        Return a generator for traversing the graph in breadth-first order
        starting from the specified vertex. Raise a ValueError if the vertex does not exist.
        :param starting_vertex:
        :return:
        """
        if starting_vertex not in self.vertices_dict:
            raise ValueError

        queue = []  # vertexes in line to be checked
        visited = []  # vertexes that already have been visited
        queue.append(starting_vertex)
        visited.append(starting_vertex)

        while queue:  # if there's something in the queue...
            popped = queue.pop(0)
            yield popped

            # include vertex and friends in here
            # for each adjacent vertex to be popped
            for adjacent_vertex in self.vertex_and_their_friends(popped):  # return a list of adj of main vertex
                if adjacent_vertex not in visited:  # if adjacent_vertex is not in list...
                    visited.append(adjacent_vertex)  # append to the visited list
                    queue.append(adjacent_vertex)

    def dsp(self, source, dest):
        """
        Return a tuple (path length , the list of vertices on the path from dest
        back to src). If no path exists, return the tuple (math.inf,  empty list.)
        :param source:
        :param dest:
        :return: tuple
        """
        if not isinstance(source, str) or not isinstance(dest, str):
            raise ValueError

        if source not in self.vertices_dict or dest not in self.vertices_dict:
            raise ValueError

        dict = {}  # hold all values from a graph
        lyst = []  # append to pathdict, contains a path
        adj_list = []  # pull all the adjacent nodes from starting node
        pathdict = {}  # key: nodes, values: keep track of path from source to dest. Return value of key: dest
        visited = [source]  # keep track of all nodes already visited
        queue = []  # keep track of all nodes that still need to be visited
        popped = source  # start the popping from the starting node
        previous_node = {}

        # set up dictionaries
        for adj in self.vertices_dict:
            dict[adj] = math.inf
            pathdict[adj] = math.inf
            previous_node[adj] = None
            queue.append(adj)

        dict[source] = 0
        previous_node[popped] = popped
        # print(dict) # debug
        lyst.append(popped)
        pathdict[popped] = lyst
        while queue:
            # print("IM THE SMALLEST NUMBER: ", min(dict))
            # if this is my first time looping...
            # if source not in visited:
            #     popped = queue.pop(0)
            # else:
            #     # ignore the 'A'
            #     # grab the letter with the next smallest value out of all adjacents
            #     num = math.inf
            #     vertex = None
            #     for adj in adj_list:
            #         if dict[adj] < num and adj not in visited:
            #             num = dict[adj]
            #             vertex = adj
            #     popped = vertex
            #     print(popped)
            #     queue.remove(popped)

            # for current vertex, find the neighbors
            info = self.vertex_and_their_friends(popped)
            for thing in info:
                if thing not in visited and thing not in adj_list:  # Omit the 'thing' that's the same char as popped
                    adj_list.append(thing)  # append to the adj_list

            # compare the current weight of an adj node with the home node + edgeWeight
            # if current weight of adj node is larger, update value with home node + edgeWeight
            for adj in adj_list:
                edgeWeight = self.get_weight(popped, adj)
                if dict[adj] > dict[popped] + edgeWeight:
                    dict[adj] = dict[popped] + edgeWeight
                    previous_node[adj] = popped  # changing value because popped is now the shorter route

            # look for the smallest value between all adjs of homenode
            num = math.inf
            vertex = None
            for keys in dict:
                if keys not in visited and keys in adj_list:
                    if dict[keys] < num:
                        num = dict[keys]
                        vertex = keys
            if vertex == None:
                break
            # the key with the smallest value becomes the new popped
            # print(vertex)
            lyst = []
            for i in pathdict[previous_node[vertex]]:
                lyst.append(i)

            lyst.append(vertex)
            pathdict[vertex] = lyst
            # print(pathdict)

            queue.remove(vertex)  # remove node from queue
            popped = vertex
            visited.append(popped)  # put vertex away in visited, don't need to visit again

            #     # if vertex matches the same char as the vertex..
            #     if popped == adj[0]:
            #         #assign weight to said vertex
            #         initial_weight = dict[popped] # A = 0.0
            #         dict[popped] = initial_weight
            #
            #     else:
            #         neighbor_of_popped = adj # update neighbor of popped in original dictionary
            #         initial_weight = dict[popped]
            #         # print(initial_weight)
            #
            #         # add initial weight with destination vertex
            #         edgeWeight = self.get_weight(popped, neighbor_of_popped) #("A", "B")
            #         totalWeight = edgeWeight + initial_weight
            #         # print(totalWeight)
            #         if dict[neighbor_of_popped] == math.inf: # if it's infinity, update edgeweight
            #             # print("value has been adjusted")
            #             dict[neighbor_of_popped] = totalWeight
            #             print(dict)
            #         # if calculated distance is less than the known distance, update the shortest distance
            #         elif totalWeight < dict[neighbor_of_popped]:
            #             dict[neighbor_of_popped] = totalWeight
            # visited.append(popped)

        # print(lyst)

        # source to current to looking
        weight_value = dict[dest]
        clear_list = []
        path_of_list = pathdict.get(dest)
        if path_of_list == math.inf:
            path_of_list = clear_list
        le_tuple = (weight_value, path_of_list)
        return le_tuple

    def dsp_all(self, source):
        """
        Return a dictionary of the shortest weighted path between src and all
        other vertices using Dijkstra's Shortest Path algorithm. In the dictionary, the key is the
        destination vertex label, the value is a list of vertices
         on the path from src to dest inclusive.
        :param source:
        :param src:
        :return:
        """

        if not isinstance(source, str):
            raise ValueError

        if source not in self.vertices_dict:
            raise ValueError
        if not isinstance(source, str):
            raise ValueError

        if source not in self.vertices_dict:
            raise ValueError

        dict = {}  # hold all values from a graph
        lyst = []  # append to pathdict, contains a path
        adj_list = []  # pull all the adjacent nodes from starting node
        pathdict = {}  # key: nodes, values: keep track of path from source to dest. Return value of key: dest
        visited = [source]  # keep track of all nodes already visited
        queue = []  # keep track of all nodes that still need to be visited
        popped = source  # start the popping from the starting node
        previous_node = {}

        # set up dictionaries
        for adj in self.vertices_dict:
            dict[adj] = math.inf
            pathdict[adj] = math.inf
            previous_node[adj] = None
            queue.append(adj)

        dict[source] = 0
        previous_node[popped] = popped
        lyst.append(popped)
        pathdict[popped] = lyst
        while queue:

            # for current vertex, find the neighbors
            info = self.vertex_and_their_friends(popped)
            for thing in info:
                if thing not in visited and thing not in adj_list:  # Omit the 'thing' that's the same char as popped
                    adj_list.append(thing)  # append to the adj_list

            # compare the current weight of an adj node with the home node + edgeWeight
            # if current weight of adj node is larger, update value with home node + edgeWeight
            for adj in adj_list:
                edgeWeight = self.get_weight(popped, adj)
                if dict[adj] > dict[popped] + edgeWeight:
                    dict[adj] = dict[popped] + edgeWeight
                    previous_node[adj] = popped  # changing value because popped is now the shorter route

            # look for the smallest value between all adjs of homenode
            num = math.inf
            vertex = None
            for keys in dict:
                if keys not in visited and keys in adj_list:
                    if dict[keys] < num:
                        num = dict[keys]
                        vertex = keys
            if vertex == None:
                break
            # the key with the smallest value becomes the new popped
            # print(vertex)
            lyst = []
            for i in pathdict[previous_node[vertex]]:
                lyst.append(i)

            lyst.append(vertex)
            pathdict[vertex] = lyst
            # print(pathdict)

            queue.remove(vertex)  # remove node from queue
            popped = vertex
            visited.append(popped)  # put vertex away in visited, don't need to visit again
        clear = []
        for i in pathdict:
            if pathdict[i] == math.inf:
                pathdict[i] = clear

        return pathdict

    def __str__(self):
        """
        Produce a string representation of the graph that can be used with print(). The
        format of the graph should be in GraphViz dot notation,
        :return:
        """
        str = ""
        str += "digraph G {\n"
        source_vertex: ""
        dest_vertex: ""
        # print(self.get_weight("A", "B"))

        for source in self.vertices_dict.keys():
            # print("source: ", source)
            for tuple in self.edges_dict.keys():
                # print("tuple: ", tuple)
                if source == tuple[0]:
                    if source == tuple[1]:
                        pass
                    else:
                        dest_vertex = tuple[1]
                        found_edge = self.get_weight(source, tuple[1])

                        str += f"   {source} -> {dest_vertex}" \
                               f" [label=\"{found_edge}\",weight=\"{found_edge}\"];\n"
        str += "}\n"
        return str


def main():
    """
    1. Construct the graph shown in Figure 1 using your ADT.
    2. Print it to the console in GraphViz notation as shown in Figure 1.
    3. Print results of DFS starting with vertex “A” as shown in Figure 2.
    4. BFS starting with vertex “A” as shown in Figure 3.
    5. Print the path from vertex “A” to vertex “F” (not shown here) using Djikstra’s
    shortest path algorithm (DSP) as a string like #3 and #4.
    6. Print the shortest paths from “A” to each other vertex, one path per line using DSP.
    :return:
    """
    g = Graph()
    g.add_vertex("A")
    g.add_vertex("B")
    g.add_vertex("C")
    g.add_vertex("D")
    g.add_vertex("E")
    g.add_vertex("F")

    g.add_edge("A", "B", 2)
    g.add_edge("A", "F", 9)

    g.add_edge("B", "F", 6)
    g.add_edge("B", "D", 15)
    g.add_edge("B", "C", 8)

    g.add_edge("C", "D", 1)

    g.add_edge("E", "C", 7)
    g.add_edge("E", "D", 3)

    g.add_edge("F", "B", 6)
    g.add_edge("F", "E", 3)

    path = g.dsp("A", "B")
    assert path == (2, ['A', 'B'])
    path = g.dsp("A", "C")
    assert path == (10, ['A', 'B', 'C'])
    path = g.dsp("A", "D")
    assert path == (11, ['A', 'B', 'C', 'D'])
    path = g.dsp("A", "F")
    assert path == (8, ['A', 'B', 'F'])
    path = g.dsp("D", "A")
    assert path == (math.inf, [])

main()
