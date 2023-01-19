#include <iostream>
using namespace std;

int main() {
	int t, n, a;

	cin >> t;
	for (int j = 1; j <= t; j++) {
		int s{};
		cin >> n;
		for (int i = 1; i <= n; i++) {
			cin >> a;
			if (a > s) {
				s = a;
			}
		}
		cout << "Case " << j << ": " << s << endl;
	}

	return 0;
}