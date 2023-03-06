#include "fifteen.hpp"
#include <Python.h>

using namespace std;

static PyObject *isSolvable_wrapper(PyObject *self, PyObject *args) {
    int numLines;       /* how many lines we passed for parsing */

    PyObject * listObj; /* the list of longs */
    PyObject * longObj;  /* one long in the list */

/* the O! parses for a Python object (listObj) checked
   to be of type PyList_Type */
    if (! PyArg_ParseTuple( args, "O!", &PyList_Type, &listObj
                            )) return NULL;
    numLines = PyList_Size(listObj);
    if (numLines != 16) {
        PyErr_SetString(PyExc_ValueError, "array must be of length 16");
        return NULL;
    }
    vector<int> instance;

    PyObject* new_list = PyList_New(16);
    for (int i=0; i<numLines; i++) {
        longObj = PyList_GetItem(listObj, i);
        long l = PyLong_AsLong(longObj);
        instance.push_back((int)l);

    }
    if(isSolvable(instance)){
        Py_RETURN_TRUE;
    }
    Py_RETURN_FALSE;
}

static PyObject *solveManhattan_wrapper(PyObject *self, PyObject *args) {
    int numLines;       /* how many lines we passed for parsing */

    PyObject * listObj; /* the list of longs */
    PyObject * longObj;  /* one long in the list */

/* the O! parses for a Python object (listObj) checked
   to be of type PyList_Type */
    if (! PyArg_ParseTuple( args, "O!", &PyList_Type, &listObj
                            )) return NULL;
    numLines = PyList_Size(listObj);
    if (numLines != 16) {
        PyErr_SetString(PyExc_ValueError, "array must be of length 16");
        return NULL;
    }
    vector<int> instance;

    for (int i=0; i<numLines; i++) {
        longObj = PyList_GetItem(listObj, i);
        long l = PyLong_AsLong(longObj);
        instance.push_back((int)l);

    }
    if(!isSolvable(instance)){
        PyErr_SetString(PyExc_ValueError, "given instance is not solvable");
        return NULL;
    }


    Heuristic* h = new ManhattanDistance();
    Node* solution = solve(instance, h);
    PyObject* solution_list = PyList_New(0);
    while(solution!=nullptr){
        PyObject* step = PyList_New(16);
        for(int i = 0; i<16; i++){
            PyList_SetItem(step, i, PyLong_FromLong(solution->state[i]));
        }
        PyList_Append(solution_list, step);
        solution = solution->previous;
    }
    PyList_Reverse(solution_list);

    return solution_list;
}

static PyObject *solveMisplaced_wrapper(PyObject *self, PyObject *args) {
    int numLines;       /* how many lines we passed for parsing */

    PyObject * listObj; /* the list of longs */
    PyObject * longObj;  /* one long in the list */

/* the O! parses for a Python object (listObj) checked
   to be of type PyList_Type */
    if (! PyArg_ParseTuple( args, "O!", &PyList_Type, &listObj
                            )) return NULL;
    numLines = PyList_Size(listObj);
    if (numLines != 16) {
        PyErr_SetString(PyExc_ValueError, "array must be of length 16");
        return NULL;
    }
    vector<int> instance;

    for (int i=0; i<numLines; i++) {
        longObj = PyList_GetItem(listObj, i);
        long l = PyLong_AsLong(longObj);
        instance.push_back((int)l);

    }
    if(!isSolvable(instance)){
        PyErr_SetString(PyExc_ValueError, "given instance is not solvable");
        return NULL;
    }


    Heuristic* h = new MisplacedTiles();
    Node* solution = solve(instance, h);
    PyObject* solution_list = PyList_New(0);
    while(solution!=nullptr){
        PyObject* step = PyList_New(16);
        for(int i = 0; i<16; i++){
            PyList_SetItem(step, i, PyLong_FromLong(solution->state[i]));
        }
        PyList_Append(solution_list, step);
        solution = solution->previous;
    }
    PyList_Reverse(solution_list);

    return solution_list;
}

