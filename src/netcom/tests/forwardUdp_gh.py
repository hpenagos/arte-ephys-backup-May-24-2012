import socket
import sys

if len(sys.argv) != 4:
	sys.exit("Usage: forwardUdp PORT_IN IP_OUT PORT_OUT")
ip_in  = ""


port_in = int(sys.argv[1]);
ip_out = sys.argv[2]
port_out = int(sys.argv[3]);

print "Sending packets received on:", port_in, " to IP:", ip_out, " port:", port_out

sock_in = socket.socket( socket.AF_INET, socket.SOCK_DGRAM )
sock_in.bind( ("", port_in) )

sock_out = socket.socket( socket.AF_INET, socket.SOCK_DGRAM )

while True:
	print "before recvfrom"
	try:
		data, addr = sock_in.recvfrom(4096)
		print data
	except:
		print "Caught an exception."
#data = sock_in.recv(1024)
		print "after recvfrom"
		sock_out.sendto( data, (ip_out, port_out) )


