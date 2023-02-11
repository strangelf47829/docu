#include "html.h"
#include <string>
#include <stdexcept>

Document::Document()
{
	root = createChild(false, "html");
}

Document::Document(element _root)
{
	root = _root;
}

void Document::appendChild(element *parent, element *child)
{

//"For both fixed and dynamic: Look for a null element. Then fill in that element
	int childIndex = parent->maxChildren;
	for(int i = 0; i < parent->maxChildren; i++)
	{
		if(parent->children[i] != nullptr)
			continue;
		childIndex = i;
		break;
	}


	if(childIndex < parent->maxChildren)
	{
		//"Empty spot found, now just set it in ig"
		parent->children[childIndex] = child;
		child->parent = parent;
		if(childIndex == parent->childCount)
			parent->childCount++;
	}
	else
	{
#ifdef DOCU_HTML_FIXED
		printf("Could not append Child. (%u)/(%u)\n",childIndex,parent->maxChildren);
		throw std::out_of_range("Attempt to append child to parent failed; Parent child count limit reached");
#else
		throw std::runtime_error("Not implemented yet");
#endif
	}




}

element Document::createChild(bool closureType, const char *tag)
{
	element newElement;

	newElement.tag = (char *)tag;
	newElement.closureType = closureType;
	newElement.parent = &newElement;
	appendChild(&root, &newElement);

	return newElement;
}

element Document::createChild(bool closureType, const char *tag, attr* attributes, int attributeCount)
{
	element newElement;

	newElement.tag = (char *)tag;
	newElement.closureType = closureType;
	newElement.attributes = attributes;
	newElement.maxAttributeCount = attributeCount;
	newElement.attributeCount = attributeCount;
	appendChild(&root, &newElement);

	return newElement;
}


element Document::createChild(const char *tag, const char *innerHtml)
{
	element newElement;

	newElement.tag = (char *)tag;
	newElement.innerHTML = (char *)innerHtml;
	newElement.containsInnerHTML = true;
	newElement.closureType = false;
	appendChild(&root, &newElement);

	return newElement;
}


element Document::createChild(const char *tag, const char *innerHtml, attr *attributes, int attributeCount)
{
	element newElement;

	newElement.tag = (char *)tag;
	newElement.innerHTML = (char *)innerHtml;
	newElement.containsInnerHTML = true;
	newElement.attributes = attributes;
	newElement.maxAttributeCount = attributeCount;
	newElement.attributeCount = attributeCount;
	newElement.closureType = false;
	appendChild(&root, &newElement);

	return newElement;

}



element Document::createChild(element *parent, bool closureType, const char *tag)
{
	element newElement;

	newElement.tag = (char *)tag;
	newElement.closureType = closureType;
	newElement.parent = &newElement;
	appendChild(parent, &newElement);

	return newElement;
}


element Document::createChild(element *parent, bool closureType, const char *tag, attr *attributes, int attributeCount)
{
	element newElement;

	newElement.tag = (char *)tag;
	newElement.closureType = closureType;
	newElement.attributes = attributes;
	newElement.maxAttributeCount = attributeCount;
	newElement.attributeCount = attributeCount;
	appendChild(parent, &newElement);

	return newElement;
}


element Document::createChild(element *parent, const char *tag, const char *innerHtml, attr *attributes, int attributeCount)
{
	element newElement;

	newElement.tag = (char *)tag;
	newElement.closureType = false;
	newElement.innerHTML = (char *)innerHtml;
	newElement.containsInnerHTML = true;
	newElement.attributes = attributes;
	newElement.attributeCount = attributeCount;
	newElement.maxAttributeCount = attributeCount;
	appendChild(parent, &newElement);

	return newElement;
}


element Document::createChild(element *parent, const char *tag, const char *innerHtml)
{
	element newElement;

	newElement.tag = (char *)tag;
	newElement.innerHTML = (char *)innerHtml;
	newElement.containsInnerHTML = true;
	newElement.closureType = false;
	appendChild(parent, &newElement);

	return newElement;

}

std::string Document::getDocumentString()
{
	return getElementString(root,std::string(""));
}

std::string Document::getElementString(element e, std::string prepend)
{
	std::string ret(prepend);
	std::string pass(prepend);
	pass = pass.append("\t");

	ret = ret.append("<").append(e.tag);

	for(int i = 0; i < e.attributeCount; i++)
		ret = ret.append(" ").append(e.attributes[i].name).append("=\"").append(e.attributes[i].value).append("\"");

	if(e.closureType)
	{
		ret = ret.append(" />");
		return ret;
	}
	ret = ret.append(">");
	if(e.containsInnerHTML)
	{
		//printf("\n[debug]: %c, %c, %d\n",e.innerHTML[0],'\n',e.innerHTML[0]-'\n');
		if(e.innerHTML[0] == '\n')
			ret = ret.append("\n").append(pass).append(e.innerHTML+1).append("\n").append(prepend);
		else
			ret = ret.append(e.innerHTML);
		//ret = ret.append(pass).append("\n\t<p>implementlater</p>\n");
	}

	for(int i = 0; i < e.childCount; i++)
		ret = ret.append("\n").append(getElementString(*e.children[i],pass));
	if(e.childCount != 0 && !e.containsInnerHTML)
		ret = ret.append("\n").append(prepend);

	ret = ret.append("</").append(e.tag).append(">");

	return ret;
}







