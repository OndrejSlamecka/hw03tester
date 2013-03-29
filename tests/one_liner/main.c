#include "html.h"

int main(void)
{
	element* html = readDocument();
	printDocument(html);
	deleteElement(html);

	return 0;
}
