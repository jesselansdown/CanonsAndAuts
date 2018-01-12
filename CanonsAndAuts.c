// To compile: gcc CanonsAndAuts.c -o CanonsAndAuts nauty.a
// To use: CanonsAndAuts graphfile.g6 colourings.txt

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

        DYNALLSTAT(int,lab,lab_sz);
        DYNALLSTAT(int,ptn,ptn_sz);
        DYNALLSTAT(int,orbits,orbits_sz);



options_sg.writeautoms = TRUE;
options_sg.cartesian = TRUE;
options_sg.linelength= 0;

        FILE *infile;
        int codetype;


        sparsegraph *g;

        infile = (FILE*) opengraphfile(graphfile,&codetype,0,1);
        g_sg =  (sparsegraph*) read_sg(infile,NULL);

        int n, m;
n = g_sg ->nv;



fprintf(stderr,"vertices %d\n", n);
m = SETWORDSNEEDED(n);


SG_DECL(csg);
options_sg.getcanon = TRUE;

nauty_check(WORDSIZE,m,n,NAUTYVERSIONID);






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

			        DYNALLOC1(int,lab,lab_sz,n,"malloc");
			        DYNALLOC1(int,ptn,ptn_sz,n,"malloc");
			        DYNALLOC1(int,orbits,orbits_sz,n,"malloc");


// !!!!!!!!!!! Here we need to set the lap and ptn up properly by reading in the values of the line

			        sparsenauty(g_sg,lab,ptn,orbits,&options_sg,&stats,&csg);



			//sortlists_sg(&csg);
			//putcanon_sg(stdout,lab,&csg,options_sg.linelength);


			//	DYNALLSTAT(int,workperm,workperm_sz);
			//    DYNALLOC1(int,workperm,workperm_sz,n+2,"putcanon");
			//    int i;
			//    for (i = 0; i < n; ++i) workperm[i] = lab[i];
			//    writeperm(stdout,workperm,TRUE,options_sg.linelength,n);

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



