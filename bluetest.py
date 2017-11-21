from bluetooth import*

sock=bluetooth.BluetoothSocket(bluetooth.L2CAP)

nearby_devices = discover_devices(lookup_names = True)

for name, addr in nearby_devices:
	print "%s - %s" % (addr,name)
