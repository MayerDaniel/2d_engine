
from random import randint
st = ''

for i in range(32*32):
    st += "%d%d," % (randint(0,2), randint(0,2))

st = st[:-1]

with open('32x32rand.txt', 'a') as the_file:
    the_file.write(st + '\n')
