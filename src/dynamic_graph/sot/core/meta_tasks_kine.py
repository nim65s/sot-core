from dynamic_graph import plug
from dynamic_graph.sot.core import GainAdaptive, Task
from dynamic_graph.sot.core.meta_task_6d import MetaTask6d
from dynamic_graph.sot.core.meta_tasks import MetaTaskCom


class MetaTaskKine6d(MetaTask6d):
    def createTask(self):
        self.task = Task('task' + self.name)

    def createGain(self):
        self.gain = GainAdaptive('gain' + self.name)
        self.gain.set(0.1, 0.1, 125e3)

    def plugEverything(self):
        self.feature.setReference(self.featureDes.name)
        plug(self.dyn.signal(self.opPoint), self.feature.signal('position'))
        plug(self.dyn.signal('J' + self.opPoint), self.feature.signal('Jq'))
        self.task.add(self.feature.name)
        plug(self.task.error, self.gain.error)
        plug(self.gain.gain, self.task.controlGain)

    def keep(self):
        self.feature.position.recompute(self.dyn.position.time)
        self.feature.keep()


class MetaTaskKineCom(MetaTaskCom):
    def __init__(self, dyn, name="com"):
        MetaTaskCom.__init__(self, dyn, name)
        self.task = Task('task' + name)
        self.plugTask()
