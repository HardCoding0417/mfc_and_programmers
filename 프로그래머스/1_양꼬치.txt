#include <string>
#include <vector>

using namespace std;

int solution(int n, int k) {
    // 양꼬치 n인분, 음료수 k개
    
    int freeDrink = n / 10;
    
    if (freeDrink > k) {
        freeDrink = k;
    }

    int DrinkCount = k - freeDrink;
    int lambCost = n * 12000;
    int DrinkCost = DrinkCount * 2000;
    
    return lambCost + DrinkCost;
}
