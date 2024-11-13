#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "../include/image.h"
#include "../include/table.h"
#include "../include/KDTree.h"
#include "time.h"

int main(int argc, char *argv[]){
    int i,j,k,h,l,d,s,c;
    clock_t start = clock();
   
   
    /* Data Initialization */
    color_table tab,tab_donnee;
    color_table_kd tab_kd,tab_donnee_kd;
    image img,img_inter,img2;

    /* Loading the image */
    img=FAIRE_image();
    img2=FAIRE_image();
    image_charger(img,argv[1]);
    img2=img;

    /* Loading the KDTree from the given color array */
    kdtree tree;
    img_inter=FAIRE_image();
    image_charger(img_inter,argv[2]);
    tab_donnee=create_color_table(img_inter);
    tree=create_kdtree(tab_donnee,10);

    /* Calculation of Dimension of the Given Image */
    h=image_give_hauteur(img);
    l=image_give_largeur(img);
    d=image_give_dim(img);

    /* Creation Of The New Image */
    image_debut(img);
    image_debut(img2);
    for(k=0;k<d;k++){
        for(i=0;i<l;i++){
            for(j=0;j<h;j++){
                int *couleur=image_lire_pixel(img);
                int min[3];
                kdtree_get_nearest_color(tree,couleur,min);
                image_ecrire_pixel(img2,min);
                image_pixel_suivant(img);
                image_pixel_suivant(img2);
            }
        }
    }
    // time execution calculating
    clock_t end = clock();
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Le programme a pris %f secondes pour s'exécuter.\n", cpu_time_used);
  
    image_sauvegarder(img2,"test.ppm");
   // image_to_stream(img2,stdout);
}
