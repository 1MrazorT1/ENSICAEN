#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "../include/image.h"
#include "../include/table.h"
#include "time.h"




int main(int argc, char *argv[]){
    clock_t start = clock();
    // Declare two image structures
    image img1 , img2;
    
    // Create two images
    img1=FAIRE_image();
    img2=FAIRE_image();
    
    // Load images from the command line arguments
    image_charger(img1,argv[1]);
    image_charger(img2,argv[2]);
    
     // Create a color table based on the second image
    color_table tab;
    tab=create_color_table(img2);
    
    // Iterating through pixels of the first image
    double d1,d2;
    int i;
    color *couleur;
    color min[3];
    color *tmp=malloc(sizeof(color)*3);
    // Set the pointer to the beginning of the image
    image_debut(img1);
    
    do {
    	// Read the color of the current pixel in the first image
    	couleur=image_lire_pixel(img1);
    	
    	// Get the first color from the color table
    	color_table_get_color(tab,0,min);
    	//the Euclidean distance between two colors
    	d1=sqrt(pow(min[0]-couleur[0],2)+pow(min[1]-couleur[1],2)+pow(min[2]-couleur[2],2));
    	
    	
    	 // Iterate through the color table to find the closest color
    	for (i=1 ; i<color_table_get_nb_color(tab) ; i++){
    		color_table_get_color(tab,i,tmp);
    		d2=sqrt(pow(tmp[0]-couleur[0],2)+pow(tmp[1]-couleur[1],2)+pow(tmp[2]-couleur[2],2));
    		if (d1>d2){
    			d1=d2;
    			min[0]=tmp[0];
    			min[1]=tmp[1];
    			min[2]=tmp[2];
    		}
    	}
    	
    	
    	// Write the closest color to the current pixel in the first image
    	image_ecrire_pixel(img1,min);
    }while(image_pixel_suivant(img1));
    // Save the modified image to a new file
    clock_t end = clock();
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Le programme a pris %f secondes pour s'exécuter.\n", cpu_time_used);
    image_sauvegarder(img1,"test_partie5.ppm");
    return 0;
}
