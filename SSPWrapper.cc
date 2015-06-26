#include <node.h>
#include <v8.h>

#include <SSPComs.h>
#include <ssp_defines.h>
#include <itl_types.h>

using namespace v8;

//returns a handle to SSP_PORT. -1 on fail;
Handle<Value> SW_OpenSSPPort(const Arguments& args) 
{
	HandleScope scope;
	
	if(args.Length() < 1)
	{
		ThrowException(Exception::SyntaxError(String::New("The first and only argument of OpenSSPPort needs to be a string")));
	}
	
	if(!args[0]->IsString())
	{
		ThrowException(Exception::SyntaxError(String::New("I need a string")));
	}
	
	const char* port = *String::AsciiValue(args[0]);
	
	int res = OpenSSPPort(port);
	
	return scope.Close(Integer::New(res));
}


Handle<Value> SW_CloseSSPPort(const Arguments& args) 
{
	HandleScope scope;
	
	if(args.Length() < 1)
	{
		ThrowException(Exception::SyntaxError(String::New("The first and only argument of CloseSSPPort needs to be a port handle (SSP_PORT == int)")));
	}
	
	if(!args[0]->IsNumber())
	{
		ThrowException(Exception::SyntaxError(String::New("CloseSSPPort need a port handle (SSP_PORT)")));
	}
	
	int port = args[0]->IntegerValue();
	
	CloseSSPPort(port);
	
	return scope.Close(Null());
}


void init(Handle<Object> target) 
{
	NODE_SET_METHOD(target, "OpenSSPPort", SW_OpenSSPPort);
	NODE_SET_METHOD(target, "CloseSSPPort", SW_CloseSSPPort); 
}

NODE_MODULE(SSPWrapper, init);
