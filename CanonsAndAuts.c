//To do:

//Read in a graph in .g6 format
//optionally read in a file with colourings
//output a file with the canonical representations - particularly of a specific coloured section? and also a file with the automorphisms
//Put flags to only output one or the other, and do both by default
//output in the form of a list, readable by gap
//flags for choosing to 0 index the input and output respectively, default being to start at 1

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


        sparsegraph *g;  //Jesse - changed to sparsegraph for Traces

        infile = (FILE*) opengraphfile(graphfile,&codetype,0,1);
        g_sg =  (sparsegraph*) read_sg(infile,NULL);

        int n, m;
n = g_sg ->nv;



fprintf(stderr,"vertices %d\n", n);
m = SETWORDSNEEDED(n);


SG_DECL(csg);
options_sg.getcanon = TRUE;

nauty_check(WORDSIZE,m,n,NAUTYVERSIONID);

        DYNALLOC1(int,lab,lab_sz,n,"malloc");
        DYNALLOC1(int,ptn,ptn_sz,n,"malloc");
        DYNALLOC1(int,orbits,orbits_sz,n,"malloc");

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



