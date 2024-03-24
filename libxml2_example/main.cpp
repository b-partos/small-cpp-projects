#include <iostream>
#include <libxml/HTMLparser.h>
#include <libxml/xpath.h>

int main()
{
  std::string htmlFilePath{"Oxygen_Wikipedia.htm"};
  const xmlChar *xpathExpr = BAD_CAST "/html/body/div[2]/div/div[3]/main/div[3]/div[3]/div[1]/div[24]/ul/li[5]/a";

  htmlDocPtr doc;
  xmlXPathContextPtr xpathCtx;
  xmlXPathObjectPtr xpathObj;

  // Initialize libxml
  xmlInitParser();
  LIBXML_TEST_VERSION


  // Load HTML document
  doc = htmlReadFile(htmlFilePath.c_str(), NULL, HTML_PARSE_RECOVER | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING);

  // Create XPath evaluation context
  xpathCtx = xmlXPathNewContext(doc);
  if (xpathCtx == NULL)
  {
    std::cerr << "Error: unable to create new XPath context" << std::endl;
    xmlFreeDoc(doc);
    xmlCleanupParser();
    return 1;
  }

  // Evaluate XPath expression
  xpathObj = xmlXPathEvalExpression(xpathExpr, xpathCtx);
  if (xpathObj == NULL)
  {
    std::cerr << "Error: unable to evaluate xpath expression" << std::endl;
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);
    xmlCleanupParser();
    return 1;
  }

  // Navigate through results
  xmlNodeSetPtr nodes = xpathObj->nodesetval;
  if (nodes->nodeNr > 0)
  {
    xmlNodePtr node = nodes->nodeTab[0]; // Assuming first matching node is the target
    if (node != NULL)
    {
      xmlChar *href = xmlGetProp(node, (const xmlChar *)"href");
      if (href != NULL)
      {
        std::cout << "Found href: " << href << std::endl;
        xmlFree(href);
      }
    }
  }
  else
  {
    std::cout << "No result found for the XPath query." << std::endl;
  }

  // Cleanup
  xmlXPathFreeObject(xpathObj);
  xmlXPathFreeContext(xpathCtx);
  xmlFreeDoc(doc);
  xmlCleanupParser();

  return 0;
}