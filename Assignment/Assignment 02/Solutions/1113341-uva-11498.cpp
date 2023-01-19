#include <iostream>
using namespace std;

int main() {
	int K, N, M, X, Y;
	
	while (true) {
		cin >> K;
		if (K == 0) {
			break;
		}

		cin >> N >> M;

		for (int j = 1; j <= K; j++) {
			cin >> X >> Y;
			if (N < X && M < Y) {
				cout << "NE\n";
			}
			else if (N > X && M < Y) {
				cout << "NO\n";
			}
			else if(N > X && M > Y) {
				cout << "SO\n";
			}
			else if (N < X && M > Y) {
				cout << "SE\n";
			}
			else {
				cout << "divisa\n";
			}
		}
	}

	return 0;

}