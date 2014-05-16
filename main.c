#include <stdio.h>
#include <math.h>

#define GRAVITATION 9.81
#define COEFF_RESTITUTION 0.8
#define PAS 0.025
#define DISTANCE_MARCHE 1.0
#define HAUTEUR_MARCHE 0.5
#define NOMBRE_MARCHES 10

int main()
{
    FILE *positions;
    FILE *escalier;

    double vz0 = -1;
    double z0 = 10;

    double vx0 = 1;
    double x0 = 0;

    double SOL = 0;

    double t1, vx1, vz1, t, z1, x1;

    positions = fopen("positions.txt", "w+");
    escalier = fopen("escalier.txt", "w+");

    double HAUTEUR_ESCALIER = NOMBRE_MARCHES * HAUTEUR_MARCHE;

    for(t=0; t<=50; t+=PAS) {

        t1 = t + PAS;
        z1 = z0 + (t1 - t) * vz0;

        //TODO: decouper en fonctions
        // Bille qui touche le sol

        int nb_marches = x0/DISTANCE_MARCHE;
        double h = HAUTEUR_ESCALIER - HAUTEUR_MARCHE * nb_marches;

        if ( h>= 0) {
          printf("%6.3f\t%6.3f\n", x0, h);
          fprintf(escalier, "%6.3f\t%6.3f\n", x0, h);
        }

        //printf("%6.3f\t\n", HAUTEUR_ESCALIER - HAUTEUR_MARCHE * nb_marches);

        if (z1 < h || z1 < SOL + 0.1)
        {
            vz1 = -vz0 * COEFF_RESTITUTION;
        }
        else
            vz1 = vz0 - (t1 - t) * GRAVITATION;

        x1 = x0 + (t1 - t) * vx0;
        vx1 = vx0;
//        printf("%6.3f\t%6.3f\t%6.3f\t%6.3f\t%6.3f\n", t, x0, vx0, z0, vz0);
        fprintf(positions, "%6.3f\t%6.3f\t%6.3f\t%6.3f\t%6.3f\n", t, x0, vx0, z0, vz0);
        z0 = z1;
        vz0 = vz1;
        x0 = x1;
        vx0 = vx1;
    }

    fclose(positions);
    fclose(escalier);

    return 0;
}
