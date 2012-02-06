//
//  slave.c
//  COMP428-A1
//
//  Created by Grégoire Morpain on 2/6/12.
//  Copyright (c) 2012 Concordia. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#include "comp428_A1.h"

int main(int argc, const char *argv[]) 
{ 
    int         taskid,
                size,
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
    

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
	MPI_Comm_size(parent, &sizeP);
    
//	MPI_Get_processor_name(name, &len);
//	printf("Hello world! I'm slave %d of %d on %s, parent size %d\n", rank, size, name, sizeP);
    
    
    /* 
     * Parallel code here.  
     * The manager is represented as the process with rank 0 in (the remote 
     * group of) the parent communicator.  If the workers need to communicate 
     * among themselves, they can use MPI_COMM_WORLD. 
     */ 
    
	int data = 1;
	
	MPI_Send(&data, 1, MPI_INT, 0, 0, parent);
	
	int sum = 0;
    
	MPI_Reduce(&data, &sum, 1, MPI_INT, MPI_SUM, 0, parent);
    
	printf("done, %d", sum);
	
	MPI_Finalize(); 

	return (EXIT_SUCCESS);
}
