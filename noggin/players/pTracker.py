
from ..util import FSA
from . import TrackBallStates
from . import GameControllerStates

class SoccerPlayer(FSA.FSA):
    def __init__(self, brain):
        FSA.FSA.__init__(self,brain)
        self.brain = brain
        #self.setTimeFunction(self.brain.nao.getSimulatedTime)
        self.addStates(GameControllerStates)
        self.addStates(TrackBallStates)
        self.currentState = 'nothing'
        self.setName('Player pTracker')
        self.setPrintStateChanges(True)
        self.setPrintFunction(self.brain.out.printf)
