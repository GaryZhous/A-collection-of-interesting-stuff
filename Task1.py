import random 
def solution(A):
  list = ["a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"]
  B = []
  for i in A:
    B.append(i)
  for i in range(len(B)):
    if B[i] == "?":
      if i == 1:
        B[i] = list[random.randint(0, 25)]
        while B[i] == B[i+1]:
          B[i] = list[random.randint(0, 25)]
      elif i == len(B)-1:
        B[i] = list[random.randint(0, 25)]
        while B[i] == B[i-1]:
          B[i] = list[random.randint(0, 25)]
      else:
        B[i] = list[random.randint(0, 25)]
        while B[i] == B[i + 1] or B[i] == B[i-1]:
          B[i] = list[random.randint(0, 25)]
  C = ''
  for i in B:
    C += i

  return C
