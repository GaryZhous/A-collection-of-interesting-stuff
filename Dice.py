import random

def throwDice():
  sum = random.randint(1, 6) + random.randint(1, 6)
  return sum

def hehehe(choice, outcome, decision):
  if decision == 1:
    winLose = "won"
  elif decision == 0:
    winLose = "tied"
  elif decision == -1:
    winLose = "lost"
  return "You chose " + choice + "\n" + "total was " + str(outcome) + "\nYou " + winLose + "!"

def decide(choice, outcome):
  if choice == "l" and outcome < 7 or choice == "h" and outcome > 7:
    return 1
  if outcome == 7:
    return 0
  else:
    return -1

choice = input("h or l:")
outcome = throwDice()
decision = decide(choice, outcome)
print(hehehe(choice, outcome, decision))
