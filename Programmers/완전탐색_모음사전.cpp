#include <string>
#include <vector>
#include <map>

using namespace std;

// EIO의 index를 구해보자.
// A로 시작하는 단어의 수 : 625 + 125 + 25 + 5 + 1 = 781
// E 1
// E A로 시작하는 단어의 수 : 125 + 25 + 5 + 1 = 156
// E E~ : 156
// E I 1
// E I A로 시작하는 단어의 수 : 25 + 5 + 1 = 31
// E I E ~ : 31
// E I I ~ : 31
// E I O : 1

// I로 해보자.
// A로 시작하는 단어 781
// E ~ 781
// I 1

map<char, int> m;

int solution(string word) {
    int answer = 0;
    
    // 위의 계산식을 바탕으로 index를 구해보자.
    // 첫 글자가 A라면 625 *  125 ... 를 거치지 않는다
    // 첫 글자가 E라면 한 번 거친다.
    // 첫 글자가 U 라면 4번 거친다.
    
    m['A']=0;
    m['E']=1;
    m['I']=2;
    m['O']=3;
    m['U']=4;
    
    int arr[5]={1, 5, 25, 125, 625};
    
    for(int i=0; i<word.size(); i++){
        int iter = m[word[i]]; 
        // i 번째 단어로 시작하는 단어 수를 구할 때 iter 만큼의 반복이 일어난다.
        // i가 0번째 자리라면 1 + 5 + 25 + 125 + 625를 해야 한다.
        // i가 1번째 자리라면 1 + 5 + 25 + 125
        // 단어 수를 세보자.
        int cur=0;
        for(int j=0; j<5-i; j++){
            cur+=arr[j];
        }
        answer += cur*iter;
        answer += 1;
    }
    
    
    return answer;
}