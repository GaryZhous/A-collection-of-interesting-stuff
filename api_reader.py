import json
import requests

url = "enter the url of the online json file here"
req = requests.get(url)
with open("requested.json", "wb") as f:
  f.write(req.text)
file_requests = req.json()
keys = []
vals = []
with open("requested.json") as f:
  data = json.load(f)
for i in data:
  for key, value in i:
    keys.append(key)
    vals.append(value)
 
 for j in range(len(keys)):
    print("key number ", j+1, "is ", keys[j], " and its corresponding value is ", vals[j])
