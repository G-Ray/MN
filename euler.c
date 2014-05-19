// *************************************************************************************************
//
// Projet Universitaire - EIDD
// Etude des rebonds d'une bille sur un escalier
// Méthode d'Euler
// --------------------------------------
// Copyright (C) 2014 Geoffrey Bonneville et Wendy Calma
//
// *************************************************************************************************

#include <stdio.h>
#include <math.h>

#define GRAVITATION 9.81
#define COEFF_RESTITUTION 0.8
#define PAS 0.01
#define DISTANCE_MARCHE 1.0 //Distance entre 2 marches
#define HAUTEUR_MARCHE 0.5 //Hauteur entre 2 marches
#define NOMBRE_MARCHES 12
#define DUREE 25 //Duree de la simulation
#define SOL 0  //Hauteur du sol

int main()
{
    FILE *positions;
    FILE *escalier;

    int dessous = 0;

    /* Definition des conditions initiales */
    double vz0 = -1;
    double z0 = 10;

    double vx0 = 1;
    double x0 = 0;

    double vx1, vz1, t, z1, x1;

    /* Ouverture des fichiers */
    positions = fopen("positions.txt", "w+");
    escalier = fopen("escalier.txt", "w+");

    /* Calcul de la hauteur maximale de l'escalier */
    double HAUTEUR_ESCALIER = NOMBRE_MARCHES * HAUTEUR_MARCHE;
    double hauteur = HAUTEUR_ESCALIER;

    for(t=0; t<=DUREE; t+=PAS) {

        /* Calcul de la hauteur courante */
        int nb_marches = x0/DISTANCE_MARCHE;
        hauteur = HAUTEUR_ESCALIER - HAUTEUR_MARCHE * nb_marches;

        /* Ecriture de l'escalier au fur et a mesure */
        if (hauteur >= 0) {
            fprintf(escalier, "%6.3f\t%6.3f\n", x0, hauteur);
        } else {
        	hauteur = 0;
        	fprintf(escalier, "%6.3f\t%6.3f\n", x0, 0);
       	}

        vz1 = vz0 - PAS * GRAVITATION;

        /* Rebond de la bille */
        if (z0 <= hauteur && dessous == 0)
        {
        	dessous = 1;
            vz1 = -vz0 * COEFF_RESTITUTION; //rebond
        }

        /* Pour corriger la traversée du sol lorsqu'il y a des rebonds de très faible amplitude*/
        if(vz1 < 0 && z0 < 0)
        	vz1 = 0;
        if(z0 >= hauteur) dessous = 0;

        x1 = x0 + PAS * vx0;
        vx1 = vx0;

        /* Ecriture du fichier des positions de la bille */
        fprintf(positions, "%6.3f\t%6.3f\t%6.3f\t%9.6f\t%6.3f\n", t, x0, vx0, z0, vz0);

        z1 = z0 + PAS * vz0;

        z0 = z1;
        vz0 = vz1;
        x0 = x1;
        vx0 = vx1;
    }

    /* Fermeture des fichiers*/
    fclose(positions);
    fclose(escalier);

    return 0;
}
