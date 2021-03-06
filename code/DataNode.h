// DataNode.h

#ifndef DATA_NODE_H_
#define DATA_NODE_H_

#include <list>
#include <string>
#include <vector>



// A DataNode is a single line of a DataFile. It consists of one or more tokens,
// which can be interpreted either as strings or as floating point values, and
// it may also have "children," which may each in turn have their own children.
// The tokens of a node are separated by white space, with quotation marks being
// used to group multiple words into a single token. If the token text contains
// quotation marks, it should be enclosed in backticks instead.
class DataNode {
public:
  // Construct a DataNode. For the purpose of printing stack traces, each node
  // must remember what its parent node is.
  explicit DataNode(const DataNode *parent = nullptr);
  // Copy constructor.
  DataNode(const DataNode &other);
  
  DataNode &operator=(const DataNode &other);
  
  // Get the number of tokens in this node.
  int Size() const;
  // Get the token at the given index. No bounds checking is done internally.
  const std::string &Token(int index) const;
  // Convert the token at the given index to a number. This returns 0 if the
  // index is out of range or the token cannot be interpreted as a number.
  double Value(int index) const;
  // Check if the token at the given index is a number in a format that this
  // class is able to parse.
  bool IsNumber(int index) const;
  
  // Check if this node has any children. If so, the iterator functions below
  // can be used to access them.
  bool HasChildren() const;
  std::list<DataNode>::const_iterator begin() const;
  std::list<DataNode>::const_iterator end() const;
  
  // Print a message followed by a "trace" of this node and its parents.
  int PrintTrace(const std::string &message = "") const;
  
  
private:
  // Adjust the parent pointers when a copy is made of a DataNode.
  void Reparent();
  
  
private:
  // These are "child" nodes found on subsequent lines with deeper indentation.
  std::list<DataNode> children;
  // These are the tokens found in this particular line of the data file.
  std::vector<std::string> tokens;
  // The parent pointer is used only for printing stack traces.
  const DataNode *parent = nullptr;
  
  // Allow DataFile to modify the internal structure of DataNodes.
  friend class DataFile;
};



#endif
