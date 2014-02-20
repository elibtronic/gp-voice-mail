#
#  Runs the GUI and listens for signals on the Serial device
#
#
from settings import *
from Tkinter import *
from tkMessageBox import showerror
import httplib, urllib, time, datetime
import serial
import serial.tools.list_ports

ts = "No\n Voice Mail."
didTrig = 0
onHold = 0


#Try to find the Arduino by looking at the descriptions of the devices
try:
        for p in serial.tools.list_ports.comports():
                if re.search('Arduino Uno',str(p[1])):
                        portString = str(p[0])     
        ser = serial.Serial(portString,9600,timeout=0)
except:
        root = Tk()
        showerror("Arduino Error","Couldn't Find Arduino")
        root.destroy()
        sys.exit()



root = Tk()
ts_label = Label(root,text=ts,font=("Helvetica", 16),anchor="center")
ts_label.pack(fill=X)


def placeHold():
        global onHold
        if onHold == 1:
                onHold = 0
                hold.config(text="Hold")
        else:
                onHold = 1
                hold.config(text="On Hold")


hold = Button(root, text="Hold",command=placeHold)
hold.pack()


def checkForSignal():
        global didTrig
        line = ser.read()
        ser.flush()
        #print type(line)
        if line == "1" and didTrig == 0 and onHold == 0:
                signal_PO()
                didTrig = 1
        if didTrig == 1 and line == "0":
                ts_label.config(text='No Voice Mail.')
                didTrig = 0
                

        root.after(pollInterval,checkForSignal)
	

def signal_PO():
	global ts
	ts = datetime.datetime.now().strftime('%Y-%m-%d\n%H:%M:%S')
	pOverMessage = "You have a voice mail! " + ts
	label_message = "You have a\nvoice mail!\n" + ts
	ts_label.config(text=label_message)
	#Following will trigger a pushover.net push notification
	#Change the next few lines to whatever else suits your fancy
	conn = httplib.HTTPSConnection("api.pushover.net:443")
	conn.request("POST", "/1/messages.json",
		urllib.urlencode({
		"token": pushOver_token,
		"user": pushOver_user,
		"message": pOverMessage,
	}), { "Content-type": "application/x-www-form-urlencoded" })
	conn.getresponse()

root.title("gp Voice Mail")
root.geometry("200x200")
mFrame = Frame(root, width=150, height=150)
mFrame.pack()
root.after(pollInterval,checkForSignal)
root.mainloop()

