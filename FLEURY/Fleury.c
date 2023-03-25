// Fleury's algorithm
// Input: a connected graph G
// Output: a Eulerian cycle in G
// Note: G is assumed to be connected

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 8

int start(int graph[MAX][MAX]);
int dfs(int prev,int start,int visited[MAX],int temp[MAX][MAX]);
int isBridge(int start,int end,int temp[MAX][MAX]);
int edgeCount(int temp[MAX][MAX]);
int fleury(int start,int temp[MAX][MAX]);


int start(int graph[MAX][MAX])
{
    for(int i = 0;i < MAX;i++)
    {
        int deg = 0;
        for(int j = 0;j < MAX;j++)
        {
            if(graph[i][j] == 1)
            {
                deg++;
            }
        }
        if(deg % 2 != 0)
        {
            return i;
        }
    }
    return 0;
}

int dfs(int prev,int start,int visited[MAX],int temp[MAX][MAX])
{
    int count = 1;
    visited[start] = 1;
    for(int i = 0;i < MAX;i++)
    {
        if(prev != i)
        {
            if(!visited[i])
            {
                if(temp[start][i] == 1)
                {
                    count += dfs(start,i,visited,temp);
                }
            }
        }
    }
    return count;
}

int isBridge(int start,int end,int temp[MAX][MAX])
{
    int deg = 0;
    for(int i = 0;i < MAX;i++)
    {
        if(temp[end][i])
        {
            deg++;
        }
    }
    if(deg > 1)
    {
        return 0;
    }
    return 1;
}

int edgeCount(int temp[MAX][MAX]) 
{
   int count = 0;
   for(int i = 0; i < MAX; i++)
   {
        for(int j = i; j < MAX; j++)
        {
            if(temp[i][j])
            {
                count++;
            }
        }
   }
    return count;
}

int fleury(int start,int temp[MAX][MAX])
{
    int n_edges = edgeCount(temp);
    static int ver = MAX;
    int v = 0;
    for(int v = 0;v < MAX;v++)
    {
        if(temp[start][v])
        {
            int visited[MAX] = {0};
            if(isBridge(start,v,temp))
            {
                ver--;
            }
            int count = dfs(start,v,visited,temp);
            if(abs(count - ver) <= 2)
            {
                printf("%d --> %d , ",start,v);
                if(isBridge(v,start,temp))
                {
                    ver--;
                }
            temp[start][v] = temp[v][start] = 0;
            n_edges--;
            fleury(v,temp);
            }
        }
    }
    return v;
}

int main()
{
    // int graph[MAX][MAX] = 
    // {
    //     {0,1,1,0,0,0,0,0},
    //     {1,0,1,1,0,0,0,0},
    //     {1,1,0,1,1,0,0,0},
    //     {0,1,1,0,1,1,0,0},
    //     {0,0,1,1,0,1,1,0},
    //     {0,0,0,1,1,0,1,1},
    //     {0,0,0,0,1,1,0,1},
    //     {0,0,0,0,0,1,1,0}
    // };
    
    int graph[MAX][MAX] = 
    {
        {0,1,0,1,1,1,0,0},
        {1,0,1,0,0,0,1,1},
        {0,1,0,1,0,0,1,1},
        {1,0,1,0,1,1,0,0},
        {1,0,0,1,0,0,0,0},
        {1,0,0,1,0,0,0,0},
        {0,1,1,0,0,0,0,0},
        {0,1,1,0,0,0,0,0}
    };
    int temp[MAX][MAX];
    for(int i = 0;i < MAX;i++)
    {
        for(int j = 0;j < MAX;j++)
        {
            temp[i][j] = graph[i][j];
        }
    }
    int s = start(graph);
    int end = fleury(s,temp);
    if(s == end)
    {
        printf("\nTherefore, Euler's cycle exists");
    }
    else
    {
        printf("\nTherefore, Euler's cycle does not exist");
    }
    return 0;
}
