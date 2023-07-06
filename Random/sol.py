#!/usr/bin/env python3
from pwn import *
import subprocess

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

#p = process("./grader.py")
p = remote("xor-trickery.hsctf.com", 1337)
p.sendafter(
	b"solution: ",
	subprocess.run(p.recvline().decode().split(": ")[1], shell=True, stdout=subprocess.PIPE).stdout
)
lines = p.recvuntil(b"Output:\n", drop=True).split(b"\n")
lines.pop(-1)
q = int(lines.pop(0))
rec = [XorBasis() for _ in range(q + 1)]
a = []

for i, line in enumerate(map(bytes.decode, lines), start=1):
	t = int(line[0])
	if t == 1:
		x = int(line[2:])
		copy = XorBasis()
		copy.basis = rec[i - 1].basis.copy()
		copy.add(x)
		rec[i] = copy
	elif t == 2:
		x = int(line[2:])
		rec[i] = rec[i - 1]
		a.append(str(rec[i].check(x)))
	elif t == 3:
		rec[i] = rec[i - 1]
		a.append(str(rec[i].getMax()))
	elif t == 4:
		x = int(line[2:])
		rec[i] = rec[x]

p.sendline("\n".join(a).encode())
print(p.recvall().decode().strip())