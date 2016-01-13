%module nyra

%{
    #include "nyra/Vector2.h"
    #include "nyra/ScriptActor.h"
    #include "nyra/ScriptEngine.h"
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
%rename(Actor) nyra::ScriptActor;

%include "std_string.i"
%include "std_vector.i"
%include "nyra/Vector2.h"
%include "nyra/ScriptActor.h"
%include "nyra/ScriptEngine.h"
%include "nyra/InputConstants.h"

%template(Vector2) nyra::Vector2Impl<double>;
%template(SizeTVector) std::vector<size_t>;

%pythoncode
%{
import nyra

def get_position(self):
    vec = self._get_position()
    return (vec.x, vec.y)

def set_position(self, values):
    self._set_position(nyra.Vector2(values[0], values[1]))

def register_button(name, values):
    inputs = SizeTVector()
    if type(values) == int:
        inputs.push_back(values)
    else:
        for val in values:
            inputs.push_back(val)
    nyra._register_button(name, inputs)

Actor.position = property(get_position)
Actor.position = Actor.position.setter(set_position)
%}

