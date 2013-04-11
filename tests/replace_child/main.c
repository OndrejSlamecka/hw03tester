#include "html.h"

int main(void)
{
	element* html = readDocument();

	element *dummy1 = html->lastChild->firstChild;
	element *node, *nodeChild, *replaced;

	/**/
	node = createElement("replace1", NULL);
	nodeChild = createElement("b", "Text1");
	appendChild(node, nodeChild);

	replaced = replaceChild(html->lastChild, node, dummy1);
	deleteElement(dummy1);

	/**/
	node = createElement("replace2", NULL);
	nodeChild = createElement("b", "Text2");
	appendChild(node, nodeChild);

	replaced = replaceChild(html->lastChild, node, html->lastChild->firstChild->nextSibling);
	deleteElement(replaced);

	/**/
	node = createElement("replace3", NULL);
	nodeChild = createElement("b", "Text3");
	appendChild(node, nodeChild);

	replaced = replaceChild(html->lastChild, node, html->lastChild->lastChild);
	deleteElement(replaced);



	printDocument(html);
	deleteElement(html);

	return 0;
}
