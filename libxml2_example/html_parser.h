#ifndef HTMLPARSER_H
#define HTMLPARSER_H

#include <string>
#include <libxml/HTMLparser.h>
#include <libxml/xpath.h>

class HtmlParser
{
public:
  // No-argument constructor
  HtmlParser();

  // Destructor
  ~HtmlParser();

  // Delete the copy constructor
  HtmlParser(const HtmlParser &) = delete;

  // Delete the copy assignment operator
  HtmlParser &operator=(const HtmlParser &) = delete;

  // Optionally, if you want to also prevent moving of the object, uncomment these:
  // HtmlParser(HtmlParser&&) = delete;
  // HtmlParser& operator=(HtmlParser&&) = delete;
  
  void loadDocument(const std::string* const);

private:
  htmlDocPtr doc;
  xmlXPathContextPtr xpathCtx;
  xmlXPathObjectPtr xpathObj;
};

#endif // HTMLPARSER_H
