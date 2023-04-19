//
// Created by BEAST on 18.04.2023.
//

#include <Python.h>
#include "FifteenSolver.h"

using namespace std;

static PyObject *solveWalkingDistance(PyObject *self, PyObject *args){
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
    char board[4][4];
    int k = 0;
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            longObj = PyList_GetItem(listObj, k);
            board[i][j] = (char)PyLong_AsLong(longObj);
            k++;
        }
    }

    FifteenInstance* start = new FifteenInstance(board);
    Heuristic* heuristic = new WalkingDistance();
    long long int counter = 0;
    vector<array<array<char, 4>, 4>> path = AStar(start, heuristic, counter);
    PyObject* solution_list = PyList_New(0);
    for (int i = 0; i < path.size(); i++) {
        PyObject* solution = PyList_New(0);
        for (int j = 0; j < 4; j++) {
            PyObject* row = PyList_New(0);
            for (int k = 0; k < 4; k++) {
                PyList_Append(row, PyLong_FromLong((long)path[i][j][k]));
            }
            PyList_Append(solution, row);
        }
        PyList_Append(solution_list, solution);
    }
    PyObject* ret = PyTuple_Pack(2, PyLong_FromLong(counter), solution_list);
    return ret;
}

static PyMethodDef Puzzle15Methods[] = {
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


