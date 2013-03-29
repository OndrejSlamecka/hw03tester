#include "html.h"

int main(void)
{
	element* html = readDocument();

	element *clone = cloneNode(html->lastChild->firstChild, true);
	appendChild(html->lastChild, clone);

	printDocument(html);
	deleteElement(html);

	return 0;
}

