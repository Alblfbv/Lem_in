#! /usr/bin/env python3
# coding: utf-8

from tkinter import *
import copy
from function_parser import *
from function_place import *
from function_move import *

#--------------------GLOBAL--------------------#

list_step = list()
list_lem = list()

#--------------------CLASS--------------------#

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

class Window:
	def __init__(self, root):
		#Root window
		root.title("Lem-In")
		root.geometry("1280x800-100+100")
		root.resizable(False, False)
		root.config(bg = "black")

class Frame_Menu:
	def __init__(self, root):
		self.fm = Frame(root, bd = 0)
		self.fm.grid(column = 1, row = 1)
		self.fm.config(bg = "black")

class Frame_Canvas:
	def __init__(self, root):
		self.fc = Frame(root, bd = 0, bg = "black")
		self.fc.grid(column = 1, row = 2)
		self.fc.config(bg = "black")

class Main_Menu:
	def __init__(self, frame_menu, root):
		self.button_start = Button(frame_menu,	text = "Play",					\
												width = 8, 						\
												height = 1, 					\
												highlightbackground = "black", 	\
												state = DISABLED, 				\
												command = lambda x = 1 : ft_move_lem(list_move, list_room, list_lem, list_step, main_canvas.canvas, main_menu))
		self.button_start.grid(column = 1, row = 1)
		self.button_reset = Button(frame_menu, 	text = "Reset",					\
												width = 8, 						\
												height = 1, 					\
												highlightbackground = "black", 	\
												command = lambda x = 2 : ft_reset_graphic(list_room, list_path, main_canvas.canvas, list_lem_static, main_menu.button_start))
		self.button_reset.grid(column = 5, row = 1)
		self.button_exit = Button(frame_menu, 	text = "Exit", 					\
												width = 8,						\
												height = 1, 					\
												highlightbackground = "black", 	\
												command = root.destroy)
		self.button_exit.grid(column = 6, row = 1)

class Main_Canvas:
	def __init__(self, frame_canvas):
		self.canvas = Canvas(frame_canvas, width = 1274, height = 766, bg = "black")
		self.canvas.grid(column = 1, row = 1)

#---------------------DEF_RESET-----------------#

def ft_init_graphic(list_room, list_path, canvas, menu):
	global list_step
	global list_lem
	ft_place_grid(canvas)
	list_lem = copy.deepcopy(list_lem_static)
	ft_place_path(list_room, list_path, canvas)
	ft_place_room(list_room, canvas)
	list_step = ft_place_lem(list_lem, canvas)
	menu.config(state="normal")


def ft_reset_graphic(list_room, list_path, canvas, list_lem_static, menu):
	global list_step
	global list_lem
	canvas.delete("all")
	ft_place_grid(canvas)
	list_lem = copy.deepcopy(list_lem_static)
	ft_place_path(list_room, list_path, canvas)
	ft_place_room(list_room, canvas)
	list_step = ft_place_lem(list_lem, canvas)
	menu.config(state="normal")

#--------------------MAIN--------------------#

if __name__ == "__main__":
	nb_lem = 0
	list_room = list()
	list_lem_static = list()
	list_move = list()
	list_path = list()

	#Parser
	read_result = ft_parser()
	nb_lem = ft_len_lem(read_result)
	i = 0
	i = ft_room_path(read_result, list_room, list_path, i)
	ft_move(read_result, list_move, i)
	ft_lem_static(list_lem_static, list_room, nb_lem)

	#Window Create
	root = Tk()
	window = Window(root)
	frame_canvas = Frame_Canvas(root)
	main_canvas = Main_Canvas(frame_canvas.fc)
	frame_menu = Frame_Menu(root)
	main_menu = Main_Menu(frame_menu.fm, root)

	ft_init_graphic(list_room, list_path, main_canvas.canvas, main_menu.button_start)

	#Place Room / Path / Lem

	root.mainloop()
