#include "ctype.h"
#include "libimage.h"


// ***************************************************************
// initImP3 : effectue l'allocation mémoire nécessaire pour une image de haut x larg pixels 
// et dont l'intensité maximal pour les pixels est vmax

// retourne une structure ImP3 et effectue l'allocation dynamique du tableau de pixels
ImP3 initImP3(int haut, int larg, int vmax){
    ImP3 im;
    im.hauteur = haut;
    im.largeur = larg;
    im.maxval = vmax;
    
    // Allocation dynamique du tableau de pixels
    im.tpix = malloc(haut * sizeof(PixelRGB *));
    for(int i=0; i<haut; i++){
        im.tpix[i]= malloc(larg * sizeof(PixelRGB));
    }
    return im;
}



// ***************************************************************
// copieImageP3 : retourne une copie de l'image donnée en paramètre

ImP3 copieImP3(const ImP3 im){
    
    ImP3 copie = initImP3(im.hauteur, im.largeur, im.maxval);
    
    for(int i=0; i<im.hauteur; i++){
        for(int j=0; j<im.largeur;j++)
            copie.tpix[i][j] = im.tpix[i][j];
    }
    
    return copie;
    
}



// ***************************************************************
// initImP2 : effectue l'allocation mémoire nécessaire pour une image en niveau de gris de haut x larg pixels
// le type et la valeur maximale ne sont initialiséa à 0 par défaut

// retourne une structure ImP2 et effectue l'allocation dynamique du tableau de pixels
ImP2 initImP2(int haut, int larg, int vmax){
    ImP2 im;
    im.hauteur = haut;
    im.largeur = larg;
    im.maxval = vmax;

    im.tpix = malloc(haut * sizeof(unsigned char *));
    for(int i=0; i<haut; i++){
        im.tpix[i]= malloc(larg * sizeof(unsigned char));
    }
    return im;
}



// ***************************************************************
// copieImageP2 : retourne une copie de l'image en niveau de gris donnée en paramètre

ImP2 copieImP2(const ImP2 im){
    
    ImP2 copie = initImP2(im.hauteur, im.largeur, im.maxval);
    
    for(int i=0; i<im.hauteur; i++){
        for(int j=0; j<im.largeur;j++)
            copie.tpix[i][j] = im.tpix[i][j];
    }
    
    return copie;
    
}


// --------------------------------------------------------------
// Fonctions annexe pour faciliter la lecture du fichier image

// Une fonction equivalente à gets mais pour la lecture d'une ligne dans un fichier
// jusqu'au \n et qui remplace le \n par \0
// Lu doit être suffisamment grand !
void litligne(FILE* fich, char*lu){
    int i=0;
    char c;
    while ((c = fgetc(fich)) != '\n' && c != EOF){
        lu[i] = c;
        i++;
    }
    lu[i]='\0';
}

// Une fonction qui se place dans le fichier au debut de la ligne suivante
void ligneSuivante(FILE* fich){
    char c;
    while ((c = fgetc(fich)) != '\n' && c != EOF);
}




// ***************************************************************
// chargeImP3 : charge dans une structure de type ImP3
// l'image contenue dans le fichier donnée en paramètre
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
    
    largeur = atoi(lecture);
    fscanf(fsource, "%s", lecture);
    hauteur = atoi(lecture);
    fscanf(fsource, "%s", lecture);
    vmax = atoi(lecture);

    newImP3 = initImP3(hauteur, largeur, vmax);

    for(j=0; j<newImP3.hauteur; j++){
        for(k=0; k<newImP3.largeur; k++){
        fscanf(fsource, "%hhu %hhu %hhu", &newImP3.tpix[j][k].r, &newImP3.tpix[j][k].v, &newImP3.tpix[j][k].b);
    }}
    return newImP3;
}

// ***************************************************************
// sauveImP3 :  créer le fichier image pnm  a partir
// de la structure tImage donnée

void sauveImP3(char* nom, const ImP3 im){
    FILE* flot;
    PixelRGB unPix;
    // Ouverture du fichier
    if( (flot = fopen(nom, "w")) == NULL){
        fprintf(stderr, "\nErreur dans sauvePnm : impossible de creer le fichier %s", nom);
        return;
    }
    // On ecrit d'abord le type de l'image
    fprintf(flot, "P3\n");
    
    // On ecrit une ligne de commentaire pour indiquer le createur
    fprintf(flot, "# CREATOR : devoir de langage C\n");
    
    // On ecrit les dimensions de l'image
    fprintf(flot, "%d %d\n", im.largeur, im.hauteur);
    
    // Puis la valeur maxi des pixels
    fprintf(flot, "%d\n", im.maxval);
    
    // Enfin on ecrit tous les pixels
    // Attention les niveaux de couleur sont des unsigned char qu'il faut écrire 
    // dans le fichier sous la forme d'entiers!
    for(int i=0; i<im.hauteur; i++){
        for(int j=0; j<im.largeur; j++){
            unPix = im.tpix[i][j];
            fprintf(flot, "%d\n", unPix.r);
            fprintf(flot, "%d\n", unPix.v);
            fprintf(flot, "%d\n", unPix.b);
        }
    }
    
    // et on ferme le fichier
    fclose(flot);
}




