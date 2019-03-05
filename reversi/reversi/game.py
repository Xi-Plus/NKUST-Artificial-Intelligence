from .reversiboard import ReversiBoard


class Game:
    def __init__(self):
        self._board = ReversiBoard()
        self._turn = self._board.PIECE_BLACK

    def getTurn(self):
        return self._turn

    def showBoard(self):
        print(self._board)

    # def _checkCanLay(self, tw, th):
    #     result = []
    #     for dire in self._DIRES:
    #         noww = tw + dire[0]
    #         nowh = th + dire[1]
    #         # if
