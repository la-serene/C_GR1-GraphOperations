# C_GR1-GraphOperations

Graph Implementation in C using Adjacency List. This program can perform DFS, BFS and check if a given set is vertex
cover of the graph.

## Getting started
There are two ways to import data to graph: importing from raw file and importing from structured data file. Using raw
file acquires more time for graph to fully ingest the whole data.

## Dataset
The dataset is downloaded from [SNAP Graph Library](http://snap.stanford.edu/data/index.html), which are roadNet-CA, roadNetPA
and roadNet-TX undirected graph dataset. Each may contain up to nearly 2M vertices and 5M edges.

Due to the size of the dataset, Adjacency List is chosen to represent graph in C.

## Vertex Cover Test
Due to privacy concern, test set is not made public. An example of test set could be found in the testset folder in root 
folder.

Here are the table demonstrating the result of the vertex cover test on CA, PA and TX dataset respectively:

| Test set | Is Vertex Cover? |
|----------|------------------|
| CA       | Yes              |
| PA       | Yes              |
| TX       | Yes              |
