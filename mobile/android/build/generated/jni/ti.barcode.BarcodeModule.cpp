/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

/** This code is generated, do not edit by hand. **/

#include "ti.barcode.BarcodeModule.h"

#include "AndroidUtil.h"
#include "EventEmitter.h"
#include "JNIUtil.h"
#include "JSException.h"
#include "Proxy.h"
#include "ProxyFactory.h"
#include "TypeConverter.h"
#include "V8Util.h"




#include "org.appcelerator.kroll.KrollModule.h"

#define TAG "BarcodeModule"

using namespace v8;

		namespace ti {
		namespace barcode {


Persistent<FunctionTemplate> BarcodeModule::proxyTemplate = Persistent<FunctionTemplate>();
jclass BarcodeModule::javaClass = NULL;

BarcodeModule::BarcodeModule(jobject javaObject) : titanium::Proxy(javaObject)
{
}

void BarcodeModule::bindProxy(Handle<Object> exports)
{
	if (proxyTemplate.IsEmpty()) {
		getProxyTemplate();
	}

	// use symbol over string for efficiency
	Handle<String> nameSymbol = String::NewSymbol("Barcode");

	Local<Function> proxyConstructor = proxyTemplate->GetFunction();
	Local<Object> moduleInstance = proxyConstructor->NewInstance();
	exports->Set(nameSymbol, moduleInstance);
}

void BarcodeModule::dispose()
{
	LOGD(TAG, "dispose()");
	if (!proxyTemplate.IsEmpty()) {
		proxyTemplate.Dispose();
		proxyTemplate = Persistent<FunctionTemplate>();
	}

	titanium::KrollModule::dispose();
}

Handle<FunctionTemplate> BarcodeModule::getProxyTemplate()
{
	if (!proxyTemplate.IsEmpty()) {
		return proxyTemplate;
	}

	LOGD(TAG, "GetProxyTemplate");

	javaClass = titanium::JNIUtil::findClass("ti/barcode/BarcodeModule");
	HandleScope scope;

	// use symbol over string for efficiency
	Handle<String> nameSymbol = String::NewSymbol("Barcode");

	Handle<FunctionTemplate> t = titanium::Proxy::inheritProxyTemplate(
		titanium::KrollModule::getProxyTemplate()
, javaClass, nameSymbol);

	proxyTemplate = Persistent<FunctionTemplate>::New(t);
	proxyTemplate->Set(titanium::Proxy::inheritSymbol,
		FunctionTemplate::New(titanium::Proxy::inherit<BarcodeModule>)->GetFunction());

	titanium::ProxyFactory::registerProxyPair(javaClass, *proxyTemplate);

	// Method bindings --------------------------------------------------------
	DEFINE_PROTOTYPE_METHOD(proxyTemplate, "getUseLED", BarcodeModule::getUseLED);
	DEFINE_PROTOTYPE_METHOD(proxyTemplate, "getHasLED", BarcodeModule::getHasLED);
	DEFINE_PROTOTYPE_METHOD(proxyTemplate, "setUseFrontCamera", BarcodeModule::setUseFrontCamera);
	DEFINE_PROTOTYPE_METHOD(proxyTemplate, "setUseLED", BarcodeModule::setUseLED);
	DEFINE_PROTOTYPE_METHOD(proxyTemplate, "capture", BarcodeModule::capture);
	DEFINE_PROTOTYPE_METHOD(proxyTemplate, "getHasCamera", BarcodeModule::getHasCamera);
	DEFINE_PROTOTYPE_METHOD(proxyTemplate, "cancel", BarcodeModule::cancel);
	DEFINE_PROTOTYPE_METHOD(proxyTemplate, "getUseFrontCamera", BarcodeModule::getUseFrontCamera);
	DEFINE_PROTOTYPE_METHOD(proxyTemplate, "parse", BarcodeModule::parse);

	Local<ObjectTemplate> prototypeTemplate = proxyTemplate->PrototypeTemplate();
	Local<ObjectTemplate> instanceTemplate = proxyTemplate->InstanceTemplate();

	// Delegate indexed property get and set to the Java proxy.
	instanceTemplate->SetIndexedPropertyHandler(titanium::Proxy::getIndexedProperty,
		titanium::Proxy::setIndexedProperty);

	// Constants --------------------------------------------------------------
	JNIEnv *env = titanium::JNIScope::getEnv();
	if (!env) {
		LOGE(TAG, "Failed to get environment in BarcodeModule");
		//return;
	}


		DEFINE_INT_CONSTANT(prototypeTemplate, "GEOLOCATION", 6);

		DEFINE_INT_CONSTANT(prototypeTemplate, "FORMAT_UPC_A", 4);

		DEFINE_INT_CONSTANT(prototypeTemplate, "FORMAT_UPC_E", 3);

		DEFINE_INT_CONSTANT(prototypeTemplate, "UNKNOWN", 0);

		DEFINE_INT_CONSTANT(prototypeTemplate, "FORMAT_QR_CODE", 1);

		DEFINE_INT_CONSTANT(prototypeTemplate, "TELEPHONE", 3);

		DEFINE_INT_CONSTANT(prototypeTemplate, "BOOKMARK", 9);

		DEFINE_INT_CONSTANT(prototypeTemplate, "CONTACT", 8);

		DEFINE_INT_CONSTANT(prototypeTemplate, "FORMAT_CODE_39", 8);

		DEFINE_INT_CONSTANT(prototypeTemplate, "WIFI", 10);

		DEFINE_INT_CONSTANT(prototypeTemplate, "FORMAT_ITF", 9);

		DEFINE_INT_CONSTANT(prototypeTemplate, "FORMAT_CODE_128", 7);

		DEFINE_INT_CONSTANT(prototypeTemplate, "CALENDAR", 5);

		DEFINE_INT_CONSTANT(prototypeTemplate, "FORMAT_EAN_8", 5);

		DEFINE_INT_CONSTANT(prototypeTemplate, "FORMAT_NONE", 0);

		DEFINE_INT_CONSTANT(prototypeTemplate, "TEXT", 4);

		DEFINE_INT_CONSTANT(prototypeTemplate, "FORMAT_EAN_13", 6);

		DEFINE_INT_CONSTANT(prototypeTemplate, "FORMAT_DATA_MATRIX", 2);

		DEFINE_INT_CONSTANT(prototypeTemplate, "EMAIL", 7);

		DEFINE_INT_CONSTANT(prototypeTemplate, "URL", 1);

		DEFINE_INT_CONSTANT(prototypeTemplate, "SMS", 2);


	// Dynamic properties -----------------------------------------------------
	instanceTemplate->SetAccessor(String::NewSymbol("useFrontCamera"),
			BarcodeModule::getter_useFrontCamera
			, BarcodeModule::setter_useFrontCamera
, Handle<Value>(), DEFAULT);
	instanceTemplate->SetAccessor(String::NewSymbol("hasCamera"),
			BarcodeModule::getter_hasCamera
			, titanium::Proxy::onPropertyChanged
		, Handle<Value>(), DEFAULT);
	instanceTemplate->SetAccessor(String::NewSymbol("useLED"),
			BarcodeModule::getter_useLED
			, BarcodeModule::setter_useLED
, Handle<Value>(), DEFAULT);
	instanceTemplate->SetAccessor(String::NewSymbol("hasLED"),
			BarcodeModule::getter_hasLED
			, titanium::Proxy::onPropertyChanged
		, Handle<Value>(), DEFAULT);

	// Accessors --------------------------------------------------------------
	instanceTemplate->SetAccessor(
		String::NewSymbol("displayedMessage"),
		titanium::Proxy::getProperty,
		titanium::Proxy::onPropertyChanged,
		Handle<Value>(), DEFAULT);
	DEFINE_PROTOTYPE_METHOD_DATA(proxyTemplate, "getDisplayedMessage", titanium::Proxy::getProperty, String::NewSymbol("displayedMessage"));
	DEFINE_PROTOTYPE_METHOD_DATA(proxyTemplate, "setDisplayedMessage", titanium::Proxy::onPropertyChanged, String::NewSymbol("displayedMessage"));
	instanceTemplate->SetAccessor(
		String::NewSymbol("allowRotation"),
		titanium::Proxy::getProperty,
		titanium::Proxy::onPropertyChanged,
		Handle<Value>(), DEFAULT);
	DEFINE_PROTOTYPE_METHOD_DATA(proxyTemplate, "getAllowRotation", titanium::Proxy::getProperty, String::NewSymbol("allowRotation"));
	DEFINE_PROTOTYPE_METHOD_DATA(proxyTemplate, "setAllowRotation", titanium::Proxy::onPropertyChanged, String::NewSymbol("allowRotation"));
	instanceTemplate->SetAccessor(
		String::NewSymbol("allowMenu"),
		titanium::Proxy::getProperty,
		titanium::Proxy::onPropertyChanged,
		Handle<Value>(), DEFAULT);
	DEFINE_PROTOTYPE_METHOD_DATA(proxyTemplate, "getAllowMenu", titanium::Proxy::getProperty, String::NewSymbol("allowMenu"));
	DEFINE_PROTOTYPE_METHOD_DATA(proxyTemplate, "setAllowMenu", titanium::Proxy::onPropertyChanged, String::NewSymbol("allowMenu"));
	instanceTemplate->SetAccessor(
		String::NewSymbol("allowInstructions"),
		titanium::Proxy::getProperty,
		titanium::Proxy::onPropertyChanged,
		Handle<Value>(), DEFAULT);
	DEFINE_PROTOTYPE_METHOD_DATA(proxyTemplate, "getAllowInstructions", titanium::Proxy::getProperty, String::NewSymbol("allowInstructions"));
	DEFINE_PROTOTYPE_METHOD_DATA(proxyTemplate, "setAllowInstructions", titanium::Proxy::onPropertyChanged, String::NewSymbol("allowInstructions"));

	return proxyTemplate;
}

// Methods --------------------------------------------------------------------
Handle<Value> BarcodeModule::getUseLED(const Arguments& args)
{
	LOGD(TAG, "getUseLED()");
	HandleScope scope;

	JNIEnv *env = titanium::JNIScope::getEnv();
	if (!env) {
		return titanium::JSException::GetJNIEnvironmentError();
	}
	static jmethodID methodID = NULL;
	if (!methodID) {
		methodID = env->GetMethodID(BarcodeModule::javaClass, "getUseLED", "()Z");
		if (!methodID) {
			const char *error = "Couldn't find proxy method 'getUseLED' with signature '()Z'";
			LOGE(TAG, error);
				return titanium::JSException::Error(error);
		}
	}

	titanium::Proxy* proxy = titanium::Proxy::unwrap(args.Holder());

	jvalue* jArguments = 0;

	jobject javaProxy = proxy->getJavaObject();
	jboolean jResult = (jboolean)env->CallBooleanMethodA(javaProxy, methodID, jArguments);



	if (!JavaObject::useGlobalRefs) {
		env->DeleteLocalRef(javaProxy);
	}



	if (env->ExceptionCheck()) {
		Handle<Value> jsException = titanium::JSException::fromJavaException();
		env->ExceptionClear();
		return jsException;
	}


	Handle<Boolean> v8Result = titanium::TypeConverter::javaBooleanToJsBoolean(env, jResult);



	return v8Result;

}
Handle<Value> BarcodeModule::getHasLED(const Arguments& args)
{
	LOGD(TAG, "getHasLED()");
	HandleScope scope;

	JNIEnv *env = titanium::JNIScope::getEnv();
	if (!env) {
		return titanium::JSException::GetJNIEnvironmentError();
	}
	static jmethodID methodID = NULL;
	if (!methodID) {
		methodID = env->GetMethodID(BarcodeModule::javaClass, "getHasLED", "()Z");
		if (!methodID) {
			const char *error = "Couldn't find proxy method 'getHasLED' with signature '()Z'";
			LOGE(TAG, error);
				return titanium::JSException::Error(error);
		}
	}

	titanium::Proxy* proxy = titanium::Proxy::unwrap(args.Holder());

	jvalue* jArguments = 0;

	jobject javaProxy = proxy->getJavaObject();
	jboolean jResult = (jboolean)env->CallBooleanMethodA(javaProxy, methodID, jArguments);



	if (!JavaObject::useGlobalRefs) {
		env->DeleteLocalRef(javaProxy);
	}



	if (env->ExceptionCheck()) {
		Handle<Value> jsException = titanium::JSException::fromJavaException();
		env->ExceptionClear();
		return jsException;
	}


	Handle<Boolean> v8Result = titanium::TypeConverter::javaBooleanToJsBoolean(env, jResult);



	return v8Result;

}
Handle<Value> BarcodeModule::setUseFrontCamera(const Arguments& args)
{
	LOGD(TAG, "setUseFrontCamera()");
	HandleScope scope;

	JNIEnv *env = titanium::JNIScope::getEnv();
	if (!env) {
		return titanium::JSException::GetJNIEnvironmentError();
	}
	static jmethodID methodID = NULL;
	if (!methodID) {
		methodID = env->GetMethodID(BarcodeModule::javaClass, "setUseFrontCamera", "(Z)V");
		if (!methodID) {
			const char *error = "Couldn't find proxy method 'setUseFrontCamera' with signature '(Z)V'";
			LOGE(TAG, error);
				return titanium::JSException::Error(error);
		}
	}

	titanium::Proxy* proxy = titanium::Proxy::unwrap(args.Holder());

	if (args.Length() < 1) {
		char errorStringBuffer[100];
		sprintf(errorStringBuffer, "setUseFrontCamera: Invalid number of arguments. Expected 1 but got %d", args.Length());
		return ThrowException(Exception::Error(String::New(errorStringBuffer)));
	}

	jvalue jArguments[1];




	if (!args[0]->IsBoolean() && !args[0]->IsNull()) {
		const char *error = "Invalid value, expected type Boolean.";
		LOGE(TAG, error);
		return titanium::JSException::Error(error);
	}
	
	
	if (!args[0]->IsNull()) {
		Local<Boolean> arg_0 = args[0]->ToBoolean();
		jArguments[0].z =
			titanium::TypeConverter::jsBooleanToJavaBoolean(env, arg_0);
	} else {
		jArguments[0].z = NULL;
	}

	jobject javaProxy = proxy->getJavaObject();
	env->CallVoidMethodA(javaProxy, methodID, jArguments);

	if (!JavaObject::useGlobalRefs) {
		env->DeleteLocalRef(javaProxy);
	}



	if (env->ExceptionCheck()) {
		titanium::JSException::fromJavaException();
		env->ExceptionClear();
	}




	return v8::Undefined();

}
Handle<Value> BarcodeModule::setUseLED(const Arguments& args)
{
	LOGD(TAG, "setUseLED()");
	HandleScope scope;

	JNIEnv *env = titanium::JNIScope::getEnv();
	if (!env) {
		return titanium::JSException::GetJNIEnvironmentError();
	}
	static jmethodID methodID = NULL;
	if (!methodID) {
		methodID = env->GetMethodID(BarcodeModule::javaClass, "setUseLED", "(Z)V");
		if (!methodID) {
			const char *error = "Couldn't find proxy method 'setUseLED' with signature '(Z)V'";
			LOGE(TAG, error);
				return titanium::JSException::Error(error);
		}
	}

	titanium::Proxy* proxy = titanium::Proxy::unwrap(args.Holder());

	if (args.Length() < 1) {
		char errorStringBuffer[100];
		sprintf(errorStringBuffer, "setUseLED: Invalid number of arguments. Expected 1 but got %d", args.Length());
		return ThrowException(Exception::Error(String::New(errorStringBuffer)));
	}

	jvalue jArguments[1];




	if (!args[0]->IsBoolean() && !args[0]->IsNull()) {
		const char *error = "Invalid value, expected type Boolean.";
		LOGE(TAG, error);
		return titanium::JSException::Error(error);
	}
	
	
	if (!args[0]->IsNull()) {
		Local<Boolean> arg_0 = args[0]->ToBoolean();
		jArguments[0].z =
			titanium::TypeConverter::jsBooleanToJavaBoolean(env, arg_0);
	} else {
		jArguments[0].z = NULL;
	}

	jobject javaProxy = proxy->getJavaObject();
	env->CallVoidMethodA(javaProxy, methodID, jArguments);

	if (!JavaObject::useGlobalRefs) {
		env->DeleteLocalRef(javaProxy);
	}



	if (env->ExceptionCheck()) {
		titanium::JSException::fromJavaException();
		env->ExceptionClear();
	}




	return v8::Undefined();

}
Handle<Value> BarcodeModule::capture(const Arguments& args)
{
	LOGD(TAG, "capture()");
	HandleScope scope;

	JNIEnv *env = titanium::JNIScope::getEnv();
	if (!env) {
		return titanium::JSException::GetJNIEnvironmentError();
	}
	static jmethodID methodID = NULL;
	if (!methodID) {
		methodID = env->GetMethodID(BarcodeModule::javaClass, "capture", "(Ljava/util/HashMap;)V");
		if (!methodID) {
			const char *error = "Couldn't find proxy method 'capture' with signature '(Ljava/util/HashMap;)V'";
			LOGE(TAG, error);
				return titanium::JSException::Error(error);
		}
	}

	titanium::Proxy* proxy = titanium::Proxy::unwrap(args.Holder());


	jvalue jArguments[1];




	bool isNew_0;
	if (args.Length() <= 0) {
		jArguments[0].l = NULL;

	} else {
	
	if (!args[0]->IsNull()) {
		Local<Value> arg_0 = args[0];
		jArguments[0].l =
			titanium::TypeConverter::jsValueToJavaObject(env, arg_0, &isNew_0);
	} else {
		jArguments[0].l = NULL;
	}
	}

	jobject javaProxy = proxy->getJavaObject();
	env->CallVoidMethodA(javaProxy, methodID, jArguments);

	if (!JavaObject::useGlobalRefs) {
		env->DeleteLocalRef(javaProxy);
	}



			if (isNew_0) {
				env->DeleteLocalRef(jArguments[0].l);
			}


	if (env->ExceptionCheck()) {
		titanium::JSException::fromJavaException();
		env->ExceptionClear();
	}




	return v8::Undefined();

}
Handle<Value> BarcodeModule::getHasCamera(const Arguments& args)
{
	LOGD(TAG, "getHasCamera()");
	HandleScope scope;

	JNIEnv *env = titanium::JNIScope::getEnv();
	if (!env) {
		return titanium::JSException::GetJNIEnvironmentError();
	}
	static jmethodID methodID = NULL;
	if (!methodID) {
		methodID = env->GetMethodID(BarcodeModule::javaClass, "getHasCamera", "()Z");
		if (!methodID) {
			const char *error = "Couldn't find proxy method 'getHasCamera' with signature '()Z'";
			LOGE(TAG, error);
				return titanium::JSException::Error(error);
		}
	}

	titanium::Proxy* proxy = titanium::Proxy::unwrap(args.Holder());

	jvalue* jArguments = 0;

	jobject javaProxy = proxy->getJavaObject();
	jboolean jResult = (jboolean)env->CallBooleanMethodA(javaProxy, methodID, jArguments);



	if (!JavaObject::useGlobalRefs) {
		env->DeleteLocalRef(javaProxy);
	}



	if (env->ExceptionCheck()) {
		Handle<Value> jsException = titanium::JSException::fromJavaException();
		env->ExceptionClear();
		return jsException;
	}


	Handle<Boolean> v8Result = titanium::TypeConverter::javaBooleanToJsBoolean(env, jResult);



	return v8Result;

}
Handle<Value> BarcodeModule::cancel(const Arguments& args)
{
	LOGD(TAG, "cancel()");
	HandleScope scope;

	JNIEnv *env = titanium::JNIScope::getEnv();
	if (!env) {
		return titanium::JSException::GetJNIEnvironmentError();
	}
	static jmethodID methodID = NULL;
	if (!methodID) {
		methodID = env->GetMethodID(BarcodeModule::javaClass, "cancel", "()V");
		if (!methodID) {
			const char *error = "Couldn't find proxy method 'cancel' with signature '()V'";
			LOGE(TAG, error);
				return titanium::JSException::Error(error);
		}
	}

	titanium::Proxy* proxy = titanium::Proxy::unwrap(args.Holder());

	jvalue* jArguments = 0;

	jobject javaProxy = proxy->getJavaObject();
	env->CallVoidMethodA(javaProxy, methodID, jArguments);

	if (!JavaObject::useGlobalRefs) {
		env->DeleteLocalRef(javaProxy);
	}



	if (env->ExceptionCheck()) {
		titanium::JSException::fromJavaException();
		env->ExceptionClear();
	}




	return v8::Undefined();

}
Handle<Value> BarcodeModule::getUseFrontCamera(const Arguments& args)
{
	LOGD(TAG, "getUseFrontCamera()");
	HandleScope scope;

	JNIEnv *env = titanium::JNIScope::getEnv();
	if (!env) {
		return titanium::JSException::GetJNIEnvironmentError();
	}
	static jmethodID methodID = NULL;
	if (!methodID) {
		methodID = env->GetMethodID(BarcodeModule::javaClass, "getUseFrontCamera", "()Z");
		if (!methodID) {
			const char *error = "Couldn't find proxy method 'getUseFrontCamera' with signature '()Z'";
			LOGE(TAG, error);
				return titanium::JSException::Error(error);
		}
	}

	titanium::Proxy* proxy = titanium::Proxy::unwrap(args.Holder());

	jvalue* jArguments = 0;

	jobject javaProxy = proxy->getJavaObject();
	jboolean jResult = (jboolean)env->CallBooleanMethodA(javaProxy, methodID, jArguments);



	if (!JavaObject::useGlobalRefs) {
		env->DeleteLocalRef(javaProxy);
	}



	if (env->ExceptionCheck()) {
		Handle<Value> jsException = titanium::JSException::fromJavaException();
		env->ExceptionClear();
		return jsException;
	}


	Handle<Boolean> v8Result = titanium::TypeConverter::javaBooleanToJsBoolean(env, jResult);



	return v8Result;

}
Handle<Value> BarcodeModule::parse(const Arguments& args)
{
	LOGD(TAG, "parse()");
	HandleScope scope;

	JNIEnv *env = titanium::JNIScope::getEnv();
	if (!env) {
		return titanium::JSException::GetJNIEnvironmentError();
	}
	static jmethodID methodID = NULL;
	if (!methodID) {
		methodID = env->GetMethodID(BarcodeModule::javaClass, "parse", "(Ljava/util/HashMap;)V");
		if (!methodID) {
			const char *error = "Couldn't find proxy method 'parse' with signature '(Ljava/util/HashMap;)V'";
			LOGE(TAG, error);
				return titanium::JSException::Error(error);
		}
	}

	titanium::Proxy* proxy = titanium::Proxy::unwrap(args.Holder());

	if (args.Length() < 1) {
		char errorStringBuffer[100];
		sprintf(errorStringBuffer, "parse: Invalid number of arguments. Expected 1 but got %d", args.Length());
		return ThrowException(Exception::Error(String::New(errorStringBuffer)));
	}

	jvalue jArguments[1];




	bool isNew_0;
	
	if (!args[0]->IsNull()) {
		Local<Value> arg_0 = args[0];
		jArguments[0].l =
			titanium::TypeConverter::jsValueToJavaObject(env, arg_0, &isNew_0);
	} else {
		jArguments[0].l = NULL;
	}

	jobject javaProxy = proxy->getJavaObject();
	env->CallVoidMethodA(javaProxy, methodID, jArguments);

	if (!JavaObject::useGlobalRefs) {
		env->DeleteLocalRef(javaProxy);
	}



			if (isNew_0) {
				env->DeleteLocalRef(jArguments[0].l);
			}


	if (env->ExceptionCheck()) {
		titanium::JSException::fromJavaException();
		env->ExceptionClear();
	}




	return v8::Undefined();

}

// Dynamic property accessors -------------------------------------------------

Handle<Value> BarcodeModule::getter_useFrontCamera(Local<String> property, const AccessorInfo& info)
{
	LOGD(TAG, "get useFrontCamera");
	HandleScope scope;

	JNIEnv *env = titanium::JNIScope::getEnv();
	if (!env) {
		return titanium::JSException::GetJNIEnvironmentError();
	}
	static jmethodID methodID = NULL;
	if (!methodID) {
		methodID = env->GetMethodID(BarcodeModule::javaClass, "getUseFrontCamera", "()Z");
		if (!methodID) {
			const char *error = "Couldn't find proxy method 'getUseFrontCamera' with signature '()Z'";
			LOGE(TAG, error);
				return titanium::JSException::Error(error);
		}
	}

	titanium::Proxy* proxy = titanium::Proxy::unwrap(info.Holder());

	if (!proxy) {
		return Undefined();
	}

	jvalue* jArguments = 0;

	jobject javaProxy = proxy->getJavaObject();
	jboolean jResult = (jboolean)env->CallBooleanMethodA(javaProxy, methodID, jArguments);



	if (!JavaObject::useGlobalRefs) {
		env->DeleteLocalRef(javaProxy);
	}



	if (env->ExceptionCheck()) {
		Handle<Value> jsException = titanium::JSException::fromJavaException();
		env->ExceptionClear();
		return jsException;
	}


	Handle<Boolean> v8Result = titanium::TypeConverter::javaBooleanToJsBoolean(env, jResult);



	return v8Result;

}

void BarcodeModule::setter_useFrontCamera(Local<String> property, Local<Value> value, const AccessorInfo& info)
{
	LOGD(TAG, "set useFrontCamera");
	HandleScope scope;

	JNIEnv *env = titanium::JNIScope::getEnv();
	if (!env) {
		LOGE(TAG, "Failed to get environment, useFrontCamera wasn't set");
		return;
	}

	static jmethodID methodID = NULL;
	if (!methodID) {
		methodID = env->GetMethodID(BarcodeModule::javaClass, "setUseFrontCamera", "(Z)V");
		if (!methodID) {
			const char *error = "Couldn't find proxy method 'setUseFrontCamera' with signature '(Z)V'";
			LOGE(TAG, error);
		}
	}

	titanium::Proxy* proxy = titanium::Proxy::unwrap(info.Holder());
	if (!proxy) {
		return;
	}

	jvalue jArguments[1];

	if (!value->IsBoolean() && !value->IsNull()) {
		const char *error = "Invalid value, expected type Boolean.";
		LOGE(TAG, error);
	}
	
	
	if (!value->IsNull()) {
		Local<Boolean> arg_0 = value->ToBoolean();
		jArguments[0].z =
			titanium::TypeConverter::jsBooleanToJavaBoolean(env, arg_0);
	} else {
		jArguments[0].z = NULL;
	}

	jobject javaProxy = proxy->getJavaObject();
	env->CallVoidMethodA(javaProxy, methodID, jArguments);

	if (!JavaObject::useGlobalRefs) {
		env->DeleteLocalRef(javaProxy);
	}



	if (env->ExceptionCheck()) {
		titanium::JSException::fromJavaException();
		env->ExceptionClear();
	}




}


Handle<Value> BarcodeModule::getter_hasCamera(Local<String> property, const AccessorInfo& info)
{
	LOGD(TAG, "get hasCamera");
	HandleScope scope;

	JNIEnv *env = titanium::JNIScope::getEnv();
	if (!env) {
		return titanium::JSException::GetJNIEnvironmentError();
	}
	static jmethodID methodID = NULL;
	if (!methodID) {
		methodID = env->GetMethodID(BarcodeModule::javaClass, "getHasCamera", "()Z");
		if (!methodID) {
			const char *error = "Couldn't find proxy method 'getHasCamera' with signature '()Z'";
			LOGE(TAG, error);
				return titanium::JSException::Error(error);
		}
	}

	titanium::Proxy* proxy = titanium::Proxy::unwrap(info.Holder());

	if (!proxy) {
		return Undefined();
	}

	jvalue* jArguments = 0;

	jobject javaProxy = proxy->getJavaObject();
	jboolean jResult = (jboolean)env->CallBooleanMethodA(javaProxy, methodID, jArguments);



	if (!JavaObject::useGlobalRefs) {
		env->DeleteLocalRef(javaProxy);
	}



	if (env->ExceptionCheck()) {
		Handle<Value> jsException = titanium::JSException::fromJavaException();
		env->ExceptionClear();
		return jsException;
	}


	Handle<Boolean> v8Result = titanium::TypeConverter::javaBooleanToJsBoolean(env, jResult);



	return v8Result;

}



Handle<Value> BarcodeModule::getter_useLED(Local<String> property, const AccessorInfo& info)
{
	LOGD(TAG, "get useLED");
	HandleScope scope;

	JNIEnv *env = titanium::JNIScope::getEnv();
	if (!env) {
		return titanium::JSException::GetJNIEnvironmentError();
	}
	static jmethodID methodID = NULL;
	if (!methodID) {
		methodID = env->GetMethodID(BarcodeModule::javaClass, "getUseLED", "()Z");
		if (!methodID) {
			const char *error = "Couldn't find proxy method 'getUseLED' with signature '()Z'";
			LOGE(TAG, error);
				return titanium::JSException::Error(error);
		}
	}

	titanium::Proxy* proxy = titanium::Proxy::unwrap(info.Holder());

	if (!proxy) {
		return Undefined();
	}

	jvalue* jArguments = 0;

	jobject javaProxy = proxy->getJavaObject();
	jboolean jResult = (jboolean)env->CallBooleanMethodA(javaProxy, methodID, jArguments);



	if (!JavaObject::useGlobalRefs) {
		env->DeleteLocalRef(javaProxy);
	}



	if (env->ExceptionCheck()) {
		Handle<Value> jsException = titanium::JSException::fromJavaException();
		env->ExceptionClear();
		return jsException;
	}


	Handle<Boolean> v8Result = titanium::TypeConverter::javaBooleanToJsBoolean(env, jResult);



	return v8Result;

}

void BarcodeModule::setter_useLED(Local<String> property, Local<Value> value, const AccessorInfo& info)
{
	LOGD(TAG, "set useLED");
	HandleScope scope;

	JNIEnv *env = titanium::JNIScope::getEnv();
	if (!env) {
		LOGE(TAG, "Failed to get environment, useLED wasn't set");
		return;
	}

	static jmethodID methodID = NULL;
	if (!methodID) {
		methodID = env->GetMethodID(BarcodeModule::javaClass, "setUseLED", "(Z)V");
		if (!methodID) {
			const char *error = "Couldn't find proxy method 'setUseLED' with signature '(Z)V'";
			LOGE(TAG, error);
		}
	}

	titanium::Proxy* proxy = titanium::Proxy::unwrap(info.Holder());
	if (!proxy) {
		return;
	}

	jvalue jArguments[1];

	if (!value->IsBoolean() && !value->IsNull()) {
		const char *error = "Invalid value, expected type Boolean.";
		LOGE(TAG, error);
	}
	
	
	if (!value->IsNull()) {
		Local<Boolean> arg_0 = value->ToBoolean();
		jArguments[0].z =
			titanium::TypeConverter::jsBooleanToJavaBoolean(env, arg_0);
	} else {
		jArguments[0].z = NULL;
	}

	jobject javaProxy = proxy->getJavaObject();
	env->CallVoidMethodA(javaProxy, methodID, jArguments);

	if (!JavaObject::useGlobalRefs) {
		env->DeleteLocalRef(javaProxy);
	}



	if (env->ExceptionCheck()) {
		titanium::JSException::fromJavaException();
		env->ExceptionClear();
	}




}


Handle<Value> BarcodeModule::getter_hasLED(Local<String> property, const AccessorInfo& info)
{
	LOGD(TAG, "get hasLED");
	HandleScope scope;

	JNIEnv *env = titanium::JNIScope::getEnv();
	if (!env) {
		return titanium::JSException::GetJNIEnvironmentError();
	}
	static jmethodID methodID = NULL;
	if (!methodID) {
		methodID = env->GetMethodID(BarcodeModule::javaClass, "getHasLED", "()Z");
		if (!methodID) {
			const char *error = "Couldn't find proxy method 'getHasLED' with signature '()Z'";
			LOGE(TAG, error);
				return titanium::JSException::Error(error);
		}
	}

	titanium::Proxy* proxy = titanium::Proxy::unwrap(info.Holder());

	if (!proxy) {
		return Undefined();
	}

	jvalue* jArguments = 0;

	jobject javaProxy = proxy->getJavaObject();
	jboolean jResult = (jboolean)env->CallBooleanMethodA(javaProxy, methodID, jArguments);



	if (!JavaObject::useGlobalRefs) {
		env->DeleteLocalRef(javaProxy);
	}



	if (env->ExceptionCheck()) {
		Handle<Value> jsException = titanium::JSException::fromJavaException();
		env->ExceptionClear();
		return jsException;
	}


	Handle<Boolean> v8Result = titanium::TypeConverter::javaBooleanToJsBoolean(env, jResult);



	return v8Result;

}




		} // barcode
		} // ti
