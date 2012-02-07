//
//  main.c
//  COMP428-A1-Sequential
//
//  Created by Grégoire Morpain on 2/4/12.
//  Copyright (c) 2012 Concordia. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "comp428_A1.h"

int main (int argc, const char *argv[])
{

    double  pi,
            avepi = 0.;

    printf("Sequential computing of pi (3.1415926535).\n");

    srandom((unsigned int)time(NULL));

    int     i;
    for (i = 0; i < ROUNDS; i++) {

        pi = dboard(DARTS);
        avepi = ((avepi * i) + pi) / (i + 1);

        // printf("    After %.0Lf throws, average value of pi = %10.8f\n", (long double)(DARTS * (i + 1)), avepi);
    }

    printf("Sequential computing of pi 3.1415926535\n");
    printf("                           %.10f\n", avepi);

    return (0);
}

