#include <stdio.h>
#include <math.h>

#define GRAVITATION 9.81
#define COEFF_RESTITUTION 0.9
#define PAS 0.025

int main()
{
    FILE *theorie;

    double vz0 = -1;
    double z; // equation de z selon le temps 
    double H0 = 50; // hauteur init  

    double vx = 1;
//     double x = 0;

    double sol = 0;

    double t1, vx1, vz1, t, z1, x1;

    theorie = fopen("theorie.txt", "w+");

    for(t=0; t<=50; t+=PAS) {
        x = vx * t;
        z = H0 - 0.5*GRAVITATION*t*t + vz0*t;

        // Bille qui touche le sol
//         if (z < sol + 0.5) {
//             vz1 = - vz0 * COEFF_RESTITUTION;
//             //sol -= 2;
//             vz0 = vz1;
//         }
//         else
            vz0 = sqrt(2*GRAVITATION*H0);

        //printf("%6.3f\t%6.3f\t%6.3f\t%6.3f\n", t, x, z, vz0);
        fprintf(theorie, "%6.3f\t%6.3f\t%6.3f\n", t, x, z);

    }

    fclose(theorie);

    return 0;
}
