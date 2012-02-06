//
//  master.c
//  COMP428-A1-Parallel-Spawn
//
//  Created by Grégoire Morpain on 2/6/12.
//  Copyright (c) 2012 Concordia. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#include "comp428_A1.h"

#define MAXPROCS 4

int main (int argc, const char *argv[])
{
	int         taskid,
                size,
                len,
                rc;

	char        name[MPI_MAX_PROCESSOR_NAME];

    MPI_Comm    everyone;
    MPI_Status  status;
    
	MPI_Init(&argc, (char***)&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &taskid);

	MPI_Comm_spawn("COMP428-A1-Parallel-Spawn-Slave", MPI_ARGV_NULL, MAXPROCS,  MPI_INFO_NULL, 0, MPI_COMM_SELF, &everyone, MPI_ERRCODES_IGNORE);

	int     data;
	int     i;
	for (i = 0; i < MAXPROCS; i++) {
	    MPI_Recv(&data, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, everyone, &status);
	    printf("Process Master: received %d by %d\n", data, status.MPI_SOURCE);
	}

    printf("Master process initiating reduce...\n");

	int sum = 0;
	rc = MPI_Reduce(&data, &sum, 1, MPI_INT, MPI_SUM, 0, everyone);
    if (rc != MPI_SUCCESS) {
        fprintf(stderr, "%d: failure on MPI_Reduce\n", taskid);
    }

    printf("Master process is done reducing, the answer is %d\n", sum);

	MPI_Finalize();

	return (EXIT_SUCCESS);
}
