import argparse
import random
import time


class Puzzle:
    board = None

    def __init__(self, size, mode=1):
        self.size = size
        self.mode = mode

    def run(self):
        self.restart()
        restart_cnt = 0
        prev_conflict = self.calc_conflict(self.board)
        step = 0
        while prev_conflict > 0:
            step += 1
            # print('Board: {}. Conflict: {}.'.format(self.board, prev_conflict))
            best_board = []
            min_conflict = 99999

            if self.mode == 1:
                for i in range(self.size):
                    for j in range(self.size):
                        board_next = self.board.copy()
                        board_next[i] = (i, j)
                        conflict = self.calc_conflict(board_next)
                        if conflict < min_conflict:
                            min_conflict = conflict
                            best_board = [board_next]
                        elif conflict == min_conflict:
                            best_board.append(board_next)
            elif self.mode == 2:
                for i in range(self.size):
                    for j in range(self.size):
                        for k in range(self.size):
                            board_next = self.board.copy()
                            board_next[i] = (j, k)
                            conflict = self.calc_conflict(board_next)
                            if conflict < min_conflict:
                                min_conflict = conflict
                                best_board = [board_next]
                            elif conflict == min_conflict:
                                best_board.append(board_next)

            if min_conflict < prev_conflict:
                self.board = best_board[random.randint(0, len(best_board) - 1)]
                prev_conflict = min_conflict
            else:
                # print('Restarting')
                self.restart()
                restart_cnt += 1
                prev_conflict = self.calc_conflict(self.board)
        print('Run {} times. {} steps.'.format(restart_cnt + 1, step))
        print('Result: {}'.format(self.board))
        self.show_board(self.board)
        return restart_cnt + 1, step

    def restart(self):
        if self.mode == 1:
            self.board = [(i, random.randint(0, self.size - 1))
                          for i in range(self.size)]
        elif self.mode == 2:
            self.board = [(random.randint(0, self.size - 1), random.randint(0, self.size - 1))
                          for i in range(self.size)]

    def calc_conflict(self, board):
        cnt = 0
        for i in range(self.size):
            for j in range(i + 1, self.size):
                if board[i][0] == board[j][0]:
                    cnt += 1
                if board[i][1] == board[j][1]:
                    cnt += 1
                if board[i][0] - board[i][1] == board[j][0] - board[j][1]:
                    cnt += 1
                if board[i][0] + board[i][1] == board[j][0] + board[j][1]:
                    cnt += 1
        return cnt

    def show_board(self, board):
        for i in range(self.size):
            for j in range(self.size):
                if (i, j) in board:
                    print('O', end='')
                else:
                    print('_', end='')
            print()


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('size', type=int, nargs='?', default=8)
    parser.add_argument('--mode', type=int, choices=[1, 2], default=1)
    parser.add_argument('--run', type=int, default=1)
    args = parser.parse_args()
    print(args)

    start = time.time()

    puzzle = Puzzle(args.size, args.mode)
    if args.run <= 1:
        puzzle.run()
        print(time.time() - start)
    else:
        sum_round = 0
        sum_step = 0
        for i in range(args.run):
            cnt_round, cnt_step = puzzle.run()
            sum_round += cnt_round
            sum_step += cnt_step
        print(sum_round / args.run, sum_step / args.run,
              (time.time() - start) / args.run)
