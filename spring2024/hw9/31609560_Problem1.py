import requests
import time
from bs4 import BeautifulSoup
from pymongo import MongoClient


url = "https://finance.yahoo.com/most-active"
response = requests.get(url)
if(response.status_code != 200):
    print("Failed to connect to site. Trying again.")
    response = requests.get(url)
    if(response.status_code != 200):
        print("Failed to connect. Exiting.")
        quit()
        
soup = BeautifulSoup(response.text, "html.parser")

while True:
    row = soup.find_all("tr", {"class":"simpTblRow"})
    query = []

    for i in row:
        symbol = i.find("a", {"class":"Fw(600)"}).string
        name = i.find("td",{"aria-label":"Name"}).string
        price = float(i.find("td",{"aria-label":"Price (Intraday)"}).string)
        change = float(i.find("td",{"aria-label":"Change"}).string)
        volume = round(float((i.find("td",{"aria-label":"Volume"}).string).replace('M', '')), 2)

        query.append({"Symbol":symbol, "Name":name, "Price (Intraday)":price, "Change":change, "Volume":volume})
        


    client = MongoClient()
    db = client["Data"]
    collection = db["Stocks"]
    collection.insert_many(query)

    # myclient = MongoClient()
    # dblist = myclient.list_database_names()

    # if "Data" in dblist:
    #     print("database exists")

    # mydb = myclient["Data"]

    # collist = mydb.list_collection_names()
    # if "Stocks" in collist:
    #     print("collection exists")
    # else:
    #     print("doesnt exist")
    print("Scraping the web\n")
    time.sleep(180)