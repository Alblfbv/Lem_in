# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    viewer.py                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/11 12:44:46 by jfleury           #+#    #+#              #
#    Updated: 2019/04/15 15:42:33 by jfleury          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -*-coding:Utf-8 -*

import os
from tkinter import *
import fileinput

#----------------------------------------------CLASS----------------------------------------------#

class Read:
	def __init__(self):
		self.result_read = ''
		self.nb_readline = 0

class Grid:
	def __init__(self):
		self.x = 0
		self.y = 0
		self.nb_room = 0
		self.nb_lem = 0

class Room:
	def __init__(self):
		self.name = ''
		self.type = ''
		self.x = 0
		self.y = 0
		self.list_neighbor = list()

class Move:
	def __init__(self):
		self.move = ''

class Lem:
	def __init__(self):
		self.name = ''
		self.x = 0
		self.y = 0

class App:
	def __init__(self, root, room, grid, lem):
		root.title("Lem-In")
		root.geometry("1280x800-100+100")
		root.resizable(False, False)
		#Frame
		frame_menu = Frame(root, bd =0, bg="#005085")
		frame_menu.grid(column=1, row=1)
		frame_canvas = Frame(root, bd=0, bg="#005085")
		frame_canvas.grid(column=1, row=2)
		#Menu
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
		#Canvas
		canvas = Canvas(frame_canvas, bd=0, background="#005085", width=1274, height=766)
		canvas.grid(column=1, row=1)
		#Place path
		i = 0
		while i < grid.nb_room:
			j = 0
			while room[i].list_neighbor[j]:
				k = 0
				while room[i].list_neighbor[j] != room[k].name:
					k += 1
				x_k = room[k].x
				y_k = room[k].y
				canvas.create_line(room[i].x + 35, room[i].y + 35, x_k + 35, y_k + 35, fill="white", width="4")
				j += 1
				if (j == 2):
					break
			i += 1
		#Place room
		i = 0
		while i < grid.nb_room:
			if room[i].type == "S":
				canvas.create_oval(room[i].x, room[i].y, room[i].x + 70, room[i].y + 70, width=4, outline='green', fill="#005085")
			elif room[i].type == "E":
				canvas.create_oval(room[i].x, room[i].y, room[i].x + 70, room[i].y + 70, width=4, outline='red', fill="#005085")
			else:
				canvas.create_oval(room[i].x, room[i].y, room[i].x + 70, room[i].y + 70, width=4, outline='white', fill="#005085")
			i += 1
		i = 0
		j = 0
		l = []
		while room[j].type != 'S':
			j += 1
		while i < grid.nb_lem:
			l.append(canvas.create_rectangle(room[j].x + 20, room[j].y + 20, room[j].x + 50, room[j].y + 50, width=2, fill="black"))
			i += 1
		canvas.move(l[0], room[1].x, room[1].y)

#----------------------------------------------PARSER----------------------------------------------#

def	ft_parser(read):
	for line in fileinput.input():
		read.result_read += line
		read.nb_readline += 1
	read.result_read = read.result_read.split('\n')

#----------------------------------------------STORE_GRID----------------------------------------------#

def ft_store_grid(read, grid):
	x = 0
	y = 0
	i = 0
	j = 0
	while read.result_read[i]:
		tmp = read.result_read[i].split(" ")
		if len(tmp) != 3:
			i += 1
		else:
			if x < int(tmp[1]):
				x = int(tmp[1])
			if y < int(tmp[2]):
				y = int(tmp[2])
			i += 1
			j += 1
	grid.x = x
	grid.y = y
	grid.nb_room = j
	if j > 20:
		print("Oula il y a trop de salle pour moi, merci de mettre une map avec 20 salles ou moins")
		sys.exit(0)
	return j

#----------------------------------------------STORE_LEM----------------------------------------------#

def ft_store_lem(read, grid):
	i = 0
	j = 0
	list_lem = list()
	while read.result_read[i] != '':
		i += 1
	i += 1
	while read.result_read[i]:
		list_lem.append(read.result_read[i])
		i += 1
		j += 1
	grid.nb_lem = j
	return list_lem

#----------------------------------------------STORE_ROOM----------------------------------------------#

def ft_store_room(read, grid):
	list_room = list()
	i = 0
	j = 0
	k = grid.nb_room
	while k > 0:
		list_room.append(Room())
		k -= 1
	while read.result_read[i]:
		start = 0
		if read.result_read[i] == "##start":
			start = 1
			i += 1
		if read.result_read[i] == "##end":
			start = 2
			i += 1
		tmp = read.result_read[i].split(" ")
		if len(tmp) != 3:
			i += 1
		else:
			list_room[j].name = tmp[0]
			if start == 1:
				list_room[j].type = 'S'
			elif start == 2:
				list_room[j].type = 'E'
			else:
				list_room[j].type = 'M'
			list_room[j].x = (int(tmp[1]) + 1) * 75
			list_room[j].y = (int(tmp[2]) + 1) * 75
			i += 1
			j += 1
	i = 0
	while read.result_read[i]:
		tmp = read.result_read[i].split("-")
		if len(tmp) != 2:
			i += 1
		else:
			j = 0
			while tmp[0] != list_room[j].name:
				j += 1
			if tmp[0] == list_room[j].name:
				list_room[j].list_neighbor.append(tmp[1])
			j = 0
			while tmp[1] != list_room[j].name:
				j += 1
			if tmp[1] == list_room[j].name:
				list_room[j].list_neighbor.append(tmp[0])
			i += 1
	return list_room

#----------------------------------------------MAIN----------------------------------------------#

if __name__ == "__main__":
	#Creation des objet de class Grid / Lem / Read
	grid = Grid()
	lem = Lem()
	read = Read()
	#Execution des fonctions
	ft_parser(read)
	ft_store_grid(read, grid)
	list_room = ft_store_room(read, grid)
	list_lem = ft_store_lem(read, grid)

	#Creation de la fenetre
	#
	root = Tk()
	display = App(root, list_room, grid, list_lem)
	root.mainloop()
