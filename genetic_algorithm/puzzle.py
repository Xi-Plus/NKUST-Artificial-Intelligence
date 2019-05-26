import argparse
import random
import time


class Board:
    def __init__(self, board):
        self.board = board
        self.board_size = len(board)
        self.conflict = self.calc_conflict(board)

    def renew_conflict(self):
        self.conflict = self.calc_conflict(self.board)

    def calc_conflict(self, board):
        cnt = 0
        for i in range(self.board_size):
            for j in range(i + 1, self.board_size):
                if board[i] == board[j]:
                    cnt += 1
                if i - board[i] == j - board[j]:
                    cnt += 1
                if i + board[i] == j + board[j]:
                    cnt += 1
        return cnt

    def show(self):
        for i in range(self.board_size):
            for j in range(self.board_size):
                if self.board[i] == j:
                    print('O', end='')
                else:
                    print('_', end='')
            print()


class Puzzle:
    score = 50

    def __init__(self, board_size, population, mutation):
        self.board_size = board_size
        self.population = population  # population size
        self.mutation = mutation  # probability of mutation

    def run(self):
        all_boards = []
        for i in range(self.population):
            all_boards.append(Board([random.randint(0, self.board_size - 1) for j in range(self.board_size)]))

        step = 0
        while True:
            for board in all_boards:
                if board.conflict == 0:
                    return board, step

            step += 1
            new_boards = []
            # crossover
            ticket_pool = []
            for i in range(self.population):
                ticket_pool.extend([i] * int(self.score / all_boards[i].conflict))
            for i in range(self.population):
                pick1 = pick2 = 0
                while pick1 == pick2:
                    pick1 = ticket_pool[random.randint(0, len(ticket_pool) - 1)]
                    pick2 = ticket_pool[random.randint(0, len(ticket_pool) - 1)]
                new_boards.append(Board(self.do_crossover(all_boards[pick1], all_boards[pick2])))
            # mutation
            for i in range(self.mutation):
                pick = random.randint(0, self.population - 1)
                row = random.randint(0, self.board_size - 1)
                value = random.randint(0, self.board_size - 1)
                new_boards[pick].board[row] = value
                new_boards[pick].renew_conflict()
            all_boards = new_boards

    def do_crossover(self, board1, board2):
        switch_cnt = random.randint(1, self.board_size - 1)
        switch = random.sample(range(0, self.board_size), switch_cnt)
        new_board = board1.board.copy()
        for i in switch:
            new_board[i] = board2.board[i]
        return new_board


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('size', type=int, nargs='?', default=8)
    parser.add_argument('--population', type=int, default=100)
    parser.add_argument('--mutation', type=int, default=20)
    parser.add_argument('--score', type=int, default=50)
    parser.add_argument('--run', type=int, default=1)
    args = parser.parse_args()
    print(args)

    start = time.time()

    puzzle = Puzzle(args.size, args.population, args.mutation)
    puzzle.score = args.score
    if args.run <= 1:
        board, step = puzzle.run()
        print('Time {:.4f} s. Step {}.'.format(time.time() - start, step))
        board.show()
    else:
        sum_step = 0
        for i in range(1, args.run + 1):
            board, step = puzzle.run()
            sum_step += step
            print('Run {}. Step {}. Avg time {:.4f} s. Avg step {:.2f}. Total time {:.4f} s.'.format(
                i, step, (time.time() - start) / i, sum_step / i, time.time() - start))
