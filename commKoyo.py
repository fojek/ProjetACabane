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
	result = myKoyo.ReadOutputs()
	if result != -1:
		return int(int(myKoyo.ReadOutputs()[::-1]),2);
	else:
		return -1;
		print 'Python : ReadOut : Timeout ignore!'

# Fonction de lecture des entrees
def ReadIn():

	import Koyo as plc
	myKoyo = plc.Koyo('192.168.0.110')
	if result != -1:
		return int(int(myKoyo.ReadInputs()[::-1]),2);
	else:
		print 'Python : ReadIn : Timeout ignore!'
		return -1;	
		
# [::-1] permet de retourner un string
 
# A faire, fonction d'ecriture des sorties
