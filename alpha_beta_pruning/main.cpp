#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
class ABP {
   private:
	int branch;
	int level;

   public:
	bool enable_alpha_beta = true;
	int* powlist;
	int* powsumlist;
	int* arr;
	bool* visit;

   public:
	ABP(int _branch, int _level) {
		branch = _branch;
		level = _level;
		powlist = (int*)malloc((level + 2) * sizeof(int));
		powsumlist = (int*)malloc((level + 2) * sizeof(int));
		powlist[0] = 1;
		powsumlist[0] = 0;
		for (int q = 1; q < level + 2; q++) {
			powlist[q] = powlist[q - 1] * branch;
			powsumlist[q] = powsumlist[q - 1] * branch + 1;
		}
		arr = (int*)malloc((powsumlist[level + 1]) * sizeof(int));
		for (int l = 0; l < level; l++) {
			for (long long q = powsumlist[l]; q < powsumlist[l + 1]; q++) {
				arr[q] = (l & 1 ? INT_MAX : INT_MIN);
			}
		}
		visit = (bool*)calloc(powsumlist[level + 1], sizeof(bool));
	}

	void run() {
		dfs(0, 0);
	}

	int dfs(int root, int now_level) {
		visit[root] = 1;
		if (now_level == level) {
			// cout << "get " << root << " " << now_level << " " << arr[root] << endl;
			return arr[root];
		}
		if (now_level & 1) {  // Min
			// cout << "get min at " << now_level << " " << root << endl;
			for (int q = 1; q <= branch; q++) {
				if (now_level && arr[root] <= arr[(root - 1) / branch] && arr[root] != INT_MAX) {
					// printf("skip at root %d level %d, %d %d\n", root, now_level, arr[root], arr[(root - 1) / branch]);
					break;
				}
				arr[root] = min(arr[root], dfs(root * branch + q, now_level + 1));
				// dump();
			}
		} else {  // Max
			// cout << "get max at " << now_level << " " << root << endl;
			for (int q = 1; q <= branch; q++) {
				if (now_level && arr[root] >= arr[(root - 1) / branch] && arr[root] != INT_MIN) {
					// printf("skip at root %d level %d, %d %d\n", root, now_level, arr[root], arr[(root - 1) / branch]);
					break;
				}
				arr[root] = max(arr[root], dfs(root * branch + q, now_level + 1));
				// cout << root << " " << now_level << endl;
				// dump();
			}
		}
		// cout << "get " << root << " " << now_level << " " << arr[root] << endl;
		return arr[root];
	}

	void dump() {
		for (int l = 0; l <= level; l++) {
			for (long long q = powsumlist[l]; q < powsumlist[l + 1]; q++) {
				printf("%*d", powlist[level - l] * 4, arr[q]);
			}
			cout << endl;
		}
		cout << endl;
	}

	void dumpvisit() {
		for (int l = 0; l <= level; l++) {
			for (long long q = powsumlist[l]; q < powsumlist[l + 1]; q++) {
				printf("%*d", powlist[level - l] * 4, visit[q]);
			}
			cout << endl;
		}
		cout << endl;
	}
};

int main() {
	//	ios::sync_with_stdio(false);
	//	cin.tie(0);
	fstream file;
	file.open("3-3-2.txt", ios::in);
	if (!file.is_open()) {
		cout << "file open failed" << endl;
		return -1;
	}
	int branch;
	file >> branch;
	int level;
	file >> level;
	cout << "branch " << branch << " level " << level << endl;

	// Init object
	ABP abp(branch, level);

	// Read & load data
	file >> abp.arr[abp.powsumlist[level]];
	for (long long q = abp.powsumlist[level] + 1; q < abp.powsumlist[level + 1]; q++) {
		file.get();
		file >> abp.arr[q];
	}

	// Dump data
	// abp.dump();

	// Calc
	abp.run();

	// Show result
	cout << "tree:" << endl;
	abp.dump();
	cout << "visit:" << endl;
	abp.dumpvisit();
	return 0;
}
