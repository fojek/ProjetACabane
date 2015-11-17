// Fonctions pour embedder la librarie PythonKoyo en c++

#ifndef commKoyo_H
#define commKoyo_H


PyObject* koyoReadIn()
{
	PyObject *pName, *pModule, *pDict, *pFunc, *pFunc2, *pValue;
	PyRun_SimpleString ("import sys; sys.path.insert(0, '/home/pi')");
	pName = PyString_FromString("commKoyo");
	pModule = PyImport_Import(pName);
	pDict = PyModule_GetDict(pModule);
	pFunc = PyDict_GetItemString(pDict, "ReadIn");	
	PyObject *pResult = PyObject_CallObject(pFunc, NULL);

	return pResult;
}

PyObject* koyoReadOut()
{
	PyObject *pName, *pModule, *pDict, *pFunc, *pFunc2, *pValue;
	PyRun_SimpleString ("import sys; sys.path.insert(0, '/home/pi')");
	pName = PyString_FromString("commKoyo");
	pModule = PyImport_Import(pName);
	pDict = PyModule_GetDict(pModule);
	pFunc = PyDict_GetItemString(pDict, "ReadOut");	
	PyObject *pResult = PyObject_CallObject(pFunc, NULL);

	return pResult;
}

#endif // commKoyo_H
