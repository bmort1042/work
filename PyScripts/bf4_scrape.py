import platform
import pandas as pd
from bs4 import BeautifulSoup
from selenium import webdriver


# PhantomJS files have different extensions
# under different operating systems
if platform.system() == 'Windows':
    PHANTOMJS_PATH = './phantomjs.exe'
else:
    PHANTOMJS_PATH = './phantomjs'


# here we'll use pseudo browser PhantomJS,
# but browser can be replaced with browser = webdriver.FireFox(),
# which is good for debugging.
browser = webdriver.PhantomJS(PHANTOMJS_PATH)
browser.get('http://battlelog.battlefield.com/bf4/servers/show/pc/311f9f27-5ac9-46d0-a061-bf455fbf5af4/MIgaming-us-5-Vanilla-CQ/')

# let's parse our html
soup = BeautifulSoup(browser.page_source, "html.parser")
# get all the games
games = soup.find_all('tr')

player_list = soup.find('table', class_='table table-hover scoreboard')

a=[]
b=[]
c=[]
d=[]
e=[]

for row in player_list.findAll("tr"):
	cells = row.findAll('td')
	if len(cells)==5:
		a.append(cells[0].find(text=True))
		b.append(cells[0].find(text=True))
		c.append(cells[0].find(text=True))
		d.append(cells[0].find(text=True))
		e.append(cells[0].find(text=True))

df=pd.DataFrame(a,columns=['Number'])
df['player']=b
df['kills']=c
df['deaths']=d
df['score']=e
df

# and print out the html for first game
print games

#I need to write a loop, or find some other way programatically to extract on the users information from table

