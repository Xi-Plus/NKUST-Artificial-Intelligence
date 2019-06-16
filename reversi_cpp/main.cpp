#include <bits/stdc++.h>
using namespace std;

#define BOARD_SIZE 8
#define CHESS_EMPTY 0
#define CHESS_BLACK 1
#define CHESS_WHITE 2
#define CHESS_WALL 3
#define ICON_BLACK "X"
#define ICON_WHITE "O"
#define ICON_EMPTY " "
#define ICON_WALL "#"
#define DFS_LIMIT 7

const string ICON[] = {ICON_EMPTY, ICON_BLACK, ICON_WHITE, ICON_WALL};
int c2n[255] = {};
char n2c[BOARD_SIZE + 1];
typedef vector<pair<int, int>> CAN_LAY_LIST;
stack<int> score_list;

struct Board {
	int board[BOARD_SIZE + 2][BOARD_SIZE + 2] = {};
};

inline int other_color(int color) {
	return CHESS_BLACK + CHESS_WHITE - color;
}

void show_board(Board *b) {
	int cntB = 0, cntW = 0;
	cout << ICON_WALL << " ";
	for (int w = 0; w < BOARD_SIZE; w++) {
		cout << (char)('A' + w) << " ";
	}
	cout << ICON_WALL << endl;
	for (int q = 1; q < BOARD_SIZE + 1; q++) {
		cout << q << " ";
		for (int w = 1; w < BOARD_SIZE + 1; w++) {
			cout << ICON[b->board[q][w]] << " ";
			if (b->board[q][w] == CHESS_BLACK)
				cntB++;
			else if (b->board[q][w] == CHESS_WHITE)
				cntW++;
		}
		cout << q << " " << endl;
	}
	cout << ICON_WALL << " ";
	for (int w = 0; w < BOARD_SIZE; w++) {
		cout << (char)('A' + w) << " ";
	}
	cout << ICON_WALL << endl;
	cout << ICON_BLACK << ": " << cntB << " " << ICON_WHITE << ": " << cntW << endl;
}

bool check_can_eat(Board *board, int color, int c, int n, int dc, int dn) {
	int eat = 0;
	int other = other_color(color);
	while (board->board[n + dn][c + dc] == other) {
		eat++;
		n += dn;
		c += dc;
	}
	if (eat == 0) return false;
	if (board->board[n + dn][c + dc] != color) return false;
	return true;
}

inline bool check_can_lay(Board *board, int color, int c, int n) {
	if (check_can_eat(board, color, c, n, 1, 1)) return true;
	if (check_can_eat(board, color, c, n, 1, -1)) return true;
	if (check_can_eat(board, color, c, n, -1, 1)) return true;
	if (check_can_eat(board, color, c, n, -1, -1)) return true;
	if (check_can_eat(board, color, c, n, 1, 0)) return true;
	if (check_can_eat(board, color, c, n, -1, 0)) return true;
	if (check_can_eat(board, color, c, n, 0, 1)) return true;
	if (check_can_eat(board, color, c, n, 0, -1)) return true;
	return false;
}

void do_eat(Board *board, int color, int c, int n, int dc, int dn) {
	int other = other_color(color);
	while (board->board[n + dn][c + dc] == other) {
		board->board[n + dn][c + dc] = color;
		n += dn;
		c += dc;
	}
}

inline void do_lay(Board *board, int color, int c, int n) {
	if (check_can_eat(board, color, c, n, 1, 1)) do_eat(board, color, c, n, 1, 1);
	if (check_can_eat(board, color, c, n, 1, -1)) do_eat(board, color, c, n, 1, -1);
	if (check_can_eat(board, color, c, n, -1, 1)) do_eat(board, color, c, n, -1, 1);
	if (check_can_eat(board, color, c, n, -1, -1)) do_eat(board, color, c, n, -1, -1);
	if (check_can_eat(board, color, c, n, 1, 0)) do_eat(board, color, c, n, 1, 0);
	if (check_can_eat(board, color, c, n, -1, 0)) do_eat(board, color, c, n, -1, 0);
	if (check_can_eat(board, color, c, n, 0, 1)) do_eat(board, color, c, n, 0, 1);
	if (check_can_eat(board, color, c, n, 0, -1)) do_eat(board, color, c, n, 0, -1);
	board->board[n][c] = color;
}

