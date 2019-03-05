from .coord import Coord


class Board:
    PIECE_BLACK = 1
    PIECE_WHITE = -1
    PIECE_EMPTY = 0
    _PIECT_INVALID = -2
    _PIECE_BLACK_CHAR = '●'
    _PIECE_WHITE_CHAR = '○'
    _PIECE_EMPTY_CHAR = ' '
    _PIECT_INVALID_CHAR = '#'
    _PIECE_CHAR = {
        PIECE_BLACK: _PIECE_BLACK_CHAR,
        PIECE_WHITE: _PIECE_WHITE_CHAR,
        PIECE_EMPTY: _PIECE_EMPTY_CHAR,
        _PIECT_INVALID: _PIECT_INVALID_CHAR,
    }

    def __init__(self, width, height):
        self._width = width
        self._height = height
        self.reset()

    def __getitem__(self, position):
        return self._board[position[0]][position[1]]

    def __str__(self):
        result = ''
        result += self._PIECE_EMPTY_CHAR
        for w in range(self._width):
            result += chr(ord('a') + w)
        result += '\n'
        for h in range(1, self._height + 1):
            result += str(h)
            for w in range(1, self._width + 1):
                result += str(self._PIECE_CHAR[self._board[w][h]])
            result += str(h)
            result += '\n'
        result += str(self._PIECE_EMPTY_CHAR)
        for w in range(self._width):
            result += chr(ord('a') + w)
        return result

    def get_opponent(self, piece):
        if piece == self.PIECE_BLACK:
            return self.PIECE_WHITE
        return self.PIECE_BLACK

    def reset(self):
        self._board = [[self.PIECE_EMPTY for h in range(self._height + 2)]
                       for w in range(self._width + 2)]
        for h in range(self._height + 2):
            self._board[0][h] = self._PIECT_INVALID
            self._board[self._width + 1][h] = self._PIECT_INVALID
        for w in range(self._width + 2):
            self._board[w][0] = self._PIECT_INVALID
            self._board[w][self._height + 1] = self._PIECT_INVALID

    def lay(self, position, piece):
        if not isinstance(position, Coord):
            raise TypeError('position不是Coord類型')
        if (position[0] < 1 or position[0] > self._width or
                position[1] < 1 or position[1] > self._height):
            raise IndexError('position {} 超出棋盤 {} 之外'.format(
                position, (self._width, self._height)))
        if piece not in [self.PIECE_BLACK, self.PIECE_WHITE, self.PIECE_EMPTY]:
            raise ValueError('piece不是有效的棋子')
        if self[position] != self.PIECE_EMPTY:
            raise IndexError('position {} 已有棋子'.format(position))
        self._board[position[0]][position[1]] = piece

    def take(self, position):
        if not isinstance(position, Coord):
            raise TypeError('position不是Coord類型')
        if (position[0] < 1 or position[0] > self._width or
                position[1] < 1 or position[1] > self._height):
            raise IndexError('position {} 超出棋盤 {} 之外'.format(
                position, (self._width, self._height)))
        if self[position] not in [self.PIECE_BLACK, self.PIECE_WHITE]:
            raise ValueError('position {} 沒有棋子')
        self._board[position[0]][position[1]] = self.PIECE_EMPTY
