#!/usr/bin/env python3

import pandas as pd
from rich import print


df = pd.read_csv('log.csv')

df.at[0, 'command'] = 'C++ with backtracking'
df.at[1, 'command'] = 'C++ with purely backtracking'
df.at[2, 'command'] = 'C++ without backtracking'
df.at[3, 'command'] = 'Python with backtracking'

index = pd.Index([0, 1, 2, 3])
df.set_index(index)
print(df.reindex([2, 1, 0, 3]))
