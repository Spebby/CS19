from random import randint
printy = []
itr = 1
while itr < randint(0, 1000):
    printy.append(randint(0, 100))
    itr += 1

printy.sort()
print(itr, printy)