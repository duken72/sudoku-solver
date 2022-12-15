#!/usr/bin/env python3

from rich import print
import numpy as np

ROW = []
for r in range(9):
    ROW.append([r*9 + c for c in range(9)])

COL = []
for c in range(9):
    COL.append([c + 9*r for r in range(9)])

BLOCK = []
B = np.array([0, 1, 2, 9, 10, 11, 18, 19, 20])
for b in range(0, 9):
    BLOCK.append([b//3 * 27 + b%3 * 3 + Bi for Bi in B])

print(np.array(ROW))
# np.array(COL)
