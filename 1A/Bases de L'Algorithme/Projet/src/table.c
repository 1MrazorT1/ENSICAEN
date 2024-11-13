#include <stdio.h>
#include <time.h>

#include "../include/table.h"
#include "../include/image.h"

typedef struct color_table
{
	int longueur;
	booleen owner;
	color *element;
}*color_table;

struct color_table_kd
{
    booleen owner;
    int longueur;
    color* *element;
};

/* Uni-dimensional Color Table Items */

int longueur_tab(color_table tab){
	return tab->longueur;
}

color tab_elements(color_table tab, int index){
	return tab->element[index];
}

booleen owner_tab( color_table tab){
	return tab->owner ;
}




/* Tables Manipulation */

color_table create_color_table(image img){
    /* check if img is not NULL*/
    assert(img!=NULL);
    int i=0;
    /*initialize our color table */
    color *pixel=malloc(sizeof(int)*3);
    color_table tab=malloc(sizeof(struct color_table));
    tab->longueur=image_give_largeur(img);
    tab->element=malloc(sizeof(int)*tab->longueur*3);
    tab->owner=1;
    /* put the cursor at the beginning*/
    image_debut(img);
    for ( i=0 ; i<tab->longueur ; i++){

    	pixel=image_lire_pixel(img);           
	/*store image data by traversing pixel by pixel*/
	tab->element[i*3]=pixel[0];
    	tab->element[i*3+1]=pixel[1];
    	tab->element[i*3+2]=pixel[2];
        image_pixel_suivant(img);
    
    }
    return tab;
}



int destroy_color_table(color_table tab){
  assert( tab!=NULL);
	/* if owner equal 1 means that color table its not a copy from other color table*/
  if (tab->owner=1){
    free(tab->element);
  }
  free(tab);
  return 1;
}


color_table color_table_duplicate(color_table tab ,int offset,int longueur){
  /*check if tab is not NULL*/
  assert(tab!=NULL);
  int i;
  /* initializing a new color table where we are going to stocke some of colors table data*/ 
  color_table new=malloc(sizeof(color_table));
  new->longueur=longueur;
  new->element=malloc(sizeof(color)*longueur*3);
  new->owner=0;
  for (i=0 ; i<longueur*3;i++){
	  /* we stocke data frome offset until the size of our new color table*/ 
        new->element[i]=tab->element[i+offset];
  }
  return new;
}


void color_table_get_color(color_table tab , int indice , color* col){
	assert( col!=NULL);
	assert( tab!=NULL);
	assert(indice < tab->longueur);
		/* we give a table size of 3 integer than we stocke in there data of the index elements*/
	col[0] = tab->element[3*indice];
	col[1] = tab->element[3*indice+1];
	col[2] = tab->element[3*indice+2];
	

}

int color_table_get_nb_color(color_table tab){
  return tab->longueur;
  /* it return number of colors ( color its a table of 3 integer*/
}

void color_table_sort(color_table tab , axis cl){
  int longeur=color_table_get_nb_color(tab);
  int i,j;
  int index;
  color min;
  /* we sort by selection*/
  for(j=0;j<longeur;j++){
	  min=tab->element[3*j+cl];
	  index=j;
	  for (i =j+1 ; i < longeur ; i++){
		  /* from j ieme position we look for minimum integer*/
	       if(min>tab->element[3*i+cl]){
		        index=i;
     			min=tab->element[3*i+cl]; 
    		}
	  }
	  /* we change minimum color with the j ieme color*/
	  color *col=malloc(sizeof(color)*3);
	  color_table_get_color(tab,j,col);
	  tab->element[3*j]=tab->element[3*index];	  
	  tab->element[3*j+1]=tab->element[3*index+1];	  
	  tab->element[3*j+2]=tab->element[3*index+2];
	  tab->element[3*index]=col[0];	  
	  tab->element[3*index+1]=col[1];	  
	  tab->element[3*index+2]=col[2];
  }
}  

/* Transformation Of Tables From Uni-dimensional to Multi-Dimensional*/

color_table_kd oned_to_kd(color_table tab){
  color_table_kd kd_tab=malloc(sizeof(struct color_table_kd));
  kd_tab->owner=tab->owner;
  kd_tab->longueur=tab->longueur;
  kd_tab->element=malloc(kd_tab->longueur*sizeof(color*));
  int i;
  int s=0;
  for(i=0;i<kd_tab->longueur;i++){
    kd_tab->element[i]=malloc(3*sizeof(color));
    kd_tab->element[i][0]=tab->element[3*i+0];
    kd_tab->element[i][1]=tab->element[3*i+1];
    kd_tab->element[i][2]=tab->element[3*i+2];
  }
  return(kd_tab);
}

/* Transformation Of Tables From Multi-dimensional to Uni-Dimensional*/

color_table kd_to_oned(color_table_kd tab_kd){
  color_table tab=malloc(sizeof(struct color_table));
  tab->owner=tab_kd->owner;
  tab->longueur=tab_kd->longueur;
  tab->element=malloc(tab_kd->longueur*sizeof(color)*3);
  int i;
  int s=0;
  for(i=0;i<tab_kd->longueur;i++){
    tab->element[3*i+0]=tab_kd->element[i][0];
    tab->element[3*i+1]=tab_kd->element[i][1];
    tab->element[3*i+2]=tab_kd->element[i][2];
  }
  return(tab);
}

int destroy_color_table_kd(color_table_kd tab){
  assert( tab!=NULL);
	/* if owner equal 1 means that color table its not a copy from other color table*/
  if (tab->owner=1){
    free(tab->element);
  }
  free(tab);
  return 1;
}
