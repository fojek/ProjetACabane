#include <bitset>

class Koyo {
public:
    int addresseIP;
    std::bitset<24> *Inputs; // 20 entrées, octal : 0-7, 10-17, 20-23. 8,9,18,19 n'existent pas
    std::bitset<18> *Outputs; // 16 sorties, octal : 0-7, 10-17. 8,9 n'existent pas
    int koyoReadIn(void);
    int koyoReadOut(void);
    int koyoWriteOut(void);
    static Koyo& Instance();

private:
    Koyo& operator = (const Koyo&) {}
    Koyo (const Koyo&) {}
    static Koyo m_instance;
    Koyo(int ip) : addresseIP(ip) {
    Inputs = new std::bitset<24>;
    }
};

int Koyo::koyoReadIn()
{
	std::bitset<24> *inputs;

	PyObject *pName, *pModule, *pDict, *pFunc;
	PyRun_SimpleString ("import sys; sys.path.insert(0, '/home/ProjetCabane')");
	pName = PyString_FromString("commKoyo");
	pModule = PyImport_Import(pName);
	pDict = PyModule_GetDict(pModule);
	pFunc = PyDict_GetItemString(pDict, "ReadIn");

	PyObject *pResult = PyObject_CallObject(pFunc, NULL);
	inputs = new std::bitset<24> (PyInt_AsLong(pResult));

	Inputs = inputs;
	
	return 1;
}

int Koyo::koyoReadOut()
{
	std::bitset<18> *outputs;

	PyObject *pName, *pModule, *pDict, *pFunc;
	PyRun_SimpleString ("import sys; sys.path.insert(0, '/home/ProjetCabane')");
	pName = PyString_FromString("commKoyo");
	pModule = PyImport_Import(pName);
	pDict = PyModule_GetDict(pModule);
	pFunc = PyDict_GetItemString(pDict, "ReadOut");

	PyObject *pResult = PyObject_CallObject(pFunc, NULL);
	outputs = new std::bitset<18> (PyInt_AsLong(pResult));

	Outputs = outputs;
	
	return 1;
}
