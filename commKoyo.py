import sys
sys.path.insert(0, '/home/ProjetCabane/lib/Koyo')

def ReadOut():

	import Koyo as plc
	myKoyo = plc.Koyo('192.168.0.110')
	return int(myKoyo.ReadOutputs(),2);

def ReadIn():

	import Koyo as plc
	myKoyo = plc.Koyo('192.168.0.110')
	return int(myKoyo.ReadInputs(),2);