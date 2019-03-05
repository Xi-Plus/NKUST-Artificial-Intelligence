import unittest

from reversi.coord import Coord
from reversi.reversiboard import ReversiBoard


class Test_ReversiBoard(unittest.TestCase):
    def test_check_can_eat(self):
        print()

        board = ReversiBoard()
        print(board)
        eat = board._check_can_eat(Coord(4, 3), Coord(0, 1), board.PIECE_BLACK)
        self.assertEqual(eat, 1)

        board = ReversiBoard()
        board._super_lay(Coord(4, 6), board.PIECE_WHITE)
        board._super_lay(Coord(4, 7), board.PIECE_WHITE)
        print(board)
        eat = board._check_can_eat(
            Coord(4, 8), Coord(0, -1), board.PIECE_BLACK)
        self.assertEqual(eat, 2)

    def test_eat(self):
        print()

        board = ReversiBoard()
        print(board)
        eat = board.eat(Coord(4, 3), Coord(0, 1), board.PIECE_BLACK)
        print(board)
        self.assertTrue(eat)
        self.assertEqual(board[Coord(4, 4)], board.PIECE_BLACK)

        board = ReversiBoard()
        board._super_lay(Coord(4, 6), board.PIECE_WHITE)
        board._super_lay(Coord(4, 7), board.PIECE_WHITE)
        print(board)
        eat = board.eat(Coord(4, 8), Coord(0, -1), board.PIECE_BLACK)
        print(board)
        self.assertTrue(eat)
        self.assertEqual(board[Coord(4, 7)], board.PIECE_BLACK)
        self.assertEqual(board[Coord(4, 6)], board.PIECE_BLACK)

    def test_get_can_lay(self):
        print()

        board = ReversiBoard()
        print(board)
        can_lay = board.get_can_lay(board.PIECE_BLACK)
        print(can_lay)
        EXPECTED = [(3, 4), (4, 3), (5, 6), (6, 5)]
        self.assertEqual(sorted(can_lay), sorted(EXPECTED))

        can_lay = board.get_can_lay(board.PIECE_WHITE)
        print(can_lay)
        EXPECTED = [(3, 5), (4, 6), (5, 3), (6, 4)]
        self.assertEqual(sorted(can_lay), sorted(EXPECTED))

    def test_lay(self):
        print()

        board = ReversiBoard()
        print(board)
        eat = board.lay(Coord(4, 3), board.PIECE_BLACK)
        print(board)
        self.assertTrue(eat)
        self.assertEqual(board[Coord(4, 3)], board.PIECE_BLACK)
        self.assertEqual(board[Coord(4, 4)], board.PIECE_BLACK)

        board = ReversiBoard()
        board._super_lay(Coord(4, 6), board.PIECE_WHITE)
        board._super_lay(Coord(4, 7), board.PIECE_WHITE)
        print(board)
        eat = board.lay(Coord(4, 8), board.PIECE_BLACK)
        print(board)
        self.assertTrue(eat)
        self.assertEqual(board[Coord(4, 8)], board.PIECE_BLACK)
        self.assertEqual(board[Coord(4, 7)], board.PIECE_BLACK)
        self.assertEqual(board[Coord(4, 6)], board.PIECE_BLACK)

    def test_count_piece(self):
        print()

        board = ReversiBoard()
        print(board)
        count = board.count_piece()
        print(count)
        self.assertEqual(count[board.PIECE_BLACK], 2)
        self.assertEqual(count[board.PIECE_WHITE], 2)
        self.assertEqual(count[board.PIECE_EMPTY], 60)

        board.lay(Coord(4, 3), board.PIECE_BLACK)
        print(board)
        count = board.count_piece()
        print(count)
        self.assertEqual(count[board.PIECE_BLACK], 4)
        self.assertEqual(count[board.PIECE_WHITE], 1)
        self.assertEqual(count[board.PIECE_EMPTY], 59)

        board.lay(Coord(5, 3), board.PIECE_WHITE)
        print(board)
        count = board.count_piece()
        print(count)
        self.assertEqual(count[board.PIECE_BLACK], 3)
        self.assertEqual(count[board.PIECE_WHITE], 3)
        self.assertEqual(count[board.PIECE_EMPTY], 58)

        board.lay(Coord(6, 3), board.PIECE_BLACK)
        print(board)
        count = board.count_piece()
        self.assertEqual(count[board.PIECE_BLACK], 6)
        self.assertEqual(count[board.PIECE_WHITE], 1)
        self.assertEqual(count[board.PIECE_EMPTY], 57)


if __name__ == '__main__':
    unittest.main()
