// To compile: gcc CanonsAndAuts.c -o CanonsAndAuts nauty.a
// To use: CanonsAndAuts graphfile.g6 colourings.txt

#include "gtools.h"
#include "nauty.h"
#include "nausparse.h"


static sparsegraph *g_sg;
static DEFAULTOPTIONS_SPARSEGRAPH(options_sg);
static statsblk stats;
static char *graphfile;

int main(argc,argv)
int argc;
char **argv;
{

        graphfile = (char*) argv[1];



//        DYNALLSTAT(int,lab,lab_sz);
//        DYNALLSTAT(int,ptn,ptn_sz);
        DYNALLSTAT(int,orbits,orbits_sz);



//options_sg.writeautoms = TRUE;
options_sg.cartesian = TRUE;
options_sg.linelength= 0;

        FILE *input;
        int codetype;


        sparsegraph *g;

        input = (FILE*) opengraphfile(graphfile,&codetype,0,1);
        g_sg =  (sparsegraph*) read_sg(input,NULL);

        int n, m;
n = g_sg ->nv;



fprintf(stderr,"vertices %d\n", n);
m = SETWORDSNEEDED(n);


SG_DECL(csg);
options_sg.getcanon = TRUE;
options_sg.defaultptn = FALSE;

nauty_check(WORDSIZE,m,n,NAUTYVERSIONID);


		int lab[n];
		int ptn[n];
		int btlst[n];

		int i;
		for (i = 0; i < n; ++i)
		{
			btlst[i]=0;
			ptn[i]=0;
			lab[i]=i;
			fprintf(stderr, "%d\n", i);
			fprintf(stderr, "%d\n", lab[i]);
			fprintf(stderr, "%d\n", ptn[i]);
		}
		
		//assign the initial partition, the btlst




		lab[0]= 4;
		btlst[4] =1;
		ptn[0]=1;
		lab[1]= 99;
		btlst[99] =1;
		ptn[1]=1;
		lab[2]= 8;
		btlst[8] =1;
		ptn[2]=0;

		int pos;
		pos = 3;
		int last;

// given an initial partion and lab, fills in the remainder.

		for ( i = 0; i < n; ++i)
		{
			if (btlst[i] !=1)
			{
				last = i;
				lab[pos] = i;
				ptn[pos++]=1;
			}
		}
		ptn[last]=0;


		for (i = 0; i < n; ++i)
		{
			fprintf(stderr, "%d ", i);
			fprintf(stderr, "%d ", lab[i]);
			fprintf(stderr, "%d\n", ptn[i]);
		}


//			        DYNALLOC1(int,lab,lab_sz,n,"malloc");
//			        DYNALLOC1(int,ptn,ptn_sz,n,"malloc");
			        DYNALLOC1(int,orbits,orbits_sz,n,"malloc");




// Here we read in a file. Later it will be the file containing the colourings, and will find auts and canons for all of them


	FILE *colourings;
	char *line = NULL;
	size_t len = 0;
	ssize_t size;
 
	colourings = fopen(argv[2], "r");
	if (colourings == NULL)
		exit(EXIT_FAILURE);




	while ((size = getline(&line, &len, colourings)) != -1) {
		printf("%s", line);




// !!!!!!!!!!! Here we need to set the lap and ptn up properly by reading in the values of the line

			        sparsenauty(g_sg,lab,ptn,orbits,&options_sg,&stats,&csg);



			//sortlists_sg(&csg);
			//putcanon_sg(stdout,lab,&csg,options_sg.linelength);


//				DYNALLSTAT(int,workperm,workperm_sz);
//			    DYNALLOC1(int,workperm,workperm_sz,n+2,"putcanon");
//			    for (i = 0; i < n; ++i) workperm[i] = lab[i];
//			    writeperm(stdout,workperm,TRUE,options_sg.linelength,n);

			    long zseed;

			               	zseed = hashgraph_sg(&csg,2922320L);
			                fprintf(stdout,"[%c%07lx",zseed);
			                zseed = hashgraph_sg(&csg,19883109L);
			                fprintf(stdout," %07lx",zseed);
			                zseed = hashgraph_sg(&csg,489317L);
			                fprintf(stdout," %07lx]\n",zseed);
			                /* print a hash function for the cannonical graph */

 

	}
 
	free(line);
	fclose(colourings);
	exit(EXIT_SUCCESS);

}



