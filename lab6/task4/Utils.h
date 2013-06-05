/*Utils - Helper Functions for supporting pipes*/

/*This function receives the number of required pipes and 
 * returns an array of pipes.*/
int **createPipes(int nPipes);

/*This function receives an array of pipes and an integer 
 * indicating the size of the array. The function releases 
 * all memory dedicated to the pipes.*/

void releasePipes(int **pipes, int nPipes);
/*This function receives an array of pipes and a pointer to 
 * a cmdLine structure. It returns the pipe which feeds the 
 * process associated with the command.
 * For example, the feed pipe of process tee in pipeline 
 * "cat | tee | more" is the first pipe. If the command does 
 * not have a feed pipe (as with cat in our example), the 
 * function returns NULL.
 * */
int *feedPipe(int **pipes, cmdLine *pCmdLine);

/*This function receives an array of pipes and a pointer to a
 * cmdLine structure. It returns the pipe which is the sink of the associated command.
 * For example, the sink pipe of process tee in pipeline 
 * "cat | tee | more" is the second pipe. If the command does 
 * not have a sink pipe (as with more in our example), 
 * the function returns NULL.*/
int *sinkPipe(int **pipes, cmdLine *pCmdLine);
