//
//  slave.c
//  COMP428-A1
//
//  Created by Grégoire Morpain on 2/6/12.
//  Copyright (c) 2012 Concordia. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

#include "comp428_A1.h"

int main(int argc, const char *argv[])
{
    double      data;

    int         taskid,
                numtasks,
                sizeP,
                len;

    char        name[MPI_MAX_PROCESSOR_NAME];

    MPI_Comm    parent;

    MPI_Init(&argc, (char***)&argv);

    MPI_Comm_get_parent(&parent);
    if (parent == MPI_COMM_NULL) {
        fprintf(stderr, "Program was not spawned.");
        return (EXIT_FAILURE);
    }

	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
	MPI_Comm_size(parent, &sizeP);

	MPI_Get_processor_name(name, &len);
    printf("Slave %d of %d on %s, parent size %d\n", taskid, numtasks, name, sizeP);

    srandom((unsigned int)time(NULL) * taskid);

    data = dboard((int)(DARTS / numtasks));
    MPI_Send(&data, 1, MPI_DOUBLE, 0, 0, parent);

	MPI_Finalize();

	return (EXIT_SUCCESS);
}
