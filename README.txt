Assignment 5: Graph, BetterPriorityQueue, and Dijkstra

Build and run (requires a C++11 compiler and make):
    make
    make test

The three executables are graph-tests, bpq-tests, and dijkstra. Each has its
own test main; do not compile all .cpp files into one executable.
Remove generated executables with:
    make clean

Files:
    Graph.h / Graph.cpp: directed graph with heap-allocated, owned edges.
    BetterPriorityQueue.h / .cpp: BPQNode and a std::priority_queue subclass.
    Dijkstra.h / Dijkstra.cpp: supplied signature and shortest-distance function.
    GraphTests.cpp / BPQTests.cpp / DijkstraTests.cpp: starter and expanded tests.
    Makefile: builds the three programs required by the assignment.

Behavior and choices where the handout does not specify a result:
    Graph keys are unsigned long long values. Zero is valid. ULLONG_MAX is
    reserved as INVALID_NODE_KEY and is rejected by AddNode.
    Edges are directed. Add both directions for an undirected connection.
    Self-loops are allowed. Duplicate ordered endpoints are rejected even
    if a different weight is supplied. Missing endpoints throw invalid_argument.
    GetOutwardEdgesFrom throws invalid_argument for an unknown node.
    Debug strings preserve insertion order and match the starter tests.
    Returned edge pointers stay valid until graph destruction or assignment.
    Copies own independent edges, avoiding double deletion and dangling copies.

    BPQNode identity is its gnode value. Update changes only priority, and
    returns false for absent nodes, equal priorities, or larger priorities.
    The algorithm inserts one queue entry per graph node. Like the supplied
    std::priority_queue interface, push itself does not enforce unique keys;
    Update changes the first matching entry if callers insert duplicates.

    dijkstra throws invalid_argument for a null graph or absent endpoint.
    The distance from a valid node to itself is zero.
    INT_MAX represents unreachable nodes and any shortest distance >= INT_MAX.
    This follows the provided int return type and BPQNode infinity sentinel.
    Exact INT_MAX distances therefore have the same representation as infinity.
    Oversized unsigned weights cannot wrap into negative distances.

Complexity of this implementation:
    Graph uses vectors for insertion order, so membership is O(V), edge
    insertion is O(V+E), and outward-edge lookup is O(V+E+d log(d+1)), where
    d is out-degree. GetNodes is O(V log(V+1)).
    Queue Contains is O(V); Update is O(V) search plus O(log(V+1)) sift-up.
    Dijkstra is O(V^2 + VE + V log(V+1)) worst-case time and O(V) auxiliary
    space, excluding the graph. See the comment above dijkstra for the analysis.

Tests include:
    All supplied starter checks.
    The full six-node sample graph (1 -> 5 costs 20).
    Directed/disconnected graphs, zero-weight cycles, self-loops, invalid
    arguments, large node keys, integer bounds, and graph copy ownership.
    3000 deterministic mixed queue operations checked against an independent map.
    All-pairs Dijkstra comparisons with independent Floyd-Warshall results on
    120 deterministic generated graphs, including oversized weights.

Sources and assistance:
    assignment_5_description.pdf: requirements, example graph, output format.
    Graph.h.png: public graph interface transcribed into Graph.h.
    BPQNode_struct.txt: supplied BPQNode fields and comparison operators.
    Dijkstra.h: copied unchanged from the supplied header.
    GraphTestsStarter.cpp, BPQTestsStarter.cpp, DijkstraTestsStarter.cpp:
    retained starter tests, renamed and expanded.
    OpenAI Codex: implementation, expanded tests, and explanatory comments.
    No external websites were used.

Submission:
    The code is prepared locally. The assignment also asks for a public GitHub
    repository, a repository link on Canvas, and a video recording. Those
    publishing/submission steps and the video are not included in this package.
