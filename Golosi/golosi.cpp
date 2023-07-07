/*
* Solucion aportada por el profesor de la FdI (UCM):
* Solution given by FdI's (UCM) professor:
*   ANTONIO ALEJANDRO SANCHEZ RUIZ-GRANADOS
*/
#include <iostream>
#include <vector>

using namespace std;

// Pre: 0<=cal.size()=nut.size()
int max_nutr_val(const vector<int>& cal, const vector<int>& nut, int threshold) {
    int a = 0, b = 0;                   // v[a..b-1] is the current subvector
    int currentCal = 0, currentNut = 0;   // calories and nutritional value in v[a..b-1]
    int bestNut = 0;                      // best nutritional value of valid subvector in v[0..b-1]

    // Inv: 0<=a<=b<=n and currentCal = sum(cal, a, b) and currentNut = sum(nut, a, b)
    //  and bestNut = Max i, j: 0<=i<=j<=b and sum(cal, i, j) <= threshold: sum(nut, i, j)
    // T: 2*n-a-b
    while (b < cal.size()) {
        if (currentCal + cal[b] <= threshold) {
            currentCal += cal[b];
            currentNut += nut[b];
            ++b;
            bestNut = max(bestNut, currentNut);
        }
        else {
            currentCal -= cal[a];
            currentNut -= nut[a];
            ++a;
        }
    }
    return bestNut;
}
// Post: bestNut = Max i, j: 0<=i<=j<=cal.size() and sum(cal, i, j) <= threshold: sum(nut, i, j)
// sum(v, i, j) = Sum k: i<=k<j: v[k] 

// Complexity: O(n) with n = cal.size() because a and b can only increment n times each at most.

bool solve() {
    int n;
    cin >> n;
    if (n == -1)
        return false;

    vector<int> cal(n), nut(n);
    for (int i = 0; i < n; ++i)
        cin >> cal[i];
    for (int i = 0; i < n; ++i)
        cin >> nut[i];
    int threshold;
    cin >> threshold;

    cout << max_nutr_val(cal, nut, threshold) << endl;

    return true;
}

int main() {
    while (solve());

    return 0;
}