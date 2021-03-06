

class BirthCertificate:
    '''Defines all the per-robot configuraations that may need to be
    defined.  Each robot has an instance created in the robots package
    initialization module.  Holds information like name, walk config,
    etc..  Each new instance will receive an id number, but these are
    dependent on the order of initialization (usually alphabetical
    order) so should not be used for comparison.  Use
      if brain.robot is robots.slarti
    for example.'''

    # Class-static variable.  Increments with each new instance
    next_id = 0

    def __init__(self, name, long_name, tts_name=None,
                  doc='', gait=None):
        self.id = BirthCertificate.next_id
        BirthCertificate.next_id += 1

        self.name = name
        self.long_name = long_name
        self.tts_name = name
        if tts_name is not None:
            self.tts_name = tts_name
        self.__doc__ = doc
        self.gait = gait

    def setRobotGait(self, motion_interface):
        if self.gait is not None:
            motion_interface.setGait(self.gait)

    def __str__(self):
        s = "CoA: " + self.long_name
        if self.__doc__:
            s += '\nCoA:   ' + self.__doc__
        return s

