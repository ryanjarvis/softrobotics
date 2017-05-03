#include <node.h>

#include <chrono>
#include <thread>

#include <boost/asio.hpp>
#include <boost/asio/serial_port.hpp>

namespace arduino {

	boost::asio::io_service io;
	boost::asio::serial_port port(io);

	void open(const v8::FunctionCallbackInfo<v8::Value>& args) {
		if(port.is_open()) {
			port.close();
		}
		port.open("/dev/tty.usbmodem1421");
		port.set_option(boost::asio::serial_port_base::baud_rate(9600));	

		//TODO: figure out how to determine
		//when arduino serial communication
		//is ready to be written
		std::this_thread::sleep_for(
				std::chrono::milliseconds(2000)
				);
		/*
		char ready;
		boost::asio::read(
				port,
				boost::asio::buffer(
					&ready,
					1
					)
				);
		*/

		v8::Isolate* isolate = args.GetIsolate();
		args.GetReturnValue().Set(v8::Boolean::New(isolate, true));
	};

	void close(const v8::FunctionCallbackInfo<v8::Value>& args) {
		port.close();
		v8::Isolate* isolate = args.GetIsolate();
		args.GetReturnValue().Set(v8::Boolean::New(isolate, true));
	};

	void send(const v8::FunctionCallbackInfo<v8::Value>& args) {
		v8::String::Utf8Value strarg( args[0] );
		std::string message(*strarg);
		boost::asio::write(
				port,
				boost::asio::buffer(
					message.c_str(),
					message.size()
					)
				);
	};
	
	void init(v8::Local<v8::Object> exports) {
		NODE_SET_METHOD(exports, "open", open);
		NODE_SET_METHOD(exports, "send", send);
		NODE_SET_METHOD(exports, "close", close);
	}

	NODE_MODULE(arduino,init)
}
