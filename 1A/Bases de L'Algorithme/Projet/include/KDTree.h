#ifndef __KDTREE_HH__
#define __KDTREE_HH__

#include "table.h"

typedef struct kdtree *kdtree;

kdtree create_kdtree(color_table,int);
void destroy_kdtree(kdtree);

void representer_arbre(kdtree);


double distance(int *couleur1,int *couleur2);
void nearest_color_table(color_table , color*, color*);
void kdtree_get_nearest_color(kdtree ,color* , color* );


#endif
