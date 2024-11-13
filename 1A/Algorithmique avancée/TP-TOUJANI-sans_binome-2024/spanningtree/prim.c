/**
 * @file graph.c
 *
 * @brief This file implements a graph data structure using a table of lists.
 */

#include <stdlib.h>
#include <stdio.h>
#include "../graph/graph.h"
#include "../heap/heap.h"

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
void Prim(Graph g, int s){
   Heap* F = createHeap(g->numberVertices);
   F = g->array;
   for(int i = 0; i < g->numberVertices; i++){
      modifyPriorityHeap(F, F->heap[i], 9999);
   }
   modifyPriorityHeap(F, F->heap[s], 0);
   préd
   while(F != NULL){
      int u_min = removeElement(F);
      List L = g->array[u_min];
      L=L->nextCell;
      Boolean L_appart_F = false;
      i = 0;
      while((L_appart_F != true) || (i < F->nbElements)){
         if(F->heap[i] == L->value){
            L_appart_F = true;
         }
         i++;
      }
      while(L != NULL){
         int x1 = g->xCoordinates[u_min];
         int y1 = g->yCoordinates[u_min];
         int x2 = g->xCoordinates[L->value];
         int y2 = g->yCoordinates[L->value];
         if(L_appart_F && (distance(x1, y1, x2, y2) < F->priority[L->value])){
            préd
            modifyPriorityHeap(F, F->heap[L->value], distance(x1, y1, x2, y2));
         }
      }
   }
}