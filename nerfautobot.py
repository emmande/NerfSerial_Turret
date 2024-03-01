import tkinter as tk
import serial
import time

serialcomm = serial.Serial(
    port="COM3", baudrate=9600
    # port="/dev/ttyACM0", baudrate=9600
    , bytesize=8, timeout=2, stopbits=serial.STOPBITS_ONE
)

serialcomm.timeout = 1

def upturn():
    i="u"    
    serialcomm.write(i.encode())

def downturn():
    i="d"    
    serialcomm.write(i.encode())

def leftturn():
    i="l"    
    serialcomm.write(i.encode())

def rightturn():
    i="r"    
    serialcomm.write(i.encode())
    
def fire():
    i="f"    
    time.sleep(0.2)
    serialcomm.write(i.encode())
    

root = tk.Tk()
root.title("RoboGun Control")
btn_up=tk.Button(root,text="^",command=upturn, bg="green")
btn_up.grid(row=1,column=3, sticky="n")

btn_lft=tk.Button(root,text="<",command=leftturn, bg="green")
btn_lft.grid(row=2,column=2, sticky="w")

btn_rgh=tk.Button(root,text=">",command=rightturn, bg="green")
btn_rgh.grid(row=2,column=4, sticky="e")

btn_dwn=tk.Button(root,text="v",command=downturn, bg="green")
btn_dwn.grid(row=3,column=3, sticky="s")

btn_fire=tk.Button(root,text="FIRE",command=fire, bg="red")
btn_fire.grid(row=2,column=3, sticky="s")

root.geometry("300x300")
root.mainloop()