CAN_LAY_LIST list_can_lay(Board *board, int color) {
	CAN_LAY_LIST result;
	for (int n = 1; n <= BOARD_SIZE; n++) {
		for (int c = 1; c <= BOARD_SIZE; c++) {
			if (board->board[n][c] != CHESS_EMPTY) continue;
			if (check_can_lay(board, color, c, n)) {
				result.push_back(make_pair(c, n));
			}
		}
	}
	return result;
}

const int POINT_SCORE[8][8] = {{100, -10, 8, 6, 6, 8, -10, 100},
							   {-10, -25, -4, -4, -4, -4, -25, -10},
							   {8, -4, 6, 4, 4, 6, -4, 8},
							   {6, -4, 4, 0, 0, 4, -4, 6},
							   {6, -4, 4, 0, 0, 4, -4, 6},
							   {8, -4, 6, 4, 4, 6, -4, 8},
							   {-10, -25, -4, -4, -4, -4, -25, -10},
							   {100, -10, 8, 6, 6, 8, -10, 100}};

int calc_score(Board *board, int color) {
	int cntMy = 0, cntOther = 0;
	int point_score = 0;
	int other = other_color(color);
	for (int n = 1; n <= BOARD_SIZE; n++) {
		for (int c = 1; c <= BOARD_SIZE; c++) {
			if (board->board[n][c] == color) {
				cntMy++;
				point_score += POINT_SCORE[n - 1][c - 1];
			} else if (board->board[n][c] == other) {
				cntOther++;
				point_score -= POINT_SCORE[n - 1][c - 1];
			}
		}
	}
	return (cntMy - cntOther) * 2 + point_score;
}

int dfs_score(Board *board, int color, int now_color, int limit) {
	// cout << "dfs_score " << color << " " << now_color << " " << limit << endl;
	// show_board(board);
	if (limit == 1) {
		int score = calc_score(board, color);
		// cout << "A limit " << limit << " color " << color << "/" << now_color << " result " << score << endl;
		return score;
	}
	CAN_LAY_LIST can_lay = list_can_lay(board, now_color);
	// cout << can_lay.size() << " can lay" << endl;
	if (can_lay.size() == 0) {
		int score = calc_score(board, color);
		// cout << "B limit " << limit << " color " << color << "/" << now_color << " result " << score << endl;
		return score;
	}
	int score;
	int other = other_color(now_color);
	if (color == now_color) {
		// MAX
		score = INT_MIN;
		for (auto lay : can_lay) {
			if (score >= score_list.top() && score != INT_MIN && score != INT_MAX) {
				// cout << "A Skip " << limit << " " << score << " " << score_list.top() << " " << score_list.size() << endl;
				continue;
			}
			Board *new_board = new Board();
			memcpy(new_board, board, sizeof(*board));
			do_lay(new_board, now_color, lay.first, lay.second);
			score_list.push(score);
			score = max(score, dfs_score(new_board, color, other, limit - 1));
			score_list.pop();
		}
		// cout << "C limit " << limit << " color " << color << "/" << now_color << " result " << score << endl;
	} else {
		// MIN
		score = INT_MAX;
		for (auto lay : can_lay) {
			if (score >= score_list.top() && score != INT_MAX && score != INT_MIN) {
				// cout << "B Skip " << limit << " " << score << " " << score_list.top() << " " << score_list.size() << endl;
				continue;
			}
			Board *new_board = new Board();
			memcpy(new_board, board, sizeof(*board));
			do_lay(new_board, now_color, lay.first, lay.second);
			score_list.push(score);
			score = min(score, dfs_score(new_board, color, other, limit - 1));
			score_list.pop();
		}
		// cout << "D limit " << limit << " color " << color << "/" << now_color << " result " << score << endl;
	}
	return score;
}

