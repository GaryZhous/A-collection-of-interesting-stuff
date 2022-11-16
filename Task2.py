def solution(A):
  seen = []
  n = 0
  for i in A:
    if i in seen:
      seen = []
      n += 1
    seen.append(i)

  return n+1
