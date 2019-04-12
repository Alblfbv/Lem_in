# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    viewer.py                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/11 12:44:46 by jfleury           #+#    #+#              #
#    Updated: 2019/04/12 16:46:08 by jfleury          ###   ########.fr        #
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

class Room:
	def __init__(self):
		self.name = ''
		self.x = 0
		self.y = 0
		self.list_neighbor = list()

class Lem:
	def __init__(self):
		self.nb_lem = 0

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
	if j > 20:
		print("Oula il y a trop de salle pour moi, merci de mettre une map avec 20 salles ou moins")
		sys.exit(0)
	return j

#----------------------------------------------STORE_LEM----------------------------------------------#

def ft_store_lem(read, lem):
	i = 0
	if (read.result_read[i].isnumeric() == False):
		i += 1
	lem.nb_lem = read.result_read[i]
	
#----------------------------------------------STORE_ROOM----------------------------------------------#

def ft_store_room(read, nb_room):
	list_room = list()
	i = 0
	j = 0
	while nb_room > 0:
		list_room.append(Room())
		nb_room -= 1
	while read.result_read[i]:
		tmp = read.result_read[i].split(" ")
		if len(tmp) != 3:
			i += 1
		else:
			list_room[j].name = tmp[0]
			list_room[j].x = tmp[1]
			list_room[j].y = tmp[2]
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
	room = []
	#Execution des fonctions
	ft_parser(read)
	nb_room = ft_store_grid(read, grid)
	ft_store_lem(read, lem)
	#Creation des objet Room
	list_room = ft_store_room(read, nb_room)
	
	window = Tk()
	window.title("Lem-In")
	window.geometry("1000x800+0+0")
	window.resizable(False, False)
	label_menu = Label(window, text='Menu', background="#223240", foreground="#D9D5D2", width=10, height=2)
	button_start = Button(window, text="Start", foreground="black", width=8, height=2)
	button_stop = Button(window, text="Stop", foreground="black", width=8, height=2)
	button_next = Button(window, text="Next", foreground="black", width=8, height=2)
	button_previous = Button(window, text="Previous", foreground="black", width=8, height=2)
	label_menu.grid(column=0, row=0)
	button_start.grid(column=0, row=1)
	button_stop.grid(column=0, row=2)
	button_next.grid(column=0, row=3)
	button_previous.grid(column=0, row=4)
	
	window.mainloop()
