#include <algorithm>
#include <iostream>

#include "rapidjson/document.h"

#include "widgettree.h"


static std::shared_ptr<Widget> walk_children(rapidjson::Value node) {
	// if node has children
	rapidjson::Value::ConstMemberIterator itr = node.FindMember("children");
	if (itr != node.MemberEnd()) {
		for (auto& v: itr->value.GetArray()) {
			std::cout << v["type"].GetString() << std::endl;
			std::cout << v.GetType() << std::endl;
			//walk_children(v);
		}
	}
	return nullptr;
}


std::shared_ptr<Container> read_widgettree(std::string json) {
	rapidjson::Document doc;
	doc.Parse(json.c_str());
	
	std::cout << json << std::endl;
	std::string roottype = doc["type"].GetString();
	// get options
	//auto rootwidget = make_widget(roottype);
	walk_children(doc.GetObject()/*rootwidget*/);
	
	return nullptr;
}
