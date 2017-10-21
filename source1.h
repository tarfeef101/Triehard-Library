#ifndef __source1_H__
#define __source1_H__
#include <iostream>
#include <vector>
using namespace std;
class Triehard // compressed binary trie
// constructor should make a left and right that are empty for search to work
// magnitude is 1 for length 1, so it must be >= 1
// flag means the value ending there is being stored
{
	private:
	
		class Trienode
		{
			private:
				
				int magnitude;
				bool flag;
				Trienode * left;
				Trienode * right;
				
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
				}
				*/
				
			public:
			
				Trienode(int magnitude, bool flag):
				magnitude{magnitude}, flag{flag}
				{
					left = nullptr;
					right = nullptr;
				}
				
				~Trienode() // Unsure about syntax, if this will play nicely with delete method
				{
					delete left;
					delete right;
					delete this;
				}
			
				int getMag()
				{
					return magnitude;
				}

				bool getFlag()
				{
					return flag;
				}
				
				/*
				//Side is 0 (left) or 1 (right)
				void print(int side, string output = "")
				{
					string val = getNodeVal(side);
					
					if(getFlag())
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
				
				Trienode * getLeft()
				{
					return left;
				}
				
				Trienode * getRight()
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
				
				void tFlag()
				{
					flag = true;
				}
				
				void fFlag()
				{
					flag = false;
				}
				
				Trienode * setLeft(int mag, bool flg)
				{
					left = new Trienode(mag, flg);
					return left;
				}
				
				Trienode * setRight(int mag, bool flg)
				{
					right = new Trienode(mag, flg);
					return right;
				}
				
				void copyLeft(Trienode * node)
				{
					left = node;
				}
				
				void copyRight(Trienode * node)
				{
					right = node;
				}
		};
		
		Trienode * left;
		Trienode * right;
	
	public:
	
		Triehard() // Initializes both sides as empty, but makes it searchable, mutatable
		{
			left = new Trienode(0, false);
			right = new Trienode(0, false);
		}
		
		~Triehard() // Same concern (syntax) as nodes, don't forget to write an erase method as well, maybe an empty/wipe
		{
			delete left;
			delete right;
			delete this;
		}
		
		/*
		void print()
		{
			//Default param arg seems to be a bit different
			//than i thought. Leaving it in the node print
			//function, try to fix later perhaps?
			if(left != nullptr)left->print(0);
			if(right != nullptr)right->print(1);
		} */
		
		// build an array of what is "processed" so far. then when a flag is hit, print that array. 
		void mainPrint(Trienode * curnode, vector<int> * chars, int right)
		{
			if (!curnode) return;			
			int curmag = curnode->getMag();
			
			while (curmag)
			{
				chars->push_back(right);
				--curmag;
			}
			
			if (curnode->getFlag())
			{
				int len = chars->size();
				cout << "This is the size: "  << len << endl;
				
				for (int i = 0; i < len; i++)
				{
					cout << (*chars)[i] << " ";
				}
				cout << endl;
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
		
		bool search(int * val, int len) // val is the string, len is its length
		{
			Trienode * curnode;
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
							return false;
						}
						
					}
					else
					{
						if (curmag)
						{
							return false;
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
							return false;
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
							return false;
						}
					}
					else
					{
						if (curmag)
						{
							return false;
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
							return false;
						}
					}
				}
			}
			
			return curnode->getFlag();
		}
		
		void insert(int * val, int len) // assumes valid input
		{						
			Trienode * curnode;
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
			
			for (int i = 0; i < len; i++)
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
						else if (curnode->getRight()) // If current node is "exhausted", move on to next one
						{
							curnode = curnode->getRight();
							curmag = curnode->getMag() - 1;
							continue;
						}
						else if (!(curnode->getLeft())) // if there are no subtrees, just increase this node's magnitude
						{
							curnode->addMag();
							continue;
						}
						else // we're on a "1" node, but it is depleted, and there is a left subtree. so, we create a new node to the right to represent this bit
						{
							curnode = curnode->setRight(1, false);
							continue;
						}
						
					}
					else // we're on a left subtree, but have a 1 coming up
					{
						if (curmag) // this means we have a value here, so we need to split this node up, branching to the right will be handled by following code
						{						
							Trienode * newnode = new Trienode(0, curnode->getFlag()); // this will be the second half of the big node
							curnode->fFlag(); // this and the getFlag ensure the flag is transferred properly
							
							while (curmag) // fills newnode with the extra magnitude
							{
								curnode->subMag();
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
							curnode = curnode->setRight(1, false);
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
						else if (!(curnode->getRight())) // no subtrees and we're on the correct side, so add to this node's magnitude
						{
							curnode->addMag();
							continue;
						}
						else // no 0s remaining, no left subtree, and we are going to add one.
						{
							curnode = curnode->setLeft(1, false);
							continue;
						}
					}
					else // we're on a right subtree but have a 0 coming up
					{
						if (curmag) // this means we have a value here, so we need to split this node up and branch to the left before this point
						{						
							Trienode * newnode = new Trienode(0, curnode->getFlag()); // this will be the second half of the big node
							curnode->fFlag(); // this and the getFlag ensure the flag is transferred properly
							
							while (curmag) // fills newnode with the extra magnitude
							{
								curnode->subMag();
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
							curnode = curnode->setLeft(1, false);
							side = false;
							continue;
						}
					}
				}
			}
			
			curnode->tFlag();
		}
		
		void cut(int * val, int len) // this is delete because i can't use delete :(
		{			
			Trienode * curnode;
			Trienode * prevnode = nullptr;
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
					right->fFlag();
				}
				else
				{
					left->fFlag();
				}
			}
			else if (curnode->getLeft() && curnode->getRight()) // we have shit to both sides, just unflag
			{
				curnode->fFlag();
			}
			else if (!(curnode->getLeft()) && !(curnode->getRight())) // if our node has no children, destroy it and change parent's reference to NULL
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
			else if (side && curnode->getLeft() && prevnode->getLeft() && side2 && !(prevnode->getFlag()) && !(prevnode->getLeft()))
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
			else if (!(side) && curnode->getRight() && prevnode->getRight() && !(side2) && !(prevnode->getFlag()) && !(prevnode->getRight()))
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
			else if ((side && curnode->getLeft()) || (!(side) && curnode->getRight()))
			// we are to the right and have shit to the left or vice versa
			{
				curnode->fFlag();
			}
			else if (side) // we are on the right and have shit to the right
			{
				Trienode * child = curnode->getRight();
				while (child->getMag()) // moves magnitude from child to parent we are removing
				{
					child->subMag();
					curnode->addMag();
				}
				
				if (child->getFlag()) curnode->tFlag(); // Sets flag based on child
				else curnode->fFlag();
				
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
				
				if (child->getFlag()) curnode->tFlag(); // Sets flag based on child
				else curnode->fFlag();
				
				curnode->copyLeft(child->getLeft()); // moves child's children to our parent node
				curnode->copyRight(child->getRight());
				child->copyLeft(nullptr); // Change child's children to null to allow for safe deletion
				child->copyRight(nullptr);
				delete child;
			}
		}
};

#endif