#include <bits/stdc++.h>
#include "testlib.h"
#define endl '\n'
using namespace std;
long long power(long long a, long long n) {
	if (n == 0) return 1;
	long long t = power(a, n / 2);
	if (n & 1) return t * t * a;
	return t * t;
}

int main(int argc, char* argv[]) {
	registerGen(argc, argv, 1);
	int branch = atoi(argv[1]);
	int level = atoi(argv[2]);
	int limit = 100;
	if (argc > 3) limit = atoi(argv[3]);

	cout << branch << endl;
	cout << level << endl;
	cout << rnd.next(-limit, limit);
	long long len = power(branch, level) - 1;
	while (len--) {
		cout << "," << rnd.next(-limit, limit);
	}
	cout << endl;

	return 0;
}
