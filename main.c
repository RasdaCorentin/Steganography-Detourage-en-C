#include "libimage.h"

void afficherMenu() {
    printf("\nMenu :\n");
    printf("1. Charger une image\n");
    printf("2. Sauvegarder une image en niveaux de gris\n");
    printf("3. Appliquer un négatif\n");
    printf("4. Appliquer un flou\n");
    printf("5. Appliquer un détourage\n");
    printf("6. Cacher une image dans une autre\n");
    printf("7. Révéler une image cachée\n");
    printf("8. Cacher un texte dans une image\n");
    printf("9. Révéler un texte caché\n");
    printf("0. Quitter\n");
    printf("Choisissez une option : ");
}

int main() {
    int choix;
    char input_file[256];
    char output_file[256];
    ImP3 image;
    ImP3 image2;
    int image_chargee = 0;

    do {
        afficherMenu();
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("Entrez le chemin de l'image à charger : ");
                scanf("%s", input_file);
                image = chargeImP3(input_file);
                image_chargee = 1;
                printf("Image chargée : %dx%d pixels, maxval = %d\n", image.largeur, image.hauteur, image.maxval);
                break;

            case 2:
                if (!image_chargee) {
                    printf("Aucune image chargée. Chargez une image d'abord.\n");
                } else {
                    printf("Entrez le chemin pour sauvegarder l'image en niveaux de gris : ");
                    scanf("%s", output_file);
                    ImP2 grayscale_image = P3toP2(image);
                    sauveImP2(output_file, grayscale_image);
                    printf("Image en niveaux de gris sauvegardée dans : %s\n", output_file);
                    free(grayscale_image.tpix);
                }
                break;

            case 3:
                if (!image_chargee) {
                    printf("Aucune image chargée. Chargez une image d'abord.\n");
                } else {
                    printf("Entrez le chemin pour sauvegarder l'image en négatif : ");
                    scanf("%s", output_file);
                    printf("S'agit-il d'une image en couleur (1) ou en niveaux de gris (2) ? ");
                    int type;
                    scanf("%d", &type);
                    if (type == 1) {
                        ImP3 negative_image = negatifP3(image);
                        sauveImP3(output_file, negative_image);
                        printf("Image en négatif sauvegardée dans : %s\n", output_file);
                        free(negative_image.tpix);
                    } else if (type == 2) {
                        ImP2 grayscale_image = P3toP2(image);
                        ImP2 negative_image = negatifP2(grayscale_image);
                        sauveImP2(output_file, negative_image);
                        printf("Image en négatif (niveaux de gris) sauvegardée dans : %s\n", output_file);
                        free(grayscale_image.tpix);
                        free(negative_image.tpix);
                    } else {
                        printf("Type invalide.\n");
                    }
                }
                break;

            case 4:
                if (!image_chargee) {
                    printf("Aucune image chargée. Chargez une image d'abord.\n");
                } else {
                    printf("Entrez le chemin pour sauvegarder l'image floutée : ");
                    scanf("%s", output_file);
                    int rayon;
                    printf("Entrez le rayon de floutage : ");
                    scanf("%d", &rayon);
                    ImP3 blurred_image = flou(image, rayon);
                    sauveImP3(output_file, blurred_image);
                    printf("Image floutée sauvegardée dans : %s\n", output_file);
                    free(blurred_image.tpix);
                }
                break;

            case 5:
                if (!image_chargee) {
                    printf("Aucune image chargée. Chargez une image d'abord.\n");
                } else {
                    printf("Entrez le chemin pour sauvegarder l'image détournée : ");
                    scanf("%s", output_file);
                    ImP3 detoured_image = detoure(image);
                    sauveImP3(output_file, detoured_image);
                    printf("Image détournée sauvegardée dans : %s\n", output_file);
                    free(detoured_image.tpix);
                }
                break;

            case 6:
                if (!image_chargee) {
                    printf("Aucune image chargée. Chargez une image d'abord.\n");
                } else {
                    printf("Entrez le chemin de la deuxième image à cacher : ");
                    scanf("%s", input_file);
                    image2 = chargeImP3(input_file);
                    printf("Entrez le chemin pour sauvegarder l'image fusionnée : ");
                    scanf("%s", output_file);
                    ImP3 hidden_image = cacheImage(image, image2);
                    sauveImP3(output_file, hidden_image);
                    printf("Image fusionnée sauvegardée dans : %s\n", output_file);
                    free(image2.tpix);
                    free(hidden_image.tpix);
                }
                break;

            case 7:
                if (!image_chargee) {
                    printf("Aucune image chargée. Chargez une image d'abord.\n");
                } else {
                    printf("Entrez le chemin pour sauvegarder l'image révélée : ");
                    scanf("%s", output_file);
                    ImP3 revealed_image = reveleImage(image);
                    sauveImP3(output_file, revealed_image);
                    printf("Image révélée sauvegardée dans : %s\n", output_file);
                    free(revealed_image.tpix);
                }
                break;

            case 8:
                if (!image_chargee) {
                    printf("Aucune image chargée. Chargez une image d'abord.\n");
                } else {
                    printf("Entrez le chemin du fichier texte à cacher : ");
                    scanf("%s", input_file);
                    printf("Entrez le chemin pour sauvegarder l'image contenant le texte : ");
                    scanf("%s", output_file);
                    ImP3 text_hidden_image = cacheTexte(image, input_file);
                    sauveImP3(output_file, text_hidden_image);
                    printf("Image avec texte caché sauvegardée dans : %s\n", output_file);
                    free(text_hidden_image.tpix);
                }
                break;

            case 9:
                if (!image_chargee) {
                    printf("Aucune image chargée. Chargez une image d'abord.\n");
                } else {
                    printf("Entrez le chemin pour sauvegarder le texte révélé : ");
                    scanf("%s", output_file);
                    reveleTexte(image, output_file);
                    printf("Texte révélé sauvegardé dans : %s\n", output_file);
                }
                break;

            case 0:
                printf("Quitter le programme.\n");
                break;

            default:
                printf("Option invalide. Veuillez réessayer.\n");
        }

    } while (choix != 0);

    return EXIT_SUCCESS;
}
