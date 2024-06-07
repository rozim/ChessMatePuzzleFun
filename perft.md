
https://www.chessprogramming.org/Perft
https://www.chessprogramming.org/Perft_Results

# Python (pychess) results:
```
time python perft.py
 1         20 0.0
 2        400 0.0
 3       8902 0.0
 4     197281 0.3
 5    4865609 6.4
 6  119060324 157.2
```

# libchess

## v1
```
./perft
d: 1 20 0s
d: 2 400 0s
d: 3 8902 0s
d: 4 197281 0s
d: 5 4865609 0s
d: 6 119060324 1s
d: 7 3195901860 9s
d: 8 84998978956 92s
d: 9 2439530234534 1190s

```

ut oh, problem suddently based on https://www.chessprogramming.org/Perft_Results
```
actual:
d: 9 2439530234534 1190s
d: 9 2,439,530,234,534 1190s
correct
     2,439,530,234,167

difference of 367
```
