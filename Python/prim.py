from turtle import *


ITER = 16
SCALE = 10

speed(5)

list = [1,1]
i = 0

def sqare(a):
    n = 0
    while n < 4:
        left(90)
        forward(a)
        n += 1


while i < ITER-2:
    list.append(list[i]+list[1+i])
    i += 1

for x in list:
    circle(x*SCALE,90)
    sqare(x*SCALE)




