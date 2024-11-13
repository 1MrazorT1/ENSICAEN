#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


int valgrind_test(char* testFunction, char* parameters, char* comment){
    char bashcommand[200];
    sprintf(bashcommand,"sh bashscript.sh %s %s",testFunction, parameters);

    char logvalgrind[100];
    sprintf(logvalgrind, "log-%s.out",testFunction);

    char scorevalgrind[100];
    sprintf(scorevalgrind, "score-%s.out",testFunction);

    printf("** Check the memory with valgrind: %s %s [%s]\n",testFunction,parameters,comment);
    //printf("%s\n",bashcommand);
    int status = system(bashcommand);
    if (status == -1) {
        printf("Error while executing \"%s\".\n",bashcommand);
        printf("Test failed.\n");
        return 0;
    }
    FILE* data = fopen(scorevalgrind,"r");
    if(data==NULL){
        printf("Fail to open file %s during the test.\n",scorevalgrind);
        printf("Test failed.\n");
        return 0;
    }
    if(fscanf(data,"%d",&status)==EOF)
    {
        printf("Fail to read in file %s during the test.\n",scorevalgrind);
        printf("Test failed.\n");
        return 0;
    }
    fclose(data);
    if (status != 0) {
        printf("Valgrind has detected memory errors. See %s for details. \n",logvalgrind);
        printf("Test failed.\n");
        return 0;
    }
    sprintf(bashcommand,"rm -f %s",logvalgrind);
    system(bashcommand);
    sprintf(bashcommand,"rm -f %s",scorevalgrind);
    system(bashcommand);
    printf("Passed.\n");
    return 1;
}

