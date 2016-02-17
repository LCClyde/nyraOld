%module nyra

%{
    #include "nyra/Vector2.h"
    #include "nyra/SwigActor.h"
    #include "nyra/SwigEngine.h"
    #include "nyra/InputConstants.h"
%}

%include "exception.i"

%exception
{
    try
    {
        $action
    }
    catch (const std::exception& e)
    {
        SWIG_exception(SWIG_RuntimeError, e.what());
    }
}

%ignore update;
%ignore initialize;
%rename(Actor) nyra::SwigActor;

%include "std_string.i"
%include "std_vector.i"
%include "nyra/Vector2.h"
%include "nyra/SwigActor.h"
%include "nyra/SwigEngine.h"
%include "nyra/InputConstants.h"

%template(Vector2) nyra::Vector2Impl<float>;
%template(SizeTVector) std::vector<size_t>;

%pythoncode
%{
import nyra

def get_position(self):
    vec = self._get_position()
    return (vec.x, vec.y)

def get_velocity(self):
    vec = self._get_velocity()
    return (vec.x, vec.y)

def set_position(self, values):
    self._set_position(nyra.Vector2(values[0], values[1]))

def apply_force(self, force):
    self._apply_force(nyra.Vector2(force[0], force[1]))

def register_input(name, values):
    inputs = SizeTVector()
    if type(values) == int:
        inputs.push_back(values)
    else:
        for val in values:
            inputs.push_back(val)
    nyra._register_input(name, inputs)

class Camera:
    @staticmethod
    def track(actor, offset=(0, 0)):
        nyra._camera_track(actor._get_data(),
                           nyra.Vector2(offset[0], offset[1]))

Actor.position = property(get_position)
Actor.position = Actor.position.setter(set_position)
Actor.velocity = property(get_velocity)
Actor.apply_force = apply_force
%}

