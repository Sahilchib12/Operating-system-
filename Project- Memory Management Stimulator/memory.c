#include<stdio.h>
#include<stdlib.h>

typedef struct process{
	int psize;
	int pflag;
}process;

typedef struct block{
	int bsize;
	int bflag;
}block;

void accept(process p[],block b[],int *n,int *m){
	
	int i,j;
	
	printf("\n Enter no. of blocks : ");
	scanf("%d",m);
	for(i=0;i<*m;i++){
		printf(" Enter size of block[%d] : ",i);
		scanf("%d",&b[i].bsize);
	}

	printf("\n Enter no. of processes : ");
	scanf("%d",n);
	for(i=0;i<*n;i++){
		printf(" Enter size of block[%d] : ",i);
		scanf("%d",&p[i].psize);
	}

}
void re_init(process p[],block b[],int n,int m){
	int i;
	for(i=0;i<n;i++)
		p[i].pflag=0;
	for(i=0;i<m;i++)
		b[i].bflag=0;
}

void first_fit(process p[],block b[],int n,int m){

	int i,j,in_frag=0,ex_frag=0;
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			if(p[i].psize <= b[j].bsize && b[j].bflag == 0 && p[i].pflag == 0){
				b[j].bflag = p[i].pflag = 1;
				in_frag += b[j].bsize - p[i].psize;
				printf("\n P[%d]\t-\tB[%d]",i,j);
				break;
			}
		}
		if(p[i].pflag == 0)
			printf("\n P[%d]\t-\tUnassigned",i);
	}
	printf("\n\n Total internal fragmentation : %d",in_frag );
	for(j=0;j<m;j++){
		if(b[j].bflag == 0)
			ex_frag+=b[j].bsize;
	}
	printf("\n Total external fragmentation : %d",ex_frag );
}

void best_fit(process p[],block b[],int n,int m){
	int i,j,min_frag,in_frag=0,ex_frag=0,id;
	for(i=0;i<n;i++){
		min_frag = 9999;
		id=9999;
		for(j=0;j<m;j++){
			if(p[i].psize <= b[j].bsize && b[j].bflag == 0 && min_frag > (b[j].bsize - p[i].psize)){
					min_frag = b[j].bsize - p[i].psize;
					id = j;
			}
		}
		if(min_frag != 9999){
				b[id].bflag = p[i].pflag = 1;
				in_frag += b[id].bsize - p[i].psize;
				printf("\n P[%d]\t-\tB[%d]",i,id);
		}
		if(p[i].pflag == 0)
			printf("\n P[%d]\t-\tUnassigned",i);
	}
	
	printf("\n\n Total internal fragmentation : %d",in_frag );
	for(j=0;j<m;j++){
		if(b[j].bflag == 0)
			ex_frag+=b[j].bsize;
	}
	printf("\n Total external fragmentation : %d",ex_frag );
	
	
}

void worst_fit(process p[],block b[],int n,int m){
	int i,j,max_frag,in_frag=0,ex_frag=0,id;
	
	for(i=0;i<n;i++){
		max_frag = -1;
		id=9999;
		for(j=0;j<m;j++){
			if(p[i].psize <= b[j].bsize && b[j].bflag == 0 && max_frag < (b[j].bsize - p[i].psize)){
					max_frag = b[j].bsize - p[i].psize;
					id = j;
			}
		}
		if(max_frag != -1){
				b[id].bflag = p[i].pflag = 1;
				in_frag += b[id].bsize - p[i].psize;
				printf("\n P[%d]\t-\tB[%d]",i,id);
		}
		if(p[i].pflag == 0)
			printf("\n P[%d]\t-\tUnassigned",i);
	}
	
	printf("\n\n Total internal fragmentation : %d",in_frag );
	for(j=0;j<m;j++){
		if(b[j].bflag == 0)
			ex_frag+=b[j].bsize;
	}
	printf("\n Total external fragmentation : %d",ex_frag );
	
	
}

void next_fit(process p[],block b[],int n,int m){

	int i,j,in_frag=0,ex_frag=0,loc;
	printf("\n Enter block no. to begin allocation : ");
	scanf("%d",&loc);
	for(i=0;i<n;i++){
		for(j=loc;j<m;j++){
			if(p[i].psize <= b[j].bsize && b[j].bflag == 0 && p[i].pflag == 0){
				b[j].bflag = p[i].pflag = 1;
				in_frag += b[j].bsize - p[i].psize;
				printf("\n P[%d]\t-\tB[%d]",i,j);
				if((j+1) == m)
					loc = 0;
				else
					loc = j+1;
				break;
			}

		}
		if(p[i].pflag == 0)
			printf("\n P[%d]\t-\tUnassigned",i);
	}
	printf("\n\n Total internal fragmentation : %d",in_frag );
	for(j=0;j<m;j++){
		if(b[j].bflag == 0)
			ex_frag+=b[j].bsize;
	}
	printf("\n Total external fragmentation : %d",ex_frag );
}


int main(){

	int ch,n=0,m=0;
	process p[10];
	block b[10];
	do{
		printf("\n\n SIMULATION OF FIXED PARTITIONING MEMORY MANAGEMENT SCHEMES");
		printf("\n\n Options:");
		printf("\n 0. Accept");
		printf("\n 1. First Fit");
		printf("\n 2. Best Fit");
		printf("\n 3. Next Fit");
		printf("\n 4. Worst Fit");
		printf("\n 5. Exit");
		printf("\n Select : ");
		scanf("%d",&ch);
		switch(ch){
			case 0:
				accept(p,b,&n,&m);
				break;
			case 1:
				re_init(p,b,n,m);
				first_fit(p,b,n,m);
				break;
			case 2:
				re_init(p,b,n,m);
				best_fit(p,b,n,m);
				break;
			case 3:
				re_init(p,b,n,m);
				next_fit(p,b,n,m);
				break;
			case 4:
				re_init(p,b,n,m);
				worst_fit(p,b,n,m);
				break;
			case 5:exit(0);
			default:
				printf("\n Invalid selection.");
		}
	}while(ch != 5);
	getch();
	return 0;
}