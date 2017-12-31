#ifndef __source1_H__
#define __source1_H__
#include <iostream>
using namespace std;
class Triehard2 // compressed binary trie
// constructor should make a left and right that are empty for search to work
// magnitude is 1 for length 1, so it must be >= 1
// no more flag, instead we have a count field which counts the number of instances
// the node represents. A small change, but much more functionality
{
	private:
	
		class Trienode2
		{
			private:
				
				int magnitude;
				int count;
				Trienode2 * left;
				Trienode2 * right;
				
				/*
				//Convenient method for printing.
				//Returns a string to be able to chain
				//printing more easily.
				//Side is either 0 (left), or 1 (right)
				string getNodeVal(int side)
				{
					string output = "";
					
					for(int i = 0; i < magnitude; ++i)
					{
						output += to_string(side);
					}
					
					return output;
				}*/
				
			public:
			
				Trienode2(int magnitude, int count):
				magnitude{magnitude}, count{count}
				{
					left = nullptr;
					right = nullptr;
				}
				
				~Trienode2()
				{
					delete left;
					delete right;
				}
			
				int getMag()
				{
					return magnitude;
				}

				int getCount()
				{
					return count;
				}
				
				/*
				//Side is 0 (left) or 1 (right)
				void print(int side, string output = "")
				{
					string val = getNodeVal(side);
					
					if(getCount())
					{
						cout << output + val << endl;
					}
					if(left != nullptr)
					{
						left->print(0, output + val);
					}
					if(right != nullptr)
					{
						right->print(1, output + val);
					}
				}*/
				
				Trienode2 * getLeft()
				{
					return left;
				}
				
				Trienode2 * getRight()
				{
					return right;
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
				
				Trienode2 * setLeft(int mag, int cnt)
				{
					left = new Trienode2(mag, cnt);
					return left;
				}
				
				Trienode2 * setRight(int mag, int cnt)
				{
					right = new Trienode2(mag, cnt);
					return right;
				}
				
				void copyLeft(Trienode2 * node)
				{
					left = node;
				}
				
				void copyRight(Trienode2 * node)
				{
					right = node;
				}
		};
		
		Trienode2 * left;
		Trienode2 * right;
	
	public:
	
		Triehard2() // Initializes both sides as empty, but makes it searchable, mutatable
		{
			left = new Trienode2(0, 0);
			right = new Trienode2(0, 0);
		}
		
		~Triehard2() // Same concern (syntax) as nodes, don't forget to write an erase method as well, maybe an empty/wipe
		{
			delete left;
			delete right;
		}
		
		/*
		void print()
		{
			//Default param arg seems to be a bit different
			//than i thought. Leaving it in the node print
			//function, try to fix later perhaps?
			if(left != nullptr)left->print(0);
			if(right != nullptr)right->print(1);
		}*/
		
		// build an array of what is "processed" so far. then when a flag is hit, print that array.
		void mainPrint(Trienode * curnode, vector<int> * chars, int right)
		{
			if (!curnode) return;
			int curmag = curnode->getMag();
			int curcount = curnode->getCount();
			
			while (curmag)
			{
				chars->push_back(right);
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
			
			mainPrint(curnode->getLeft(), chars, 0);
			mainPrint(curnode->getRight(), chars, 1);
			curmag = curnode->getMag();
			
			while (curmag)
			{
				chars->pop_back();
				--curmag;
			}
		}
		
		void myPrintIsBetterThanYoursLogan()
		{
			vector<int> * side1 = new vector<int>();
			vector<int> * side2 = new vector<int>();
			
			mainPrint(left, side1, 0);
			mainPrint(right, side2, 1);
			delete side1;
			delete side2;
		}
		
		int search(int * val, int len) // val is the string, len is its length
		{
			Trienode2 * curnode;
			bool side; // represents if you are on the left or right (right being true)
			if (val[0])
			{
				curnode = right;
				side = true;
			}
			else
			{
				curnode  = left;
				side = false;
			}
			
			int curmag = curnode->getMag();
			
			for (int i = 0; i < len; i++) // each iteration checks the current character for accuracy. it does not prepare for the next character like the preamble
			{
				if (val[i]) // if next digit is 1
				{
					if (side) // if you're on the right
					{
						if (curmag) // if your current magnitude is >= 1 (still info "left" in this node)
						{
							--curmag;
							continue;
						}
						
						if (curnode->getRight()) // If current node is "exhausted", move on to next one
						{
							curnode = curnode->getRight();
							curmag = curnode->getMag() - 1;
							continue;
						}
						else
						{
							return 0;
						}
						
					}
					else
					{
						if (curmag)
						{
							return 0;
						}
						
						if (curnode->getRight())
						{
							curnode = curnode->getRight();
							curmag = curnode->getMag() - 1;
							side = true;
							continue;
						}
						else
						{
							return 0;
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
							continue;
						}
						
						if (curnode->getLeft())
						{
							curnode = curnode->getLeft();
							curmag = curnode->getMag() - 1;
							continue;
						}
						else
						{
							return 0;
						}
					}
					else
					{
						if (curmag)
						{
							return 0;
						}
						
						if (curnode->getLeft())
						{
							curnode = curnode->getLeft();
							curmag = curnode->getMag() - 1;
							side = false;
							continue;
						}
						else
						{
							return 0;
						}
					}
				}
			}
			
			return curnode->getCount();
		}
		
		void insert(int * val, int len) // assumes valid input
		{
			Trienode2 * curnode; // the node we are checking against our current value
			bool side; // represents if you are on the left or right (right being true)
			if (val[0])
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
			
			for (int i = 0; i < len; i++)
			{
				if (val[i]) // if current digit is 1
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
							Trienode2 * newnode = new Trienode2(0, curnode->getCount()); // this will be the second half of the big node
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
							Trienode2 * newnode = new Trienode2(0, curnode->getCount()); // this will be the second half of the big node
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
		
		void cut(int * val, int len) // this is delete because i can't use delete :(
		{
			Trienode2 * curnode;
			Trienode2 * prevnode = nullptr;
			bool side; // represents if you are on the left or right (right being true)
			bool side2; // previous node's side
			if (val[0])
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
			
			for (int i = 0; i < len; i++) // each iteration checks the current character for accuracy. it does not prepare for the next character like the preamble
			{
				if (val[i]) // if next digit is 1
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
			if (curnode->getCount) return; // This means we aren't removing a node, so no compression is possible
			
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
				Trienode2 * child = curnode->getRight();
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
				Trienode2 * child = curnode->getLeft();
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
};

#endif