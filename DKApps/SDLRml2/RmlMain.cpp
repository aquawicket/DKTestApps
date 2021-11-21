#ifdef USE_rmlui_debugger
#include <RmlUi/Debugger.h>
#endif
#include "RmlMain.h"
#include "RmlWindow.h"
#include "SDLRml.h"
#include "RMLUtility.h"
//#include "Curl.h"
//#include "DKDuktape/DKDuktape.h"
//#include "DKXml/DKXml.h"
//#include "RmlMain/RmlMainHeadInstancer.h"

#include <RmlUi/Core/StreamMemory.h>
#include "../../3rdParty/RmlUi-master/Source/Core/PluginRegistry.h"
#include "../../3rdParty/RmlUi-master/Source/Core/XMLNodeHandlerDefault.h"
#include "../../3rdParty/RmlUi-master/Source/Core/XMLNodeHandlerBody.h"

//#define DRAG_FIX 1
RmlFile* RmlMain::rmlMainFile = NULL;

bool RmlMain::Init(){
	//RmlClass::RmlCreate("RmlMainJS");
	//RmlClass::RmlCreate("RmlMainV8");
	SDLRml* sdlRml = NULL;
	document = NULL;
	if(!rmlMainFile){ 
		rmlMainFile = new RmlFile();
		Rml::SetFileInterface(rmlMainFile);
	}

	//Create SDLRml or DKOSGRml
	//if(RmlClass::DKAvailable("SDLRml")){
	SDLRml* sldRml = new SDLRml();
	if(sdlRml){
		if(!Rml::Initialise())
			return RMLERROR("Rml::Initialise(): failed\n");
		int w;
		if(!RmlWindow::GetWidth(w)){ return false; }
		int h;
		if(!RmlWindow::GetHeight(h)){ return false; }
		context = Rml::CreateContext("default", Rml::Vector2i(w, h));
	}
	//else if(RmlClass::RmlAvailable("SFMLRml")){
	//	RmlClass::RmlCreate("SFMLRml");
	//}
	else{
		RMLERROR("No window types registered\n");
		return false;
	}
#ifdef USE_rmlui_debugger
	if (!Rml::Debugger::Initialise(context))
		return RMLERROR("Rml::Debugger::Initialise(): failed\n");
#endif
	//Add missing stylesheet properties
	//TODO - https://developer.mozilla.org/en-US/docs/Web/CSS/background-repeat
	/*Rml::PropertyId background_repeat =  unused code */ Rml::StyleSheetSpecification::RegisterProperty("background-repeat", "repeat", false)
		.AddParser("keyword", "repeat, space, round, no-repeat")
		.AddParser("string")
		.GetId(); //this supresses background-repeat warnings temporarily
	//TODO - https://developer.mozilla.org/en-US/docs/Web/CSS/border-style
	/* Rml::PropertyId border_style =  unused code */ Rml::StyleSheetSpecification::RegisterProperty("border-style", "none", false)
		.AddParser("keyword", "none, hidden")
		.AddParser("string")
		.GetId(); //this supresses border-style warnings temporarily

	context->SetDocumentsBaseTag("html");
	std::string rmlFonts = RmlFile::Get()->_root + "RmlMain";
	LoadFonts(rmlFonts);
	LoadFonts(RmlFile::Get()->_root);
	//RmlEvents::AddRegisterEventFunc(&RmlMain::RegisterEvent, this);
	//DKEvents::AddUnegisterEventFunc(&RmlMain::UnregisterEvent, this);
	//DKEvents::AddSendEventFunc(&RmlMain::SendEvent, this);
	//DKClass::DKCreate("RmlMainJS");  //NOTE: already call above.   around line 23
	
	//Rml::Factory::RegisterElementInstancer("html", new Rml::ElementInstancerGeneric<Rml::ElementDocument>);
	//Rml::XMLParser::RegisterNodeHandler("html", std::make_shared<Rml::XMLNodeHandlerBody>());
	//Rml::XMLParser::RegisterNodeHandler("head", std::make_shared<HeadInstancer>());
	//Rml::Factory::RegisterElementInstancer("body", new Rml::ElementInstancerElement);
	//Rml::XMLParser::RegisterNodeHandler("body", std::make_shared<Rml::XMLNodeHandlerDefault>());
	
	//RmlClass::RmlCreate("DKDom");
	
	std::string html;
	std::string workingPath = RmlFile::Get()->_root;
	RmlFile::FileToString(workingPath +"RmlMain/blank.html", html);
	RmlFile::ChDir(workingPath);
	LoadHtml(html);
	return true;
}

