//
//  main.c
//  COMP428-A1
//
//  Created by Grégoire Morpain on 1/19/12.
//  Copyright (c) 2012 Concordia. All rights reserved.
//

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#include "comp428_A1.h"

int main(int argc, char *argv[])
{
    double  homepi,
            pisum,
            pi,
            avepi;

    int     taskid,
            numtasks,
            rc;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &taskid);

    if (taskid == MASTER) {
        printf("Parallel computing of pi (3.1415926535), using %d tasks.\n", numtasks);
    }

    printf("MPI task %d has started...\n", taskid);

    srandom(taskid);

    avepi = 0.;
    for (int i = 0; i < ROUNDS; i++) {
        homepi = dboard(DARTS);

        rc = MPI_Reduce(&homepi, &pisum, 1, MPI_DOUBLE, MPI_SUM, MASTER, MPI_COMM_WORLD);

        if (rc != MPI_SUCCESS) {
            printf("%d: failure on mpc_reduce\n", taskid);
        }

        if (taskid == MASTER) {
            pi = pisum / numtasks;
            avepi = ((avepi * i) + pi) / (i + 1);
            printf("    After %8d throws, average value of pi = %10.8f\n", (DARTS * (i + 1)), avepi);
        }
    }

    MPI_Finalize();

    return (0);
}