void check_next(Board *board, int color) {
	CAN_LAY_LIST can_lay = list_can_lay(board, color);
	if (can_lay.size() == 0) {
		cout << "No can lay" << endl;
		return;
	}
	cout << can_lay.size() << " position to lay: ";
	for (auto v : can_lay) {
		cout << n2c[v.first] << v.second << " ";
	}
	cout << endl;

	int best_score = INT_MIN, score;
	pair<int, int> lay;
	Board *new_board = new Board();
	for (auto v : can_lay) {
		memcpy(new_board, board, sizeof(*board));
		do_lay(new_board, color, v.first, v.second);
		assert(score_list.size() == 0);
		score_list.push(INT_MAX);
		score = dfs_score(new_board, color, other_color(color), DFS_LIMIT);
		score_list.pop();
		if (score > best_score) {
			lay = v;
			best_score = score;
		}
	}
	cout << "lay " << n2c[lay.first] << lay.second << " score " << best_score << endl;
	do_lay(board, color, lay.first, lay.second);
	show_board(board);
}

int main() {
	for (int q = 1; q <= BOARD_SIZE; q++) {
		c2n[(char)('A' + q - 1)] = q;
		c2n[(char)('a' + q - 1)] = q;
		n2c[q] = 'A' + q - 1;
	}

	Board *board = new Board();
	for (int q = 0; q < BOARD_SIZE + 2; q++) {
		board->board[q][0] = CHESS_WALL;
		board->board[q][BOARD_SIZE + 1] = CHESS_WALL;
		board->board[0][q] = CHESS_WALL;
		board->board[BOARD_SIZE + 1][q] = CHESS_WALL;
	}
	board->board[4][c2n['D']] = CHESS_WHITE;
	board->board[4][c2n['E']] = CHESS_BLACK;
	board->board[5][c2n['D']] = CHESS_BLACK;
	board->board[5][c2n['E']] = CHESS_WHITE;
	show_board(board);

	string s;
	int layn, layc;

	int turn = CHESS_BLACK;

	int temp = -1;
	cout << "Input AI color (0: Black=First, not 0: White=Second): ";
	cin >> temp;
	cin.ignore();
	if (temp == 1) {
		goto other_turn;
	}

	while (true) {
	my_turn:
		// AI turn
		cout << "-------------------------------" << endl;
		cout << "AI (" << ICON[turn] << ") turn" << endl;
		check_next(board, turn);
		turn = other_color(turn);
	other_turn:
		CAN_LAY_LIST can_lay = list_can_lay(board, turn);
		cout << "-------------------------------" << endl;
		cout << "Player (" << ICON[turn] << ") turn" << endl;
		if (can_lay.size() == 0) {
			cout << "No can lay" << endl;
			goto my_turn;
		}
		cout << can_lay.size() << " position to lay: ";
		for (auto v : can_lay) {
			cout << n2c[v.first] << v.second << " ";
		}
		cout << endl;
		while (true) {
			cout << "Input player lay: ";
			getline(cin, s);
			if (s.size() != 2) continue;
			if (('A' <= s[0] && s[0] <= 'Z') || ('a' <= s[0] && s[0] <= 'z')) {
				layc = c2n[s[0]];
				if (layc < 1 || layc > BOARD_SIZE) continue;
			} else {
				continue;
			}
			if ('1' <= s[1] && s[1] <= '8') {
				layn = s[1] - '0';
				if (layn < 1 || layn > BOARD_SIZE) continue;
			} else {
				continue;
			}
			if (!check_can_lay(board, turn, layc, layn)) {
				cout << "You cannot lay here" << endl;
				continue;
			}
			break;
		}
		cout << "lay " << layc << " " << layn << endl;
		do_lay(board, turn, layc, layn);
		show_board(board);
		turn = other_color(turn);
	}
}
