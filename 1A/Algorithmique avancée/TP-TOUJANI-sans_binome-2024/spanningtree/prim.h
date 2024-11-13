/**
 * @file prim.h
 *
 * @brief This file defines the Prim function for Minimal Spanning Tree.
 */

#ifndef PRIM_H
#define PRIM_H

#include <stdlib.h>
#include <stdio.h>
#include "../graph/graph.h"

/**
 * @brief Function that computes a minimum spanning tree of graph g of the connex component of the vertex s
 *
 * @param graph The graph
 * @param s Index of the initial vertex of the Prim procedure.
 *
 * The array parents is updated so that it contains the spanning tree
 * computed by the Prim algorithm.
 * Note that the array parents must be initialized before calling the function.
 */
 void Prim(Graph g, int s);




#endif  // PRIM_H
