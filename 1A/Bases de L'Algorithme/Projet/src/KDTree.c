#include <stdio.h>
#include <math.h>
#include "../include/KDTree.h"
#include "../include/table.h"
#include "../include/image.h"

typedef struct kdtree{
    color_table tableau;
    struct kdtree *left_son;
    struct kdtree *right_son;
    axis axe;
    float plan;
};

axis choisir_axe(color_table tab){
    int taille_tableau,i;
    taille_tableau=longueur_tab(tab);
    /*mu_x correspond a la moyenne du tableau x et x correspond a l'ecart type du tableau x*/
    float mu_r,mu_g,mu_b,r,g,b;
    /*initialisation*/
    mu_r=0;
    mu_b=0;
    mu_g=0;
    r=0;
    b=0;
    g=0;
    /*calcul de la moyenne de chaque tableau*/
    for(i=0;i<taille_tableau;i++){
        mu_r=mu_r+tab_elements(tab,3*i);
        mu_g=mu_g+tab_elements(tab,3*i+1);
        mu_b=mu_b+tab_elements(tab,3*i+2);
    }
    mu_r=mu_r/(float)taille_tableau;
    mu_g=mu_g/(float)taille_tableau;
    mu_b=mu_b/(float)taille_tableau;
    /*calcul de l'ecart type*/
    for(i=0;i<taille_tableau;i++){
        r=r+pow((tab_elements(tab,3*i)-mu_r),2);
        g=g+pow((tab_elements(tab,3*i+1)-mu_g),2);
        b=b+pow((tab_elements(tab,3*i+2)-mu_b),2);
    }
    r=1/(float)taille_tableau*r;
    g=1/(float)taille_tableau*g;
    r=sqrt(r);
    b=sqrt(b);
    g=sqrt(g);
    /*choix de l'axe suivant la plus grande valeur*/
    if(r>=b){
        if(r>=g){
            return 0;
        }else{
            return 1;
        }
    }else{
        if(b>=g){
            return 2;
        }else{
            return 1;
        }
    }
}

float calcul_plan_coupe(color_table tab,axis axe){
    int taille_tableau,i;
    float s=0;
    taille_tableau=longueur_tab(tab);
    /*for(i=0;i<taille_tableau;i++){
        s=s+tab_elements(tab,3*i+axe);
    }
    s=s/(float)taille_tableau;
    i=0;
    while(tab_elements(tab,3*i+axe)<s){
        i=i+1;
    }*/
    int couleur1;
    int couleur2;
    
    if (taille_tableau % 2==0){
    	i=(int)taille_tableau;
    	couleur1=tab_elements(tab,(i/2)-1+axe);
    	couleur2=tab_elements(tab,(i/2)+1+axe);
    	return (couleur1+couleur2)/2;
    }else{
    	return tab_elements(tab,(i-1)/2+axe);
    }
}

kdtree create_kdtree(color_table tab, int n) {
    int taille_tableau;
    color_table avant, apres;

    kdtree tree = malloc(sizeof(struct kdtree));
    tree->tableau=malloc(sizeof(int)*longueur_tab(tab));

    if (tree == NULL) {
        // Handle memory allocation failure
        fprintf(stderr, "Memory allocation for kdtree failed\n");
        exit(EXIT_FAILURE);
    }

    tree->tableau = tab;
    tree->axe = choisir_axe(tab);

    color_table_sort(tab, tree->axe);

    tree->plan = calcul_plan_coupe(tab, tree->axe);

    avant = malloc(longueur_tab(tab)/2 * sizeof(int));
    apres = malloc((longueur_tab(tab) - longueur_tab(tab)/2 + 1) * sizeof(int));

    if (avant == NULL || apres == NULL) {
        // Handle memory allocation failure
        free(tree);
        exit(EXIT_FAILURE);
    }

    if (longueur_tab(tab) < n) {
        tree->left_son = NULL;
        tree->right_son = NULL;
	return tree;
    } else {
        avant = color_table_duplicate(tab, 0, longueur_tab(tab)/2);

        apres = color_table_duplicate(tab,longueur_tab(tab)/2, longueur_tab(tab)/2);
        tree->left_son = create_kdtree(avant, n);
        tree->right_son = create_kdtree(apres, n);
	return tree;
    }

}

void destroy_kdtree(kdtree tree) {
    
    if (tree == NULL) {
        return;
    }

    destroy_kdtree(tree->left_son);
    destroy_kdtree(tree->right_son);

    if (tree->tableau != NULL) {
        destroy_color_table(tree->tableau);
    }
    tree=NULL;
    free(tree);
}

void representer_arbre(kdtree arbre) {
    int i;
    if (arbre==NULL){
	    return;
    }
    printf("%d\n",longueur_tab(arbre->tableau));
    
    for (i=0;i<longueur_tab(arbre->tableau);i++) {
			printf("%d %d %d\n",tab_elements(arbre->tableau,3*i),tab_elements(arbre->tableau,3*i+1),tab_elements(arbre->tableau,3*i+2));
	}
    printf("-------------------------------\n");
	
    representer_arbre(arbre->left_son);
    
    representer_arbre(arbre->right_son);
    
}

double distance(int *tmp,int *couleur){
    
    return(sqrt(pow(tmp[0]-couleur[0],2)+pow(tmp[1]-couleur[1],2)+pow(tmp[2]-couleur[2],2)));
}

void nearest_color_table(color_table tab , color * couleur , color* data_couleur){
	int i;
	double d1,d2;
	int min=0;
	color cl[3]={tab_elements(tab,0),tab_elements(tab,1),tab_elements(tab,2)};
	d1=distance(couleur,cl);

	for ( i=1 ; i<longueur_tab(tab); i+=3){
		color cl_i[3]={tab_elements(tab,3*i),tab_elements(tab,3*i+1),tab_elements(tab,3*i+2)};
		d2=distance(couleur,cl_i) ;
		if (d2<d1){
			min=i;
			d1=d2;
		}
	
	}
	data_couleur[0]=tab_elements(tab,3*min+0);
	data_couleur[1]=tab_elements(tab,3*min+1);
	data_couleur[2]=tab_elements(tab,3*min+2);
}


void kdtree_get_nearest_color(kdtree arbre ,color* couleur, color* color_data){
	kdtree son_voisin=malloc(sizeof(kdtree));
	if (arbre->left_son==NULL && arbre->right_son==NULL){
		nearest_color_table( arbre->tableau, couleur, color_data);
		return;
	}
	if (arbre->plan > couleur[arbre->axe]){
		son_voisin=arbre->right_son;
		kdtree_get_nearest_color(arbre->left_son,couleur,color_data);
	}else{
		son_voisin=arbre->left_son;
		kdtree_get_nearest_color(arbre->right_son,couleur,color_data);	
	}
	double d;
	color plan[3]={tab_elements(arbre->tableau,3*arbre->plan),tab_elements(arbre->tableau,3*arbre->plan+1),tab_elements(arbre->tableau,3*arbre->plan+2)};
	d=sqrt(pow(plan[0]-couleur[0],2)+pow(plan[1]-couleur[1],2)+pow(plan[2]-couleur[2],2));
	if (d<sqrt(pow(color_data[0]-couleur[0],2)+pow(color_data[1]-couleur[1],2)+pow(color_data[2]-couleur[2],2))){
		nearest_color_table(son_voisin->tableau ,couleur,color_data);
		return;
		
	}		
}		
	
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
