//MAITRI SHASTRI
//2014B2A70220P

struct trienode
{
	struct trienode *child[27];
	//to account for underscore character
	int isleaf;
	//1 if it is a leaf node
	int count;
	//no of children

	int val;
	//return keyword tkid if present
};