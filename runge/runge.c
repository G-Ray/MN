// *************************************************************************************************
//
// Projet Universitaire - EIDD
// Etude des rebonds d'une bille sur un escalier
// Méthode de Runge-Kutta
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

double f(double vz0) {
    return vz0;
}

double g() {
    return -GRAVITATION;
}

double h(double vx0) {
    return vx0;
}

double i() {
    return 0;
}

int main()
{
    FILE *positions;
    FILE *escalier;

    int dessous = 0;

    double k1x0, k1vx0, k1z0, k1vz0,
        k2x0, k2vx0, k2z0, k2vz0,
        k3x0, k3vx0, k3z0, k3vz0,
        k4x0, k4vx0, k4z0, k4vz0;

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

        int nb_marches = x0/DISTANCE_MARCHE;
        hauteur = HAUTEUR_ESCALIER - HAUTEUR_MARCHE * nb_marches;

        /* Ecriture de l'escalier au fur et a mesure */
        if ( hauteur >= 0 ) {
            fprintf(escalier, "%6.3f\t%6.3f\n", x0, hauteur);
        } else {
            fprintf(escalier, "%6.3f\t%6.3f\n", x0, 0);
            hauteur = 0;
        }

        /* Runge-Kutta */
        k1z0 = PAS * f(vz0);
        k1vz0 = PAS * g();
        k1x0 = PAS * h(vx0);
        k1vx0 = PAS * i();

        k2z0 = PAS * f(vz0 + k1vz0/2);
        k2vz0 = PAS * (g() + k1vz0/2);
        k2x0 = PAS * h(vx0 + k1vx0/2);
        k2vx0 = PAS * i(h(vx0) + k1vx0/2);

        k3z0 = PAS * f(vz0 + k2vz0/2);
        k3vz0 = PAS * (g() + k2vz0/2);
        k3x0 = PAS * h(vx0 + k2vx0/2);
        k3vx0 = PAS * i(h(vx0) + k2vx0/2);

        k4z0 = PAS * f(vz0 + k3vz0);
        k4vz0 = PAS * (g() + k3vz0);
        k4x0 = PAS * h(vx0 + k3vx0);
        k4vx0 = PAS * i(h(vx0) + k3vx0);

        z1 = z0 + (k1z0 + 2*k2z0 + 2*k3z0 + k4z0 ) / 6;

        vz1 = vz0 + (k1vz0 + 2*k2vz0 + 2*k3vz0 + k4vz0 ) / 6;

        /* Rebond de la bille */
        if (z0 <= hauteur && dessous == 0)
        {
            dessous = 1;
            vz1 = -vz0 * COEFF_RESTITUTION; //rebond
        }

        /* Pour corriger la traversée du sol lorsqu'il y a des rebonds de très faible amplitude*/
        if(vz1 < 0 && z0 < 0)
          z1 = 0;
        if (z0 >= hauteur) dessous = 0;

        x1 = x0 + (k1x0 + 2*k2x0 + 2*k3x0 + k4x0 ) / 6;
        vx1 = vx0 + (k1vx0 + 2*k2vx0 + 2*k3vx0 + k4vx0 ) / 6;

        /* Ecriture du fichier des positions de la bille */
        fprintf(positions, "%6.3f\t%6.3f\t%6.3f\t%6.3f\t%6.3f\n", t, x0, vx0, z0, vz0);

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
