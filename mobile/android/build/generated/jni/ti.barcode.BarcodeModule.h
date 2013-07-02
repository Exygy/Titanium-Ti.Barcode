/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

/** This is generated, do not edit by hand. **/

#include <jni.h>

#include "Proxy.h"

		namespace ti {
		namespace barcode {


class BarcodeModule : public titanium::Proxy
{
public:
	explicit BarcodeModule(jobject javaObject);

	static void bindProxy(v8::Handle<v8::Object> exports);
	static v8::Handle<v8::FunctionTemplate> getProxyTemplate();
	static void dispose();

	static v8::Persistent<v8::FunctionTemplate> proxyTemplate;
	static jclass javaClass;

private:
	// Methods -----------------------------------------------------------
	static v8::Handle<v8::Value> getUseLED(const v8::Arguments&);
	static v8::Handle<v8::Value> getHasLED(const v8::Arguments&);
	static v8::Handle<v8::Value> setUseFrontCamera(const v8::Arguments&);
	static v8::Handle<v8::Value> setUseLED(const v8::Arguments&);
	static v8::Handle<v8::Value> capture(const v8::Arguments&);
	static v8::Handle<v8::Value> getHasCamera(const v8::Arguments&);
	static v8::Handle<v8::Value> cancel(const v8::Arguments&);
	static v8::Handle<v8::Value> getUseFrontCamera(const v8::Arguments&);
	static v8::Handle<v8::Value> parse(const v8::Arguments&);

	// Dynamic property accessors ----------------------------------------
	static v8::Handle<v8::Value> getter_useFrontCamera(v8::Local<v8::String> property, const v8::AccessorInfo& info);
	static void setter_useFrontCamera(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::AccessorInfo& info);
	static v8::Handle<v8::Value> getter_hasCamera(v8::Local<v8::String> property, const v8::AccessorInfo& info);
	static v8::Handle<v8::Value> getter_useLED(v8::Local<v8::String> property, const v8::AccessorInfo& info);
	static void setter_useLED(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::AccessorInfo& info);
	static v8::Handle<v8::Value> getter_hasLED(v8::Local<v8::String> property, const v8::AccessorInfo& info);

};

		} // barcode
		} // ti
