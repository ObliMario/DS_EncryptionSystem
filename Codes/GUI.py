#!/usr/bin/env python3
import tkinter  
import os

from tkinter import filedialog
from tkinter import *
from tkinter import messagebox as MessageBox

Codebool = None

root = Tk()
candestroy=False
inputtxt = Text(root, height = 10, width = 25, bg = "light yellow") 
Output = Text(root, height = 5, width = 25, bg = "light cyan") 
CodeButton = Button(root, height = 2, width = 20, text ="Code", command = lambda:Take_inputCode()) 
DecodeButton = Button(root, height = 2, width = 20, text ="Decode", command = lambda:Take_inputDecode()) 
l = Label(text = "ASD")
#ME QUEDE AQUI, TENGO QUE CREAR UN .SH PARA CODIFICAR Y PONER EL OUTPUT EN LA OTRA CAJA
def Take_inputCode(): 
    Output.delete('1.0', END)
    INPUT = inputtxt.get("1.0", "end-1c") 
    inputfile = open('uncoded.txt','w')
    inputfile.write(INPUT)
    inputfile.close()
    os.system("./ACodingText.sh")
    outputfile = open('coded.txt','r')
    Output.insert(END, outputfile.read())
    outputfile.close()

def Take_inputDecode(): 
    Output.delete('1.0', END)
    INPUT = inputtxt.get("1.0", "end-1c") 
    os.system("./ADecodingText.sh "+INPUT)
    outputfile = open('decoded.txt','r')
    Output.insert(END, outputfile.read())
    
def CodeCallBack():
    root.filename =  filedialog.askopenfilename(initialdir = "~/Escritorio/Codes",title = "Select file",filetypes = (("all files","*.*"),("image files","*.jpg *.jpeg"),("video files","*.mp4"),("audio files","*.mp3 *.wav"),("compressed files","*.zip *.tar.xz *.7z")))
    os.system("./ACoding.sh "+root.filename)
def DecodeCallBack():
    root.filename =  filedialog.askopenfilename(initialdir = "~/Escritorio/Codes",title = "Select file",filetypes = (("ds files","*.ds"),("ds files","*.ds")))
    os.system("./ADecoding.sh "+root.filename)

def TextCodeCallBack():
    Output.delete('1.0', END)
    inputtxt.delete('1.0', END)
    #************************
    global candestroy,l,CodeButton
    if(candestroy):
        l.forget() 
        DecodeButton.forget() 
    #************************
    l = Label(text = "Enter Text to Code") 
    l.pack() 
    CodeButton.pack() 
    inputtxt.pack() 
    Output.pack() 
    candestroy=True

def TextDecodeCallBack():
    Output.delete('1.0', END)
    inputtxt.delete('1.0', END)
    #************************
    global candestroy,l,CodeButton
    if(candestroy):
        l.forget() 
        CodeButton.forget() 
    #************************
    l = Label(text = "Enter Text to Decode") 
    l.pack() 
    DecodeButton.pack() 
    inputtxt.pack() 
    Output.pack() 
    candestroy=True

CB = tkinter.Button(root, text ="Code", command = CodeCallBack)
DB = tkinter.Button(root, text ="Decode", command = DecodeCallBack)
TCB = tkinter.Button(root, text ="Code Text", command = TextCodeCallBack)
TDB = tkinter.Button(root, text ="Decode Text", command = TextDecodeCallBack)

CB.pack()
DB.pack()
TCB.pack()
TDB.pack()

root.mainloop()
