#include <stdio.h>
#include <math.h>

#define GRAVITATION 9.81

int main()
{

    FILE *pos_temps;

    double const PAS = 1;

    double vz0 = -1;
    double z0 = 5;

    double vx0 = 1;
    double x0 = 0;

    double SOL = 0;

    double t1, vx1, vz1, t, z1, x1;

    pos_temps = fopen("pos_temps.txt", "w+");

    for(t=0; t<=50; t+=PAS) {
        t1 = t + PAS;
        z1 = z0 + (t1 - t) * vz0;
        //TODO: decouper en fonctions
        vz1 = vz0 - (t1 - t) * GRAVITATION;
        x1 = x0 + (t1 - t) * vx0;
        vx1 =  vx0;
        printf("%6.3f\t%6.3f\t%6.3f\t%6.3f\t%6.3f\n", t, x0, vx0, z0, vz0);
        fprintf(pos_temps, "%6.3f\t%6.3f\t%6.3f\t%6.3f\t%6.3f\n", t, x0, vx0, z0, vz0);
        z0 = z1;
        vz0 = vz1;
        x0 = x1;
        vx0 = vx1;
    }

    fclose(pos_temps);

    return 0;
}
