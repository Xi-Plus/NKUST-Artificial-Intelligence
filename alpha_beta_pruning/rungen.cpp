#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

int main(int argc, char* argv[]) {
	int type = 2;
	if (argc >= 2) type = atoi(argv[1]);
	tuple<int, int, int, int> list[] = {
		{2, 3, 10, 10},
		{2, 11, 15, 50},
		{2, 16, 20, 100},
		{2, 21, 25, 1000},
		{3, 2, 5, 10},
		{3, 6, 10, 100},
		{3, 11, 15, 1000},
		{4, 2, 5, 50},
		{4, 6, 10, 100},
		{4, 11, 12, 1000},
		{5, 2, 5, 50},
		{5, 6, 10, 500},
		{6, 2, 5, 100},
		{6, 6, 9, 1000},
		{7, 2, 5, 100},
		{7, 6, 8, 1000},
		{8, 2, 4, 100},
		{8, 5, 8, 1000},
		{9, 2, 4, 100},
		{9, 5, 8, 1000},
		{10, 2, 4, 100},
		{10, 5, 7, 1000},
		{20, 2, 4, 1000},
		{20, 5, 5, 1000},
		{50, 2, 4, 1000},
		{100, 2, 3, 1000},
	};
	for (auto v : list) {
		int branch = get<0>(v);
		int limit = get<3>(v);
		for (int level = get<1>(v); level <= get<2>(v); level++) {
			stringstream ss;
			if (type == 1) {
				ss << "gendata " << branch << " " << level << " " << limit << " > data/" << branch << "-" << level << "-" << limit << ".txt";
				cout << ss.str() << endl;
			} else if (type == 2) {
				ss << "main data/" << branch << "-" << level << "-" << limit << ".txt 1";
			} else {
				cout << "Nothing to do" << endl;
				return 0;
			}
			system(ss.str().c_str());
		}
	}

	return 0;
}
