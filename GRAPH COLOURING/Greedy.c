#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int* Graph_Colouring(int n,int G[n][n],int *result);
double time_elapsed(struct timespec start, struct timespec end);

double time_elapsed(struct timespec start, struct timespec end)
{
	double t;
	t = (end.tv_sec - start.tv_sec);				   
	t += (end.tv_nsec - start.tv_nsec) * 0.000000001;  
	return t;
}

int* Graph_Colouring(int n,int G[n][n],int *result)
{    
    result[0] = 0;
    for (int u = 1; u < n; u++)
    {
        result[u] = -1;  // no color is assigned to u
    }
    int available[n];
    for (int clr = 0; clr < n; clr++)
    {
        available[clr] = 0;
    }
 
    for (int u = 1; u < n; u++)
    {
        for (int i = 0; i <n; i++)
        {
            if(G[i][u]==1)
            {
                if (result[i] != -1)
                {
                    available[result[i]] = 1;
                }
            }
           
        }
        int clr;
        for (clr = 0; clr < n; clr++)
        {
            if (available[clr] == 0)
            {
                break;
            }
        }
 
        result[u] = clr;
 
      // Resetting the value of available for next iteration
        for (int i = 0; i <n; i++)
        {
            if(G[i][u]==1)
            {
                if (result[i] != -1)
                {
                    available[result[i]] = 0;
                }
            }          
        }
    }
    return result;
}

int main() 
{
    // n is no of vertices.
    // e is no of edges.
    struct timespec start;
	struct timespec end;
    int n,e;
    printf("Enter the number of vertices and edges :-\n");
    scanf("%d %d",&n,&e);
    int G[n][n];
    printf("Enter edge in this format : \" u v \" where u and v are vertices and u is connected to v:-\n");
    for(int i = 0; i < e; i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        G[u][v] = 1;
        G[v][u] = 1;
    }
    int res[n];
    int *result;
    srand(time(0));
    clock_gettime(CLOCK_REALTIME, &start);
    result = Graph_Colouring(n,G,res);
    clock_gettime(CLOCK_REALTIME, &end);
 
    printf("The pattern of colouring is:-\n");
    for (int u = 0; u < n; u++)
    {
        printf("Vertex %d ---> Color %d \n",u,result[u]);
    }
    int max = -1;
    for(int i = 0; i < n; i++)
    {
        if(result[i]>max)
        {
            max = result[i];
        }
    }
    printf("Chromatic Number of the graph is %d\n",max + 1);
    printf("Time : %lf ns\n", time_elapsed(start, end)*1000000000);
        return 0;
}

/*
0 1
0 2
0 3
0 4
0 5
0 6
2 3
1 7
2 7
3 7
4 7
8 7
9 7
5 8
5 6
6 9
8 9
6 8
5 9
*/

/* 30 40

0 1
0 2
2 3
1 4
4 6
1 5
1 3
3 5
6 5
5 7
5 27
7 27
27 26
26 28
26 29
26 24
24 25
5 8
8 9
9 5
9 16
16 15
15 11
11 3
11 12
11 13
11 14
13 14
14 17
17 18
18 19
19 9
14 22
22 23
9 21
21 20
9 20
21 23
23 24
8 10
*/