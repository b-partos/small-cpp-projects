#include "html_parser.h"

// Constructor
HtmlParser::HtmlParser()
    : doc(), xpathCtx(), xpathObj()
{
  // Constructor body can be empty or contain initialization code
  xmlInitParser();
  LIBXML_TEST_VERSION
}

// Destructor
HtmlParser::~HtmlParser()
{
  // Free resources if they have been allocated
  if (xpathObj)
  {
    xmlXPathFreeObject(xpathObj);
    xpathObj = nullptr;
  }
  if (xpathCtx)
  {
    xmlXPathFreeContext(xpathCtx);
    xpathCtx = nullptr;
  }
  if (doc)
  {
    xmlFreeDoc(doc);
    doc = nullptr;
  }
  xmlCleanupParser(); // Clean up libxml parser. Only call if no other XML parsing will be done
                      // Destructor body can be empty or contain cleanup code
}