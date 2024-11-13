/**
 * @file graph.h
 *
 * @brief This file defines a graph data structure using a table of lists.
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>
#include <stdio.h>
#include "../list/list.h"




/**
 * @brief This struct represents the graph using an array of adjacency lists.
 *
 */
typedef struct Graph {
    int numberVertices;   /** The number of vertices in the graph. */
    List *array;     /** Array of adjacency lists. A null pointer means an empty list*/

    double *xCoordinates;  /** array of the x coordinates of the points of each vertex */
    double *yCoordinates;  /** array of the y coordinates of the points of each vertex */
    double sigma; /** maximal distance between two neighboring vertices */

    int *parents; /** array to store the parent of each node for the covering tree. */


    int *topological_ordering; /** array to store a topological orderingof the graph. */
    double *earliest_start; /** array to store the earliest start of each node. */
    double *latest_start; /** array to store the latest start of each node. */

} Graph;


/**
 * @brief Computes the Euclidean distance between two points.
 *
 * @param x1 x coordinate of the first point
 * @param y1 y coordinate of the first point.
 * @param x2 x coordinate of the second point.
 * @param y2 y coordinate of the second point.
 * @return The Euclidean distance between the input points
 */
double distance(double x1, double y1, double x2, double y2);

/**
 * @brief Function to add an oriented edge in a graph.
 *
 * @param origin Origin vertex  of the edge.
 * @param destination Destination vrtex of the edge.
 * @param graph The graph in which the edge is added.
 *
 * Only the array of adjacency lists is updated.
 */
void addEdgeInGraph(Graph graph, int origin, int destination);


/**
 * @brief Function to create a random graph with a specified number of vertices and parameter sigma.
 *
 * @param numVertices The number of vertices in the graph.
 * @param sigma Parameter of the procedure to generate a random graph.
 * @param directedt The graph is undirected if directed==0, directed otherwise
 *
 * @return A pointer to the new graph.
 *
 * The elements of the array parents are set to -1.
 * The array of adjacency lists must be updated.
 */
Graph createGraph(int directed, int numVertices, double sigma);


/**
 * @brief Function to print the graph in the console.
 *
 * @param graph The graph to print.
 */
void printConsoleGraph(Graph graph);


/**
 * @brief Function to draw the graph in a svg file.
 *
 * @param graph The graph to print.
 * @param filename Name of the svg file.
 * @param type if 0, draws only the graph, if 1 draws the covering tree, if 2 draws both graph and spanning tree, if 3 draws the graph with topological order and dates
 * @param directed If directed==0, the graph is undirected and lines are drawn. Otherwise, arrows are drawn.
 */

void drawGraph(Graph graph, char* filename, int type, int directed);

/**
 * @brief Function that performs a depth first search from a vertex.
 *
 * @param graph The graph on which the depth first search is done.
 * @param vertex The origin of depth first search.
 *
 * The array parents is updated so that it contains the covering tree
 * computed by the depth first search.
 * Note that the array parents is not initialized in the function and
 * must be initialized before calling the function.
 */
void graphDFS(Graph graph, int vertex);

/**
 * @brief Function that performs a breadth first search from a vertex.
 *
 * @param graph The graph on which the breadth first search is done.
 * @param vertex The origin of breadth first search.
 *
 * The array parents is updated so that it contains the covering tree
 * computed by the breadth first search.
 * Note that the array parents is not initialized in the function and
 * must be initialized before calling the function.
 */
void graphBFS(Graph graph, int vertex);


/**
 * @brief Function that counts te number of connex components in a graph and that computes a covering forest (one tree by components)
 *
 * @param graph The graph
 *
 * The array parents is updated so that it contains the covering tree
 * computed by the breadth first search.
 * Note that the array parents is initialized in the function.
 */
int numberOfComponents(Graph graph);

#endif  // GRAPH_H
