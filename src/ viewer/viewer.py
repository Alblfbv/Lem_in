# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    viewer.py                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/11 12:44:46 by jfleury           #+#    #+#              #
#    Updated: 2019/04/11 18:08:02 by jfleury          ###   ########.fr        #
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
	def __init__(self, name, x, y, neighbor):
		self.name = name
		self.x = x
		self.y = y
		self.neighbor = neighnbor

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
	grid.x = x
	grid.y = y

#----------------------------------------------STORE_LEM----------------------------------------------#

def ft_store_lem(read, lem):
	i = 0
	if (read.result_read[i].isnumeric() == False):
		i += 1
	lem.nb_lem = read.result_read[i]
	
#----------------------------------------------STORE_ROOM----------------------------------------------#

def ft_store_room(read):
	pass

#----------------------------------------------MAIN----------------------------------------------#

if __name__ == "__main__":
	#Creation des objet de class Grid / Lem / Read
	grid = Grid()
	lem = Lem()
	read = Read()
	#Execution des fonctions
	ft_parser(read)
	ft_store_grid(read, grid)
	print(grid.x)
	print(grid.y)
	ft_store_lem(read, lem)
	ft_store_room(read)
	window = Tk()
	bouton_quitter = Button(window, text="Quitter", command=window.quit)
	bouton_quitter.pack()
	window.mainloop()
