#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "../include/image.h"
#include "../include/table.h"



int main(int argc, char *argv[]){
    int i,j,s;

    /* Data Initialization */
    color_table tab_donnee1;
    
    image img,img2;

    /* Loading the image */
    img=FAIRE_image();
    img2=FAIRE_image();
    image_charger(img,argv[1]);
    
    double d1,d2;
    /* Loading the given color array */
 
    image_charger(img2,argv[2]);
    //tab_donnee=malloc(sizeof(struct color_table));
    tab_donnee1=create_color_table(img2);
    
    

    /* Calculation of Dimension of the Given Image */
    
    /* Creation Of The New Image */
    image_debut(img);
    
         
    
    do {
    		int *couleur=image_lire_pixel(img);
    		int min[3];
   		min[0]=tab_elements(tab_donnee1,0);
    		min[1]=tab_elements(tab_donnee1,1);
    		min[2]=tab_elements(tab_donnee1,2);
    		d1=distance(min,couleur);
    		int tmp[3];
        	for(s=1;s < longueur_tab(tab_donnee1);s++){
          		
          		
    	  		tmp[0]=tab_elements(tab_donnee1,3*s+0);
    	  		tmp[1]=tab_elements(tab_donnee1,3*s+1);
    	  		tmp[2]=tab_elements(tab_donnee1,3*s+2);
    	  		
    	  	
    	  		d2=distance(tmp,couleur);
          		if(d1>d2){
                        	min[0]=tmp[0];
                        	min[1]=tmp[1];
                        	min[2]=tmp[2];
                        	d1=d2;
                        	
          		}
          	
		}             
       		image_ecrire_pixel(img,min);
       		
    }while(image_pixel_suivant(img));	
        
    
    
    image_sauvegarder(img,"teste_partie5.ppm");
    //image_to_stream(img,stdout);
}
