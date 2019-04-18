#! /usr/bin/env python3
# coding: utf-8

from tkinter import *
from function_parser import *
from function_place import *
from function_move import *
from class_viewer import *

if __name__ == "__main__":
	nb_lem = 0
	list_room = list()
	list_lem = list()
	list_move = list()
	list_path = list()
	list_step = list()

	#Parser
	read_result = ft_parser()
	nb_lem = ft_len_lem(read_result)
	i = 0
	i = ft_room_path(read_result, list_room, list_path, i)
	ft_move(read_result, list_move, i)
	print(nb_lem)
	ft_lem(list_lem, list_room, nb_lem)

	#Window Create
	root = Tk()
	window = Window(root)
	frame_menu = Frame_Menu(root)
	frame_canvas = Frame_Canvas(root)
	main_menu = Main_Menu(frame_menu.fm)
	main_canvas = Main_Canvas(frame_canvas.fc)

	#Place Room / Path / Lem
	ft_place_path(list_room, list_path, main_canvas.canvas)
	ft_place_room(list_room, main_canvas.canvas)
	list_step = ft_place_lem(list_lem, main_canvas.canvas)

	#Move Lem
	ft_move_lem(list_move, list_room, list_lem, list_step, main_canvas.canvas)
	root.mainloop()
