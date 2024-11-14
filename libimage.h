#ifndef LIBIMAGE_H
#define LIBIMAGE_H

// ************************************************
// Définition des types

// Le type PixelRGB pour représenter les niveaux de (rouge, vert, bleu)
// Chaque quantité de couleur est comprise entre 0 et 255
// ce qui correspond au type unsigned char (un entier non signé sur un octet)
typedef struct pixelrgb {
    unsigned char r;
    unsigned char v;
    unsigned char b;
} PixelRGB;

// Le type ImP3 pour stocker une image de type P3 dans un tableau de pixels
typedef struct image3 {
    int hauteur;        // Hauteur en pixels
    int largeur;        // Largeur en pixels
    int maxval;         // Valeur maximal d'un pixel
    PixelRGB** tpix;       // Le tableau des pixels
} ImP3;


// Le type ImP2 pour stocker une image de type P2 dans un tableau rectangulaires d'octets 
// niveau de gris entre 0 net 255

typedef struct image2 {
    int hauteur;        // Hauteur en pixels
    int largeur;        // Largeur en pixels
    int maxval;         // Valeur maximal d'un pixel
    unsigned char** tpix;       // Le tableau des pixels gris
} ImP2;

// initImP3 : int x int x int -> ImP3
// Entrée : 3 entiers, hauteur , largeur et vmax de l'image
// Sortie : une structure ImP3 (tableau de tableau)
extern ImP3 initImP3(int haut, int larg, int vmax);

// copieImP3 : ImP3 -> ImP3
// Entrée : un ImP3 im
// Sortie : une copie de la structure ImP3 entrée en paramètre
extern ImP3 copieImP3(ImP3 im);

// chargeImP3 : char* -> ImP3
// Entrée : un pointeur sur le nom du fichier à charger
// Sortie : une structure ImP3 avec les valeurs dicté par le fichier.
extern ImP3 chargeImP3(char* fichier);


// chargeImP3 : char* x ImP3 -> ImP3
// Entrée : un pointeur sur une chaine de caractère et une image
// Sortie : Rien
//Crée un fichier image .ppm
extern void sauveImP3(char* nom, ImP3 im);

#endif
