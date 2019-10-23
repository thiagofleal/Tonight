#ifdef WIN32
#	include <winsock.h>
#else
#	include <sys/types.h>
#	include <sys/socket.h>
#endif

#include "../include/tonight.h"
#include "../include/Tonight/exceptions.h"
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

static void Socket_constructor(){
	static ISocket iSock;

	construct(superOf(Socket));
/*
	iSock.accept = Tonight->Util->DefaultFunctionPointer;
	iSock.start = Tonight->Util->DefaultFunctionPointer;
	iSock.connect = Tonight->Util->DefaultFunctionPointer;
	iSock.bind = Tonight->Util->DefaultFunctionPointer;
	iSock.listen = Tonight->Util->DefaultFunctionPointer;
	iSock.send = Tonight->Util->DefaultFunctionPointer;
	iSock.receive = Tonight->Util->DefaultFunctionPointer;
	iSock.close = Tonight->Util->DefaultFunctionPointer;
*/
	setInterface(Socket, iSock);
}

static void Socket_destructor(){
	destruct(superOf(Socket));
}

static void ISocket_accept(object socket){
	Method(Socket){
        getInterface(Socket).accept(socket);
	}
}

static void ISocket_start(void){
	Method(Socket){
        getInterface(Socket).start();
	}
}

static void ISocket_connect(void){
	Method(Socket){
        getInterface(Socket).connect();
	}
}

static void ISocket_bind(void){
	Method(Socket){
        getInterface(Socket).bind();
	}
}

static void ISocket_listen(int backlog){
	Method(Socket){
        getInterface(Socket).listen(backlog);
	}
}

static void ISocket_send(Package message){
	Method(Socket){
        getInterface(Socket).send(message);
	}
}

static Package ISocket_receive(void){
	Package ret;
    Method(Socket){
        ret = getInterface(Socket).receive();
	}
	return ret;
}

static void ISocket_close(void){
	Method(Socket){
        getInterface(Socket).close();
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

Constructor(Socket, Socket_constructor);
Destructor(Socket, Socket_destructor);

Define_Class(Socket $extends Object $implements ISocket $with iSock);
