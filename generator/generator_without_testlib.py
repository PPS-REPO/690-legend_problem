import sys
import random
import hashlib

from random import randint as rnd

# Fixed Random Seed
hashValue = hashlib.sha256("|".join(sys.argv[1:]).encode()).hexdigest()
random.seed(hashValue)

al = int(sys.argv[1])
ar = int(sys.argv[2])
bl = int(sys.argv[3])
br = int(sys.argv[4])

a = rnd(al, ar)
b = rnd(bl, br)

print(a, b)