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
			
			for (int i = 0; i < val->size(); i++) // each iteration checks the current character for accuracy. it does not prepare for the next character like the preamble
			{
				if ((*val)[i] == pos) // if we are on the correct node already
				{
					if (curmag) // if your current magnitude is >= 1 (still info "left" in this node)
					{
						--curmag;
						continue;
					}
					
					if (curnode->getX(pos)) // if our current node is exhausted, move on to the next one
					{
						curnode = curnode->getX(pos);
						curmag = curnode->getMag() - 1;
						continue;
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
						continue;
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
		
		// START WORK HERE
		void insert(vector<int> * val) // assumes valid input
		{
			Trienode * curnode; // the node we are checking against our current value
			bool side; // represents if you are on the left or right (right being true)
			if ((*val)[0])
			{
				curnode = right;
				side = true;
			}
			else
			{
				curnode  = left;
				side = false;
			}
			
			int curmag = curnode->getMag(); // "remaining" magnitude of the current node
			
			for (int i = 0; i < val->size(); i++)
			{
				if ((*val)[i]) // if current digit is 1
				{
					if (side) // if you're on the right
					{
						if (curmag) // if your current magnitude is >= 1 (still info "left" in this node)
						{
							--curmag;
							continue;
						}
						else if (curnode->getRight()) // If current node is "exhausted", move on to next one
						{
							curnode = curnode->getRight();
							curmag = curnode->getMag() - 1;
							continue;
						}
						else if (!(curnode->getLeft()) && !(curnode->getCount())) // if there are no subtrees, just increase this node's magnitude
						// also can't do that if the node is flagged, since it needs to retain that info, so check for this
						{
							curnode->addMag();
							continue;
						}
						else // we're on a "1" node, but it is depleted, and there is a left subtree. so, we create a new node to the right to represent this bit
						// also works if the node is flagged and we just need a new node to represent the unflagged set of 1s
						{
							curnode = curnode->setRight(1, 0);
							continue;
						}
						
					}
					else // we're on a left subtree, but have a 1 coming up
					{
						if (curmag) // this means we have a value here, so we need to split this node up, branching to the right will be handled by following code
						{
							Trienode * newnode = new Trienode(0, curnode->getCount()); // this will be the second half of the big node
							curnode->zeroCount(); // this and the passing of the count into newnode ensure count is not lost
							
							while (curmag) // fills newnode with the extra magnitude
							{
								curnode->subMag();
								--curmag;
								newnode->addMag();
							}
							
							newnode->copyLeft(curnode->getLeft()); // move the children to the bottom half
							newnode->copyRight(curnode->getRight());
							curnode->copyLeft(newnode); // put new node at left of curnode
							curnode->copyRight(nullptr); // nothing is in the right yet
							goto SKIP1; // skip next if check since we know new right is NULL
						}
						
						if (curnode->getRight()) // we can and should move to the right. once there, we sub 1 from magnitude and move on.
						{
							curnode = curnode->getRight();
							curmag = curnode->getMag() - 1;
							side = true;
							continue;
						}
						else // we are on left, it is empty, and the right side is empty. create and set that node to curnode->
						{
							SKIP1:
							curnode = curnode->setRight(1, 0);
							side = true;
							continue;
						}
					}
				}
				else // next digit is a 0
				{
					if (!side) // on a left subtree
					{
						if (curmag) // still have 0s "remaining" at this node
						{
							--curmag;
							continue;
						}
						else if (curnode->getLeft()) // no 0s remaining, but there is a left subtree
						{
							curnode = curnode->getLeft();
							curmag = curnode->getMag() - 1;
							continue;
						}
						else if (!(curnode->getRight()) && !(curnode->getCount())) // no subtrees and we're on the correct side, so add to this node's magnitude
						// only if this node isn't flagged, since we must retain that info
						{
							curnode->addMag();
							continue;
						}
						else // no 0s remaining || we are flagged, no left subtree, and we are going to add one.
						{
							curnode = curnode->setLeft(1, 0);
							continue;
						}
					}
					else // we're on a right subtree but have a 0 coming up
					{
						if (curmag) // this means we have a value here, so we need to split this node up and branch to the left before this point
						{
							Trienode * newnode = new Trienode(0, curnode->getCount()); // this will be the second half of the big node
							curnode->zeroCount(); // This and the passing of getCount to newnode ensure count is not lost
							
							while (curmag) // fills newnode with the extra magnitude
							{
								curnode->subMag();
								--curmag;
								newnode->addMag();
							}
							
							newnode->copyLeft(curnode->getLeft()); // move the children to the bottom half
							newnode->copyRight(curnode->getRight());
							curnode->copyLeft(nullptr); // nothing is in the left yet
							curnode->copyRight(newnode); // put new node at right of curnode
							goto SKIP2; // skip next if check since we know new left is NULL
						}
						
						if (curnode->getLeft()) // we can and should move to the left. once there, we sub 1 from magnitude and move on.
						{
							curnode = curnode->getLeft();
							curmag = curnode->getMag() - 1;
							side = false;
							continue;
						}
						else // we are on right, it is empty, and the left side is empty. create and set that node to curnode->
						{
							SKIP2:
							curnode = curnode->setLeft(1, 0);
							side = false;
							continue;
						}
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
				
				// now we create the newnode on the appropriate side
				newnode->copyLeft(curnode->getLeft());
				newnode->copyRight(curnode->getRight());
				
				if (side)
				{
					curnode->copyLeft(nullptr);
					curnode->copyRight(newnode);
				}
				else
				{
					curnode->copyLeft(newnode);
					curnode->copyRight(nullptr);
				}
			}
		}
		
		void cut(vector<int> * val) // this is delete because i can't use delete :(
		{
			Trienode * curnode;
			Trienode * prevnode = nullptr;
			bool side; // represents if you are on the left or right (right being true)
			bool side2; // previous node's side
			if ((*val)[0])
			{
				curnode = right;
				side = true;
				side2 = true;
			}
			else
			{
				curnode  = left;
				side = false;
				side2 = false;
			}
			
			int curmag = curnode->getMag();
			
			for (int i = 0; i < val->size(); i++) // each iteration checks the current character for accuracy. it does not prepare for the next character like the preamble
			{
				if ((*val)[i]) // if next digit is 1
				{
					if (side) // if you're on the right
					{
						if (curmag) // if your current magnitude is >= 1 (still info "left" in this node)
						{
							--curmag;
							side2 = side;
							continue;
						}
						
						if (curnode->getRight()) // If current node is "exhausted", move on to next one
						{
							prevnode = curnode;
							curnode = curnode->getRight();
							curmag = curnode->getMag() - 1;
							side2 = side;
							continue;
						}
						else // node doesn't exist
						{
							return;
						}
						
					}
					else
					{
						if (curmag) // node doesn't exist
						{
							return;
						}
						
						if (curnode->getRight())
						{
							prevnode = curnode;
							curnode = curnode->getRight();
							curmag = curnode->getMag() - 1;
							side = true;
							side2 = false;
							continue;
						}
						else // node doesn't exist
						{
							return;
						}
					}
				}
				else
				{
					if (!side)
					{
						if (curmag)
						{
							--curmag;
							side2 = side;
							continue;
						}
						
						if (curnode->getLeft())
						{
							prevnode = curnode;
							curnode = curnode->getLeft();
							curmag = curnode->getMag() - 1;
							side2 = side;
							continue;
						}
						else // node doesn't exist
						{
							return;
						}
					}
					else
					{
						if (curmag) // node doesn't exist
						{
							return;
						}
						
						if (curnode->getLeft())
						{
							prevnode = curnode;
							curnode = curnode->getLeft();
							curmag = curnode->getMag() - 1;
							side = false;
							side2 = true;
							continue;
						}
						else // node doesn't exist
						{
							return;
						}
					}
				}
			}
			
			// at this point, we have curnode being the "end" of our value
			if (!(prevnode)) // if we are deleting one of the 2 base trees
			{
				if (side)
				{
					right->subCount();
				}
				else
				{
					left->subCount();
				}
				
				return;
			}
			
			curnode->subCount(); // Normally this is all that is necessary
			if (curnode->getCount()) return; // This means we aren't removing a node, so no compression is possible
			
			// Cases where nodes have to be removed/compressed
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