bool RmlMain::End(){
	if(context){
		Rml::ReleaseTextures();
		Rml::Shutdown();
		delete Rml::GetRenderInterface();
		delete Rml::GetSystemInterface();
		delete Rml::GetFileInterface();
	}
	//RmlClass::RmlClose("RmlMainJS");
	//RmlClass::RmlClose("RmlMainV8");
	//RmlEvents::RemoveRegisterEventFunc(&RmlMain::RegisterEvent, this);
	//RmlEvents::RemoveUnegisterEventFunc(&RmlMain::UnregisterEvent, this);
	//RmlEvents::RemoveSendEventFunc(&RmlMain::SendEvent, this);
	return true;
}

RmlMain* RmlMain::Get()
{
	return this;
}

bool RmlMain::GetSourceCode(std::string& source_code) {
	source_code = document->GetContext()->GetRootElement()->GetInnerRML();
	RMLINFO("######################## CODE FROM RmlUi #########################\n");
	RMLINFO(source_code+"\n");
	RMLINFO("##################################################################\n");
	
	// Actually, we only want the  last html node
	unsigned long n = source_code.rfind("<html");
	if(n < 0)
		return RMLWARN("html tag not found\n");

	source_code = source_code.substr(n);
	RmlUtility::replace(source_code, "<", "\n<"); //put all tags on a new line
	RMLINFO("################## Last <html> node from RmlUi ##################\n");
	RMLINFO(source_code+"\n");
	RMLINFO("#################################################################\n");
	return true;
}

bool RmlMain::LoadFont(const std::string& file){
	if(!Rml::LoadFontFace(file.c_str()))
		return RMLERROR("Could not load "+file+"\n");
	return true;
}

bool RmlMain::LoadFonts(std::string& directory){
	
	char ch = directory.back();
	if(ch != '/')
		directory += '/'; //make sure directory has a trailing /

	RmlStringArray files;
	RmlFile::GetDirectoryContents(directory, files);
	for(unsigned int i=0; i<files.size(); ++i){
		if(RmlFile::IsDirectory(directory+files[i]))
			continue;
		std::string extension;
		RmlFile::GetExtention(files[i],extension);
		if(RmlUtility::stringsMatch(extension,".otf") || RmlUtility::stringsMatch(extension,".ttf")){
			//std::string file;
			//RmlFile::GetFileName(files[i],file);
			LoadFont(directory+files[i]);
		}
	}
	return true;
}

