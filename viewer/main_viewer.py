#! /usr/bin/env python3
# coding: utf-8

from tkinter import *
import copy
from function_parser import *
from function_place import *
from function_move import *

#--------------------CLASS--------------------#

list_step = list()
list_lem = list()

class Grid:
	def __init__(self):
		self.nb_room = 0
		self.nb_lem = 0
		self.win_width = 0
		self.win_height = 0
		self.xmax = 0
		self.ymax = 0

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
	def __init__(self, root, grid):
		#Root window
		grid.win_width = (100 * grid.nb_room)
		grid.win_height = (100 * grid.nb_room)
		geometry = "%dx%d-100+100" % (1920, 1080)
		root.title("Lem-In")
		root.resizable(False, False)
		root.geometry(geometry)
		root.config(bg = "black")

class Frame_Menu:
	def __init__(self, root):
		self.fm = Frame(root, bd = 0)
		self.fm.grid(column = 1, row = 1)
		self.fm.config(bg = "black")

class Frame_Canvas:
	def __init__(self, root):
		self.fc = Frame(root, bd = 0)
		self.fc.grid(column = 1, row = 2)

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
												command = lambda x = 2 : ft_reset_graphic(list_room, list_path, main_canvas.canvas, static_list_lem, main_menu.button_start, grid))
		self.button_reset.grid(column = 5, row = 1)
		self.button_exit = Button(frame_menu, 	text = "Exit", 					\
												width = 8,						\
												height = 1, 					\
												highlightbackground = "black", 	\
												command = root.destroy)
		self.button_exit.grid(column = 6, row = 1)

class Main_Canvas:
	def __init__(self, frame_canvas, grid):
		self.canvas = Canvas(frame_canvas, 	borderwidth=2,													\
											width = 1910,													\
											height = 1042,													\
											bg = "black",													\
											scrollregion=(0, 0, grid.nb_room * 100, grid.nb_room * 100),	\
											xscrollcommand=1,												\
											yscrollcommand=1)
		self.canvas.grid(column = 1, row = 1)
		self.canvas.grid_propagate(0)
		self.canvas.bind("<Left>",  lambda event: self.canvas.xview_scroll(-1, "units"))
		self.canvas.bind("<Right>", lambda event: self.canvas.xview_scroll( 1, "units"))
		self.canvas.bind("<Up>",    lambda event: self.canvas.yview_scroll(-1, "units"))
		self.canvas.bind("<Down>",  lambda event: self.canvas.yview_scroll( 1, "units"))
		self.canvas.focus_set()
		self.canvas.bind("<1>", lambda event: self.canvas.focus_set())

#---------------------DEF_RESET-----------------#

def ft_init_graphic(list_room, list_path, static_list_lem, canvas, menu, grid):
	global list_step
	global list_lem
	ft_place_grid(canvas, grid)
	list_lem = copy.deepcopy(static_list_lem)
	ft_place_path(list_room, list_path, canvas)
	ft_place_room(list_room, canvas)
	list_step = ft_place_lem(list_lem, canvas)
	menu.config(state="normal")


def ft_reset_graphic(list_room, list_path, canvas, list_lem_static, menu, grid):
	global list_step
	global list_lem
	canvas.delete("all")
	ft_place_grid(canvas, grid)
	list_lem = copy.deepcopy(static_list_lem)
	ft_place_path(list_room, list_path, canvas)
	ft_place_room(list_room, canvas)
	list_step = ft_place_lem(list_lem, canvas)
	menu.config(state="normal")

#--------------------MAIN--------------------#

if __name__ == "__main__":
	list_room = list()
	static_list_lem = list()
	list_move = list()
	list_path = list()
	grid = Grid()

	#Parser
	ft_parser(list_room, list_move, list_path, grid)
	ft_normalize(list_room, grid)
	ft_lem_static(static_list_lem, list_room, grid.nb_lem)

	#Window Create
	root = Tk()
	window = Window(root, grid)
	frame_canvas = Frame_Canvas(root)
	main_canvas = Main_Canvas(frame_canvas.fc, grid)
	frame_menu = Frame_Menu(root)
	main_menu = Main_Menu(frame_menu.fm, root)

	ft_init_graphic(list_room, list_path, static_list_lem, main_canvas.canvas, main_menu.button_start, grid)

	#Place Room / Path / Lem

	root.mainloop()
