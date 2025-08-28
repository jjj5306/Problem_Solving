#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

bool func(int st, int en, vector<string> &phone_book)
{
    // st index의 문자가 en index에 대해 접두사인지 판단
    bool rt = false; // 접두사면 false를 리턴해야 함

    if (phone_book[st].length() > phone_book[en].length())
    {
        rt = true;
    }
    else
    {
        for (int i = 0; i < phone_book[st].length(); i++)
            if (phone_book[st][i] != phone_book[en][i])
            {
                rt = true;
                break;
            }
    }
    return rt;
}

bool solution(vector<string> phone_book)
{
    bool answer = true; // true면 접두사가 없는거임

    // 하나가 접두사가 되려면 정렬했을 때 붙어있을 수 밖에 없음
    // 즉, i / i+1 번째를 비교하면 됨

    sort(phone_book.begin(), phone_book.end());

    for (int i = 0; i < phone_book.size() - 1; i++)
    {
        answer = func(i, i + 1, phone_book);
        if (!answer)
            break;
    }

    return answer;
}