bool RmlMain::LoadHtml(const std::string& html){
	//// Prepair the html document for RmlUi

	std::string rml;
	//rmlMainConverter.HtmlToRml(html, rml);

	//// Clear any document and load the rml into the document
	if (document) {
		Rml::Factory::ClearStyleSheetCache();
		document->Close();
	}
	auto stream = std::make_unique<Rml::StreamMemory>((Rml::byte*)rml.c_str(), rml.size());
	stream->SetSourceURL("[document from memory]");
	Rml::PluginRegistry::NotifyDocumentOpen(context, stream->GetSourceURL().GetURL());
	document = context->CreateDocument("html");
	
	/*
	//Create DOM javascript instance of the document using the documents element address
	std::string rval;
	std::string document_address = elementToAddress(document);
	DKDuktape::RunDuktape("var document = new Document(\"" + document_address + "\");", rval);
	Rml::Element* ele = document;
	*/
	
	/*
	Rml::XMLParser parser(ele);
	parser.Parse(stream.get());
	//Make sure we have <head> and <body> tags
	Rml::ElementList heads;
	Rml::ElementList bodys;
	Rml::Element* head = NULL;
	Rml::Element* body = NULL;
	//Rml::ElementDocument* elementDocument = document->GetOwnerDocument(); unused code
	document->GetOwnerDocument()->GetElementsByTagName(heads, "head");
	if (!heads.empty())
		head = heads[0];
	document->GetOwnerDocument()->GetElementsByTagName(bodys, "body");
	if (!bodys.empty()) 
		body = bodys[0];
	if (!head && !body) {
		document->GetOwnerDocument()->AppendChild(document->CreateElement("head"), true);
		document->GetOwnerDocument()->AppendChild(document->CreateElement("body"), true);
	}
	else if (head && !body)
		document->GetOwnerDocument()->AppendChild(document->CreateElement("body"), true);
	else if (!head && body)
		document->GetOwnerDocument()->InsertBefore(document->CreateElement("head"), body);
	*/

	//Load user agent style sheet
	std::string file = RmlFile::Get()->_root + "RmlMain/RmlMain.css";
	const Rml::StyleSheetContainer* doc_sheet = document->GetOwnerDocument()->GetStyleSheetContainer();
	Rml::SharedPtr<Rml::StyleSheetContainer> file_sheet = Rml::Factory::InstanceStyleSheetFile(file.c_str());
	if(doc_sheet) { 
		//Combine the file_sheet and the doc_sheet into a new_sheet and load it back to the document
		Rml::SharedPtr<Rml::StyleSheetContainer> new_sheet = doc_sheet->CombineStyleSheetContainer(*file_sheet);
		document->GetOwnerDocument()->SetStyleSheetContainer(std::move(new_sheet));
	}
	else  //no current sheet, just load the file sheet
		document->GetOwnerDocument()->SetStyleSheetContainer(std::move(file_sheet));
	//Finish loading the document
	//Rml::ElementUtilities::BindEventAttributes(document);
	Rml::PluginRegistry::NotifyDocumentLoad(document);
	document->DispatchEvent(Rml::EventId::Load, Rml::Dictionary());
	document->UpdateDocument();
	if(!document){
		document = context->LoadDocumentFromMemory("");
		return RMLERROR("RmlMain::LoadHtml(): document invalid\n");
	}
	Rml::ElementList elements;
	RmlMain::Get()->document->GetElementsByTagName(elements, "body");
	if(!elements[0])
		return RMLERROR("body element invalid\n");
	//rmlMainConverter.PostProcess(document);
	//rmlMainConverter.PostProcess(elements[0]);
	document->Show();
#ifdef ANDROID
	//We have to make sure the fonts are loaded on ANDROID
	LoadFonts();
#endif
	return true;
}

bool RmlMain::LoadUrl(const std::string& url){
	std::string _url = url;
	if(RmlUtility::stringContains(_url,":/")) //could be http:// , https://, file:/// or C:/
		href = _url; //absolute path including protocol
	else if(RmlUtility::stringContains(_url,"//")){ //could be //www.site.com/style.css or //site.com/style.css
		return RMLERROR("RmlMain::LoadUrl(): no protocol specified\n"); //absolute path without protocol
	}
	else
		_url = workingPath + _url;
	//Get the working path;
	std::size_t found = _url.find_last_of("/");
	workingPath = _url.substr(0, found + 1);
	RMLINFO("RmlMain::LoadUrl(): workingPath: " + workingPath + "\n");
	RMLINFO("RmlMain::LoadUrl(): href: " + href + "\n");
	//get the protocol
	unsigned long n = _url.find(":");
	protocol = _url.substr(0,n);
	RMLINFO("RmlMain::LoadUrl(): protocol: "+protocol+"\n");
	found = _url.rfind("/");
	_path = _url.substr(0,found+1);
	//DKWARN("RmlMain::LoadUrl(): last / at "+toString(found)+"\n");
	RMLINFO("RmlMain::LoadUrl(): _path = "+_path+"\n");

	std::string html;
	/*
	if(RmlUtility::stringContains(_url, "http://") || RmlUtility::stringContains(_url, "https://")){
		DKClass::DKCreate("DKCurl");
		if(!DKCurl::Get()->HttpFileExists(_url))
			return RMLERROR("Could not locate "+_url+"\n");
		if(!DKCurl::Get()->HttpToString(_url, html))
			return RMLERROR("Could not get html from url "+_url+"\n");
	}
	else{
	*/
	if(!RmlFile::FileToString(_url, html))
		return RMLERROR("RmlFile::FileToString failed on "+_url+"\n");
	//}
	LoadHtml(html);
	return true;
}

