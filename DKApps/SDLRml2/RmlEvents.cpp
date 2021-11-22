#include "RmlEvents.h"
#include "RmlUtility.h"
//#include "RMLClass.h"

std::vector<RmlEvents*> RmlEvents::events;
std::vector<std::function<bool(const Rml::String&, const Rml::String&)> > RmlEvents::reg_funcs;
std::vector<std::function<bool(const Rml::String&, const Rml::String&)> > RmlEvents::unreg_funcs;
std::vector<std::function<bool(const Rml::String&, const Rml::String&, const Rml::String&)> > RmlEvents::send_funcs;

bool RmlEvents::AddEvent(const Rml::String& id, const Rml::String& type, std::function<bool(RmlEvents*)> func){
	return RmlEvents::AddEvent(id, type, "", func);
}

bool RmlEvents::AddEvent(const Rml::String& id, const Rml::String& type, const Rml::String& jsreturn, std::function<bool(RmlEvents*)> func){
	Rml::String _jsreturn = jsreturn;
	RmlUtility::replace(_jsreturn, "() { [ecmascript code] }", ""); //remove  () { [ecmascript code] }
	if(id.empty())
		return RMLERROR("("+id+","+type+","+_jsreturn+"): No Id Specified\n");
	if(type.empty())
		return RMLERROR("("+id+","+type+","+_jsreturn+"): No Type Specified\n");
	RmlEvents* event = new RmlEvents;
	event->id = id;
	event->type = type;
	event->jsreturn = _jsreturn;
	event->event_func = func;
	for(unsigned int i = 0; i < events.size(); ++i){
		if(event == events[i]){
			RMLWARN("Event already Exists, Re-registering. ("+id+" : "+type+" : "+_jsreturn+")\n.");
			events[i] = event;
			for(unsigned int nn=0; nn<reg_funcs.size(); ++nn)
				reg_funcs[nn](id, type); //External Reg Functions
			return true;
		}
	}
	events.push_back(event);
	for(unsigned int i=0; i<reg_funcs.size(); ++i)
		reg_funcs[i](id, type); //External Reg Functions
	return true;
}

bool RmlEvents::SendEvent(const Rml::String& id, const Rml::String& type, const Rml::String& value){
	if(!RmlUtility::stringsMatch(id,"RmlLog") && !RmlUtility::stringsMatch(type,"second") && !RmlUtility::stringsMatch(type,"mousemove")) //prevent looping messages
	if(type.empty())
		return RMLERROR("("+id+", ,"+value+"): No Type Specified \n");
	if(id.empty())
		return RMLERROR("( ,"+type+","+value+"): No Id Specified \n");
	//call the function directly
	for(unsigned int i = 0; i < events.size(); ++i){
		if((RmlUtility::stringsMatch(events[i]->id, id)) && RmlUtility::stringsMatch(events[i]->type, type)){
			events[i]->data.clear();
			events[i]->data.push_back(value);
			events[i]->event_func(events[i]); //call the function linked to the event
			if(i < events.size())
				events[i]->data.clear(); //clear data after send
			if(!RmlUtility::stringsMatch(id,"window"))
				return true;
		}
	}
	for(unsigned int i=0; i<send_funcs.size(); ++i)
		send_funcs[i](id, type, value); //returns bool
	return true;
}

bool RmlEvents::RemoveEvent(const Rml::String& id, const Rml::String& type, const Rml::String& jsreturn){
	Rml::String _jsreturn = jsreturn;
	RmlUtility::replace(_jsreturn, "() { [ecmascript code] }", ""); //remove  () { [ecmascript code] }
	for(unsigned int i = 0; i < events.size(); ++i){
		if(RmlUtility::stringsMatch(events[i]->id, id) && RmlUtility::stringsMatch(events[i]->type, type) && RmlUtility::stringsMatch(events[i]->jsreturn, _jsreturn)){
			events.erase(events.begin()+i);
			return true; //This event should not exist twice.
		}
	}
	for(unsigned int i=0; i<unreg_funcs.size(); ++i)
		unreg_funcs[i](id, type); //returns bool
	return true;
}

bool RmlEvents::RemoveEvents(const Rml::String& id, const Rml::String& type){
	for(unsigned int i = 0; i < events.size(); ++i){
		if(RmlUtility::stringsMatch(events[i]->id,id) && RmlUtility::stringsMatch(events[i]->type,type)){
			events.erase(events.begin()+i);
			i--;
		}
	}
	return true;
}

bool RmlEvents::RemoveEvents(const Rml::String& variable){
	//variable can be id or jsreturn
	Rml::String _variable = variable;
	RmlUtility::replace(_variable, "() { [ecmascript code] }", ""); //remove  () { [ecmascript code] }
	for(unsigned int i=0; i < events.size(); ++i){
		if(RmlUtility::stringsMatch(events[i]->id, _variable) || RmlUtility::stringsMatch(events[i]->jsreturn, _variable)){
			events.erase(events.begin()+i);
			i--;
		}
	}
	return true;
}

bool RmlEvents::RemoveEvents(){
	for(unsigned int i = 0; i < events.size(); ++i){
			events.erase(events.begin()+i);
			i--;
	}
	return true;
}

Rml::String RmlEvents::GetType(){
	return type;
}

Rml::String RmlEvents::GetJSReturn(){
	return jsreturn;
}

Rml::String RmlEvents::GetId(){
	return id;
}

//Rml::String RmlEvents::GetValue(){
//	Rml::String value = std::to_string(data, ",");
//	return value;
//}

Rml::String RmlEvents::GetValue(int n){
	return data[n];
}

int RmlEvents::GetKeyNum(){
	if (data.size() < 1) 
		return 0;
	//return toInt(data[0]);
}

bool RmlEvents::RenameEventId(const Rml::String& oldID, const Rml::String& newID){
	for(unsigned int i = 0; i < events.size(); ++i){
		if(RmlUtility::stringsMatch(events[i]->id, oldID))
			events[i]->id = newID;
	}
	return true;
}
