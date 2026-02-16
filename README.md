# Urban Route Planning Tool

Implementation of an urban route planning system similar to a simplified GPS application. The system models a city map as a weighted graph, where nodes represent locations and edges represent street segments with different travel times for driving and walking.
The main objective was to design and implement efficient shortest-path solutions under different constraints, applying algorithmic techniques- dijsktra- studied in class.

## Key features
- Fastest route computation (driving only) using shortest-path algorithms
- Alternative independent route generation, ensuring no shared intermediate nodes or edges
- Restricted routing, allowing exclusion of specific nodes or road segments
- Environmentally-friendly routing, combining driving and walking with parking constraints
- Approximate solutions when strict constraints could not be satisfied