void RmlMain::ProcessEvent(Rml::Event& rmlEvent){
	//TODO - make rmlEvent accessable through javascript
	//1. Create Javascript Event object that references the rmlEvent
	std::string rmlEventAddress = eventToAddress(&rmlEvent);
	//std::string code = "new Event("+rmlEventAddress+")";
	//std::string rval;
	//DKDuktape::Get()->RunDuktape(code, rval);
	//RMLINFO("RmlMain::ProcessEvent(): "+code+": rval="+rval+"\n");
	if (!rmlEvent.GetCurrentElement())
		return;
	if (!rmlEvent.GetTargetElement())
		return;
	Rml::Element* currentElement = rmlEvent.GetCurrentElement();
	std::string currentElementAddress = elementToAddress(currentElement);
	Rml::Element* targetElement = rmlEvent.GetTargetElement();
	std::string targetElementAddress = elementToAddress(targetElement);
	std::string type = rmlEvent.GetType();
	//TODO: implement this
    //int phase = (int)rmlEvent.GetPhase(); //{ None, Capture = 1, Target = 2, Bubble = 4 };
	
    
    /*
	// Send this event back to duktape to be processed in javascript
	std::string evnt = "{type:'"+type+"', eventPhase:"+toString(phase)+"}";
	std::string code = "EventFromCPP('"+ currentElementAddress +"',"+evnt+");";
	std::string rval;
	DKDuktape::Get()->RunDuktape(code, rval);
	if(!rval.empty()){ RMLINFO("RmlMain::ProcessEvent(): rval = "+rval+"\n"); }
	*/
	// If the event bubbles up, ignore elements underneith 
	Rml::Context* context = document->GetContext();
	Rml::Element* hoverElement = NULL;
	if (context)
		hoverElement = context->GetHoverElement();
	Rml::Element* hoverParent = NULL;
	if (hoverElement)
		hoverParent = hoverElement->GetParentNode();
	if (hoverParent)
		hover = hoverParent;
	//if(rmlEvent.GetPhase() == 1 && currentElement != hover){ return; }
	/*
	//Event Monitor
	std::string tag = currentElement->GetTagName();
	std::string id = currentElement->GetId();
	std::string target_id = targetElement->GetId();
	std::string target_tag = targetElement->GetTagName();
	std::string hover_id = hover->GetId();
	std::string string = "EVENT: " + type + " (current) " + tag + "> " + id + " (target) " + target_tag + "> " + target_id + "(hover)" + hover_id + "\n";
	RMLINFO(string + "\n");
	*/
#ifdef ANDROID
	//Toggle Keyboard on text element click
	if (type == "mousedown") {
		if (same(currentElement->GetTagName(), "textarea") ||
			same(currentElement->GetTagName(), "input")) {
			CallJavaFunction("toggleKeyboard", "");
			return;
		}
	}
	//Hide Keyboard on input Enter
	if (type == "keydown" && currentElement->GetTagName() == "input") {
		int key = rmlEvent.GetParameter<int>("key_identifier", 0);
		if (key == Rml::Input::KI_RETURN) { //Enter
			CallJavaFunction("toggleKeyboard", "");
			return;
		}
	}
#endif
	if (RmlUtility::stringsMatch(type, "mouseup") && rmlEvent.GetParameter<int>("button", 0) == 1) 
		type = "contextmenu";
	for(unsigned int i = 0; i < RmlEvents::events.size(); ++i){
		RmlEvents* ev = RmlEvents::events[i];
		//certain stored events are altered before comparison 
		std::string _type = ev->GetType();
		if (RmlUtility::stringsMatch(_type, "input"))
			_type = "change";
		//// PROCESS ELEMENT EVENTS //////
		if (RmlUtility::stringsMatch(ev->GetId(), currentElementAddress) && RmlUtility::stringsMatch(_type, type)) {
			ev->data.clear();
			ev->data.push_back(rmlEventAddress);
			//ev->rEvent = &rmlEvent;
			/*
			//pass the value
			if (same(type, "keydown") || same(type, "keyup")) {
				ev->data.clear();
				ev->data.push_back(toString(rmlEvent.GetParameter<int>("key_identifier", 0)));
			}
			if (same(type, "mousedown") || same(type, "mouseup")) {
				ev->data.clear();
				ev->data.push_back(toString(rmlEvent.GetParameter<int>("button", 0)));
			}
			*/
			//FIXME - we run the risk of having event function pointers that point to nowhere
			if (!ev->event_func(ev)){
				RMLERROR("RmlMain::ProcessEvent failed \n");
				return;
			}
		    //call the function linked to the event
			//RMLINFO("Event: "+ev->type+", "+ev->id+"\n");
			//FIXME - StopPropagation() on a mousedown even will bock the elements ability to drag
			// we need to find a way to stop propagation of the event, while allowing drag events.
/*
#ifdef DRAG_FIX
			if (!same(type, "mousedown")) {
#endif
				if (!same(type, "keydown")) 
					rmlEvent.StopPropagation();
#ifdef DRAG_FIX
			}
#endif
*/
			//ev->rEvent = NULL;
			return;
		}
	}
}

