#include <string>
#include <vector>
#include <cmath>
using namespace std;

long long solution(int r1, int r2) {
    long long answer = 0;

    for (int i = 1; i <= r2; i++) {
        int s = 0;
        if (i <= r1) {
            s = ceil(sqrt(1LL * r1 * r1 - 1LL * i * i));
        }

        int e = floor(sqrt(1LL * r2 * r2 - 1LL * i * i));
        answer += e - s + 1;
    }

    return answer * 4;
}