#include "main.h"
int main(int argc, char **argv)
{
    int rank, size;
    int buf_rank = 0;
    double buf, buf1;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    srand(time(NULL) + rank);
    buf = (double)rand() / RAND_MAX;
    printf("Process #%d number: #%lf\n", rank, buf);
    if (rank != 0) {
        MPI_Send(&buf, 1, MPI_DOUBLE,
            0, 0, MPI_COMM_WORLD);
    } else {
        for (int i = 1; i < size; i++) {
            MPI_Recv(&buf1, 1, MPI_DOUBLE, i, MPI_ANY_TAG,
                MPI_COMM_WORLD, &status);
            if (buf1 > buf) {
                buf = buf1;
                buf_rank = i;
            }
        }
    }
    
    MPI_Finalize();
    if (rank == 0) {
        printf("Highest number: #%lf in thread #%d\n", buf, buf_rank);
    }
    return 0;
}
