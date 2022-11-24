For game path finding, agents are treated similarly to particles, and so the general structure of an array of 'Person' structs or classes held within a 'Population' class that handles spawning and calling of Person functions will be used. 

A lot of research on pathfinding in games is based on efficiency; due to the very narrow and focussed nature of this project this is not of immediate concern, although considerations may be made when testing larger numbers of Persons on larger maps to stress test the made system at a later point in the project. 

As mentioned, this project will also link to a Villager AI from a previous project. This will involve loading python scripts into c++, (Jon's demo here: https://github.com/NCCA/EmbedPython/blob/master/src/Agent.cpp )
Pathfinding generally uses derivations of Dijkstra's or A* path finding algorithms across a grid or generated NavMesh. In each case, a network is generated of connected points with distances measured which are then used in the path finding algorithms. 

As this is realtime, updating the path based on changes to the world such as to avoid other Persons or to avoid obstacles could be explored. 

- (Not sure of the inclusion of this step because is might be complicated) generation of nav mesh / map data
- Generation of network to be used by...
- The actual path finding with an algorithm such as Dijkstra or A*
  - Driven by the AI of the Persons 
- The real time use of this path by an ai agent with considerations for avoidance of obstacles and other agents. 

(Makes sense to try to work on a navmesh based approach as it is used by both unity and unreal for their inbuilt pathfinding implementations)

REFERNENCE
***
1. A Comprehensive Study on Pathfinding Techniques for Robotics and Video Games
    https://downloads.hindawi.com/journals/ijcgt/2015/736138.pdf

"Pathfinding is a fundamental component of many important applications in the fields of GPS, video games, robotics, logistics, and crowd simulation..."
"Generally.. two main steps: graph generation and a pathfinding algorithm."

![Relationships between topologies](../pictures/01.png)

Generation:
  Sekeltonization
    Defines graph G = (V,E)
    Where V is a set of coordinates in the environment and E is the edges connecting these in line of sight of one another. 
    Produces irregular grip, either a Visibility Graph or Waypoint Graph.
  Cell Decomposition
    Decomposes traversable space into cells, either a circle or convex polygon; a region of traversable space with no obstacles. 
    With no obstacles, agents can travel in a straight line within any given cell without path planning. 

Search Algorithm:
  A*, basis for modified and improved path finding algorithms. 
  Efficiency is a calculation of Execution Time, Memory Overhead, and whether the environment of the search is static, dynamic, or real-time "deterministic".

Grids:
  Regular (squares etc.) or irregular (mesh, visibility graph, waypoints).
   Square 2D grid: 
    Jump Point Search (single agent). Accelerated wuth generated subgoal graphs. 
    Exhaustive and Monte-Carlo Iterative Taxing Algorithms (multi agent) using priority system.

  Visibility Graphs: 
    S. K. Ghosh and P. P. Goswami, “Unsolved problems in visibility graphs of points, segments, and polygons,” ACM Computing Surveys, vol. 46, article 22, 2013

  **Mesh Navigation**: [45]
    ˇSiˇsl ́ak et al. [42] AA* algorithm enables flight-path-planning (single agent) and can concider nonzero-sized agents. 
    Kapadia et al. [46] for multi-agent.
    Harabor and Botea [47] HAA* algorith has low computational effort for low level searches but produces sub optimal paths for many problems.
    Chen et al. [48] transfering scene data into an abstract contour model for heuristic search. 
    Sturtevand and Geisberger [1] say contraction hierarchies and abstractions have simple overhead and perfomance and both are useful high-level planning approaches. 

"basic shortest-path principles in ... videogames are mature theories" "Researchers from all over the word are working to improve path-planning algorithms."

***
2. Smart Move: Intelligent Path-Finding
    https://www.gamasutra.com/view/feature/3317/smart_move_intelligent_.php?print=1

***
3. Pathfinding Algorithms in Game Development
    https://iopscience.iop.org/article/10.1088/1757-899X/769/1/012021/pdf

***
4. Pathfinding in Computer Games
    https://arrow.tudublin.ie/cgi/viewcontent.cgi?article=1063&context=itbj

***
5. Navigation Queries from Triangular Meshes
    https://www.researchgate.net/publication/225139496_Navigation_Queries_from_Triangular_Meshes
    Marcelo Kallmann

  "Local Clearance Triangulation" to check if a disk of arbitrary size can pass through any narrow passage of the mesh. 
  Using triangular cell decomposition to create triangulations means environment has O(n) cells, where n is the number of segments used to describe the obstacles in the environment. 
  This means that spatial processing algorithms depend on complexity and not size of the environment. Therefore better than uniform grids over large areas. 

  1. Static objects, the environment. Do not move over time, but can change from time to time (e.g. a door opening)
  2. Dynamic objects, continuously moving (e.g. other agents)

  Adjacency graphs from triangulations for path planning.
  Most popular approach for path finding in polygonal 

  **The Symedge Data Structure for Mesh Representation**
  Represents planar meshes while encoding adjacency relations. Here the quad-edge structure [9] integrating adjacency operators and attachment of information per element similar to half-edge structure [18]. 
  Obtained stucture is Symedge, an oriented edge and symmetrical to reflected edge. Each symedge adjacent to only one vertex, one edge, and one face. Keeps a pointer to the next symedge adjacent to the same face, and one to the next symedge adjacent to the smae vertex. 

***
6. Multi-Domain Real-Time Planning in Dynamic Environments
    https://dl.acm.org/doi/pdf/10.1145/2485895.2485909
    Mubbasir Kapadia, Alejandro Beacco, Francisco Garcia, Vivek Reddy, Nuria Pelechano, Narman I. Badler

***
7. Hierarchical Path Planning for Multi-Size Agents in Heterogeneous Environments
    https://ieeexplore.ieee.org/stamp/stamp.jsp?tp=&arnumber=5035648
    Danierl Harabor, Adi Botea; 2008

  Hierarchal path planning: Abstraction of search problem into many smaller problems. 

  Previous efforts do not solve for heterogeneous agents in heterogeneous environments.
  HPA* builds an abstract search graph from dividing the environment into square clusters connected by entrances. 
  PRA* builds a multi-level search-space by abstracting cliques of nodes, to narrow search to a window of nodes along the optimal path. 

  Robotics: force potentials. 
  Attracted to far goal, repulsed by obstacles as it nears. (e.g. Brushfire Algorithm [6])
  Annotates each tile on gridmap with distances to nearest obstacle.
  Gradient descent strategy.
  Can lead robot into local minimum, causing it to stop. (incompleteness)

  Nav Meshes: Triangulation A* and Triangulation Reduction A*. [3]
  Delaunay triangulation to create undirected graph connected by constrained and unconstrained edges (traversable & non-traversable). 
  Assumes homogeneous environment. 

7.1 Near Optimal Hierarchical Path-Finding
    http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.479.4675&rep=rep1&type=pdf
    Adi Botea, Martin Muller, 2004

  "Computational effort... increases with size of the search space"
  "Path finding on large maps can result in serious performance bottlenecks."
  Grid-based maps. oops. 
  Local level. Linked local clusters. Optimal crossings precomputed and cached. 
  Global level. Clusters traversed in one big step. 
  Hierarchies can extend to more levels. 
  Works in dynamically changing environement.
  10x faster than A* and within 1% of optimal afer a path-smoothing procedure.  

  A* returns complete path, HPA* returns complete path of subproblems, first subgraph can be calculated to give the first steps without having to calculate the whole thing, useful in games where units have to change course, so no effort is wasted on computing a path to a goal node that was not needed. 

  With dynamic path changes you just need to adapt the current local cluster, not the whole global graph. 

7.2 Partial Pathfinding Using Map Abstractioni and Refinement
    https://www.aaai.org/Papers/AAAI/2005/AAAI05-221.pdf
    Nathan Sturtevant, Michael Buro; 2005

  Partial-Refinement A* (PRA*).
  Spreads cost of path computation over execution time. 
  Gradual refinement from high-level plans about the world down to low-level actions as needed. 

  Unlike HPA* which overlays a structure on the search space, PRA* abstracts existing graphs based on 'clique' and 'orphan' patterns.
  Cliques are reduced to a single node in parent abstraction, and guarantee all nodes within can move to each other in a single step (except orphans).
  Orphans can only be reached by a single operator (line connecting two nodes).
  Orphans get included into their connected clique.

  Abstracted node position is average of all nodes it abstracts. 
  Distance between abstracted nodes is octile of their abstract location. 

7.3 Graph Abstraction in Real-Time Heuristic Search
    https://www.jair.org/index.php/jair/article/view/10510/25177
    Vadim Bulitko, Nathan Sturtevant, Jieshan Lu, Timothy Yau; 2007

  Large scale study on the impact of abstraction on a variety of pathfinding algorithms. 
  "Abstraction is found to improve efficiency by providing better trading offs between planning time, learning speed, and other negatively correlated performance measures."

  'Agent-Centred Real-Time Heuristic Search' (Koenig, 2001)
  Also, AI controlled characters don't always have access to the entire map to avoid unrealistic behaviour (Dini, van Lent, Carpenter, & Iyer, 2006)

  Path Refinement Learning Real-Time Search (PR LRTS). 
  Enhances existing realtime heuristic search algorithms with automatically-built graph abstraction. 
  Learning accellerated by learning heuristic function in abstract space. 
  Abstract space actions then refuned to  environment actions by A* algorithm .

7.4 Efficient Triangulation-Based Pathfinding
    https://skatgame.net/mburo/ps/thesis_demyen_2006.pdf
    Douglas Jon Demyen; 2006-7

  Delaunay triangulation of environment. 
  Triangulation A*, Triangulation Reduction A*. 
  Paths for circular nonzero radius agents. 

  Position & Orientation = Configuration

  Triangulation to represent environment, described in terms of Line Segment Barriers (polygonal representation). 
  'Constrained Triangulation'to identify dead-ends, corridors, decision points. 
  Resulting graph where nodes represent where a decision must be made. 

  New version of the 'funnel algorithm' to consider circular objects of non-zero radius by imagining circles around environment corners of object radius. (also in linear time like original)

  Heuristics for A* and similar algorithms can be found through abstract space, like grouping nodes & areas together.
  E.g. pattern databasesm [explained pg24] or Hierarchical A* (HA*)

  Visibility Graphs: connecting vertices of obstacles together that have line of sight. This graph is then used for searching. 
  However, only guaranteed for zero-size objects, can have edges quadratic to obstacle vertices, and is difficult to repair in a changing environment. 

  also unused Trapezoidal Decomposition [30, 29] as polygonal representation

  PRA* good, compromise search by doing it on middle abstraction layer. Also by going up abstraction layers, if two points end up on the same node it is guaranteed thay can form a path, making a quick check for that easier without having to do an exhaustive search. 

  Grid world representation, imprecision leading to suboptimal paths if obstacles and walls are not alligned with the grid, or if the grid doesn't have sufficient resolution. 
  Adding more resolution greatly increases execution time for pathfinding. 
  Also larger areas have more cells than small ones even if geometrically similar. 

  Constrained Triangulation, obstacle boarders are line segments, or constrained edges, with unconstrained edges linking them up without crossing until all triangles. 

  Dynamic Constrained Delaunay Triangulation. [41 for mroe geometric structures]
  Triangulates while trying to maximise the minimum interior angle of all triangles, to avoid sliver triangles. [1 for efficient computation method of delaunay triangulation]
  Dynamic also means that it can be repaired locally when changes are made. 

  Non-point objects: common to use Minkowski Sum operation. Adding the objects shape to every element in the environement. Pathfinding is then done as a point in this new environment. 
  However, separate representations of the map are needed for each sized object. Also with common sphere representations of objects it becomes hard to triangulate the curves, adding in a lot of extra geometry. 

  Instead calculate per triangle the largest sphere than can travel through it and use this for calculation. 


***
8. Fast Path Searching in Real-Time 3D Game
    https://ieeexplore.ieee.org/stamp/stamp.jsp?tp=&arnumber=5209169
    Siyuan Chen, Guangshun Shi, Yuan Liu
 

***
10. A Comparison of High-Level Approaches for Speeding Up Pathfinding
    https://www.cs.du.edu/~sturtevant/papers/highlevelpathfinding.pdf
    Nathan R. Sturtevant, Robert Geisberger; 2010


  
***
11. The Quake III Arena Bot
    http://www.kbs.twi.tudelft.nl/docs/MSc/2001/Waveren_Jean-Paul_van/thesis.pdf
    J.M.P van Waveren; 2001
  
  Commonly used - waypoint system
  Points connected by straight line paths. 
  Low memory cost. Hard to calculate whether points are reachable from a waypoint. 

***
12. Multi-Agent Pathfinding with Continuous Time

  Multi-agent pathfinding

  - Continuous-time Conflict-Based Search (CCBS) proposed, building on Safe Interval Path Planning (SIPP)