bool RmlMain::RegisterEvent(const std::string& elementAddress, const std::string& type){
	if(elementAddress.empty())
		return RMLERROR("RmlMain::RegisterEvent(): elementAddress empty\n"); 
	if(type.empty())
		return RMLERROR("RmlMain::RegisterEvent("+elementAddress+"): type empty\n");
	Rml::Element* element = addressToElement(elementAddress.c_str());
	if(!element)
		return RMLERROR("RmlMain::RegisterEvent("+elementAddress+","+type+"): element invalid\n");
	std::string _type = type;
	if(RmlUtility::stringsMatch(type, "contextmenu"))
		_type = "mouseup";
	if(RmlUtility::stringsMatch(type, "input"))
		_type = "change";
	//NOTE: This was an old libRocket issue and has not been tested for a long time
	//FIXME - StopPropagation() on a mousedown event will bock the elements ability to drag
	// we need to find a way to stop propagation of the event, while allowing drag events.
	// If we bubble our event upward and allow mousedown events to propagate, it works,
	// but it's a very nasty fix as every mousedown listener under the element will process
	// first and then finally process the element clicked, allowing drag.
	// WE don't want to process mousedown on other events! We want a one-shot mousedown event
	// processed for that element and stopped. And it must allow drag to bleed thru.
#ifdef DRAG_FIX
	if(same(type, "mousedown"))
		element->AddEventListener(_type.c_str(), this, true); //bubble up
	else{
#endif
		element->AddEventListener(_type.c_str(), this, false);
#ifdef DRAG_FIX
	}
#endif
	return true;
}

bool RmlMain::SendEvent(const std::string& elementAddress, const std::string& type, const std::string& value){
	if(elementAddress.empty())
		return RMLERROR("elementAddress invalid");
	if(type.empty())
		return RMLERROR("type invalid");
	if(!document)
		return RMLERROR("document invalid");
	//if(same(addressToElement(elementAddress)->GetId(),"window"))
		//DKWARN("RmlMain::SendEvent(): recieved global window event\n");
	Rml::Element* element = addressToElement(elementAddress);
	if(!element)
		return RMLERROR("element invalid");
	Rml::Dictionary parameters;
	//parameters.Set("msg0", value.c_str());
	element->DispatchEvent(type.c_str(), parameters, false);
	return true;
}

bool RmlMain::DebuggerOff(){
#ifdef USE_rmlui_debugger
	Rml::Debugger::SetVisible(false);
	RMLINFO("Rml Debugger OFF\n");
#else
	return RMLERROR("RML Debugger not available \n");
#endif
	return true;
}

bool RmlMain::DebuggerOn(){
#ifdef USE_rmlui_debugger
	Rml::Debugger::SetVisible(true);
	RMLINFO("Rml Debugger ON\n");
#else
	return RMLERROR("RML Debugger not available \n");
#endif
	return true;
}

bool RmlMain::DebuggerToggle(){
#ifdef USE_rmlui_debugger
	if(Rml::Debugger::IsVisible()) //FIXME:  always returns false
		RmlMain::DebuggerOff();
	else
		RmlMain::DebuggerOn();
#else
	return RMLERROR("RML Debugger not available \n");
#endif
	return true;
}

