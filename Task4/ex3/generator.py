import random

with open('input.txt','w') as file:
    resultList = list()
    randNumber = random.randint(1, 100)
    for i in range(randNumber):
        resultList.append(random.randint(0, 1))
    string = str()
    string += ''.join(str(v) for v in resultList)
    print(string)
    file.write(string)
