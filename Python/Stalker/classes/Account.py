from bs4 import BeautifulSoup
import requests
import winsound

class Account:

    def __init__(self, log_, pass_, rau_):
        self.login = log_
        self.password = pass_
        self.rau = rau_
        self.data = None
        self.session = requests.Session()
        self.soup = None
        self.login_url = "https://platforma.polsl.pl/" + self.rau + "/login/index.php"
        self.success = False
        self.last_logins = []
        self.list_initiatet = False

    def log(self):
        # odwiedzenie strony z loginem tylko po to, by pobrac logintoken
        html = self.session.get(self.login_url)
        self.soup = BeautifulSoup(html.text, "html.parser")
        token = self.soup.find_all("input", {"name": "logintoken"})
        # przypisanie do zmiennej value, wartosci logintoken pobranej ze strony
        for attr in token:
            token_value = attr["value"]
        self.data = {"username": self.login, "password": self.password, "anchor": "", "logintoken": token_value}
        resp = self.session.post(self.login_url, data=self.data)
        sup = BeautifulSoup(resp.text, "html.parser")
        tmp = sup.find("a", {"class": "accesshide"})
        if tmp is None:
            # print("Login successful!")
            self.success = True
            return True
        else:
            return False
            # print("Login failed!")
            exit(1)

    def initiate(self, nr):
        for x in range(0, nr):
            self.last_logins.append({"name": None, "day": 0, "hour": 0, "minute": 0, "second": 0})
        self.list_initiatet = True

    def stalk(self, links):
        if not self.list_initiatet:
            self.initiate(len(links))
        index = 0
        for link in links:
            counter = 0
            req = self.session.get(link)
            self.soup = BeautifulSoup(req.text, "html.parser")
            #print(self.soup)
            lnks = self.soup.find_all("dd")
            # lnks = self.soup.find_all("li", {"class": "contentnode"})

            for lnk in lnks:
                counter += 1

            temp = 1
            seen = None
            for lnk in lnks:
                if temp == counter:
                    seen = lnk.string
                temp += 1
            last_visit = seen[seen.find("(")+1:seen.find(")")]
            # obsluga dni
            if "dzień" in last_visit:
                try:
                    days = int(last_visit[0:last_visit.find("dzień")])
                    last_visit = last_visit[last_visit.find("dzień") + 6:-1]
                except:
                    days = 0
            elif "dni" in last_visit:
                try:
                    days = int(last_visit[0:last_visit.find("dni")])
                    last_visit = last_visit[last_visit.find("dni")+4:-1]
                except:
                    days = 0
            else:
                days = 0
            # obsluga godzin i minut
            try:
                hours = int(last_visit[0:last_visit.find("g")])
            except:
                hours = 0

            if "min" in last_visit:
                try:
                    minutes = int(last_visit[last_visit.find("min") - 3:last_visit.find("min")])
                except:
                    minutes = int(last_visit[last_visit.find("min") - 2:last_visit.find("min")])
            else:
                minutes = 0

            # try:
            #     minutes = int(last_visit[last_visit.find(".")+1:last_visit.find("m")])
            # except:
            #     minutes = 0
            if "sek" in last_visit:
                try:
                    seconds = int(last_visit[last_visit.find("sek") - 3:last_visit.find("sek")])
                except:
                    seconds = int(last_visit[last_visit.find("sek") - 2:last_visit.find("sek")])
            else:
                seconds = 0
            teacher = self.soup.title.string
            teacher = teacher[0:teacher.find(":")]
            if self.has_refreshed(self.last_logins[index], days, hours, minutes, seconds):
                print(teacher + " has refreshed!!")
                winsound.Beep(2500, 1000)

            self.last_logins[index]["name"] = teacher
            self.last_logins[index]["day"] = days
            self.last_logins[index]["hour"] = hours
            self.last_logins[index]["minute"] = minutes
            self.last_logins[index]["second"] = seconds
            index += 1
            # w teacher - nazwa prowadzacego, w hours - ile h temu logowal, w minutes - ile minut temu logowal
            print(teacher + " last seen: " + str(days) + " days, " + str(hours) + " h, " + str(minutes) + " min, " + str(seconds) + " sec ago")
            # print(teacher + str(self.last_logins[index-1]))
            # print("----------------")
        print("---------------------------")
    def has_refreshed(self, last_date, d, h, m, s):
        if((d < last_date["day"] ) or
                (d == last_date["day"] and h < last_date["hour"]) or
                (d == last_date["day"] and h == last_date["hour"] and m < last_date["minute"]) or
                (d == last_date["day"] and h == last_date["hour"] and m == last_date["minute"] and s < last_date["second"])):
            return True
        return False
