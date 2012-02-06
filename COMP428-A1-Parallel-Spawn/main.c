//
//  main.c
//  COMP428-A1-Parallel-Spawn
//
//  Created by Grégoire Morpain on 2/6/12.
//  Copyright (c) 2012 Concordia. All rights reserved.
//

#include <stdio.h>

#include "comp428_A1.h"

int main (int argc, const char *argv[])
{
	int     rank,
            size,
            len;

	char    name[MPI_MAX_PROCESSOR_NAME];

	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Get_processor_name(name, &len);

	printf("Hello world! I'm %d of %d on %s\n", rank, size, name);
    
	MPI_Comm everyone;
	MPI_Comm_spawn("hello2.o", MPI_ARGV_NULL, 4,  MPI_INFO_NULL, 0, MPI_COMM_SELF, &everyone, MPI_ERRCODES_IGNORE);
    
	int     data;
	int     i;
	for (i = 0; i < 4; i++) {
	    MPI_Status status;
	    MPI_Recv (&data, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, everyone, &status);
	    printf ("process Master: received %d by %d\n", data, status.MPI_SOURCE);
	}
    
    printf ("process Master initiating reduce");
    
	int sum = 0;	
	MPI_Reduce(&data, &sum, 1, MPI_INT, MPI_SUM, 0, everyone);
    
    printf("process Master is done reducing, the answer is %d", sum);
    
	MPI_Finalize();

	return (0);
}

