#define BUFS 1024*1024*100
#define HANDLES 100000

MPI_File fh[HANDLES];
MPI_Request request[HANDLES];
MPI_Status status, array_of_statuses[HANDLES];
int f_count, procs, myrank;
int size, rank;
unsigned long f_offset;
char sendbuf[BUFS], recvbuf[BUFS], buf[BUFS];

int main(int argc,char *argv[])
{
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&procs);
	MPI_Comm_rank(MPI_COMM_WORLD,&myrank);

	if (myrank == 0) {
		for(int i=0; i<62096197; i++); /* Simulate compute time */

		MPI_Comm_size(MPI_COMM_WORLD, &size);

		for(int i=0; i<1739; i++); /* Simulate compute time */

		MPI_Comm_rank(MPI_COMM_WORLD, &rank);

		for(int i=0; i<390; i++); /* Simulate compute time */

		for (int r=0; r<7; r++){
		MPI_Recv(buf, 1024, MPI_CHAR, -1, -1, MPI_COMM_WORLD, status);

		}

		for(int i=0; i<13074; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 1, MPI_INT, 0, MPI_COMM_WORLD);

		for(int i=0; i<549147; i++); /* Simulate compute time */

		MPI_Comm_size(MPI_COMM_WORLD, &size);

		for(int i=0; i<13190; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 4, MPI_BYTE, 0, MPI_COMM_WORLD);

		for(int i=0; i<594867; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(int i=0; i<24861; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<516; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<447; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

		for(int i=0; i<4882; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 1, MPI_INT, 0, MPI_COMM_WORLD);

		for(int i=0; i<472; i++); /* Simulate compute time */

		for (int r=0; r<7; r++){
		MPI_Recv(buf, 1024, MPI_CHAR, -1, -1, MPI_COMM_WORLD, status);

		}

		for(int i=0; i<572; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 1, MPI_INT, 0, MPI_COMM_WORLD);

		for(int i=0; i<52579; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 1, MPI_UNSIGNED_INT, 0, MPI_COMM_WORLD);

		for(int i=0; i<53682; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(int i=0; i<82618; i++); /* Simulate compute time */

		MPI_File_open(MPI_COMM_SELF, /home/wzzhang/project-cse/zhangyou/tmp/ior.dat.00000000, 41, info, &(fh[1]));

		for(int i=0; i<714; i++); /* Simulate compute time */

		f_offset = 0;
		for (int r=0; r<1024; r++){
			f_count=131072;
			f_offset += f_count * 1;
		MPI_File_write_at(fh[1], f_offset, buf, 131072, MPI_BYTE, status);

		}

		for(int i=0; i<55361; i++); /* Simulate compute time */

		MPI_File_close(&(fh[1]));

		for(int i=0; i<2223; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(int i=0; i<5213; i++); /* Simulate compute time */

		MPI_File_open(MPI_COMM_WORLD, /home/wzzhang/project-cse/zhangyou/tmp/ior.dat.00000000, 2, info, &(fh[1]));

		for(int i=0; i<26513; i++); /* Simulate compute time */

		MPI_File_close(&(fh[1]));

		for(int i=0; i<0; i++); /* Simulate compute time */

		for (int r=0; r<2; r++){
		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_LONG_LONG, MPI_SUM, MPI_COMM_WORLD);

		}

		for(int i=0; i<3399; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<347; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<406; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<301; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<331; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<283; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<318; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<290; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<305; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<467; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<300; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<294; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<3795; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(int i=0; i<3820; i++); /* Simulate compute time */

		MPI_File_open(MPI_COMM_SELF, /home/wzzhang/project-cse/zhangyou/tmp/ior.dat.00000000, 41, info, &(fh[1]));

		for(int i=0; i<423; i++); /* Simulate compute time */

		f_offset = 0;
		for (int r=0; r<1024; r++){
			f_count=131072;
			f_offset += f_count * 1;
		MPI_File_read_at(fh[1], f_offset, buf, 131072, MPI_BYTE, status);

		}

		for(int i=0; i<28013; i++); /* Simulate compute time */

		MPI_File_close(&(fh[1]));

		for(int i=0; i<1042; i++); /* Simulate compute time */

		MPI_File_open(MPI_COMM_WORLD, /home/wzzhang/project-cse/zhangyou/tmp/ior.dat.00000000, 2, info, &(fh[1]));

		for(int i=0; i<6979; i++); /* Simulate compute time */

		MPI_File_close(&(fh[1]));

		for(int i=0; i<0; i++); /* Simulate compute time */

		for (int r=0; r<2; r++){
		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_LONG_LONG, MPI_SUM, MPI_COMM_WORLD);

		}

		for(int i=0; i<962; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<384; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<333; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<335; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<289; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<345; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<306; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<497; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<309; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<346; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<306; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<352; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<0; i++); /* Simulate compute time */

		for (int r=0; r<2; r++){
		MPI_Barrier(MPI_COMM_WORLD);

		}

		for(int i=0; i<102501; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

	}

	if (myrank == 1) {
		for(int i=0; i<62096197; i++); /* Simulate compute time */

		MPI_Comm_size(MPI_COMM_WORLD, &size);

		for(int i=0; i<1739; i++); /* Simulate compute time */

		MPI_Comm_rank(MPI_COMM_WORLD, &rank);

		for(int i=0; i<13074; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 1, MPI_INT, 0, MPI_COMM_WORLD);

		for(int i=0; i<549147; i++); /* Simulate compute time */

		MPI_Comm_size(MPI_COMM_WORLD, &size);

		for(int i=0; i<13190; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 4, MPI_BYTE, 0, MPI_COMM_WORLD);

		for(int i=0; i<594867; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(int i=0; i<24861; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<516; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<447; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

		for(int i=0; i<4882; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 1, MPI_INT, 0, MPI_COMM_WORLD);

		for(int i=0; i<572; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 1, MPI_INT, 0, MPI_COMM_WORLD);

		for(int i=0; i<52579; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 1, MPI_UNSIGNED_INT, 0, MPI_COMM_WORLD);

		for(int i=0; i<53682; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(int i=0; i<714; i++); /* Simulate compute time */

		f_offset = 0;
		for (int r=0; r<1024; r++){
			f_count=131072;
			f_offset += f_count * 1;
		MPI_File_write_at(fh[1], f_offset, buf, 131072, MPI_BYTE, status);

		}

		for(int i=0; i<55361; i++); /* Simulate compute time */

		MPI_File_close(&(fh[1]));

		for(int i=0; i<2223; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(int i=0; i<0; i++); /* Simulate compute time */

		for (int r=0; r<2; r++){
		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_LONG_LONG, MPI_SUM, MPI_COMM_WORLD);

		}

		for(int i=0; i<3399; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<347; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<406; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<301; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<331; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<283; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<318; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<290; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<305; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<467; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<300; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<294; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<3795; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(int i=0; i<0; i++); /* Simulate compute time */

		for (int r=0; r<2; r++){
		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_LONG_LONG, MPI_SUM, MPI_COMM_WORLD);

		}

		for(int i=0; i<962; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<384; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<333; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<335; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<289; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<345; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<306; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<497; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<309; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<346; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<306; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<352; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<0; i++); /* Simulate compute time */

		for (int r=0; r<2; r++){
		MPI_Barrier(MPI_COMM_WORLD);

		}

		for(int i=0; i<102501; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

	}

	if (myrank == 2) {
		for(int i=0; i<62096197; i++); /* Simulate compute time */

		MPI_Comm_size(MPI_COMM_WORLD, &size);

		for(int i=0; i<1739; i++); /* Simulate compute time */

		MPI_Comm_rank(MPI_COMM_WORLD, &rank);

		for(int i=0; i<13074; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 1, MPI_INT, 0, MPI_COMM_WORLD);

		for(int i=0; i<549147; i++); /* Simulate compute time */

		MPI_Comm_size(MPI_COMM_WORLD, &size);

		for(int i=0; i<13190; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 4, MPI_BYTE, 0, MPI_COMM_WORLD);

		for(int i=0; i<594867; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(int i=0; i<24861; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<516; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<447; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

		for(int i=0; i<4882; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 1, MPI_INT, 0, MPI_COMM_WORLD);

		for(int i=0; i<572; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 1, MPI_INT, 0, MPI_COMM_WORLD);

		for(int i=0; i<52579; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 1, MPI_UNSIGNED_INT, 0, MPI_COMM_WORLD);

		for(int i=0; i<53682; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(int i=0; i<714; i++); /* Simulate compute time */

		f_offset = 0;
		for (int r=0; r<1024; r++){
			f_count=131072;
			f_offset += f_count * 1;
		MPI_File_write_at(fh[1], f_offset, buf, 131072, MPI_BYTE, status);

		}

		for(int i=0; i<55361; i++); /* Simulate compute time */

		MPI_File_close(&(fh[1]));

		for(int i=0; i<2223; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(int i=0; i<0; i++); /* Simulate compute time */

		for (int r=0; r<2; r++){
		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_LONG_LONG, MPI_SUM, MPI_COMM_WORLD);

		}

		for(int i=0; i<3399; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<347; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<406; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<301; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<331; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<283; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<318; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<290; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<305; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<467; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<300; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<294; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<3795; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(int i=0; i<423; i++); /* Simulate compute time */

		f_offset = 0;
		for (int r=0; r<1024; r++){
			f_count=131072;
			f_offset += f_count * 1;
		MPI_File_read_at(fh[1], f_offset, buf, 131072, MPI_BYTE, status);

		}

		for(int i=0; i<28013; i++); /* Simulate compute time */

		MPI_File_close(&(fh[1]));

		for(int i=0; i<6979; i++); /* Simulate compute time */

		MPI_File_close(&(fh[1]));

		for(int i=0; i<0; i++); /* Simulate compute time */

		for (int r=0; r<2; r++){
		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_LONG_LONG, MPI_SUM, MPI_COMM_WORLD);

		}

		for(int i=0; i<962; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<384; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<333; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<335; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<289; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<345; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<306; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<497; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<309; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<346; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<306; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<352; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<0; i++); /* Simulate compute time */

		for (int r=0; r<2; r++){
		MPI_Barrier(MPI_COMM_WORLD);

		}

		for(int i=0; i<102501; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

	}

	if (myrank == 3) {
		for(int i=0; i<62096197; i++); /* Simulate compute time */

		MPI_Comm_size(MPI_COMM_WORLD, &size);

		for(int i=0; i<1739; i++); /* Simulate compute time */

		MPI_Comm_rank(MPI_COMM_WORLD, &rank);

		for(int i=0; i<13074; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 1, MPI_INT, 0, MPI_COMM_WORLD);

		for(int i=0; i<549147; i++); /* Simulate compute time */

		MPI_Comm_size(MPI_COMM_WORLD, &size);

		for(int i=0; i<13190; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 4, MPI_BYTE, 0, MPI_COMM_WORLD);

		for(int i=0; i<594867; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(int i=0; i<24861; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<516; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<447; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

		for(int i=0; i<4882; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 1, MPI_INT, 0, MPI_COMM_WORLD);

		for(int i=0; i<572; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 1, MPI_INT, 0, MPI_COMM_WORLD);

		for(int i=0; i<52579; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 1, MPI_UNSIGNED_INT, 0, MPI_COMM_WORLD);

		for(int i=0; i<53682; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(int i=0; i<714; i++); /* Simulate compute time */

		f_offset = 0;
		for (int r=0; r<1024; r++){
			f_count=131072;
			f_offset += f_count * 1;
		MPI_File_write_at(fh[1], f_offset, buf, 131072, MPI_BYTE, status);

		}

		for(int i=0; i<55361; i++); /* Simulate compute time */

		MPI_File_close(&(fh[1]));

		for(int i=0; i<2223; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(int i=0; i<0; i++); /* Simulate compute time */

		for (int r=0; r<2; r++){
		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_LONG_LONG, MPI_SUM, MPI_COMM_WORLD);

		}

		for(int i=0; i<3399; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<347; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<406; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<301; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<331; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<283; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<318; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<290; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<305; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<467; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<300; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<294; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<3795; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(int i=0; i<0; i++); /* Simulate compute time */

		for (int r=0; r<2; r++){
		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_LONG_LONG, MPI_SUM, MPI_COMM_WORLD);

		}

		for(int i=0; i<962; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<384; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<333; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<335; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<289; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<345; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<306; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<497; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<309; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<346; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<306; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<352; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<0; i++); /* Simulate compute time */

		for (int r=0; r<2; r++){
		MPI_Barrier(MPI_COMM_WORLD);

		}

		for(int i=0; i<102501; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

	}

	if (myrank == 4) {
		for(int i=0; i<62096197; i++); /* Simulate compute time */

		MPI_Comm_size(MPI_COMM_WORLD, &size);

		for(int i=0; i<1739; i++); /* Simulate compute time */

		MPI_Comm_rank(MPI_COMM_WORLD, &rank);

		for(int i=0; i<13074; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 1, MPI_INT, 0, MPI_COMM_WORLD);

		for(int i=0; i<549147; i++); /* Simulate compute time */

		MPI_Comm_size(MPI_COMM_WORLD, &size);

		for(int i=0; i<13190; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 4, MPI_BYTE, 0, MPI_COMM_WORLD);

		for(int i=0; i<594867; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(int i=0; i<24861; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<516; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<447; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

		for(int i=0; i<4882; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 1, MPI_INT, 0, MPI_COMM_WORLD);

		for(int i=0; i<572; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 1, MPI_INT, 0, MPI_COMM_WORLD);

		for(int i=0; i<52579; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 1, MPI_UNSIGNED_INT, 0, MPI_COMM_WORLD);

		for(int i=0; i<53682; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(int i=0; i<714; i++); /* Simulate compute time */

		f_offset = 0;
		for (int r=0; r<1024; r++){
			f_count=131072;
			f_offset += f_count * 1;
		MPI_File_write_at(fh[1], f_offset, buf, 131072, MPI_BYTE, status);

		}

		for(int i=0; i<55361; i++); /* Simulate compute time */

		MPI_File_close(&(fh[1]));

		for(int i=0; i<2223; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(int i=0; i<0; i++); /* Simulate compute time */

		for (int r=0; r<2; r++){
		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_LONG_LONG, MPI_SUM, MPI_COMM_WORLD);

		}

		for(int i=0; i<3399; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<347; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<406; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<301; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<331; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<283; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<318; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<290; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<305; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<467; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<300; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<294; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<3795; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(int i=0; i<0; i++); /* Simulate compute time */

		for (int r=0; r<2; r++){
		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_LONG_LONG, MPI_SUM, MPI_COMM_WORLD);

		}

		for(int i=0; i<962; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<384; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<333; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<335; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<289; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<345; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<306; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<497; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<309; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<346; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<306; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<352; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<0; i++); /* Simulate compute time */

		for (int r=0; r<2; r++){
		MPI_Barrier(MPI_COMM_WORLD);

		}

		for(int i=0; i<102501; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

	}

	if (myrank == 5) {
		for(int i=0; i<62096197; i++); /* Simulate compute time */

		MPI_Comm_size(MPI_COMM_WORLD, &size);

		for(int i=0; i<1739; i++); /* Simulate compute time */

		MPI_Comm_rank(MPI_COMM_WORLD, &rank);

		for(int i=0; i<13074; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 1, MPI_INT, 0, MPI_COMM_WORLD);

		for(int i=0; i<549147; i++); /* Simulate compute time */

		MPI_Comm_size(MPI_COMM_WORLD, &size);

		for(int i=0; i<13190; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 4, MPI_BYTE, 0, MPI_COMM_WORLD);

		for(int i=0; i<594867; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(int i=0; i<24861; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<516; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<447; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

		for(int i=0; i<4882; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 1, MPI_INT, 0, MPI_COMM_WORLD);

		for(int i=0; i<572; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 1, MPI_INT, 0, MPI_COMM_WORLD);

		for(int i=0; i<52579; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 1, MPI_UNSIGNED_INT, 0, MPI_COMM_WORLD);

		for(int i=0; i<53682; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(int i=0; i<714; i++); /* Simulate compute time */

		f_offset = 0;
		for (int r=0; r<1024; r++){
			f_count=131072;
			f_offset += f_count * 1;
		MPI_File_write_at(fh[1], f_offset, buf, 131072, MPI_BYTE, status);

		}

		for(int i=0; i<55361; i++); /* Simulate compute time */

		MPI_File_close(&(fh[1]));

		for(int i=0; i<2223; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(int i=0; i<0; i++); /* Simulate compute time */

		for (int r=0; r<2; r++){
		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_LONG_LONG, MPI_SUM, MPI_COMM_WORLD);

		}

		for(int i=0; i<3399; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<347; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<406; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<301; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<331; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<283; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<318; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<290; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<305; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<467; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<300; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<294; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<3795; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(int i=0; i<0; i++); /* Simulate compute time */

		for (int r=0; r<2; r++){
		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_LONG_LONG, MPI_SUM, MPI_COMM_WORLD);

		}

		for(int i=0; i<962; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<384; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<333; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<335; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<289; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<345; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<306; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<497; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<309; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<346; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<306; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<352; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<0; i++); /* Simulate compute time */

		for (int r=0; r<2; r++){
		MPI_Barrier(MPI_COMM_WORLD);

		}

		for(int i=0; i<102501; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

	}

	if (myrank == 6) {
		for(int i=0; i<62096197; i++); /* Simulate compute time */

		MPI_Comm_size(MPI_COMM_WORLD, &size);

		for(int i=0; i<1739; i++); /* Simulate compute time */

		MPI_Comm_rank(MPI_COMM_WORLD, &rank);

		for(int i=0; i<13074; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 1, MPI_INT, 0, MPI_COMM_WORLD);

		for(int i=0; i<549147; i++); /* Simulate compute time */

		MPI_Comm_size(MPI_COMM_WORLD, &size);

		for(int i=0; i<13190; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 4, MPI_BYTE, 0, MPI_COMM_WORLD);

		for(int i=0; i<594867; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(int i=0; i<24861; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<516; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<447; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

		for(int i=0; i<4882; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 1, MPI_INT, 0, MPI_COMM_WORLD);

		for(int i=0; i<572; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 1, MPI_INT, 0, MPI_COMM_WORLD);

		for(int i=0; i<52579; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 1, MPI_UNSIGNED_INT, 0, MPI_COMM_WORLD);

		for(int i=0; i<53682; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(int i=0; i<714; i++); /* Simulate compute time */

		f_offset = 0;
		for (int r=0; r<1024; r++){
			f_count=131072;
			f_offset += f_count * 1;
		MPI_File_write_at(fh[1], f_offset, buf, 131072, MPI_BYTE, status);

		}

		for(int i=0; i<55361; i++); /* Simulate compute time */

		MPI_File_close(&(fh[1]));

		for(int i=0; i<2223; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(int i=0; i<0; i++); /* Simulate compute time */

		for (int r=0; r<2; r++){
		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_LONG_LONG, MPI_SUM, MPI_COMM_WORLD);

		}

		for(int i=0; i<3399; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<347; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<406; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<301; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<331; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<283; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<318; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<290; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<305; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<467; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<300; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<294; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<3795; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(int i=0; i<0; i++); /* Simulate compute time */

		for (int r=0; r<2; r++){
		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_LONG_LONG, MPI_SUM, MPI_COMM_WORLD);

		}

		for(int i=0; i<962; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<384; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<333; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<335; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<289; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<345; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<306; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<497; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<309; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<346; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<306; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<352; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<0; i++); /* Simulate compute time */

		for (int r=0; r<2; r++){
		MPI_Barrier(MPI_COMM_WORLD);

		}

		for(int i=0; i<102501; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

	}

	if (myrank == 7) {
		for(int i=0; i<62096197; i++); /* Simulate compute time */

		MPI_Comm_size(MPI_COMM_WORLD, &size);

		for(int i=0; i<1739; i++); /* Simulate compute time */

		MPI_Comm_rank(MPI_COMM_WORLD, &rank);

		for(int i=0; i<13074; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 1, MPI_INT, 0, MPI_COMM_WORLD);

		for(int i=0; i<549147; i++); /* Simulate compute time */

		MPI_Comm_size(MPI_COMM_WORLD, &size);

		for(int i=0; i<13190; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 4, MPI_BYTE, 0, MPI_COMM_WORLD);

		for(int i=0; i<594867; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(int i=0; i<24861; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<516; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<447; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

		for(int i=0; i<4882; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 1, MPI_INT, 0, MPI_COMM_WORLD);

		for(int i=0; i<572; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 1, MPI_INT, 0, MPI_COMM_WORLD);

		for(int i=0; i<52579; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 1, MPI_UNSIGNED_INT, 0, MPI_COMM_WORLD);

		for(int i=0; i<53682; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(int i=0; i<714; i++); /* Simulate compute time */

		f_offset = 0;
		for (int r=0; r<1024; r++){
			f_count=131072;
			f_offset += f_count * 1;
		MPI_File_write_at(fh[1], f_offset, buf, 131072, MPI_BYTE, status);

		}

		for(int i=0; i<55361; i++); /* Simulate compute time */

		MPI_File_close(&(fh[1]));

		for(int i=0; i<2223; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(int i=0; i<0; i++); /* Simulate compute time */

		for (int r=0; r<2; r++){
		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_LONG_LONG, MPI_SUM, MPI_COMM_WORLD);

		}

		for(int i=0; i<3399; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<347; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<406; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<301; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<331; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<283; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<318; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<290; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<305; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<467; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<300; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<294; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<3795; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(int i=0; i<0; i++); /* Simulate compute time */

		for (int r=0; r<2; r++){
		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_LONG_LONG, MPI_SUM, MPI_COMM_WORLD);

		}

		for(int i=0; i<962; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<384; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<333; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<335; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<289; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<345; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<306; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<497; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<309; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<346; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<306; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<352; i++); /* Simulate compute time */

		MPI_Reduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		for(int i=0; i<0; i++); /* Simulate compute time */

		for (int r=0; r<2; r++){
		MPI_Barrier(MPI_COMM_WORLD);

		}

		for(int i=0; i<102501; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

	}

