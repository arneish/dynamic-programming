#include <stdio.h>
#include<iostream>
#include <vector>
using namespace std;

/*0,1 Knapsack Problem 
    Implemented in C++ by Arneish Prateek
    Description: functions memo_V and table_V [N, W, ...] return the best value(V) from items 1,2,3...N that can be collected in a knapsack of capacity W
    DP Recurrence: V[i, W] = max ( V[i-1, W-w[i]] + values[i], V[i-1, W])
    DP implemented Top-Down using Memoization in function "memo_V()"
    DP implemented Bottom-Up using Table filling in function "table_V()"
*/
int memo_V(int N, int W, vector<vector<int>>&table, vector<int>&values, vector<int>&weights)
{
    if (table[N][W]!=-1)
        return table[N][W];
    if (N==0)
    {   
        table[0][W] = 0;
        return table[0][W];
    }
    if (W==0)
    {
        table[N][W]=0;
        return table[N][W];
    }
    if (weights[N]>W)
    {   
        return memo_V(N-1, W, table, values, weights);
    }
    return max(memo_V(N-1, W-weights[N], table, values, weights)+values[N], memo_V(N-1, W, table, values, weights));
}

int table_V(int N, int W, vector<vector<int>>&table, vector<int>&values, vector<int>&weights)
{
    /*for N=0, set table[N][W]=0*/
    for (int w=0; w<=N; w++)
        table[0][w]=0;
    /*for W=0, set table[N][W]=0*/
    for (int n=1; n<=N; n++)
        table[n][0]=0;
    for (int i=1; i<=N; i++)
    {
        for (int j=1; j<=W; j++)
        {
            if (weights[i]>j)
                table[i][j] = table[i-1][j];
            else
                table[i][j] = max(table[i-1][j-weights[i]]+values[i], table[i-1][j]);
        }
    }
    return table[N][W];
}

int main(int argc, char** argv) 
{
	int N, W; 
	cin>>N>>W;
	vector<int> values(N+1, -1);
	vector<int> weights(N+1, -1);
	for (int i=1; i<=N; i++)
	    cin>>values[i];
	for (int i=1; i<=N; i++)
        cin>>weights[i];
	vector<vector<int>> table (N+1, vector<int>(W+1, -1));
	table[N][W] = memo_V(N, W, table, values, weights);
    cout<<"DP Memoization:"<<table[N][W]<<"\n";
    table = vector<vector<int>> (N+1, vector<int>(W+1, -1));  
    cout<<"DP Table-filling:"<<table_V(N, W, table, values, weights)<<"\n";
	return 0;
}