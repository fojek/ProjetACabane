# commKoyo.py
# ------------
# Gestion de la communication avec Koyo, via libkoyo
# ------------
# 
# A faire :
# - Ajouter la fonction d'ecriture des sorties
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

# Fonction de lecture des entrees
def ReadIn():

	import Koyo as plc
	myKoyo = plc.Koyo('192.168.0.110')
	return int(myKoyo.ReadInputs(),2);

# A faire, fonction d'ecriture des sorties
