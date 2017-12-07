# generate all combinations of N items
def powerSet(items):
    """
    Generating all combination of a set (By including or not an item). 
    explain by example:
    3 items in a set
    000
    100
    010
    001
    110
    101
    011
    111
    
    The result is 2^(number of elements in the set)
    """
    
    N = len(items)

    for i in range(2**N):
    
        comb=[]
        for j in range(N):
            if (i >> j) % 2 == 1:
                comb.append(items[j])
        yield comb
    
for x in powerSet([1,2,3]):
    print (x)