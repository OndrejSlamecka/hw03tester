#include "html.h"
 
int main(void)
{
	element* html = readDocument();
 
	element *clone = cloneNode(html->lastChild->firstChild, true);
	appendChild(html->lastChild, clone);
 
	element *clone2 = cloneNode(html->lastChild->firstChild, true);
	appendChild(html->lastChild, clone2);

	element *removedChild = removeChild(clone, clone->lastChild); 
	deleteElement(removedChild);
 
	printDocument(html);
	deleteElement(html);
 
	return 0;
}
