#!/usr/bin/python

rows = []

width = 20
height = 20

rows.append([1] * (width + 1))

for i in range(1,height + 1):
    row = [ rows[i-1][0] ]
    for j in range(1, width + 1):
        row.append( row[j-1] + rows[i-1][j] )
    rows.append(row)

print rows[2][2]
print rows[20][20]
