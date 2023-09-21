import ctypes

from ctypes import cdll
from database_handler import Database_handler

dh = Database_handler()
library = cdll.LoadLibrary('../server_base/server.so')

class Server:
    def __init__(self):
        pass

    def set_town_facility(self):
        facility = []
        l = dh.get_town_facility('Минск')
        for v in l:
            facility.append(v[1])
        facility_array = (ctypes.c_char_p * len(facility))()
        facility_array[:] = [ctypes.c_char_p(str(item).encode()) for item in facility]
        print(library.server(facility_array, len(facility)))

server = Server()
server.set_town_facility()