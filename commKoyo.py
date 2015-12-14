# commKoyo.py
# ------------
# Gestion de la communication avec Koyo, via libkoyo
# ------------
# 
# À faire :
# - Ajouter la fonction d'écriture des sorties
#
# ------------

# Importation de la librarie libkoyo
import sys
sys.path.insert(0, '/home/ProjetCabane/lib/Koyo')

# Fonction de lecture des sorties
def ReadOut():

	import Koyo as plc
	myKoyo = plc.Koyo('192.168.0.110')
	return int(myKoyo.ReadOutputs(),2);

# Fonction de lecture des entrées
def ReadIn():

	import Koyo as plc
	myKoyo = plc.Koyo('192.168.0.110')
	return int(myKoyo.ReadInputs(),2);

# À faire, fonction d'écriture des sorties