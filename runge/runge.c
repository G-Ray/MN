#include <stdio.h>
#include <math.h>

#define GRAVITATION 9.81
#define COEFF_RESTITUTION 0.8
#define PAS 0.025
#define DISTANCE_MARCHE 1.0
#define HAUTEUR_MARCHE 0.5
#define NOMBRE_MARCHES 10

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

    double k1x0, k1vx0, k1z0, k1vz0,
        k2x0, k2vx0, k2z0, k2vz0,
        k3x0, k3vx0, k3z0, k3vz0,
        k4x0, k4vx0, k4z0, k4vz0;

    double vz0 = -1;
    double z0 = 10;

    double vx0 = 1;
    double x0 = 0;

    double SOL = 0;

    double t1, vx1, vz1, t, z1, x1;

    int dessous = 0;

    positions = fopen("positions.txt", "w+");
    escalier = fopen("escalier.txt", "w+");

    double HAUTEUR_ESCALIER = NOMBRE_MARCHES * HAUTEUR_MARCHE;

    for(t=0; t<=50; t+=PAS) {

        //t1 = t + PAS;
        //z1 = z0 + (t1 - t) * vz0;

        //TODO: decouper en fonctions
        // Bille qui touche le sol

        int nb_marches = x0/DISTANCE_MARCHE;
        double hauteur = HAUTEUR_ESCALIER - HAUTEUR_MARCHE * nb_marches;

        if ( hauteur >= 0 ) {
          //printf("%6.3f\t%6.3f\n", x0, hauteur);
          fprintf(escalier, "%6.3f\t%6.3f\n", x0, hauteur);
        }
        printf("%f\n", hauteur);

        //printf("%6.3f\t\n", HAUTEUR_ESCALIER - HAUTEUR_MARCHE * nb_marches);


        //else
            //vz1 = vz0 - (t1 - t) * GRAVITATION;
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

        if ((z0 < hauteur || z0 <= 0) && dessous == 0)
        {
            dessous = 1;
            vz1 = -vz0 * COEFF_RESTITUTION;
        }
        else {
            vz1 = vz0 + (k1vz0 + 2*k2vz0 + 2*k3vz0 + k4vz0 ) / 6;
        }

        if (z0 > hauteur) dessous = 0;

        x1 = x0 + (k1x0 + 2*k2x0 + 2*k3x0 + k4x0 ) / 6;
        vx1 = vx0 + (k1vx0 + 2*k2vx0 + 2*k3vx0 + k4vx0 ) / 6;

        //x1 = x0 + (t1 - t) * vx0;dessous = 1
        //vx1 =  vx0;
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
