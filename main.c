#include <stdio.h>
#include <math.h>

#define GRAVITATION 9.81
#define COEFF_RESTITUTION 0.9
#define PAS 0.025

int main()
{
    FILE *positions;

    double vz0 = -1;
    double z0 = 50;

    double vx0 = 1;
    double x0 = 0;

    double sol = 0;

    double t1, vx1, vz1, t, z1, x1;

    positions = fopen("positions.txt", "w+");

    for(t=0; t<=50; t+=PAS) {
        t1 = t + PAS;
        z1 = z0 + (t1 - t) * vz0;
        //TODO: decouper en fonctions

        // Bille qui touche le sol
        if (z1 < sol + 0.5) {
            vz1 = -vz0 * COEFF_RESTITUTION;
            sol -= 2;
        }
        else
            vz1 = vz0 - (t1 - t) * GRAVITATION;

        x1 = x0 + (t1 - t) * vx0;
        vx1 =  vx0;
        printf("%6.3f\t%6.3f\t%6.3f\t%6.3f\t%6.3f\n", t, x0, vx0, z0, vz0);
        fprintf(positions, "%6.3f\t%6.3f\t%6.3f\t%6.3f\t%6.3f\n", t, x0, vx0, z0, vz0);
        z0 = z1;
        vz0 = vz1;
        x0 = x1;
        vx0 = vx1;
    }

    fclose(positions);

    return 0;
}
