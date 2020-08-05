import fileinput
import sys
from itertools import tee, islice
import re

from srcs_py.map import parse_map_str, Map
from srcs_py.parser import parse_solution_str, Solution
import srcs_py.view as view

def extract_map_and_solution(input_data):
    solution_begin = re.search('^L', input_data, re.MULTILINE) # находит начало решения
    i1, i2 = tee(input_data) # делает два итератора (копии)
    i1 = islice(i1, solution_begin.start()) # копирует до начало решения
    i2 = islice(i2, solution_begin.start(), None) # копирует от начало решения и до конца
    map_data = ''.join(i1)
    solution_data = ''.join(i2)
    return (map_data, solution_data)

# если отправлять файл с картой и решением сразу
map_solution_filename = sys.argv[1]

with open(map_solution_filename) as map_file:
    input_data = map_file.read()

# если файл пустой
if len(input_data) == 0:
    sys.exit()

try:
    map_data, solution_data = extract_map_and_solution(input_data)
except Exception as ex:
    print("Error")
    sys.exit()

try:
    map = parse_map_str(map_data)
except Exception as ex:
    print("Error")
    sys.exit()

try:
    solution = parse_solution_str(solution_data, map)
except Exception as ex:
    print("Error")
    sys.exit()

view.init_and_run(map, solution)
