//
//  master.c
//  COMP428-A1-Parallel-Spawn
//
//  Created by Grégoire Morpain on 2/6/12.
//  Copyright (c) 2012 Concordia. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

#include "comp428_A1.h"

#define MAXPROCS 4

int main (int argc, const char *argv[])
{
	double		pi,
				avepi = 0.;

	int         taskid,
                size,
                rc;

    MPI_Comm    everyone;
    MPI_Status  status;

	MPI_Init(&argc, (char***)&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &taskid);

	MPI_Comm_spawn("COMP428-A1-Parallel-Spawn-Slave", MPI_ARGV_NULL, MAXPROCS,  MPI_INFO_NULL, 0, MPI_COMM_SELF, &everyone, MPI_ERRCODES_IGNORE);

    int i;
    for (i = 0; i < MAXPROCS; i++) {
        MPI_Recv(&pi, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, everyone, &status);
        printf("Process Master: received %.10f by %d\n", pi, status.MPI_SOURCE);
    }
    

	MPI_Finalize();

	return (EXIT_SUCCESS);
}
