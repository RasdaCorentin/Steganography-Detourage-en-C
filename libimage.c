#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libimage.h"

ImP3 initImP3(int haut, int larg, int vmax) {
    ImP3 InitImP3;
    int i;
    InitImP3.hauteur = haut;
    InitImP3.largeur = larg;
    InitImP3.maxval = vmax;
    InitImP3.tpix = malloc(haut * sizeof(int *));
    for(i=0; i<haut; i++){
        InitImP3.tpix[i]= malloc(larg * sizeof(int));
    }
    return InitImP3;
}

ImP3 copieImP3(ImP3 im) {
    ImP3 newImP3;
    
    int i,j;
    newImP3 = initImP3(im.hauteur, im.largeur, im.maxval);
    for(i=0; i<newImP3.hauteur; i++){
        for(j=0; j<newImP3.largeur; j++){
        newImP3.tpix[i][j] = im.tpix[i][j];
    }}
    return newImP3;
}

//Manque "si le type de l’image contenu dans le fichier n’est pas P3"
//charge image est simplifiable TABD INUTILE cf: ICI
ImP3 chargeImP3(char* fichier){
    FILE* fsource = fopen(fichier, "r");
    int hauteur, largeur, vmax, tmax;
    PixelRGB** tabD;
    int i= 0, j = 0, k =0;
    char type[2];
    char lecture[255];
    int checkC = 0;

    ImP3 newImP3;
    if (fsource == NULL) {
        fscanf(stderr, "Erreur lors de l'ouverture du fichier");
        return newImP3;
    }

    fscanf(fsource, "%s", type);
    while((fscanf(fsource,"%s",lecture)) != EOF) {
        if (lecture[0] == '#'){
            fgets(lecture,sizeof(lecture), fsource);
        }
        else break;
    }
    
    hauteur = atoi(lecture);
    fscanf(fsource, "%s", lecture);
    largeur = atoi(lecture);
    fscanf(fsource, "%s", lecture);
    vmax= atoi(lecture);

    tabD = malloc(((hauteur*largeur)) * sizeof(PixelRGB));
    if (tabD == NULL) {
        fprintf(stderr,"Erreur d'allocation mémoire");
        fclose(fsource);
        return newImP3;
    } 

    newImP3 = initImP3(hauteur, largeur, vmax);

    newImP3.hauteur = hauteur;
    newImP3.largeur = largeur;
    newImP3.maxval = vmax;

    for(j=0; j<newImP3.hauteur; j++){
        for(k=0; k<newImP3.largeur; k++){
        fscanf(fsource, "%hhu %hhu %hhu", &newImP3.tpix[j][k].r, &newImP3.tpix[j][k].v, &newImP3.tpix[j][k].b);
    }}
    free(tabD);
    return newImP3;
}

void sauveImP3(char* nom, ImP3 im){
    int i, j;
    FILE * fdest = fopen(nom, "w"); // Ouverture du fichier destination en écriture et vérification
    if (fdest == NULL){
        fprintf(stderr, "\n%s : erreur à la création du fichier", nom);
        abort();
    }
    for(i=0; i<im.hauteur; i++){
        for(j=0; j<im.largeur; j++){
        fprintf(fdest, "%hhu\n%hhu\n%hhu\n", im.tpix[i][j].r, im.tpix[i][j].v, im.tpix[i][j].b);
    }
    
}
}

int main(){
    char* fichier = "./CCTP24/raki.ppm";
    char* nom = "./CCTP24/raki2.ppm";
    ImP3 oldImP3, newImP3; 
    oldImP3 = chargeImP3(fichier);
    sauveImP3(nom, oldImP3);
}