// ***************************************************************
// chargeImP2 : charge dans une structure de type ImP2
// l'image contenue dans le fichier donnée en paramètre

ImP2 chargeImP2(char* fichier){
    FILE* flot;
    ImP2 im;
    char c;
    
    // Pour lire le type de l'image
    char imtype[4];
    
    // Tableau suffisament grand pour lire une ligne
    char uneligne[255];
    
    int h, l, vmax;   // hauteur, largeur, valeur max
    
    
    // Ouverture du fichier texte en lecture
    // On vérifie qu'il n'y a pas d'erreur a l'ouverture
    if ((flot = fopen(fichier, "r")) == NULL){
        fprintf(stderr, "\nErreur dans chargeImP2 : %s innaccessible", fichier);
        im.hauteur = 0;
        im.largeur = 0;
        im.tpix = NULL;
        return im;
    };
    
    // Première ligne = type de l'image
    // on récupère le type de l'image et on vérifie que c'est bien P3
    // sinon on arrete et on retourne une image vide
    fscanf(flot, "%s", imtype);
    if ( strcmp(imtype, "P2") !=0 ){
        fprintf(stderr, "\nErreur dans chargeImP2 : %s n'est pas de type P3", fichier);
        im.hauteur = 0;
        im.largeur = 0;
        im.tpix = NULL;
        fclose(flot); // On ferme le fichier
        return im;
    }
    
    // On se place au début de la ligne suivante
    ligneSuivante(flot);
    
    // On passe eventuellement toute les lignes de commentaires commencant par #
    // on lit ligne par ligne
    // tant que la ligne commence par un #
    
    litligne(flot, uneligne);
    while (uneligne[0] == '#')
        litligne(flot, uneligne);
    
    // A la fin de cette boucle while, la ligne lue contient
    // la largeur et la hauteur de l'image
    // On peut les récupérer avec la fonction sscanf
    sscanf(uneligne, "%d%d", &l, &h);    

    // On récupère la valeur maxi des pixels 
    fscanf(flot, "%d", &vmax);
        
    // On initialise l'image en mémoire
    im = initImP2(h, l, vmax);
    
    // Puis on lit tous les pixels qu'on place dans le tableau 
    // Attention : les niveaux de couleur sont donné sous forme d'entiers, 
    // il faut les convertir en unsigned char !
    int g; 
    for (int i=0; i<im.hauteur; i++) {
        for(int j=0; j< im.largeur; j++){
            fscanf(flot, "%d", &g);
            im.tpix[i][j] = (unsigned char) g;
        }
    }
    
    // On ferme le fichier
    fclose(flot);
    // Et on retourne l'image lue
    return im;
}




// ***************************************************************
// sauveImP2 :  créer le fichier image pnm  a partir
// de la structure tImage donnée

void sauveImP2(char* nom, const ImP2 im){
    FILE* flot;
    // Ouverture du fichier
    if( (flot = fopen(nom, "w")) == NULL){
        fprintf(stderr, "\nErreur dans sauvePnm : impossible de creer le fichier %s", nom);
        return;
    }
    // On ecrit d'abord le type de l'image
    fprintf(flot, "P2\n");
    
    // On ecrit une ligne de commentaire pour indiquer le createur
    fprintf(flot, "# CREATOR : devoir de langage C\n");
    
    // On ecrit les dimensions de l'image
    fprintf(flot, "%d %d\n", im.largeur, im.hauteur);
    
    // Puis la valeur maxi des pixels
    fprintf(flot, "%d\n", im.maxval);
    
    // On ecrit tous les pixels
    // Attention les niveaux de gris sont des unsigned char qu'il faut écrire dans le fichier sous la forme d'entiers!
    for(int i=0; i<im.hauteur; i++){
        for(int j=0; j<im.largeur; j++){
            fprintf(flot, "%d\n", im.tpix[i][j]);
        }
    }
    
    // et on ferme le fichier
    fclose(flot);
}

