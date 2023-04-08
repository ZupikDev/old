class SumPrimes:
    """
    Return the sum of all primes numbers (between 2 and "prim_nbr") which is equal to "result"
    """
    def __init__(self, result: int, prime_limit_nb: int):
        self.result = result
        self.prime_limit_nb = prime_limit_nb
        
    def is_prime(self, n) -> int:
        result = True
        for i in range(2, n-1):
            if n % i == 0:
                result = False
                
        return n if result == True else False


    def sumprimes(self) -> list:
        out, temp = [], []
        stop = False
        primes = [self.is_prime(n) for n in range(2, self.prime_limit_nb) if self.is_prime(n) != False]
        
        for pnbr in primes:
            if stop:
                break
            for nbry in primes:
                if pnbr + nbry == self.result:
                    temp = (pnbr, nbry)
                    if len(out) > 0:
                        for i in out:
                            if stop:
                                break
                            else:
                                if i[0] == temp[1] and i[1] == temp[0]:
                                    stop = True
                        if stop:
                            break
                        out.append(temp)
                                
                    else:
                        out.append(temp)
                    
                    temp = ()
            
        if len(out) == 0:
            return "No result found."
        
        return out