bool RmlMain::UnregisterEvent(const std::string& elementAddress, const std::string& type){
	if(elementAddress.empty())
		return RMLERROR("elementAddress invalid");
	if(type.empty())
		return RMLERROR("type invalid");
	if (RmlUtility::stringsMatch(addressToElement(elementAddress)->GetId(), "window"))
		return RMLERROR("can not Unregister window event");
	//if(!DKValid("RmlMain0")){ return false; }
	Rml::Element* element = addressToElement(elementAddress);
	if(!element)
		return RMLERROR("element invalid");
	std::string _type = type;
	if(RmlUtility::stringsMatch(type, "contextmenu"))
		_type = "mouseup";
	if(RmlUtility::stringsMatch(type, "input"))
		_type = "change";
	element->RemoveEventListener(_type.c_str(), this, false);
	return true;
}

/*
Rml::Event* RmlMain::addressToEvent(const std::string& address){
	Rml::Event* event;
	if (address.compare(0, 2, "0x") != 0 || address.size() <= 2 || address.find_first_not_of("0123456789abcdefABCDEF", 2) != std::string::npos) {
		RMLERROR("the address ("+address+") is not a valid hex notation\n");
		return NULL;
	}
	//Convert a string of an address back into a pointer
	std::stringstream ss;
	ss << address.substr(2, address.size() - 2);
	std::uint64_t tmp;
	if (!(ss >> std::hex >> tmp)) {
		RMLERROR("RmlMain::addressToEvent(" + address + "): invalid address\n");
		return NULL;
	}
	event = reinterpret_cast<Rml::Event*>(tmp);
	if (!event->GetCurrentElement()) {
		RMLERROR("RmlMain::addressToEvent(" + address + "): currentElement invalid\n");
		return NULL;
	}
	return event;
}
*/

/*
std::string RmlMain::eventToAddress(Rml::Event* event){
	if (!event) {
		RMLERROR("RmlMain::eventToAddress(): invalid event\n");
		return "";
	}
	std::stringstream ss;
	const void* address = static_cast<const void*>(event);
#ifdef WIN32
	ss << "0x" << address;
#else 
	ss << address;
#endif
	return ss.str();
}
*/

/*
Rml::Element* RmlMain::addressToElement(const std::string& address) {
	Rml::Element* element = nullptr;
	if (address == "window") {
		element = RmlMain::Get()->document->GetContext()->GetRootElement(); //Root element that holds all the documents.
	}
	else if (address == "document") {
		element = RmlMain::Get()->document->GetOwnerDocument();
	}
	else {
		if (address.compare(0, 2, "0x") != 0 || address.size() <= 2 || address.find_first_not_of("0123456789abcdefABCDEF", 2) != std::string::npos) {
			RMLERROR("NOTE: RmlMain::addressToElement(): the address is not a valid hex notation");
			return NULL;
		}
		//Convert a string of an address back into a pointer
		std::stringstream ss;
		ss << address.substr(2, address.size() - 2);
		std::uint64_t tmp;
		if (!(ss >> std::hex >> tmp)) {
			RMLERROR("invalid address\n");
			return NULL;
		}
		element = reinterpret_cast<Rml::Element*>(tmp);
	}	
	if (!element) {
		RMLERROR("invalid element\n");
		return NULL;
	}
	if (element->GetTagName().empty())
		return NULL;
	return element;
}
*/

/*
std::string RmlMain::elementToAddress(Rml::Element* element){
	if (!element) {
		RMLERROR("RmlMain::elementToAddress(): invalid element\n");
		return "";
	}
	std::stringstream ss;
	if (element == RmlMain::Get()->document->GetContext()->GetRootElement())
		ss << "window";
	else if (element == RmlMain::Get()->document->GetOwnerDocument())
		ss << "document";
	else if (element == RmlMain::Get()->document) {
		//TEST: Let's just test if we ever hear anything from this one
		throw RMLERROR("!!!! element = RmlMain::Get()->document  !!!!");
		ss << "document";
	}
	else {
		const void* address = static_cast<const void*>(element);
#ifdef WIN32
		ss << "0x" << address;
#else 
		ss << address;
#endif
	}
	if (same("0xDDDDDDDD", ss.str()))
		return "";
	return ss.str();
}
*/