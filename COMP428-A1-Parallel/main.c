//
//  main.c
//  COMP428-A1
//
//  Created by Grégoire Morpain on 1/19/12.
//  Copyright (c) 2012 Concordia. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

#include "comp428_A1.h"

int main(int argc, const char *argv[])
{
    double  homepi,
            pisum,
            pi,
            avepi = 0.;

    int     taskid,
            numtasks,
            rc;

    MPI_Init(&argc, (char***)&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &taskid);

    if (taskid == MASTER) {
        printf("Parallel computing of pi (3.1415926535), using %d tasks.\n", numtasks);
    }

    printf("MPI task %d has started...\n", taskid);

    srandom((unsigned int)time(NULL));

    int     i;
    for (i = 0; i < ROUNDS; i++) {
        homepi = dboard((int)(DARTS / numtasks));

        rc = MPI_Reduce(&homepi, &pisum, 1, MPI_DOUBLE, MPI_SUM, MASTER, MPI_COMM_WORLD);
        if (rc != MPI_SUCCESS) {
            fprintf(stderr, "%d: failure on MPI_Reduce\n", taskid);
        }

        if (taskid == MASTER) {
            pi = pisum / numtasks;
            avepi = ((avepi * i) + pi) / (i + 1);

            // printf("    After %.0Lf throws, average value of pi = %.10f\n", (long double)(DARTS * (i + 1)), avepi);
        }
    }

    if (taskid == MASTER) {
        printf("Parallel computing of pi 3.1415926535\n");
        printf("                         %.10f\n", avepi);
    }

    MPI_Finalize();

    return (0);
}