static PyObject *solveMDLC_wrapper(PyObject *self, PyObject *args) {
    int numLines;       /* how many lines we passed for parsing */

    PyObject * listObj; /* the list of longs */
    PyObject * longObj;  /* one long in the list */

/* the O! parses for a Python object (listObj) checked
   to be of type PyList_Type */
    if (! PyArg_ParseTuple( args, "O!", &PyList_Type, &listObj
                            )) return NULL;
    numLines = PyList_Size(listObj);
    if (numLines != 16) {
        PyErr_SetString(PyExc_ValueError, "array must be of length 16");
        return NULL;
    }
    vector<int> instance;

    for (int i=0; i<numLines; i++) {
        longObj = PyList_GetItem(listObj, i);
        long l = PyLong_AsLong(longObj);
        instance.push_back((int)l);

    }
    if(!isSolvable(instance)){
        PyErr_SetString(PyExc_ValueError, "given instance is not solvable");
        return NULL;
    }


    Heuristic* h = new MDLinearConflict();
    Node* solution = solve(instance, h);
    PyObject* solution_list = PyList_New(0);
    while(solution!=nullptr){
        PyObject* step = PyList_New(16);
        for(int i = 0; i<16; i++){
            PyList_SetItem(step, i, PyLong_FromLong(solution->state[i]));
        }
        PyList_Append(solution_list, step);
        solution = solution->previous;
    }
    PyList_Reverse(solution_list);

    return solution_list;
}

static PyObject *solveID_wrapper(PyObject *self, PyObject *args) {
    int numLines;       /* how many lines we passed for parsing */

    PyObject * listObj; /* the list of longs */
    PyObject * longObj;  /* one long in the list */

    if (! PyArg_ParseTuple( args, "O!", &PyList_Type, &listObj
                            )) return NULL;
    numLines = PyList_Size(listObj);
    if (numLines != 16) {
        PyErr_SetString(PyExc_ValueError, "array must be of length 16");
        return NULL;
    }
    vector<int> instance;

    for (int i=0; i<numLines; i++) {
        longObj = PyList_GetItem(listObj, i);
        long l = PyLong_AsLong(longObj);
        instance.push_back((int)l);

    }
    if(!isSolvable(instance)){
        PyErr_SetString(PyExc_ValueError, "given instance is not solvable");
        return NULL;
    }


    Heuristic* h = new InvertDistance();
    Node* solution = solve(instance, h);
    PyObject* solution_list = PyList_New(0);
    while(solution!=nullptr){
        PyObject* step = PyList_New(16);
        for(int i = 0; i<16; i++){
            PyList_SetItem(step, i, PyLong_FromLong(solution->state[i]));
        }
        PyList_Append(solution_list, step);
        solution = solution->previous;
    }
    PyList_Reverse(solution_list);

    return solution_list;
}

static PyObject *solveWD_wrapper(PyObject *self, PyObject *args) {
    int numLines;       /* how many lines we passed for parsing */

    PyObject * listObj; /* the list of longs */
    PyObject * longObj;  /* one long in the list */

    if (! PyArg_ParseTuple( args, "O!", &PyList_Type, &listObj
                            )) return NULL;
    numLines = PyList_Size(listObj);
    if (numLines != 16) {
        PyErr_SetString(PyExc_ValueError, "array must be of length 16");
        return NULL;
    }
    vector<int> instance;

    for (int i=0; i<numLines; i++) {
        longObj = PyList_GetItem(listObj, i);
        long l = PyLong_AsLong(longObj);
        instance.push_back((int)l);

    }
    if(!isSolvable(instance)){
        PyErr_SetString(PyExc_ValueError, "given instance is not solvable");
        return NULL;
    }


    Heuristic* h = new WalkingDistance();
    Node* solution = solve(instance, h);
    PyObject* solution_list = PyList_New(0);
    while(solution!=nullptr){
        PyObject* step = PyList_New(16);
        for(int i = 0; i<16; i++){
            PyList_SetItem(step, i, PyLong_FromLong(solution->state[i]));
        }
        PyList_Append(solution_list, step);
        solution = solution->previous;
    }
    PyList_Reverse(solution_list);

    return solution_list;
}

static PyMethodDef Puzzle15Methods[] = {
        {"isSolvable", isSolvable_wrapper, METH_VARARGS, "Python function that determines if a given 15 puzzle instance is solvable"},
        {"solveManhattan", solveManhattan_wrapper, METH_VARARGS, "Python function that solves a given 15 puzzle instance"},
        {"solveMisplaced", solveMisplaced_wrapper, METH_VARARGS, "Python function that solves a given 15 puzzle instance"},
        {"solveMDLinearConflict", solveMDLC_wrapper, METH_VARARGS, "Python function that solves a given 15 puzzle instance"},
        {"solveInvertDistance", solveID_wrapper, METH_VARARGS, "Python function that solves a given 15 puzzle instance"},
        {"solveWalkingDistance", solveWD_wrapper, METH_VARARGS, "Python function that solves a given 15 puzzle instance"},
        {NULL, NULL, 0, NULL}
};


static struct PyModuleDef puzzle15module = {
        PyModuleDef_HEAD_INIT,
        "puzzle15",
        "Python module for solving puzzle15",
        -1,
        Puzzle15Methods
};

PyMODINIT_FUNC PyInit_puzzle15(void) {
    return PyModule_Create(&puzzle15module);
}

