import time

import unreal_engine as ue

"""Liason class between Python and Unreal that allows hooking into the world tick"""

print('Loading DummyPyActor')

class DummyPyActor:

    def __init__(self):
        self.worlds = None
        self.world = None
        self.ai_controllers = None

    def _find_world(self):
        self.worlds = ue.all_worlds()
        # print('All worlds length ' + str(len(self.worlds)))

        # print([w.get_full_name() for w in self.worlds])

        if hasattr(ue, 'get_editor_world'):
            # print('Detected Unreal Editor')
            self.worlds.append(ue.get_editor_world())
        else:
            # print('Determined we are in a packaged game')
            # self.worlds.append(self.uobject.get_current_level()) # A LEVEL IS NOT A WORLD
            pass

        self.worlds = [w for w in self.worlds if 'DeepDriveSim_Demo.DeepDriveSim_Demo' in w.get_full_name()]

        for w in self.worlds:
            self.ai_controllers = [a for a in w.all_actors()
                                   if 'localaicontroller_' in a.get_full_name().lower()]
            if self.ai_controllers:
                self.world = w
                print('FOUND WORLD WITH CONTROLLER !!!!!!!!!!!!!!!!!')
                break
        else:
            # print('NO WORLDS WITH CONTROLLER')
            pass

        return self.world

    # this is called on game start
    def begin_play(self):
        print('Begin Play on DummyPyActor class')
        self._find_world()



    # this is called at every 'tick'
    def tick(self, delta_time):
        if self.world is None:
            self._find_world()

        for controller in self.ai_controllers:
            if controller.getIsPassing():
                print('IS PASSING!!!!!!!!!!!!!!!!!!!!!!!')

        # py.cmd print([a.get_full_name() for a in ue.all_worlds()[0].all_actors()])
        #  # get current location
        # location = self.uobject.get_actor_location()
        # # increase Z honouring delta_time
        # location.z += 100 * delta_time
        # # set new location
        # self.uobject.set_actor_location(location)

# if __name__ == '__main__':
#     print('main')
#     DummyPyActor()._find_world()