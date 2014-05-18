#include <stdio.h>
#include <math.h>

#define GRAVITATION 9.81
#define COEFF_RESTITUTION 0.8
#define PAS 0.01
#define DISTANCE_MARCHE 1.0
#define HAUTEUR_MARCHE 0.5
#define NOMBRE_MARCHES 12
#define DUREE 25

int main()
{
    FILE *positions;
    FILE *escalier;

    int dessous = 0;

    double vz0 = -1;
    double z0 = 10;

    double vx0 = 1;
    double x0 = 0;

    double SOL = 0;

    double t1, vx1, vz1, t, z1, x1;

    positions = fopen("positions.txt", "w+");
    escalier = fopen("escalier.txt", "w+");

    double HAUTEUR_ESCALIER = NOMBRE_MARCHES * HAUTEUR_MARCHE;

    for(t=0; t<=DUREE; t+=PAS) {

        t1 = t + PAS;

        int nb_marches = x0/DISTANCE_MARCHE;
        double hauteur = HAUTEUR_ESCALIER - HAUTEUR_MARCHE * nb_marches;

        if (hauteur >= 0) {
            fprintf(escalier, "%6.3f\t%6.3f\n", x0, hauteur);
        } else {
        	hauteur = 0;
        	fprintf(escalier, "%6.3f\t%6.3f\n", x0, 0);
       	}

        vz1 = vz0 - (t1 - t) * GRAVITATION;

        if (z0 <= hauteur && dessous == 0)
        {
        	dessous = 1;
            vz1 = -vz0 * COEFF_RESTITUTION;
        }

        // Pour corriger la traversée du sol lorsqu'il y a des rebonds de très faible amplitude
        if(vz1 < 0 && z0 < 0)
        	vz1 = 0;

        if(z0 >= hauteur) dessous = 0;

        x1 = x0 + (t1 - t) * vx0;
        vx1 = vx0;

        fprintf(positions, "%6.3f\t%6.3f\t%6.3f\t%9.6f\t%6.3f\n", t, x0, vx0, z0, vz0);

        z1 = z0 + (t1 - t) * vz0;

        z0 = z1;
        vz0 = vz1;
        x0 = x1;
        vx0 = vx1;
    }

    fclose(positions);
    fclose(escalier);

    return 0;
}
