// Copyright Mozilla Foundation. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.

#include <assert.h>

#include "conversions.h"
#include "v8local.h"

namespace v8 {

Local<Template> Template::New(Isolate* isolate) {
  JSContext* cx = JSContextFromIsolate(isolate);
  JSObject* obj = JS_NewObject(cx, nullptr);
  if (!obj) {
    return Local<Template>();
  }
  JS::Value objVal;
  objVal.setObject(*obj);
  return internal::Local<Template>::NewTemplate(isolate, objVal);
}

void Template::Set(Local<String> name, Local<Data> value,
                   PropertyAttribute attributes) {
  // We have to ignore the return value since the V8 API returns void here.
  Object* thisObj = Object::Cast(GetV8Value(this));
  thisObj->ForceSet(name, value.As<Value>(), attributes);
}
}
