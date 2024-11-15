#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libimage.h"

//#########################################################################################################
//#######################################         IMP2         ############################################
//#########################################################################################################
ImP2 initImP2(int haut, int larg, int vmax) {
    ImP2 InitImP2;
    int i;
    InitImP2.hauteur = haut;
    InitImP2.largeur = larg;
    InitImP2.maxval = vmax;
    InitImP2.tpix = malloc(haut * sizeof(unsigned char *));
    for(i = 0; i<InitImP2.hauteur; i++){
        InitImP2.tpix[i] = malloc(larg * sizeof(unsigned char));
    }
    return InitImP2;
}

ImP2 copieImP2(ImP2 im) {
    ImP2 newImP2;
    
    int i,j;
    newImP2 = initImP2(im.hauteur, im.largeur, im.maxval);
    for(i=0; i<newImP2.hauteur*newImP2.largeur; i++){
        newImP2.tpix[i][j] = im.tpix[i][j];
    }
    return newImP2;
}

ImP2 chargeImP2(char* fichier){

    FILE* fsource = fopen(fichier, "r");
    int hauteur, largeur, vmax, tmax;
    int i= 0, j = 0, k =0;
    char type[3];
    char lecture[255];

    ImP2 newImP2;
    if (fsource == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier. %s introuvable", fichier);
        return newImP2;
    }

    fscanf(fsource, "%s", type);
    if (strcmp(type, "P2") != 0) {
        fprintf(stderr, "Erreur de typage \"%s\" incompatible.", type);
        return newImP2;
    }

    //Cette boucle permet de vérifie rsi le debut de la ligne est un "#"
    //On ne la traite pas et utilise fgets pour passer à la prochaine ligne
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
    vmax = atoi(lecture);

    newImP2 = initImP2(hauteur, largeur, vmax);

    newImP2.hauteur = hauteur;
    newImP2.largeur = largeur;
    newImP2.maxval = vmax;

    for(j=0; j<newImP2.hauteur; j++){
        for(k=0; k<newImP2.largeur; k++){
        fscanf(fsource, "%hhu", &newImP2.tpix[j][k]);
    }}
    return newImP2;
}
void sauveImP2(char* nom, ImP2 im){
    int i, j;
    FILE * fdest = fopen(nom, "w"); // Ouverture du fichier destination en écriture et vérification
    if (fdest == NULL){
        fprintf(stderr, "\n%s : erreur à la creation du fichier", nom);
        abort();
    }

    //Mettre Type
    fprintf(fdest, "P2\n");
    //Mettre Commentaire 
    fprintf(fdest, "#RASDA_RAZAFITSALAMA ANDRIAMAHENINA_43004877_36000793\n");
    //Mettre  Mettre Hauteur Largeur
    fprintf(fdest, "%d %d\n", im.hauteur, im.largeur);
    //Mettre Vmax
    fprintf(fdest, "%d\n", im.maxval);

    for(i=0; i<im.hauteur; i++){
        for(j=0; j<im.largeur; j++){
        fprintf(fdest, "%hhu\n", im.tpix[i][j]);
    }
    }
}
//#########################################################################################################
//#######################################         IMP3         ############################################
//#########################################################################################################
ImP3 initImP3(int haut, int larg, int vmax) {
    ImP3 InitImP3;
    int i;
    InitImP3.hauteur = haut;
    InitImP3.largeur = larg;
    InitImP3.maxval = vmax;
    InitImP3.tpix = malloc(haut * sizeof(PixelRGB *));
    for(i=0; i<haut; i++){
        InitImP3.tpix[i]= malloc(larg * sizeof(PixelRGB));
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
ImP3 chargeImP3(char* fichier){

    FILE* fsource = fopen(fichier, "r");
    int hauteur, largeur, vmax, tmax;
    int i= 0, j = 0, k =0;
    char type[3];
    char lecture[255];

    ImP3 newImP3;
    if (fsource == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier. %s introuvable", fichier);
        return newImP3;
    }

    fscanf(fsource, "%s", type);
    if (strcmp(type, "P3") != 0) {
        fprintf(stderr, "Erreur de typage \"%s\" incompatible.", type);
        return newImP3;
    }

    //Cette boucle permet de vérifie rsi le debut de la ligne est un "#"
    //On ne la traite pas et utilise fgets pour passer à la prochaine ligne
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
    vmax = atoi(lecture);

    newImP3 = initImP3(hauteur, largeur, vmax);

    newImP3.hauteur = hauteur;
    newImP3.largeur = largeur;
    newImP3.maxval = vmax;

    for(j=0; j<newImP3.hauteur; j++){
        for(k=0; k<newImP3.largeur; k++){
        fscanf(fsource, "%hhu %hhu %hhu", &newImP3.tpix[j][k].r, &newImP3.tpix[j][k].v, &newImP3.tpix[j][k].b);
    }}
    return newImP3;
}

void sauveImP3(char* nom, ImP3 im){
    int i, j;
    FILE * fdest = fopen(nom, "w"); // Ouverture du fichier destination en écriture et vérification
    if (fdest == NULL){
        fprintf(stderr, "\n%s : erreur à la creation du fichier", nom);
        abort();
    }

    //Mettre Type
    fprintf(fdest, "P3\n");
    //Mettre Commentaire 
    fprintf(fdest, "#RASDA_RAZAFITSALAMA ANDRIAMAHENINA_43004877_36000793\n");
    //Mettre  Mettre Hauteur Largeur
    fprintf(fdest, "%d %d\n", im.hauteur, im.largeur);
    //Mettre Vmax
    fprintf(fdest, "%d\n", im.maxval);

    for(i=0; i<im.hauteur; i++){
        for(j=0; j<im.largeur; j++){
        fprintf(fdest, "%hhu\n%hhu\n%hhu\n", im.tpix[i][j].r, im.tpix[i][j].v, im.tpix[i][j].b);
    }
}

}

int main(){
    char* fichier = "./CCTP24/chaises.pgm";
    char* nom = "./CCTP24/chaises2.pgm";
    ImP2 oldImP2, newImP2; 
    oldImP2 = chargeImP2(fichier);
    sauveImP2(nom, oldImP2);
}