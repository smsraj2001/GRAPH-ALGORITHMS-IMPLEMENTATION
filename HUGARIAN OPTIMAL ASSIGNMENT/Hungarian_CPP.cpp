// Hungariam method to find optimal assignment for m job and m workers
// Salary expectations and proficiency in executing a job of every worker is taken as input.
// It is not mandatory that every worker is suitable for available vacant posts.

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
using namespace std;

int hungarian(vector<vector<int>> &cost, vector<int> &row, vector<int> &col, vector<int> &path, int n)
{
    vector<int> u(n + 1), v(n + 1), p(n + 1), way(n + 1);
    for (int i = 1; i <= n; i++)
    {
        p[0] = i;
        int j0 = 0;
        vector<int> minv(n + 1, INT_MAX);
        vector<bool> used(n + 1, false);
        do
        {
            used[j0] = true;
            int i0 = p[j0], delta = INT_MAX, j1;
            for (int j = 1; j <= n; j++)
            {
                if (!used[j])
                {
                    int cur = cost[i0][j] - u[i0] - v[j];
                    if (cur < minv[j])
                    {
                        minv[j] = cur;
                        way[j] = j0;
                    }
                    if (minv[j] < delta)
                    {
                        delta = minv[j];
                        j1 = j;
                    }
                }
            }
            for (int j = 0; j <= n; j++)
            {
                if (used[j])
                {
                    u[p[j]] += delta;
                    v[j] -= delta;
                }
                else
                {
                    minv[j] -= delta;
                }
            }
            j0 = j1;
        } while (p[j0] != 0);
        do
        {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }
    for (int j = 1; j <= n; j++)
    {
        row[p[j]] = j;
        col[j] = p[j];
    }
    return -v[0];
}

int main()
{
    int n;
    cout << "Enter number of workers and jobs: ";
    cin >> n;
    vector<vector<int>> cost(n + 1, vector<int>(n + 1));
    cout << "Enter cost matrix: " << endl;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> cost[i][j];
        }
    }
    vector<int> row(n + 1), col(n + 1), path(n + 1);
    int ans = hungarian(cost, row, col, path, n);
    cout << "Optimal assignment: " << endl;
    for (int i = 1; i <= n; i++)
    {
        cout << "Worker " << i << " is assigned to job " << row[i] << endl;
    }
    cout << "Total cost: " << ans << endl;
    return 0;
}