// ***************************************************************
// P3toP2: charge dans une structure de type ImP3 et la change en une image ImP2
ImP2 P3toP2(const ImP3 im3){
    ImP2 newImP2;
    int i, j;
    newImP2 = initImP2(im3.hauteur, im3.largeur ,im3.maxval);
    for(i=0; i<im3.hauteur; i++){
        for(j=0; j<im3.largeur; j++){
            newImP2.tpix[i][j] =  (int)((0.2125 * im3.tpix[i][j].r) + (0.7154 * im3.tpix[i][j].v) + (0.0721 * im3.tpix[i][j].b));
    }}
    return newImP2;
}

// ***************************************************************
// negatifP2: charge une image ImP2, et la change en une image de la même structure en negatif
ImP2 negatifP2(const ImP2 im) {
    ImP2 negativeImP2;

    int i,j;
    negativeImP2 = initImP2(im.hauteur, im.largeur, im.maxval);
    for(i=0; i<negativeImP2.hauteur; i++){
        for(j=0; j<negativeImP2.largeur; j++){
            negativeImP2.tpix[i][j] = im.maxval-(im.tpix[i][j]);
    }}
    return negativeImP2;
}
// ***************************************************************
// negatifP3: charge une image ImP3, et la change en une image de la même structure en negatif
ImP3 negatifP3(const ImP3 im3){
    ImP3 newImP3;
    int i, j;
    newImP3 = initImP3(im3.hauteur, im3.largeur ,im3.maxval);
    for(i=0; i<im3.hauteur; i++){
        for(j=0; j<im3.largeur; j++){
            newImP3.tpix[i][j].r =  im3.maxval - im3.tpix[i][j].r;
            newImP3.tpix[i][j].v =  im3.maxval - im3.tpix[i][j].v;
            newImP3.tpix[i][j].b =  im3.maxval - im3.tpix[i][j].b;
        }}
    return newImP3;
}

// ***************************************************************
// flou: charge dans une structure de type ImP3 
// retourne une image de même structure flouté 
ImP3 flou(const ImP3 im, int r){
    int i,j,k,l;
    int division = (r+r+1)*3;
    ImP3 newImP3;
    int moy_r, moy_v, moy_b;
    newImP3 = initImP3(im.hauteur,im.largeur,im.maxval);

    int count,m;

    //On fait la moyenne de tout les éléments dans un rayon de r autour d'un pixel précis
    //Manque encore la gestion des bordures
    for(i=0; i<(im.hauteur); i++){
        for(j=0; j<(im.largeur); j++){
                //reset les valeurs 
                moy_r = 0;
                moy_v = 0;
                moy_b = 0;
                count = 0;
            //Ici la boucle for vérifie par des "if ... else ..." si les valeurs recherché sont des bordures
            for (k = (i - r > 0 ? i - r : 0); k <= (i + r < im.hauteur ? i + r : im.hauteur - 1); k++) {
                for (l = (j - r > 0 ? j - r : 0); l <= (j + r < im.largeur ? j + r : im.largeur - 1); l++) {
                    moy_r += im.tpix[k][l].r;
                    moy_v += im.tpix[k][l].v;
                    moy_b +=im.tpix[k][l].b;
                    count++;
                    }
            }
            newImP3.tpix[i][j].r = (int)(moy_r / count) ;
            newImP3.tpix[i][j].v = (int)(moy_v / count);
            newImP3.tpix[i][j].b = (int)(moy_b / count);
        }}
    return newImP3;
}

// ***************************************************************
// detoure: charge dans une structure de type ImP3 
// renvoie une image ImP3 detouré de l'image entré en paramètre
ImP3 detoure(const ImP3 im){
    ImP3 flouImP3 = flou(im, 6);
    ImP3 newImP3;
    int i,j;
    newImP3 = initImP3(im.hauteur,im.largeur,im.maxval);
    for(i=0; i<(im.hauteur); i++){
        for(j=0; j<(im.largeur); j++){
            newImP3.tpix[i][j].r = 255 - (im.tpix[i][j].r - flouImP3.tpix[i][j].r > 0 ? im.tpix[i][j].r - flouImP3.tpix[i][j].r : 0);
            newImP3.tpix[i][j].v = 255 - (im.tpix[i][j].v - flouImP3.tpix[i][j].v > 0 ? im.tpix[i][j].v - flouImP3.tpix[i][j].v : 0);
            newImP3.tpix[i][j].b = 255 - (im.tpix[i][j].b - flouImP3.tpix[i][j].b > 0 ? im.tpix[i][j].b - flouImP3.tpix[i][j].b : 0);
    }}
    return newImP3;
}
