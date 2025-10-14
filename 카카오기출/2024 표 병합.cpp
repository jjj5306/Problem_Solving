#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>

using namespace std;
string board[51][51];
pair<int, int> par[51][51] = {};

// (r, c)의 최종 대표 셀(루트)을 찾아 반환하고, 경로를 압축함
pair<int, int> find(int r, int c)
{
    // 자기 자신이 부모이면, 스스로가 대표 셀임
    if (par[r][c].first == r && par[r][c].second == c)
    {
        return {r, c};
    }
    // 재귀적으로 부모를 찾아 올라가면서, 자신의 부모를 최종 대표 셀로 갱신 (경로 압축)
    return par[r][c] = find(par[r][c].first, par[r][c].second);
}

void update(string rs, string cs, string value)
{
    pair<int, int> root = find(stoi(rs), stoi(cs));
    board[root.first][root.second] = value;
}

void update(string value1, string value2)
{
    for (int r = 1; r < 51; r++)
    {
        for (int c = 1; c < 51; c++)
        {
            pair<int, int> root = find(r, c);
            if (board[root.first][root.second] == value1)
            {
                board[root.first][root.second] = value2;
            }
        }
    }
}

void merge(int r1, int c1, int r2, int c2)
{
    if (r1 == r2 && c1 == c2)
        return; // 같은 셀 병합은 무시

    // 각 셀의 최종 대표 셀을 찾음
    pair<int, int> root1 = find(r1, c1);
    pair<int, int> root2 = find(r2, c2);

    // 이미 같은 그룹이면 아무것도 하지 않음
    if (root1 == root2)
        return;

    int R1 = root1.first, C1 = root1.second;
    int R2 = root2.first, C2 = root2.second;

    // r1, c1을 가진 그룹 기준으로 병합
    // 만약 r1 그룹의 값이 비어있고 r2 그룹의 값은 있다면, r2 그룹의 값을 사용
    if (board[R1][C1].empty() && !board[R2][C2].empty())
    {
        board[R1][C1] = board[R2][C2];
    }

    // r2 그룹의 대표가 r1 그룹의 대표를 가리키도록 함
    par[R2][C2] = root1;
}

string print_(int r, int c)
{
    pair<int, int> root = find(r, c);
    string value = board[root.first][root.second];
    return value.empty() ? "EMPTY" : value;
}

void unmerge(int r, int c)
{
    pair<int, int> root = find(r, c);
    string root_value = board[root.first][root.second];

    vector<pair<int, int>> to_unmerge;
    for (int i = 1; i < 51; i++)
    {
        for (int j = 1; j < 51; j++)
        {
            if (find(i, j) == root)
            {
                to_unmerge.push_back({i, j});
            }
        }
    }

    for (auto &cell : to_unmerge)
    {
        par[cell.first][cell.second] = {cell.first, cell.second};
        board[cell.first][cell.second].clear();
    }
    board[r][c] = root_value;
}

vector<string> solution(vector<string> commands)
{
    vector<string> answer;
    for (int i = 0; i < 51; i++)
        for (int j = 0; j < 51; j++)
            par[i][j] = make_pair(i, j);

    for (auto command : commands)
    {
        vector<string> tokens;
        stringstream ss(command);
        string token;
        while (getline(ss, token, ' '))
        {
            tokens.push_back(token);
        }

        if (tokens[0] == "UPDATE")
        {
            if (tokens.size() == 4)
            {
                // UPDATE r c value
                update(tokens[1], tokens[2], tokens[3]);
            }
            else
            {
                // UPDATE value1 value2
                update(tokens[1], tokens[2]);

                // cout << command<<'\n';

                //                 for(int i=1; i<=4; i++){
                //                     for(int j=1; j<=4; j++)
                //                         cout << print_(i, j)<<' ';
                //                     cout<<'\n';
                //                 }
                //                 cout<<'\n';
            }
        }
        else if (tokens[0] == "MERGE")
        {
            merge(stoi(tokens[1]), stoi(tokens[2]), stoi(tokens[3]), stoi(tokens[4]));

            // cout << command<<'\n';
            // int a = stoi(tokens[1]), b = stoi(tokens[2]), c = stoi(tokens[3]), d = stoi(tokens[4]);
            // cout << a <<", "<<b<<" : "<<par[a][b].first<<' '<<par[a][b].second<<'\n';
            // cout << c <<", "<<d<<" : "<<par[c][d].first<<' '<<par[c][d].second<<'\n';
            // for(int i=1; i<=4; i++){
            //     for(int j=1; j<=4; j++)
            //         cout << print_(i, j)<<' ';
            //     cout<<'\n';
            // }
            // cout<<'\n';
        }
        else if (tokens[0] == "UNMERGE")
        {
            unmerge(stoi(tokens[1]), stoi(tokens[2]));

            // cout << command<<'\n';
            // int a = stoi(tokens[1]), b = stoi(tokens[2]);
            // cout << a <<", "<<b<<" : "<<par[a][b].first<<' '<<par[a][b].second<<'\n';
            // for(int i=1; i<=4; i++){
            //     for(int j=1; j<=4; j++)
            //         cout << par[i][j].first<<par[i][j].second<<' ';
            //     cout<<'\n';
            // }

            // for(int i=1; i<=4; i++){
            //     for(int j=1; j<=4; j++)
            //         cout << print_(i, j)<<' ';
            //     cout<<'\n';
            // }
            // cout<<'\n';
        }
        else
        {
            answer.push_back(print_(stoi(tokens[1]), stoi(tokens[2])));
        }
    }

    return answer;
}

/*
1. UPDATE r c value
    - par[r][c]={x, y} -> board[x][y]도 업데이트
2. UPDATE value1 value2
    - 모든 칸을 순회하며, par[r][c]={x, y} -> board[x][y]도 업데이트
3. MERGE r1 c1 r2 c2
    case 1) 둘 다 origin cell -> 값을 가지고 있으면 우선순위. 둘 다 있으면 r1 c1이 값을 가짐. par[r2][c2]={r1, c1} 과 같은 방식
    case 2) merged cell을 포함하는 경우 -> merged cell(r1, c1)이 주체가 된다면 그 셀을 부모로. / origin cell이 주체가 된다면 par[i][j] = {r1, c1}인 모든 i, j에 대해 par 업데이트
4. UNMERGE r c
    - par[i][j]=par[r][c]인 모든 i, j에 대해 par 제거
    - 모든 i, j는 값도 제거
5. PRINT r c
- par[r][c]={x, y} -> board[x][y]만 출력

merge해서 대표로 선택된 노드를 int par[r][c]로 저장.

*/