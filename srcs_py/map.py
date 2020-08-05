import itertools
from dataclasses import dataclass
from collections import namedtuple
from enum import Enum
from io import StringIO

Coords = namedtuple("Coords", "x y")
RoomType = Enum("RoomType", "start end")


@dataclass(frozen=True)
class Room:
    name: str
    coords: Coords
    type: RoomType


@dataclass
class Link:
    from_: Room
    to_: Room

    def __hash__(self):
        return id(self.from_) ^ id(self.to_)

    def __eq__(self, other):
        return self.from_ is other.from_ and self.to_ is other.to_ or \
            self.from_ is other.to_ and self.to_ is other.from_


class Map:
    def __init__(self):
        self.count_a: int = 0
        self.rooms: dict = {}
        self.links: list = []
        self.start_room: Room = None
        self.end_room: Room = None

def parse_map_str(map_str):
    map_buf = StringIO(map_str)
    map = Map()

    map.count_a = int(map_buf.readline())

    map_file_iter = iter(map_buf)
    room_type = None
    for line_in_file in map_file_iter:
        line_in_file = line_in_file.strip()

        if len(line_in_file) == 0: # игнор пустых линий
            continue
        if is_comment(line_in_file):
            continue
        if is_link(line_in_file):
            map_file_iter = itertools.chain((line_in_file,), map_file_iter)
            break
        if is_command(line_in_file):
            room_type = parse_command_line(line_in_file)
            continue
        room = parse_line_in_file(line_in_file, room_type)
        map.rooms[room.name] = room
        if room_type == RoomType.start:
            map.start_room = room
        if room_type == RoomType.end:
            map.end_room = room

        room_type = None

    for link_line in map_file_iter:
        link_line = link_line.strip()

        if len(link_line) == 0:
            continue

        if is_comment(link_line):
            continue

        link = parse_link_line(link_line, map.rooms)
        map.links.append(link)

    return map


def is_comment(line):
    if line[0] == '#':
        if len(line) == 1:
            return True
        else:
            if line[1] != '#':
                return True

    return False


def is_link(line):
    return True if ' ' not in line and '-' in line else False


def is_command(line):
    return True if line.startswith('##') else False


def parse_command_line(line):
    type_str = line[2:]
    if type_str == 'start':
        return RoomType.start
    elif type_str == 'end':
        return RoomType.end

    return None


def parse_line_in_file(line, room_type):
    data = line.split(' ')
    room_name = str(data[0])
    x = int(data[1])
    y = int(data[2])

    return Room(room_name, Coords(x, y), room_type)

def parse_link_line(line, rooms):
    data = line.split('-')
    from_room_name = str(data[0])
    to_room_name = str(data[1])

    return Link(rooms[from_room_name], rooms[to_room_name])
