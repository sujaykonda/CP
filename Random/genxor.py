import itertools
import random
import sys

# xor basis
class XorBasis:
	def __init__(self):
		self.basis = [0] * 32
	
	def add(self, mask):
		for i in range(31, -1, -1):
			if self.getbit(mask, i):
				if not self.basis[i]:
					self.basis[i] = mask
					return
				mask ^= self.basis[i]
	
	def check(self, mask):
		for i in range(31, -1, -1):
			if self.getbit(mask, i) and self.basis[i]:
				mask ^= self.basis[i]
		if mask == 0:
			return 1
		else:
			return 0
	
	def getMax(self):
		mx = 0
		for i in range(31, -1, -1):
			if not self.getbit(mx, i) and self.basis[i]:
				mx ^= self.basis[i]
		return mx
	
	@staticmethod
	def getbit(num, bit):
		return (num >> bit) & 1

q = 100000
s = [str(q)]
rec = [XorBasis() for _ in range(q + 1)]
a = []
for i in range(1, q + 1):
	if random.randint(0, 9) == 0:
		t = random.randint(3, 4)
	else:
		t = random.randint(1, 2)
	line = str(t)
	if t == 1:
		x = random.randint(1, int(1e9 - 1))
		line += ' ' + str(x)
		copy = XorBasis()
		copy.basis = rec[i - 1].basis.copy()
		copy.add(x)
		rec[i] = copy
	elif t == 2:
		x = random.randint(1, int(1e9 - 1))
		line += ' ' + str(x)
		rec[i] = rec[i - 1]
		a.append(str(rec[i].check(x)))
	elif t == 3:
		rec[i] = rec[i - 1]
		a.append(str(rec[i].getMax()))
	elif t == 4:
		x = random.randint(0, i - 1) // 10
		line += ' ' + str(x)
		rec[i] = rec[x]
	s.append(line)

print("\n".join(s))

o = input("")
print(len(o))
print(o)
if " ".join(a) == o:
	print("flag{y0u_G0t_th1s}")
else:
	print("you are wrong")
	print("correct answer:")
	print(a)