OPEN = [(0, 0, [])]
CLOSE = []
FULL_A = 3
FULL_B = 4

while len(OPEN) > 0:
    now = OPEN.pop(0)

    if now[0] == 2 or now[1] == 2:
        print(now[2] + [(now[0], now[1])])
        break

    CLOSE.append((now[0], now[1]))

    if now[0] > 0 and (0, now[1]) not in (OPEN + CLOSE):
        OPEN.append((0, now[1], now[2] + [(now[0], now[1])]))
    if now[1] > 0 and (now[0], 0) not in (OPEN + CLOSE):
        OPEN.append((now[0], 0, now[2] + [(now[0], now[1])]))

    if now[0] < FULL_A and (FULL_A, now[1]) not in (OPEN + CLOSE):
        OPEN.append((FULL_A, now[1], now[2] + [(now[0], now[1])]))
    if now[1] < FULL_B and (now[0], FULL_B) not in (OPEN + CLOSE):
        OPEN.append((now[0], FULL_B, now[2] + [(now[0], now[1])]))

    if now[1] < FULL_B and now[0] > 0:
        if now[0] + now[1] <= FULL_B:
            if (0, now[0] + now[1]) not in (OPEN + CLOSE):
                OPEN.append((0, now[0] + now[1], now[2] + [(now[0], now[1])]))
        else:
            if (now[0] + now[1] - FULL_B, FULL_B) not in (OPEN + CLOSE):
                OPEN.append((now[0] + now[1] - FULL_B, FULL_B,
                             now[2] + [(now[0], now[1])]))

    if now[0] < FULL_A and now[1] > 0:
        if now[0] + now[1] <= FULL_A:
            if (now[0] + now[1], 0) not in (OPEN + CLOSE):
                OPEN.append((now[0] + now[1], 0, now[2] + [(now[0], now[1])]))
        else:
            if (FULL_A, now[0] + now[1] - FULL_A) not in (OPEN + CLOSE):
                OPEN.append(
                    (FULL_A, now[0] + now[1] - FULL_A, now[2] + [(now[0], now[1])]))
