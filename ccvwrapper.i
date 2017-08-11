%module ccvwrapper

%{
#include "ccvwrapper.h"
%}

%typemap(out) int* swt {
	int i;
	$result = PyList_New($1[0]);
	for(i = 0; i < $1[0]; i++){
		PyObject *o = PyInt_FromLong($1[i+1]);
		PyList_SetItem($result, i, o);
	}
	free($1);
}

%include "ccvwrapper.h"


