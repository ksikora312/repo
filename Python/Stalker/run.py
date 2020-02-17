from classes import Account as acc
import time
from tkinter import *

login = input("Login: ")
password = input("Password: ")
rau = input("Faculty (eg. rau2): ")
account = acc.Account(login, password, rau)
account.log()
links = []
temp = None
if account.success:
    while temp != "end":
        temp = input("Enter url to prifle you would like to stalk (\"end\" if that's all)")
        if temp != "end":
            links.append(temp)
while account.success:
    account.stalk(links)
    time.sleep(60)
