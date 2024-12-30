#include <string>
#include <vector>

using namespace std;

int solution(vector<int> ingredient) {
    int answer = 0;
    vector<int> myStack;
    
    for (int i : ingredient) {
        myStack.push_back(i);
        
        if (myStack.size() >= 4) {
            int size = myStack.size();

            if (myStack[size - 4] == 1 &&
               myStack[size - 3] == 2 &&
               myStack[size - 2] == 3 &&
               myStack[size - 1] == 1 )
            {
                myStack.pop_back();
                myStack.pop_back();
                myStack.pop_back();
                myStack.pop_back();
                answer++;
            }
        }
    }
    return answer;
}