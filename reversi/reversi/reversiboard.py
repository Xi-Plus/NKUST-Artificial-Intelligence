from .board import Board
from .coord import Coord


class ReversiBoard(Board):
    _WIDTH = 8
    _HEIGHT = 8
    _start_lay = [[(4, 4), Board.PIECE_WHITE],
                  [(5, 4), Board.PIECE_BLACK],
                  [(4, 5), Board.PIECE_BLACK],
                  [(5, 5), Board.PIECE_WHITE]]
    _UPPER = -1
    _LOWER = 1
    _RIGHT = 1
    _LEFT = -1
    _NONE = 0
    _DIRES = [
        Coord(_NONE, _UPPER),
        Coord(_RIGHT, _UPPER),
        Coord(_RIGHT, _NONE),
        Coord(_RIGHT, _LOWER),
        Coord(_NONE, _LOWER),
        Coord(_LEFT, _LOWER),
        Coord(_LEFT, _NONE),
        Coord(_LEFT, _UPPER),
    ]

    def __init__(self):
        super().__init__(self._WIDTH, self._HEIGHT)
        for preplace in self._start_lay:
            super().lay(Coord(preplace[0][0], preplace[0][1]), preplace[1])

    def _check_can_eat(self, position, dire, turn):
        opponent = self.get_opponent(turn)
        if self[position + dire] != opponent:
            return 0
        eat = 0
        while self[position + dire] == opponent:
            position += dire
            eat += 1
        if self[position + dire] != turn:
            return 0
        return eat

    def eat(self, position, dire, turn):
        if self._check_can_eat(position, dire, turn) == 0:
            return False
        opponent = self.get_opponent(turn)
        while self[position + dire] == opponent:
            position += dire
            self.take(position)
            super().lay(position, turn)
        return True

    def _check_can_lay(self, position, turn):
        if self[position] != Board.PIECE_EMPTY:
            return False
        for dire in self._DIRES:
            if self._check_can_eat(position, dire, turn) > 0:
                return True
        return False

    def get_can_lay(self, turn):
        result = []
        for w in range(1, self._width + 1):
            for h in range(1, self._height + 1):
                position = Coord(w, h)
                if self._check_can_lay(position, turn):
                    result.append(position)
        return result

    def lay(self, position, turn):
        if not self._check_can_lay(position, turn):
            return False
        for dire in self._DIRES:
            self.eat(position, dire, turn)
        super().lay(position, turn)
        return True

    def _super_lay(self, position, turn):
        super().lay(position, turn)

    def count_piece(self):
        count = {
            Board.PIECE_BLACK: 0,
            Board.PIECE_WHITE: 0,
            Board.PIECE_EMPTY: 0
        }
        for w in range(1, self._width + 1):
            for h in range(1, self._height + 1):
                count[self[Coord(w, h)]] += 1
        return count
