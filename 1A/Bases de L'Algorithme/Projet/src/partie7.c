#include "../include/table.h"
#include "../include/image.h"
#include <stdlib.h>
#include <stdio.h>





void kdtree_get_nearest_color(kdtree arbre ,color* color, color* color_data){
	if (arbre->tableau[arbre->axis]>color[arbre->axis]){
		if (arbre->left_son!=NULL && arbre->right_son!=NULL){
			kdtree_get_nearest_color(arbre->left_son,color* color,color* color_data);
		}else{
			color_data=arbre->left_son->tableau;
			return;
	}else{
		if (arbre->left_son!=NULL && arbre->right_son!=NULL){
			kdtree_get_nearest_color(arbre->right_son,color* color,color* color_data);
		}else{
			color_data=arbre->right_son->tableau;
			return;
			}
		}
	}
}	
