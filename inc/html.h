#ifndef DOCU_HTMLEMIT
#define DOCU_HTMLEMIT

#define DOCU_HTML_FIXED 16

#ifndef DOCU_HTML_FIXED
#define DOCU_HTML_DYNAMIC
#endif


//"<... name="value" ...>"
struct attr
{
	char *name;
	char *value;
};

struct element
{
	//"The tag of the HTTP element
	char *tag;

	//"The array containing element attributes"
	attr *attributes;
	unsigned int maxAttributeCount = 0;
	unsigned int attributeCount = 0;

	//"if true: <... />, else <..> ... </..>
	bool closureType = false;

	//"This flags tells the emitter whether to even consider " innerHTML "
	bool containsInnerHTML = false;

	//"this string is what the element encloses
	char *innerHTML;

	//"The parent of this element. Itself if this is root"
	element *parent;

	//"The children of this element
#ifdef DOCU_HTML_FIXED
	element *children[DOCU_HTML_FIXED] = {(element*)0};
	unsigned int maxChildren = DOCU_HTML_FIXED;
#else
	element *children;
	unsigned int maxChildren = 0;
#endif
	unsigned int childCount = 0;
};

#include <string>

class Html;
class Document
{
	public:
		Document();
		Document(element);

		void appendChild(element *, element *);

		element createChild(bool, const char *);
		element createChild(const char *, const char *);
		element createChild(const char *, const char *, attr *, int);
		element createChild(bool, const char *, attr *, int);

		element createChild(element *, bool, const char *);
		element createChild(element *, const char *, const char *);
		element createChild(element *, const char *, const char *, attr *, int);
		element createChild(element *, bool, const char *, attr *, int);

		std::string getDocumentString();
		std::string getElementString(element, std::string);

	private:
		element root;
		friend Html;
};

#include <fstream>

class Html
{
	//public:
		//Html(string);
		//Html(ifstream, string);

	//private:
		//Document document;
};




#endif

