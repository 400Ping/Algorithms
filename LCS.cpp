//s1113356
#include<iostream>
#include<string>
using namespace std;

int lcs(string X, string Y){
    int m = X.length();
    int n = Y.length();

    // Initializing a matrix of size (101 x 101)
    int L[101][101];

    // Following steps build L[m+1][n+1]
    // in bottom up fashion. Note that
    // L[i][j] contains length of LCS of
    // X[0..i-1] and Y[0..j-1]
    for (int i = 0; i <= m; i++){
        for (int j = 0; j <= n; j++){
            if (i == 0 || j == 0)
                L[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                L[i][j] = L[i - 1][j - 1] + 1;
            else
                L[i][j] = max(L[i - 1][j], L[i][j - 1]);
        }
    }
    // L[m][n] contains length of LCS
    // for X[0..n-1] and Y[0..m-1]
    return L[m][n];
}

int main(){
    string S1, S2;
    while (getline(cin, S1)){
        if (cin.eof()) break;
        getline(cin, S2);
        if (S2.empty()) break;
        cout << lcs(S1, S2) << endl;
    }
    return 0;
}