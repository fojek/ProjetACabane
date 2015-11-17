import koyo as plc

myKoyo = plc.Koyo('192.168.0.110')
myKoyo.WriteOutput(7,0) # write output Y0 to true, (if this isn't tied to any rung in the ladder it should turn on)
print myKoyo.ReadInput(1)
#print myKoyo.ReadC(16) #this currently only returns data of the first 4 bytes of C Memory
#if(myKoyo.ReadOutput(5)):
#   myKoyo.WriteC(16,false)
#else:
#   myKoyo.WriteC(16,true)

#other helpful commands:
#myKoyo.FindKoyo()          #return a list (ip,mac) of koyo plcs on the network
#myKoyo.ChangeIP(00e062202aed,192.168.0.110) #change an ip address of a koyo that's plugged into your subnet
