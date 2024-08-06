import time
import requests
from pymongo import MongoClient
from bs4 import BeautifulSoup

url = "https://finance.yahoo.com/most-active"

response = requests.get(url)

if(response.status_code != 200):
	print("Request failed. Trying again")
	response = requests.get(url)
	if (response.status_code != 200):
		print("Request failed. Exiting")
		quit()

soup = BeautifulSoup(response.text, "html.parser")


num = 0

while True:
	data = soup.find_all("tr",{"class":"simpTblRow"})
	query = []
	
	for i in data:
		symbol = i.find("a", {"class":"Fw(600)"}).string
		name = i.find("td", {"aria-label":"Name"}).string
		price = float(i.find("td", {"aria-label":"Price (Intraday)"}).string)
		change = float(i.find("td", {"aria-label":"Price (Intraday)"}).string)
		volume = round(float((i.find("td", {"aria-label":"Volume"}).string).replace('M', '')), 2)
	
		query.append({"Symbol":symbol, "Name":name, "Price (Intraday)":price, "Change":change, "Volume":volume})	
		
	client = MongoClient()
	db = client['stocks']
	collection = db['info']
		
	collection.insert_many(query)
	print("Scraping data")
	time.sleep(180)
