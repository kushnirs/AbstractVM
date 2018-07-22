# AbstractVM

AbstractVM is a machine that uses a stack to compute simple arithmetic expressions. 
These arithmetic expressions are provided to the machine as basic assembly programs.

****Example:****

****push int32(42)****\
****push int32(33)****\
****add****\
****push float(44.55)****\
****mul****\
****push double(42.42)****\
****push int32(42)****\
****dump****\
****pop****\
****assert double(42.42)****\
****exit****
