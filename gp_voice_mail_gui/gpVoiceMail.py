#
#  Runs the GUI and listens for signals on the Serial device
#
#
from settings import *
from Tkinter import *
import httplib, urllib, time, serial
import time
ts = ""
ser = serial.Serial("/dev/ttyACM0")
root = Tk()


def checkForSignal():
	line = ser.readline()
	ser.flush()
	print line
	if (int(line) == 1):
		signal_PO()
	root.after(pollInterval,checkForSignal)

def signal_PO():
	global ts
	#ts = datetime.fromtimestamp(time.time()).strftime('%Y-%m-%d %H:%M:%S')
	#pOverMessage =  str("You have a voice mail! " + ts)
	pOverMessage = "You have a voice mail!"
	print pOverMessage
	#conn = httplib.HTTPSConnection("api.pushover.net:443")
	#conn.request("POST", "/1/messages.json",
		#urllib.urlencode({
		#"token": pushOver_token,
		#"user": pushOver_user,
		#"message": pOverMessage,
	#}), { "Content-type": "application/x-www-form-urlencoded" })
	#conn.getresponse()

root.title("gp Voice Mail")
root.geometry("200x200")
mFrame = Frame(root, width=150, height=150)
mFrame.pack()
root.after(pollInterval,checkForSignal)
root.mainloop()

