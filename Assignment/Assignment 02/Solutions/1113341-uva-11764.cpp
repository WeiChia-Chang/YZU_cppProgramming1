#include <iostream>
using namespace std;

int main() {
	int t, n, a;


	cin >> t;
	for (int j = 1; j <= t; j++) {
		int H{}, L{}, s{};
		cin >> n;

		for (int i = 1; i <= n; i++) {
			cin >> a;
			if (a > s) {
				H++;
			}
			else if (a < s) {
				L++;
			}
			s = a;
		}

		cout << "Case " << j << ": " << H - 1 << " " << L << endl;
	}


	return 0;
}