#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <deque>
bool cur_possible=true;

using namespace std;

void is_possible(int start, int end, deque <int> &bin_num){
    // 함수 정의 : start~end에서 루트, 왼쪽 자식, 오른쪽 자식을 보고 가능한지 판단
    if(!cur_possible) return;
    if(start >= end) return;

    // root : (end+start)/2
    // left_root : ((root-1)+start)/2
    // right_root : (end+(root+1))/2
    int root = (end+start)/2;
    int left_root = ((root-1)+start)/2, right_root = (end+(root+1))/2;
    if(bin_num[root] == 0 && (bin_num[left_root] == 1 || bin_num[right_root]==1)){
        cur_possible=false;
        return;
    }
    is_possible(start, root-1, bin_num);
    if(!cur_possible) return;
    is_possible(root+1, end, bin_num);
    if(!cur_possible) return;
}


vector<int> solution(vector<long long> numbers) {
    vector<int> answer;
    /*
    1. 수를 2진수로 표현
    2. 2진수 앞에 0을 패딩해서 2^h-1로 만들어, 포화트리의 각 노드에 대응되도록 수를 맞춘다.
    3. 이진수는 노드 방문 순서이고, inorder 방식이다. (왼쪽-부모-오른쪽)
    4. 42를 예시로 보면, 0101010이다. 루트 노드는 idx 3이고, 루트 노드의 왼쪽 자식은 0~2, 오른쪽 자식은 4~6이다. 또 거기에서도 루트는 중간이다. 
    5. 따라서 재귀로 탐색하며, 자식이 0인데 부모가 1인 경우라면 이진트리로 표현할 수 없는 경우이다.
    */
    for(int cur=0; cur<numbers.size(); cur++){
        // 2진수로 표현 및 0 패딩
        bool is_find=false;
        deque <int> bin_num;
        for(int i=63; i>=0; i--){
            if((numbers[cur]>>i&1) == 1) is_find=true;
            if(is_find) bin_num.push_back((numbers[cur]>>i&1));
        }

        // 0를 몇 개 패딩해야할지 찾아야함.
        // 2^h-1 >= bin_num.size -> break
        int h=1;
        while(1){
            if((1LL << h)-1 >= bin_num.size()) break;
            h++;
        }
        int target_len = (1LL<<h)-1;
        while(target_len > bin_num.size())
            bin_num.push_front(0);
        
        // 이 2진수가 트리로 표현이 가능한지 체크
        cur_possible=true;
        is_possible(0, bin_num.size()-1, bin_num);
        answer.push_back(cur_possible);
    }

    
    return answer;
}

