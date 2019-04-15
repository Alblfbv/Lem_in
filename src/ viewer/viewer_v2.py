# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    viewer_v2.py                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/15 15:53:26 by jfleury           #+#    #+#              #
#    Updated: 2019/04/15 20:09:34 by jfleury          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -*-coding:Utf-8 -*

import os
from tkinter import *
import fileinput
import time

#---------------------------------Class---------------------------------#

class Grid:
	def __init__(self):
		self.size_x = 0
		self.size_y = 0
		self.nb_room = 0
		self.nb_lem = 0

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
		self.can = ''
		self.x = 0
		self.y = 0

class Move:
	def __init__(self):
		self.tab_move = []

#----------------------------------Tk-----------------------------------#

class Window:
	def __init__(self, root, grid, room, lem, path, move):
		#Root window
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
		while i < len(path):
			j = 0
			k = 0
			while room[j].name != path[i].path_1:
				j += 1
			while room[k].name != path[i].path_2:
				k += 1
			canvas.create_line(room[j].x + 35, room[j].y + 35, room[k].x + 35, room[k].y + 35, fill="white", width="4")
			i += 1
		#Place Room
		i = 0
		while i < len(room):
			if room[i].type_room == 'S':
				canvas.create_oval(room[i].x, room[i].y, room[i].x + 75, room[i].y + 75, outline="green", width="4", fill="#005085")
			if room[i].type_room == 'E':
				canvas.create_oval(room[i].x, room[i].y, room[i].x + 75, room[i].y + 75, outline="red", width="4", fill="#005085")
			if room[i].type_room == 'M':
				canvas.create_oval(room[i].x, room[i].y, room[i].x + 75, room[i].y + 75, outline="white", width="4", fill="#005085")
			i += 1
		#Place Lem
		i = 0
		while i < len(lem):
			tmp = Lem()
			l = canvas.create_rectangle(lem[i].x + 25, lem[i].y + 25, lem[i].x + 50, lem[i].y + 50, outline="black", width="2")
			lem[i].can = l
			i += 1
		x = y = 5
		for loops in range(50):
			time.sleep(0.005)
			canvas.move(lem[0].can, x, y)
			canvas.update()


#---------------------------------Funct---------------------------------#

def	ft_parser():
	read = list()
	for line in fileinput.input():
		read.append(line)
	return (read)

def ft_store_room(read, room, type_room):
	tmp_room = Room()
	line = read.split(' ')
	if len(line) != 3:
		return
	line[2] = line[2].replace('\n', '')
	if line[1].isnumeric() == False or line[2].isnumeric() == False:
		return
	tmp_room.name = str(line[0].replace('\n', ''))
	tmp_room.x = int(line[1])
	tmp_room.y = int(line[2])
	if type_room == 'S':
		tmp_room.type_room = 'S'
	if type_room == 'E':
		tmp_room.type_room = 'E'
	if type_room == 'M':
		tmp_room.type_room = 'M'
	room.append(tmp_room)

def ft_store_path(read, path, room):
	tmp_path = Path()
	line = read.split('-')
	if len(line) != 2:
		return
	tmp_path.path_1 = str(line[0].replace('\n', ''))
	tmp_path.path_2 = str(line[1].replace('\n', ''))
	path.append(tmp_path)

def ft_store_lem(lem, nb_lem, room):
	i = 0
	j = 0
	tmp_lem = Lem()
	while room[j].type_room != 'S':
		j += 1
	tmp_lem.x = room[j].x
	tmp_lem.y = room[j].y
	while i < int(nb_lem):
		lem.append(tmp_lem)
		i += 1

def ft_store_move(read, move):
	tmp = Move()
	tmp.tab_move = read
	tmp.tab_move = tmp.tab_move.split(' ')
	move.append(tmp)

#---------------------------------Main----------------------------------#

if __name__ == "__main__":
	#Class
	grid = Grid()
	room = list()
	lem = list()
	move = list()
	path = list()

#-----------Parser
	read = ft_parser()
	i = 0
	#Nb_lem
	while i < len(read):
		tmp = read[i].replace('\n', '')
		if tmp.isnumeric() == True:
			nb_lem = tmp
			break
		i += 1
	#Store Room
	while i < len(read):
		if (read[i] == "\n"):
			break
		if read[i] == "##start\n":
			i += 1
			ft_store_room(read[i], room, 'S')
			i += 1
		if read[i] == "##end\n":
			i += 1
			ft_store_room(read[i], room, 'E')
			i += 1
		ft_store_room(read[i], room, 'M')
		ft_store_path(read[i], path, room)
		i += 1
	i += 1
	#Create Lem
	ft_store_lem(lem, nb_lem, room)
	#Store Move
	while i < len(read):
		ft_store_move(read[i], move)
		i += 1
#----------Window
	root = Tk()
	display = Window(root, grid, room, lem, path, move)
	root.mainloop()

