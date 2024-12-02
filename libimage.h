//
//  libimage.h
//
// Régis Girard 2024

#ifndef LIBIMAGE_H
#define LIBIMAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


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
    int maxval;         // Valeur maximal d'un pixel (255)
    PixelRGB** tpix;       // Le tableau des pixels
} ImP3;


// Le type ImP2 pour stocker une image de type P2 dans un tableau rectangulaire d'octets 
// niveau de gris entre 0 net 255

typedef struct image2 {
    int hauteur;        // Hauteur en pixels
    int largeur;        // Largeur en pixels
    int maxval;         // Valeur maximal d'un pixel (255)
    unsigned char** tpix;       // Le tableau des pixels gris
} ImP2;



// ************************************************
// initImP3 : effectue l'allocation mémoire nécessaire pour une image de haut x larg pixels 
// et dont l'intensité maximal pour les pixels est vmax


extern ImP3 initImP3(int haut, int larg, int vmax);


// ************************************************
// copieImageP3 : retourne une copie de l'image donnée en paramètre

extern ImP3 copieImP3(const ImP3 im);


// ************************************************
// initImP2 : effectue l'allocation mémoire nécessaire pour une image en niveaux de gris 
// de haut x larg pixels et dont l'intensité maximal pour les pixels est vmax

extern ImP2 initImP2(int haut, int larg, int vmax);


// ************************************************
// copieImP2 : retourne une copie de l'image de type P2 donnée en paramètre

extern ImP2 copieImP2(const ImP2 im);


// ************************************************
// chargeImP3 : charge dans une structure de type imP3
// l'image contenue dans le fichier donnée en paramètre

extern ImP3 chargeImP3(char* fichier);


// ************************************************
// sauveImP3 :  créer le fichier image pnm  a partir
// de la structure ImP3 donnée

extern void sauveImP3(char* nom, ImP3 im);


// ************************************************
// chargeImP2 : charge dans une structure de type ImP2
// l'image contenue dans le fichier donnée en paramètre

extern ImP2 chargeImP2(char* fichier);


// ************************************************
// sauveImP2 :  créer le fichier image pnm  a partir
// de la structure ImP2 donnée

extern void sauveImP2(char* nom, ImP2 im);


// ************************************************
// Transformation en niveau de gris
/*
La C.I.E (Commission Internationale de l'Éclairage) propose, de caractériser l’information de luminance (la valeur de gris) d’un pixel par deux formules :
          
 Dans sa recommandation 709, qui concerne les couleurs « vraies » ou naturelles :
 Gris = 0.2125 Rouge + 0.7154 Vert + 0.0721 Bleu
 */
 // Renvoie une nouvelle image de type P2, l'image d'origine n'est pas modifiée
extern ImP2 P3toP2(const ImP3 im3);


// ************************************************
// Inversion des couleurs d'une image P3 (négatif)
// Renvoie une image en négatif de l'image donnée en paramètre 

extern ImP3 negatifP3(ImP3 im);


// ************************************************
// Négatif d'une image P2 n niveaux de gris
// Renvoie une image en négatif de l'image donnée en paramètre 

extern ImP2 negatifP2(ImP2 im);





// ************************************************
// Floutage gaussien
// 
// On travaille sur une copie de l'image
// Chaque pixel p(x,y) est remplacé par la moyenne des pixels
// se trouvant dans un carré de 2n+1 pixels de coté autour de p(x,y)

// Calcule la moyenne des pixels a une distance au plus n de p(x,y)
extern PixelRGB floumoy(ImP3 im, int x, int y, int n);

// flou : floute une image en appliquant le rayon de floutage 
// Renvoie une nouvelle image, celle d'origine n'est pas modifiée
extern ImP3 flou(const ImP3 im, int r);



// -------------------------------------------
// Détourage en utilisant le floutage gaussien
// -------------------------------------------

// Renvoie une nouvelle image résultat du détourage de l'image initilae 
// en utilisant le flou gaussien avec un rayon de 2
extern ImP3 detoure(const ImP3 im);




// ************************************************
// CACHER UNE IMAGE DANS UNE IMAGE
// 

// cacheImage : cache l'image im2 dans l'image im1
// im2 doit avoir des dimensions inferieure à celle de im1
// Chaque pixels de im2 est caché dans le pixel correspondant de im1
// Renvoie une nouvelle image, celles d'origine ne sont pas modifiées
extern ImP3 cacheImage(const ImP3 im1, const ImP3 im2);



// reveleImage : revele l'image cachée dans im
// On reconstruit l'image cachée à partir des bits de poids faible
// des octest de l'image im
// Rq : il y a perte de l'info contenu dans les bits de poids faible de l'image
// qu'on a cachée.
// renvoie une nouvelle image, celle d'origine n'est pas modifiée
extern ImP3 reveleImage(const ImP3 im);




// ************************************************
// CACHER DU TEXTE DANS UNE IMAGE


// cacheTexte: cache le contenu d'un fichier texte dans une image couleur
// Les caractères du texte sont cachés dans les premiers pixel de l'image
// Renvoie une nouvelle image, l'image d'origine n'est pas modifiée.
extern ImP3 cacheTexte(const ImP3 im, char* lefichier);




// reveleTexte : revele le texte caché dans une image couleur im 
// Créer un fichier texte dans lequel est écrit le texte caché dans une image

extern void reveleTexte(const ImP3 im, char* fichExtrait);


#endif /* libimage_h */

