/*
* This source file is part of digitalknob, the cross-platform C/C++/Javascript/Html/Css Solution
*
* For the latest information, see https://github.com/aquawicket/DigitalKnob
*
* Copyright(c) 2010 - 2022 Digitalknob Team, and contributors
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files(the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions :
*
* The above copyright noticeand this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#pragma once
#ifndef RmlEvents_H
#define RmlEvents_H
#include <functional>
#include <RmlUi/Core.h>

class RmlEvents{
public:
	static bool AddEvent(const Rml::String& id, const Rml::String& type, std::function<bool(RmlEvents*)> func);
	static bool AddEvent(const Rml::String& id, const Rml::String& type, const Rml::String& jsreturn, std::function<bool(RmlEvents*)> func);
	static bool RemoveEvent(const Rml::String& id, const Rml::String& type, const Rml::String& jsreturn);
	static bool RemoveEvents(const Rml::String& id, const Rml::String& type);
	static bool RemoveEvents(const Rml::String& variable); //variable can be id or jsreturn
	static bool RemoveEvents();
	static bool SendEvent(const Rml::String& id, const Rml::String& type, const Rml::String& value);
	static bool RenameEventId(const Rml::String& oldID, const Rml::String& newID);
	Rml::String GetId();
	Rml::String GetType();
	Rml::String GetJSReturn();
	Rml::String GetValue();
	Rml::String GetValue(int n);
	int GetKeyNum();
	static std::vector<RmlEvents*> events;

private:
	RmlEvents(){};
	Rml::String id;
	Rml::String type;
	Rml::String jsreturn;

public:
	Rml::StringList data;
	void* data2;
	std::function<bool(RmlEvents*)> event_func;

	//template<class T> 
	//static bool AddEvent(const Rml::String& id, const Rml::String& type, bool (T::* func) (RmlEvents*), T* _this) {
	//	return RmlEvents::AddEvent(id, type, std::bind(func, _this, std::placeholders::_1), _this);
	//}

	template<class T>
	static bool AddEvent(const Rml::String& id, const Rml::String& type, const Rml::String& jsreturn, bool (T::* func) (RmlEvents*), T* _this) {
		return RmlEvents::AddEvent(id, type, jsreturn, std::bind(func, _this, std::placeholders::_1), _this);
	}

	template<class T>
	static void AddRegisterEventFunc(bool (T::* func)(const Rml::String&, const Rml::String&), T* _this) {
		reg_funcs.push_back(std::bind(func, _this, std::placeholders::_1, std::placeholders::_2));
	}

	template<class T>
	static void RemoveRegisterEventFunc(bool (T::*func)(const Rml::String&, const Rml::String&), T* _this){
		for(unsigned int i=0; i<reg_funcs.size(); ++i){
			//if (reg_funcs[i] == std::bind(func, _this, std::placeholders::_1, std::placeholders::_2)) {
			//	reg_funcs.erase(reg_funcs.begin() + i);
			//}
		}
	}
	
	template<class T>
	static void AddUnegisterEventFunc(bool (T::* func)(const Rml::String&, const Rml::String&), T* _this) {
		unreg_funcs.push_back(std::bind(func, _this, std::placeholders::_1, std::placeholders::_2));
	}

	template<class T>
	static void RemoveUnegisterEventFunc(bool (T::*func)(const Rml::String&, const Rml::String&), T* _this){
		for(unsigned int i=0; i<unreg_funcs.size(); ++i){
			//if (unreg_funcs[i] == std::bind(func, _this, std::placeholders::_1, std::placeholders::_2)) {
			//	unreg_funcs.erase(unreg_funcs.begin() + i);
			//}
		}
	}
	
	template<class T>
	static void AddSendEventFunc(bool (T::* func)(const Rml::String&, const Rml::String&, const Rml::String&), T* _this) {
		send_funcs.push_back(std::bind(func, _this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	}

	template<class T>
	static void RemoveSendEventFunc(bool (T::*func)(const Rml::String&, const Rml::String&, const Rml::String&), T* _this){
		for(unsigned int i=0; i<send_funcs.size(); ++i){
			//if (send_funcs[i] == std::bind(func, _this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)) {
			//	send_funcs.erase(send_funcs.begin() + i);
			//}
		}
	}

	static std::vector<std::function<bool(const Rml::String&, const Rml::String&)> > reg_funcs;
	static std::vector<std::function<bool(const Rml::String&, const Rml::String&)> > unreg_funcs;
	static std::vector<std::function<bool(const Rml::String&, const Rml::String&, const Rml::String&)> > send_funcs;
};

#endif //RmlEvents_H