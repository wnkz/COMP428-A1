//
//  dboard.c
//  COMP428-A1
//
//  Created by Grégoire Morpain on 1/19/12.
//  Copyright (c) 2012 Concordia. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "comp428_A1.h"

double dboard(int darts)
{
    double  x_coord,
            y_coord,
            pi,
            r;

    int     score,
            n;

    unsigned int cconst;  /* must be 4-bytes in size */
    /*************************************************************************
     * The cconst variable must be 4 bytes. We check this and bail if it is
     * not the right size
     ************************************************************************/
    if (sizeof(cconst) != 4) {
        printf("Wrong data size for cconst variable in dboard routine!\n");
        printf("See comments in source file. Quitting.\n");
        exit(1);
    }

    cconst = 2 << (31 - 1);
    score = 0;

    /* "throw darts at board" */
    for (n = 1; n <= darts; n++) {
        /* generate random numbers for x and y coordinates */
        r = (double)random() / cconst;
        x_coord = (2.0 * r) - 1.0;
        r = (double)random()/cconst;
        y_coord = (2.0 * r) - 1.0;

        /* if dart lands in circle, increment score */
        if ((SQR(x_coord) + SQR(y_coord)) <= 1.0)
            score++;
    }

    /* calculate pi */
    pi = 4.0 * (double)score / (double)darts;
    return(pi);
}