#include "html.h"
#include "stdio.h"

/*
Input:
<!DOCTYPE html><html><head><title></title></head><body></body></html>
*/

#define assert(message, test) do { if (!(test)){ fprintf(stderr, "ERROR: %s\n", message); return 1; }} while (0)

int main(void)
{
	element *html = readDocument();

	// createElement
	element *t1 = createElement("t1", "Text node");

	assert("createElement - empty pointers - parentNode", t1->parentNode == NULL);
	assert("createElement - empty pointers - nextSibling", t1->nextSibling == NULL);
	assert("createElement - empty pointers - previousSibling", t1->previousSibling == NULL);
	assert("createElement - empty pointers - firstChild", t1->firstChild == NULL);
	assert("createElement - empty pointers - lastChild", t1->lastChild == NULL);


	// appendChild
	appendChild(html->lastChild, t1);

	assert("Append child test - parent pointer", t1->parentNode == html->lastChild);

	assert("Append only child test - previousSibling pointer", t1->previousSibling == NULL);
	assert("Append only child test - nextSibling pointer", t1->nextSibling == NULL);

	element *t2 = createElement("t2", NULL);
	appendChild(html->lastChild, t2);

	assert("Append second child test - previousSibling pointer to the first child", t2->previousSibling == html->lastChild->firstChild);
	assert("Append second child test - nextSibling pointer to NULL", t2->nextSibling == NULL);

	element *t3 = createElement("t3", NULL);
	appendChild(html->lastChild, t3);

	assert("Append third child test - second child nextSibling pointer equals to the pointer to the last child", t2->nextSibling == html->lastChild->lastChild);

	// replaceChild
	element *r2 = createElement("r2", NULL);
	replaceChild(html->lastChild, r2, html->lastChild->firstChild->nextSibling);

	assert("Replace child in the middle - parent", r2->parentNode == html->lastChild);
	assert("Replace child in the middle - prevSibling", r2->previousSibling == html->lastChild->firstChild);
	assert("Replace child in the middle - nextSibling", r2->nextSibling == html->lastChild->lastChild);

	element *r3 = createElement("r3", NULL);
	replaceChild(html->lastChild, r3, html->lastChild->lastChild);

	assert("Replace last child - prevSibling", (r3->previousSibling == html->lastChild->firstChild->nextSibling) && (r3->previousSibling == r2));
	assert("Replace last child - nextSibling", r3->nextSibling == NULL);

	element *r1 = createElement("r1", NULL);
	replaceChild(html->lastChild, r1, html->lastChild->firstChild);

	assert("Replace first child - prevSibling", r1->previousSibling == NULL);
	assert("Replace first child - nextSibling", r1->nextSibling == r2);

	// removeChild
	removeChild(html->lastChild, r1);
	assert("Remove child - first child removed", html->lastChild->firstChild == r2);

	removeChild(html->lastChild, r3);
	assert("Remove child - last (not least) child is removed", html->lastChild->lastChild == r2);
	assert("Remove child - last (not least) child is removed - siblings check for the remaining child", r2->previousSibling == NULL && r2->nextSibling == NULL);

	removeChild(r2->parentNode, r2);
	assert("Remove child - body is empty", html->lastChild->firstChild == NULL && html->lastChild->lastChild == NULL);

	appendChild(html->lastChild, r1);
	appendChild(html->lastChild, r2);
	appendChild(html->lastChild, r3);

	removeChild(r2->parentNode, r2);
	assert("Remove the middle child - relation between first and last",
			html->lastChild->firstChild->nextSibling == html->lastChild->lastChild &&
			html->lastChild->firstChild == html->lastChild->lastChild->previousSibling);

	removeChild(html->lastChild, r1);
	removeChild(html->lastChild, r3);

	// insertBefore
	appendChild(html->lastChild, r3);

	insertBefore(html->lastChild, r2, r3);
	assert("insertBefore - new firstChild", html->lastChild->firstChild == r2);
	assert("insertBefore - lastChild kept", html->lastChild->lastChild == r3);
	assert("insertBefore - parentNode set", html->lastChild == r2->parentNode);

	insertBefore(html->lastChild, r1, r3);
	assert("insertBefore - siblings", r1->previousSibling == r2 && r1->nextSibling == r3);

	removeChild(html->lastChild, r1);
	removeChild(html->lastChild, r2);
	removeChild(html->lastChild, r3);

	// cloneNode
	appendChild(r2, t1);
	appendChild(t1, t2);
	appendChild(r2, t3);

	element *c0 = cloneNode(t2, false);
	insertBefore(r2, c0, t3);

	element *c1 = cloneNode(r2, true);
	element *c2 = cloneNode(r2, false);
	appendChild(html->lastChild, c1);
	appendChild(html->lastChild, c2);

	element *c3 = cloneNode(r3, true); // r3
	insertBefore(html->lastChild, c3, c1);

	// Now it should be in order: r3, r2 deep, r2

	assert("Clone - first r2 is deep", html->lastChild->firstChild->nextSibling->firstChild->firstChild != NULL // html body r2 t1 t2
			&& html->lastChild->firstChild->nextSibling->lastChild != NULL); // html body r2 t3

	deleteElement(r1);
	//deleteElement(r2);
	deleteElement(r3);

	deleteElement(html);

	return 0;
}

