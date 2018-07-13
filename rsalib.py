import sys
import random
from itertools import combinations

def powermod(base, exp, n):
	result = base
	exp = bin(exp)
	for i in range(3, len(exp)):
		if exp[i] == '1':
			result = (result ** 2) * base % n
		if exp[i] == '0':
			result = (result ** 2) % n
	return result

def is_prime(n):
  for i in range(2, int(n ** 0.5)+1):
    if n%i==0:
      return False
  return True

def generate_prime():
	num=random.randint(2,101)
	while True:
	  if is_prime(num):
	  	break
	  else:
	  	num=random.randint(2, 101)	  
	return num

def fin(p,q):
	return (p-1)*(q-1)

def encrypt_rsa(msg, e, n):
	return (msg ** e) % n

def get_decryption_key_odd(e ,fn, n):
	for i in range(1, n):
		if e*i%fn==1:
			return i

def decrypt_rsa(c, d, n):
	return (c ** d) % n
	
def gcd(a, b):
    a = abs(a)
    b = abs(b)
    if a < b:
        a, b = b, a
    while b != 0:
        a, b = b, a % b
    return a

def extendedGCD(a, b):
    #return a tuple of three values: x, y and z, such that x is
    #the GCD of a and b, and x = y * a + z * b
    if a == 0:
        return b, 0, 1
    else:
        g, y, x = extendedGCD(b % a, a)
        return g, x - (b // a) * y, y

def coPrime(l):
	#returns 'True' if the values in the list L are all co-prime
    #otherwise, it returns 'False'
    for i, j in combinations(l, 2):
        if gcd(i, j) != 1:
            return False
    return True

def get_decryption_key(e, fn):
    if coPrime([e, fn]):
        linearCombination = extendedGCD(e, fn)
        return linearCombination[1] % fn
    else:
        return 0

def string2numList(strn):
    """Converts a string to a list of integers based on ASCII values"""
    return [ ord(chars) for chars in pickle.dumps(strn) ]

def numList2string(l):
    """Converts a list of integers to a string based on ASCII values"""
    return pickle.loads(''.join(map(chr, l)))

def factorial(n):
  if n == 0:
    return 1
  else:
    return n * factorial(n-1)

def numberFactorization(n):
	for i in range(2, n/2):
		a = 2 ** factorial(i) % n
		q = gcd(a-1, n)
		if gcd(a-1, n) > 1:
			p = n / q
			break
	return p, q

def rsa(msg):
	p = generate_prime()
	q = generate_prime()
	n = p*q
	fn = fin(p,q)
	e = generate_prime()
	cp = coPrime([e, fn])
	print '(e, fn)=1', cp, 'e =', e, 'fn =', fn
	if cp == False:
		p = generate_prime()
		q = generate_prime()
		n = p*q
		fn = fin(p,q)
		e = generate_prime()
		cp = coPrime([e, fn])
		print '(e, fn)=1', cp, 'e =', e, 'fn =', fn
	c = 0
	print 'message=', msg
	print 'p=', p
	print 'q=', q
	print 'n=', n
	print 'fn=', fn
	while (e > fn):
		e = generate_prime()
	print 'e=', e
	c = encrypt_rsa(msg, e, n)
	print 'cipher=', c
	d = get_decryption_key(e, fn)
	print 'd=e^-1%fn)=1', get_decryption_key(e, fn)
	msgd = decrypt_rsa(c, d, n)
	print 'message=', msgd
	print '(fn,e)=', gcd(fn, e)
	print '(n,e)=', gcd(n, e)
	print p, ' is prime?', is_prime(p)
	print q,' is prime?', is_prime(q)
	print e,' is prime?', is_prime(e)
