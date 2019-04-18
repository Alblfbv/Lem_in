#! /usr/bin/env python3
# coding: utf-8

from tkinter import *

class Room:
	def __init__(self):
		self.name = ""
		self.type_room = ""
		self.x = 0
		self.y = 0

class Path:
	def __init__(self):
		self.path_1 = ''
		self.path_2 = ''

class Lem:
	def __init__(self):
		self.x = 0
		self.y = 0

class Move:
	def __init__(self):
		self.tab_move = []

class Display:
	def __init__(self):
		self.name = list()
		self.x = []
		self.y = []

class Window:
	def __init__(self, root):
		#Root window
		root.title("Lem-In")
		root.geometry("1280x800-100+100")
		root.resizable(False, False)

class Frame_Menu:
	def __init__(self, root):
		self.fm = Frame(root, bd =0)
		self.fm.grid(column=1, row=1)

class Frame_Canvas:
	def __init__(self, root):
		self.fc = Frame(root, bd=0, bg="#005085")
		self.fc.grid(column=1, row=2)

class Main_Menu:
	def __init__(self, frame_menu):
		button_start = Button(frame_menu, text="Play", width=8, height=1)
		button_start.grid(column=1, row=1)
		button_stop = Button(frame_menu, text="Pause", width=8, height=1)
		button_stop.grid(column=2, row=1)
		button_next = Button(frame_menu, text="<<", width=8, height=1)
		button_next.grid(column=3, row=1)
		button_previous = Button(frame_menu, text=">>", width=8, height=1)
		button_previous.grid(column=4, row=1)
		button_previous = Button(frame_menu, text="Reset", width=8, height=1)
		button_previous.grid(column=5, row=1)
		button_previous = Button(frame_menu, text="Exit", width=8, height=1)
		button_previous.grid(column=6, row=1)
		compteur = 0
		self.affichage_compteur = Label(frame_menu, text=str(compteur), width=8, height=1)
		self.affichage_compteur.grid(column=7, row=1)

class Main_Canvas:
	def __init__(self, frame_canvas):
		self.canvas = Canvas(frame_canvas, bd=0, background="#005085", width=1274, height=766)
		self.canvas.grid(column=1, row=1)
