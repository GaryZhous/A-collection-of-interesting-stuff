import csv
class reading():
  def __init__(self, type='a'):
    self.type = type
  def write_text(self, title):
    with open("companies.csv", "a") as fopen:
        csv_writer = csv.writer(fopen)
        csv_writer.writerow([self.type, title])
companies = []
positions = []
object = open("companies.txt", "r")
filetext = object.readline()
while (filetext):
  company = ''
  position = ''
  count = 0
  while filetext[count] != ",":
    company += filetext[count]
    count += 1
  while count +1 < len(filetext):
    position += filetext[count+1]
    count += 1
  companies.append(company)
  positions.append(position.rstrip())
  filetext = object.readline()


for i in range(len(companies)):
  read = text_reader_sub.reading(companies[i])
  read.write_text(positions[i])
  
#I use csv to record my failure of winter job hunt...
