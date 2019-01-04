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

static Constructor(Socket)
{
	CLASS(Socket);
	static ISocket iSock;
	
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

static Destructor(Socket)
{
	CLASS(Socket);
}

static void ISocket_accept(object socket)
{
	CLASS(Socket);
	callInterface.accept(socket);
}

static void ISocket_start(void)
{
	CLASS(Socket);
	callInterface.start();
}

static void ISocket_connect(void)
{
	CLASS(Socket);
	callInterface.connect();
}

static void ISocket_bind(void)
{
	CLASS(Socket);
	callInterface.bind();
}

static void ISocket_listen(int backlog)
{
	CLASS(Socket);
	callInterface.listen(backlog);
}

static void ISocket_send(Package message)
{
	CLASS(Socket);
	callInterface.send(message);
}

static Package ISocket_receive(void)
{
	CLASS(Socket);
	callInterface.receive();
}

static void ISocket_close(void)
{
	CLASS(Socket);
	callInterface.close();
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
