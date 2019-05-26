import argparse
import random
import time


class Board:
    def __init__(self, board):
        self.board = board
        self.board_size = len(board)
        self.conflict = self.calc_conflict(board)

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
    board = None

    def __init__(self, board_size, population, crossover, mutation):
        self.board_size = board_size
        self.population = population  # population size
        self.crossover = crossover  # probability of performing crossover
        self.mutation = mutation  # probability of mutation

    def run(self):
        all_boards = []
        for i in range(self.population):
            all_boards.append(Board([random.randint(0, self.board_size - 1) for j in range(self.board_size)]))

        step = 0
        while True:
            step += 1
            new_boards = []
            # crossover
            for i in range(self.crossover):
                pick1 = pick2 = 0
                while pick1 == pick2:
                    pick1 = random.randint(0, self.population - 1)
                    pick2 = random.randint(0, self.population - 1)
                new_boards.append(Board(self.do_crossover(all_boards[pick1], all_boards[pick2])))
            # mutation
            for i in range(self.mutation):
                pick = random.randint(0, self.population - 1)
                row = random.randint(0, self.board_size - 1)
                value = random.randint(0, self.board_size - 1)
                new_boards[pick].board[row] = value
            # selection
            all_boards = self.select(new_boards)
            # print(step, all_boards[0], self.calc_conflict(all_boards[0]))
            if all_boards[0].conflict == 0:
                break
        return all_boards[0], step

    def select(self, new_boards):
        temp_boards = [
            (new_boards[i].conflict, new_boards[i])
            for i in range(self.crossover)
        ]
        temp_boards.sort(key=lambda v: v[0])
        return [temp_boards[i][1] for i in range(self.population)]

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
    parser.add_argument('--crossover', type=int, default=200)
    parser.add_argument('--mutation', type=int, default=20)
    parser.add_argument('--run', type=int, default=1)
    args = parser.parse_args()
    print(args)

    start = time.time()

    puzzle = Puzzle(args.size, args.population, args.crossover, args.mutation)
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
