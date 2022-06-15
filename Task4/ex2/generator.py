import random

with open('input.txt','w') as file:
    resultList = list()
    randNumber = random.randint(1, 1000)
    for i in range(randNumber):
        resultList.append(random.randint(1, 10000))
    string = str(randNumber) + '\n'
    string += ' '.join(str(v) for v in resultList)
    print(string)
    file.write(string)
