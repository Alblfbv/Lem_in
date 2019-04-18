#! /usr/bin/env python3
# coding: utf-8

import fileinput
from class_viewer import *

def	ft_parser():
	read = list()
	for line in fileinput.input():
		read.append(line)
	return (read)

def	ft_len_lem(read):
	i = 0
	nb_lem = 0
	while i < len(read):
		tmp = read[i].replace('\n', '')
		if tmp.isnumeric() == True:
			nb_lem = tmp
			break
		i += 1
	return nb_lem

# STORE ROOM / PATH

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

def	ft_room_path(read, room, path, i):
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
	return i

#STORE MOVE

def ft_store_move(read, move):
	tmp = Move()
	tmp.tab_move = read
	tmp.tab_move = tmp.tab_move.split(' ')
	move.append(tmp)

def	ft_move(read, move, i):
	while i < len(read):
		ft_store_move(read[i], move)
		i += 1
	i = 0

#STORE LEM

def ft_store_lem(lem, room):
	tmp_lem = Lem()
	tmp_lem.x = room.x
	tmp_lem.y = room.y
	lem.append(tmp_lem)

def	ft_lem(lem, room, nb_lem):
	j = 0
	i = 0
	while room[j].type_room != 'S':
		j += 1
	while i < int(nb_lem):
		ft_store_lem(lem, room[j])
		i += 1
