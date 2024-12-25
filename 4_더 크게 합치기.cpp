#include <string>
#include <vector>

using namespace std;

int solution(int a, int b) {
    
    string strA = to_string(a);
    string strB = to_string(b);

    string combinedA = strA + strB;
    string combinedB = strB + strA;
    
    int convertedA = stoi(combinedA);
    int convertedB = stoi(combinedB);
        
    if(convertedA > convertedB) {
        return convertedA;
    } else {
        return convertedB;
    }   
}