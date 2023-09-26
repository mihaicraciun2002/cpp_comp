import sys

class pair:
    first = 0
    second = 0
    def __init__(self):
        self.first = 0
        self.second  = 0
    def __init__(self, valFirst, valSecond):
        self.first = valFirst
        self.second = valSecond

LIMIT_SYS = 1000000

sys.setrecursionlimit(LIMIT_SYS)

def euclid(a, b):
    if(b == 0):
        return pair(1, 0)
    quotient = a // b
    remainder = a % b
    rest = euclid(b, remainder)

    x = rest.second
    y = rest.first - quotient * rest.second
    return pair(x, y)

DEBUG_MODE = bool(False)
ATTEMPT_WRITE_CORRECT = bool(True)


if DEBUG_MODE:
    fin = open("aux.in", "r")
    fout = open("aux.out", "w")
else:
    fin = sys.stdin
    fout = sys.stdout

finBuff = fin.read().split()
n = int(finBuff[0])

powNN = 1
powNN1 = 1


for index in range(1, n + 1):
    powNN = powNN * n
    powNN1 = powNN1 * (n - 1)

S = int(0)

powNAux = 1
powN1Aux = powNN1

for index in range(1, n + 1):
    S += int(finBuff[index]) * powNAux * powN1Aux
    powNAux *= n
    powN1Aux //= n - 1

A = powNN1
B = powNN

P = euclid(B, A)
B1 = P.first

sHelper = A - (S % A)

firstGuy = sHelper * B1
firstGuy %= A
firstGuy += A
firstGuy %= A

lastGuy = (firstGuy * powNN + S) // powNN1

if(lastGuy == 0):
    lastGuy = powNN

lastGuyCopy = lastGuy

if ATTEMPT_WRITE_CORRECT:

    ansString = str("")


    while (lastGuyCopy):
        ansString += str(lastGuyCopy % int(10))
        lastGuyCopy //= int(10)

    sizeString = len(ansString)
    index = sizeString - 1

    while (index >= 0):
        fout.write(ansString[index])
        index = index - 1


    fout.write('\n')

else:
    fout.write(str(lastGuy))
    fout.write('\n')

fin.close()
fout.close()
