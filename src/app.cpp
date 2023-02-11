#include "html.h"
#include <cstdio>
#include <string>
#include <fstream>
#include <stdexcept>

#define attributeList(a,b) attr a [b]; int a##_##a = 0;
#define _attributeSet(a,b,c) a[a##_##a++] = {(char *)b, (char *)c};
#define list(a) a, a##_##a


int main()
{
	std::ofstream out;
	out.open("web.html");
	Document web;


	//Structure


	element head = web.createChild(false,"head");
	element body = web.createChild(false,"body");


	//"Include external files
	attributeList(extCss,2)
	_attributeSet(extCss,"rel","stylesheet")
	_attributeSet(extCss,"href","testStyles.css")
	element css = web.createChild(&head,true,"link",list(extCss));

	//Create header at body
	attributeList(header,1)
	_attributeSet(header,"class","topHeader")
	attributeList(headerH1C,1)
	_attributeSet(headerH1C,"class","h1container")


	element topDiv = web.createChild(&body,false,"div",list(header));
	element tDH1C = web.createChild(&topDiv,false,"div",list(headerH1C));


	element tDH1 = web.createChild(&tDH1C,"h1","Dress Mate");
	element tDHr = web.createChild(&topDiv,true,"hr");


	//"END"


	std::string webStr = web.getDocumentString();
	//printf("%s\n",webStr.data());

	out << "<!DOCTYPE html>\n" << webStr.data() << std::endl;

	out.close();
}










/*
int main()
{
	Document web;
	try
	{
		attr set[16];
		set[0] = {(char *)"href", (char *)"yo"};
		set[1] = {(char *)"id",(char *)"prep"};
		element head = web.createChild(false, "head");
		element head_span1 = web.createChild(&head, "span", "hehe");
		element head_span2 = web.createChild(&head, "span", "\nhohos");
		element body = web.createChild(false, "body");
		element body_span = web.createChild(&body, "a", "click me!", set, 2);

		std::string webStr = web.getDocumentString();

		printf("Code:\n%s\n",webStr.data());

//		system("rm web.html");
//		system(std::string("echo ").append(webStr).append(" >> web.html").data());

		return 0;
	}
	catch(const std::out_of_range& e)
	{
		printf("Error: %s\n", e.what());
		return -1;
	}
}*/ 

