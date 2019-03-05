class Coord(tuple):
    def __new__(cls, x, y):
        return tuple.__new__(cls, (x, y))

    def __add__(self, other):
        if not isinstance(other, Coord):
            raise ValueError('other {} is not a Coord'.format(other))
        return Coord(self[0] + other[0], self[1] + other[1])

    def __sub__(self, other):
        if not isinstance(other, Coord):
            raise ValueError('other {} is not a Coord'.format(other))
        return Coord(self[0] - other[0], self[1] - other[1])
