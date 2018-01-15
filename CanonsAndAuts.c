// Jesse Lansdown

// To compile: gcc CanonsAndAuts.c -o CanonsAndAuts nauty.a
// To use: CanonsAndAuts graphfile.g6 colourings.txt

#include "gtools.h"
#include "nauty.h"
#include "nausparse.h"
#include <stdbool.h>

static sparsegraph *g_sg;
static DEFAULTOPTIONS_SPARSEGRAPH(options_sg);
static statsblk stats;
static char *graphfile;

int main(argc,argv)
int argc;
char **argv;
{

	bool silent;
	silent = FALSE;

    graphfile = (char*) argv[1];

    DYNALLSTAT(int,orbits,orbits_sz);

	options_sg.writeautoms = TRUE;
	options_sg.cartesian = TRUE;
	options_sg.linelength= 0;		// Setting to 0 turns the line breaks off.
	options_sg.getcanon = TRUE;
	options_sg.defaultptn = FALSE;		// Allow user defined partitons to be used.

    FILE *input;
    int codetype;

    sparsegraph *g;

    input = (FILE*) opengraphfile(graphfile,&codetype,0,1);
    g_sg =  (sparsegraph*) read_sg(input,NULL);

    int n, m;
	n = g_sg ->nv;
	m = SETWORDSNEEDED(n);
	nauty_check(WORDSIZE,m,n,NAUTYVERSIONID);

	SG_DECL(csg);

	int lab[n];
	int ptn[n];
	int btlst[n];

	int i;
	for (i = 0; i < n; ++i)
	{
		btlst[i]=0;		// Initially set the bit list to all 0
		ptn[i]=0;		// Set initial ptn to all 0
		lab[i]=i;		// Set initial lab to be [0 .. n-1]
	}
		
	DYNALLOC1(int,orbits,orbits_sz,n,"malloc"); // set up orbits.

	int pos;  // This will mark the position in lab to resume from
	int last;	// This will mark the last entry added to ptn, so that it can be set to 0


	FILE *colourings;
	char *line = NULL;
	size_t len = 0;
	ssize_t size;
 
 	if (argc == 3){
		colourings = fopen(argv[2], "r"); 	// If a second argument is given, it is a file containing partions	
	}
 	else{
 		colourings = stdin;		// If no second argument is given, read partions from stdin
	}
	if (colourings == NULL)
		exit(EXIT_FAILURE);

	int val;
	int count;
	count = 0;

	while ((size = getline(&line, &len, colourings)) != -1) {
//		printf("%s", line);

		count++;
		if (silent!=TRUE)
			fprintf(stdout, "%d\n", count);

		for (i = 0; i < n; ++i)
		{
			btlst[i]=0;		// Reset the bitlist to 0 at the start of each iteration
			ptn[i]=0;		// Rest the ptn and lab
			lab[i]=i;
			// fprintf(stderr, "%d\n", i);
			// fprintf(stderr, "%d\n", lab[i]);
			// fprintf(stderr, "%d\n", ptn[i]);
		}


		i=0;
		while (sscanf(line, "%d", &val) == 1) {
			lab[i]=val;		// Set the value of lab to be the value read in from the line
			btlst[val] =1;		// Indicate that this value has been considered by setting the bitlist entry to 1
			ptn[i++]=1;		// Set the corresponding ptn entry to 1 to indicate a continuation of the partition
		    line = strchr(line, ' ');		// move to the next integer in the line
		    if (!line) break;
		    line++;
		}
		ptn[i-1]=0;		// set the last ptn entry to 0 to indicate th end of the partion
		pos=i;		// Set pos to the value immeadiately after the last entry of lab, to complete the partition


		for ( i = 0; i < n; ++i)
		{
			if (btlst[i] !=1)	// Loop through, putting everything in the second half of the partition if the bitlist indicates it hasn't yet been considered
			{
				last = i;
				lab[pos] = i;
				ptn[pos++]=1;
			}
		}
		ptn[last]=0;

		if (silent!=TRUE)
			fprintf(stdout, "About to call nauty!\n");

		sparsenauty(g_sg,lab,ptn,orbits,&options_sg,&stats,&csg);

		if (silent!=TRUE)
			fprintf(stdout, "Finished nauty!\n");

			sortlists_sg(&csg);
//			putcanon_sg(stdout,lab,&csg,options_sg.linelength);

//				fprintf(stdout,"%d %d\n",lab[0], ptn[0]);
//				DYNALLSTAT(int,workperm,workperm_sz);
//			    DYNALLOC1(int,workperm,workperm_sz,n+2,"putcanon");
//			    for (i = 0; i < n; ++i) workperm[i] = lab[i];
//			    writeperm(stdout,workperm,TRUE,options_sg.linelength,n);


//                putptn(stdout,lab,ptn,0,options_sg.linelength,n);

		long zseed;

		if (silent!=TRUE)
			fprintf(stdout, "Canonical hash code:\n");

			               	zseed = hashgraph_sg(&csg,2922320L);	// as done in dreadnaut.c - replace with canonically labelled partion once able
			                fprintf(stdout,"[%c%07lx",zseed);
			                zseed = hashgraph_sg(&csg,19883109L);
			                fprintf(stdout," %07lx",zseed);
			                zseed = hashgraph_sg(&csg,489317L);
			                fprintf(stdout," %07lx]\n",zseed);
			                /* print a hash function for the cannonical graph */


		line = NULL;	// Debug: Why is this needed? Gives segfault otherwise

		if (silent!=TRUE)
			fprintf(stdout, "\n" );

	}

	free(line);
	fclose(colourings);
	exit(EXIT_SUCCESS);

}



