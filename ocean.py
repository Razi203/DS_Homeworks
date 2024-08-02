from enum import Enum


class StatusType(Enum):
    ALLOCATION_ERROR = 1
    INVALID_INPUT = 2
    FAILURE = 3
    SUCCESS = 4


class output_t:
    def __init__(self, status, x=0):
        self.status = status
        self.result = x


class Fleet:
    def __init__(self, id):
        self.ship_count = 1
        self.id = id
        self.pirates = []
        self.live = True
    
    @property
    def id(self):
        return self.id
    

    def id(self, id):
        self.id = id


class Pirate:
    def __init__(self, id):
        self.id = id
        self.money = 0
        self.fleetId = 0
        self.rank = 0


class Ocean:
    def __init__(self):
        self.fleets = []
        self.fleet_ids = []
        self.pirate_ids = []

    def add_fleet(self, id):
        if id <= 0:
            return StatusType.INVALID_INPUT
        if id in self.fleet_ids:
            return StatusType.FAILURE
        self.fleets.append(Fleet(id))
        return StatusType.SUCCESS

    def add_pirate(self, pirateId, fleetId):
        if pirateId <= 0 or fleetId <= 0:
            return StatusType.INVALID_INPUT
        if pirateId in self.pirate_ids or fleetId not in self.fleet_ids:
            return StatusType.FAILURE
        for fleet in self.fleets:
            if fleet.id == fleetId:
                if 
