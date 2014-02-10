from Tkinter import *

root = Tk()

def callback():
    #print "clicked at", event.x, event.y 
    print "Reset"

cTriggered = Canvas(root, width=100,height=100)
cTriggered.create_line(0,100,200,100)
cTriggered.pack()
bReset = Button(root, text="Reset", command=callback)
bReset.pack()
mFrame = Frame(root, width=250, height=250)
mFrame.pack()
#frame.bind("<Button-1>", callback)





root.mainloop()
