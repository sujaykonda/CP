import numpy as np

def primes(n):
    x = np.ones((n+1,), dtype=np.bool_)
    x[0] = False
    x[1] = False
    for i in range(2, int(n**0.5)+1):
        if x[i]:
            x[2*i::i] = False

    primes = np.where(x == True)[0]
    return primes

counter = 0
prime_list = primes(330000)
for p in prime_list:
    for q in prime_list:
        # turns the number into a string
        result = str(p**2 + q**3)
        if(len(result) < 10):
            continue
        if(len(result) > 10):
            break
        good = True
        for i in range(10):
            # check if i appears exactly once
            if(result.count(str(i)) != 1):
                good = False
        if good:
            counter += 1
print(counter)