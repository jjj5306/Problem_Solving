#include <string>
#include <vector>
#include <iostream>

using namespace std;

int dp[510][510];

int solution(vector<vector<int>> triangle)
{
    int answer = 0;

    dp[0][0] = triangle[0][0];
    // i행 j열 -> i-1행 j-1, j열에서 파생된 것
    for (int i = 1; i < triangle.size(); i++)
    {
        for (int j = 0; j < triangle[i].size(); j++)
        {
            if (j - 1 < 0)
                dp[i][j] = dp[i - 1][j];
            else
                dp[i][j] = max(dp[i - 1][j - 1], dp[i - 1][j]);
            dp[i][j] += triangle[i][j];
        }
    }

    for (int i = 0; i < triangle[triangle.size() - 1].size(); i++)
        answer = max(answer, dp[triangle.size() - 1][i]);
    // for(int i=0; i<triangle.size(); i++){
    //     for(int j=0; j<triangle[i].size(); j++)
    //         cout<<dp[i][j]<<' ';
    //     cout<<'\n';
    // }

    return answer;
}