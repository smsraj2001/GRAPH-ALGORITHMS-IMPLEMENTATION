#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double time_elapsed(struct timespec start, struct timespec end)
{
	double t;
	t = (end.tv_sec - start.tv_sec);				   
	t += (end.tv_nsec - start.tv_nsec) * 0.000000001;  
	return t;
}

int colour(int pcolour,int n,int G[n][n],int cor[n],int coloring)
{
    for(int j = 0; j < n; j++)
    {
        if(G[pcolour][j])
        {
            if(cor[j] == coloring)
            {
                return coloring + 1;
            }
        }
    }
    return coloring;
}

void find_edge(int n,int G[n][n],int find_edges[n])
{
    for(int a = 0; a < n; a++)
    {
        for(int k = 0; k < n; k++)
        {
            if(G[a][k] == 1)
            {
                find_edges[a]++;
            }
        }
    }
}
void welshPowell(int n,int G[n][n],int find_edges[n],int coloring,int cor[n]){
    int v, aux;
    do  
    {
        aux = 0;
        for(int a = 0; a < n; a++)
        {
            if(cor[a] == 0) 
            {
                if(find_edges[a] > aux) 
                {
                    v = a;
                    aux = find_edges[a];
                }
            }
        }
        if(cor[v] == 0)
        {
            cor[v] = coloring;
        }
        else 
        {
            break;
        }
        for(int y = 0; y < n; y++)
        {
            if(G[v][y] == 0 && cor[y] == 0)
            {
                cor[y] = colour(y,n,G,cor,coloring);
            }
        }
        coloring++;
    } while(1);
}


int main()
{  
    struct timespec start;
	struct timespec end;
    int n,e;
    int max = -1;
    printf("Enter the number of vertices and edges :-\n");
    scanf("%d %d",&n,&e);
    int G[n][n];
    int find_edges[n];
    int coloring = 1;
    int cor[n];
    printf("Enter edge in this format : \" u v \" where u and v are vertices and u is connected to v:-\n");
    for(int i = 0; i < e; i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        G[u][v] = 1;
        G[v][u] = 1;
    }
    for(int g = 0; g < n; g++)
        cor[g] = find_edges[g] = 0;
    find_edge(n,G,find_edges); 
    
    srand(time(0));
    clock_gettime(CLOCK_REALTIME, &start);
    welshPowell(n,G,find_edges,coloring,cor);
    clock_gettime(CLOCK_REALTIME, &end);
 
    printf("The pattern of colouring is:-\n");
    for (int u = 0; u < n; u++)
    {
        printf("Vertex %d ---> Color %d \n",u,cor[u]);
    }
    for(int i = 0; i < n; i++)
    {
        if(cor[i]>max)
        {
            max = cor[i];
        }
    }
    printf("Chromatic Number of the graph is %d\n",max);
    printf("Time : %lf ns\n", time_elapsed(start, end)*1000000000);

    return 0;
}