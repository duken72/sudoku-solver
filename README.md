# Sudoku solver

A C++ Sudoku solver.

Sad story, I didn't know about backtracking when I started. If you don't know about it yet, you can check this [link](https://youtu.be/G_UYXzGuqvM).

I tried to avoid using it, but some Sudoku puzzles are so damn hard that you just have to try out all possibilities, with backtracking :)

-------

## Strategies

- Sudoku is a puzzle game, you start with a $9 \times 9$ grid like below on the left
- The goal is to fill in missing values, such that each row, column, and block has 9 different values from 1 to 9 like on the right\
    E.g.: row 1: `1| 7 4 8 | 5 1 6 | 3 2 9 |`

```txt
   1 2 3   4 5 6   7 8 9                1 2 3   4 5 6   7 8 9
 -------------------------            -------------------------
1|       |   1   |       |           1| 7 4 8 | 5 1 6 | 3 2 9 |
2|   9   |       | 6 4 7 |           2| 1 9 5 | 2 3 8 | 6 4 7 |
3|   2 6 | 7   9 |       |           3| 3 2 6 | 7 4 9 | 5 8 1 |
 -------------------------            -------------------------
4|   6 4 | 8     |   3   |           4| 5 6 4 | 8 9 7 | 1 3 2 |
5|     3 |   5   | 9     |   ==>     5| 2 8 3 | 1 5 4 | 9 7 6 |
6|   1   |     3 | 4 5   |           6| 9 1 7 | 6 2 3 | 4 5 8 |
 -------------------------            -------------------------
7|       | 4   2 | 8 1   |           7| 6 5 9 | 4 7 2 | 8 1 3 |
8| 4 3 2 |       |   6   |           8| 4 3 2 | 9 8 1 | 7 6 5 |
9|       |   6   |       |           9| 8 7 1 | 3 6 5 | 2 9 4 |
 -------------------------            -------------------------
```

Some common strategies for reasoning are as follows, with the example for the above puzzle:

- Let consider a group as either a row, column or block
- Within a group, cells can not have the same value

    With this, you have an initial guess of what values can each cell has. E.g.:

    Consider the 1st cell, which is in the 1st row, 1st column and 1st block.\
    There is already "1" in the 1st row, "4" in the 1st column, "2, 6, 9" in the 1st block.\
    Thus, this 1st cell can only take "3, 5, 7, 8"

    ```txt
       1 2 3   4 5 6   7 8 9
     -------------------------
    1|       |   1   |       |
    2|   9   |
    3|   2 6 |
     ---------
    4|   
    5|   
    6|   
     ----
    7|   
    8| 4 
    9|   
     ----
    ```
  
- Within a group, if a missing value can lie only in one cell, well then, that cell has it. E.g.:\
    After the above process for all cells, in the 1st block, the 2nd cells can take 4 possible values "4, 5, 7, 8".\
    However, in this block, other cells can not take value "4", because there are already "4" in column "1, 3" and row "2"

    ```txt
       1 2 3   4 5 6   7 8 9
     -------------------------
    1|   ?   |
    2|   9   |       |   4   |
    3|   2 6 |
     ---------
    4|     4 |
    5|       |
    6|       |
     ---------
    7|       |
    8| 4     |
    9|       |
     ---------
    ```

- Within a block, if a missing value can lie in specific row/column, other cells in that row/column can't have it.\
    E.g.: Check the 7th block, the one in bottom left corner.\
    Because there is a "1" in the 7th row, in this block, "7" can only lie in the bottom row.\
    Thus, in the 8th block, which is right next to it, "1" can not lie in the bottom row, but only the middle row.

    ```txt
       1 2 3   4 5 6   7 8 9
     -------------------------
    1|       |   1   |       |
    2|       |
    3|       |
     ---------
    4|       |
    5|       |
    6|   1   |
     -------------------------
    7|       | 4   2 |   1   |
    8| 4 3 2 | ?   ? |       |
    9| ?   ? |   6   |       |
     -------------------------
    ```

- Within a group, if two cells have exactly two possible missing values, then that two values lie in that two cells, not other cells in the group. E.g.:

    Consider the 1st row, where the possible values for the 1st and 3rd cells are both "7, 8".\
    Other cells in the 1st will not have "7, 8". From that, we can guess that in the 3rd block, "8" must lie in the bottom row\
    Not really a good example, because these two cells are also in the same block.\
    In practice, this trick is more advanced, time-consuming.\
    But it manages to deal with many scenarios.

    ```txt
       1 2 3   4 5 6   7 8 9
     -------------------------
    1| ? 4 ? |   1   |       |
    2| 1 9 5 |       | 6 4 7 |
    3| 3 2 6 | 7   9 | ? ? ? |
     -------------------------
    ```

- As you repeating these above processes, you end up with cells which can have specific values.\
    Filling them, getting more info to update possible values of other cells.\
    Repeat this until all cells are filled. Or so you hope.
- In the extremely hard puzzles, there will be a point that all cells can take up more than one values, and all above updates lead to nothing ... Then you just have to try out a scenario and see if it leads to a valid solution.

-------

## Testing

I collect 25 test cases from [Sudoku.com](https://sudoku.com/), divided into 5 difficulty levels: ***easy, medium, hard, expert, evil*** (whatever that is).

- The methods are compared based on computation time (seconds).
- For these problems, memory cost will be insignificant to worry about.
- Without backtracking, the solver only manage to solve 20/25 puzzles.\
    With these test cases, it failed 4 expert and 1 evil puzzles, bizarre.\
    Any who, as I talked about, backtracking is ... **inevitable**.
- Using just backtracking is slow, not compared to human, I mean, it takes just `220 ms` in total.\
    It is two time slower than combining it with above strategies to reduce the search scale.
- `python` is ... well `python`. Still, the result in the table is the total time to solve 25 puzzles, so to defense `python`, it took in average only `5.6 secs`.

| Method                       |    mean    |  stddev  |   median   |    user    |   system  |     min    |     max    | solve | run |
|------------------------------|:----------:|:--------:|:----------:|:----------:|:---------:|:----------:|:----------:|:-----:|:---:|
| C++ without backtracking     |  0.089682  | 0.001774 |  0.089350  |  0.074951  |  0.015081 |  0.085642  |  0.095366  | 20/25 |  50 |
| C++ with purely backtracking |  0.220017  | 0.021765 |  0.234024  |  0.200076  |  0.019870 |  0.181504  |  0.243024  | 25/25 |  50 |
| C++ with backtracking        |  0.082581  | 0.003640 |  0.081748  |  0.072242  |  0.010713 |  0.076725  |  0.094794  | 25/25 |  50 |
| Python with backtracking     | 140.377851 | 9.113384 | 141.716168 | 147.431499 | 12.517461 | 125.713472 | 157.775039 | 25/25 |  10 |

-------

## TODO

- Use OpenCV to read the map from images, because typing is ... silly for us
