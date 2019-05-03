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
	int visitcnt = 0;

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
		visitcnt++;
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

int main(int argc, char* argv[]) {
	//	ios::sync_with_stdio(false);
	//	cin.tie(0);
	bool simpleoutput = false;
	if (argc >= 3 && atoi(argv[2]) > 0) simpleoutput = true;
	char inputpath[100];
	if (argc < 2) {
		printf("Missing parameter\n");
		string temps;
		printf("file input: ");
		gets(inputpath);
	} else {
		strcpy(inputpath, argv[1]);
		if (simpleoutput) {
			printf("%s\t", inputpath);
		} else {
			printf("file input: %s\n", inputpath);
		}
	}

	fstream file;
	file.open(inputpath, ios::in);
	if (!file.is_open()) {
		cout << "file open failed" << endl;
		return -1;
	}
	int branch;
	file >> branch;
	int level;
	file >> level;
	if (!simpleoutput) {
		cout << "branch " << branch << " level " << level << endl;
	}
	clock_t start_time = clock();

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
	// cout << "tree:" << endl;
	// abp.dump();
	// cout << "visit:" << endl;
	// abp.dumpvisit();
	int runtime = (clock() - start_time) * 1000 / CLOCKS_PER_SEC;
	if (simpleoutput) {
		cout << abp.arr[0] << "\t";
		cout << abp.visitcnt << "\t";
		cout << abp.powsumlist[level + 1] - abp.visitcnt << "\t";
		cout << runtime << endl;
	} else {
		cout << "root result: " << abp.arr[0] << endl;
		cout << "visit cnt: " << abp.visitcnt << endl;
		cout << "not visit: " << abp.powsumlist[level + 1] - abp.visitcnt << endl;
		printf("It tooks %d milliseconds\n", runtime);
	}

	return 0;
}
