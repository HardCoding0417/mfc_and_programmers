#include <string>
#include <vector>

using namespace std;

int solution(string my_string, string is_prefix) {
    int answer = 0;
    if (is_prefix.size() <= my_string.size()) {
        if (my_string.compare(0, is_prefix.size(), is_prefix) ==0){
            answer = 1;
        }
    }
    return answer;
}