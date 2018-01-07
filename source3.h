#ifndef __source3_H__
#define __source3_H__
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;
class Triehard // compressed decimal trie
// constructor should make 1-10 base nodes that are empty for search to work
// magnitude is 1 for length 1, so it must be >= 1
// no more flag, instead we have a count field which counts the number of instances
// the node represents. A small change, but much more functionality
{
	private:
	
		class Trienode
		{
			private:
				
				int magnitude;
				int count;
				vector<Trienode *> children(10);
				
			public:
			
				Trienode(int magnitude, int count):
				magnitude{magnitude}, count{count}
				{
					for (int i = 0; i < 10; ++i)
					{
						children[i] = nullptr;
					}
				}
				
				~Trienode()
				{
					for (int i = 0; i < 10; ++i)
					{
						delete children[i];
					}
				}
			
				int getMag()
				{
					return magnitude;
				}

				int getCount()
				{
					return count;
				}
				
				Trienode * getX(int x)
				{
					return children[x];
				}
				
				void addMag()
				{
					++magnitude;
				}
				
				void subMag()
				{
					--magnitude;
				}
				
				void addCount()
				{
					++count;
				}
				
				void subCount()
				{
					--count;
				}
				
				void zeroCount()
				{
					count = 0;
				}
				
				void setCount(int x)
				{
					count = x;
				}
				
				Trienode * setX(int x, int mag, int cnt)
				{
					children[x] = new Trienode(mag, cnt);
					return children[x];
				}
				
				void copyX(int x, Trienode * node)
				{
					children[x] = node;
				}
				
				bool isLeaf()
				{
					for (int i = 0; i < 10; ++i)
					{
						if (children[i]) return false;
					}
					
					return true;
				}
				
				int sumMag()
				{
					int result = magnitude;
					
					for (int i = 0; i < 10; ++i)
					{
						if (children[i]) result += children[i]->sumMag();
					}
					
					return result;
				}
    
    			int sumCount()
    			{
    				int result = 1;
					
					for (int i = 0; i < 10; ++i)
					{
						if (children[i]) result += children[i]->sumCount();
					}
					
					return result;
    			}
		};
		
		vector<Trienode *> nodes(10);
	
	public:
	
		Triehard() // Initializes both sides as empty, but makes it searchable, mutatable
		{
			for (int i = 0; i < 10; ++i)
			{
				nodes[i] = nullptr;
			}
		}
		
		~Triehard() // Same concern (syntax) as nodes, don't forget to write an erase method as well, maybe an empty/wipe
		{
			for (int i = 0; i < 10; ++i)
			{
				delete nodes[i];
			}
		}
		
		// build an array of what is "processed" so far. then when a flag is hit, print that array.
		void mainPrint(Trienode * curnode, vector<int> * chars, int val)
		{
			if (!curnode) return;
			int curmag = curnode->getMag();
			int curcount = curnode->getCount();
			
			while (curmag)
			{
				chars->push_back(val);
				--curmag;
			}
			
			while (curcount)
			{
				int len = chars->size();
				
				for (int i = 0; i < len; i++)
				{
					cout << (*chars)[i] << " ";
				}
				cout << endl;
				--curcount;
			}
			
			for (int i = 0; i < 10; ++i)
			{
				mainPrint(children[i], chars, i)
			}
			curmag = curnode->getMag();
			
			while (curmag)
			{
				chars->pop_back();
				--curmag;
			}
		}
		
		void myPrintIsBetterThanYoursLogan()
		{
			for (int i = 0; i < 10; ++i)
			{
				vector<int> * chars = new vector<int>();
				mainPrint(nodes[i], chars, i);
				delete side;
			}
		}
		
		int search(vector<int> * val) // val is the string
		{
			Trienode * curnode = nodes[(*val)[0]];
			int pos = (*val)[0]; // represents what value your current node is
			int curmag = curnode->getMag();
			
			for (int i = 0; i < val->size(); i++) // each iteration checks the current character for accuracy.
			{
				if ((*val)[i] == pos) // if we are on the correct node already
				{
					if (curmag) // if your current magnitude is >= 1 (still info "left" in this node)
					{
						--curmag;
					}
					else if (curnode->getX(pos)) // if our current node is exhausted, move on to the next one
					{
						curnode = curnode->getX(pos);
						curmag = curnode->getMag() - 1;
					}
					else
					{
						return 0;
					}
				}
				else // we are not on the right node
				{
					if (curmag) // if we have magnitude left
					{
						return 0;
					}
					else if (curnode->getX(pos)) // if our child for that # exists
					{
						curnode = curnode->getX(pos);
						curmag = curnode->getMag() - 1;
					}
					else // we don't have the child, must be absent
					{
						return 0;
					}
				}
			}
			
			if (!curmag)
			{
				return curnode->getCount();
			}
			
			return 0;
		}
		
		void insert(vector<int> * val) // assumes valid input
		{
			Trienode * curnode = nodes[(*val)[0]];
			int pos = (*val)[0]; // represents what value your current node is
			int curmag = curnode->getMag(); // "remaining" magnitude of the current node
			
			for (int i = 0; i < val->size(); i++) // each iteration validates against curnode for position i
			{
				if ((*val)[i] == pos) // curnode matches current value
				{
					if (curmag) // curnode has magnitude left, just sub1 and continue
					{
						--curmag;
					}
					else if (curnode->getX(pos)) // curnode is exhausted, but we have the same child with mag >=1, so use that
					{
						curnode = curnode->getX(pos);
						curmag = curnode->getMag() - 1;
					}
					else if (!(curnode->getCount()) && curnode->isLeaf()) // we aren't flagged and are a leaf, so add mag
					{
						curnode->addMag();
					}
					else
					{
						curnode = curnode->setX(pos, 1, 0) // we must create a child with mag1, curmag is 0 so no change
					}
				}
				else // curnode is not the same digit as val[i]
				{
					if (curmag) // this means we are going to have to decompress
					{
						Trienode * newnode = new Trienode(0, curnode->getCount()); // this'll be the second half of curnode-
						curnode->zeroCount; // newnode should be flagged (if curnode was), not curnode
						
						while (curmag) // put extra magnitude into newnode
						{
							curnode->subMag();
							--curmag;
							newnode->addMag();
						}
						
						for (int i = 0; i < 10; i++) // move children to newnode
						{
							newnode->copyX(i, curnode->getX(i));
							curnode->copyX(i, nullptr);
						}
						
						curnode->copyX(pos, newnode); // put newnode in its place
						curnode = curnode->setX((*val)[i], 1, 0); // insert new node for the string being inserted
						curmag = curnode->getMag() - 1; // reset curmag
						pos = (*val)[i]; // update pos
					}
					else if (curnode->getX((*val)[i])) // we have a child of the correct val
					{
						pos = (*val)[i];
						curnode = curnode->getX(pos);
						curmag = curnode->getMag() - 1;
					}
					else // insert a child, curmag is still 0
					{
						pos = (*val)[i];
						curnode = curnode->setX(pos, 1, 0)'
					}
				}
			}
			
			// at this point, the node we are at needs to be flagged. However, there is an issue: this node may have magnitude remaining
			// if this is the case, we need to split it up at curnode->getMag() - curmag. lets check for the easy case, then proceed
			// with that logic if necessary
			// basically curmag is our "extra" magnitude that needs to be sent along
			if (!curmag)
			{
				curnode->addCount();
			}
			else
			{
				Trienode * newnode = new Trienode(0, curnode->getCount()); // this is our new node, which should retain old flagging
				curnode->setCount(1); // curnode will now end where we want to insert, so this should be true
				
				while (curmag) // fills newnode with the extra magnitude
				{
					curnode->subMag();
					--curmag;
					newnode->addMag();
				}
				
				for (int i = 0; i < 10; i++) // move children to newnode
				{
					newnode->copyX(i, curnode->getX(i));
					curnode->copyX(i, nullptr);
				}
				
				curnode->copyX(pos, newnode); // ensure newnode is actually linked to curnode
			}
		}
		
		void cut(vector<int> * val) // this is delete because i can't use delete :(
		// NOT DONE AT ALL!!!!
		{
			Trienode * curnode;
			Trienode * prevnode = nullptr;
			int pos; // represents the represented value of curnode (0-9)
			int pos2; // previous node's side
			side = (*val)[i];
			side2 = side;
			curnode = nodes[side];
			int curmag = curnode->getMag();
			
			for (int i = 0; i < val->size(); i++) // each iteration checks the current character for accuracy.
			{
				if ((*val)[i] == pos) // curnode matches current value
				{
					if (curmag) // we have mag left
					{
						--curmag;
						pos2 = pos;
					}
					else if (curnode->getX(pos)) // if we have the correct child
					{
						prevnode = curnode;
						curnode = curnode->getX(pos);
						curmag = curnode->getMag() - 1;
						pos2 = pos;
					}
					else
					{
						return; // node does not exist, will make this an error later
					}
				}
				else // curnode does NOT match current value
				{
					if (curmag)
					{
						return; // should be error later, but the val isn't inserted, since there is mag left in the wrong number
					}
					else if (curnode->getX((*val)[i])) // if we have the correct child
					{
						pos2 = pos;
						pos = (*val)[i];
						prevnode = curnode;
						curnode = curnode->getX((*val)[i]);
						curmag = curnode->getMag();
					}
					else
					{
						return; // we don't have the right child, so return (to be error)
					}
				}
			}
			
			// at this point, we have curnode being the "end" of our value
			if (!(prevnode)) // if we are deleting one of the 2 base trees
			{
				if (nodes[pos]->getCount()) nodes[pos]->subCount();
				else return; // later throw error for removing nothing
			}
			
			if (curnode->getCount()) curnode->subCount(); // Normally this is all that is necessary
			else return; // later throw error for removing nothing
			if (curnode->getCount()) return; // This means we aren't removing a node, so no compression is possible
			
			// Cases where nodes have to be removed/compressed
			// THIS NEEDS A LOT OF WORK!!!
			if (!(curnode->getLeft()) && !(curnode->getRight())) // if our node has no children, destroy it and change parent's reference to NULL
			{
				if (side)
				{
					delete curnode;
					prevnode->copyRight(nullptr);
				}
				else
				{
					delete curnode;
					prevnode->copyLeft(nullptr);
				}
			}
			else if (side && curnode->getLeft() && prevnode->getLeft() && side2 && !(prevnode->getCount()) && !(prevnode->getLeft()))
			// we are on the right, we have shit to the left, and the parent has nothing to the left, and is not flagged
			// this is a rare case where we do have to compress
			{
				while (curnode->getMag()) // Change mag to parent
					{
						curnode->subMag();
						prevnode->addMag();
					}
					
					prevnode->copyLeft(curnode->getLeft()); // Move left side up, delete old data
					curnode->copyLeft(nullptr);
					prevnode->copyRight(nullptr);
					delete curnode;
			}
			else if (!(side) && curnode->getRight() && prevnode->getRight() && !(side2) && !(prevnode->getCount()) && !(prevnode->getRight()))
			// we are on the left, we have shit to the right, and the parent has nothing to the right, and is not flagged
			// the same rare case as above
			{
				while (curnode->getMag()) // Change mag to parent
					{
						curnode->subMag();
						prevnode->addMag();
					}
					
					prevnode->copyRight(curnode->getRight()); // Move left side up, delete old data
					curnode->copyRight(nullptr);
					prevnode->copyLeft(nullptr);
					delete curnode;
			}
			else if (side) // we are on the right and have shit to the right
			{
				Trienode * child = curnode->getRight();
				while (child->getMag()) // moves magnitude from child to parent we are removing
				{
					child->subMag();
					curnode->addMag();
				}
				
				curnode->setCount(child->getCount()); // Sets count to child's count
				
				curnode->copyLeft(child->getLeft()); // moves child's children to our parent node
				curnode->copyRight(child->getRight());
				child->copyLeft(nullptr); // Change child's children to null to allow for safe deletion
				child->copyRight(nullptr);
				delete child;
			}
			else // we are on the left and have shit to the left
			{
				Trienode * child = curnode->getLeft();
				while (child->getMag()) // moves magnitude from child to parent we are removing
				{
					child->subMag();
					curnode->addMag();
				}
				
				curnode->setCount(child->getCount()); // Sets count to child's count
				
				curnode->copyLeft(child->getLeft()); // moves child's children to our parent node
				curnode->copyRight(child->getRight());
				child->copyLeft(nullptr); // Change child's children to null to allow for safe deletion
				child->copyRight(nullptr);
				delete child;
			}
		}
    
    // update counter with children recursively
	void mainCount(Trienode * curnode, int len, int right, int * counter)
	{
		if (!curnode) return;
		len += curnode->getMag();
		*counter += (len * curnode->getCount());
		mainCount(curnode->getLeft(), len, 0, counter);
		mainCount(curnode->getRight(), len, 1, counter);
	}
		
	int countChars() // returns total word length of trie
	{
		int counter = 0;
		if (left) mainCount(left, 0, 0, &counter);
		if (right) mainCount(right, 0, 1, &counter);
		return counter;
	}
    
    float compressionovertrie() // returns nodes / nodes in a normal trie
	{
		float total = left->sumMag() + right->sumMag();
		float compressed = left->sumCount() + right->sumCount();
		return roundf(compressed/total * 100) / 100;
	}
    
    float compressionoverdict() // returns nodes / sum of all word length
    {
    	float compressed = left->sumCount() + right->sumCount();
    	float total = countChars();
    	return roundf(compressed/total * 100) / 100;
    }
};

#endif