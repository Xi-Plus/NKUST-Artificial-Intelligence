#include <bits/stdc++.h>
using namespace std;

#define BOARD_SIZE 8
#define CHESS_BLACK 1
#define CHESS_WHITE 2
#define CHESS_WALL 3
#define ICON_BLACK "X"
#define ICON_WHITE "O"
#define ICON_EMPTY " "
#define ICON_WALL "#"
const string ICON[] = {ICON_EMPTY, ICON_BLACK, ICON_WHITE, ICON_WALL};
int c2n[255] = {};
char n2c[BOARD_SIZE + 1];

struct Board {
	int board[BOARD_SIZE + 2][BOARD_SIZE + 2] = {};
};

inline int other_color(int color) {
	return CHESS_BLACK + CHESS_WHITE - color;
}

void show_board(Board *b) {
	cout << ICON_WALL << " ";
	for (int w = 0; w < BOARD_SIZE; w++) {
		cout << (char)('A' + w) << " ";
	}
	cout << ICON_WALL << endl;
	for (int q = 1; q < BOARD_SIZE + 1; q++) {
		cout << q << " ";
		for (int w = 1; w < BOARD_SIZE + 1; w++) {
			cout << ICON[b->board[q][w]] << " ";
		}
		cout << q << " " << endl;
	}
	cout << ICON_WALL << " ";
	for (int w = 0; w < BOARD_SIZE; w++) {
		cout << (char)('A' + w) << " ";
	}
	cout << ICON_WALL << endl;
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
	do_eat(board, color, c, n, 1, 1);
	do_eat(board, color, c, n, 1, -1);
	do_eat(board, color, c, n, -1, 1);
	do_eat(board, color, c, n, -1, -1);
	do_eat(board, color, c, n, 1, 0);
	do_eat(board, color, c, n, -1, 0);
	do_eat(board, color, c, n, 0, 1);
	do_eat(board, color, c, n, 0, -1);
	board->board[n][c] = color;
}

void check_next(Board *board) {
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
		// AI turn
		check_next(board);
		turn = other_color(turn);
	other_turn:
		while (true) {
			cout << "Input other (" << ICON[turn] << ") lay: ";
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
