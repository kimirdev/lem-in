from dataclasses import dataclass
from functools import reduce
from operator import xor
from itertools import tee
from collections import OrderedDict
from io import StringIO

from srcs_py.map import Link


def mix(x, y, a):
    return x*(1 - a) + y*a


@dataclass
class Rect:
    top: int
    left: int
    bottom: int
    right: int

@dataclass
class Path:
    links: list

    def __hash__(self):
        return reduce(xor, (hash(link) for link in self.links), 0)

    def __eq__(self, other):
        return len(self.links) == len(other.links) and all(l1 == l2 for l1, l2 in zip(self.links, other.links))

class Ant:
    def __init__(self, start_room):
        self.steps = OrderedDict()
        self.path = Path([])

        self.start_room = start_room
        self.current_room = start_room
        self.next_room = start_room

        self.x = start_room.coords.x
        self.y = start_room.coords.y

    def set_step(self, step):
        if int(step) not in self.steps:
            return

        self.compute_position(step)

    def compute_position(self, step):
        integer_step = int(step)
        self.current_room = self.steps[integer_step]

        next_step = integer_step + 1

        self.next_room = self.steps[next_step] if next_step in self.steps else self.current_room

        blend_coef = step - integer_step

        self.x = mix(self.current_room.coords.x,
                     self.next_room.coords.x, blend_coef)
        self.y = mix(self.current_room.coords.y,
                     self.next_room.coords.y, blend_coef)


class Solution:
    def __init__(self):
        self.ants: dict = {}
        self.number_of_steps: int = 0
        self.error: str = None
        self.rect: Rect = None
        self.all_rooms = set()
        self.float_step = 0.0

    def set_step(self, step):
        self.float_step = step
        for ant in self.ants.values():
            ant.set_step(step)

    def move_ants_to_start(self):
        for ant in self.ants.values():
            ant.x = ant.start_room.coords.x
            ant.y = ant.start_room.coords.y

    def ants_at_step(self, int_step, direction=1):
        if direction > 0:
            return self.float_step >= int_step
        else:
            return self.float_step <= int_step


def parse_solution_str(solution_str, map):
    solution_buf = StringIO(solution_str)
    solution = Solution()

    for i in range(map.count_a):
        ant_id = str(i+1)
        solution.ants[ant_id] = Ant(map.start_room)

    solution_step = 1

    for line in solution_buf:
        line = line.strip()

        ants_per_line = line.split(' ')
        for ant_state in ants_per_line:
            separated_data = ant_state.split('-')
            ant_id = separated_data[0][1:]
            room_name = separated_data[1]
            solution.ants[ant_id].steps[solution_step] = map.rooms[room_name]
        solution_step += 1
    solution.number_of_steps = solution_step
    solution.all_rooms = find_all_rooms(solution, map)
    solution.rect = find_solution_rect(solution)
    return solution


def ants_add_initial_step(solution, map):
    for ant in solution.ants.values():
        first_step = min(ant.steps.keys())
        zero_step = first_step - 1
        ant.steps[zero_step] = map.start_room
        ant.steps.move_to_end(zero_step, False)


def pairwise(iterable):
    a, b = tee(iterable)
    next(b, None)
    return zip(a, b)


def ants_add_solution_paths(solution, map):
    for ant in solution.ants.values():
        path = ant.path
        for from_room, to_room in pairwise(ant.steps.values()):
            link = Link(from_room, to_room)
            path.links.append(link)


def find_solution_rect(solution):
    top = float('+inf')
    left = float('+inf')
    bottom = float('-inf')
    right = float('-inf')

    for ant in solution.ants.values():
        for room in ant.steps.values():
            if room.coords.y < top:
                top = room.coords.y
            elif room.coords.y > bottom:
                bottom = room.coords.y

            if room.coords.x < left:
                left = room.coords.x
            elif room.coords.x > right:
                right = room.coords.x

    return Rect(top, left, bottom, right)


def find_all_rooms(solution, map):
    all_solution_rooms = set()

    for ant in solution.ants.values():
        for room in ant.steps.values():
            if room is map.start_room or room is map.end_room:
                continue
            else:
                all_solution_rooms.add(room)

    return all_solution_rooms
