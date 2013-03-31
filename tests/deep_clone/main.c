#include "html.h"
 
int main(void)
{
	element* html = readDocument();
 
	element *clone = cloneNode(html->lastChild->firstChild, true);
	appendChild(html->lastChild, clone);
 
	element *clone2 = cloneNode(html->lastChild->firstChild, true);
	appendChild(html->lastChild, clone2);

	removeChild(clone, clone->lastChild); 
	deleteElement(clone->lastChild);
 
	printDocument(html);
	deleteElement(html);
 
	return 0;
}
