#include "html.h"

int main(void)
{
	element* html = readDocument();

	element *node = createElement("test", "");
	element *nodeChild = createElement("p", "Random text");
	appendChild(node, nodeChild);

	element *replaced = replaceChild(html->lastChild, node, html->lastChild->firstChild);

	appendChild(html->firstChild, replaced);

	printDocument(html);
	deleteElement(html);

	return 0;
}
