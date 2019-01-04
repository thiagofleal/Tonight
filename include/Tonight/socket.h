#ifndef	TONIGHT_ABSTRACT_SOCKET
#	define	TONIGHT_ABSTRACT_SOCKET
	
	EXCEPTION SocketException;
	EXCEPTION AcceptSocketException;
	EXCEPTION StartSocketException;
	EXCEPTION ConnectSocketException;
	EXCEPTION BindSocketException;
	EXCEPTION ListenSocketException;
	EXCEPTION SendSocketException;
	EXCEPTION ReceiveSocketException;
	EXCEPTION CloseSocketException;
	
	extern struct socketResources{
		const string localhost;
		const int autoValue;
		const int TCP;
		const int UDP;
		const int inet;
	}SocketResources;
	
	typedef struct{
		pointer value;
		int length;
	}Package;
	
	struct ISocket{
		void (* accept)(object socket);
		void (* start)(void);
		void (* connect)(void);
		void (* bind)(void);
		void (* listen)(int backlog);
		void (* send)(Package message);
		Package (* receive)(void);
		void (* close)(void);
	};
	
	interface(ISocket);
	
	struct Socket{};
	
	class(Socket $extends Object $implements ISocket);
	
#endif
