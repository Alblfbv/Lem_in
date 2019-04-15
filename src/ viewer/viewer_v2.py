# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    viewer_v2.py                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/15 15:53:26 by jfleury           #+#    #+#              #
#    Updated: 2019/04/15 17:33:15 by jfleury          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -*-coding:Utf-8 -*

import os
from tkinter import *
import fileinput

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
		self.type = ""
		self.x = 0
		self.y = 0

class Lem:
	def __init__(self):
		self.x = 0
		self.y = 0

class Move:
	def __init__(self):
		self.tab_move = []

class Window:
	def __init__(self):
		pass

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
	tmp_room.name = line[0]
	tmp_room.x = line[1]
	tmp_room.y = line[2]
	if type_room == 'S':
		tmp_room.type = 'S'
	if type_room == 'E':
		tmp_room.type = 'E'
	if type_room == 'M':
		tmp_room.type = 'M'
	room.append(tmp_room)

def ft_store_lem(lem, nb_lem, room):
	i = 0
	j = 0
	tmp_lem = Lem()
	while room[j].type != 'S':
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

	#Parser
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
		i += 1
	i += 1
	#Create Lem
	ft_store_lem(lem, nb_lem, room)
	#Store Move
	while i < len(read):
		ft_store_move(read[i], move)
		i += 1
	print(move[0].tab_move[0])

