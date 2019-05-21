#ifdef WIN32
#	include <winsock.h>
#else
#	include <sys/types.h>
#	include <sys/socket.h>
#endif

#include "../include/Tonight/tonight.h"
#include "../include/Tonight/socket.h"

Define_Exception(SocketException $as "Socket exception" $extends GenericException);
Define_Exception(AcceptSocketException $as "Accept socket exception" $extends SocketException);
Define_Exception(StartSocketException $as "Start socket exception" $extends SocketException);
Define_Exception(ConnectSocketException $as "Connect socket exception" $extends SocketException);
Define_Exception(BindSocketException $as "Bind socket exception" $extends SocketException);
Define_Exception(ListenSocketException $as "Listen socket exception" $extends SocketException);
Define_Exception(SendSocketException $as "Send socket exception" $extends SocketException);
Define_Exception(ReceiveSocketException $as "Receive socket exception" $extends SocketException);
Define_Exception(CloseSocketException $as "Close socket exception" $extends SocketException);

struct socketResources SocketResources = {
	.localhost = "127.0.0.1",
	.autoValue = 0,
	.TCP = SOCK_STREAM,
	.UDP = SOCK_DGRAM,
	.inet = AF_INET
};

static Constructor(Socket){
	object self = getCurrentObject();
	This(Socket, self);
	static ISocket iSock;

	construct(superOf(Socket), self);

	iSock.accept = Tonight.DefaultFunctionPointer;
	iSock.start = Tonight.DefaultFunctionPointer;
	iSock.connect = Tonight.DefaultFunctionPointer;
	iSock.bind = Tonight.DefaultFunctionPointer;
	iSock.listen = Tonight.DefaultFunctionPointer;
	iSock.send = Tonight.DefaultFunctionPointer;
	iSock.receive = Tonight.DefaultFunctionPointer;
	iSock.close = Tonight.DefaultFunctionPointer;

	setInterface(iSock);
}

static Destructor(Socket){
    object self = getCurrentObject();
	destruct(superOf(Socket), self);
}

static void ISocket_accept(object socket){
	object self = getCurrentObject();
	This(Socket, self);

	with(self){
        getInterface.accept(socket);
	}
}

static void ISocket_start(void){
	object self = getCurrentObject();
	This(Socket, self);

	with(self){
        getInterface.start();
	}
}

static void ISocket_connect(void){
	object self = getCurrentObject();
	This(Socket, self);

	with(self){
        getInterface.connect();
	}
}

static void ISocket_bind(void){
	object self = getCurrentObject();
	This(Socket, self);

	with(self){
        getInterface.bind();
	}
}

static void ISocket_listen(int backlog){
	object self = getCurrentObject();
	This(Socket, self);

	with(self){
        getInterface.listen(backlog);
	}
}

static void ISocket_send(Package message){
	object self = getCurrentObject();
	This(Socket, self);

	with(self){
        getInterface.send(message);
	}
}

static Package ISocket_receive(void){
	object self = getCurrentObject();
	This(Socket, self);
	Package ret;

	with(self){
        ret = getInterface.receive();
	}

	return ret;
}

static void ISocket_close(void){
	object self = getCurrentObject();
	This(Socket, self);

	with(self){
        getInterface.close();
	}
}

static ISocket iSock = {
	.accept = ISocket_accept,
	.start = ISocket_start,
	.connect = ISocket_connect,
	.bind = ISocket_bind,
	.listen = ISocket_listen,
	.send = ISocket_send,
	.receive = ISocket_receive,
	.close = ISocket_close
};

Define_Class(Socket $extends Object $implements ISocket $with iSock);
