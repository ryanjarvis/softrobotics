#include <node.h>
#include <opencv2/opencv.hpp>

namespace imager {

	void get_orientation(const v8::FunctionCallbackInfo<v8::Value>& args) {
		v8::Isolate* isolate = args.GetIsolate();

		if(args.Length() < 1) {
			isolate->ThrowException(
					v8::Exception::TypeError(
						v8::String::NewFromUtf8(isolate, "Number of arguments should be 2")
						)
					);
			return;
		}

		if(!args[0]->IsString()) {
			isolate->ThrowException(
					v8::Exception::TypeError(
						v8::String::NewFromUtf8(isolate, "First argument should be a string")
						)
					);
			return;
		}

		v8::String::Utf8Value strarg(args[0]);
		std::string imagepath(*strarg);

		cv::Mat image;
		image = cv::imread(imagepath, 1);
		if(!image.data) {
			isolate->ThrowException(
					v8::Exception::TypeError(
						v8::String::NewFromUtf8(isolate, "Image is invalid")
						)
					);
			return;
		}

		cv::Mat edges;
		Canny(image, edges, 50, 200, 3);

		cv::vector<cv::Vec2f> lines;
		HoughLines(edges, lines, 1, CV_PI/180, 100);

		int angle = static_cast<int>(std::round(lines[0][1] * 57.2958f));
		args.GetReturnValue().Set(v8::Number::New(isolate, angle));
	}

	void init(v8::Local<v8::Object> exports) {
		NODE_SET_METHOD(exports, "get_orientation", get_orientation);
	}

	NODE_MODULE(imager,init)
}
