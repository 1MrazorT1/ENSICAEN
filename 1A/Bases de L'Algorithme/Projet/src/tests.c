#include <stdio.h>
#include <stdlib.h>
#include "../include/KDTree.h"

#include <stdio.h>
#include <stdlib.h>
#include "../include/KDTree.h"  // Assuming this is the header where KD tree functions are declared

int main(int argc, char *argv[]) {
    color_table tab;
    image img;
    kdtree tree;

    img = FAIRE_image();
    image_charger(img, argv[1]);

    tab = create_color_table(img);

    tree=create_kdtree(tab,30);
    printf("arbre cree !\n");

    //representer_arbre(tree);
    color couleur[]={111,212,8};
    color color_data[3];
    kdtree_get_nearest_color(tree ,couleur , color_data );
    printf("la couleur plus prooche: %d %d %d\n",color_data[0],color_data[1],color_data[2]);

   // destroy_kdtree(tree);
   // printf("arbre detruite !\n");

    /*kdtree arbre = create_kdtree(tab, 10);
    printf("Arbre cree !\n");

    representer_arbre(arbre);

    destroy_kdtree(arbre);

    return 0;*/
}


/*int main(int argc, char *argv[]){
    color_table tab;
    image img;
    img=FAIRE_image();
    image_charger(img,argv[1]);
    tab=create_color_table(img);
    kdtree arbre;
    arbre=create_kdtree(tab,10);
    printf("arbre cree !");
    representer_arbre(arbre);
    destroy_kdtree(arbre);
    return(0);
}*/

/*int main(int argc, char *argv[]){
    color_table new_tab,tab;
    color_table_kd kd_tab;
    image img;
    img=FAIRE_image();
    image_charger(img,argv[1]);
    tab=create_color_table(img);
    kd_tab=oned_to_kd(tab);
    int i,j;
    for (i=0;i<longueur_tab(tab);i++) {
		printf("%d %d %d\n",tab_elements(tab,3*i),tab_elements(tab,3*i+1),tab_elements(tab,3*i+2));
	}
    printf("\n");
    for(i=0;i<longueur_tab_kd(kd_tab);i++){
        printf("%d %d %d \n",tab_kd_elements(kd_tab,i)[0],tab_kd_elements(kd_tab,i)[1],tab_kd_elements(kd_tab,i)[2]);
    }
    printf("\n");
    new_tab=kd_to_oned(kd_tab);
    for(i=0;i<longueur_tab(new_tab);i++){
        printf("%d %d %d\n",new_tab->element[3*i],new_tab->element[3*i+1],new_tab->element[3*i+2]);
    }
    printf("\n");
}*/

/*int main (int argc , char *argv[]){
	image img;
	img=FAIRE_image();
	image_charger(img,argv[1]);
	color_table tab=create_color_table(img);
	int i;
	color *cl=malloc(3*sizeof(color));
	color_table_get_color(tab,2,cl);
	printf("%d %d %d \n",cl[0],cl[1],cl[2]);
	printf("----------------------\n");
	color_table_sort(tab,2);
	for (i=0;i<longueur_tab(tab);i+=3) {
		printf("%d %d %d\n",tab_elements(tab,i),tab_elements(tab,i+1),tab_elements(tab,i+2));
	}
	return 0;
}*/
