#ifndef __TABLE_HH__
#define __TABLE_HH__

#include "image.h"



typedef enum {red,green,blue} axis;
typedef int color; /* ou int*/
typedef enum {false,true} boolean;
typedef struct color_table *color_table;
typedef struct color_table_kd *color_table_kd;




int longueur_tab(color_table);
color tab_elements( color_table,int);
booleen owner_tab(color_table);

int longueur_tab_kd(color_table_kd);
color* tab_kd_elements( color_table_kd,int);
color** tab_kd_elements_all( color_table_kd);
booleen owner_tab_kd(color_table_kd);

color_table create_color_table(image);
int destroy_color_table(color_table);
color_table color_table_duplicate(color_table,int,int);

void color_table_get_color(color_table,int,color*);
int color_table_get_nb_color(color_table);
void color_table_sort(color_table,axis);

color_table_kd oned_to_kd(color_table);
color_table kd_to_oned(color_table_kd);

#endif
